#include "stdafx.h"
#include "clientfactory.h"
#include "client.h"

[!output CLIENT_FACTORY_CLASS_NAME]::[!output CLIENT_FACTORY_CLASS_NAME]()
{
	//
}

[!output CLIENT_FACTORY_CLASS_NAME]::~[!output CLIENT_FACTORY_CLASS_NAME]()
{
	//
}

[!if CHALLENGE_CONNECTIONS]
class ChallengeContext : public ConnectionContext
{
public:
	ChallengeContext(int seed)
	{
		this->seed = seed;
	}
	~ChallengeContext()
	{
		//
	}
	static int getValidResponse(int seed)
	{
		return seed + 1;
	}
	int getChallenge()
	{
		return seed;
	}
public:
	int seed;
};

OutgoingPacket* [!output CLIENT_FACTORY_CLASS_NAME]::onNewConnection( ConnectionContext*& lpConnectionContext )
{
	int iChallenge = rand()%100;

	lpConnectionContext = new ChallengeContext(iChallenge);

	LoginChallengeResponse* pResponse = new LoginChallengeResponse();
	pResponse->set_challenge(iChallenge);

	return reinterpret_cast<OutgoingPacket*> (pResponse);
}
[!endif]

int [!output CLIENT_FACTORY_CLASS_NAME]::onFirstRequest( IncomingPacket& request, ConnectionContext* pConnectionContext, LogicalConnection*& lpClient, OutgoingPacket*& lpPacket )
{
	LoginRequest& loginMessage = reinterpret_cast<LoginRequest&> (request);

	[!if CHALLENGE_CONNECTIONS]
	int challengeResponse = loginMessage.challengeresponse();
	ChallengeContext* pCxt = (ChallengeContext*) pConnectionContext;

	if (challengeResponse != ChallengeContext::getValidResponse(pCxt->getChallenge()))
	{
		return RefuseAndClose;
	}
	[!endif]
	
	MyClient* pClient = new MyClient(loginMessage.pseudo().c_str());
	lpClient = pClient;

	return ClientFactory::CreateClient;
}

[!if OVERRIDE_CLIENTFACTORY]
void [!output CLIENT_FACTORY_CLASS_NAME]::onClientDisconnected( LogicalConnection* pClient, CloseReason closeReason )
{
	//
}

void [!output CLIENT_FACTORY_CLASS_NAME]::onClientConnected( LogicalConnection* pClient )
{
	//
}

void [!output CLIENT_FACTORY_CLASS_NAME]::onClientReconnected( LogicalConnection* pClient )
{
	//
}

bool [!output CLIENT_FACTORY_CLASS_NAME]::onBeforeClosingIdleClient( LogicalConnection* pClient )
{
	return false;
}

void [!output CLIENT_FACTORY_CLASS_NAME]::CopyLogicalConnection( LogicalConnection* pSrc, LogicalConnection* pDest )
{
	//
}
[!endif]
