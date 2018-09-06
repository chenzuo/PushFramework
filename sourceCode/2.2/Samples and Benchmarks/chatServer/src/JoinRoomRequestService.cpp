#include "StdAfx.h"
#include "JoinRoomRequestService.h"

#include "ChatParticipant.h"

JoinRoomRequestService::JoinRoomRequestService(void)
{
}

JoinRoomRequestService::~JoinRoomRequestService(void)
{
}

void JoinRoomRequestService::handle( LogicalConnection* pClient, IncomingPacket* pRequest )
{
    ChatParticipant* pParticipant = (ChatParticipant*) pClient;
    //First un-subscribe from current room :
    std::string curRoom = pParticipant->getChatRoom();
    if(curRoom != "")
    {
        broadcastManager.UnsubscribeConnectionFromQueue(pParticipant->getKey(), curRoom.c_str());
    }

    JoinRoomRequest* request = (JoinRoomRequest*) pRequest;

    std::string roomName = request->Room();
    pParticipant->setChatRoom(roomName);
    broadcastManager.SubscribeConnectionToQueue(pParticipant->getKey(), roomName.c_str());

    JoinRoomResponse response;
    response.Room(roomName);
    pParticipant->PushPacket(&response);
    //
}
