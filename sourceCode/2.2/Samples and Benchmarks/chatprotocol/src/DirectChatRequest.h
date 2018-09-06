#ifndef DirectChatRequest__INCLUDED
#define DirectChatRequest__INCLUDED

#pragma once

#include "ProtocolIDs.h"
#include "Symbols.h"

class CHATPROTOCOL_API DirectChatRequest : public XMLRequest
{
public:
    DirectChatRequest(void);
    ~DirectChatRequest(void);

    std::string Msg() const
    {
        return msg;
    }
    void Msg(std::string val)
    {
        msg = val;
    }
    std::string Recipient() const
    {
        return recipient;
    }
    void Recipient(std::string val)
    {
        recipient = val;
    }


private:
    std::string recipient;
    std::string msg;

protected:
    virtual bool FragmentXML();
    virtual bool ConstructXML();

    virtual void* CreateInstance();


};
#endif // DirectChatRequest__INCLUDED
