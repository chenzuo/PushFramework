#ifndef JoinRoomResponse__INCLUDED
#define JoinRoomResponse__INCLUDED

#pragma once

#include "ProtocolIDs.h"
#include "Symbols.h"

class CHATPROTOCOL_API JoinRoomResponse : public XMLResponse
{
public:
    JoinRoomResponse(void);
    ~JoinRoomResponse(void);
    std::string Room() const
    {
        return room;
    }
    void Room(std::string val)
    {
        room = val;
    }

private:
    std::string room;

protected:
    virtual bool FragmentXML();
    virtual bool ConstructXML();

    virtual void* CreateInstance();
};
#endif // JoinRoomResponse__INCLUDED
