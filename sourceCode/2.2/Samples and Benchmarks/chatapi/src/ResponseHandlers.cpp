
#include "stdafx.h"
#include "ResponseHandlers.h"
#include "ChatAPI.h"

DirectChatResponseHandler::DirectChatResponseHandler( ChatAPI* pSession )
{
    this->pSession = pSession;
}

void DirectChatResponseHandler::handleResponse( PushFramework::IncomingPacket& packet )
{
    DirectChatResponse& response = (DirectChatResponse&) packet;

    pSession->OnDirectChat(response.Sender(), response.Msg());
}

JoinRoomResponseHandler::JoinRoomResponseHandler( ChatAPI* pSession )
{
    this->pSession = pSession;
}

void JoinRoomResponseHandler::handleResponse( PushFramework::IncomingPacket& packet )
{
    JoinRoomResponse& response = (JoinRoomResponse&) packet;

    pSession->OnJoinRoom(response.Room());
}

ParticipantInResponseHandler::ParticipantInResponseHandler( ChatAPI* pSession )
{
    this->pSession = pSession;
}

void ParticipantInResponseHandler::handleResponse( PushFramework::IncomingPacket& packet )
{
    ParticipantInResponse& response = (ParticipantInResponse&) packet;

    pSession->OnParticipantIn(response.Pseudo());
}

ParticipantOutResponseHandler::ParticipantOutResponseHandler( ChatAPI* pSession )
{
    this->pSession = pSession;
}

void ParticipantOutResponseHandler::handleResponse( PushFramework::IncomingPacket& packet )
{
    ParticipantOutResponse& response = (ParticipantOutResponse&) packet;

    pSession->OnParticipantOut(response.Pseudo());
}

RoomChatResponseHandler::RoomChatResponseHandler( ChatAPI* pSession )
{
    this->pSession = pSession;
}

void RoomChatResponseHandler::handleResponse( PushFramework::IncomingPacket& packet )
{
    RoomChatResponse& response = (RoomChatResponse&) packet;

    pSession->OnRoomChat(response.Sender(), response.Msg(), response.Room());
}

LoginPuzzleResponseHandler::LoginPuzzleResponseHandler( ChatAPI* pSession )
{
    this->pSession = pSession;
}

void LoginPuzzleResponseHandler::handleResponse( PushFramework::IncomingPacket& packet )
{
    LoginPuzzleResponse& response = (LoginPuzzleResponse&) packet;

    pSession->OnLoginPuzzle(response.PuzzleQuestion());
}

LoginResponseHandler::LoginResponseHandler( ChatAPI* pSession )
{
    this->pSession = pSession;
}

void LoginResponseHandler::handleResponse( PushFramework::IncomingPacket& packet )
{
    LoginResponse& response = (LoginResponse&) packet;

    pSession->OnLoginResponse(response.BAccepted(), response.Msg());
}

RoomsResponseHandler::RoomsResponseHandler( ChatAPI* pSession )
{
    this->pSession = pSession;
}

void RoomsResponseHandler::handleResponse( PushFramework::IncomingPacket& packet )
{
    RoomsResponse& response = (RoomsResponse&) packet;

    pSession->OnRooms(response.getRooms());
}

