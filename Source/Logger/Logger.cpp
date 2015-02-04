#include "Precompiled.hpp"
#include "Logger/Logger.hpp"
using namespace Logger;

namespace
{
    Sink* globalSink = nullptr;
}

void Logger::SetGlobal(Sink* sink)
{
    globalSink = sink;
}

Sink* Logger::GetGlobal()
{
    return globalSink;
}
