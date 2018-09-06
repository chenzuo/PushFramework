#include "StdAfx.h"
#include "ChatParticipantFactory.h"

#include "ChatParticipant.h"

ChatParticipantFactory::ChatParticipantFactory(void)
{
}

ChatParticipantFactory::~ChatParticipantFactory(void)
{
}

int ChatParticipantFactory::onFirstRequest( IncomingPacket& request, ConnectionContext* lpContext, LogicalConnection*& lpClient, OutgoingPacket*& lpPacket )
{
    LoginRequest& packet = (LoginRequest&) request;

    std::string pseudo = packet.Pseudo();

    int question = ((ChatConnectionCxt*) lpContext)->puzzle;

    if (packet.LoginPuzzleReply() != ( question + 1 ) )
    {
        LoginResponse* pLoginResponse = new LoginResponse;
        pLoginResponse->BAccepted(false);
        pLoginResponse->Msg("login puzzle is false");

        lpPacket = pLoginResponse;

        return ClientFactory::RefuseRequest;
    }

    ChatParticipant* pClient = new ChatParticipant(pseudo);
    lpClient = pClient;

    return ClientFactory::CreateClient;
}

OutgoingPacket* ChatParticipantFactory::onNewConnection( ConnectionContext*& lpContext )
{
    //Send the login challenge :
    LoginPuzzleResponse* pPuzzle = new LoginPuzzleResponse;

    ChatConnectionCxt* pCxt = new ChatConnectionCxt;
    pCxt->puzzle = rand()%100;

    pPuzzle->PuzzleQuestion(pCxt->puzzle);

    lpContext = pCxt;
    return pPuzzle;
}

void ChatParticipantFactory::onClientConnected( LogicalConnection* pClient )
{
    //When a client connects.
    ChatParticipant* pParticipant = (ChatParticipant*) pClient;

    LoginResponse loginRespone;
    loginRespone.BAccepted(true);
    loginRespone.Msg("welcome to server");
    pParticipant->PushPacket(&loginRespone);

    ParticipantInResponse* pPacket = new ParticipantInResponse;
    pPacket->Pseudo(pClient->getKey());
    broadcastManager.PushPacket(pPacket, "participants", pClient->getKey(), 0);
}

void ChatParticipantFactory::onClientDisconnected( LogicalConnection* pClient, CloseReason closeReason )
{
	broadcastManager.RemovePacket(pClient->getKey(), 0, "participants");

	ParticipantOutResponse* pPacket = new ParticipantOutResponse;
	pPacket->Pseudo() = pClient->getKey();

	broadcastManager.PushPacket(pPacket, "signals", "", 0);
}
