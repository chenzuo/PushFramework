#ifndef JoinRoomRequest__INCLUDED
#define JoinRoomRequest__INCLUDED

#pragma once

#include "ProtocolIDs.h"
#include "Symbols.h"

class CHATPROTOCOL_API JoinRoomRequest : public XMLRequest
{
public:
    JoinRoomRequest(void);
    ~JoinRoomRequest(void);
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
#endif // JoinRoomRequest__INCLUDED
