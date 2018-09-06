#pragma once

class CMemTestService : public Service
{
public:
	CMemTestService(void);
	~CMemTestService(void);
protected:
	virtual void handle(LogicalConnection* pClient, IncomingPacket* pRequest);
};
