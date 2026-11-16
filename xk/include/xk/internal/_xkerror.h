// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__XKERROR_H
#define XK_INTERNAL__XKERROR_H

#include <stddef.h>

size_t xkgeterrorcount(void);
const char* xkpoperror(void);
void xkpusherror(const char* msg);
size_t xkgetwraningcount(void);
const char* xkpopwraning(void);
void xkpushwraning(const char* msg);

#endif
