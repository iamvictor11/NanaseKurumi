// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_XKHASH_H
#define XK_XKHASH_H

#ifndef XK_CAT
#define XK_CAT_(a, b)   a##b
#define XK_CAT(a, b)    XK_CAT_(a, b)
#endif

#define xkhash(T) XK_CAT(xk_GLOBAL_hash_, T)

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

static inline size_t xk_PRIVATE_hash_mix64(uint64_t x)
{
    x ^= x >> 33;
    x *= 0xFF51AFD7ED558CCDull;
    x ^= x >> 33;
    x *= 0xC4CEB9FE1A85EC53ull;
    x ^= x >> 33;
    return (size_t)x;
}

static inline size_t xkhash(bool)(bool v) { return v ? 1u : 0u; }
static inline size_t xkhash(char)(char v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(short)(short v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(int)(int v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(long)(long v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(float)(float v)
{
    if (v == 0.0f) v = 0.0f;
    uint32_t bits;
    memcpy(&bits, &v, sizeof bits);
    return xk_PRIVATE_hash_mix64((uint64_t)bits);
}
static inline size_t xkhash(double)(double v)
{
    if (v == 0.0) v = 0.0;
    uint64_t bits;
    memcpy(&bits, &v, sizeof bits);
    return xk_PRIVATE_hash_mix64(bits);
}
static inline size_t xkhash(int8_t)(int8_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(int16_t)(int16_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(int32_t)(int32_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(int64_t)(int64_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(uint8_t)(uint8_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(uint16_t)(uint16_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(uint32_t)(uint32_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(uint64_t)(uint64_t v) { return xk_PRIVATE_hash_mix64(v); }
static inline size_t xkhash(intptr_t)(intptr_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(uintptr_t)(uintptr_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(intmax_t)(intmax_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(uintmax_t)(uintmax_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(int_least8_t)(int_least8_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(int_least16_t)(int_least16_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(int_least32_t)(int_least32_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(int_least64_t)(int_least64_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(uint_least8_t)(uint_least8_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(uint_least16_t)(uint_least16_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(uint_least32_t)(uint_least32_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(uint_least64_t)(uint_least64_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(int_fast8_t)(int_fast8_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(int_fast16_t)(int_fast16_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(int_fast32_t)(int_fast32_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(int_fast64_t)(int_fast64_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(uint_fast8_t)(uint_fast8_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(uint_fast16_t)(uint_fast16_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(uint_fast32_t)(uint_fast32_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(uint_fast64_t)(uint_fast64_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(size_t)(size_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(ptrdiff_t)(ptrdiff_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }
static inline size_t xkhash(wchar_t)(wchar_t v) { return xk_PRIVATE_hash_mix64((uint64_t)v); }

#endif
