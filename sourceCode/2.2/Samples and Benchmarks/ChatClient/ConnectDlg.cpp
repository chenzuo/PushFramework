// ConnectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ConnectDlg.h"


// CConnectDlg dialog

IMPLEMENT_DYNAMIC(CConnectDlg, CDialog)

CConnectDlg::CConnectDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CConnectDlg::IDD, pParent)
    , m_ServerIP(_T("127.0.0.1"))
    , m_ServerPort(20011)
    , m_Pseudo(_T("ahmed"))
{

}

CConnectDlg::~CConnectDlg()
{
}

void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, m_ServerIP);
    DDX_Text(pDX, IDC_EDIT2, m_ServerPort);
    DDX_Text(pDX, IDC_EDIT3, m_Pseudo);
}


BEGIN_MESSAGE_MAP(CConnectDlg, CDialog)
END_MESSAGE_MAP()


// CConnectDlg message handlers
