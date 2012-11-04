#pragma once
////////////////////////////////////////////////////
// precompiled header file
////////////////////////////////////////////////////

#include <stdlib.h>
#include <string>
#include <queue>

using namespace std;

#if defined( _WIN32 ) || defined( __WIN32__ )
    // Windows
#   define ZN_PLATFORM_WIN32
    // avoid min/max problems
#   ifndef NOMINMAX
#       define NOMINMAX
#   endif
    // exclude rarely-used services from Windows headers
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif
#else
#   error This operation system is not supported
#endif

// redefine new for debugging purposes
#if defined( _DEBUG )
#	define ZN_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#else
#	define ZN_NEW new
#endif

// safe delete pointer
#ifndef ZN_SAFE_DELETE
#   define ZN_SAFE_DELETE( x ) if( x ) delete x; x = NULL;
#endif
// safe delete array
#ifndef ZN_SAFE_DELETE_ARRAY
#   define ZN_SAFE_DELETE_ARRAY( x ) if( x ) delete [] x; x = NULL;
#endif
// safe release
#ifndef ZN_SAFE_RELEASE
#   define ZN_SAFE_RELEASE( x ) if( x ) x->Release(); x = NULL;
#endif

// typedefs
namespace zn
{
    typedef signed char int8;
    typedef unsigned char uint8;
    typedef signed short int16;
    typedef unsigned short uint16;
    typedef signed int int32;
    typedef unsigned int uint32;
#   ifdef _MSC_VER
        typedef signed __int64 int64;
        typedef unsigned __int64 uint64;
#   else
        typedef signed long long int64;
        typedef unsigned long long uint64;
#   endif
}

#include "..\Geometry\Vec2.h"