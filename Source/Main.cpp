#include "Precompiled.hpp"

int main(int argc, char* argv[])
{
    // Initialize debug routines.
    Debug::Initialize();

    // Initialize build info.
    Build::Initialize();

    // Initialize logging system.
    Logger::Initialize();

    // Example code.
    Log() << "Hello world!";

    return 0;
}
