#include "StdAfx.h"
#include "PolicyRequest.h"

PolicyRequest::PolicyRequest()
{
}

PolicyRequest::~PolicyRequest(void)
{
}

bool PolicyRequest::Decode(char* pString, unsigned int nBytes)
{
    char* pRequestString = new char[nBytes + 1];
    memcpy(pRequestString, pString, nBytes);
    pRequestString[nBytes] = '\0';
    strRequest = pRequestString;
    delete pRequestString;

    return strRequest == "<policy-file-request/>";
}
