#include "StdAfx.h"
#include "RoomChatRequest.h"

RoomChatRequest::RoomChatRequest(void)
    : XMLRequest(RoomChatRequestID)
{
}

RoomChatRequest::~RoomChatRequest(void)
{
}

bool RoomChatRequest::FragmentXML()
{
    bool bResult = true;
    msg = getArgumentAsText("msg", bResult);
    room = getArgumentAsText("room", bResult);

    return bResult;
}

bool RoomChatRequest::ConstructXML()
{
    setArgumentAsText("msg", msg.c_str());
    setArgumentAsText("room", room.c_str());

    return true;
}

void* RoomChatRequest::CreateInstance()
{
    return new RoomChatRequest;
}