#pragma once

#include "Precompiled.hpp"

//
// Logger Message
//  An object that contains the message and it's meta data.
//

namespace Logger
{
    class Message : public NonCopyable, public std::ostream
    {
    public:
        Message();
        Message(Message&& other);
        virtual ~Message();

        Message& SetText(const char* text);
        Message& SetSource(const char* source);
        Message& SetLine(unsigned int line);

        bool IsEmpty() const
        {
            return m_buffer.str().empty();
        }

        std::string GetText() const
        {
            return m_buffer.str();
        }

        std::string GetSource() const
        {
            return m_source;
        }

        unsigned int GetLine() const
        {
            return m_line;
        }

    private:
        std::stringbuf m_buffer;
        std::string    m_source;
        unsigned int   m_line;
    };
}
