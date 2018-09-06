#pragma once

class LogoutRequestService : public Service
{
public:
    LogoutRequestService(void);
    ~LogoutRequestService(void);
    void handle( LogicalConnection* pClient, IncomingPacket* pRequest );
};
