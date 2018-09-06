#include "StdAfx.h"
#include "ChatClientProtocol.h"


#include "DirectChatResponse.h"
#include "JoinRoomResponse.h"
#include "LoginResponse.h"
#include "ParticipantInResponse.h"
#include "ParticipantOutResponse.h"
#include "RoomChatResponse.h"
#include "RoomsResponse.h"
#include "LoginPuzzleResponse.h"



ChatClientProtocol::ChatClientProtocol(void)
{
    registerIncomingPacketTemplate(DirectChatResponseID, new DirectChatResponse, 100);
    registerIncomingPacketTemplate(JoinRoomResponseID, new JoinRoomResponse, 100);
    registerIncomingPacketTemplate(LoginResponseID, new LoginResponse, 100);
    registerIncomingPacketTemplate(ParticipantInResponseID, new ParticipantInResponse, 100);
    registerIncomingPacketTemplate(ParticipantOutResponseID, new ParticipantOutResponse, 100);
    registerIncomingPacketTemplate(RoomChatResponseID, new RoomChatResponse, 100);
    registerIncomingPacketTemplate(RoomsResponseID, new RoomsResponse, 100);
    registerIncomingPacketTemplate(LoginPuzzleResponseID, new LoginPuzzleResponse, 100);
}

ChatClientProtocol::~ChatClientProtocol(void)
{
}
