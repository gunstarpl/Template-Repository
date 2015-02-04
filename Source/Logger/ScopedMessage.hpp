#pragma once

#include "Precompiled.hpp"
#include "Logger/Message.hpp"

//
// Logger Scoped Message
//  Log message wrapper that sends itself to the 
//  sink after it reaches the end of it's scope.
//

namespace Logger
{
    class Sink;

    class ScopedMessage : public Message
    {
    public:
        ScopedMessage(Sink* sink);
        ScopedMessage(ScopedMessage&& other);
        ~ScopedMessage();

    private:
        Sink* m_sink;
    };
}
