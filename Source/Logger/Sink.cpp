#include "Precompiled.hpp"
#include "Logger/Sink.hpp"
#include "Logger/Logger.hpp"
using namespace Logger;

Sink::Sink()
{
}

Sink::~Sink()
{
    Cleanup();
}

void Sink::Cleanup()
{
    ClearContainer(m_outputs);

    // Discard if global.
    if(Logger::GetGlobal() == this)
    {
        Logger::SetGlobal(nullptr);
    }
}

void Sink::AddOutput(Output* output)
{
    if(output == nullptr)
        return;

    // Add logger output.
    m_outputs.push_back(output);
}

void Sink::RemoveOutput(Output* output)
{
    if(output == nullptr)
        return;

    // Find and remove logger output.
    auto it = std::find(m_outputs.begin(), m_outputs.end(), output);

    if(it != m_outputs.end())
    {
        m_outputs.erase(it);
    }
}

void Sink::Write(const Message& message)
{
    // Write to every logger output.
    auto it = m_outputs.begin();

    while(it != m_outputs.end())
    {
        (*it++)->Write(message);
    }
}
