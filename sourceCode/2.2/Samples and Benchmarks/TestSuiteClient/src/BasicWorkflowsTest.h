#pragma once
#include "TestSuiteBase.h"
#include "TestClient.h"

class CBasicWorkflowsTest :  public TestSuiteBase
{
public:
	CBasicWorkflowsTest(void);
	~CBasicWorkflowsTest(void);
public:
	virtual void DoTest();
	virtual const char* GetTitle();
	virtual const char* GetDescription();
private:
    CTestClient client1, client2, client3;
    void PrepareConnections();
    void TestEcho();
    void TestRoutedCommunication();
    void TestGroupCommunication();

};
