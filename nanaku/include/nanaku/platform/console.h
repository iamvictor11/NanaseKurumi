#ifndef NANAKU_PLATFORM_CONSOLE_H
#define NANAKU_PLATFORM_CONSOLE_H

void nkSetConsoleOutputCP_UTF8();
void nkGetChar();

#ifdef NANAKU_IMPL_FILE

#include "kua.h"

void nkSetConsoleOutputCP_UTF8()
{
#if NK_PLATFORM_WINDOWS
    SetConsoleOutputCP(CP_UTF8);
#elif NK_PLATFORM_LINUX
#elif NK_PLATFORM_MACOS
#else
#endif
}
void nkGetChar()
{
#if NK_PLATFORM_WINDOWS
    _getch();
#elif NK_PLATFORM_LINUX
#elif NK_PLATFORM_MACOS
#else
#endif
}

#endif

#endif
