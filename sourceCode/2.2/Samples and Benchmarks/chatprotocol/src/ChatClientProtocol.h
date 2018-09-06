#pragma once
#include "ProtocolIDs.h"
#include "Symbols.h"

class CHATPROTOCOL_API ChatClientProtocol : public XMLProtocol
{
public:
    ChatClientProtocol(void);
    ~ChatClientProtocol(void);
};
