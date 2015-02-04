#include "Precompiled.hpp"
#include "Logger/ScopedMessage.hpp"
#include "Logger/Sink.hpp"
using namespace Logger;

ScopedMessage::ScopedMessage(Sink* sink) :
    m_sink(sink)
{
}

ScopedMessage::ScopedMessage(ScopedMessage&& other) :
    Message(std::forward<ScopedMessage>(other))
{
    m_sink = other.m_sink;
    other.m_sink = nullptr;
}

ScopedMessage::~ScopedMessage()
{
    if(m_sink != nullptr)
    {
        m_sink->Write(*this);
    }
}
