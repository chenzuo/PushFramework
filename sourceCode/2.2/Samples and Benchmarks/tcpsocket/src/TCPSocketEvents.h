#pragma once

#include "Symbols.h"


namespace PushFramework
{
class IncomingPacket;
}



struct TCPSOCKET_API TCPSocketEvent
{
    enum
    {
        ConnectionEstablished = 0,
        ConnectionClosed,
        NewMessage,
    };
    int type;
    int commandId;
    PushFramework::IncomingPacket* pPacket;
};
