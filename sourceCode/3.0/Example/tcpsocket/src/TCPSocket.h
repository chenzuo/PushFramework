#pragma once

#include "Symbols.h"


class TCPSocketImpl;
class ResponseHandler;

struct TCPSocketEvent;
struct ReceivedDataEvent;


namespace ProtocolFramework
{
class Protocol;
class AbstractMessage;
}



class TCPSOCKET_API TCPSocket
{
    friend class TCPSocketImpl;
public:
    enum
    {
        Disconnected = 1,
        Connecting,
        Connected,
        WaitingToClose
    };
	enum
	{
		ResultOK = 0,
		ResultTryAgain,
		ResultFailed,
	};

    TCPSocket(bool relayToUserThread = false);
    ~TCPSocket();

    static bool initializeWinsock();

    bool connect(const char* hostAddress, unsigned int uPort, string& strError);
    void registerHandler(unsigned int requestId, ResponseHandler* pHandler);
    bool initialize(ProtocolFramework::Protocol* pProtocol, ProtocolFramework::MessageFactory* messageFactory);
    int sendRequest(ProtocolFramework::OutgoingPacket* pPacket);
    int getStatus();
    void disconnect(bool waitForSend = true );
    virtual void OnReadyToSend();
    const char* explainLastError();
	time_t getLastSentDataTime();

protected:
    virtual void onConnected() = 0;
    virtual void onConnectionClosed() = 0;
    virtual void onPerformAutomatedJob();
	virtual void onReadyToSendRequests();
  
public:
    void ProcessReturnedEvent(TCPSocketEvent* pEvent);
    virtual void PostTCPEvent(TCPSocketEvent* pEvent);
    bool isRelayTCPEvents() const;

private:
    TCPSocketImpl* pImpl;
    bool relayTCPEvents;
};