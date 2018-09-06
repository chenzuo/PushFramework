#pragma once

class CRoutedService : public Service
{
public:
    CRoutedService(void);
    ~CRoutedService(void);

protected:
    virtual void handle(LogicalConnection* pClient, IncomingPacket* pRequest);
};
