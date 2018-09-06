#pragma once




typedef struct Options_t
{
    std::string serverIP;
    int port;
    int stayDuration;
    int directChatDuration;
    int directChatBulks;
    int joinRoomDuration;
    int replyDirectProb;
    int sendRoomChatDuration;
    int nConnectAtOnce;
    int stagedPhaseDuration;
    int stagedConnectionPerSecond;
} Options_t;


class Bot : public ChatAPI
{
public:
    Bot(Options_t& options);
    ~Bot(void);
private:
    Options_t& options;
    virtual void onConnected();
    virtual void onConnectionClosed();
    virtual void OnDirectChat(std::string sender, std::string msg);
    virtual void OnJoinRoom(std::string roomName);
    virtual void OnParticipantIn(std::string pseudo)
    {
        clientVect.push_back(pseudo);
    }
    virtual void OnParticipantOut(std::string pseudo)
    {
        //
    }
    virtual void OnRoomChat(std::string sender, std::string msg, std::string room)
    {
        //
    }
    virtual void OnRooms(std::vector<std::string>& roomsList);
    virtual void OnLoginResponse(bool bAccepted, std::string msg);




    void setLogged();
    unsigned int getLoggedTime();
public:
	void onPerformAutomatedJob();

private:
    std::string pseudo;
    bool isLogged;
    time_t dtLoggedTime;
    //
    std::vector<std::string> clientVect;
    std::vector<std::string> roomsList;
    std::string joinedRoom;
private:
    int roomChatFreq;
    int directChatFreq;
    int directChatSinking;
    int joinRoomFreq;
    int nCentiSec;
    int nSecs;

private:

    std::string getRandomBotName();
    void SendChatToRandomClient();

    void SendChatToJoinedRoom();
    void JoinRandomRoom();
};
