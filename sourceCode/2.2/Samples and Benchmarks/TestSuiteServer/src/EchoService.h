#pragma once

class CEchoService : public Service
{
public:
    CEchoService(void);
    ~CEchoService(void);
protected:
    virtual void handle(LogicalConnection* pClient, IncomingPacket* pRequest);
};
