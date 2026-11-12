// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_XKCOMPARE_H
#define XK_XKCOMPARE_H


#ifndef XK_CAT
#define XK_CAT_(a, b)   a##b
#define XK_CAT(a, b)    XK_CAT_(a, b)
#endif

#define xkcompare(T) XK_CAT(xk_GLOBAL_compare_, T)

#include <stdbool.h>
static inline int xkcompare(bool)(bool a, bool b) { return (a > b) - (a < b); }
static inline int xkcompare(char)(char a, char b) { return (a > b) - (a < b); }
static inline int xkcompare(short)(short a, short b) { return (a > b) - (a < b); }
static inline int xkcompare(int)(int a, int b) { return (a > b) - (a < b); }
static inline int xkcompare(long)(long a, long b) { return (a > b) - (a < b); }
static inline int xkcompare(float)(float a, float b) { return (a > b) - (a < b); }
static inline int xkcompare(double)(double a, double b) { return (a > b) - (a < b); }
#include <stdint.h>
static inline int xkcompare(int8_t)(int8_t a, int8_t b) { return (a > b) - (a < b); }
static inline int xkcompare(int16_t)(int16_t a, int16_t b) { return (a > b) - (a < b); }
static inline int xkcompare(int32_t)(int32_t a, int32_t b) { return (a > b) - (a < b); }
static inline int xkcompare(int64_t)(int64_t a, int64_t b) { return (a > b) - (a < b); }
static inline int xkcompare(uint8_t)(uint8_t a, uint8_t b) { return (a > b) - (a < b); }
static inline int xkcompare(uint16_t)(uint16_t a, uint16_t b) { return (a > b) - (a < b); }
static inline int xkcompare(uint32_t)(uint32_t a, uint32_t b) { return (a > b) - (a < b); }
static inline int xkcompare(uint64_t)(uint64_t a, uint64_t b) { return (a > b) - (a < b); }
static inline int xkcompare(intptr_t)(intptr_t a, intptr_t b) { return (a > b) - (a < b); }
static inline int xkcompare(uintptr_t)(uintptr_t a, uintptr_t b) { return (a > b) - (a < b); }
static inline int xkcompare(intmax_t)(intmax_t a, intmax_t b) { return (a > b) - (a < b); }
static inline int xkcompare(uintmax_t)(uintmax_t a, uintmax_t b) { return (a > b) - (a < b); }
static inline int xkcompare(int_least8_t)(int_least8_t a, int_least8_t b) { return (a > b) - (a < b); }
static inline int xkcompare(int_least16_t)(int_least16_t a, int_least16_t b) { return (a > b) - (a < b); }
static inline int xkcompare(int_least32_t)(int_least32_t a, int_least32_t b) { return (a > b) - (a < b); }
static inline int xkcompare(int_least64_t)(int_least64_t a, int_least64_t b) { return (a > b) - (a < b); }
static inline int xkcompare(uint_least8_t)(uint_least8_t a, uint_least8_t b) { return (a > b) - (a < b); }
static inline int xkcompare(uint_least16_t)(uint_least16_t a, uint_least16_t b) { return (a > b) - (a < b); }
static inline int xkcompare(uint_least32_t)(uint_least32_t a, uint_least32_t b) { return (a > b) - (a < b); }
static inline int xkcompare(uint_least64_t)(uint_least64_t a, uint_least64_t b) { return (a > b) - (a < b); }
static inline int xkcompare(int_fast8_t)(int_fast8_t a, int_fast8_t b) { return (a > b) - (a < b); }
static inline int xkcompare(int_fast16_t)(int_fast16_t a, int_fast16_t b) { return (a > b) - (a < b); }
static inline int xkcompare(int_fast32_t)(int_fast32_t a, int_fast32_t b) { return (a > b) - (a < b); }
static inline int xkcompare(int_fast64_t)(int_fast64_t a, int_fast64_t b) { return (a > b) - (a < b); }
static inline int xkcompare(uint_fast8_t)(uint_fast8_t a, uint_fast8_t b) { return (a > b) - (a < b); }
static inline int xkcompare(uint_fast16_t)(uint_fast16_t a, uint_fast16_t b) { return (a > b) - (a < b); }
static inline int xkcompare(uint_fast32_t)(uint_fast32_t a, uint_fast32_t b) { return (a > b) - (a < b); }
static inline int xkcompare(uint_fast64_t)(uint_fast64_t a, uint_fast64_t b) { return (a > b) - (a < b); }
#include <stddef.h>
static inline int xkcompare(size_t)(size_t a, size_t b) { return (a > b) - (a < b); }
static inline int xkcompare(ptrdiff_t)(ptrdiff_t a, ptrdiff_t b) { return (a > b) - (a < b); }
static inline int xkcompare(wchar_t)(wchar_t a, wchar_t b) { return (a > b) - (a < b); }

#endif
