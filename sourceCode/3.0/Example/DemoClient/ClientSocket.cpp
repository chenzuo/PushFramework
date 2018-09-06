#include "stdafx.h"
#include "ClientSocket.h"


ClientSocket::ClientSocket(void)
{
}


ClientSocket::~ClientSocket(void)
{
}

void ClientSocket::onConnected()
{
	cout << "connected" << endl;
}

void ClientSocket::onConnectionClosed()
{
	cout << "closed" << endl;
}

void ClientSocket::handleResponse( ProtocolFramework::IncomingPacket& _packet )
{
	XMLMessage& msg = (XMLMessage&) _packet;

	cout << "received new server reply: " << msg.getArgumentAsInt("id") << endl;
}