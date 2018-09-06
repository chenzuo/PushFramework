// ChatRobots.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Bot.h"


typedef std::vector<Bot*> botVectT;

botVectT botVect;


bool getConfigFile(std::string& path);
void readConfig(std::string& strIniFile, Options_t& options);
void startBot();

Options_t globalOptions;


int main(int argc, char* argv[])
{
	for (int i=0;i<1024;i++)
		fixedMessage += "a";

    TCPSocket::initializeWinsock();

    std::string strIniFile;
    if (!getConfigFile(strIniFile))
    {
        cout << "Unable to find conf file" << endl;
        return false;
    }
    readConfig(strIniFile, globalOptions);

    //
    cout << "Simulator started.." << std::endl;



    //Connect at once phase :
    for (int i = 0; i < globalOptions.nConnectAtOnce; i++)
    {
        startBot();
    }

    //Staged phase :
    int stagedPhaseDurationCounter = 0;
    while (stagedPhaseDurationCounter < globalOptions.stagedPhaseDuration)
    {
        sleep(1000);
        for (int i = 0; i < globalOptions.stagedConnectionPerSecond; i++)
        {
            startBot();
        }
        stagedPhaseDurationCounter++;
        //
    }

    cout << "Ready to quit : tape q";
    while (true)
    {
        char ch;

        cin >> ch;

        if (ch == 'q')
        {
            break;
        }
    }

    for (botVectT::iterator it = botVect.begin();
            it != botVect.end(); it++)
    {
        Bot* pBot = *it;

        //
        pBot->disconnect(false);
        delete pBot;
    }

    return 0;
}

void startBot()
{
    static int i = 0;
    i++;
    //forming unique pseudo :
    std::stringstream ss;
    ss << std::noskipws;
    ss << "Bot ";
    ss << i;
    std::string botPseudo = ss.str();

    Bot* pBot = new Bot(globalOptions);
    pBot->setLoginInfo(botPseudo);

    cout << "Connecting bot " << botPseudo.c_str() << std::endl;

    if (!pBot->connect(globalOptions.serverIP.c_str(), globalOptions.port))
    {
        cout << "Unable to connect bot " << i << std::endl;
        delete pBot;
        return;
    }
    else
        botVect.push_back(pBot);
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


    options.serverIP = reader.Get("server", "hostIp", "127.0.0.1");
    options.port = reader.GetInteger("server", "port", 2011);

    options.stayDuration = reader.GetInteger("connection", "stayDuration", 40);
    options.stagedPhaseDuration = reader.GetInteger("connection", "stagedPhaseDuration", 120);
    options.stagedConnectionPerSecond = reader.GetInteger("connection", "stagedConnectionPerSecond", 1);
    options.nConnectAtOnce = reader.GetInteger("connection", "connectAtOnce", 100);

    options.directChatDuration = reader.GetInteger("behavior", "directChat", 1);
    options.directChatBulks = reader.GetInteger("behavior", "directChatBulks", 10);
    options.replyDirectProb = reader.GetInteger("behavior", "replyToDirect", 0);
    options.sendRoomChatDuration = reader.GetInteger("behavior", "roomChat", -1);
    options.joinRoomDuration = reader.GetInteger("behavior", "joinRoom", -1);
}



#ifdef Plateform_Linux
bool getConfigFile(std::string& path)
{

    char linkname[64]; /* /proc/<pid>/exe */
    pid_t pid;

    /* Get our PID and build the name of the link in /proc */
    pid = getpid();
    snprintf(linkname, sizeof (linkname), "/proc/%i/exe", pid);

    char buf[512 + 1];
    /* Now read the symbolic link */
    int ret = readlink(linkname, buf, sizeof (buf));
    /* Ensure proper NUL termination */
    buf[ret] = 0;

    for (int i = ret; i >= 0; i--)
    {
        if (buf[i] == '/')
        {
            buf[i] = 0;
            break;
        }
    }

    std::string strModuleDirectory(buf);
    path = strModuleDirectory + "/ChatRobots.ini";

    return true;

}
#endif


#ifdef Plateform_Windows
bool getConfigFile( std::string& path )
{
    char szPath[MAX_PATH];
    if( !GetModuleFileNameA( NULL, szPath, MAX_PATH ) )
        return 1;
    std::string strPath(szPath);
    std::string::size_type pos1 = strPath.rfind('\\');
    std::string::size_type pos2 = strPath.rfind('/');
    std::string::size_type pos = (pos1==-1) ? pos2 : (pos2==-1) ? pos1 : (max(pos1, pos2));
    szPath[pos] = '\0';
    std::string strModuleDirectory(szPath);

    path = strModuleDirectory + "\\ChatRobots.ini";

    return true;
}
#endif


