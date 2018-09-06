#pragma once

#include "ProtocolIDs.h"
#include "Symbols.h"

class CHATPROTOCOL_API LoginResponse : public XMLResponse
{
public:
    LoginResponse(void);
    ~LoginResponse(void);
    std::string Msg() const
    {
        return msg;
    }
    void Msg(std::string val)
    {
        msg = val;
    }

    bool BAccepted() const
    {
        return bAccepted;
    }
    void BAccepted(bool val)
    {
        bAccepted = val;
    }
private:
    bool bAccepted;

    std::string msg;

protected:
    virtual bool FragmentXML();
    virtual bool ConstructXML();

    virtual void* CreateInstance();


};
