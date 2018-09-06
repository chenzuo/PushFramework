#include "StdAfx.h"
#include "ChatServerProtocol.h"

#include "LoginRequest.h"
#include "DirectChatRequest.h"
#include "JoinRoomRequest.h"
#include "LeaveRoomRequest.h"
#include "RoomChatRequest.h"
#include "LogoutRequest.h"

ChatServerProtocol::ChatServerProtocol(void)
{
    registerIncomingPacketTemplate(LoginRequestID, new LoginRequest, 100);
    registerIncomingPacketTemplate(DirectChatRequestID, new DirectChatRequest, 100);
    registerIncomingPacketTemplate(JoinRoomRequestID, new JoinRoomRequest, 100);
    registerIncomingPacketTemplate(LeaveRoomRequestID, new LeaveRoomRequest, 100);
    registerIncomingPacketTemplate(RoomChatRequestID, new RoomChatRequest, 100);
    registerIncomingPacketTemplate(LogoutRequestID, new LogoutRequest, 100);
}

ChatServerProtocol::~ChatServerProtocol(void)
{
}
