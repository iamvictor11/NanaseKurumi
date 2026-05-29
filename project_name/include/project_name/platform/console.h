#ifndef PNX_PLATFORM_CONSOLE_H
#define PNX_PLATFORM_CONSOLE_H

void pnxSetConsoleOutputCP_UTF8();
void pnxGetChar();

#ifdef PNX_IMPL_FILE

#include "kua.h"

void pnxSetConsoleOutputCP_UTF8()
{
#if PNX_PLATFORM_WINDOWS
    SetConsoleOutputCP(CP_UTF8);
#elif PNX_PLATFORM_LINUX
#elif PNX_PLATFORM_MACOS
#else
#endif
}
void pnxGetChar()
{
#if PNX_PLATFORM_WINDOWS
    _getch();
#elif PNX_PLATFORM_LINUX
#elif PNX_PLATFORM_MACOS
#else
#endif
}

#endif

#endif
