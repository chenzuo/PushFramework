#pragma once

#include "ProtocolIDs.h"
#include "Symbols.h"

class CHATPROTOCOL_API RoomsResponse : public XMLResponse
{
public:
    RoomsResponse(void);
    ~RoomsResponse(void);
    typedef std::vector<std::string> roomVectorT;
    roomVectorT& getRooms();
    void addRoom(std::string roomName);
private:
    roomVectorT roomVector;
protected:
    virtual bool FragmentXML();
    virtual bool ConstructXML();

    virtual void* CreateInstance();
};
