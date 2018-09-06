#ifndef XMLResponse__INCLUDED
#define XMLResponse__INCLUDED



#pragma once

#include "Symbols.h"
#include "IncomingXMLPacket.h"
#include "OutgoingXMLPacket.h"

class XMLPROTOCOL_API XMLResponse : public IncomingXMLPacket, public OutgoingXMLPacket
{
public:
    XMLResponse(unsigned int serviceId);
    virtual ~XMLResponse(void);
};



#endif // XMLResponse__INCLUDED
