#pragma once

class DirectChatRequestService : public Service
{
public:
    DirectChatRequestService(void);
    ~DirectChatRequestService(void);

    virtual void handle(LogicalConnection* pClient, IncomingPacket* pRequest);

};
