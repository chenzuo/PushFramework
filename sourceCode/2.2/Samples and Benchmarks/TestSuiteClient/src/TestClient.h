#pragma once
#include <wtypes.h>

struct QueueReceiveStats
{
    unsigned int uCount;
    unsigned int uLastReceivedMessageId;
    unsigned int uLossCount;
    QueueReceiveStats()
    {
        uCount = 0;
        uLastReceivedMessageId = 0;
        uLossCount = 0;
    }
};
class CTestClient : public TCPSocket, public ResponseHandler
{
public:
	CTestClient();
	~CTestClient(void);
    void ConnectToServer(const char* _pseudo);
    bool WaitForLogin();
protected:
	virtual void handleResponse(IncomingPacket& _packet);
	virtual void onConnected();
	virtual void onConnectionClosed();

public:
	int sendRequest( protobuf::Message* pMessage );
    void ClearBroadcastStats();
    void ReportBroadcastStats();

private:
	string pseudo;
	bool isLogged;
    HANDLE hEvent;

    typedef map<string, QueueReceiveStats*> QueueToMessageCountMapT;
    QueueToMessageCountMapT QueueToMessageCountMap;
    unsigned int totalReceivedPackets;

};
