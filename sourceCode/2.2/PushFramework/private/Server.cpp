/********************************************************************
	File :			Server.cpp
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
#include "../include/Server.h"

#include "ServerImpl.h"
#include "../include/Service.h"
#include "../include/OutgoingPacket.h"
#include "BroadcastStreamerManager.h"

#include "ChannelFactory.h"

#include "Utilities.h"
#include "../include/ServerOptions.h"
#include "MonitorAcceptor.h"

namespace PushFramework
{
Server::Server(void)
{
    pImpl = new ServerImpl(this);
}

Server::~Server(void)
{
    delete pImpl;
}

void Server::setClientFactory( ClientFactory* pClientFactory, bool bManageDisposal /*= false*/ )
{
    pImpl->setClientFactory(pClientFactory, bManageDisposal);
}

void Server::registerService( unsigned int serviceId, Service* pService, const char* serviceName, bool bManageDisposal/* = false*/ )
{
    pService->pServer = this;
    //
    pImpl->registerService(serviceId, pService, serviceName, bManageDisposal);
}

void Server::start(bool startInSeparateThread)
{
    pImpl->start(startInSeparateThread);
}

void Server::stop()
{
    pImpl->stop();
}

void Server::pause()
{
    pImpl->pause();
}

void Server::resume()
{
    pImpl->resume();
}

ClientFactory* Server::getClientFactory()
{
    return pImpl->getClientFactory();
}


bool Server::handleMonitorRequest( const char* command, char* lpOut )
{
    return false;
}

void Server::setServerInfos( const char* serverName )
{
    pImpl->setServeInfos(serverName);
}
void Server::getPath(char* path, int len)
{
    Utilities::getPath(path, len);
}

void* Server::workerThreadBegin()
{
    return NULL;
}

void Server::workerThreadEnd( void* )
{
    //
}

bool Server::createListener( int port, ListenerOptions* pOptions /*= NULL*/ )
{
    return pImpl->createListener(port, pOptions);
}


void Server::addBlockedIPRange( const char* ipStart, const char* ipStop )
{
    channelFactory.addIPRangeAccess(ipStart, ipStop, false);
}

void Server::addPermitIPRange( const char* ipStart, const char* ipStop )
{
    channelFactory.addIPRangeAccess(ipStart, ipStop, true);
}

void Server::performPeriodicTasks()
{

}

void Server::OnStarted()
{

}

}
