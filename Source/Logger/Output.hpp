#pragma once

#include "Precompiled.hpp"

//
// Output
//  Base interface for output implementations.
//

namespace Logger
{
    // Forward declarations.
    class Message;

    // Output interface.
    class Output : private NonCopyable
    {
    public:
        // Writes a message to an output.
        virtual void Write(const Logger::Message& message) = 0;
    };
}
