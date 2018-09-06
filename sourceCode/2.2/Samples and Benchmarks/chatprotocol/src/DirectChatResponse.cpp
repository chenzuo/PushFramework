#include "StdAfx.h"
#include "DirectChatResponse.h"

DirectChatResponse::DirectChatResponse(void)
    :XMLResponse(DirectChatResponseID)
{
}

DirectChatResponse::~DirectChatResponse(void)
{
}

bool DirectChatResponse::FragmentXML()
{
    bool bResult = true;
    sender = getArgumentAsText("from", bResult);
    msg = getArgumentAsText("msg", bResult);

    return bResult;
}

bool DirectChatResponse::ConstructXML()
{
    setArgumentAsText("from", sender.c_str());
    setArgumentAsText("msg", msg.c_str());

    return true;
}

void* DirectChatResponse::CreateInstance()
{
    return new DirectChatResponse;
}