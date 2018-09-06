/********************************************************************
	File :			ServerImpl.cpp
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
#include "ServerImpl.h"

#include "Demultiplexor.h"
#include "Dispatcher.h"
#include "ServerStats.h"

#ifdef Plateform_Windows
#include "IOQueue_Win.h"
#else
#ifdef Plateform_Linux
#include "IOQueue_Linux.h"
#endif
#endif

#include "Acceptor.h"
#include "MonitorAcceptor.h"
#include "../include/BroadcastManager.h"
#include "ChannelFactory.h"
#include "../include/ClientFactory.h"
#include "ClientFactoryImpl.h"
#include "BroadcastManagerImpl.h"
#include "../include/Server.h"
#include "MonitorsBroadcastManager.h"
#include "GarbageCollector.h"
#include "BroadcastStreamerManager.h"

#ifdef Plateform_Windows
#include <mmsystem.h>
#endif

#include "Utilities.h"
#include "../include/ServerOptions.h"


namespace PushFramework
{

ServerImpl *pServerImpl;

void ServerImpl::setClientFactory( ClientFactory* pClientFactory, bool bManageDisposal )
{
    this->pClientFactory = pClientFactory;
	bManageClientFactoryDisposal = bManageDisposal;
}

ClientFactory* ServerImpl::getClientFactory()
{
    return pClientFactory;
}


#ifdef Plateform_Windows
void ServerImpl::eternal_loop()
{
     pFacade->OnStarted();

    //Periodic Timer
    m_hEventTimer = CreateEvent(NULL, TRUE, FALSE, NULL);
    ResetEvent(m_hEventTimer);
    //Abort event. (set by stop function)
    m_hEventAbort = CreateEvent(NULL, TRUE, FALSE, NULL);
    ResetEvent(m_hEventAbort);
    //

    HANDLE			hWaits[2];
    hWaits[0]		= m_hEventTimer;
    hWaits[1]		= m_hEventAbort;


    UINT			sleepTimeMs=1000;//1 second.

    nSecsGCCount=0;
    nSecsPerfObservCount=0;
    //

    while(true)
    {
        MMRESULT result = timeSetEvent(sleepTimeMs, 1,
                                       (LPTIMECALLBACK) m_hEventTimer, 0, TIME_ONESHOT|TIME_CALLBACK_EVENT_SET);
        _ASSERT(result != NULL);

        // Sleep here until the timer interval ends or abort occurs
        if(WaitForMultipleObjects(2, hWaits, FALSE, INFINITE)==0)
        {

            DoPeriodicJobs();
            ResetEvent(m_hEventTimer);
        }
        else
        {
            //m_hEventAbort is set : break from while.
            break;
        }
        //
    }

    CloseHandle(m_hEventAbort);
    CloseHandle(m_hEventTimer);
    //quit blocking.
}

DWORD WINAPI ServerImpl::threadProc( LPVOID WorkContext )
{
    ServerImpl* pMe = reinterpret_cast<ServerImpl*>(WorkContext);
    pMe->eternal_loop();
    return 0;
}
#endif


#ifdef Plateform_Linux
void ServerImpl::eternal_loop()
{


    pFacade->OnStarted();


    int sec = 1;
    struct timespec ts;
    pthread_mutex_t cs;
    pthread_mutex_init(&cs, NULL);
    pthread_mutex_lock(&cs);
    pthread_cond_init(&abortCond, NULL);

    nSecsGCCount = 0;
    nSecsPerfObservCount = 0;

    while (true)
    {
        ::clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += sec;

        int rc = pthread_cond_timedwait(&abortCond, &cs, &ts);
        if (rc == ETIMEDOUT)
        {

            DoPeriodicJobs();
        }
        else
        {
            //Server is to die.
            break;
        }

    }


    pthread_mutex_unlock(&cs);

}
void* ServerImpl::threadProc(void* WorkContext)
{
    ServerImpl* pMe = reinterpret_cast<ServerImpl*> (WorkContext);
    pMe->eternal_loop();
    return 0;
}
#endif


bool ServerImpl::start( bool startInSeparateThread )
{
    if(pClientFactory == NULL)
        return false;

    if (!ioQueue.create())
        return false;

    if (!demux.start())
    {
        ioQueue.free();
        return false;
    }

    if (!theAcceptor.startListening())
    {
        demux.stop();
        ioQueue.free();
		return false;
    }

	channelFactory.start();

    if ( options.isMonitorEnabled)
    {
		monitorAcceptor.setListeningPort(options.monitorPort);
		if (!monitorAcceptor.startListening())
		{
			theAcceptor.stopListening();
			demux.stop();
			ioQueue.free();
			return false;
		}
    }

    broadcastStreamerManager.start();

    if (startInSeparateThread)
    {
#ifdef Plateform_Windows
        DWORD  nThreadID;

        hThread = CreateThread(NULL,// Security
                                         0,						// Stack size - use default
                                         threadProc,     		// Thread fn entry point
                                         (void*) this,			// Param for thread
                                         0,						// Init flag
                                         &nThreadID);			// Thread address
#else
#ifdef Plateform_Linux
        pthread_create(&hThread, NULL, threadProc, (void*) this);
#endif
#endif
    }
    else
        eternal_loop();

	return true;
}

void ServerImpl::stop()
{
#ifdef Plateform_Windows
    SetEvent(m_hEventAbort);//stops eternal_loop
    WaitForSingleObject(hThread, INFINITE);
#else
#ifdef Plateform_Linux
    pthread_cond_signal(&abortCond);
#endif
#endif

    if (options.isMonitorEnabled)
        monitorAcceptor.stopListening();

    theAcceptor.stopListening();

    demux.stop();

    channelFactory.stop();

	broadcastStreamerManager.stop();// this stops streaming.

    broadcastManagerImpl.disposeAllPackets();
	monitorBroadcastManager.disposeAllPackets();

    ioQueue.free();

    garbageCollector.activate(true);
}

void ServerImpl::registerService( unsigned int serviceId, Service* pService, const char* serviceName, bool bManageDisposal = false )
{
    dispatcher.registerService(serviceId, pService, serviceName, bManageDisposal);
}

ServerImpl::ServerImpl( Server* pFacade )
{
#ifdef Plateform_Windows
    //Initialize WinSock :
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);
#endif

    this->pFacade = pFacade;

    pClientFactory = NULL;
    listeningPort = 2010;

    uGCPeriod = 10;

    pServerImpl = this;

    bManageClientFactoryDisposal = false;

    nSecsGCCount=0;
    nSecsPerfObservCount=0;
}

ServerImpl::~ServerImpl( void )
{
	if (bManageClientFactoryDisposal){
		delete pClientFactory;
	}
}

Server* ServerImpl::getFacade()
{
    return pFacade;
}

void ServerImpl::setServeInfos( const char* serverInfos )
{
    this->serverInfos = serverInfos;
}

std::string ServerImpl::getServerInfos()
{
    return serverInfos;
}

void ServerImpl::pause()
{
    theAcceptor.stopListening();
}

void ServerImpl::resume()
{
    theAcceptor.startListening();
}

bool ServerImpl::createListener( int port, ListenerOptions* pOptions /*= NULL*/ )
{
	theAcceptor.setListeningPort(port);
	theAcceptor.setOptions(*pOptions);
    return true;
}

void ServerImpl::DoPeriodicJobs()
{
    nSecsGCCount++;
    nSecsPerfObservCount++;

    if(nSecsGCCount==uGCPeriod)
    {
        nSecsGCCount=0;
        garbageCollector.activate();
        channelFactory.scrutinize();
		clientFactoryImpl.scrutinize();
    }

    if(nSecsPerfObservCount==options.samplingRate && options.isProfilingEnabled)
    {
        nSecsPerfObservCount=0;
        OutgoingPacket* pPacket = stats.getPerformancePacket();
        monitorBroadcastManager.pushPacket(pPacket, "stats");
    }

}


}

