// TestSuiteServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestServer.h"
#include "TestClientFactory.h"


int _tmain(int argc, _TCHAR* argv[])
{
	CTestServer server;

	server.setClientFactory(new CTestClientFactory(), true);
	server.CreateServices();
	server.CreateQueues();

	options.isMonitorEnabled = true;
	options.monitorPort = 20011;
	options.password = "alibaba";
	options.isProfilingEnabled = true;
	options.samplingRate = 10;
	options.nMaxConnections = 10000;
	options.uLoginExpireDuration = 60;
	options.uMaxClientIdleTime = 120;

	
	ListenerOptions lOptions;
	lOptions.pProtocol = new TestProtocol();

	server.createListener(20010, &lOptions);

	server.start(true);

	while (true)
	{
		char ch;
		cin >> ch;
		if (ch == 'q')
		{
			break;
		}
	}

	cout << "Failures " << nFailed << endl;
	char ch2;
	cin >> ch2;

	server.stop();
	return 0;
}

