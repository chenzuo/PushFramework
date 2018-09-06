/********************************************************************
	File :			ServerImpl.h
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
#ifndef ServerImpl__INCLUDED
#define ServerImpl__INCLUDED

#pragma once




namespace PushFramework
{

class Protocol;
class OutgoingPacket;
class ClientFactory;
class Service;
class BroadcastManager;
class MonitorProtocol;
class Demultiplexor;
class Dispatcher;
class ServerStats;
class ChannelFactory;
class IOQueue;
class BroadcastManagerImpl;
class ClientFactoryImpl;
class Acceptor;
class Server;
class GarbageCollector;
struct Version;
struct ListenerOptions;

class ServerImpl
{
public:
    ServerImpl(Server* pFacade);
    ~ServerImpl(void);

    void setServeInfos(const char* serverInfos);
    string getServerInfos();
    void setClientFactory(ClientFactory* pClientFactory, bool bManageDisposal);
    bool createListener( int port, ListenerOptions* pOptions /*= NULL*/ );

    void registerService(unsigned int serviceId, Service* pService, const char* serviceName, bool bManageDisposal);
    bool start(bool startInSeparateThread);
    void stop();
    void pause();
    void resume();
    ClientFactory* getClientFactory();

    Server* getFacade();

private:
    Server* pFacade;
    string serverInfos;

    // User defined
    ClientFactory* pClientFactory;
	bool bManageClientFactoryDisposal;
    short listeningPort;

#ifdef Plateform_Windows
    HANDLE			m_hEventTimer;	// Used for sleeping during interval period.
    HANDLE			m_hEventAbort;// set by stop function.
    //In case of an asynchronous start :
    HANDLE hThread;
    static DWORD WINAPI threadProc(LPVOID WorkContext);
#else
#ifdef Plateform_Linux
    pthread_cond_t abortCond;// set by stop function.
    //In case of an asynchronous start :
    pthread_t hThread;
    static void* threadProc(void* WorkContext);
#endif
#endif

    unsigned int uGCPeriod;

    void eternal_loop();
private:
    int nSecsGCCount;
    int nSecsPerfObservCount;

    void DoPeriodicJobs();
};


extern ServerImpl *pServerImpl;

}
#endif // ServerImpl__INCLUDED

