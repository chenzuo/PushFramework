// DemoClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ClientSocket.h"

int _tmain(int argc, _TCHAR* argv[])
{
	TCPSocket::initializeWinsock();


	ClientSocket client;
	SimpleProtocol simpleProtocol;
	XMLSerializer xmlSerializer;

	if (!client.initialize(&simpleProtocol, &xmlSerializer))
		return -1;

	client.registerHandler(1, &client);

	string strError;
	if (!client.connect("localhost", 10010, strError))
	{
		cout << strError << endl;
		return -1;
	}


	cout << "Press q to quit, s to subscribe all connected clients to real time, e to trigger echo" << endl;
	int ch;
	do 
	{
		ch = _getch();
		ch = toupper(ch);

		if (ch == 'S')
		{
			XMLMessage message(1);
			message.setArgumentAsText("arg1", "subscribe");

			client.sendRequest(&message);
		}


		if (ch == 'E')
		{
			XMLMessage message(1);
			message.setArgumentAsText("arg1", "echo");
			client.sendRequest(&message);
		}

	} while (ch !='Q');


	client.disconnect(true);

	return 0;
}

