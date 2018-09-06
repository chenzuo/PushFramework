#pragma once

class CSubscribeService : public Service
{
public:
    CSubscribeService(void);
    ~CSubscribeService(void);
protected:
    virtual void handle(LogicalConnection* pClient, IncomingPacket* pRequest);
};
