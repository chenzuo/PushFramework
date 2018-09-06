#include "StdAfx.h"
#include "LogoutRequestService.h"

#include "ChatParticipant.h"

LogoutRequestService::LogoutRequestService(void)
{
}

LogoutRequestService::~LogoutRequestService(void)
{
}

void LogoutRequestService::handle( LogicalConnection* pClient, IncomingPacket* pRequest )
{
    Disconnect(pClient, false);
}
