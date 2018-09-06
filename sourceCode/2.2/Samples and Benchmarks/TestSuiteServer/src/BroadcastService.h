#pragma once

class BroadcastService : public Service
{
public:
    BroadcastService(void);
    ~BroadcastService(void);
protected:
    virtual void handle(LogicalConnection* pClient, IncomingPacket* pRequest);
};
