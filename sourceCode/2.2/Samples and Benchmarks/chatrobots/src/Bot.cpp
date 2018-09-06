#include "stdafx.h"
#include "Bot.h"


Bot::Bot(Options_t& _options)
    : options(_options)
{
    isLogged = false;
    //
    nCentiSec = 0;
    nSecs = 0;
}

Bot::~Bot(void)
{
    //
}

unsigned int Bot::getLoggedTime()
{
    if (isLogged)
    {
        time_t current = time(NULL);
        return difftime(current, dtLoggedTime);
    }
    return 0;
}

void Bot::setLogged()
{
    dtLoggedTime = time(NULL);
    isLogged = true;
}

void Bot::onPerformAutomatedJob()
{
    if (!isLogged)
        return;

    nSecs++;


    if (options.sendRoomChatDuration > 0 && (nSecs % options.sendRoomChatDuration == 0))
    {
        SendChatToJoinedRoom();
    }


    if (options.directChatDuration > 0 && (nSecs % options.directChatDuration == 0) )
    {
        for (int i=0;i<options.directChatBulks;i++)
            SendChatToRandomClient();
    }


    if (options.joinRoomDuration > 0 && (nSecs % options.joinRoomDuration == 0))
    {
        JoinRandomRoom();
    }

    if (getLoggedTime() > options.stayDuration)
    {
        Logout();
    }

}

void Bot::onConnected()
{
    cout << ChatAPI::getPseudo() << " has succesfully connected" << std::endl;
}

void Bot::OnLoginResponse(bool bAccepted, std::string msg)
{
    if (bAccepted)
    {
        setLogged();
        cout << ChatAPI::getPseudo() << " has logged in" << std::endl;
    }
    else
    {
        cout << ChatAPI::getPseudo() << " was unable to login" << std::endl;
    }
}

void Bot::OnRooms(std::vector<std::string>& roomsList)
{
    this->roomsList = roomsList;
}

void Bot::onConnectionClosed()
{
    isLogged = false;
    cout << ChatAPI::getPseudo() << " 'connection was closed" << std::endl;
}

void Bot::OnDirectChat(std::string sender, std::string msg)
{

    if (options.replyDirectProb > 0)
    {
        if (rand() % 100 > directChatSinking)
        {
            std::string str = "hi " + sender + " i received ur msg";
            SendDirectChat(sender, str);
        }
    }

}

void Bot::OnJoinRoom(std::string roomName)
{
    joinedRoom = roomName;
}

std::string Bot::getRandomBotName()
{
    int i = rand() % 1000;
    std::stringstream ss;
    ss << std::noskipws;
    ss << "Bot ";
    ss << i;
    std::string botPseudo = ss.str();

    return botPseudo;
}

void Bot::SendChatToRandomClient()
{
    std::string player;

    if (clientVect.size() == 0)
    {
        player = getRandomBotName();
    }
    else
    {
        int index = rand() % clientVect.size();

        player = clientVect.at(index);
    }


    ChatAPI::SendDirectChat(player, fixedMessage);
}

void Bot::SendChatToJoinedRoom()
{
    if (joinedRoom == "")
        return;

    ChatAPI::SendRoomChat(fixedMessage, joinedRoom);
}

void Bot::JoinRandomRoom()
{
    if (roomsList.size() == 0)
        return;

    int index = rand() % roomsList.size();

    std::string roomName = roomsList.at(index);
    if (roomName == joinedRoom)
        return;

    ChatAPI::JoinRoom(roomName);
}
