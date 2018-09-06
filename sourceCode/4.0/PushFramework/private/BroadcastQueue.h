/********************************************************************
	File :			BroadcastQueue.h
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
#ifndef BroadcastQueue__INCLUDED
#define BroadcastQueue__INCLUDED

#pragma once

#include "../include/PushFramework.h"
#include "../include/QueueOptions.h"
#include "PacketInfo.h"

namespace PushFramework
{

class BroadcastManager;

class BroadcastQueue
{
public:
    BroadcastQueue(BroadcastManager* pManager, std::string channelName, QueueOptions& queueOptions);
    ~BroadcastQueue(void);

public:

    bool pushPacket(OutgoingPacket* pPacket, BROADCASTPACKET_KEY killKey="", int objectCategory =0);

    bool checkAgainstMaxFillRate();

    void removePacket(BROADCASTPACKET_KEY killKey="", int objectCategory =0);

    void disposePacket(PacketInfo* pPacketInfo);

    OutgoingPacket* getNextPacket(int previouslyInsertedId, PacketInfo*& pPacketInfo);

    std::string getChannelName();

	unsigned int getLastGeneratedId();

	QueueOptions& getOptions();

private:
    BroadcastManager* pManager;
    //
    std::string channelName;
    QueueOptions queueOptions;
    //
	vector<PacketInfo*> activeList;
    std::unordered_set<PacketInfo*> removedList;

    CRITICAL_SECTION cs;
    void internalRemove( PacketInfo* pPacketInfo );
    void cleanUpRemovedPackets();

    unsigned int cumulatedCount;
    time_t lastCountTime;
    unsigned int lastGenId;

};

}

#endif // BroadcastQueue__INCLUDED
