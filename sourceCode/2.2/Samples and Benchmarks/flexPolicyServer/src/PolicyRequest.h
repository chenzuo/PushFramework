#pragma once

class PolicyRequest : public IncomingPacket
{
public:
    PolicyRequest();
    ~PolicyRequest(void);

    virtual bool Decode(char* pString, unsigned int nBytes);

private:
    std::string strRequest;
};
