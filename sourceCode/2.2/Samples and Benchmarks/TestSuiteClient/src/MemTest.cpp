#include "StdAfx.h"
#include "MemTest.h"

CMemTest::CMemTest(void)
{
}

CMemTest::~CMemTest(void)
{
}

void CMemTest::DoTest()
{
	PrepareConnections();

	SendOneGiga();
}

void CMemTest::PrepareConnections()
{
	client1.ConnectToServer("memTestClient1");
	//client2.ConnectToServer("memTestClient2");

	client1.WaitForLogin();
	//client2.WaitForLogin();

	SubscribeToBroadcastQueueRequest request;
	request.add_queuename("memTestQueue");
	//client2.sendRequest(&request);

	Sleep(1000);
}

void CMemTest::SendOneGiga()
{
	MemTestRequest request;
	request.set_msg(fixedMessage);
	request.set_target(3);

	UINT nTotal = 10 * 1000;
	UINT i = 0;
	for (i=0;i<nTotal;i++)
	{
		while (true)
		{
			int result = client1.sendRequest(&request);
			if (result == TCPSocket::ResultFailed)
				return;
			if(result == TCPSocket::ResultOK)
				break;
		}
	}

	cout << "Sent: " << i << endl;
}
