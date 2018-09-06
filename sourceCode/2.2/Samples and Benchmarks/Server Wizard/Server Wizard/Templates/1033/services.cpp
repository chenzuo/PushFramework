#include "stdafx.h"
#include "services.h"
#include "client.h"

[!output SERVICE_ECHO_CLASS]::[!output SERVICE_ECHO_CLASS]()
{
	//
}

[!output SERVICE_ECHO_CLASS]::~[!output SERVICE_ECHO_CLASS]()
{
	//
}

void [!output SERVICE_ECHO_CLASS]::handle( LogicalConnection* pClient, IncomingPacket* pRequest )
{
	[!output CLIENT_CLASS_NAME]* pCurClient = ([!output CLIENT_CLASS_NAME]*) (pClient);
	EchoRequest* pEchoRequest = reinterpret_cast<EchoRequest*> (pRequest);

	EchoResponse response;
	response.set_msg(pEchoRequest->msg());

	pCurClient->PushPacket(&response);
}

[!output SERVICE_REDIRECT_CLASS]::[!output SERVICE_REDIRECT_CLASS]()
{
	//
}

[!output SERVICE_REDIRECT_CLASS]::~[!output SERVICE_REDIRECT_CLASS]()
{
	//
}

void [!output SERVICE_REDIRECT_CLASS]::handle( LogicalConnection* pClient, IncomingPacket* pRequest )
{
	[!output CLIENT_CLASS_NAME]* pCurClient = ([!output CLIENT_CLASS_NAME]*) (pClient);
	RoutedMessageRequest* pMsgRequest = reinterpret_cast<RoutedMessageRequest*> (pRequest);

	[!output CLIENT_CLASS_NAME]* pRecipient = ([!output CLIENT_CLASS_NAME]*) FindClient(pMsgRequest->recipient().c_str());
	if (pRecipient)
	{
		RoutedMessageResponse response;
		response.set_sender(pCurClient->getKey());
		response.set_msg(pMsgRequest->msg());

		pRecipient->PushPacket(&response);
		ReturnClient(pRecipient);
	}
}

[!output SERVICE_BROADCAST_CLASS]::[!output SERVICE_BROADCAST_CLASS]()
{
	//
}

[!output SERVICE_BROADCAST_CLASS]::~[!output SERVICE_BROADCAST_CLASS]()
{
	//
}

void [!output SERVICE_BROADCAST_CLASS]::handle( LogicalConnection* pClient, IncomingPacket* pRequest )
{
	GroupMessageRequest* pMsgRequest = reinterpret_cast<GroupMessageRequest*> (pRequest);

	GroupMessageResponse* pGroupMsgResponse = new GroupMessageResponse();
	pGroupMsgResponse->set_sender(pClient->getKey());
	pGroupMsgResponse->set_msg(pMsgRequest->msg());

	BroadcastPacket(pGroupMsgResponse, "[!output QUEUE_NAME]");
}
