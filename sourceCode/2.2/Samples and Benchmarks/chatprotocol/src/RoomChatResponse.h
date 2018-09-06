#pragma once

#include "ProtocolIDs.h"
#include "Symbols.h"

class CHATPROTOCOL_API RoomChatResponse : public XMLResponse
{
public:
    RoomChatResponse(void);
    ~RoomChatResponse(void);

    std::string Room() const
    {
        return room;
    }
    void Room(std::string val)
    {
        room = val;
    }
    std::string Sender() const
    {
        return sender;
    }
    void Sender(std::string val)
    {
        sender = val;
    }
    std::string Msg() const
    {
        return msg;
    }
    void Msg(std::string val)
    {
        msg = val;
    }

private:
    std::string sender;
    std::string msg;
    std::string room;

protected:
    virtual bool FragmentXML();
    virtual bool ConstructXML();

    virtual void* CreateInstance();
};
