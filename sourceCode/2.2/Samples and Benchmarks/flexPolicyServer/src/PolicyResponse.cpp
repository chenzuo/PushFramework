#include "StdAfx.h"
#include "PolicyResponse.h"

PolicyResponse::PolicyResponse(std::string& _strPolicyContent)
    : strPolicyContent(_strPolicyContent)
{
}

PolicyResponse::~PolicyResponse(void)
{
}
char* PolicyResponse::getBuffer()
{
    return (char*) strPolicyContent.c_str();
}

unsigned int PolicyResponse::getBufferLen()
{
    return strPolicyContent.length();
}

bool PolicyResponse::Encode()
{
    return true;
}