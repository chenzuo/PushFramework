#include "StdAfx.h"
#include "TCPSocketImpl.h"




#include "TCPSocket.h"
#include "ResponseHandler.h"

#include "ScopedLock.h"


#define nReceiveBufferSize 1024 * 8/*8192*/
#define nSendBufferSize 1024 * 8/*8192*/

TCPSocketImpl::TCPSocketImpl(TCPSocket* pFacade)
    : oBuffer(nSendBufferSize), inBuffer(nReceiveBufferSize)
{

    this->pFacade = pFacade;

    status = TCPSocket::Disconnected;

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

bool TCPSocketImpl::connect(const char* hostAddress, unsigned int uPort)
{
    ScopedLock lock(cs);

    if (status != TCPSocket::Disconnected)
        return true;

    this->strIP = hostAddress;
    this->uPort = uPort;

    //Create the socket :
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (hSocket < 0)
    {
        return false;
    }

    int on = 1;
    if (setsockopt(hSocket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof (on)))
    {
        cout << "Could not set socket %d option for reusability" << endl;
        close(hSocket);
        return false;
    }

    //Set as non-blocking before processing events:
    if (fcntl(hSocket, F_SETFL, O_NONBLOCK))
    {
        close(hSocket);
        return false;
    }


    sockaddr_in saServer;
    memset(&saServer, 0, sizeof (saServer));

    saServer.sin_family = AF_INET;
    saServer.sin_addr.s_addr = inet_addr(strIP.c_str());
    saServer.sin_port = htons(uPort);

    int nRet = ::connect(hSocket, (sockaddr*) & saServer, sizeof (saServer));

    if (nRet < 0 && errno != EINPROGRESS)
    {
        perror("Connection Issue");
        close(hSocket);
        return false;
    }


    status = TCPSocket::Connecting;


    pthread_create(&hThread, NULL, threadProc, (void*) this);


    return true;
}

void* TCPSocketImpl::threadProc(void* lParam)
{
    TCPSocketImpl* pThis = reinterpret_cast<TCPSocketImpl*> (lParam);

    pThis->doClientLoop();

    return 0;
}

bool TCPSocketImpl::OnConnect()
{
    ScopedLock lock(cs);

    status = TCPSocket::Connected;

    pFacade->onConnected(true);

    return true;
}

bool TCPSocketImpl::OnClose()
{
    status = TCPSocket::Disconnected;

    pFacade->onConnected(false);

    return false;
}

bool TCPSocketImpl::OnRead()
{

    int nMaxToPick = inBuffer.getRemainingSize();

    if (nMaxToPick == 0)
    {
        //Fatal
        return false;
    }


    int ret = recv(hSocket, inBuffer.GetBuffer() + inBuffer.GetDataSize(), nMaxToPick, 0);
    if (ret == -1)
        return true;

    if (ret == 0)
    {
        pFacade->onConnectionClosed(true);
        return false;
    }


    if(status == TCPSocket::Connecting)
    {
        OnConnect();
    }
    inBuffer.GrowSize(ret);



    //Now Try depacketize :
    int uCommmandID;
    PushFramework::IncomingPacket* pPacket = NULL;
    int iResult;
    unsigned int uExtractedBytes;

    while (true)
    {
        iResult = pProtocol->tryDeserializeIncomingPacket(inBuffer, pPacket, uCommmandID, uExtractedBytes);

        if (iResult == PushFramework::Protocol::Success)
        {
            inBuffer.Pop(uExtractedBytes);
            //
            dispatchResponse(uCommmandID, *pPacket);
            pProtocol->disposeIncomingPacket(pPacket);
        }
        else if (iResult == PushFramework::Protocol::eDecodingFailure)
        {
            inBuffer.Pop(uExtractedBytes);
        }
        else
            break;
    }
    if (iResult != PushFramework::Protocol::eIncompletePacket)
    {
        close(hSocket);
        return false;
    }
    return true;
}

void TCPSocketImpl::registerHandler(unsigned int requestId, ResponseHandler* pHandler)
{
    handlerMap[requestId] = pHandler;
}

void TCPSocketImpl::dispatchResponse(unsigned int requestId, PushFramework::IncomingPacket& packet)
{
    handlerMapT::iterator it = handlerMap.find(requestId);
    if (it == handlerMap.end())
        return;

    ResponseHandler* pHandler = it->second;
    pHandler->handleResponse(packet);
}

void TCPSocketImpl::setProtocol(PushFramework::Protocol* pProtocol)
{
    this->pProtocol = pProtocol;
}

bool TCPSocketImpl::sendRequest(PushFramework::OutgoingPacket* pPacket)
{
    unsigned int uWrittenBytes = 0;
    int iResult = pProtocol->serializeOutgoingPacket(*pPacket, oBuffer, uWrittenBytes);
    //int iResult = pProtocol->serializeOutgoingPacket(pPacket, oBuffer.GetBuffer()+ oBuffer.GetDataSize(), oBuffer.GetMaxDataSize() - oBuffer.GetDataSize(), uWrittenBytes);
    if (iResult != PushFramework::Protocol::Success)
    {
        return false;
    }
    //oBuffer.GrowSize(uWrittenBytes);
    return WriteBytes();
}

bool TCPSocketImpl::WriteBytes()
{
    if (oBuffer.GetDataSize() == 0)
    {
        return true;
    }

    unsigned int uSize = min((unsigned int)4096, oBuffer.GetDataSize());

    int dwBytes = send(hSocket, oBuffer.GetBuffer(), uSize, 0);

    if (dwBytes < 0)
    {
        if (dwBytes == EAGAIN)
        {
            bSendInProgress = true;
            return true;
        }
        else
        {
            close(hSocket);
            return false;
        }
    }
    else
    {
        oBuffer.Pop(uSize);
        return WriteBytes();
    }
}

bool TCPSocketImpl::OnWrite()
{

    bSendInProgress = false;

    return WriteBytes();
}

int TCPSocketImpl::getStatus()
{
    return status;
}

void TCPSocketImpl::disconnect(bool waitForSend)
{
    if (waitForSend && oBuffer.GetDataSize() != 0)
    {
        status = TCPSocket::WaitingToClose;
        return;
    }

    close(hSocket);
    //Stop the processing thread.


    stopClient = true;




    status = TCPSocket::Disconnected;
}

void TCPSocketImpl::doClientLoop(bool bServerMode/* = false*/)
{
    int pollsize = 1024;
    int pollQueue = epoll_create(pollsize);

    if (pollQueue < 0)
    {
        cout << "unable to create pollQueue" << endl;
        return;
    }

    epoll_event ev;
    ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
    ev.data.ptr = 0;

    if (epoll_ctl(pollQueue, EPOLL_CTL_ADD, hSocket, &ev) < 0)
    {

        return;
    }


    int epollArraySize = 64;
    struct epoll_event epoll_events[64];



    while (!stopClient)
    {
        int rval = epoll_wait(pollQueue, epoll_events, epollArraySize, 1000);

        if (rval == 0)
        {
            //cout << "timeout happened" << endl;
            pFacade->onPerformAutomatedJob();
            continue;
        }

        if (rval < 0)
        {
            if (errno == EAGAIN || errno == EINTR)
            {
                continue;
            }
            perror("Error on epoll_wait");
            break;
        }

        //
        for (int i = 0; i < rval; i++)
        {
            //
            uint32_t events = epoll_events[i].events;
            int fd = epoll_events[i].data.fd;
            void* lpObject = (epoll_events[i].data.ptr);


            if (events & EPOLLERR ||
                    events & EPOLLHUP ||
                    events & EPOLLRDHUP)
            {
                if (!OnConnect())
                    break;
            }



            //
            if (events & EPOLLOUT)
            {
                if (!OnWrite())
                    break;
            }
            if (events & EPOLLIN)
            {
                if (!OnRead())
                    break;
            }

        }
    }

    status = TCPSocket::Disconnected;
}

bool TCPSocketImpl::listen(int uListenPort, const char* interfaceAddress)
{
    return false;
}
void TCPSocketImpl::stopServer()
{
    //
}





