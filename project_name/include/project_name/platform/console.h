#ifndef PN_PLATFORM_CONSOLE_H
#define PN_PLATFORM_CONSOLE_H

void pn_SetConsoleOutputCP_UTF8();
void pn_GetChar();

#ifdef PN_IMPL_FILE

#include "kua.h"

void pn_SetConsoleOutputCP_UTF8()
{
#if PN_PLATFORM_WINDOWS
    SetConsoleOutputCP(CP_UTF8);
#elif PN_PLATFORM_LINUX
#elif PN_PLATFORM_MACOS
#else
#endif
}
void pn_GetChar()
{
#if PN_PLATFORM_WINDOWS
    _getch();
#elif PN_PLATFORM_LINUX
#elif PN_PLATFORM_MACOS
#else
#endif
}

#endif

#endif
