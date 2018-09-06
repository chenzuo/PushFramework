#include "stdafx.h"
#include "server.h"

[!output SERVER_CLASS_NAME] theServer;

[!output SERVER_CLASS_NAME]::[!output SERVER_CLASS_NAME]() :SystemService(L"[!output REGISTER_AS_SERVICE_NAME]")
{
	//
}

[!output SERVER_CLASS_NAME]::~[!output SERVER_CLASS_NAME]()
{
	//
}

void [!output SERVER_CLASS_NAME]::OnStart()
{
	Server::start(false);
}

void [!output SERVER_CLASS_NAME]::OnStop()
{
	Server::stop();
}
