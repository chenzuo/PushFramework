/*
 * File:   ChatAPI.cpp
 * Author: ahmed
 *
 * Created on 6 juin 2011, 20:06
 */


#include "stdafx.h"

#include "ChatAPI.h"


#include "ResponseHandlers.h"




void ChatAPI::OnLoginPuzzle( int puzzleQuestion )
{
    tryLogin(puzzleQuestion);
}

bool ChatAPI::tryConnect( std::string serverHost, unsigned int uPort )
{
    return TCPSocket::connect((char*) serverHost.c_str(), uPort);
}

bool ChatAPI::tryLogin( int loginPuzzle /*= -1*/ )
{
    if (getStatus() == Disconnected)
    {
        return false;
    }

    if (getStatus() != Connected)
    {
        return false;
    }

    if(loginPuzzle!=-1)
        this->loginPuzzle = loginPuzzle;

    LoginRequest request;
    //
    request.Pseudo(pseudo);
    request.LoginPuzzleReply(loginPuzzle + 1);

    return sendRequest(&request);
}

bool ChatAPI::SendDirectChat( std::string recipient, std::string msg )
{
    DirectChatRequest request;
    //
    request.Recipient(recipient);
    request.Msg(msg);

    return sendRequest(&request);
}

bool ChatAPI::JoinRoom( std::string room )
{
    JoinRoomRequest request;
    //
    request.Room(room);

    return sendRequest(&request);
}

bool ChatAPI::LeaveRoom( std::string room )
{
    LeaveRoomRequest request;
    //
    request.Room(room);

    return sendRequest(&request);
}

bool ChatAPI::SendRoomChat( std::string msg, std::string room )
{
    RoomChatRequest request;
    //
    request.Room(room);
    request.Msg(msg);

    return sendRequest(&request);
}

void ChatAPI::Logout()
{
    LogoutRequest request;
    sendRequest(&request);
    disconnect(true);
}

ChatAPI::ChatAPI( bool relayToUserThread /*= false */)
    :TCPSocket(relayToUserThread)
{
    registerHandler(LoginPuzzleResponseID, new LoginPuzzleResponseHandler(this));
    registerHandler(LoginResponseID, new LoginResponseHandler(this));
    registerHandler(RoomsResponseID, new RoomsResponseHandler(this));
    registerHandler(ParticipantInResponseID, new ParticipantInResponseHandler(this));
    registerHandler(ParticipantOutResponseID, new ParticipantOutResponseHandler(this));
    registerHandler(DirectChatResponseID, new DirectChatResponseHandler(this));
    registerHandler(RoomChatResponseID, new RoomChatResponseHandler(this));
    registerHandler(JoinRoomResponseID, new JoinRoomResponseHandler(this));

    setProtocol(new ChatClientProtocol);
}

void ChatAPI::setLoginInfo( std::string pseudo )
{
    this->pseudo = pseudo;
}






