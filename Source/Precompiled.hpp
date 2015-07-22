#pragma once

#include <memory>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#define BOOST_SCOPE_EXIT_CONFIG_USE_LAMBDAS
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/scope_exit.hpp>
#include <boost/range.hpp>

#include "Common/Debug.hpp"
#include "Common/Build.hpp"
#include "Common/Logger.hpp"
#include "Common/Utility.hpp"
