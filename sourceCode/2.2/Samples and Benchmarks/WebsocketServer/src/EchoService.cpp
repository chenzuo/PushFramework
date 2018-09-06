#include "StdAfx.h"
#include "EchoService.h"

#include "WebsocketClient.h"
#include "WebsocketDataMessage.h"


EchoService::EchoService(void)
{
}


EchoService::~EchoService(void)
{
}

void EchoService::handle( LogicalConnection* pClient, IncomingPacket* pRequest )
{
	WebsocketDataMessage& request = (WebsocketDataMessage&)(*pRequest);
	WebsocketClient& client = (WebsocketClient&) (*pClient);

	WebsocketDataMessage response(EchoCommunication);
	response.SetArguments(request.GetArg1());
	client.PushPacket(&response);
}
