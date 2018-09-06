/********************************************************************
	File :			BroadcastStreamer.cpp
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
#include "BroadcastStreamer.h"

#include "../include/LogicalConnection.h"
#include "BroadcastQueueInfo.h"
#include "PacketInfo.h"
#include "BroadcastManagerImpl.h"
#include "PhysicalConnection.h"
#include "BroadcastContext.h"
#include "GarbageCollector.h"

namespace PushFramework
{

BroadcastStreamer::BroadcastStreamer(void)
{
}

BroadcastStreamer::~BroadcastStreamer(void)
{
}

ProcessResult BroadcastStreamer::processItem( ItemPtr pItem )
{
    LogicalConnection* pLogicalConnection = reinterpret_cast<LogicalConnection*> (pItem);

    //Try to send one packet :

    BroadcastQueueInfo* pFoundInfo = NULL;
    PacketInfo* pPacketInfo = NULL;

    BroadcastContext& broadcastCtxt = pLogicalConnection->pPhysicalConnection->broadcastCxt;
    std::string subscriberKey = pLogicalConnection->getKey();


    OutgoingPacket* pPacket = broadcastManagerImpl.getNextPacket(subscriberKey, broadcastCtxt, pPacketInfo, pFoundInfo);
    if (!pPacket)
        return PauseProcessing;

    SendResult result = pLogicalConnection->TryPushPacket(pPacket);

    broadcastManagerImpl.disposePacket(pPacketInfo, subscriberKey, pFoundInfo, broadcastCtxt, result == SendResult_OK);

	if (result == SendResult_NotOK)
	{
		return DeleteItem;
	}

    return ContinueProcessing;
}

void BroadcastStreamer::addItem( ItemPtr pItem )
{
    LogicalConnection* pLogicalConnection = reinterpret_cast<LogicalConnection*> (pItem);
    pLogicalConnection->IncrementUsage();

    AbstractDistributor::addItem(pItem);
}

void BroadcastStreamer::handleItemRemoved( ItemPtr pItem )
{
    LogicalConnection* pLogicalConnection = reinterpret_cast<LogicalConnection*> (pItem);
    pLogicalConnection->DecrementUsage();
}

}
