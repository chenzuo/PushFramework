#pragma once

class CGroupService : public Service
{
public:
    CGroupService(void);
    ~CGroupService(void);

protected:
    virtual void handle(LogicalConnection* pClient, IncomingPacket* pRequest);
};
