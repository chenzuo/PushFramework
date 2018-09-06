#pragma once

class JoinRoomRequestService : public Service
{
public:
    JoinRoomRequestService(void);
    ~JoinRoomRequestService(void);

    void handle( LogicalConnection* pClient, IncomingPacket* pRequest );
};
