#include "StdAfx.h"
#include "TCPSocketImpl.h"

#include <process.h>


#include "TCPSocket.h"
#include "TCPSocketEvents.h"
#include "ResponseHandler.h"

#include "ScopedLock.h"

#define nSendWindow	8192
#define nReceiveWindow 8192
#define nReceiveBufferSize (nReceiveWindow * 4)
#define nSendBufferSize (nSendWindow * 4)


#include <stdio.h>
#include <tchar.h>

#include <conio.h>
#include <ctype.h>
#include <mmsystem.h>




TCPSocketImpl::TCPSocketImpl(TCPSocket* pFacade)
    :oBuffer(nSendBufferSize), inBuffer(nReceiveBufferSize)
{

    this->pFacade = pFacade;

    status = TCPSocket::Disconnected;

    hSocket = NULL;
    hSocketEvent = NULL;

    hThread = NULL;

    bSendInProgress = false;

    ::InitializeCriticalSection(&cs);
}

TCPSocketImpl::~TCPSocketImpl()
{
    //Stop processing thread :
    if (status != TCPSocket::Disconnected)
    {
        disconnect(false);
    }
    ::DeleteCriticalSection(&cs);
}


bool TCPSocketImpl::connect( const char* hostAddress, unsigned int uPort )
{
    ScopedLock lock(cs);

    if(status != TCPSocket::Disconnected)
        return true;

    this->strIP = hostAddress;
    this->uPort = uPort;


    hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (hSocket == INVALID_SOCKET)
    {
        return false;
    }


	int windowSize = nSendWindow;

	int nErr = setsockopt(hSocket, SOL_SOCKET, SO_SNDBUF, (char*) &windowSize, sizeof(windowSize));
	if (nErr == -1)
	{
		closesocket(hSocket);
		return false;
	}
	windowSize = nReceiveWindow;
	nErr = setsockopt(hSocket, SOL_SOCKET, SO_RCVBUF, (char*) &windowSize, sizeof(windowSize));
	if (nErr == -1)
	{
		closesocket(hSocket);
		return false;
	}


    SOCKADDR_IN		saServer;
    memset(&saServer,0,sizeof(saServer));

    saServer.sin_family = AF_INET;
    saServer.sin_addr.s_addr = inet_addr(strIP.c_str());
    saServer.sin_port = htons(uPort);

    int nRet = ::connect(hSocket,(sockaddr*)&saServer, sizeof(saServer));

    if (nRet == SOCKET_ERROR &&
            WSAGetLastError() != WSAEWOULDBLOCK)
    {
        int iError = WSAGetLastError();

        closesocket(hSocket);
        return false;
    }

    bool m_bInProgress = true;

    hSocketEvent = WSACreateEvent();
    if (hSocketEvent == WSA_INVALID_EVENT)
    {
        closesocket(hSocket);
        return FALSE;
    }

    nRet = WSAEventSelect(hSocket,
                          hSocketEvent,
                          FD_CONNECT|FD_CLOSE|FD_READ|FD_WRITE);

    if (nRet == SOCKET_ERROR)
    {
        closesocket(hSocket);
        return false;
    }

    status = TCPSocket::Connecting;

    hKillEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    UINT m_dwThreadId;
    hThread = (HANDLE)_beginthreadex(NULL, 0, networkJobsThreadProc, (void*) this, 0, &m_dwThreadId);

    return true;
}



unsigned __stdcall TCPSocketImpl::networkJobsThreadProc( LPVOID lParam )
{
    TCPSocketImpl* pThis = reinterpret_cast<TCPSocketImpl*>(lParam);

    pThis->doNetworkJobs();

    return 0;
}


bool TCPSocketImpl::OnConnect()
{
    ScopedLock lock(cs);

    status = TCPSocket::Connected;

    if (pFacade->isRelayTCPEvents())
    {
        TCPSocketEvent* pEvent = new TCPSocketEvent;
        pEvent->type = TCPSocketEvent::ConnectionEstablished;
        pFacade->PostTCPEvent(pEvent);
    }
    else
        pFacade->onConnected();       

    return true;
}

bool TCPSocketImpl::OnClose()
{
    return false;
}

bool TCPSocketImpl::OnRead()
{
    DWORD dwSize = 0;
    int nRet = ioctlsocket(hSocket, FIONREAD, &dwSize);

    if (nRet == -1)
        return true;

    if (dwSize == 0)
    {
        return false;
    }


    int nBytesToBeRead = min(dwSize, inBuffer.getRemainingSize());

    BYTE* pData = new BYTE[nBytesToBeRead];

    int nRead = recv(hSocket, (char*) pData, nBytesToBeRead, 0);
    if (nRead == -1)
        return true;


    inBuffer.append((char*)pData, nRead);

    delete [] pData;


    //Now Try depacketize :
    int uCommmandID;
    PushFramework::IncomingPacket* pPacket = NULL;
    int iResult;
    unsigned int uExtractedBytes;

    while (true)
    {
        iResult = pProtocol->tryDeserializeIncomingPacket(inBuffer, pPacket, uCommmandID, uExtractedBytes, NULL);
        if (iResult == PushFramework::Protocol::Success)
        {
            inBuffer.pop(uExtractedBytes);
            //
            if (pFacade->isRelayTCPEvents())
            {
                TCPSocketEvent* pEvent = new TCPSocketEvent;
                pEvent->type = TCPSocketEvent::NewMessage;
                pEvent->commandId = uCommmandID;
                pEvent->pPacket = pPacket;
                pFacade->PostTCPEvent(pEvent);
            }
            else
            {
                dispatchResponse(uCommmandID, *pPacket);
                pProtocol->disposeIncomingPacket(pPacket);
            }
        }
        else if (iResult == PushFramework::Protocol::eDecodingFailure)
        {
            inBuffer.pop(uExtractedBytes);
        }
        else
            break;
    }
    if (iResult != PushFramework::Protocol::eIncompletePacket)
    {
        
        closesocket(hSocket);
        return false;
    }
    return true;
}

void TCPSocketImpl::registerHandler( unsigned int requestId, ResponseHandler* pHandler )
{
    handlerMap[requestId] =  pHandler;
}

void TCPSocketImpl::dispatchResponse( unsigned int requestId, PushFramework::IncomingPacket& packet )
{
    handlerMapT::iterator it = handlerMap.find(requestId);
    if (it==handlerMap.end())
        return;

    ResponseHandler* pHandler = it->second;
    pHandler->handleResponse(packet);
}

void TCPSocketImpl::setProtocol( PushFramework::Protocol* pProtocol )
{
    this->pProtocol = pProtocol;
}

int TCPSocketImpl::sendRequest( PushFramework::OutgoingPacket* pPacket )
{
    unsigned int uWrittenBytes = 0;
    int iResult = pProtocol->serializeOutgoingPacket(*pPacket, oBuffer, uWrittenBytes);
	if (iResult == PushFramework::Protocol::eInsufficientBuffer)
	{
		//The intermediate buffer is still full.
		//Caller should try later when pending write operation succeed and make some room in the buffer.
		return TCPSocket::ResultTryAgain;
	}
    if (iResult!=PushFramework::Protocol::Success)
    {
		//For any other reason, caller should not retry with the same packet.
		return TCPSocket::ResultFailed;
    }
	if (WriteBytes())
	{
		return TCPSocket::ResultOK;
	}
	else
		return TCPSocket::ResultFailed;
}

bool TCPSocketImpl::WriteBytes()
{
    if (oBuffer.getDataSize()==0)
    {
        return true;
    }

    unsigned int uSize = min(nSendWindow, oBuffer.getDataSize());

    int dwBytes = send(hSocket, oBuffer.getBuffer(), uSize,0);

    if (dwBytes == SOCKET_ERROR)
    {
        if (GetLastError() == WSAEWOULDBLOCK)
        {
            bSendInProgress = true;
            return true;
        }
        else
        {
            closesocket(hSocket);
            return false;
        }
    }
    else
    {
        oBuffer.pop(dwBytes);
        return WriteBytes();
    }
}

bool TCPSocketImpl::OnWrite()
{
    bSendInProgress = false;

    if (oBuffer.getDataSize()==0)
    {

        pFacade->OnReadyToSend();

        return true;
    }

    return WriteBytes();
}

int TCPSocketImpl::getStatus()
{
    return status;
}

void TCPSocketImpl::disconnect( bool waitForSend )
{
    if (waitForSend && oBuffer.getDataSize()!=0)
    {
        status = TCPSocket::WaitingToClose;
        return;
    }

    closesocket(hSocket);
    //Stop the processing thread.

    ::SetEvent(hKillEvent);

	WaitForSingleObject(hThread, INFINITE);

    status = TCPSocket::Disconnected;
}

const char* TCPSocketImpl::explainLastError()
{
    DWORD dwIOError = GetLastError();

    LPVOID lpMsgBuf;

    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dwIOError,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR) &lpMsgBuf,
        0, NULL );

    return (LPCSTR)lpMsgBuf;
}
PushFramework::Protocol* TCPSocketImpl::getProtocol()
{
    return pProtocol;
}

HANDLE TCPSocketImpl::CreatePeriodicTimer() 
{
    HANDLE hTimer = NULL;
    LARGE_INTEGER liDueTime;

    const int unitsPerSecond=10*1000*1000; // 100 nano seconds

    // Set the event the first time 1 seconds
    // after calling SetWaitableTimer

    liDueTime.QuadPart=-(1*unitsPerSecond);

    // Create an unnamed waitable timer.
    hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
    if (NULL == hTimer)
    {
        return NULL;
    }

    // Set a timer to wait for 10 seconds.
    if (!SetWaitableTimer(hTimer, &liDueTime, 1000, NULL, NULL, 0))
    {
        return NULL;
    }
    return hTimer;
}
void TCPSocketImpl::doNetworkJobs()
{
    HANDLE hTimer = CreatePeriodicTimer();


    //
    HANDLE			hWaits[3];
    hWaits[0]		= hKillEvent;
    hWaits[1]		= hTimer;
    hWaits[2]		= hSocketEvent;

    DWORD dwRet;

    WSANETWORKEVENTS events;

    while (true)
    {
        dwRet = WSAWaitForMultipleEvents(3, hWaits,	FALSE, INFINITE, FALSE);

        if (dwRet == WAIT_OBJECT_0)
        {
            break;
        }
        
        if (dwRet == WAIT_OBJECT_0 + 1)
        {
            pFacade->onPerformAutomatedJob();
            continue;
        }

        // Figure out what happened
        int nRet = WSAEnumNetworkEvents(hSocket, hSocketEvent, &events);

        if (nRet == SOCKET_ERROR)
        {
            int ierror = WSAGetLastError();
            break;
        }

        //Dispatch event :
        if(events.lNetworkEvents & FD_CONNECT)
        {
            if(!OnConnect())
                break;
        }

        if(events.lNetworkEvents & FD_READ)
        {
            if(!OnRead())
                break;
        }

        if(events.lNetworkEvents & FD_CLOSE)
        {
            if(!OnClose())
                break;
        }


        if(events.lNetworkEvents & FD_WRITE)
        {
            if(!OnWrite())
                break;
        }
    }

    CloseHandle(hKillEvent);

    WSACloseEvent(hSocketEvent);
    status = TCPSocket::Disconnected;

	if (dwRet != WAIT_OBJECT_0)
	{
		if (pFacade->isRelayTCPEvents())
		{
			TCPSocketEvent* pEvent = new TCPSocketEvent;
			pEvent->type = TCPSocketEvent::ConnectionClosed;
			pFacade->PostTCPEvent(pEvent);
		}
		else
			pFacade->onConnectionClosed();
	}
    
}