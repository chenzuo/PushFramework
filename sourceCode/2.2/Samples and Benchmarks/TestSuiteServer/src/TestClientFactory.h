#pragma once

class CTestClientFactory : public ClientFactory
{
public:
    CTestClientFactory(void);
    ~CTestClientFactory(void);
protected:

    virtual int onFirstRequest(IncomingPacket& request, ConnectionContext* lpContext, LogicalConnection*& lpClient, OutgoingPacket*& lpPacket);

};
