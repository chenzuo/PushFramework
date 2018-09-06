// FlexLicenseServer.cpp : Defines the entry point for the console application.
//

#include "StdAfx.h"

#include "FlexClientFactory.h"
#include "LicenseProtocol.h"

#include "INIReader.h"

typedef struct Options_t
{
    int port;
} Options_t;


std::string license = "<cross-domain-policy><allow-access-from domain=\"*\" to-ports=\"*\" secure=\"false\"/></cross-domain-policy>";

void readConfig(std::string& strIniFile, Options_t& options);
bool getConfigFile(std::string& path);

Options_t globalOptions;

class MyServer : public Server, public SystemService
{
public:

    MyServer():
        SystemService(L"FlexPolicyServer")
    {
        //
    }

    ~MyServer()
    {
        //
    }
protected:
    virtual void OnStart()
    {
        Server::start(false);
    }
    virtual void OnStop()
    {
        Server::stop();
    }

};

MyServer server;

LicenseProtocol protocol;
FlexClientFactory factory(license);

int main(int argc, char* argv[])
{
    std::string strIniFile;
    if (!getConfigFile(strIniFile))
    {
        return -1;
    }
    readConfig(strIniFile, globalOptions);
    server.setClientFactory(&factory);


	ListenerOptions lOptions;
	lOptions.pProtocol = &protocol;
    server.createListener(globalOptions.port, &lOptions);

	options.nStreamers = 0;

    bool runInteractively = true;
    /*if (argc == 2)
    {
        char param = argv[1][0];
        if (param == 'i' || param == 'I')
        {
            //Install service into SCM :
            server.Install(L"Allows Dashboards to connect to Push Framework servers by servicing them a policy file");
            return -1;
        }
        if (param == 'u' || param == 'U')
        {
            server.UnInstall();
            return -1;
        }
        if (param == 'm' || param == 'M')
        {
            runInteractively = true;
        }
    }*/

    if (runInteractively)
    {
        server.start(true);

        cout << "You are starting the server in interactive mode" << std::endl;
        cout << "Press q or Q to stop the server." << std::endl;

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
    else
    {
        server.Run();
    }
}
void readConfig(std::string& strIniFile, Options_t& options)
{
    INIReader reader(strIniFile.c_str());

    if (reader.ParseError() < 0)
    {
        std::cout << "Could not load ini file " << strIniFile << endl;
        return;
    }

    options.port = reader.GetInteger("server", "port", 10010);
    cout << "port is " << options.port << endl;
}
bool getConfigFile( std::string& path )
{
    char modulePath[260];
    Server::getPath(modulePath, 260);

    path = modulePath;
    path += "/FlexLicenseServer.ini";

    cout << "the path is : " << path << endl;
    return true;
}

