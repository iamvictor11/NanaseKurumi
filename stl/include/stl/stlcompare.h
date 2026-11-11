// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef STL_STLCOMPARE_H
#define STL_STLCOMPARE_H


#ifndef STL_CAT
#define STL_CAT_(a, b)  a##b
#define STL_CAT(a, b)   STL_CAT_(a, b)
#endif

#define stlcompare(T) STL_CAT(stl_GLOBAL_compare_, T)

#include <stdbool.h>
static inline int stlcompare(bool)(bool a, bool b) { return (a > b) - (a < b); }
static inline int stlcompare(char)(char a, char b) { return (a > b) - (a < b); }
static inline int stlcompare(short)(short a, short b) { return (a > b) - (a < b); }
static inline int stlcompare(int)(int a, int b) { return (a > b) - (a < b); }
static inline int stlcompare(long)(long a, long b) { return (a > b) - (a < b); }
static inline int stlcompare(float)(float a, float b) { return (a > b) - (a < b); }
static inline int stlcompare(double)(double a, double b) { return (a > b) - (a < b); }
#include <stdint.h>
static inline int stlcompare(int8_t)(int8_t a, int8_t b) { return (a > b) - (a < b); }
static inline int stlcompare(int16_t)(int16_t a, int16_t b) { return (a > b) - (a < b); }
static inline int stlcompare(int32_t)(int32_t a, int32_t b) { return (a > b) - (a < b); }
static inline int stlcompare(int64_t)(int64_t a, int64_t b) { return (a > b) - (a < b); }
static inline int stlcompare(uint8_t)(uint8_t a, uint8_t b) { return (a > b) - (a < b); }
static inline int stlcompare(uint16_t)(uint16_t a, uint16_t b) { return (a > b) - (a < b); }
static inline int stlcompare(uint32_t)(uint32_t a, uint32_t b) { return (a > b) - (a < b); }
static inline int stlcompare(uint64_t)(uint64_t a, uint64_t b) { return (a > b) - (a < b); }
static inline int stlcompare(intptr_t)(intptr_t a, intptr_t b) { return (a > b) - (a < b); }
static inline int stlcompare(uintptr_t)(uintptr_t a, uintptr_t b) { return (a > b) - (a < b); }
static inline int stlcompare(intmax_t)(intmax_t a, intmax_t b) { return (a > b) - (a < b); }
static inline int stlcompare(uintmax_t)(uintmax_t a, uintmax_t b) { return (a > b) - (a < b); }
static inline int stlcompare(int_least8_t)(int_least8_t a, int_least8_t b) { return (a > b) - (a < b); }
static inline int stlcompare(int_least16_t)(int_least16_t a, int_least16_t b) { return (a > b) - (a < b); }
static inline int stlcompare(int_least32_t)(int_least32_t a, int_least32_t b) { return (a > b) - (a < b); }
static inline int stlcompare(int_least64_t)(int_least64_t a, int_least64_t b) { return (a > b) - (a < b); }
static inline int stlcompare(uint_least8_t)(uint_least8_t a, uint_least8_t b) { return (a > b) - (a < b); }
static inline int stlcompare(uint_least16_t)(uint_least16_t a, uint_least16_t b) { return (a > b) - (a < b); }
static inline int stlcompare(uint_least32_t)(uint_least32_t a, uint_least32_t b) { return (a > b) - (a < b); }
static inline int stlcompare(uint_least64_t)(uint_least64_t a, uint_least64_t b) { return (a > b) - (a < b); }
static inline int stlcompare(int_fast8_t)(int_fast8_t a, int_fast8_t b) { return (a > b) - (a < b); }
static inline int stlcompare(int_fast16_t)(int_fast16_t a, int_fast16_t b) { return (a > b) - (a < b); }
static inline int stlcompare(int_fast32_t)(int_fast32_t a, int_fast32_t b) { return (a > b) - (a < b); }
static inline int stlcompare(int_fast64_t)(int_fast64_t a, int_fast64_t b) { return (a > b) - (a < b); }
static inline int stlcompare(uint_fast8_t)(uint_fast8_t a, uint_fast8_t b) { return (a > b) - (a < b); }
static inline int stlcompare(uint_fast16_t)(uint_fast16_t a, uint_fast16_t b) { return (a > b) - (a < b); }
static inline int stlcompare(uint_fast32_t)(uint_fast32_t a, uint_fast32_t b) { return (a > b) - (a < b); }
static inline int stlcompare(uint_fast64_t)(uint_fast64_t a, uint_fast64_t b) { return (a > b) - (a < b); }
#include <stddef.h>
static inline int stlcompare(size_t)(size_t a, size_t b) { return (a > b) - (a < b); }
static inline int stlcompare(ptrdiff_t)(ptrdiff_t a, ptrdiff_t b) { return (a > b) - (a < b); }
static inline int stlcompare(wchar_t)(wchar_t a, wchar_t b) { return (a > b) - (a < b); }

#endif
