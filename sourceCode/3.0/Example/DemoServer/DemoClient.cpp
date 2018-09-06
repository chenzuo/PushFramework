#include "stdafx.h"
#include "DemoClient.h"


DemoClient::DemoClient()
{
}


DemoClient::~DemoClient(void)
{
}

void DemoClient::handleRequest( IncomingPacket* pRequest )
{
	XMLMessage& message = (XMLMessage&) (*pRequest);


	string requestText = message.getArgumentAsText("arg1");
	if ( requestText == "echo")
	{
		XMLMessage reply(1);

		reply.setArgumentAsText("text", "hello");
		PushPacket(&reply);
	}

	if (requestText == "subscribe")
	{
		SubscribeToQueue("queue1");
	}
}

Login::Type DemoClient::processLogin(LoginData& loginData)
{
	return Login::AcceptClient;
}

void DemoClient::Recycle()
{
	//
}


