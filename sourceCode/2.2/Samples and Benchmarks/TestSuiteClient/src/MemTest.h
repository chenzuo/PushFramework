#pragma once
#include "TestSuiteBase.h"
#include "TestClient.h"

class CMemTest :  public TestSuiteBase
{
public:
	CMemTest(void);
	~CMemTest(void);

	virtual void DoTest();
	virtual const char* GetTitle()
	{
		return "Memory Test";
	}
	virtual const char* GetDescription()
	{
		return "Verifies memory stability under stationary conditions";
	}
private:
	CTestClient client1, client2;
	void PrepareConnections();

	void SendOneGiga();
};
