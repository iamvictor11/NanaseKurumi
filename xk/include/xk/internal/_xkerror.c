// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__XKERROR_C
#define XK_INTERNAL__XKERROR_C

#include "_xkerror.h"
#include <string.h>

#define XK_CAP_ 8
#define XK_LEN_ 256

static char g_errors[XK_CAP_][XK_LEN_] = { 0 };
static size_t g_errorCount = 0;
static char g_wranings[XK_CAP_][XK_LEN_] = { 0 };
static size_t g_wraningCount = 0;

size_t xkgeterrorcount(void)
{
    return g_errorCount;
}
const char* xkpoperror(void)
{
    if (g_errorCount == 0) return NULL;
    --g_errorCount;
    return g_errors[g_errorCount];
}
void xkpusherror(const char* msg)
{
    if (msg == NULL || g_errorCount >= XK_CAP_) return;
    strncpy(g_errors[g_errorCount], msg, XK_LEN_ - 1);
    g_errors[g_errorCount][XK_LEN_ - 1] = '\0';
    ++g_errorCount;
}
size_t xkgetwraningcount(void)
{
    return g_wraningCount;
}
const char* xkpopwraning(void)
{
    if (g_wraningCount == 0) return NULL;
    --g_wraningCount;
    return g_wranings[g_wraningCount];
}
void xkpushwraning(const char* msg)
{
    if (msg == NULL || g_wraningCount >= XK_CAP_) return;
    strncpy(g_wranings[g_wraningCount], msg, XK_LEN_ - 1);
    g_wranings[g_wraningCount][XK_LEN_ - 1] = '\0';
    ++g_wraningCount;
}

#undef XK_CAP_
#undef XK_LEN_

#endif
