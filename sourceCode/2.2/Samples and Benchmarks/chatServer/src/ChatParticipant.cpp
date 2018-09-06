#include "StdAfx.h"
#include "ChatParticipant.h"

ChatParticipant::ChatParticipant(std::string pseudo)
{
    this->pseudo = pseudo;
}

ChatParticipant::~ChatParticipant(void)
{
}

CLIENT_KEY ChatParticipant::getKey()
{
    return pseudo.c_str();
}
