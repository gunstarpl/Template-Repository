#pragma once

#include "Precompiled.hpp"

/*
    Logger Message Class

    Object that holds a messages along with its metadata.
*/

namespace Logger
{
    // Message class.
    class Message : private NonCopyable, public std::ostream
    {
    public:
        Message();
        Message(Message&& other);
        virtual ~Message();

        // Sets the message text.
        Message& SetText(const char* text);

        // Sets the message source.
        Message& SetSource(const char* source);

        // Sets the message line.
        Message& SetLine(int line);

        // Gets the message text.
        std::string GetText() const;

        // Gets the message source.
        std::string GetSource() const;

        // Gets the message line.
        int GetLine() const;

        // Checks if the message is empty.
        bool IsEmpty() const;

    private:
        // Message state.
        std::stringbuf m_text;
        std::string    m_source;
        int            m_line;
    };
}

/*
    Scoped Logger Message Class

    Logger message object that writes to a sink at the end of its lifetime.
*/

namespace Logger
{
    // Forward declarations.
    class Sink;

    // Scoped message class.
    class ScopedMessage : public Message
    {
    public:
        ScopedMessage(Logger::Sink* sink);
        ScopedMessage(ScopedMessage&& other);
        ~ScopedMessage();

    private:
        // Message sink output.
        Logger::Sink* m_sink;
    };
}
