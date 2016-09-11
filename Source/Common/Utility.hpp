#pragma once

#include "Precompiled.hpp"

//
// Utility
//

namespace Utility
{
    // Gets the size of a static array.
    template<typename Type, size_t Size>
    size_t ArraySize(const Type(&)[Size])
    {
        return Size;
    }

    // Frees STL container's memory.
    template<typename Type>
    void ClearContainer(Type& container)
    {
        container.swap(Type());
    }

    // Gets the path of a file.
    std::string GetFilePath(std::string filename);

    // Gets the extension of a file.
    std::string GetFileExtension(std::string filename);

    // Gets the content of a text file.
    std::string GetTextFileContent(std::string filename);

    // Gets the content of a binary file.
    std::vector<char> GetBinaryFileContent(std::string filename);
}
