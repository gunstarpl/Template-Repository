#pragma once

/*
    Platform Defines
*/

// Windows specific defines.
#if defined(WIN32) && !defined(NDEBUG)
    #define _CRTDBG_MAP_ALLOC
    #define _CRTDBG_MAP_ALLOC_NEW
    #include <stdlib.h>
    #include <crtdbg.h>

    /* 
    // Override new operator (breaks placement new).
    #define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
    #define new DEBUG_NEW
    */
#endif

/*
    Debug Utility
*/

namespace Debug
{
    // Initializes debug helpers.
    inline void Initialize()
    {
        // Don't do anything if not in debug mode.
        #ifdef NDEBUG
            return;
        #endif

        // Enable memory leak detection.
        #if defined(WIN32)
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
        #endif
    }
}

/*
    Debug Macros
*/

#define DEBUG_EXPAND_MACRO(x) x

#define DEBUG_PRINT_ASSERT_SIMPLE(expression) \
    Logger::ScopedMessage(Logger::GetGlobal()).SetSource(__FILE__).SetLine(__LINE__) \
        << "Assertion failed: \"" << expression << "\"";

#define DBEUG_PRINT_ASSERT_MESSAGE(expression, message) \
    Logger::ScopedMessage(Logger::GetGlobal()).SetSource(__FILE__).SetLine(__LINE__) \
        << "Assertion failed: \"" << expression << "\" - " << message;

/*
    Assert Macros

    Makes sure that a given expression is true.
    Used to check for programming errors during debugging and development.
    
    Behaviour in different build types:
    - Debug: Triggers a breakpoint
    - Release: Check is stripped
    
    Usage:
        Assert(m_initialized);
        Assert(instance != nullptr, "Invalid instance.");
*/

#ifndef NDEBUG
    #define ASSERT_SIMPLE(expression)                         \
        if(!(expression))                                     \
        {                                                     \
            DEBUG_PRINT_ASSERT_SIMPLE(#expression);           \
            __debugbreak();                                   \
        }

    #define ASSERT_MESSAGE(expression, message)               \
        if(!(expression))                                     \
        {                                                     \
            DBEUG_PRINT_ASSERT_MESSAGE(#expression, message); \
            __debugbreak();                                   \
        }
#else
    #define ASSERT_SIMPLE(expression) ((void)0)
    #define ASSERT_MESSAGE(expression, message) ((void)0) 
#endif

#define ASSERT_DEDUCE(arg1, arg2, arg3, ...) arg3
#define ASSERT_CHOOSER(...) DEBUG_EXPAND_MACRO(ASSERT_DEDUCE(__VA_ARGS__, ASSERT_MESSAGE, ASSERT_SIMPLE))

#define Assert(...) DEBUG_EXPAND_MACRO(ASSERT_CHOOSER(__VA_ARGS__)(__VA_ARGS__))

/*
    Verify Macro
    
    Makes sure that a given expression is true.
    Same as Assert(), but triggers in release builds.
    Runtime checks should be prefered instead of this.
    
    Behaviour in different build types:
    - Debug: Triggers a breakpoint
    - Release: Triggers a breakpoint
    
    Usage:
        Verify(m_initialized);
        Verify(instance != nullptr, "Invalid instance.");
*/

#ifndef NDEBUG
    #define VERIFY_SIMPLE(expression)                         \
        if(!(expression))                                     \
        {                                                     \
            DEBUG_PRINT_ASSERT_SIMPLE(#expression);           \
            __debugbreak();                                   \
        }

    #define VERIFY_MESSAGE(expression, message)               \
        if(!(expression))                                     \
        {                                                     \
            DBEUG_PRINT_ASSERT_MESSAGE(#expression, message); \
            __debugbreak();                                   \
        }
#else
    #define VERIFY_SIMPLE(expression)                         \
        if(!(expression))                                     \
        {                                                     \
            DEBUG_PRINT_ASSERT_SIMPLE(#expression);           \
            __debugbreak();                                   \
        }

    #define VERIFY_MESSAGE(expression, message)               \
        if(!(expression))                                     \
        {                                                     \
            DBEUG_PRINT_ASSERT_MESSAGE(#expression, message); \
            __debugbreak();                                   \
        }
#endif

#define VERIFY_DEDUCE(arg1, arg2, arg3, ...) arg3
#define VERIFY_CHOOSER(...) DEBUG_EXPAND_MACRO(VERIFY_DEDUCE(__VA_ARGS__, VERIFY_MESSAGE, VERIFY_SIMPLE))

#define Verify(...) DEBUG_EXPAND_MACRO(VERIFY_CHOOSER(__VA_ARGS__)(__VA_ARGS__))
