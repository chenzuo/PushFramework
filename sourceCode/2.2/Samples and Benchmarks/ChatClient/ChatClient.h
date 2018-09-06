
// ChatClient.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CChatClientApp:
// See ChatClient.cpp for the implementation of this class
//
class CChatClientDlg;

#include "MyChatAPI.h"

class CChatClientApp : public CWinAppEx
{
public:
    CChatClientApp();

// Overrides
public:
    virtual BOOL InitInstance();

// Implementation

    DECLARE_MESSAGE_MAP()
public:
    CChatClientDlg* getWindow();

private:
    CMyChatAPI theChatAPI;
public:
    CMyChatAPI& getChatAPI()
    {
        return theChatAPI;
    }
};

extern CChatClientApp theApp;