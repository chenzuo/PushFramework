#pragma once

#include "Symbols.h"

namespace PushFramework
{
class IncomingPacket;
}

class  TCPSOCKET_API ResponseHandler
{
public:
    ResponseHandler(void)
    {
        //
    }
    ~ResponseHandler(void)
    {
        //
    }

public:
    virtual void handleResponse(PushFramework::IncomingPacket& _packet) = 0;

};
