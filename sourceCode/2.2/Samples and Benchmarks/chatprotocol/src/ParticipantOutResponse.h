#pragma once

#include "ProtocolIDs.h"
#include "Symbols.h"

class CHATPROTOCOL_API ParticipantOutResponse : public XMLResponse
{
public:
    ParticipantOutResponse(void);
    ~ParticipantOutResponse(void);
    std::string Pseudo() const
    {
        return pseudo;
    }
    void Pseudo(std::string val)
    {
        pseudo = val;
    }
private:
    std::string pseudo;

protected:
    virtual bool FragmentXML();
    virtual bool ConstructXML();

    virtual void* CreateInstance();
};
