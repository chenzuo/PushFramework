#pragma once
class MyServer : public PushFramework::Server
{
public:
	MyServer(void);
	~MyServer(void);

protected:

	virtual LogicalConnection* createLogicalConnection();

	virtual Login::Type processLogin( LoginData& loginData );

};

