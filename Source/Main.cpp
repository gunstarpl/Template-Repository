#include "Precompiled.hpp"

int main(int argc, char* argv[])
{
    // Initialize debug routines.
    Debug::Initialize();

    // Initialize build info.
    Build::Initialize();

    // Create logger sink.
    Logger::Sink loggerSink;
    Logger::SetGlobal(&loggerSink);

    // Create logger output.
    Logger::FileOutput loggerOutput;
    loggerOutput.Open("Log.txt");

    loggerSink.AddOutput(&loggerOutput);

    // Output some text to logger.
    Log() << "Hello world!";

    // Output some text to console.
    std::cout << "Hello world!" << std::endl;
    std::cin.get();

    return 0;
}
