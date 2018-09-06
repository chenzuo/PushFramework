#pragma once
#include "resource.h"
#include "afxwin.h"


#include "ChatInboxManager.h"
// CDirectChatTab dialog

class CDirectChatTab : public CDialog, public CChatInboxManager
{
    DECLARE_DYNAMIC(CDirectChatTab)

public:
    CDirectChatTab(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDirectChatTab();

// Dialog Data
    enum { IDD = IDD_DIRECTCHATTAB };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    CComboBox m_membersComboBox;
    CEdit m_chatHistory;
    CEdit m_chatInput;
public:
    virtual void DeliverParticipantIn(std::string pseudo);
    virtual void DeliverParticipantOut(std::string pseudo);
    virtual void DeliverDirectChat(std::string sender, std::string msg);
    afx_msg void OnBnClickedSend();
    afx_msg void OnCbnSelchangeCombo();


};
