#include "StdAfx.h"
#include "FlexClientFactory.h"


FlexClientFactory::FlexClientFactory( std::string strPolicyContent )
{
    this->strPolicyContent = strPolicyContent;
}

FlexClientFactory::~FlexClientFactory( void )
{

}
void FlexClientFactory::onClientConnected( LogicalConnection* pClient )
{
    PolicyResponse response(strPolicyContent);
    pClient->PushPacket(&response);
    Disconnect(pClient, true);
}

int FlexClientFactory::onFirstRequest( IncomingPacket& request, ConnectionContext* lpContext, LogicalConnection*& lpClient, OutgoingPacket*& lpPacket )
{
    static int clientID = 0;
    clientID++;

    char pClientName[256];
    sprintf(pClientName, "client #%d", clientID);

    FlexSandbox* pClient = new FlexSandbox(pClientName);
    lpClient = pClient;

    return ClientFactory::CreateClient;
}
