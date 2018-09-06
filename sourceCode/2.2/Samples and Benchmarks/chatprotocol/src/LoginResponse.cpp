#include "StdAfx.h"
#include "LoginResponse.h"

LoginResponse::LoginResponse(void)
    :XMLResponse(LoginResponseID)
{
}

LoginResponse::~LoginResponse(void)
{
}

bool LoginResponse::FragmentXML()
{
    bool bResult = true;
    msg = getArgumentAsText("msg", bResult);
    bAccepted = getArgumentAsBool("accepted", bResult);
    return bResult;
}

bool LoginResponse::ConstructXML()
{
    setArgumentAsText("msg", msg.c_str());
    setArgumentAsBool("accepted", bAccepted);
    return true;
}

void* LoginResponse::CreateInstance()
{
    return new LoginResponse;
}