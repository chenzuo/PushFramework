#pragma once

class FlexSandbox : public LogicalConnection
{
public:

    FlexSandbox(std::string clientName)
    {
        this->clientName = clientName;
    }

    ~FlexSandbox(void)
    {
    }

    virtual const char* getKey()
    {
        return clientName.c_str();
    }

private:
    std::string clientName;
};
