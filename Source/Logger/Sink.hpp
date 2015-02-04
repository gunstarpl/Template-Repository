#pragma once

#include "Precompiled.hpp"

#include "Common/NonCopyable.hpp"
#include "Logger/Output.hpp"
#include "Logger/Message.hpp"
#include "Logger/ScopedMessage.hpp"

//
// Logger Sink
//  Entry point for log messages that will be redirected to registered outputs.
//

namespace Logger
{
    class Message;

    class Sink : public NonCopyable
    {
    public:
        Sink();
        ~Sink();

        void Cleanup();

        void AddOutput(Output* output);
        void RemoveOutput(Output* output);

        void Write(const Message& message);

    private:
        std::vector<Output*> m_outputs;
    };
}
