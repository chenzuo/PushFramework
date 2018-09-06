#ifndef LeaveRoomRequest__INCLUDED
#define LeaveRoomRequest__INCLUDED

#pragma once

#include "ProtocolIDs.h"
#include "Symbols.h"

class CHATPROTOCOL_API LeaveRoomRequest : public XMLRequest
{
public:
    LeaveRoomRequest(void);
    ~LeaveRoomRequest(void);

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
#endif // LeaveRoomRequest__INCLUDED
