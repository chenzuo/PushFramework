/********************************************************************
	File :			BroadcastManagerImpl.cpp
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
#include "BroadcastManagerImpl.h"

#include "../include/Protocol.h"
#include "../include/OutgoingPacket.h"
#include "ServerStats.h"
#include "../include/Server.h"
#include "ServerImpl.h"
#include "ChannelFactory.h"
#include "BroadcastStreamerManager.h"
#include "ServerImpl.h"
#include "ClientFactoryImpl.h"
#include "../include/LogicalConnection.h"
#include "BroadcastStreamer.h"
#include "Acceptor.h"

namespace PushFramework
{

BroadcastManagerImpl broadcastManagerImpl;

BroadcastManagerImpl::BroadcastManagerImpl(void)
{
}

BroadcastManagerImpl::~BroadcastManagerImpl(void)
{
}


bool BroadcastManagerImpl::subscribeClient( CLIENT_KEY clientKey, BROADCASTQUEUE_NAME channelKey, bool ignorePreviousPackets /*= false*/ )
{
	if (BroadcastManagerImplBase::subscribeClient(clientKey, channelKey, ignorePreviousPackets))
	{
		//Should awake streamer.
		LogicalConnection* pClient = clientFactoryImpl.findLogicalConnection(clientKey);
		if (pClient)
		{
			if (pClient->pStreamer)
			{
				pClient->pStreamer->reactivateItem(pClient);
			}
			clientFactoryImpl.returnClient(pClient);
		}
		return true;
	}
	return false;
}

void BroadcastManagerImpl::preEncodeOutgoingPacket( OutgoingPacket* pPacket )
{
    theAcceptor.getProtocol()->encodeOutgoingPacket(*pPacket);
}

void BroadcastManagerImpl::deleteOutgoingPacket( OutgoingPacket* pPacket )
{
	theAcceptor.getProtocol()->disposeOutgoingPacket(pPacket);
}

void BroadcastManagerImpl::activateSubscribers( std::string channelName )
{
    broadcastStreamerManager.reshuffle();
}

void BroadcastManagerImpl::hanldeOnBeforePushPacket( std::string channelName )
{
    stats.addToDistribution(ServerStats::QoSFillRatePerChannel,channelName, 1);
}

void BroadcastManagerImpl::handleOnAfterPacketIsSent( std::string channelName, std::string subscriberKey )
{
    stats.addToDistribution(ServerStats::QoSSendRatePerChannel,channelName, 1);
    stats.addToKeyedDistributionDuration(ServerStats::QoSAvgSendRatePerChannel, channelName, subscriberKey, 1);
}

}

