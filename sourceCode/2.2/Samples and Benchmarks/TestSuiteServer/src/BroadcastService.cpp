#include "StdAfx.h"
#include "BroadcastService.h"

BroadcastService::BroadcastService(void)
{
}

BroadcastService::~BroadcastService(void)
{
}

void BroadcastService::handle( LogicalConnection* pClient, IncomingPacket* pRequest )
{
    BroadcastMessageRequest& request = reinterpret_cast<BroadcastMessageRequest&> (*pRequest);

    for (int i=0;i<request.queuename_size();i++)
    {
        const string& queueName = request.queuename(i);

        BroadcastMessageResponse* pMsgResponse = new BroadcastMessageResponse();
        pMsgResponse->set_sender(pClient->getKey());
        pMsgResponse->set_messageid(request.messageid());
        pMsgResponse->set_queuename(queueName);
        pMsgResponse->set_timestamp(request.timestamp());

        BroadcastPacket(pMsgResponse, queueName.c_str());
    }
}
