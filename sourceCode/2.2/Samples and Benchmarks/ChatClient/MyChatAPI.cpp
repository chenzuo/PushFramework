#include "StdAfx.h"
#include "MyChatAPI.h"

#include "ChatClient.h"
#include "ChatClientDlg.h"
#include "ConsoleTab.h"
#include "DirectChatTab.h"
#include "RoomChatTab.h"

#include "ConnectDlg.h"

UINT UWM_MESSAGE = ::RegisterWindowMessage(UWM_MESSAGE_MSG);

CMyChatAPI::CMyChatAPI(void)
    :ChatAPI(true)
{
}

CMyChatAPI::~CMyChatAPI(void)
{
}

void CMyChatAPI::OnDirectChat( std::string sender, std::string msg )
{
    theApp.getWindow()->getDirectChatTab().DeliverDirectChat(sender, msg);

}

void CMyChatAPI::OnJoinRoom( std::string roomName )
{
    theApp.getWindow()->getRoomChatTab().DeliverJoinRoom(roomName);
}

void CMyChatAPI::OnParticipantIn( std::string pseudo )
{
    theApp.getWindow()->getDirectChatTab().DeliverParticipantIn(pseudo);
}

void CMyChatAPI::OnParticipantOut( std::string pseudo )
{
    theApp.getWindow()->getDirectChatTab().DeliverParticipantOut(pseudo);
}

void CMyChatAPI::OnRoomChat( std::string sender, std::string msg, std::string room )
{
    theApp.getWindow()->getRoomChatTab().DeliverRoomChat(sender, msg, room);
}

void CMyChatAPI::OnRooms( std::vector<std::string>& roomsList )
{
    theApp.getWindow()->getRoomChatTab().DeliverRooms(roomsList);
}

void CMyChatAPI::PostTCPEvent( TCPSocketEvent* pEvent )
{
	PostMessage(theApp.getWindow()->m_hWnd,UWM_MESSAGE,(WPARAM)  pEvent,(LPARAM) 0);
}

void CMyChatAPI::onConnected( )
{
    theApp.getWindow()->getConsoleTab().DeliverConnectionResult(true);
}

void CMyChatAPI::onConnectionClosed(  )
{
    theApp.getWindow()->getConsoleTab().DeliverConnectionClosed(true);
}

void CMyChatAPI::OnLoginResponse( bool bAccepted, std::string msg )
{
    theApp.getWindow()->getConsoleTab().DeliverLoginResponse(bAccepted, msg);
    if (!bAccepted)
    {
        CConnectDlg m_conDlg;
        if (m_conDlg.DoModal()!=IDOK)
        {
            return;
        }
        theApp.getChatAPI().setLoginInfo((char*) CT2CA(m_conDlg.m_Pseudo));
        theApp.getChatAPI().tryLogin();
    }
}


