#include "StdAfx.h"
#include "TestClientFactory.h"
#include "TestClient.h"

CTestClientFactory::CTestClientFactory(void)
{
}

CTestClientFactory::~CTestClientFactory(void)
{
}


int CTestClientFactory::onFirstRequest( IncomingPacket& request, ConnectionContext* lpContext, LogicalConnection*& lpClient, OutgoingPacket*& lpPacket )
{
	//This cast is ok.
	protobuf::Message& message = reinterpret_cast<protobuf::Message&> (request);

	//If dynamic cast fails, now we should close the connection, because all is expected
	//at this time is a LoginRequest message : 
	
	LoginRequest* pLoginRequest = dynamic_cast<LoginRequest*> (&message);
	if (!pLoginRequest)
	{
		return ClientFactory::RefuseAndClose;
	}


    CTestClient* pClient = new CTestClient(pLoginRequest->pseudo().c_str());
    lpClient = pClient;

	LoginResultResponse* pResponse = new LoginResultResponse();
	pResponse->set_pseudo(pLoginRequest->pseudo());
	pResponse->set_is_accepted(true);
	lpPacket = reinterpret_cast<OutgoingPacket*> (pResponse);

    return ClientFactory::CreateClient;
}
