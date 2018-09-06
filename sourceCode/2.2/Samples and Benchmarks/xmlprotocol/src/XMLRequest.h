#ifndef XMLRequest__INCLUDED
#define XMLRequest__INCLUDED

#pragma once

#include "Symbols.h"
#include "IncomingXMLPacket.h"
#include "OutgoingXMLPacket.h"

class XMLPROTOCOL_API XMLRequest : public IncomingXMLPacket, public OutgoingXMLPacket
{
public:
    XMLRequest(unsigned int serviceId);
    ~XMLRequest(void);
};
#endif // XMLRequest__INCLUDED
