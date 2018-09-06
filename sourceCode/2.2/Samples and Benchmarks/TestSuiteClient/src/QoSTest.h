#pragma once
#include "TestSuiteBase.h"
#include "TestClient.h"

class CQoSTest :  public TestSuiteBase
{
public:
    CQoSTest(void);
    ~CQoSTest(void);
public:
    virtual void DoTest();
    virtual const char* GetTitle()
    {
        return "QoS Test";
    }
    virtual const char* GetDescription()
    {
        return "Performs tests relative to broadcast QoS";
    }
private:
    CTestClient publisher, subscriber;
    void PrepareConnections();
    void TestSingle();
    void TestPriorityEffect();
    void TestQuotaEffect();

    void PublishMessagesToSpecificQueues(vector<string>& queues);
};
