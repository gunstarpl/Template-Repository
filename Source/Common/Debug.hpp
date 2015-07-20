#pragma once

// Windows specific defines.
#if defined(_WINDOWS) && defined(_DEBUG)
    #define _CRTDBG_MAP_ALLOC
    #define _CRTDBG_MAP_ALLOC_NEW
    #include <stdlib.h>
    #include <crtdbg.h>

    /* 
    // Conflicts with Boost new operator.
    // Leaks are still going to be shown,
    // but without detailed info.
    #define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
    #define new DEBUG_NEW
    */
#endif

//
// Debug
//

namespace Debug
{
    // Initializes debug routines.
    // Call once at the very beginning of main().
    inline void Initialize()
    {
        // Don't do anything if not in debug mode.
        #ifndef _DEBUG
            return;
        #endif

        // Enable memory leak detection.
        #if defined(_WINDOWS) && defined(_DEBUG)
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
        #endif
    }
}
