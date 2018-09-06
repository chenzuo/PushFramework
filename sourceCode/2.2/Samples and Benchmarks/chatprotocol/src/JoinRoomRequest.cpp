#include "StdAfx.h"
#include "JoinRoomRequest.h"

JoinRoomRequest::JoinRoomRequest(void)
    :XMLRequest(JoinRoomRequestID)
{
}

JoinRoomRequest::~JoinRoomRequest(void)
{
}

bool JoinRoomRequest::FragmentXML()
{
    bool bResult = true;
    room = getArgumentAsText("room", bResult);
    return bResult;
}

bool JoinRoomRequest::ConstructXML()
{
    setArgumentAsText("room", room.c_str());
    return true;
}

void* JoinRoomRequest::CreateInstance()
{
    return new JoinRoomRequest;
}
