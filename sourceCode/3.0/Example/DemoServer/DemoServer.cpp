// DemoServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "DemoPublisher.h"
#include "MyServer.h"


MyServer theServer;
int _tmain(int argc, _TCHAR* argv[])
{
	XMLSerializer xmlSerializer;
	SimpleProtocol simpleProtocol;

	theServer.setMessageFactory(&xmlSerializer);

	ListenerOptions lOptions;
	lOptions.pProtocol = &simpleProtocol;

	theServer.createListener(10010, &lOptions);

	QueueOptions qOptions;
	qOptions.priority = 10;
	qOptions.packetsQuota = 4;

	theServer.CreateQueue("queue1", qOptions);

	DemoPublisher publisher;

	theServer.start(true);

	Sleep(1000);
	publisher.start();

	while (true)
	{
		char ch;

		cin >> ch;

		if (ch == 'q')
		{
			break;
		}
	}

	publisher.stop();
	theServer.stop();
	

	return 0;
}




/*
void f()
{
	PushFramework::Server theServer;

	Protocol* pWebsocketProtocol = new WebsocketProtocol();
	
	Protocol* pSSLProtocol = new SSLProtocol();
	pWebsocketProtocol->addLowerProtocolLayer(pSSLProtocol);

	ListenerOptions lOptions;
	lOptions.pProtocol = pWebsocketProtocol;

	theServer.createListener(10010, &lOptions);
};*/