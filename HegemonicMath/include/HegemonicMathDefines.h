#pragma once

#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	// Windows logic
	#define WINDOWS_PLATFORM 1
	#define LINUX_PLATFORM 0
	#define FILESEP "\\"
    #ifdef BUILDING_HEGEMONIC_MATH
        #define HEXPORT_MATH __declspec(dllexport)
    #else
        #define HEXPORT_MATH __declspec(dllimport)
    #endif
#else
    // Linux/Unix logic
	#define WINDOWS_PLATFORM 0
	#define LINUX_PLATFORM 1
	#define FILESEP "/"
    #if __GNUC__ >= 4
        #define HEXPORT_MATH __attribute__((visibility("default")))
    #else
        #define HEXPORT_MATH
    #endif
#endif