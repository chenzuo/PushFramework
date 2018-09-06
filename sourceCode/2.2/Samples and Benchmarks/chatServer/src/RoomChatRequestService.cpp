#include "StdAfx.h"
#include "RoomChatRequestService.h"

#include "ChatParticipant.h"

RoomChatRequestService::RoomChatRequestService(void)
{
}

RoomChatRequestService::~RoomChatRequestService(void)
{
}

void RoomChatRequestService::handle( LogicalConnection* pClient, IncomingPacket* pRequest )
{
    ChatParticipant* pParticipant = (ChatParticipant*) pClient;

    RoomChatRequest* request = (RoomChatRequest*) pRequest;

    RoomChatResponse* pResponse = new RoomChatResponse;

    pResponse->Sender(pParticipant->getKey());
    pResponse->Msg(request->Msg());
    pResponse->Room(request->Room());

    broadcastManager.PushPacket(pResponse, request->Room().c_str(), "", 0);
}
