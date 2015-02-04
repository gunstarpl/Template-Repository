#include "Precompiled.hpp"

int main(int argc, char* argv[])
{
    // Initialize debug routines.
    Debug::Initialize();

    // Load build info.
    Build::LoadInfo();

    // Create logger sink.
    Logger::Sink loggerSink;
    Logger::SetGlobal(&loggerSink);

    // Create logger output.
    Logger::FileOutput loggerOutput;

    if(loggerOutput.Open("Log.txt"))
    {
        loggerSink.AddOutput(&loggerOutput);
    }

    Log() << "Hello world!";
    
    // Output some text to console.
    std::cout << "Hello world!" << std::endl;
    std::cin.get();

    return 0;
}
