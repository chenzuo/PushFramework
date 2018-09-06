#pragma once


class ChatConnectionCxt : public ConnectionContext
{
public:
    ChatConnectionCxt()
    {
        //
    }
    ~ChatConnectionCxt()
    {
        //
    }
    int puzzle;
};

class ChatParticipantFactory : public ClientFactory
{
public:
    ChatParticipantFactory(void);
    ~ChatParticipantFactory(void);
protected:
    virtual OutgoingPacket* onNewConnection(ConnectionContext*& lpContext);
    virtual void onClientDisconnected(LogicalConnection* pClient, CloseReason closeReason);
    virtual void onClientConnected(LogicalConnection* pClient);
	virtual int onFirstRequest(IncomingPacket& request, ConnectionContext* lpContext, LogicalConnection*& lpClient, OutgoingPacket*& lpPacket);
};
