// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef STL_HASH_H
#define STL_HASH_H


#ifndef STL_CAT
#define STL_CAT_(a, b)  a##b
#define STL_CAT(a, b)   STL_CAT_(a, b)
#endif

#define stlhash(T) STL_CAT(stl_GLOBAL_hash_, T)

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

static inline size_t stl_PRIVATE_hash_mix64(uint64_t x)
{
    x ^= x >> 33;
    x *= 0xFF51AFD7ED558CCDull;
    x ^= x >> 33;
    x *= 0xC4CEB9FE1A85EC53ull;
    x ^= x >> 33;
    return (size_t)x;
}

static inline size_t stlhash(bool)(bool a) { return a ? 1u : 0u; }
static inline size_t stlhash(char)(char a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(short)(short a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(int)(int a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(long)(long a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(float)(float a)
{
    if (a == 0.0f) a = 0.0f;
    uint32_t bits;
    memcpy(&bits, &a, sizeof bits);
    return stl_PRIVATE_hash_mix64((uint64_t)bits);
}
static inline size_t stlhash(double)(double a)
{
    if (a == 0.0) a = 0.0;
    uint64_t bits;
    memcpy(&bits, &a, sizeof bits);
    return stl_PRIVATE_hash_mix64(bits);
}
static inline size_t stlhash(int8_t)(int8_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(int16_t)(int16_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(int32_t)(int32_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(int64_t)(int64_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(uint8_t)(uint8_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(uint16_t)(uint16_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(uint32_t)(uint32_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(uint64_t)(uint64_t a) { return stl_PRIVATE_hash_mix64(a); }
static inline size_t stlhash(intptr_t)(intptr_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(uintptr_t)(uintptr_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(intmax_t)(intmax_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(uintmax_t)(uintmax_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(int_least8_t)(int_least8_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(int_least16_t)(int_least16_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(int_least32_t)(int_least32_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(int_least64_t)(int_least64_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(uint_least8_t)(uint_least8_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(uint_least16_t)(uint_least16_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(uint_least32_t)(uint_least32_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(uint_least64_t)(uint_least64_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(int_fast8_t)(int_fast8_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(int_fast16_t)(int_fast16_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(int_fast32_t)(int_fast32_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(int_fast64_t)(int_fast64_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(uint_fast8_t)(uint_fast8_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(uint_fast16_t)(uint_fast16_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(uint_fast32_t)(uint_fast32_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(uint_fast64_t)(uint_fast64_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(size_t)(size_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(ptrdiff_t)(ptrdiff_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }
static inline size_t stlhash(wchar_t)(wchar_t a) { return stl_PRIVATE_hash_mix64((uint64_t)a); }

#endif
