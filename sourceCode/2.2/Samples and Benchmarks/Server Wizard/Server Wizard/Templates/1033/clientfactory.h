#pragma once

class [!output CLIENT_FACTORY_CLASS_NAME] : public ClientFactory
{
public:
	[!output CLIENT_FACTORY_CLASS_NAME]();
	~[!output CLIENT_FACTORY_CLASS_NAME]();

protected:
	[!if CHALLENGE_CONNECTIONS]
	virtual OutgoingPacket* onNewConnection(ConnectionContext*& lpConnectionContext);
	[!endif]
	virtual int onFirstRequest(IncomingPacket& request, ConnectionContext* pConnectionContext, LogicalConnection*& lpClient, OutgoingPacket*& lpPacket);
	
	[!if OVERRIDE_CLIENTFACTORY]
	virtual void onClientDisconnected(LogicalConnection* pClient, CloseReason closeReason);
	virtual void onClientConnected(LogicalConnection* pClient);
	virtual void onClientReconnected(LogicalConnection* pClient);
	virtual bool onBeforeClosingIdleClient(LogicalConnection* pClient);
	virtual void CopyLogicalConnection(LogicalConnection* pSrc, LogicalConnection* pDest);
	[!endif]
};
