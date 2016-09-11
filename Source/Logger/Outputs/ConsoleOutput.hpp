#pragma once

#include "Precompiled.hpp"
#include "Logger/Output.hpp"

//
// Console Output
//  Writes log messsages to the console window.
//

namespace Logger
{
    class ConsoleOutput : public Logger::Output
    {
    public:
        ConsoleOutput();
        ~ConsoleOutput();

        // Writes a message to the console window.
        void Write(const Logger::Message& message);
    };
}
