#include "StdAfx.h"
#include "RoutedService.h"
#include "TestClient.h"

CRoutedService::CRoutedService(void)
{
}

CRoutedService::~CRoutedService(void)
{
}

void CRoutedService::handle( LogicalConnection* pClient, IncomingPacket* pRequest )
{
    CTestClient* pTestClient = dynamic_cast<CTestClient*> (pClient);
    RoutedMessageRequest* pMsgRequest = reinterpret_cast<RoutedMessageRequest*> (pRequest);

    CTestClient* pRecipient = dynamic_cast<CTestClient*> (FindClient(pMsgRequest->recipient().c_str()));
    if (pRecipient)
    {
        RoutedMessageResponse response;
        response.set_sender(pTestClient->getKey());
        response.set_msg(pMsgRequest->msg());

        pRecipient->PushPacket(&response);
    }

    
}
