/********************************************************************
	File :			ClientFactory.cpp
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
#include "../include/ClientFactory.h"

#include "ClientFactoryImpl.h"
#include "ServerImpl.h"

namespace PushFramework
{


ClientFactory::ClientFactory(void)
{
}

ClientFactory::~ClientFactory(void)
{
}

unsigned int ClientFactory::getClientCount()
{
	return clientFactoryImpl.getClientCount();
}

bool ClientFactory::onBeforeClosingIdleClient( LogicalConnection* pClient )
{
	return false;
}

void ClientFactory::CopyLogicalConnection( LogicalConnection* pSrc, LogicalConnection* pDest )
{

}

void ClientFactory::disposeClient( LogicalConnection* pClient )
{
	delete pClient;
}

void ClientFactory::onClientReconnected( LogicalConnection* pClient )
{
	//
}

void ClientFactory::onClientConnected( LogicalConnection* pClient )
{
	//
}

void ClientFactory::onClientDisconnected( LogicalConnection* pClient, CloseReason closeReason )
{
	//
}

OutgoingPacket* ClientFactory::onNewConnection( ConnectionContext*& lpConnectionContext )
{
	return NULL;
}




}

