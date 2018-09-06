#pragma once

class LeaveRoomRequestService : public Service
{
public:
    LeaveRoomRequestService(void);
    ~LeaveRoomRequestService(void);

    void handle(  LogicalConnection* pClient, IncomingPacket* pRequest );
};
