#include "stdafx.h"
#include "MyServer.h"
#include "DemoClient.h"


MyServer::MyServer(void)
{
}


MyServer::~MyServer(void)
{
}

LogicalConnection* MyServer::createLogicalConnection()
{
	return new DemoClient();
}
