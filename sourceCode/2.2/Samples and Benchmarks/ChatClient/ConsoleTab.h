#pragma once
#include "resource.h"
#include "afxwin.h"


// CConsoleTab dialog

class CConsoleTab : public CDialog
{
    DECLARE_DYNAMIC(CConsoleTab)

public:
    CConsoleTab(CWnd* pParent = NULL);   // standard constructor
    virtual ~CConsoleTab();

// Dialog Data
    enum { IDD = IDD_CONSOLETAB };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    CEdit m_consoleEdit;
    afx_msg void OnBnClickedConnect();

    void Print(CString strLog);
    void Print(CStringA str);
    void Print(std::string str);

    afx_msg void OnBnClickedLogout();

    //
    void DeliverConnectionResult(bool bSuccess)
    {
        Print( bSuccess ? _T("Connection ok") : _T("Connection failed"));
    }
    void DeliverConnectionClosed(bool bPeer)
    {
        Print(_T("Connection closed"));
    }

    void DeliverLoginResponse(bool bAccepted, std::string msg)
    {
        if(bAccepted)
            Print( _T("You are logged"));
        else
            Print(_T("Login failed"));
    }
};
