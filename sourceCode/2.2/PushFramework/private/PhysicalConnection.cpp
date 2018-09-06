/********************************************************************
	File :			PhysicalConnection.cpp
	Creation date :	2010/6/27

	License :			Copyright 2010 Ahmed Charfeddine, http://www.pushframework.com

				   Licensed under the Apache License, Version 2.0 (the "License");
				   you may not use this file except in compliance with the License.
				   You may obtain a copy of the License at

					   http://www.apache.org/licenses/LICENSE-2.0

				   Unless required by applicable law or agreed to in writing, software
				   distributed under the License is distributed on an "AS IS" BASIS,
				   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
				   See the License for the specific language governing permissions and
				   limitations under the License.


*********************************************************************/
#include "StdAfx.h"
#include "PhysicalConnection.h"

#ifdef Plateform_Windows
#include "IOQueue_Win.h"
#else

#ifdef Plateform_Linux
#include "IOQueue_Linux.h"
#endif
#endif

#include "ServerImpl.h"

#include "Dispatcher.h"
#include "ServerStats.h"

#include "ScopedLock.h"

#include "../include/LogicalConnection.h"
#include "../include/ConnectionContext.h"
#include "../include/ServerOptions.h"
#include "Acceptor.h"
#include "MonitorAcceptor.h"


namespace PushFramework
{
PhysicalConnection::PhysicalConnection()
{

    oBuffer.allocate(options.uIntermediateSendBufferSize);
    inBuffer.allocate(options.uIntermediateReceiveBufferSize);

#ifdef Plateform_Windows
    m_byInBuffer	= NULL;
    m_byOutBuffer	= NULL;
    m_byInBuffer = new BYTE[options.uReadBufferSize];
    m_byOutBuffer = new BYTE[options.uSendBufferSize];

    m_wsaInBuffer.buf = (char*)m_byInBuffer;
    m_wsaInBuffer.len = options.uReadBufferSize;
    m_wsaOutBuffer.buf = (char*)m_byOutBuffer;
    m_wsaOutBuffer.len = options.uSendBufferSize;
    pReadOverlap = new OVERLAPPEDPLUS(IORead);
    pWriteOverlap = new OVERLAPPEDPLUS(IOWrite);
#endif

	pConnectionContext = NULL;

    ::InitializeCriticalSection(&csLock);
}

void PhysicalConnection::reset( SOCKET s, SOCKADDR_IN address, bool bIsObserver )
{
	this->socket = s;

	rPeerPort = address.sin_port;
	rPeerIP = inet_ntoa(address.sin_addr);

	dtCreationTime = time(NULL);

	bWriteInProgress = FALSE;

	this->bIsObserver = bIsObserver;

	status = Connected;

	ioWorkersReferenceCounter = 0;

	broadcastCxt.nSentPackets = 0;
	broadcastCxt.pCurrentSinkChannel = NULL;

	delete pConnectionContext;
	pConnectionContext = NULL;
}

PhysicalConnection::~PhysicalConnection(void)
{
#ifdef Plateform_Windows
	if( m_byOutBuffer )
		delete [] m_byOutBuffer;

	if( m_byInBuffer)
		delete [] m_byInBuffer;

    if(pReadOverlap)
        delete pReadOverlap;
    if(pWriteOverlap)
        delete pWriteOverlap;
#endif
    ::DeleteCriticalSection(&csLock);
	delete pConnectionContext;
}

int PhysicalConnection::getStatus()
{
    return status;
}

double PhysicalConnection::getLifeDuration()
{
    time_t current = time(NULL);
    return difftime(current, dtCreationTime);
}
SendResult PhysicalConnection::tryPushPacket( OutgoingPacket* pPacket )
{
    if (TryEnterCriticalSection(&csLock))
    {
        SendResult result = pushPacketCommon(pPacket);
        LeaveCriticalSection(&csLock);
        return result;
    }
    return SendResult_Retry;
}
SendResult PhysicalConnection::pushPacket( OutgoingPacket* pPacket )
{
    ScopedLock lock(csLock);
    return pushPacketCommon(pPacket);

}

const char* PhysicalConnection::getLogicalConnectionKey()
{
    if (isObserverChannel())
    {
        return clientKey.c_str();
    }
    else
        return pLogicalConnection->getKey();
}

void PhysicalConnection::SetConnectionContext( ConnectionContext* pConnectionContext )
{
    this->pConnectionContext = pConnectionContext;
}

ConnectionContext* PhysicalConnection::GetConnectionContext()
{
    return pConnectionContext;
}

DataBuffer& PhysicalConnection::GetReceiveBuffer()
{
    return inBuffer;
}

void PhysicalConnection::attachToClient( LogicalConnection* pLogicalConnection )
{
    this->pLogicalConnection = pLogicalConnection;
    status = Attached;
}

void PhysicalConnection::attachToClient( std::string clientKey )
{
    this->clientKey = clientKey;
    status = Attached;
}

bool PhysicalConnection::isObserverChannel()
{
    return bIsObserver;
}

UINT PhysicalConnection::getPeerPort()
{
    return rPeerPort;
}

std::string PhysicalConnection::getPeerIP()
{
    return rPeerIP;
}

Protocol* PhysicalConnection::getProtocol()
{
	return bIsObserver ? monitorAcceptor.getProtocol() : theAcceptor.getProtocol();
}

LogicalConnection* PhysicalConnection::getLogicalConnection()
{
    return pLogicalConnection;
}

void PhysicalConnection::incrementIoWorkersReferenceCounter()
{
    AtomicIncrement(&ioWorkersReferenceCounter);
}

void PhysicalConnection::decrementIoWorkersReferenceCounter()
{
    AtomicDecrement(&ioWorkersReferenceCounter);
}

int PhysicalConnection::getIoWorkersReferenceCounter() const
{
    return ioWorkersReferenceCounter;
}

SOCKET PhysicalConnection::getSocket()
{
    return socket;
}

PushFramework::SendResult PhysicalConnection::pushPacketCommon( OutgoingPacket* pPacket )
{
    if (status < Connected)
    {
        return SendResult_NotOK;
    }

    unsigned int uWrittenBytes = 0;

	Protocol* pProtocol = getProtocol();

    int iResult = pProtocol->serializeOutgoingPacket(*pPacket, oBuffer, uWrittenBytes);

    if (iResult!=Protocol::Success)
    {
        stats.addToCumul(ServerStats::BandwidthRejection, uWrittenBytes);
        return iResult==Protocol::eInsufficientBuffer ? SendResult_Retry : SendResult_NotOK;
    }

    stats.addToCumul(ServerStats::BandwidthOutstanding, uWrittenBytes);
    std::string serviceName;
    if (dispatcher.getCurrentService(serviceName))
    {
        stats.addToDistribution(ServerStats::BandwidthOutboundVolPerRequest, serviceName, uWrittenBytes);
    }

    //oBuffer.GrowSize(uWrittenBytes);

    if (!bWriteInProgress)
    {
        return WriteBytes() ? SendResult_OK : SendResult_NotOK;
    }
    return SendResult_OK;
}

double PhysicalConnection::getTimeToLastReceive()
{
	time_t current = time(NULL);
	return difftime(current, dtLastReceiveTime);
}

DataBuffer& PhysicalConnection::GetSendBuffer()
{
	return oBuffer;
}






}
