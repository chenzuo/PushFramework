#pragma once
#include "resource.h"
#include "afxwin.h"

#include "ChatInboxManager.h"


// CRoomChatTab dialog

class CRoomChatTab : public CDialog, public CChatInboxManager
{
    DECLARE_DYNAMIC(CRoomChatTab)

public:
    CRoomChatTab(CWnd* pParent = NULL);   // standard constructor
    virtual ~CRoomChatTab();

// Dialog Data
    enum { IDD = IDD_ROOMCHATTAB };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    CComboBox m_roomsComboBox;
    afx_msg void OnBnClickedJoinRoom();
    CEdit m_chatHistoryEdit;
    CEdit m_chatInputEdit;
public:
    virtual void DeliverJoinRoom(std::string roomName);
    virtual void DeliverRoomChat(std::string sender, std::string msg, std::string room);
    virtual void DeliverRooms(std::vector<std::string>& roomsList);
private:
    std::string joinedRoom;
public:
    afx_msg void OnCbnSelchangeCombo();
    afx_msg void OnBnClickedSend();
};
