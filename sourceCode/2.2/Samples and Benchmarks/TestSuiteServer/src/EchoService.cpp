#include "StdAfx.h"
#include "EchoService.h"
#include "TestClient.h"

CEchoService::CEchoService(void)
{
}

CEchoService::~CEchoService(void)
{
}

void CEchoService::handle( LogicalConnection* pClient, IncomingPacket* pRequest )
{
	CTestClient* pTestClient = reinterpret_cast<CTestClient*> (pClient);
    EchoRequest* pEchoRequest = reinterpret_cast<EchoRequest*> (pRequest);

    EchoResponse response;
    response.set_msg(pEchoRequest->msg());

    pTestClient->PushPacket(&response);
}
