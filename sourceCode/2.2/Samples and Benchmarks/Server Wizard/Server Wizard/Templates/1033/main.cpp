#include "stdafx.h"
#include "server.h"
#include "protocol.h"
#include "clientfactory.h"
#include "services.h"



[!output CLIENT_FACTORY_CLASS_NAME] clientFactory;
ProtobufProtocol protocol;

[!if SERVICE_ECHO]
[!output SERVICE_ECHO_CLASS] service1;
[!endif]

[!if SERVICE_REDIRECT]
[!output SERVICE_REDIRECT_CLASS] service2;
[!endif]

[!if SERVICE_BROADCAST]
[!output SERVICE_BROADCAST_CLASS] service3;
[!endif]


void configure();

int main(int argc, char* argv[])
{
	// Configure and link all objects together before running the server.
	configure();


	[!if REGISTER_AS_SERVICE]
	bool runInteractively = false;
	if (argc == 2)
	{
		char param = argv[1][0];
		if (param == 'i' || param == 'I')
		{
			//Install service into SCM :
			theServer.Install(L"[!output REGISTER_AS_SERVICE_DISPLAYNAME]");
			return -1;
		}
		if (param == 'u' || param == 'U')
		{
			theServer.UnInstall();
			return -1;
		}
		if (param == 'm' || param == 'M')
		{
			runInteractively = true;
		}
	}
	if (!runInteractively)
	{
		theServer.Run();
		return 0;
	}
	[!endif]

	theServer.start(true);

	cout << "You are starting the server in interactive mode." << std::endl;
	cout << "Server should have started to listen for connections." << std::endl;
	cout << "Press q or Q to stop the server." << std::endl;

	while (true)
	{
		char ch;

		cin >> ch;

		if (ch == 'q')
		{
			break;
		}
	}

	theServer.stop();
	return 0;
}

void configure()
{
	theServer.setServerInfos("[!output SERVER_DESCRIPTION]");
	theServer.setClientFactory(new [!output CLIENT_FACTORY_CLASS_NAME]());

	PushFramework::options.uLoginExpireDuration = [!output MAX_LOGIN_TIME];
	PushFramework::options.uMaxClientIdleTime = [!output MAX_INACTIVITY_TIME];
	PushFramework::options.nMaxConnections = [!output MAX_CLIENTS];
	PushFramework::options.nStreamers = [!output STREAMING_THREADS];

	ListenerOptions lOptions;
	lOptions.pProtocol = &protocol;
	theServer.createListener([!output PORT], &lOptions);

	protocol.registerMessage(&EchoRequest::default_instance());
	protocol.registerMessage(&EchoResponse::default_instance());
	protocol.registerMessage(&LoginRequest::default_instance());
	protocol.registerMessage(&LoginChallengeResponse::default_instance());
	protocol.registerMessage(&RoutedMessageRequest::default_instance());
	protocol.registerMessage(&RoutedMessageResponse::default_instance());
	protocol.registerMessage(&GroupMessageRequest::default_instance());
	protocol.registerMessage(&GroupMessageResponse::default_instance());

	[!if SERVICE_ECHO]
	theServer.registerService(ProtobufProtocol::hash(EchoRequest::default_instance().GetTypeName()), &service1, "[!output SERVICE_ECHO_TAGNAME]");
	[!endif]

	[!if SERVICE_REDIRECT]
	theServer.registerService(ProtobufProtocol::hash(RoutedMessageRequest::default_instance().GetTypeName()), &service2, "[!output SERVICE_REDIRECT_TAGNAME]");
	[!endif]

	[!if SERVICE_BROADCAST]
	theServer.registerService(ProtobufProtocol::hash(GroupMessageRequest::default_instance().GetTypeName()), &service3, "[!output SERVICE_BROADCAST_TAGNAME]");
	[!endif]


	QueueOptions options;
	options.maxPackets = [!output QUEUE_SIZE];
	[!if QUEUE_EXPLICIT]
	options.requireRegistration = true;
	[!else]
	options.requireRegistration = false;
	[!endif]
	options.priority = [!output QUEUE_PRIORITY];
	options.packetsQuota = [!output QUEUE_QUOTA];
	[!if QUEUE_IGNORE_PREVIOUS]
	options.ignorePreviousPackets = true;
	[!else]
	options.ignorePreviousPackets = false;
	[!endif]
	options.fillRateThrottlingPeriod = [!output QUEUE_THROTTLE_PERIOD];
	options.fillRateThrottlingMaxPackets = [!output QUEUE_THROTTLE_COUNT];
	broadcastManager.CreateQueue("[!output QUEUE_NAME]", options);


	[!if REMOTE_MONITORING]
	PushFramework::options.isMonitorEnabled = true;
	[!else]
	PushFramework::options.isMonitorEnabled = false;
	[!endif]
	PushFramework::options.password = "[!output REMOTE_MONITORING_PASSWORD]";
	PushFramework::options.monitorPort = [!output REMOTE_MONITORING_PORT];
	[!if REMOTE_MONITORING_PROFILING]
	PushFramework::options.isProfilingEnabled = true;
	[!else]
	PushFramework::options.isProfilingEnabled = false;
	[!endif]
	PushFramework::options.samplingRate = [!output REMOTE_MONITORING_SAMPLING];
}


