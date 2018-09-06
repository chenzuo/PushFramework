/********************************************************************
        File :			Dispatcher.cpp
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
#include "Dispatcher.h"



#include "ScopedLock.h"
#include "PhysicalConnection.h"
#include "ServerImpl.h"
#include "ServerStats.h"

#include "../include/Protocol.h"
#include "../include/ListenerOptions.h"
#include "XMLPacket.h"

#include "../include/ClientFactory.h"
#include "../include/LogicalConnection.h"
#include "../include/Service.h"
#include "../include/BroadcastManager.h"
#include "../include/Server.h"
#include "ChannelFactory.h"
#include "ClientFactoryImpl.h"

#include "BroadcastManagerImpl.h"

#include "MonitorsBroadcastManager.h"
#include "BroadcastStreamerManager.h"

#include "BroadcastQueue.h"
#include "StopWatch.h"
#include "Utilities.h"
#include "../include/ServerOptions.h"
#include "Acceptor.h"
#include "MonitorAcceptor.h"

namespace PushFramework
{

Dispatcher dispatcher;

Dispatcher::Dispatcher()
{
    ::InitializeCriticalSection(&csSrvMap);
}

Dispatcher::~Dispatcher(void)
{
    ::DeleteCriticalSection(&csSrvMap);
    for(serviceMapT::iterator it = serviceMap.begin();it != serviceMap.end();it++)
    {
        ServiceInfo* pInfo = it->second;
        if(pInfo->bManageDisposal){
                delete pInfo->pService;
        }
        delete pInfo;
    }
}

std::string Dispatcher::getServiceNames()
{
    std::stringstream ss;
    ss << std::noskipws;

    for (serviceMapT::iterator it = serviceMap.begin();
            it != serviceMap.end();
            it++)
    {
        ss << "<service val=\"" << it->second->serviceName << "\"/>";
    }

    return ss.str();
}

void Dispatcher::setCurrentService(std::string serviceName)
{
    ScopedLock lock(csSrvMap);
    ThreadIDType dwThread = Utilities::getCurrentThreadID();

    workerServiceMap[dwThread] = serviceName;
}

void Dispatcher::unsetCurrentService()
{
    ScopedLock lock(csSrvMap);
    ThreadIDType dwThread = Utilities::getCurrentThreadID();

    workerServiceMapT::iterator it = workerServiceMap.find(dwThread);
    if (it != workerServiceMap.end())
        workerServiceMap.erase(it);
}

bool Dispatcher::getCurrentService(std::string& serviceName)
{
    ScopedLock lock(csSrvMap);
    ThreadIDType dwThread = Utilities::getCurrentThreadID();

    workerServiceMapT::iterator it = workerServiceMap.find(dwThread);
    if (it == workerServiceMap.end())
        return false;

    serviceName = it->second;
    return true;
}

void Dispatcher::notifyObserversClientIN(const char* key, std::string peerIP, unsigned int peerPort)
{
	if (!options.isProfilingEnabled)
		return;

    std::string timestamp = Utilities::getCurrentTime();

    XMLPacket *response = new XMLPacket(AnalyticsProtocol::VisitorInResponse);
    response->setArgumentAsText("time", timestamp.c_str());
    response->setArgumentAsText("name", key);
    response->setArgumentAsText("ip", peerIP.c_str());
    response->setArgumentAsInt("port", peerPort);

    monitorBroadcastManager.pushPacket(response, "clientsIn", key, 0);
}

void Dispatcher::notifyObserversClientOut(const char* key)
{
	if (!options.isProfilingEnabled)
		return;
    
	XMLPacket *response = new XMLPacket(AnalyticsProtocol::VisitorOutResponse);
    response->setArgumentAsText("name", key);

    monitorBroadcastManager.pushPacket(response, "clientsOut");

    //Remove client from the other broadcast group :
    monitorBroadcastManager.removePacket(key, 0, "clientsIn");
}

void Dispatcher::handleInitialize(PhysicalConnection* pChannel)
{
    bool isClient = !pChannel->isObserverChannel();

    if (isClient)
    {
        ConnectionContext* lpContext = NULL;
        OutgoingPacket* pPacket = NULL;
        pPacket = pServerImpl->getClientFactory()->onNewConnection(lpContext);
        if (lpContext)
            pChannel->SetConnectionContext(lpContext);
        if (pPacket)
        {         
            pChannel->pushPacket(pPacket);
			theAcceptor.getProtocol()->disposeOutgoingPacket(pPacket);
        }
    }

    pChannel->postReceive();
    //
}

void Dispatcher::registerService(unsigned int uCommmand, Service* pService, std::string serviceName, bool bManageDisposal)
{
    ServiceInfo* pServiceInfo = new ServiceInfo;

    pServiceInfo->pService = pService;
    pServiceInfo->serviceName = serviceName;
	pServiceInfo->bManageDisposal = bManageDisposal;

    serviceMap[uCommmand] = pServiceInfo;
}

void Dispatcher::dispatchRequest( unsigned int uCommand,PushFramework::LogicalConnection* pClient,IncomingPacket& packet,unsigned int serviceBytes )
{
    serviceMapT::iterator it = serviceMap.find(uCommand);
    if (it == serviceMap.end())
        return;
    //
    ServiceInfo* pInfo = it->second;

    setCurrentService(pInfo->serviceName);

    StopWatch watch;
    pInfo->pService->handle(pClient, &packet);


    double duration = watch.getElapsedTime();
    stats.addToDistribution(ServerStats::PerformanceProcessingTimePerService, it->second->serviceName, duration);

    stats.addToDuration(ServerStats::PerformanceProcessingTime, duration);

    unsetCurrentService();

    //Stats. :

    stats.addToDistribution(ServerStats::BandwidthInboundVolPerRequest, it->second->serviceName, serviceBytes);
    stats.addToDistribution(ServerStats::PerformanceRequestVolPerRequest, it->second->serviceName, 1);
}

void Dispatcher::processFirstPacket(PhysicalConnection* pChannel, unsigned int uCommand, IncomingPacket& packet, unsigned int serviceBytes)
{
    OutgoingPacket* pOutPacket = NULL;
    //
    LogicalConnection* pClient;
    int iResult = pServerImpl->getClientFactory()->onFirstRequest(packet, pChannel->GetConnectionContext(), pClient, pOutPacket);

    //packet and lpContext are not good.
    if (iResult == ClientFactory::RefuseAndClose)
    {
		bool bWaitForSendToComplete = (pOutPacket != NULL);
        if (pOutPacket)
        {
            pChannel->pushPacket(pOutPacket);
			theAcceptor.getProtocol()->disposeOutgoingPacket(pOutPacket);
        }
        pChannel->closeConnection(bWaitForSendToComplete);
        return;
    }
    //
    if (iResult == ClientFactory::RefuseRequest)
    {
        if (pOutPacket)
        {
            pChannel->pushPacket(pOutPacket);
            theAcceptor.getProtocol()->disposeOutgoingPacket(pOutPacket);
        }
        return;
    }

    std::string clientKey = pClient->getKey();


    //iResult >= CClientFactory::CreateClient
    if (!channelFactory.removePhysicalConnection(pChannel))
    {
        if(pClient)
			pServerImpl->getClientFactory()->disposeClient(pClient);

        pChannel->decrementIoWorkersReferenceCounter();
        return;
    }


    //Bind the two structures.
    pClient->pPhysicalConnection = pChannel;
    pChannel->attachToClient(pClient); //status is attached.

    stats.addToCumul(ServerStats::VisitorsHitsIn, 1);

    LogicalConnection* pRet = clientFactoryImpl.addLogicalConnection(pClient);
    if (pRet != pClient)
    {
        //Copy data from existing to new instance.
        pServerImpl->getClientFactory()->CopyLogicalConnection(pRet, pClient);

        //Silent disconnect :
        clientFactoryImpl.silentDisconnect(pRet);

        //Now add ours :
        clientFactoryImpl.addLogicalConnection(pClient);

        //Fire Reconnect event.
        pServerImpl->getClientFactory()->onClientReconnected(pClient);

        //Add client to a streamer :
        broadcastStreamerManager.addClient(pClient);

        pClient->DecrementUsage();
        return;
    }

    //Fire connect event.
    pServerImpl->getClientFactory()->onClientConnected(pClient);
    //Add client to a streamer :
    broadcastStreamerManager.addClient(pClient);

    //Statistics :
    notifyObserversClientIN(clientKey.c_str(), pChannel->getPeerIP(), pChannel->getPeerPort());
    stats.addToCumul(ServerStats::VisitorsOnline, 1);

    if (iResult == ClientFactory::CreateAndRouteRequest)
    {
        dispatchRequest(uCommand, pClient, packet, serviceBytes);
    }
    else
    {
        if (pOutPacket)
        {
            pChannel->pushPacket(pOutPacket);
            theAcceptor.getProtocol()->disposeOutgoingPacket(pOutPacket);
        }
    }

    pClient->DecrementUsage();
}

void Dispatcher::handleMonitorRequest(PhysicalConnection* pChannel, IncomingPacket& packet)
{
    XMLPacket& requestPacket = (XMLPacket&) packet;


    int typeId = requestPacket.getTypeId();

    if (typeId == AnalyticsProtocol::LiveSubscriptionRequest)
    {
        bool bSubscribe = requestPacket.getArgumentAsBool("resume");
        if (bSubscribe)
        {
            OutgoingPacket* pInitPacket = stats.getInitializationPacket();
            pChannel->pushPacket(pInitPacket);
            monitorAcceptor.getProtocol()->disposeOutgoingPacket(pInitPacket);

            //
            monitorBroadcastManager.subscribeClient(pChannel->getLogicalConnectionKey(), "stats");
            monitorBroadcastManager.subscribeClient(pChannel->getLogicalConnectionKey(), "clientsIn");
            monitorBroadcastManager.subscribeClient(pChannel->getLogicalConnectionKey(), "clientsOut");
        }
        else
        {
            monitorBroadcastManager.removeClient(pChannel->getLogicalConnectionKey());
        }
    }


    if (typeId == AnalyticsProtocol::LogoutRequest)
    {
        pChannel->closeConnection(false);
    }

    if (typeId == AnalyticsProtocol::ConsoleCommandRequest)
    {
        std::string command = requestPacket.getArgumentAsText("command");

        XMLPacket response(AnalyticsProtocol::ConsoleCommandResponse);

        response.setArgumentAsText("client", requestPacket.getArgumentAsText("client"));

        if (command == "about")
        {
            std::string str = pServerImpl->getServerInfos() + "\nBased on PushFramework version 1.0";
            response.setArgumentAsText("console", str.c_str());
        }

        if (command == "profiling enable")
        {
            std::string str;
            if (options.isProfilingEnabled)
            {
                str = "Profiling is already enabled.";
            }
            else
            {
                options.isProfilingEnabled = false;
                str = "Profiling was enabled.";
            }
            response.setArgumentAsText("console", str.c_str());
        }

        if (command == "profiling disable")
        {
            std::string str;
            if (!options.isProfilingEnabled)
            {
                str = "Profiling is already disabled.";
            }
            else
            {
                options.isProfilingEnabled = false;
                str = "Profiling was disabled.";
            }
            response.setArgumentAsText("console", str.c_str());
        }

        if (command == "profiling status")
        {
            response.setArgumentAsText("console", (!options.isProfilingEnabled) ? "Profiling was found to be disabled." :
                                       "Profiling was found to be enabled.");
        }

        char pOut[256];

        bool bRet = pServerImpl->getFacade()->handleMonitorRequest(command.c_str(), pOut);

        if (bRet)
        {
            response.setArgumentAsText("console", pOut);
        }

        pChannel->pushPacket(&response);
    }

}

void Dispatcher::processMonitorFirstPacket(PhysicalConnection* pChannel, IncomingPacket& packet)
{
    XMLPacket& requestPacket = (XMLPacket&) packet;

    //
    XMLPacket response(AnalyticsProtocol::LoginResponse);

    std::string password = requestPacket.getArgumentAsText("password");

    if (password == options.password)
    {

        static int observerId = 1;
        observerId++;
        std::stringstream ss;
        ss << observerId;

        if (channelFactory.removePhysicalConnection(pChannel))
        {
            pChannel->attachToClient(ss.str().c_str());
            //
            monitorBroadcastManager.addMonitor(pChannel);
            //
            response.setArgumentAsText("result", "ok");
            pChannel->pushPacket(&response);
        }
        else
        {
            //Structure was removed by closeUnlogged.
        }
    }
    else
    {
        //Reply
        XMLPacket response(AnalyticsProtocol::LoginResponse);
        response.setArgumentAsText("result", "pass");
        pChannel->pushPacket(&response);
        //pChannel->close(true);
    }
}

void Dispatcher::handleFailedIO( PhysicalConnection* pChannel )
{
	pChannel->decrementIoWorkersReferenceCounter();
}


void Dispatcher::handleRead(PhysicalConnection* pChannel, int dwIoSize)
{
	int status = pChannel->getStatus();
	bool isClient = !pChannel->isObserverChannel();
	
	if (!pChannel->readReceivedBytes(dwIoSize))
	{
		if (status == PhysicalConnection::Attached && isClient)
		{
			clientFactoryImpl.disconnect(pChannel->getLogicalConnection(), false, ClientFactory::PeerClosure);
		}
		else
		{
			// Non attached + Monitor connections.
			pChannel->closeConnection(false);
		}
		pChannel->decrementIoWorkersReferenceCounter();
		return;
	}

	//The Processing Loop.
	int uCommandID;
	IncomingPacket* pPacket;
	int iResult;
	unsigned int uExtractedBytes;
	Protocol* pProtocol = pChannel->getProtocol();
	DataBuffer& sourceBuffer = pChannel->GetReceiveBuffer();

	bool bProcessDataInQueue = true;
	while (bProcessDataInQueue)
	{
		iResult = pProtocol->tryDeserializeIncomingPacket(sourceBuffer, pPacket, uCommandID, uExtractedBytes, pChannel->GetConnectionContext());

		if (iResult == Protocol::Success)
		{
			pChannel->GetReceiveBuffer().pop(uExtractedBytes);
			if (status == PhysicalConnection::Attached)
			{
				if (isClient)
					dispatchRequest(uCommandID, pChannel->getLogicalConnection(), *pPacket, uExtractedBytes);
				else
					handleMonitorRequest(pChannel, *pPacket);
			}
			else if (status == PhysicalConnection::Connected)
			{
				if (isClient)
					processFirstPacket(pChannel, uCommandID, *pPacket, uExtractedBytes);
				else
					processMonitorFirstPacket(pChannel, *pPacket);
			}
			else
			{
				//Status changed by another thread eg ::disconnect.
				bProcessDataInQueue = false;
			}
			pProtocol->disposeIncomingPacket(pPacket);
		}
		else if (iResult == Protocol::eDecodingFailure)
		{
			pChannel->GetReceiveBuffer().pop(uExtractedBytes);
		}
		else
			break;
	}
	//
	if (iResult == Protocol::eIncompletePacket && pChannel->getStatus() >= PhysicalConnection::Connected)
	{
		pChannel->postReceive();
	}

	pChannel->decrementIoWorkersReferenceCounter();
}

void Dispatcher::handleWrite( PhysicalConnection* pChannel, int dwIoSize )
{
	bool bIsBufferIdle;
	int status = pChannel->getStatus();

	if (!pChannel->OnSendCompleted(dwIoSize, bIsBufferIdle))
	{
		if (!pChannel->isObserverChannel() && status == PhysicalConnection::Attached)
		{
			clientFactoryImpl.disconnect(pChannel->getLogicalConnection(), false, ClientFactory::PeerClosure);
		}
		else
		{
			pChannel->closeConnection(false);
		}
		pChannel->decrementIoWorkersReferenceCounter();
		return;
	}

	if (status == PhysicalConnection::Attached)
	{
		if (pChannel->isObserverChannel() && bIsBufferIdle)
			monitorBroadcastManager.sendStatsToMonitor(pChannel);

		if (!pChannel->isObserverChannel())
			pChannel->getLogicalConnection()->OnReadyForSend(pChannel->GetSendBuffer().getRemainingSize());
	}

	pChannel->decrementIoWorkersReferenceCounter();
}
}

