#pragma once


class TCPSocket;
class ResponseHandler;

class TCPSocketImpl : public Connection
{
public:
    TCPSocketImpl(TCPSocket* pFacade);
    ~TCPSocketImpl(void);

	bool initialize(ProtocolFramework::Protocol* pProtocol, ProtocolFramework::MessageFactory* messageFactory);

    int getStatus();

    bool connect(const char* hostAddress, unsigned int uPort, string& strError);
    void registerHandler(unsigned int requestId, ResponseHandler* pHandler);

    int sendRequest(ProtocolFramework::OutgoingPacket* pPacket);
	int sendBufferBytesRequest(Buffer& protocolBytes, Protocol* pProtocol);
    void disconnect(bool waitForSend);
    void dispatchResponse(unsigned int requestId, ProtocolFramework::IncomingPacket& packet);
    const char* explainLastError();

	void LogStatistics();

	unsigned int calculateMaxBufferSizePerMessage();
private:
    TCPSocket* pFacade;

    int status;

    std::string strIP;
    unsigned int uPort;

    SOCKET hSocket;

    HANDLE hThread;
    HANDLE hKillEvent;
  
    WSAEVENT hSocketEvent;

    ProtocolFramework::Buffer oBuffer;

    ProtocolFramework::Protocol* pProtocol;
	ProtocolFramework::MessageFactory* messageFactory;

    typedef std::map<unsigned int, ResponseHandler*> handlerMapT;
    handlerMapT handlerMap;

    CRITICAL_SECTION cs;

	ProtocolFramework::ProtocolContext* pContext;

	ProtocolManager theProtocolManager;

private:

    static unsigned __stdcall networkJobsThreadProc(LPVOID lParam);
    void doNetworkJobs();

    HANDLE CreatePeriodicTimer();

    bool OnRead();
    bool OnWrite();
    bool OnConnect();
    bool OnClose();

    bool bSendInProgress;

    bool WriteBytes();

    bool stopClient;

	std::string getLastErrorStdStr();

	bool ReadReceivedBytes(Buffer& incomingBytes);

	//CStats m_stats;

public:

	time_t lastTimeDataIsSent;

protected:
	virtual Protocol* getProtocol();
	virtual MessageFactory& getMessageFactory();
	virtual void InitializeConnection();
};
