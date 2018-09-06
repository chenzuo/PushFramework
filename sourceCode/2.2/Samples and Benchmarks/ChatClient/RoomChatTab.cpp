// RoomChatTab.cpp : implementation file
//

#include "stdafx.h"
#include "ChatClient.h"
#include "RoomChatTab.h"


// CRoomChatTab dialog

IMPLEMENT_DYNAMIC(CRoomChatTab, CDialog)

CRoomChatTab::CRoomChatTab(CWnd* pParent /*=NULL*/)
    : CDialog(CRoomChatTab::IDD, pParent),
      CChatInboxManager(m_chatHistoryEdit, m_roomsComboBox)
{

}

CRoomChatTab::~CRoomChatTab()
{
}

void CRoomChatTab::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, m_roomsComboBox);
    DDX_Control(pDX, IDC_EDIT1, m_chatHistoryEdit);
    DDX_Control(pDX, IDC_EDIT2, m_chatInputEdit);
}


BEGIN_MESSAGE_MAP(CRoomChatTab, CDialog)
    ON_BN_CLICKED(IDC_JOIN_ROOM, &CRoomChatTab::OnBnClickedJoinRoom)
    ON_CBN_SELCHANGE(IDC_COMBO1, &CRoomChatTab::OnCbnSelchangeCombo)
    ON_BN_CLICKED(IDC_SEND, &CRoomChatTab::OnBnClickedSend)
END_MESSAGE_MAP()


// CRoomChatTab message handlers

void CRoomChatTab::OnBnClickedJoinRoom()
{
    // TODO: Add your control notification handler code here
    std::string room = CChatInboxManager::getCurView();
    if (room == joinedRoom)
    {
        return;
    }
    //
    theApp.getChatAPI().JoinRoom(room);
}

void CRoomChatTab::DeliverRooms( std::vector<std::string>& roomsList )
{
    for (int i=0; i<roomsList.size(); i++)
    {
        CChatInboxManager::AddView(roomsList.at(i));
    }
}

void CRoomChatTab::DeliverJoinRoom( std::string roomName )
{
    this->joinedRoom = roomName;
}

void CRoomChatTab::DeliverRoomChat( std::string sender, std::string msg, std::string room )
{
    std::string printMsg = "[" + sender + "] "+ msg;
    CChatInboxManager::DeliverChatToView(printMsg, room);
}

void CRoomChatTab::OnCbnSelchangeCombo()
{
    // TODO: Add your control notification handler code here
    CChatInboxManager::OnViewChanged();
    if (CChatInboxManager::getCurView() == "" || CChatInboxManager::getCurView()==joinedRoom)
    {
        GetDlgItem(IDC_JOIN_ROOM)->EnableWindow(FALSE);
    }
    else
        GetDlgItem(IDC_JOIN_ROOM)->EnableWindow(TRUE);
}

void CRoomChatTab::OnBnClickedSend()
{
    CString strText;
    m_chatInputEdit.GetWindowText(strText);
    std::string msg = (char*) CT2CA(strText);
    //
    theApp.getChatAPI().SendRoomChat(msg, CChatInboxManager::getCurView());
    //
    m_chatInputEdit.SetSel(0, -1);
    m_chatInputEdit.ReplaceSel(_T(""));
    //
}
