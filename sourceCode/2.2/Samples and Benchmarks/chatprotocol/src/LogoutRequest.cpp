#include "StdAfx.h"
#include "LogoutRequest.h"

LogoutRequest::LogoutRequest(void)
    :XMLRequest(LogoutRequestID)
{
}

LogoutRequest::~LogoutRequest(void)
{
}

bool LogoutRequest::FragmentXML()
{
    return true;
}

bool LogoutRequest::ConstructXML()
{
    return true;
}

void* LogoutRequest::CreateInstance()
{
    return new LogoutRequest;
}