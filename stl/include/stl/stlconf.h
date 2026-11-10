// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef STL_STLCONF_H
#define STL_STLCONF_H

#ifndef stlrealloc
#define stlrealloc  realloc
#endif
#ifndef stlfree
#define stlfree     free
#endif

#ifndef stlabort
#define stlabort    abort
#endif

#ifndef stlassert
#define stlassert   assert
#endif

#ifdef __cplusplus
#   define stlrestrict __restrict
#elif defined(_MSC_VER)
#   define stlrestrict __restrict
#else
#   define stlrestrict restrict
#endif

#endif
