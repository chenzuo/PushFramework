#include "StdAfx.h"
#include "DirectChatRequest.h"

DirectChatRequest::DirectChatRequest(void)
    :XMLRequest(DirectChatRequestID)
{
}

DirectChatRequest::~DirectChatRequest(void)
{
}

bool DirectChatRequest::FragmentXML()
{
    bool bResult = true;
    recipient = getArgumentAsText("to", bResult);
    msg = getArgumentAsText("msg", bResult);

    return bResult;
}

bool DirectChatRequest::ConstructXML()
{
    setArgumentAsText("to", recipient.c_str());
    setArgumentAsText("msg", msg.c_str());
    return true;
}

void* DirectChatRequest::CreateInstance()
{
    return new DirectChatRequest;
}
