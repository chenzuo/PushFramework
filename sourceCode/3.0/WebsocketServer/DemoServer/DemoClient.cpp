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
	TextMessage* textRequest = (TextMessage*) pRequest;
	//cout << "received  text request: " << textRequest->getText() << endl;


/*
	TextMessage echoReply(textRequest->getText());
*/
	PushPacket(textRequest);


	/*XMLMessage& message = (XMLMessage&) (*pRequest);


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
	}*/
}

void DemoClient::initialize( IncomingPacket* loginRequest )
{
	TextMessage* textRequest = (TextMessage*) loginRequest;
	//cout << "received  login request: " << textRequest->getText() << endl;
}


