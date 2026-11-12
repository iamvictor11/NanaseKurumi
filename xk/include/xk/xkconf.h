// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_XKCONF_H
#define XK_XKCONF_H

#ifndef xkrealloc
#define xkrealloc   realloc
#endif
#ifndef xkfree
#define xkfree      free
#endif

#ifndef xkabort
#define xkabort     abort
#endif

#ifndef xkassert
#define xkassert    assert
#endif

#ifdef __cplusplus
#   define xkrestrict __restrict
#elif defined(_MSC_VER)
#   define xkrestrict __restrict
#else
#   define xkrestrict restrict
#endif

#endif
