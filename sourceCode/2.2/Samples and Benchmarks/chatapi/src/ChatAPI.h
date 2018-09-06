/*
 * File:   ChatAPI.h
 * Author: ahmed
 *
 * Created on 6 juin 2011, 20:06
 */

#ifndef CHATAPI_H
#define	CHATAPI_H

#pragma once


#include "Symbols.h"

// This class is exported from the ChatAPI.dll
class CHATAPI_API ChatAPI : public TCPSocket
{
public:
    ChatAPI(bool relayToUserThread = false);
    ~ChatAPI()
    {

    }
    bool tryConnect(std::string serverHost, unsigned int uPort);
    bool tryLogin(int loginPuzzle = -1);
    void setLoginInfo(std::string pseudo);

    bool SendDirectChat(std::string recipient, std::string msg);
    bool JoinRoom(std::string room);
    bool LeaveRoom(std::string room);
    bool SendRoomChat(std::string msg, std::string room);
    void Logout();
    std::string getPseudo() const
    {
        return pseudo;
    }
private:
    std::string pseudo;
    int loginPuzzle;
public:
    virtual void onConnected() =0;
    virtual void onConnectionClosed()=0;
    virtual void OnDirectChat(std::string sender, std::string msg) = 0;
    virtual void OnJoinRoom(std::string roomName) = 0;
    virtual void OnParticipantIn(std::string pseudo) = 0;
    virtual void OnParticipantOut(std::string pseudo) = 0;
    virtual void OnRoomChat(std::string sender, std::string msg, std::string room) = 0;
    virtual void OnRooms(std::vector<std::string>& roomsList) =0;
    virtual void OnLoginResponse(bool bAccepted, std::string msg) = 0;
    //
    void OnLoginPuzzle(int puzzleQuestion);


};

#endif	/* CHATAPI_H */

