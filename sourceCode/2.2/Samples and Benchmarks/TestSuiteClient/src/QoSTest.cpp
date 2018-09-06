#include "StdAfx.h"
#include "QoSTest.h"

CQoSTest::CQoSTest(void)
{
}

CQoSTest::~CQoSTest(void)
{
}



void CQoSTest::PrepareConnections()
{
    publisher.ConnectToServer("P");
    subscriber.ConnectToServer("S");

    subscriber.WaitForLogin();
    publisher.WaitForLogin();
}

void CQoSTest::TestSingle()
{
    SubscribeToBroadcastQueueRequest request;
    request.add_queuename("Q1");
    subscriber.sendRequest(&request);

    Sleep(1000);

    subscriber.ClearBroadcastStats();
    
    vector<string> queues;
    queues.push_back("Q1");
    PublishMessagesToSpecificQueues(queues);
 
    subscriber.ReportBroadcastStats();
}

void CQoSTest::TestPriorityEffect()
{
    SubscribeToBroadcastQueueRequest request;
    request.add_queuename("Q1");
    request.add_queuename("Q2");
    request.add_queuename("Q3");
    subscriber.sendRequest(&request);

    Sleep(1000);

    subscriber.ClearBroadcastStats();

    vector<string> queues;
    queues.push_back("Q1");
    queues.push_back("Q2");
    queues.push_back("Q3");

    PublishMessagesToSpecificQueues(queues);
    subscriber.ReportBroadcastStats(); 
}
void CQoSTest::TestQuotaEffect()
{
    SubscribeToBroadcastQueueRequest request;
    request.add_queuename("Q4");
    request.add_queuename("Q5");
    request.add_queuename("Q6");

    subscriber.sendRequest(&request);

    Sleep(1000);

    subscriber.ClearBroadcastStats();
 
    vector<string> queues;
    queues.push_back("Q4");
    queues.push_back("Q5");
    queues.push_back("Q6");

    PublishMessagesToSpecificQueues(queues);
    subscriber.ReportBroadcastStats();
}

void CQoSTest::PublishMessagesToSpecificQueues( vector<string>& queues )
{
    unsigned int messageId = 1;

    while (messageId < 5000)
    {
        BroadcastMessageRequest broadcastRequest;

        for (int i =0;i<queues.size();i++)
            broadcastRequest.add_queuename(queues.at(i));

        broadcastRequest.set_messageid(messageId);
        broadcastRequest.set_payload("Hello");
        broadcastRequest.set_timestamp("time");
        
        while (true)
        {
            if (publisher.sendRequest(&broadcastRequest) == TCPSocket::ResultOK)
            {
                break;
            }
            Sleep(50);
        }
        messageId ++;
    }
}

void CQoSTest::DoTest()
{
    PrepareConnections();
    TestSingle();
    TestPriorityEffect();
    TestQuotaEffect();
}

