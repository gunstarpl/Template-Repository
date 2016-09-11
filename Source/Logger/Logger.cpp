#include "Precompiled.hpp"
#include "Logger.hpp"
#include "Sink.hpp"

#include "Outputs/DebuggerOutput.hpp"
#include "Outputs/ConsoleOutput.hpp"
#include "Outputs/FileOutput.hpp"

namespace
{
    // Logger sink.
    Logger::Sink sink;

    // Logger outputs.
    Logger::DebuggerOutput debuggerOutput;
    Logger::ConsoleOutput consoleOutput;
    Logger::FileOutput fileOutput;

    // Initialization state.
    bool initialized = false;
}

void Logger::Initialize()
{
    if(initialized)
        return;

    // Add the debugger output.
    sink.AddOutput(&debuggerOutput);

    // Add the console output.
    sink.AddOutput(&consoleOutput);

    // Add the file output.
    if(fileOutput.Initialize("Log.txt"))
    {
        sink.AddOutput(&fileOutput);
    }

    // Set initialized state.
    initialized = true;
}

void Logger::Write(const Logger::Message& message)
{
    sink.Write(message);
}

Logger::Sink* Logger::GetGlobal()
{
    return &sink;
}
