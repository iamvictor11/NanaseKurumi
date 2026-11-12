// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_XKVECTOR_H
#define XK_XKVECTOR_H

#include "xkconf.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef XK_CAT
#define XK_CAT_(a, b)   a##b
#define XK_CAT(a, b)    XK_CAT_(a, b)
#endif

#define XK_PRIVATE_FLATMAP_NAME(NAME, T, H) \
    XK_CAT(XK_CAT(NAME, T), XK_CAT(_, H))

typedef struct xklisthead
{
    struct xklisthead* prev;
    struct xklisthead* next;
} xklisthead;
#define xklist(T, H) XK_PRIVATE_FLATMAP_NAME(xk_DETAIL_list_, T, H)

#endif