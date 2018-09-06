/********************************************************************
        File :			Server.h
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
#ifndef Server__INCLUDED
#define Server__INCLUDED

#pragma once

#include "PushFramework.h"

namespace PushFramework
{

class ServerImpl;
class Protocol;
class ClientFactory;
class Service;
class BroadcastManager;
class OutgoingPacket;
struct ListenerOptions;

/*!
    A Server object provides member functions for initializing your server application and for running it.
    Each application that uses Push Framework classes can only contain one object derived from Server.
    Declare your server object at the global level. When you instantiate your server object,
    call the available initialization members such as ::setProtocol, ::setClientFactory etc before you call ::start.
*/
class PUSHFRAMEWORK_API Server
{
public:
    /** @name TORs **/
    //@{
    Server();
    virtual ~Server(void);
    //@}

    /**  @name Configuration  **/
    //@{
    /**
    \param pClientFactory pointer to a ClientFactory object. The object should remain valid till you call Server::stop.

    A call to setClientFactory is necessary before calling Server::start.
     */
    void setClientFactory(ClientFactory* pClientFactory, bool bManageDisposal = false);
    /**
    \param port The port number to listen to. If port is used by another application, ::start will fail.
    \param pOptions Optional options on how to deal with clients connected to that port.

    Push Framework creates a dedicated thread to listen for all incoming connection on the port specified. The pOptions
    is very useful when you want to handle clients that support different communication protocol. If pOptions is NULL
    the Protocol instance supplied by ::setProtocol will be used.
     */
    bool createListener(int port, ListenerOptions* pOptions = NULL);
 

    /**
    \param ipStart Ip value
    \param ipStop Ip value

    Specify a range of ip addresses to be blocked.
     */
    void addBlockedIPRange(const char* ipStart, const char* ipStop);
    /**
    \param ipStart Ip value
    \param ipStop Ip value

    Specify a range of ip addresses to be allowed.
     */
    void addPermitIPRange(const char* ipStart, const char* ipStop);
    
    /**
    \param serviceId Service id also called the request id.
    \param pService reference to the Service instance to be registered.
    \param serviceName display name.

    Supplies a Service instance address to be invoked for incoming requests identified as belonging the same service id value.
     */
    void registerService(unsigned int serviceId, Service* pService, const char* serviceName, bool bManageDisposal = false);
    /**
    \param serverName Text value.

    Sets your server infos. The value is displayed by the remote Dashboard after the "info" command.
     */
    void setServerInfos(const char* serverName);
    /**
    \param uLoginExpireDuration Value in seconds. The internal default value is 15 seconds.

    If a a new connection is not logged within the specified maximum duration, the library will automatically
    shuts it down.
     */
    //@}

    /** @name Profiling and remote control **/
    //@{
    /**
    \param command a null terminating string containing the received user command.

    An 256-length buffer. Write a null terminating string to this buffer and return the value of true so the framework sends it as a reply.
     */
    virtual bool handleMonitorRequest(const char* command, char* lpOut);
    //@}

    /** @name Start and stop **/
    //@{
    /**
    \param startInSeparateThread if false then the call is blocking.

    Runs the server. The call is blocking if startInSeparateThread is false.
    The method initializes all needed data and launches all necessary threads (example : worker threads, listening threads, ..).
    The server is then ready to accept remote connections and service their requests.*/
    void start(bool startInSeparateThread = false);
    /**
    Stops the server. Your application is expected to exit after this call.
    You can't call start after stop.*/
    void stop();
    /**
    Pauses the server. This only affects the listening process.
    The server continue to service existing clients till they disconnect.
    It only stops from accepting new connections. Also continues to service remote Dashboards.*/
    void pause();
    /**
    Resumes server. Server is able to accept new connections.
     */
    void resume();
    //@}


    /*********** @name Others *************/
    //@{
    /**
    Returns a reference to the ClientFactory previously gathered by the call to ::setClientFactory.
     */
    ClientFactory* getClientFactory();

	virtual void* workerThreadBegin();
    virtual void workerThreadEnd(void*);
    virtual void performPeriodicTasks();;
    virtual void OnStarted();;
    static void getPath(char* path, int len);
private:
    ServerImpl* pImpl;
};
}

#endif // Server__INCLUDED
