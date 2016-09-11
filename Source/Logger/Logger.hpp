#pragma once

#include "Precompiled.hpp"
#include "Logger/Message.hpp"
#include "Logger/Sink.hpp"

//
// Logger
//  Writes log messages to multiple outputs for debugging purposes.
//
//  Example usage:
//      Logger::Initialize();
//      Log() << "Hello world!";
//

namespace Logger
{
    // Forward declarations.
    class Sink;

    // Initializes the logger.
    void Initialize();

    // Writes to the global logger sink.
    void Write(const Logger::Message& message);
    
    // Gets the global logger sink.
    Sink* GetGlobal();
}

//
// Macros
//

#ifndef NDEBUG
    #define Log() Logger::ScopedMessage(Logger::GetGlobal()).SetSource(__FILE__).SetLine(__LINE__)
#else
    #define Log() Logger::ScopedMessage(Logger::GetGlobal())
#endif
