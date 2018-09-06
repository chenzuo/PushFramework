#pragma once

#include "Symbols.h"

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
    virtual void handleResponse(ProtocolFramework::IncomingPacket& _packet) = 0;

};
