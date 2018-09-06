#include "StdAfx.h"
#include "TestClient.h"

CTestClient::CTestClient()
{
	registerHandler(LoginResultResponseID, this);
	registerHandler(RoutedMessageResponseID, this);
	registerHandler(GroupMessageResponseID, this);
    registerHandler(EchoResponseID, this);
    registerHandler(BroadcastMessageResponseID, this);
	setProtocol(new TestProtocol());
    isLogged = false;
}

CTestClient::~CTestClient(void)
{
}

int CTestClient::sendRequest( protobuf::Message* pMessage )
{
	OutgoingPacket* pPacket = reinterpret_cast<OutgoingPacket*> (pMessage);
	return TCPSocket::sendRequest(pPacket);
}

void CTestClient::onConnected()
{
	cout << pseudo << ": " << "Connected to server." << endl;
	//Try login
	LoginRequest request;
	request.set_accesskey("alibaba");
	request.set_pseudo(pseudo);
	request.set_claimpseudo(false);

	if (sendRequest(&request) == TCPSocket::ResultOK)
	{
		cout << pseudo << ": " << "Login request successfully sent." << endl;
	}
	else
	{
		cout << pseudo << ": " << "Unable to send login request." << endl;
	}
}

void CTestClient::onConnectionClosed()
{
	cout << pseudo << ": " << "Connection closed with the server." << endl;
    ::SetEvent(hEvent);
}



void CTestClient::ConnectToServer( const char* _pseudo )
{
    hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    pseudo = _pseudo;
    if (!connect("127.0.0.1", 20010))
    {
        cout << pseudo << ": unable to connect." << endl;
        ::SetEvent(hEvent);
    }
}

void CTestClient::handleResponse( IncomingPacket& _packet )
{
    //Re-interpret cast then find child using dynamic cast.
    protobuf::Message* packet = reinterpret_cast<protobuf::Message*> (&_packet);

    LoginResultResponse* pLoginResponse  = dynamic_cast<LoginResultResponse*> (packet);
    if (pLoginResponse)
    {
        //
        if (pLoginResponse->is_accepted())
        {
            cout << pseudo << ": " << "Logged in to server as " << pLoginResponse->pseudo() << endl;
            pseudo = pLoginResponse->pseudo();
            isLogged = true;
        }
        else
        {
            cout << pseudo << ": " << "Login refused."  << endl;
            isLogged = false;
        }
        ::SetEvent(hEvent);
        return;
    }

    EchoResponse* pEchoResponse = dynamic_cast<EchoResponse*> (packet);
    if (pEchoResponse)
    {
        cout << pseudo <<": Received echo message: " << pEchoResponse->msg() << endl;
        return;
    }

    RoutedMessageResponse* pRoutedMsgResponse = dynamic_cast<RoutedMessageResponse*> (packet);
    if (pRoutedMsgResponse)
    {
        cout << pseudo <<": Received direct message from: "<< pRoutedMsgResponse->sender() << " saying: " << pRoutedMsgResponse->msg() << endl;
        return;
    }

    GroupMessageResponse* pGroupMsgResponse = dynamic_cast<GroupMessageResponse*> (packet);
    if (pGroupMsgResponse)
    {
        cout << pseudo <<": "<< pGroupMsgResponse->sender() << " broadcasted: " << pGroupMsgResponse->msg() << endl;
        return;
    }
    
    BroadcastMessageResponse* pBroadcastResponse = dynamic_cast<BroadcastMessageResponse*> (packet);
    if (pBroadcastResponse)
    {
        QueueToMessageCountMapT::iterator it = QueueToMessageCountMap.find(pBroadcastResponse->queuename());
        QueueReceiveStats* pStats;
        if (it == QueueToMessageCountMap.end())
        {
            pStats = new QueueReceiveStats;
            QueueToMessageCountMap[pBroadcastResponse->queuename()] = pStats;
        }
        else
            pStats = it->second;

        pStats->uCount++;
        if(pStats->uLastReceivedMessageId != 0)
        {
            unsigned int skippedMessages = pBroadcastResponse->messageid() - pStats->uLastReceivedMessageId + 1;
            pStats->uLossCount += skippedMessages;
        }
        pStats->uLastReceivedMessageId = pBroadcastResponse->messageid(); 
        totalReceivedPackets++;
        return;
    }

    cout << "unknown received" << endl;
}

bool CTestClient::WaitForLogin()
{
    WaitForSingleObject(hEvent, 2000);
    return isLogged;
}

void CTestClient::ClearBroadcastStats()
{
    totalReceivedPackets = 0;
    QueueToMessageCountMapT::iterator it = QueueToMessageCountMap.begin();
    while (it!= QueueToMessageCountMap.end())
    {
        delete it->second;
        it++;
    }
    QueueToMessageCountMap.clear();
}

void CTestClient::ReportBroadcastStats()
{
    cout << pseudo <<": Broadcast statistics: Total received: "<< totalReceivedPackets << endl;

    QueueToMessageCountMapT::iterator it = QueueToMessageCountMap.begin();
    while (it!= QueueToMessageCountMap.end())
    {
        QueueReceiveStats* pQueueStats = it->second;
        unsigned int receivedPercentage = pQueueStats->uCount * 100 / totalReceivedPackets;
        unsigned int lossPercentage = pQueueStats->uLossCount * 100 / (pQueueStats->uCount + pQueueStats->uLossCount);

        cout << "queue:" << it->first << "\tReceived: " << receivedPercentage << "%\t Queue loss: " << lossPercentage << "%" << endl;
        it++;
    }
}
