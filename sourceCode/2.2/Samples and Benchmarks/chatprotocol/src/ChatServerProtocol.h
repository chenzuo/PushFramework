#pragma once
#include "ProtocolIDs.h"
#include "Symbols.h"

class CHATPROTOCOL_API ChatServerProtocol : public XMLProtocol
{
public:
    ChatServerProtocol(void);
    ~ChatServerProtocol(void);
};
