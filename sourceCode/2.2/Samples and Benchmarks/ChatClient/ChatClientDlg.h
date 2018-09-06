
// ChatClientDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include "MyTabCtrl.h"


class CConsoleTab;
class CDirectChatTab;
class CRoomChatTab;
// CChatClientDlg dialog
class CChatClientDlg : public CDialog
{
// Construction
public:
    CChatClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
    enum { IDD = IDD_CHATCLIENT_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

protected:
    virtual void OnOK();
public:
    afx_msg void OnClose();

private:
    CMyTabCtrl m_tab;
public:
    CConsoleTab& getConsoleTab();
    CDirectChatTab& getDirectChatTab();
    CRoomChatTab& getRoomChatTab();

    LRESULT OnPostedNetworkEventMessage(WPARAM, LPARAM);
};
