/********************************************************************
	File :			ClientFactoryImpl.cpp
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
#include "ClientFactoryImpl.h"


#include "../include/LogicalConnection.h"
#include "../include/ClientFactory.h"
#include "PhysicalConnection.h"
#include "ServerImpl.h"
#include "ServerStats.h"
#include "../include/BroadcastManager.h"
#include "BroadcastManagerImpl.h"
#include "BroadcastStreamerManager.h"
#include "Dispatcher.h"
#include "GarbageCollector.h"

#include "ScopedLock.h"


namespace PushFramework
{

PUSHFRAMEWORK_API void ReturnClient(LogicalConnection* pClient)
{
    clientFactoryImpl.returnClient(pClient);
}
PUSHFRAMEWORK_API LogicalConnection* FindClient(CLIENT_KEY clientName)
{
    return clientFactoryImpl.findLogicalConnection(clientName);
}
PUSHFRAMEWORK_API void Disconnect( LogicalConnection* pLogicalConnection, bool waitForPendingPackets )
{
	clientFactoryImpl.disconnect(pLogicalConnection, waitForPendingPackets, ClientFactory::ForceableClosure);
}



ClientFactoryImpl clientFactoryImpl;

ClientFactoryImpl::ClientFactoryImpl()
{
    nClientsCount = 0;
    ::InitializeCriticalSection(&cs);
}

ClientFactoryImpl::~ClientFactoryImpl(void)
{
    ::DeleteCriticalSection(&cs);
}

LogicalConnection* ClientFactoryImpl::addLogicalConnection( LogicalConnection* pClient )
{
    std::string key(pClient->getKey());
    ScopedLock csLock(cs);
    //
    LogicalConnection* pRet = pClient;

    clientMapT::iterator it = clientMap.find(key);
    if(it!=clientMap.end())
    {
        pRet =  it->second;
    }
    else
    {
        clientMap[key] = pClient;
        nClientsCount++;
    }

    pRet->IncrementUsage();
    return pRet;
}




LogicalConnection* ClientFactoryImpl::findLogicalConnection( const char* _key )
{
    std::string key(_key);
    //
    ScopedLock csLock(cs);

    clientMapT::iterator it = clientMap.find(key);
    if(it==clientMap.end())
        return NULL;

    LogicalConnection* pClient = it->second;

    pClient->IncrementUsage();
    return pClient;
}


Server* ClientFactoryImpl::getServer()
{
    return pServerImpl->getFacade();
}

void ClientFactoryImpl::silentDisconnect( LogicalConnection* pLogicalConnection )
{
    if (!removeIfExisting(pLogicalConnection))
    {
        return;
    }
    pLogicalConnection->pPhysicalConnection->closeConnection(false);

    //Send to garbage collector directly, since the structure is not referenced by any streamer yet.
    garbageCollector.addDisposableClient(pLogicalConnection);

}
bool ClientFactoryImpl::disconnect( LogicalConnection* pLogicalConnection, bool waitForPendingPackets , int closeReason)
{
    if (!removeIfExisting(pLogicalConnection))
    {
        return false;
    }
	disconnectIntern(pLogicalConnection, waitForPendingPackets, closeReason);
	return true;
}

bool ClientFactoryImpl::removeIfExisting( LogicalConnection* pLogicalConnection )
{
    ScopedLock csLock(cs);

    clientMapT::iterator it = clientMap.find(pLogicalConnection->getKey());
    if (it == clientMap.end())
    {
        return false;
    }
    nClientsCount--;

    clientMap.erase(it);
    return true;
}

unsigned int ClientFactoryImpl::getClientCount()
{
    return nClientsCount;
}

void ClientFactoryImpl::returnClient( LogicalConnection* pClient )
{
    pClient->DecrementUsage();
}

void ClientFactoryImpl::scrutinize()
{
	ScopedLock csLock(cs);

	clientMapT::iterator it = clientMap.begin();
	while (it!=clientMap.end())
	{
		LogicalConnection* pClient = it->second;
		if (pClient->IsInactive())
		{
			nClientsCount--;
			bool waitForPendingPackets = pServerImpl->getClientFactory()->onBeforeClosingIdleClient(pClient);
			disconnectIntern(pClient, waitForPendingPackets, ClientFactory::InactiveClient);
			clientMap.erase(it++);
		}
		else
			++it;
	}
}

void ClientFactoryImpl::disconnectIntern( LogicalConnection* pLogicalConnection, bool waitForPendingPackets, int closeReason )
{
	pLogicalConnection->pPhysicalConnection->closeConnection(waitForPendingPackets);

	broadcastManagerImpl.removeClient(pLogicalConnection->getKey());
	dispatcher.notifyObserversClientOut(pLogicalConnection->getKey());

	//Statistics :
	stats.addToCumul(ServerStats::VisitorsHitsOut, 1);
	stats.addToCumul(ServerStats::VisitorsOnline, -1);
	stats.addToDuration(ServerStats::VisitorsDuration, pLogicalConnection->getVisitDuration());

	broadcastStreamerManager.removeClient(pLogicalConnection);

	pServerImpl->getClientFactory()->onClientDisconnected(pLogicalConnection, (ClientFactory::CloseReason) closeReason);
	
	garbageCollector.addDisposableClient(pLogicalConnection);
}


}

