#include "Precompiled.hpp"
#include "Sink.hpp"
#include "Output.hpp"
#include "Message.hpp"
using namespace Logger;

Sink::Sink()
{
}

Sink::~Sink()
{
}

void Sink::AddOutput(Logger::Output* output)
{
    if(output == nullptr)
        return;

    // Add an output to the list.
    m_outputs.push_back(output);
}

void Sink::RemoveOutput(Logger::Output* output)
{
    if(output == nullptr)
        return;

    // Find and remove an output from the list.
    m_outputs.erase(std::remove(m_outputs.begin(), m_outputs.end(), output), m_outputs.end());
}

void Sink::Write(const Logger::Message& message)
{
    // Write a message to all outputs.
    for(auto output : m_outputs)
    {
        output->Write(message);
    }
}
