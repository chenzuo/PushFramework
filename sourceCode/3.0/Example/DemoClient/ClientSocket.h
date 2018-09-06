#pragma once
class ClientSocket : public TCPSocket, public ResponseHandler
{
public:
	ClientSocket(void);
	~ClientSocket(void);

	virtual void onConnected();

	virtual void onConnectionClosed();

	virtual void handleResponse(ProtocolFramework::IncomingPacket& _packet);
};

