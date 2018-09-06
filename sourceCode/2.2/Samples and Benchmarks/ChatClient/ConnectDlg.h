#pragma once


// CConnectDlg dialog

class CConnectDlg : public CDialog
{
    DECLARE_DYNAMIC(CConnectDlg)

public:
    CConnectDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CConnectDlg();

// Dialog Data
    enum { IDD = IDD_CONNECTDLG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    CString m_ServerIP;
    UINT m_ServerPort;
    CString m_Pseudo;
};
