#pragma once

#include "Precompiled.hpp"
#include "Logger/Message.hpp"

//
// Logger Output
//  Base interface for sink output.
//

namespace Logger
{
    class Output
    {
    public:
        virtual void Write(const Message& message) = 0;
    };
}
