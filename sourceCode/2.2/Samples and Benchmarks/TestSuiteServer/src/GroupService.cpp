#include "StdAfx.h"
#include "GroupService.h"

CGroupService::CGroupService(void)
{
}

CGroupService::~CGroupService(void)
{
}

void CGroupService::handle( LogicalConnection* pClient, IncomingPacket* pRequest )
{
    GroupMessageRequest* pMsgRequest = reinterpret_cast<GroupMessageRequest*> (pRequest);

    GroupMessageResponse* pGroupMsgResponse = new GroupMessageResponse();
    pGroupMsgResponse->set_sender(pClient->getKey());
    pGroupMsgResponse->set_msg(pMsgRequest->msg());

    BroadcastPacket(pGroupMsgResponse, "queue1");
}
