
// ChatClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"

#include "ConnectDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CChatClientDlg dialog




CChatClientDlg::CChatClientDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CChatClientDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB1, m_tab);
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialog)
    ON_REGISTERED_MESSAGE(UWM_MESSAGE, OnPostedNetworkEventMessage)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CChatClientDlg message handlers

BOOL CChatClientDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    ShowWindow(SW_SHOW);

    // TODO: Add extra initialization here

    m_tab.InsertItem(0, _T("Console"));
    m_tab.InsertItem(1, _T("Player-to-player chat"));
    m_tab.InsertItem(2, _T("Player-to-group chat"));



    m_tab.Init();


    if (!ChatAPI::initializeWinsock())
    {
        AfxMessageBox(_T("Unable to initialize socket library"));
        return FALSE;
    }





    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChatClientDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}





void CChatClientDlg::OnOK()
{
    // TODO: Add your specialized code here and/or call the base class



    CDialog::OnOK();
}

void CChatClientDlg::OnClose()
{
    // TODO: Add your message handler code here and/or call default

    CDialog::OnClose();
}

CConsoleTab& CChatClientDlg::getConsoleTab()
{
    return (CConsoleTab&) (*m_tab.m_tabPages[0]);
}

CDirectChatTab& CChatClientDlg::getDirectChatTab()
{
    return (CDirectChatTab&) (*m_tab.m_tabPages[1]);
}

CRoomChatTab& CChatClientDlg::getRoomChatTab()
{
    return (CRoomChatTab&) (*m_tab.m_tabPages[2]);
}

LRESULT CChatClientDlg::OnPostedNetworkEventMessage( WPARAM wParam, LPARAM lParam )
{
	TCPSocketEvent* pEvent = reinterpret_cast<TCPSocketEvent*> (wParam);
	theApp.getChatAPI().ProcessReturnedEvent(pEvent);
	 delete pEvent;
	return 0;
}