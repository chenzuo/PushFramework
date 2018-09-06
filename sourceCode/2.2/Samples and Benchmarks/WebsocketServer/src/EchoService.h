#pragma once
class EchoService : public Service
{
public:
	EchoService(void);
	~EchoService(void);
	void handle( LogicalConnection* pClient, IncomingPacket* pRequest );

};

