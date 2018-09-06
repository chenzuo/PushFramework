/*
 * File:   ResponseHandlers.h
 * Author: ahmed
 *
 * Created on 6 juin 2011, 20:06
 */

#ifndef RESPONSEHANDLERS_H
#define	RESPONSEHANDLERS_H

#pragma once

class ChatAPI;

class DirectChatResponseHandler : public ResponseHandler
{
public:
    DirectChatResponseHandler(ChatAPI* pSession);
    ~DirectChatResponseHandler() {}
    virtual void handleResponse(PushFramework::IncomingPacket& packet);
private:
    ChatAPI* pSession;
};


//


class JoinRoomResponseHandler : public ResponseHandler
{
public:
    JoinRoomResponseHandler(ChatAPI* pSession);
    ~JoinRoomResponseHandler() {}
    virtual void handleResponse(PushFramework::IncomingPacket& packet);
private:
    ChatAPI* pSession;
};

//


class ParticipantInResponseHandler : public ResponseHandler
{
public:
    ParticipantInResponseHandler(ChatAPI* pSession);
    ~ParticipantInResponseHandler() {}
    virtual void handleResponse(PushFramework::IncomingPacket& packet);
private:
    ChatAPI* pSession;
};


class ParticipantOutResponseHandler : public ResponseHandler
{
public:
    ParticipantOutResponseHandler(ChatAPI* pSession);
    ~ParticipantOutResponseHandler() {}
    virtual void handleResponse(PushFramework::IncomingPacket& packet);
private:
    ChatAPI* pSession;
};

//

class RoomChatResponseHandler : public ResponseHandler
{
public:
    RoomChatResponseHandler(ChatAPI* pSession);
    ~RoomChatResponseHandler() {}
    virtual void handleResponse(PushFramework::IncomingPacket& packet);
private:
    ChatAPI* pSession;
};

//

class LoginPuzzleResponseHandler : public ResponseHandler
{
public:
    LoginPuzzleResponseHandler(ChatAPI* pSession);
    ~LoginPuzzleResponseHandler() {}
    virtual void handleResponse(PushFramework::IncomingPacket& packet);
private:
    ChatAPI* pSession;
};


//

class LoginResponseHandler : public ResponseHandler
{
public:
    LoginResponseHandler(ChatAPI* pSession);
    ~LoginResponseHandler() {}
    virtual void handleResponse(PushFramework::IncomingPacket& packet);
private:
    ChatAPI* pSession;
};

//

class RoomsResponseHandler : public ResponseHandler
{
public:
    RoomsResponseHandler(ChatAPI* pSession);
    ~RoomsResponseHandler() {}
    virtual void handleResponse(PushFramework::IncomingPacket& packet);
private:
    ChatAPI* pSession;
};

#endif	/* RESPONSEHANDLERS_H */

