#include "StdAfx.h"
#include "MemTestService.h"
#include "TestClient.h"

CMemTestService::CMemTestService(void)
{
}

CMemTestService::~CMemTestService(void)
{
}

void CMemTestService::handle( LogicalConnection* pClient, IncomingPacket* pRequest )
{
	CTestClient* pTestClient = dynamic_cast<CTestClient*> (pClient);
	MemTestRequest* pTestRequest = reinterpret_cast<MemTestRequest*> (pRequest);

	if (pTestRequest->target() == 0)
	{
		//Do nothing.
		return; 
	}

	if (pTestRequest->target() == 1)
	{
		//Echo it back.
		MemTestResponse response;
		response.set_msg(pTestRequest->msg());
		pTestClient->PushPacket(&response);
	}

	if (pTestRequest->target() == 2)
	{
		//Relay to another client.
		MemTestResponse response;
		response.set_msg(pTestRequest->msg());
		CTestClient* pTarget = (CTestClient*) FindClient("memTestClient2");
		if (pTarget)
		{
			pTarget->PushPacket(&response);
			ReturnClient(pTarget);
		}
	}

	if (pTestRequest->target() == 3)
	{
		//Push to queue.
		MemTestResponse* response = new MemTestResponse();
		response->set_msg(pTestRequest->msg());
		bool ret = BroadcastPacket(response, "memTestQueue");

		static UINT i = 0;
		if (!ret)
		{
			nFailed ++;
		}
		i++;
		if (i == 10000)
		{
			cout << "received all packets";
		}
	}
}
