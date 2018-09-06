#include "StdAfx.h"
#include "ParticipantOutResponse.h"

ParticipantOutResponse::ParticipantOutResponse(void)
    :XMLResponse(ParticipantOutResponseID)
{
}

ParticipantOutResponse::~ParticipantOutResponse(void)
{
}

bool ParticipantOutResponse::FragmentXML()
{
    bool bResult = true;
    pseudo = getArgumentAsText("pseudo", bResult);
    return true;
}

bool ParticipantOutResponse::ConstructXML()
{
    setArgumentAsText("pseudo", pseudo.c_str());
    return true;
}

void* ParticipantOutResponse::CreateInstance()
{
    return new ParticipantOutResponse;
}
