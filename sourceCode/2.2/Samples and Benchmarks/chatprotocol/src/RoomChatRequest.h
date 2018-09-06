#pragma once

#include "ProtocolIDs.h"
#include "Symbols.h"

class CHATPROTOCOL_API RoomChatRequest : public XMLRequest
{
public:
    RoomChatRequest(void);
    ~RoomChatRequest(void);
    std::string Room() const
    {
        return room;
    }
    void Room(std::string val)
    {
        room = val;
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
    std::string msg;
    std::string room;
protected:
    virtual bool FragmentXML();
    virtual bool ConstructXML();
    virtual void* CreateInstance();
};
