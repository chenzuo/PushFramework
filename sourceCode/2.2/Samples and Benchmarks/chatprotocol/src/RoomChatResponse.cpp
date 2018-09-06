#include "StdAfx.h"
#include "RoomChatResponse.h"

RoomChatResponse::RoomChatResponse(void)
    :XMLResponse(RoomChatResponseID)
{
}

RoomChatResponse::~RoomChatResponse(void)
{
}

bool RoomChatResponse::FragmentXML()
{
    bool bResult = true;
    sender = getArgumentAsText("from", bResult);
    msg = getArgumentAsText("msg", bResult);
    room = getArgumentAsText("room", bResult);

    return bResult;
}

bool RoomChatResponse::ConstructXML()
{
    setArgumentAsText("from", sender.c_str());
    setArgumentAsText("msg", msg.c_str());
    setArgumentAsText("room", room.c_str());

    return true;
}

void* RoomChatResponse::CreateInstance()
{
    return new RoomChatResponse;
}