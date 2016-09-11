#pragma once

//
// Standard
//

#include <cctype>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

//
// External
//

// Windows
#ifdef WIN32
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX
    #include <windows.h>
#endif

//
// Project
//

#include "Common/Build.hpp"
#include "Common/Debug.hpp"
#include "Common/Utility.hpp"
#include "Common/NonCopyable.hpp"
#include "Common/ScopeGuard.hpp"
#include "Common/Delegate.hpp"
#include "Common/Collector.hpp"
#include "Logger/Logger.hpp"
