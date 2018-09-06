// ChatServer.cpp : Defines the entry point for the console application.
//

#include "StdAfx.h"


#include "DirectChatRequestService.h"
#include "JoinRoomRequestService.h"
#include "LeaveRoomRequestService.h"
#include "RoomChatRequestService.h"
#include "LogoutRequestService.h"

#include "ChatParticipantFactory.h"

class ChatServer : public Server, public SystemService
{
public:
    ChatServer()
        :SystemService(L"chatserver")
    {
        //
    }
    ~ChatServer()
    {
        //
    }
protected:
    virtual void disposeOutgoingPacket(OutgoingPacket* pPacket)
    {
        delete pPacket;
    }
    virtual void OnStart()
    {
        Server::start(false);
    };
    virtual void OnStop()
    {
        Server::stop();
    }
    virtual bool OnPause()
    {
        return false;
    }
    virtual bool OnResume()
    {
        return false;
    }
    virtual void OnStarted()
    {
        RoomsResponse* pRoomsPacket = new RoomsResponse;
        pRoomsPacket->addRoom("room1");
        pRoomsPacket->addRoom("room2");
        pRoomsPacket->addRoom("room3");
        broadcastManager.PushPacket(pRoomsPacket, "signals", "", 0);
    }
};



typedef struct Options_t
{
    int port;
    int monitorPort;
    std::string monitorPwd;
    int sampleRate;
    bool disableRooms;
} Options_t;

Options_t globalOptions;

void readConfig(std::string& strIniFile, Options_t& options);
bool getConfigFile( std::string& path );


int main(int argc, char* argv[])
{
    std::string strIniFile;
    if (!getConfigFile(strIniFile))
    {
        cout << "Unable to find conf file" << endl;
        return -1;
    }
    readConfig(strIniFile, globalOptions);


    ChatServer server;

    server.setServerInfos("Chat Server by Ahmed Charfeddine");



    server.registerService(DirectChatRequestID, new DirectChatRequestService, "directChat", true);
    server.registerService(JoinRoomRequestID, new JoinRoomRequestService, "joinRoom", true);
    server.registerService(LeaveRoomRequestID, new LeaveRoomRequestService, "leaveRoom", true);
    server.registerService(RoomChatRequestID, new RoomChatRequestService, "roomChat", true);
    server.registerService(LogoutRequestID, new LogoutRequestService, "logout", true);

    server.setClientFactory(new ChatParticipantFactory, true);

	options.uLoginExpireDuration = 60;
	options.uMaxClientIdleTime = 120;
	options.nMaxConnections = 10000;

    ListenerOptions lOptions;
	lOptions.pProtocol = new ChatServerProtocol;
    server.createListener(globalOptions.port, &lOptions);


    //Broadcast channels :

    if (!globalOptions.disableRooms)
    {
		QueueOptions options;
		options.maxPackets = 1000;
		options.requireRegistration = false;
		options.priority = 10;
		options.packetsQuota = 20;
        broadcastManager.CreateQueue("participants", options);
		
		options.maxPackets = 20;
		options.priority = 7;
		options.packetsQuota = 1;
        broadcastManager.CreateQueue("signals", options);

		options.requireRegistration = true;
		options.priority = 5;
		options.packetsQuota = 3;
        broadcastManager.CreateQueue("room1", options);
        broadcastManager.CreateQueue("room2", options);
        broadcastManager.CreateQueue("room3", options);
    }



    try
    {
        server.start(true);
    }
    catch (std::exception& e)
    {
        cout << "Failed to start server. Exception : " << e.what() << std::endl;
        return 0;
    }




    while (true)
    {
        char ch;

        cin >> ch;

        if (ch == 'q')
        {
            break;
        }
    }

    server.stop();

    return 0;
}

bool getConfigFile( std::string& path )
{
    char modulePath[260];
    Server::getPath(modulePath, 260);

    path = modulePath;
    path += "/ChatServer.ini";

    return true;
}
#include "INIReader.h"
void readConfig(std::string& strIniFile, Options_t& options)
{
    INIReader reader(strIniFile.c_str());

    if (reader.ParseError() < 0)
    {
        std::cout << "Could not load ini file " << strIniFile << endl;
        return;
    }

    options.port = reader.GetInteger("server", "port", 2011);
    options.monitorPort = reader.GetInteger("server", "monitoringPort", 2012);
    options.monitorPwd = reader.Get("server",  "monitoringPwd", "ahmed");
    options.sampleRate = reader.GetInteger("server",  "sampleRate", 10);
    options.disableRooms = (reader.GetInteger("chat",  "disableRooms", 0) == 1);
}
