#pragma once

#include "ProtocolIDs.h"
#include "Symbols.h"

class CHATPROTOCOL_API DirectChatResponse : public XMLResponse
{
public:
    DirectChatResponse(void);
    ~DirectChatResponse(void);

    std::string Msg() const
    {
        return msg;
    }
    void Msg(std::string val)
    {
        msg = val;
    }

    std::string Sender() const
    {
        return sender;
    }
    void Sender(std::string val)
    {
        sender = val;
    }

private:
    std::string sender;
    std::string msg;

protected:
    virtual bool FragmentXML();
    virtual bool ConstructXML();

    virtual void* CreateInstance();
};
