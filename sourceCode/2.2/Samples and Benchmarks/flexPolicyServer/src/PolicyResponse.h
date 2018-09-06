#pragma once

class PolicyResponse : public OutgoingPacket
{
public:
    PolicyResponse(std::string& strPolicyContent);
    ~PolicyResponse(void);
    char* getBuffer();
    unsigned int getBufferLen();
    bool Encode();
private:
    std::string& strPolicyContent;
};
