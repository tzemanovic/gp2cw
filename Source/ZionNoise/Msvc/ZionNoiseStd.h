#pragma once
////////////////////////////////////////////////////
// precompiled header file
////////////////////////////////////////////////////

#include <stdlib.h>

#if defined(_WIN32) || defined(__WIN32__)
    // Windows
    #define ZN_SYSTEM_WINDOWS
    // avoid min/max problems
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    // exclude rarely-used services from Windows headers
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
#else
    #error This operation system is not supported
#endif