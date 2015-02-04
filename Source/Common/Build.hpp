#pragma once

#include "Precompiled.hpp"

//
// Build
//

namespace Build
{
    // Loads build info.
    void LoadInfo();

    // Gets set at build time working directory.
    std::string GetWorkingDir();

    // Gets set at build time source directory.
    std::string GetSourceDir();
}
