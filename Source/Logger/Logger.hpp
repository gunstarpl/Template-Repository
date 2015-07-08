#pragma once

#include "Logger/ScopedMessage.hpp"
#include "Logger/FileOutput.hpp"
#include "Logger/Sink.hpp"

// Log macro.
#ifdef _DEBUG
    #define Log() Logger::ScopedMessage(Logger::GetGlobal()).SetSource(__FILE__).SetLine(__LINE__)
#else
    #define Log() Logger::ScopedMessage(Logger::GetGlobal())
#endif

//
// Logger
//
//  Logs messages to multiple outputs. See other headers for more info.
//
//  Creating a logger sink:
//      Logger::Sink sink;
//      
//      Logger::FileOutput output;
//      if(output.Open("Log.txt"))
//      {
//          sink.AddOutput(&output);
//      }
//
//  Using global macros to write log messages:
//      Logger::SetGlobal(&sink);
//      Log() << "Hello world!";
//

namespace Logger
{
    // Sets the global logging sink.
    void SetGlobal(Sink* sink);

    // Gets the global logging sink.
    Sink* GetGlobal();
}
