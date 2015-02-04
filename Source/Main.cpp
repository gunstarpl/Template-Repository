#include "Precompiled.hpp"

int main(int argc, char* argv[])
{
    // Initialize debug routines.
    Debug::Initialize();
    
    // Output some text.
    std::cout << "Hello world!" << std::endl;
    std::cin.get();

    return 0;
}
