#pragma once

class RoomChatRequestService : public Service
{
public:
    RoomChatRequestService(void);
    ~RoomChatRequestService(void);

    void handle( LogicalConnection* pClient, IncomingPacket* pRequest );
};
