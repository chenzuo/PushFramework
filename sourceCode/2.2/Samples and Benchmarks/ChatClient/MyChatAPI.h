#pragma once
#define UWM_MESSAGE_MSG _T("UWM_MESSAGE-{72A92340-60F9-11d5-A02F-006067718D04}")
extern UINT UWM_MESSAGE;


class CMyChatAPI : public ChatAPI
{
public:
    CMyChatAPI(void);
    ~CMyChatAPI(void);
private:
    virtual void onConnected();
    virtual void onConnectionClosed();
    
	virtual void PostTCPEvent(TCPSocketEvent* pEvent);

    virtual void OnDirectChat(std::string sender, std::string msg);
    virtual void OnJoinRoom(std::string roomName);
    virtual void OnParticipantIn(std::string pseudo);
    virtual void OnParticipantOut(std::string pseudo);
    virtual void OnRoomChat(std::string sender, std::string msg, std::string room);
    virtual void OnRooms(std::vector<std::string>& roomsList);
    virtual void OnLoginResponse(bool bAccepted, std::string msg);
};
