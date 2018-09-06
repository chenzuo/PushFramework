#include "StdAfx.h"
#include "RoomsResponse.h"

RoomsResponse::RoomsResponse(void)
    :XMLResponse(RoomsResponseID)
{
}

RoomsResponse::~RoomsResponse(void)
{
}

RoomsResponse::roomVectorT& RoomsResponse::getRooms()
{
    return roomVector;
}

void RoomsResponse::addRoom( std::string roomName )
{
    roomVector.push_back(roomName);
}

bool RoomsResponse::FragmentXML()
{
    XMLNode xNode = getInputXML();
    int nRooms = xNode.getChildNode("rooms").nChildNode("room");
    for (int i=0; i<nRooms; i++)
    {
        XMLNode xRoom = xNode.getChildNode("rooms").getChildNode("room", i);
        std::string roomName = xRoom.getAttribute("name");

        roomVector.push_back(roomName);
    }
    return true;
}

bool RoomsResponse::ConstructXML()
{
    getOutputXML().addChild("rooms");
    for (roomVectorT::iterator it = roomVector.begin();
            it!=roomVector.end();
            it++)
    {
        std::string roomName = *it;
        getOutputXML().getChildNode("rooms").addChild("room").addAttribute("name", roomName.c_str());
    }
    return true;
}

void* RoomsResponse::CreateInstance()
{
    return new RoomsResponse();
}
