#pragma once
class DemoClient : public LogicalConnection
{
public:
	DemoClient();
	~DemoClient(void);
	
protected:

	virtual void handleRequest( IncomingPacket* pRequest );

	virtual Login::Type processLogin( LoginData& loginData );

	virtual void Recycle();
};

