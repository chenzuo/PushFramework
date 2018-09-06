#pragma once

#include "ProtocolIDs.h"
#include "Symbols.h"

class CHATPROTOCOL_API LogoutRequest : public XMLRequest
{
public:
    LogoutRequest(void);
    ~LogoutRequest(void);

protected:
    virtual bool FragmentXML();
    virtual bool ConstructXML();

    virtual void* CreateInstance();
};
