/********************************************************************
	File :			BroadcastQueue.cpp
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
#include "BroadcastQueue.h"

#include "ScopedLock.h"
#include "BroadcastManager.h"


// Uncomment the following #define to allow the deletion of packets to happen
// on the same thread that pushed them into the queue:
// #define PushAndDeletePacketsOnSameThread 


namespace PushFramework
{

BroadcastQueue::BroadcastQueue(BroadcastManager* pManager, std::string channelName, QueueOptions& queueOptions)
{
    this->pManager = pManager;
    this->channelName = channelName;
    this->queueOptions = queueOptions;

    ::InitializeCriticalSection(&cs);
    cumulatedCount = 0;
    lastGenId = 0;
}

BroadcastQueue::~BroadcastQueue(void)
{
    //Delete all packets still present in the queue.
    for (unsigned int i = 0; i < activeList.size(); i++)
    {
        PacketInfo* pTemp = activeList.at(i);
        pManager->deleteOutgoingPacket(pTemp->pPacket);
        delete pTemp;
    }

    ::DeleteCriticalSection(&cs);
}


bool BroadcastQueue::pushPacket( OutgoingPacket* pPacket, BROADCASTPACKET_KEY killKey/*=""*/, int objectCategory /*=0*/ )
{
    ScopedLock csLock(cs);

    if (!checkAgainstMaxFillRate())
    {
        return false;
    }

    activeList.push_back(new PacketInfo(pPacket, killKey, objectCategory, ++lastGenId));

	if (activeList.size() > queueOptions.maxPackets)
	{
		PacketInfo* head = activeList.front();
		activeList.erase(activeList.begin());

		internalRemove(head);
	}

#ifdef PushAndDeletePacketsOnSameThread
    cleanUpRemovedPackets();
#endif // PushAndDeletePacketsOnSameThread


	return true;
}

void BroadcastQueue::removePacket( BROADCASTPACKET_KEY killKey/*=""*/, int objectCategory /*=0*/ )
{
    ScopedLock csLock(cs);

	packetInfoListT::iterator it = activeList.begin();
	while (it!=activeList.end())
	{
		PacketInfo* pInfo = *it;
		if (pInfo->killKey == killKey && pInfo->objectCategory == objectCategory)
		{
			internalRemove(pInfo);
			activeList.erase(it);
			return;
		}

		it++;
	}
}

void BroadcastQueue::disposePacket( PacketInfo* pPacketInfo)
{
    ScopedLock csLock(cs);

    // In all cases dec refCount :
    pPacketInfo->refCount--;

#ifndef PushAndDeletePacketsOnSameThread 
    // If Item has been marked for removal, and refCount has become 0, then delete it.
    if (pPacketInfo->bWaitingForRemoval && pPacketInfo->refCount == 0)
    {
        std::unordered_set<PacketInfo*>::iterator it = removedList.find(pPacketInfo);

        if (it != removedList.end())
        {
            pManager->deleteOutgoingPacket(pPacketInfo->pPacket);
            delete pPacketInfo;
            removedList.erase(it);
        }
    }
#endif
    
}

OutgoingPacket* BroadcastQueue::getNextPacket( int previouslyInsertedId, PacketInfo*& pPacketInfo )
{
	pPacketInfo = NULL;

    ScopedLock csLock(cs);

	packetInfoListT::iterator it = activeList.begin();

	PacketInfo* pSearchItem = NULL;
	while (it != activeList.end())
	{
		pSearchItem = *it;

		bool isNotSent = pSearchItem->packetId > previouslyInsertedId;
		if (isNotSent)
		{
			bool isNotExpired = queueOptions.maxExpireDurationSecs == 0 || pSearchItem->getLife() <= queueOptions.maxExpireDurationSecs;
			if (isNotExpired)
			{
				pPacketInfo = pSearchItem;
				break;
			}
		}

		it++;
	}

    if (pPacketInfo)
    {
        pPacketInfo->refCount++;
        return pPacketInfo->pPacket;
    }
    return NULL;
}


std::string BroadcastQueue::getChannelName()
{
    return channelName;
}

void BroadcastQueue::internalRemove( PacketInfo* pPacketInfo )
{
    if(pPacketInfo->refCount==0)
    {
        pManager->deleteOutgoingPacket(pPacketInfo->pPacket);
        delete pPacketInfo;
    }
    else
    {
        removedList.insert(pPacketInfo);
        pPacketInfo->bWaitingForRemoval = true;
    }
}

bool BroadcastQueue::checkAgainstMaxFillRate()
{
    if (queueOptions.fillRateThrottlingPeriod != 0)
    {
        time_t timeNow = time(NULL);

        if (cumulatedCount == 0)
        {
            lastCountTime = timeNow;
            cumulatedCount = 1;
        }
        else
        {
            if (difftime(timeNow, lastCountTime) < queueOptions.fillRateThrottlingPeriod )
            {
                if (cumulatedCount == queueOptions.fillRateThrottlingMaxPackets)
                {
                    return false;
                }
                else
                {
                    cumulatedCount++;
                }
            }
            else
            {
                cumulatedCount = 1;
                lastCountTime = timeNow;
            }
        }
    }
    return true;
}

unsigned int BroadcastQueue::getLastGeneratedId()
{
	return lastGenId;
}

QueueOptions& BroadcastQueue::getOptions()
{
	return queueOptions;
}

void BroadcastQueue::cleanUpRemovedPackets()
{
    std::unordered_set<PacketInfo*>::iterator it = removedList.begin();

    while (it != removedList.end())
    {
        PacketInfo* pPacketInfo = *it;
        if (pPacketInfo->refCount == 0)
        {
            pManager->deleteOutgoingPacket(pPacketInfo->pPacket);
            delete pPacketInfo;
            it = removedList.erase(it);
        }
        else
        {
            ++it;
        }
    }

}

}

