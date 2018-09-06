#pragma once

#include "ProtocolIDs.h"
#include "Symbols.h"

class CHATPROTOCOL_API LoginRequest : public XMLRequest
{
public:
    LoginRequest(void);
    ~LoginRequest(void);

    std::string Pseudo() const
    {
        return pseudo;
    }
    void Pseudo(std::string val)
    {
        pseudo = val;
    }

    int LoginPuzzleReply() const
    {
        return loginPuzzleReply;
    }
    void LoginPuzzleReply(int val)
    {
        loginPuzzleReply = val;
    }
private:
    std::string pseudo;
    int loginPuzzleReply;

protected:
    virtual bool FragmentXML();
    virtual bool ConstructXML();

    virtual void* CreateInstance();

};
