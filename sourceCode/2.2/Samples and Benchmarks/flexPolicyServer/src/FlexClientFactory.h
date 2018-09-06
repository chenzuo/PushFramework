#pragma once


#include "FlexSandbox.h"
#include "PolicyResponse.h"


class FlexClientFactory : public ClientFactory
{
public:

    FlexClientFactory(std::string strPolicyContent);

    ~FlexClientFactory(void);

    virtual void onClientConnected(LogicalConnection* pClient);
    virtual int onFirstRequest(IncomingPacket& request, ConnectionContext* lpContext, LogicalConnection*& lpClient, OutgoingPacket*& lpPacket);

private:
    std::string strPolicyContent;
};
