// stdafx.cpp : source file that includes just the standard includes
// TestSuiteServer.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
bool BroadcastPacket( protobuf::Message* pMessage, BROADCASTQUEUE_NAME channelName )
{
    OutgoingPacket* pPacket = reinterpret_cast<OutgoingPacket*> (pMessage);
    return broadcastManager.PushPacket(pPacket, channelName);
}

bool BroadcastPacket( protobuf::Message* pMessage, BROADCASTQUEUE_NAME channelName, BROADCASTPACKET_KEY killKey, int objectCategory )
{
    OutgoingPacket* pPacket = reinterpret_cast<OutgoingPacket*> (pMessage);
    return broadcastManager.PushPacket(pPacket, channelName, killKey, objectCategory);
}

UINT nFailed = 0;