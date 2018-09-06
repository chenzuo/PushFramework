#pragma once

class CTestClient : public LogicalConnection
{
public:
    CTestClient(const char* _pseudo);
    ~CTestClient(void);

    virtual const char* getKey();

private:
    string pseudo;

public:
    SendResult PushPacket(protobuf::Message* pMessage);
};
