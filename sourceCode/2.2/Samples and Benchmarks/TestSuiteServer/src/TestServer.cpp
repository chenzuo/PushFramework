#include "StdAfx.h"
#include "TestServer.h"

#include "EchoService.h"
#include "RoutedService.h"
#include "GroupService.h"
#include "BroadcastService.h"
#include "SubscribeService.h"
#include "MemTestService.h"

CTestServer::CTestServer(void)
{
}

CTestServer::~CTestServer(void)
{
}

void CTestServer::CreateQueues()
{
    CreateDefaultQueue();
    CreateQueueForQoSTest();
	CreateQueueForMemTesting();
}

void CTestServer::CreateServices()
{
    Server::registerService(EchoRequestID, new CEchoService(), "echo", true);
    Server::registerService(RoutedMessageRequestID, new CRoutedService(), "routed", true);
    Server::registerService(GroupMessageRequestID, new CGroupService(), "group", true);
    Server::registerService(BroadcastMessageRequestID, new BroadcastService(), "broadcast", true);
    Server::registerService(SubscribeToBroadcastQueueRequestID, new CSubscribeService(), "subscribe", true);
	Server::registerService(MemTestRequestID, new CMemTestService(), "memTest", true);
}

void CTestServer::CreateDefaultQueue()
{
    QueueOptions options;
    options.maxPackets = 100;
    options.requireRegistration = false;
    options.priority = 10;
    options.packetsQuota = 10;

    broadcastManager.CreateQueue("queue1", options);
}

void CTestServer::CreateQueueForQoSTest()
{
    QueueOptions options;
    options.maxPackets = 100;
    options.requireRegistration = true;
    options.priority = 10;
    options.packetsQuota = 10;

    //Q1 is the highest priority queue
    broadcastManager.CreateQueue("Q1", options);

    //Q2 and Q3 share same priority
    options.priority = 8;
    broadcastManager.CreateQueue("Q2", options);
    broadcastManager.CreateQueue("Q3", options);

    //Q4, Q5 and Q6 have same priority but differ in quota
    options.priority = 5;
    options.packetsQuota = 10;
    broadcastManager.CreateQueue("Q4", options);

    options.packetsQuota = 20;
    broadcastManager.CreateQueue("Q5", options);

    options.packetsQuota = 5;
    broadcastManager.CreateQueue("Q6", options);
}

void CTestServer::CreateQueueForMemTesting()
{
	QueueOptions options;
	options.maxPackets = 1;
	options.requireRegistration = true;
	options.priority = 11;
	options.packetsQuota = 10;

	broadcastManager.CreateQueue("memTestQueue", options);
}
