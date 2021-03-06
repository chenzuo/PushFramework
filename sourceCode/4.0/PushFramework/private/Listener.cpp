/********************************************************************
	File :			Listener.cpp
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
#include "Listener.h"

#include "../include/ServerOptions.h"
#include "ServerImpl.h"
#include "ServerStats.h"
#include "ClientFactory.h"

#ifdef Plateform_Windows
#include "ListenerImpl_Win.h"
#else
#ifdef Plateform_Linux
#include "ListenerImpl_Linux.h"
#endif
#endif



namespace PushFramework
{


Listener::Listener(ServerImpl* pServerImpl)
{
	this->pServerImpl = pServerImpl;
    pImpl = new ListenerImpl(this);
    uPort = 0;
}
Listener::~Listener(void)
{
    delete pImpl;
}

void Listener::setListeningPort( unsigned int uPort )
{
    this->uPort = uPort;
}

bool Listener::startListening()
{
    return pImpl->startListening();
}

void Listener::stopListening()
{
    pImpl->stopListening();
}

Protocol* Listener::getProtocol()
{
	return listenerOptions.pProtocol;
}

void Listener::setOptions( ListenerOptions& listenerOptions )
{
	this->listenerOptions = listenerOptions;
}

unsigned int Listener::getPort()
{
	return uPort;
}

bool Listener::handleAcceptedSocket(SOCKET clientSocket, SOCKADDR_IN address)
{
	pServerImpl->getServerStats().addToCumul(ServerStats::VisitorsSYNs, 1);

	if (pServerImpl->getClientFactory().getClientCount() >= pServerImpl->getServerOptions().nMaxConnections)
	{
		return false;
	}

	//Check if address is not blocked :
	if (!pServerImpl->getClientFactory().isAddressAllowed(address.sin_addr))
	{
		return false;
	}

	return pServerImpl->getClientFactory().createPhysicalConnection(clientSocket, address, &listenerOptions);
}

}
