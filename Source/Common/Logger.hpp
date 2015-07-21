#pragma once

#include "Precompiled.hpp"

#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>

//
// Logger
//

namespace Logger
{
    // Initializes the logger.
    void Initialize();
}

// Log macro.
#ifdef _DEBUG
    #define Log() BOOST_LOG_FUNCTION(); BOOST_LOG_TRIVIAL(info)
#else
    #define Log() BOOST_LOG_TRIVIAL(info)
#endif
