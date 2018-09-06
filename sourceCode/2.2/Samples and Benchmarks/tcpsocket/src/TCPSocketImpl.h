#pragma once


class TCPSocket;
class ResponseHandler;

class TCPSocketImpl
{
public:
    TCPSocketImpl(TCPSocket* pFacade);
    ~TCPSocketImpl(void);

    int getStatus();

    bool connect(const char* hostAddress, unsigned int uPort);
    void registerHandler(unsigned int requestId, ResponseHandler* pHandler);
    void setProtocol(PushFramework::Protocol* pProtocol);

    PushFramework::Protocol* getProtocol();
    int sendRequest(PushFramework::OutgoingPacket* pPacket);
    void disconnect(bool waitForSend);
    void dispatchResponse(unsigned int requestId, PushFramework::IncomingPacket& packet);
    const char* explainLastError();
private:
    TCPSocket* pFacade;

    int status;

    std::string strIP;
    unsigned int uPort;

    SOCKET hSocket;

    HANDLE hThread;
    HANDLE hKillEvent;
  
    WSAEVENT hSocketEvent;

    PushFramework::DataBuffer oBuffer;
    PushFramework::DataBuffer inBuffer;

    PushFramework::Protocol* pProtocol;


    typedef std::map<unsigned int, ResponseHandler*> handlerMapT;
    handlerMapT handlerMap;

    CRITICAL_SECTION cs;
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
};
