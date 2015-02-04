#include "Precompiled.hpp"
#include "Logger/Message.hpp"
using namespace Logger;

Message::Message() :
    std::ostream(&m_buffer),
    m_source(),
    m_line(0)
{
}

Message::Message(Message&& other) :
    std::ostream(&m_buffer)
{
    m_buffer = std::move(other.m_buffer);

    m_source = other.m_source;
    other.m_source = nullptr;

    m_line = other.m_line;
    other.m_line = 0;
}

Message::~Message()
{
}

Message& Message::SetText(const char* text)
{
    m_buffer.str("");

    if(text != nullptr)
    {
        m_buffer.sputn(text, strlen(text));
    }

    return *this;
}

Message& Message::SetSource(const char* source)
{
    if(source == nullptr)
        return *this;

    // Set message source.
    m_source = source;

    // Replace source path separators.
    std::replace(m_source.begin(), m_source.end(), '\\', '/');

    // Remove base path to source directory.
    std::size_t position = m_source.find(Build::GetSourceDir());

    if(position != std::string::npos)
    {
        m_source.erase(position, Build::GetSourceDir().size());
    }

    return *this;
}

Message& Message::SetLine(unsigned int line)
{
    // Set message line.
    m_line = line;

    return *this;
}
