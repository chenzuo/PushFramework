#pragma once
#include "ProtobufProtocol.h"

namespace testsuitemessages
{
    class TestProtocol : public ProtobufProtocol
    {
    public:
        TestProtocol(void);
        ~TestProtocol(void);
    };
}

