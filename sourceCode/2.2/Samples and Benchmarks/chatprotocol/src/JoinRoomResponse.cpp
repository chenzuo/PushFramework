#include "StdAfx.h"
#include "JoinRoomResponse.h"

JoinRoomResponse::JoinRoomResponse(void)
    :XMLResponse(JoinRoomResponseID)
{
}

JoinRoomResponse::~JoinRoomResponse(void)
{
}

bool JoinRoomResponse::FragmentXML()
{
    bool bResult = true;
    room = getArgumentAsText("room", bResult);
    return bResult;
}

bool JoinRoomResponse::ConstructXML()
{
    setArgumentAsText("room", room.c_str());
    return true;
}

void* JoinRoomResponse::CreateInstance()
{
    return new JoinRoomResponse;
}
