/********************************************************************
	File :			MonitorsBroadcastManager.cpp
	Creation date :	2012/01/29

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
#include "MonitorsBroadcastManager.h"

#include "ChannelFactory.h"
#include "XMLPacket.h"

#include "PhysicalConnection.h"
#include "BroadcastContext.h"

#include "ScopedLock.h"
#include "../include/QueueOptions.h"

namespace PushFramework
{

MonitorsBroadcastManager monitorBroadcastManager;

MonitorsBroadcastManager::MonitorsBroadcastManager()
{
    QueueOptions options;
    //
    options.maxPackets = 100;
    options.requireRegistration = true;
    options.priority = 10;
    options.packetsQuota = 10;
    options.fillRateThrottlingPeriod = 60;
    options.fillRateThrottlingMaxPackets = 100;

    createBroadcastQueue("stats", options);

    options.maxPackets = 1000;
    options.priority = 5;
    options.packetsQuota = 5;

    createBroadcastQueue("clientsIn", options);

    options.maxPackets = 50;

    createBroadcastQueue("clientsOut", options);

    InitializeCriticalSection(&cs);
}

MonitorsBroadcastManager::~MonitorsBroadcastManager( void )
{
    DeleteCriticalSection(&cs);
}

void MonitorsBroadcastManager::activateSubscribers( std::string channelName )
{
    sendStatsToAllMonitors();
}

void MonitorsBroadcastManager::preEncodeOutgoingPacket( OutgoingPacket* pPacket )
{
    //Nothing to do, packet is already encoded.
}

void MonitorsBroadcastManager::deleteOutgoingPacket( OutgoingPacket* pPacket )
{
    delete pPacket;
}

bool MonitorsBroadcastManager::sendStatsToMonitor( PhysicalConnection* pMonitorChannel )
{
    if (pMonitorChannel->checkIfUnusedByIOWorkers())
        return true;

    BroadcastQueueInfo* pFoundInfo = NULL;
    PacketInfo* pPacketInfo = NULL;

    std::string subscriberKey = pMonitorChannel->getLogicalConnectionKey();
    BroadcastContext& broadcastCtxt = pMonitorChannel->broadcastCxt;

    unsigned int nRetryCount = 0;
    while (true)
    {
        OutgoingPacket* pPacket = getNextPacket(subscriberKey, broadcastCtxt, pPacketInfo, pFoundInfo);
        if (!pPacket)
            return false;

        SendResult result = pMonitorChannel->pushPacket(pPacket);
        disposePacket(pPacketInfo, subscriberKey, pFoundInfo, broadcastCtxt, result == SendResult_OK);

        if (result == SendResult_NotOK)
        {
            return false;
        }
        if (result == SendResult_Retry)
        {
            nRetryCount++;
            if(nRetryCount >= 5)
                return false;
        }
    }
}

void MonitorsBroadcastManager::sendStatsToAllMonitors()
{
    ScopedLock lock(cs);
    //
    vectConnectionsT::iterator it = vectMonitorsConnections.begin();
    while (it != vectMonitorsConnections.end())
    {
        PhysicalConnection* pMonitor = *it;
        if (sendStatsToMonitor(pMonitor))
        {
            it = vectMonitorsConnections.erase(it);
            delete pMonitor;
        }
        else
            it++;
    }
}

void MonitorsBroadcastManager::addMonitor( PhysicalConnection* pMonitor )
{
    ScopedLock lock(cs);
    //
    vectMonitorsConnections.push_back(pMonitor);
    //
}

}

