#pragma once

#include "Precompiled.hpp"
#include "Logger/Output.hpp"

/*
    Logger Debugger Output Class

    Writes log messages to the debugger's window.
*/

namespace Logger
{
    class DebuggerOutput : public Logger::Output
    {
    public:
        DebuggerOutput();
        ~DebuggerOutput();

        // Writes a message to the debugger window.
        void Write(const Logger::Message& message);

    private:
        // Reusable string stream.
        std::stringstream m_stream;
    };
}
