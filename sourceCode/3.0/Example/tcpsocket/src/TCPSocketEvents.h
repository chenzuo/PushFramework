#pragma once

#include "Symbols.h"


namespace ProtocolFramework
{
class AbstractMessage;
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
    ProtocolFramework::IncomingPacket* pPacket;
};
