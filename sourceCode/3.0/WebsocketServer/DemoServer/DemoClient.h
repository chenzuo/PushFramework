#pragma once
class DemoClient : public LogicalConnection
{
public:
	DemoClient();
	~DemoClient(void);
	
protected:
	
	virtual void Recycle()
	{
		//
	}

	virtual void initialize(IncomingPacket* loginRequest);

	virtual void handleRequest( IncomingPacket* pRequest );

};

