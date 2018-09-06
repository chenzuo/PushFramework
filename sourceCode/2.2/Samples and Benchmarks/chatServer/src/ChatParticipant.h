#pragma once

class ChatParticipant : public LogicalConnection
{
public:
    ChatParticipant(std::string pseudo);
    ~ChatParticipant(void);
    virtual CLIENT_KEY getKey();
    std::string getChatRoom()
    {
        return chatRoom;
    }
    void setChatRoom(std::string chatRoom)
    {
        this->chatRoom = chatRoom;
    }
private:
    std::string pseudo;
    std::string chatRoom;
};
