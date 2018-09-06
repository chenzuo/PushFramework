#include "StdAfx.h"
#include "LeaveRoomRequestService.h"

#include "ChatParticipant.h"

LeaveRoomRequestService::LeaveRoomRequestService(void)
{
}

LeaveRoomRequestService::~LeaveRoomRequestService(void)
{
}

void LeaveRoomRequestService::handle( LogicalConnection* pClient, IncomingPacket* pRequest )
{
    ChatParticipant* pParticipant = (ChatParticipant*) pClient;

    LeaveRoomRequest* request = (LeaveRoomRequest*) pRequest;

    std::string roomName = request->Room();

    broadcastManager.UnsubscribeConnectionFromQueue(pParticipant->getKey(), roomName.c_str());

    ReturnClient(pParticipant);
}
