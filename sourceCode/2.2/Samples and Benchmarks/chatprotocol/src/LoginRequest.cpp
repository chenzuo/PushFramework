#include "StdAfx.h"
#include "LoginRequest.h"

LoginRequest::LoginRequest(void)
    :XMLRequest(LoginRequestID)
{
}

LoginRequest::~LoginRequest(void)
{
}

bool LoginRequest::FragmentXML()
{
    bool bResult = true;
    pseudo = getArgumentAsText("pseudo", bResult);
    loginPuzzleReply = getArgumentAsInt("puzzleReply", bResult);
    return bResult;
}

bool LoginRequest::ConstructXML()
{
    setArgumentAsText("pseudo", pseudo.c_str());
    setArgumentAsInt("puzzleReply", loginPuzzleReply);
    return true;
}

void* LoginRequest::CreateInstance()
{
    return new LoginRequest;
}