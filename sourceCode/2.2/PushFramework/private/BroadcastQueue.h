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

class BroadcastManagerImplBase;
class OutgoingPacket;
class Protocol;

class BroadcastQueue
{
public:
    BroadcastQueue(BroadcastManagerImplBase* pManager, std::string channelName, QueueOptions& queueOptions);
    ~BroadcastQueue(void);

public:

    bool pushPacket(OutgoingPacket* pPacket, BROADCASTPACKET_KEY killKey="", int objectCategory =0);

    bool checkAgainstMaxFillRate();

    void removePacket(BROADCASTPACKET_KEY killKey="", int objectCategory =0);

    void subscribeClient(std::string clientKey, bool ignorePreviousPackets = false);
    void unsubscribeClient(std::string clientKey);

    void disposePacket(PacketInfo* pPacketInfo, std::string clientKey, bool bSuccess = true);

    OutgoingPacket* getNextPacket(std::string clientKey, PacketInfo*& pPacketInfo);

    void disposeAllPackets();

    std::string getChannelName();
private:
    BroadcastManagerImplBase* pManager;
    //
    std::string channelName;
    QueueOptions queueOptions;
    //
	vector<PacketInfo*> activeList;
    std::vector<PacketInfo*> removedList;
 
    //References :
    typedef std::map<std::string, int> clientMapT;
    clientMapT clientMap;

    CRITICAL_SECTION cs;
    void internalRemove( PacketInfo* pPacketInfo );

    unsigned int cumulatedCount;
    time_t lastCountTime;
    unsigned int lastGenId;

};

}

#endif // BroadcastQueue__INCLUDED
