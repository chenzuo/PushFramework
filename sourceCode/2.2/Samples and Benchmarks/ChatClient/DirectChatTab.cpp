// DirectChatTab.cpp : implementation file
//

#include "stdafx.h"
#include "ChatClient.h"
#include "DirectChatTab.h"


// CDirectChatTab dialog

IMPLEMENT_DYNAMIC(CDirectChatTab, CDialog)

CDirectChatTab::CDirectChatTab(CWnd* pParent /*=NULL*/)
    : CDialog(CDirectChatTab::IDD, pParent),
      CChatInboxManager(m_chatHistory, m_membersComboBox)
{

}

CDirectChatTab::~CDirectChatTab()
{
}

void CDirectChatTab::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, m_membersComboBox);
    DDX_Control(pDX, IDC_EDIT1, m_chatHistory);
    DDX_Control(pDX, IDC_EDIT2, m_chatInput);
}


BEGIN_MESSAGE_MAP(CDirectChatTab, CDialog)
    ON_BN_CLICKED(IDC_SEND, &CDirectChatTab::OnBnClickedSend)
    ON_CBN_SELCHANGE(IDC_COMBO1, &CDirectChatTab::OnCbnSelchangeCombo)
END_MESSAGE_MAP()


// CDirectChatTab message handlers

void CDirectChatTab::OnBnClickedSend()
{
    // TODO: Add your control notification handler code here
    CString strText;
    m_chatInput.GetWindowText(strText);
    std::string msg = (char*) CT2CA(strText);
    //
    theApp.getChatAPI().SendDirectChat(CChatInboxManager::getCurView(), msg);
    //
    m_chatInput.SetSel(0, -1);
    m_chatInput.ReplaceSel(_T(""));
    //

    std::string printMsg = "[You] " + msg;
    CChatInboxManager::DeliverChatToView(printMsg);

}

void CDirectChatTab::OnCbnSelchangeCombo()
{
    // TODO: Add your control notification handler code here

    CChatInboxManager::OnViewChanged();

}


void CDirectChatTab::DeliverDirectChat( std::string sender, std::string msg )
{
    std::string printMsg = "[" + sender + "] " + msg;
    CChatInboxManager::DeliverChatToView(printMsg, sender);
}

void CDirectChatTab::DeliverParticipantIn( std::string pseudo )
{
    CChatInboxManager::AddView(pseudo);
}

void CDirectChatTab::DeliverParticipantOut( std::string pseudo )
{
    std::string printMsg = "[Server] " + pseudo + " has disconnected";
    CChatInboxManager::DeliverChatToView(printMsg, pseudo);
}
