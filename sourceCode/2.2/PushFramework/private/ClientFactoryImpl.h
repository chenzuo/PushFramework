/********************************************************************
	File :			ClientFactoryImpl.h
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
#ifndef ClientFactoryImpl__INCLUDED
#define ClientFactoryImpl__INCLUDED

#pragma once

namespace PushFramework
{

class ClientFactory;
class LogicalConnection;
class ServerImpl;
class Server;
class ServerImpl;

class ClientFactoryImpl
{
public:
    ClientFactoryImpl();
    ~ClientFactoryImpl(void);
    LogicalConnection* findLogicalConnection(const char* key);
    LogicalConnection* addLogicalConnection(LogicalConnection* pClient);
    bool disconnect(LogicalConnection* pLogicalConnection, bool waitForPendingPackets, int closeReason);

	void disconnectIntern( LogicalConnection* pLogicalConnection, bool waitForPendingPackets, int closeReason );

	void silentDisconnect(LogicalConnection* pLogicalConnection);
    void returnClient(LogicalConnection* pClient);
    unsigned int getClientCount();
	void scrutinize();

private:
    bool removeIfExisting(LogicalConnection* pLogicalConnection);
    Server* getServer();

private:
    typedef std::map<std::string, LogicalConnection*> clientMapT;
    clientMapT clientMap;
    CRITICAL_SECTION cs;
    clientMapT::iterator curIt;
    unsigned int nClientsCount;
    //
};
extern ClientFactoryImpl clientFactoryImpl;
}

#endif // ClientFactoryImpl__INCLUDED
