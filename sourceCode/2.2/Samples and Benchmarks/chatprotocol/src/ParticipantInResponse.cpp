#include "StdAfx.h"
#include "ParticipantInResponse.h"

ParticipantInResponse::ParticipantInResponse(void)
    :XMLResponse(ParticipantInResponseID)
{
}

ParticipantInResponse::~ParticipantInResponse(void)
{
}

bool ParticipantInResponse::FragmentXML()
{
    bool bResult = true;
    pseudo = getArgumentAsText("pseudo", bResult);
    return bResult;
}

bool ParticipantInResponse::ConstructXML()
{
    setArgumentAsText("pseudo", pseudo.c_str());
    return true;
}

void* ParticipantInResponse::CreateInstance()
{
    return new ParticipantInResponse;
}
