#include "StdAfx.h"
#include "SubscribeService.h"

CSubscribeService::CSubscribeService(void)
{
}

CSubscribeService::~CSubscribeService(void)
{
}

void CSubscribeService::handle( LogicalConnection* pClient, IncomingPacket* pRequest )
{
    SubscribeToBroadcastQueueRequest& request = reinterpret_cast<SubscribeToBroadcastQueueRequest&> (*pRequest);

    broadcastManager.RemoveConnection(pClient->getKey());

    for (int i=0;i<request.queuename_size();i++)
    {
        const string& queueName = request.queuename(i);
        broadcastManager.SubscribeConnectionToQueue(pClient->getKey(), queueName.c_str());
    }
    
}
