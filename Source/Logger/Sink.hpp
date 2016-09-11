#pragma once

#include "Precompiled.hpp"

//
// Sink
//  Writes messages to multiple outputs.
//

namespace Logger
{
    // Forward declarations.
    class Output;
    class Message;

    // Sink class.
    class Sink : private NonCopyable
    {
    public:
        // Type declarations.
        typedef std::vector<Logger::Output*> OutputList;

    public:
        Sink();
        ~Sink();

        // Adds an output.
        void AddOutput(Logger::Output* output);

        // Removes an output.
        void RemoveOutput(Logger::Output* output);

        // Writes a log message.
        void Write(const Logger::Message& message);

    private:
        // List of outputs.
        OutputList m_outputs;
    };
}
