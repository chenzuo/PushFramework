/********************************************************************
	File :			ClientFactory.h
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
#ifndef ClientFactory__INCLUDED
#define ClientFactory__INCLUDED

#pragma once

#include "PushFramework.h"

namespace PushFramework
{

class LogicalConnection;
class ClientFactory;
class IncomingPacket;
class OutgoingPacket;
class ClientFactoryImpl;
class Dispatcher;
class Server;
class ServerImpl;
class ConnectionContext;

/**
	Contains the clients management logic (creation, login, disconnection, disposal, storage, ref count etc).
	*/
class PUSHFRAMEWORK_API ClientFactory
{
    friend class Dispatcher;
    friend class ServerImpl;
public:
    enum Result
    {
        RefuseRequest = -2,
        RefuseAndClose,
        CreateClient,
        CreateAndRouteRequest,
    };

	enum CloseReason
	{
		PeerClosure =0 ,
		InactiveClient,
		ForceableClosure,
		UnknownFailure,
	};

    ClientFactory(void);
    virtual ~ClientFactory(void);

    /**
    	\param lpContext Used to store any contextual infos that can be provided to you back when the first request is received from the same connection.

    	When a new connection is accepted, you can choose to send an outgoing packet before beginning to receive
    	incoming requests. Also allows you to store a custom structure so it can be given back to
    	when the first request is received by same connection.
    	If you return NULL, the framework does nothing.
    */
    virtual OutgoingPacket* onNewConnection(ConnectionContext*& lpConnectionContext);

    /**
    	\param key Client identifier.

    	Called when client disconnects from server.
    */
    virtual void onClientDisconnected(LogicalConnection* pClient, CloseReason closeReason);

    /**
    	\param key Client identifier.

    	When the framework detects that an existing client has logged in through another connection,
    	the past connection is closed and the new one is attached the existing Client structure.
    	Furthermore, this function is triggered so you can perform certain logic.
    */
    virtual void onClientReconnected(LogicalConnection* pClient);
    /**
    	\param key Client key.

    	Called after you successful login a Client in OnFirstRequest.
    */
    virtual void onClientConnected(LogicalConnection* pClient);

    /**
    	\param pClient Client structure.

    	Called to delete Client structure. Gives the chance to use a pool of re-usable structures.
    */
    virtual void disposeClient(LogicalConnection* pClient);

    /**
    \param request A reference to the received request packet.
    \param lpContext reference to the context data that you supplied at ::onNewConnection.
    \param lpClient reference address to write your newly allocated Client structure to.
    \param lpPacket used to send a reply when the request is refused.

    	Called for the first request received by an accepted connection.
    	The function behaves like a login function. You may decide to create a new Client or refuse the request.
    */
    virtual int onFirstRequest(IncomingPacket& request, ConnectionContext* pConnectionContext, LogicalConnection*& lpClient, OutgoingPacket*& lpPacket) = 0;


    /**
    	\param clientKey Client identifier.

    	Returns Client structure corresponding to given identifier. Also increment reference counter by one.
    */

    /**
    	Copies
    */
    virtual void CopyLogicalConnection(LogicalConnection* pSrc, LogicalConnection* pDest);

	virtual bool onBeforeClosingIdleClient(LogicalConnection* pClient);

	unsigned int getClientCount();
};

}
#endif // ClientFactory__INCLUDED

