#include "StdAfx.h"
#include "LeaveRoomRequest.h"

LeaveRoomRequest::LeaveRoomRequest(void)
    :XMLRequest(LeaveRoomRequestID)
{
}

LeaveRoomRequest::~LeaveRoomRequest(void)
{
}

bool LeaveRoomRequest::FragmentXML()
{
    bool bResult = true;
    room = getArgumentAsText("room", bResult);
    return bResult;
}

bool LeaveRoomRequest::ConstructXML()
{
    setArgumentAsText("room", room.c_str());
    return true;
}

void* LeaveRoomRequest::CreateInstance()
{
    return new LeaveRoomRequest;
}
