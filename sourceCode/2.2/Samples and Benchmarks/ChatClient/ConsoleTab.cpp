// ConsoleTab.cpp : implementation file
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ConsoleTab.h"

#include "ConnectDlg.h"


// CConsoleTab dialog

IMPLEMENT_DYNAMIC(CConsoleTab, CDialog)

CConsoleTab::CConsoleTab(CWnd* pParent /*=NULL*/)
    : CDialog(CConsoleTab::IDD, pParent)
{

}

CConsoleTab::~CConsoleTab()
{
}

void CConsoleTab::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_consoleEdit);
}


BEGIN_MESSAGE_MAP(CConsoleTab, CDialog)
    ON_BN_CLICKED(IDC_CONNECT, &CConsoleTab::OnBnClickedConnect)
    ON_BN_CLICKED(IDC_LOGOUT, &CConsoleTab::OnBnClickedLogout)
END_MESSAGE_MAP()


// CConsoleTab message handlers

void CConsoleTab::OnBnClickedConnect()
{
    // TODO: Add your control notification handler code here
    switch (theApp.getChatAPI().getStatus())
    {
    case TCPSocket::Disconnected:
    {
        Print(_T("Connecting .."));
        CConnectDlg m_conDlg;
        if (m_conDlg.DoModal()!=IDOK)
        {
            return;
        }
        theApp.getChatAPI().setLoginInfo((char*) CT2CA(m_conDlg.m_Pseudo));
        if (!theApp.getChatAPI().connect(CT2CA(m_conDlg.m_ServerIP), m_conDlg.m_ServerPort))
        {
            Print(_T("Unable to connect."));
            return;
        }
    }
    break;
    case TCPSocket::Connecting:
        Print(_T("Still connecting .."));
        break;
    case TCPSocket::Connected:
        Print(_T("Already connected .."));
        break;
    default:
        break;
    }
}

void CConsoleTab::Print( CString strLog )
{
    strLog+= _T("\n");
    m_consoleEdit.SetSel(-1);
    m_consoleEdit.ReplaceSel(strLog);
}

void CConsoleTab::Print( std::string str )
{
    CString strLog;
    strLog.Format(_T("%S"), str.c_str());
    Print(strLog);
}

void CConsoleTab::Print( CStringA str )
{
    CString strLog(str);
    Print(strLog);
}

void CConsoleTab::OnBnClickedLogout()
{
    // TODO: Add your control notification handler code here
    theApp.getChatAPI().Logout();
}
