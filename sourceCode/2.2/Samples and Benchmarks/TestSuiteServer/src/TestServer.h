#pragma once

class CTestServer : public Server
{
public:
    CTestServer(void);
    ~CTestServer(void);

    void CreateQueues();

    void CreateDefaultQueue();
	void CreateQueueForMemTesting();
	void CreateQueueForQoSTest();
    void CreateServices();
};
