// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_XKEQUAL_H
#define XK_XKEQUAL_H

#ifndef XK_CAT
#define XK_CAT_(a, b)   a##b
#define XK_CAT(a, b)    XK_CAT_(a, b)
#endif

#define xkequal(T) XK_CAT(xk_GLOBAL_equal_, T)

#include <stdbool.h>
static inline bool xkequal(bool)(bool a, bool b) { return a == b; }
static inline bool xkequal(char)(char a, char b) { return a == b; }
static inline bool xkequal(short)(short a, short b) { return a == b; }
static inline bool xkequal(int)(int a, int b) { return a == b; }
static inline bool xkequal(long)(long a, long b) { return a == b; }
static inline bool xkequal(float)(float a, float b) { return a == b; }
static inline bool xkequal(double)(double a, double b) { return a == b; }
#include <stdint.h>
static inline bool xkequal(int8_t)(int8_t a, int8_t b) { return a == b; }
static inline bool xkequal(int16_t)(int16_t a, int16_t b) { return a == b; }
static inline bool xkequal(int32_t)(int32_t a, int32_t b) { return a == b; }
static inline bool xkequal(int64_t)(int64_t a, int64_t b) { return a == b; }
static inline bool xkequal(uint8_t)(uint8_t a, uint8_t b) { return a == b; }
static inline bool xkequal(uint16_t)(uint16_t a, uint16_t b) { return a == b; }
static inline bool xkequal(uint32_t)(uint32_t a, uint32_t b) { return a == b; }
static inline bool xkequal(uint64_t)(uint64_t a, uint64_t b) { return a == b; }
static inline bool xkequal(intptr_t)(intptr_t a, intptr_t b) { return a == b; }
static inline bool xkequal(uintptr_t)(uintptr_t a, uintptr_t b) { return a == b; }
static inline bool xkequal(intmax_t)(intmax_t a, intmax_t b) { return a == b; }
static inline bool xkequal(uintmax_t)(uintmax_t a, uintmax_t b) { return a == b; }
static inline bool xkequal(int_least8_t)(int_least8_t a, int_least8_t b) { return a == b; }
static inline bool xkequal(int_least16_t)(int_least16_t a, int_least16_t b) { return a == b; }
static inline bool xkequal(int_least32_t)(int_least32_t a, int_least32_t b) { return a == b; }
static inline bool xkequal(int_least64_t)(int_least64_t a, int_least64_t b) { return a == b; }
static inline bool xkequal(uint_least8_t)(uint_least8_t a, uint_least8_t b) { return a == b; }
static inline bool xkequal(uint_least16_t)(uint_least16_t a, uint_least16_t b) { return a == b; }
static inline bool xkequal(uint_least32_t)(uint_least32_t a, uint_least32_t b) { return a == b; }
static inline bool xkequal(uint_least64_t)(uint_least64_t a, uint_least64_t b) { return a == b; }
static inline bool xkequal(int_fast8_t)(int_fast8_t a, int_fast8_t b) { return a == b; }
static inline bool xkequal(int_fast16_t)(int_fast16_t a, int_fast16_t b) { return a == b; }
static inline bool xkequal(int_fast32_t)(int_fast32_t a, int_fast32_t b) { return a == b; }
static inline bool xkequal(int_fast64_t)(int_fast64_t a, int_fast64_t b) { return a == b; }
static inline bool xkequal(uint_fast8_t)(uint_fast8_t a, uint_fast8_t b) { return a == b; }
static inline bool xkequal(uint_fast16_t)(uint_fast16_t a, uint_fast16_t b) { return a == b; }
static inline bool xkequal(uint_fast32_t)(uint_fast32_t a, uint_fast32_t b) { return a == b; }
static inline bool xkequal(uint_fast64_t)(uint_fast64_t a, uint_fast64_t b) { return a == b; }
#include <stddef.h>
static inline bool xkequal(size_t)(size_t a, size_t b) { return a == b; }
static inline bool xkequal(ptrdiff_t)(ptrdiff_t a, ptrdiff_t b) { return a == b; }
static inline bool xkequal(wchar_t)(wchar_t a, wchar_t b) { return a == b; }

#endif
