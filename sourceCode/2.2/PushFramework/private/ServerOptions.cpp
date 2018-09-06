/********************************************************************
	File :			ServerOptions.cpp
	Creation date :	2010/6/27

	License :			Copyright 2010 Ahmed Charfeddine, http://www.pushframework.com

				   Licensed under the Apache License, Version 2.0 (the "License");
				   you may not use this file except in compliance with the License.
				   You may obtain a copy of the License at

					   http://www.apache.org/licenses/LICENSE-2.0

				   Unless required by applicable law or agreed to in writing, software
				   distributed under the License is distributed on an "AS IS" BASIS,
				   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
				   See the License for the specific language governing permissions and
				   limitations under the License.



*********************************************************************/
#include "StdAfx.h"
#include "../include/ServerOptions.h"
#include "Utilities.h"


namespace PushFramework
{
ServerOptions options;

ServerOptions::ServerOptions(void)
{
	nMaxConnections = 1000;
	uLoginExpireDuration = 35;
	nWorkersCount = Utilities::getProcessorsCount() * 2;
	nStreamers = 1;
	isProfilingEnabled = false;
	isMonitorEnabled = false;
	monitorPort = 2011;
	samplingRate = 10;
	password = "";
	uMaxClientIdleTime = 120;
	usePools = false;
	nPhysicalConnectionsPoolSize = 100;

	uReadBufferSize = 8192;
	uSendBufferSize = 8192;

	uIntermediateReceiveBufferSize = uReadBufferSize*2;
	uIntermediateSendBufferSize = uSendBufferSize*3;
}

ServerOptions::~ServerOptions(void)
{
}
}