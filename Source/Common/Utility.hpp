#pragma once

#include "Precompiled.hpp"

// Gets the size of a static array.
template<typename Type, size_t Size>
size_t StaticArraySize(const Type(&)[Size])
{
    return Size;
}

// Clamps a value between the lower and upper range.
template<typename Type>
Type Clamp(const Type& value, const Type& lower, const Type& upper)
{
    return std::max(lower, std::min(value, upper));
}

// Frees a container's memory (for STL implementations only).
template<typename Type>
void ClearContainer(Type& container)
{
    container.swap(Type());
}

// Gets the content of a text file.
std::string GetTextFileContent(std::string filename);

// Gets the content of a binary file.
std::vector<char> GetBinaryFileContent(std::string filename);

