/********************************************************************
	File :			BroadcastManager.cpp
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
#include "../include/BroadcastManager.h"

#include "BroadcastManagerImpl.h"

namespace PushFramework
{

PUSHFRAMEWORK_API BroadcastManager broadcastManager;

BroadcastManager::BroadcastManager(void)
{
}

BroadcastManager::~BroadcastManager(void)
{
}

void BroadcastManager::CreateQueue( BROADCASTQUEUE_NAME channelKey, QueueOptions& queueOptions )
{
    broadcastManagerImpl.createBroadcastQueue(channelKey, queueOptions);
}

void BroadcastManager::RemoveQueue( BROADCASTQUEUE_NAME channelKey )
{
    broadcastManagerImpl.removeBroadcastQueue(channelKey);
}

bool BroadcastManager::SubscribeConnectionToQueue( CLIENT_KEY clientKey, BROADCASTQUEUE_NAME channelKey, bool ignorePreviousPackets/* = false*/ )
{
    return broadcastManagerImpl.subscribeClient(clientKey, channelKey, ignorePreviousPackets);
}

bool BroadcastManager::UnsubscribeConnectionFromQueue( CLIENT_KEY clientKey, BROADCASTQUEUE_NAME channelKey )
{
    return broadcastManagerImpl.unsubscribeClient(clientKey, channelKey);
}

bool BroadcastManager::PushPacket( OutgoingPacket* pPacket, BROADCASTQUEUE_NAME channelName, BROADCASTPACKET_KEY killKey, int objectCategory )
{
    return broadcastManagerImpl.pushPacket(pPacket, channelName, killKey, objectCategory);
}

bool BroadcastManager::PushPacket( OutgoingPacket* pPacket, BROADCASTQUEUE_NAME channelName )
{
    return broadcastManagerImpl.pushPacket(pPacket, channelName, "", 0);
}

void BroadcastManager::RemovePacket( BROADCASTPACKET_KEY killKey, int objectCategory, BROADCASTQUEUE_NAME channelKey )
{
    broadcastManagerImpl.removePacket(killKey, objectCategory, channelKey);
}

void BroadcastManager::RemoveConnection( CLIENT_KEY clientKey )
{
    broadcastManagerImpl.removeClient(clientKey);
}
}

