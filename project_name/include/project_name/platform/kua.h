#ifndef PNX_PLATFORM_KUA_H
#define PNX_PLATFORM_KUA_H

#if defined(_WIN32) || defined(_WIN64)
    #define PNX_PLATFORM_WINDOWS 1
    #define PNX_PLATFORM_NAME "Windows"
    #include <windows.h>
    #include <conio.h>
#elif defined(__linux__) || defined(__linux)
    #define PNX_PLATFORM_LINUX 1
    #define PNX_PLATFORM_NAME "Linux"
    #include <unistd.h>
#elif defined(__APPLE__) && defined(__MACH__)
    #define PNX_PLATFORM_MACOS 1
    #define PNX_PLATFORM_NAME "macOS"
    #include <mach/mach.h>
#else
    #define PNX_PLATFORM_UPNNOWN 1
    #define PNX_PLATFORM_NAME "Unknown"
    #warning "Unknown platform, using POSIX compatibility mode"
#endif

#endif
