#include "StdAfx.h"
#include "LoginPuzzleResponse.h"

LoginPuzzleResponse::LoginPuzzleResponse(void)
    :XMLResponse(LoginPuzzleResponseID)
{
}

LoginPuzzleResponse::~LoginPuzzleResponse(void)
{
}

bool LoginPuzzleResponse::FragmentXML()
{
    bool bResult = true;
    puzzleQuestion = getArgumentAsInt("puzzle", bResult);
    return bResult;
}

bool LoginPuzzleResponse::ConstructXML()
{
    setArgumentAsInt("puzzle", puzzleQuestion);
    return true;
}

void* LoginPuzzleResponse::CreateInstance()
{
    return new LoginPuzzleResponse();
}
