// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_XKBITSET_H
#define XK_XKBITSET_H

#include "xkconf.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#ifndef XK_BITSET_WORD
#define XK_BITSET_WORD uint64_t
#endif

#if defined(_MSC_VER) && !defined(__clang__)
#   include <intrin.h>
#endif

#ifndef XK_CAT
#define XK_CAT_(a, b)   a##b
#define XK_CAT(a, b)    XK_CAT_(a, b)
#endif

#define XK_PRIVATE_BITSET_WORD_WIDTH    (sizeof(XK_BITSET_WORD) * 8)
#define XK_PRIVATE_BITSET_WORD_COUNT(N) (((N) + XK_PRIVATE_BITSET_WORD_WIDTH - 1) / XK_PRIVATE_BITSET_WORD_WIDTH)
#define XK_PRIVATE_BITSET_FULLWORD      (~(XK_BITSET_WORD)0)

static inline size_t xk_PRIVATE_bitset_popcount_word(XK_BITSET_WORD w)
{
#if defined(__GNUC__) || defined(__clang__)
    if (sizeof(w) <= sizeof(unsigned))
        return (size_t)__builtin_popcount((unsigned)w);
    if (sizeof(w) <= sizeof(unsigned long))
        return (size_t)__builtin_popcountl((unsigned long)w);
    return (size_t)__builtin_popcountll((unsigned long long)w);
#elif defined(_MSC_VER)
    if (sizeof(w) <= sizeof(unsigned int))
        return (size_t)__popcnt((unsigned int)w);
#   if defined(_M_X64) || defined(_M_ARM64)
    if (sizeof(w) <= sizeof(unsigned __int64))
        return (size_t)__popcnt64((unsigned __int64)w);
#   endif
    {
        size_t c = 0;
        unsigned __int64 x = (unsigned __int64)w;
        while (x) { x &= x - 1; ++c; }
        return c;
    }
#else
    {
        size_t c = 0;
        while (w) { w &= (XK_BITSET_WORD)(w - 1); ++c; }
        return c;
    }
#endif
}
static inline XK_BITSET_WORD xk_PRIVATE_bitset_mask(size_t lo, size_t hi)
{
    const size_t W = XK_PRIVATE_BITSET_WORD_WIDTH;
    XK_BITSET_WORD left  = (lo == 0)
        ? XK_PRIVATE_BITSET_FULLWORD
        : (XK_PRIVATE_BITSET_FULLWORD << lo);
    XK_BITSET_WORD right = (hi >= W)
        ? XK_PRIVATE_BITSET_FULLWORD
        : (((XK_BITSET_WORD)1 << hi) - 1);
    return left & right;
}

#define xkbitset(N)             XK_CAT(xk_DETAIL_bitset_, N)
#define xkbitsetget(N)          XK_CAT(xk_PUBLIC_bitset_get_, N)
#define xkbitsetset(N)          XK_CAT(xk_PUBLIC_bitset_set_, N)
#define xkbitsetreset(N)        XK_CAT(xk_PUBLIC_bitset_reset_, N)
#define xkbitsetflip(N)         XK_CAT(xk_PUBLIC_bitset_flip_, N)
#define xkbitsettest(N)         XK_CAT(xk_PUBLIC_bitset_test_, N)
#define xkbitsetsetall(N)       XK_CAT(xk_PUBLIC_bitset_setall_, N)
#define xkbitsetresetall(N)     XK_CAT(xk_PUBLIC_bitset_resetall_, N)
#define xkbitsetflipall(N)      XK_CAT(xk_PUBLIC_bitset_flipall_, N)
#define xkbitsetall(N)          XK_CAT(xk_PUBLIC_bitset_all_, N)
#define xkbitsetany(N)          XK_CAT(xk_PUBLIC_bitset_any_, N)
#define xkbitsetnone(N)         XK_CAT(xk_PUBLIC_bitset_none_, N)
#define xkbitsetcount(N)        XK_CAT(xk_PUBLIC_bitset_count_, N)
#define xkbitsetsize(N)         XK_CAT(xk_PUBLIC_bitset_size_, N)
#define xkbitsetcapacity(N)     XK_CAT(xk_PUBLIC_bitset_capacity_, N)
#define xkbitsetsetrange(N)     XK_CAT(xk_PUBLIC_bitset_setrange_, N)
#define xkbitsetresetrange(N)   XK_CAT(xk_PUBLIC_bitset_resetrange_, N)
#define xkbitsetfliprange(N)    XK_CAT(xk_PUBLIC_bitset_fliprange_, N)
#define xkbitsetand(N)          XK_CAT(xk_PUBLIC_bitset_and_, N)
#define xkbitsetor(N)           XK_CAT(xk_PUBLIC_bitset_or_, N)
#define xkbitsetxor(N)          XK_CAT(xk_PUBLIC_bitset_xor_, N)
#define xkbitsetnot(N)          XK_CAT(xk_PUBLIC_bitset_not_, N)
#define xkbitsetshl(N)          XK_CAT(xk_PUBLIC_bitset_shl_, N)
#define xkbitsetshr(N)          XK_CAT(xk_PUBLIC_bitset_shr_, N)

// MARK: inst
#define xkbitsetinst(N) \
    struct xkbitset(N) \
    { \
        XK_BITSET_WORD words[XK_PRIVATE_BITSET_WORD_COUNT(N) ? XK_PRIVATE_BITSET_WORD_COUNT(N) : 1]; \
    };

// MARK: decl
#define xkbitsetdecl(N, ATTR) \
    struct xkbitset(N); \
    typedef struct xkbitset(N) xkbitset(N); \
    ATTR int xkbitsetget(N)(const xkbitset(N)* me, size_t pos); \
    ATTR void xkbitsetset(N)(xkbitset(N)* me, size_t pos, int val); \
    ATTR void xkbitsetreset(N)(xkbitset(N)* me, size_t pos); \
    ATTR void xkbitsetflip(N)(xkbitset(N)* me, size_t pos); \
    ATTR int xkbitsettest(N)(const xkbitset(N)* me, size_t pos); \
    ATTR void xkbitsetsetall(N)(xkbitset(N)* me); \
    ATTR void xkbitsetresetall(N)(xkbitset(N)* me); \
    ATTR void xkbitsetflipall(N)(xkbitset(N)* me); \
    ATTR int xkbitsetall(N)(const xkbitset(N)* me); \
    ATTR int xkbitsetany(N)(const xkbitset(N)* me); \
    ATTR int xkbitsetnone(N)(const xkbitset(N)* me); \
    ATTR size_t xkbitsetcount(N)(const xkbitset(N)* me); \
    ATTR size_t xkbitsetsize(N)(const xkbitset(N)* me); \
    ATTR size_t xkbitsetcapacity(N)(const xkbitset(N)* me); \
    ATTR void xkbitsetsetrange(N)(xkbitset(N)* me, size_t start, size_t end); \
    ATTR void xkbitsetresetrange(N)(xkbitset(N)* me, size_t start, size_t end); \
    ATTR void xkbitsetfliprange(N)(xkbitset(N)* me, size_t start, size_t end); \
    ATTR xkbitset(N) xkbitsetand(N)(const xkbitset(N)* xkrestrict a, const xkbitset(N)* xkrestrict b); \
    ATTR xkbitset(N) xkbitsetor(N)(const xkbitset(N)* xkrestrict a, const xkbitset(N)* xkrestrict b); \
    ATTR xkbitset(N) xkbitsetxor(N)(const xkbitset(N)* xkrestrict a, const xkbitset(N)* xkrestrict b); \
    ATTR xkbitset(N) xkbitsetnot(N)(const xkbitset(N)* a); \
    ATTR xkbitset(N) xkbitsetshl(N)(const xkbitset(N)* me, size_t k); \
    ATTR xkbitset(N) xkbitsetshr(N)(const xkbitset(N)* me, size_t k);

// MARK: impl
#define xkbitsetimpl(N, ATTR) \
    ATTR int xkbitsetget(N)(const xkbitset(N)* me, size_t pos) \
    { \
        xkassert(pos < (N)); \
        return (int)((me->words[pos / XK_PRIVATE_BITSET_WORD_WIDTH] \
                    >> (pos % XK_PRIVATE_BITSET_WORD_WIDTH)) & 1); \
    } \
    ATTR void xkbitsetset(N)(xkbitset(N)* me, size_t pos, int val) \
    { \
        xkassert(pos < (N)); \
        size_t w = pos / XK_PRIVATE_BITSET_WORD_WIDTH; \
        size_t b = pos % XK_PRIVATE_BITSET_WORD_WIDTH; \
        if (val) me->words[w] |=  ((XK_BITSET_WORD)1 << b); \
        else me->words[w] &= ~((XK_BITSET_WORD)1 << b); \
    } \
    ATTR void xkbitsetreset(N)(xkbitset(N)* me, size_t pos) \
    { \
        xkassert(pos < (N)); \
        me->words[pos / XK_PRIVATE_BITSET_WORD_WIDTH] &= ~((XK_BITSET_WORD)1 << (pos % XK_PRIVATE_BITSET_WORD_WIDTH)); \
    } \
    ATTR void xkbitsetflip(N)(xkbitset(N)* me, size_t pos) \
    { \
        xkassert(pos < (N)); \
        me->words[pos / XK_PRIVATE_BITSET_WORD_WIDTH] ^= ((XK_BITSET_WORD)1 << (pos % XK_PRIVATE_BITSET_WORD_WIDTH)); \
    } \
    ATTR int xkbitsettest(N)(const xkbitset(N)* me, size_t pos) \
    { \
        xkassert(pos < (N)); \
        return (int)((me->words[pos / XK_PRIVATE_BITSET_WORD_WIDTH] >> (pos % XK_PRIVATE_BITSET_WORD_WIDTH)) & 1); \
    } \
    ATTR void xkbitsetsetall(N)(xkbitset(N)* me) \
    { \
        memset(me->words, 0xFF, sizeof(me->words)); \
        size_t rem = (N) % XK_PRIVATE_BITSET_WORD_WIDTH; \
        if (rem != 0) \
            me->words[XK_PRIVATE_BITSET_WORD_COUNT(N) - 1] &= xk_PRIVATE_bitset_mask(0, rem); \
    } \
    ATTR void xkbitsetresetall(N)(xkbitset(N)* me) \
    { \
        memset(me->words, 0, sizeof(me->words)); \
    } \
    ATTR void xkbitsetflipall(N)(xkbitset(N)* me) \
    { \
        size_t nw = XK_PRIVATE_BITSET_WORD_COUNT(N); \
        for (size_t i = 0; i < nw; ++i) \
            me->words[i] = ~me->words[i]; \
        size_t rem = (N) % XK_PRIVATE_BITSET_WORD_WIDTH; \
        if (rem != 0) \
            me->words[nw - 1] &= xk_PRIVATE_bitset_mask(0, rem); \
    } \
    ATTR int xkbitsetall(N)(const xkbitset(N)* me) \
    { \
        size_t nw = XK_PRIVATE_BITSET_WORD_COUNT(N); \
        for (size_t i = 0; i + 1 < nw; ++i) \
            if (me->words[i] != XK_PRIVATE_BITSET_FULLWORD) return 0; \
        if (nw > 0) \
        { \
            size_t rem = (N) % XK_PRIVATE_BITSET_WORD_WIDTH; \
            XK_BITSET_WORD mask = xk_PRIVATE_bitset_mask(0, rem ? rem : XK_PRIVATE_BITSET_WORD_WIDTH); \
            if ((me->words[nw - 1] & mask) != mask) return 0; \
        } \
        return 1; \
    } \
    ATTR int xkbitsetany(N)(const xkbitset(N)* me) \
    { \
        size_t nw = XK_PRIVATE_BITSET_WORD_COUNT(N); \
        for (size_t i = 0; i + 1 < nw; ++i) \
            if (me->words[i]) return 1; \
        if (nw > 0) \
        { \
            size_t rem = (N) % XK_PRIVATE_BITSET_WORD_WIDTH; \
            XK_BITSET_WORD mask = xk_PRIVATE_bitset_mask(0, rem ? rem : XK_PRIVATE_BITSET_WORD_WIDTH); \
            if (me->words[nw - 1] & mask) return 1; \
        } \
        return 0; \
    } \
    ATTR int xkbitsetnone(N)(const xkbitset(N)* me) \
    { \
        return !xkbitsetany(N)(me); \
    } \
    ATTR size_t xkbitsetcount(N)(const xkbitset(N)* me) \
    { \
        size_t total = 0; \
        size_t nw = XK_PRIVATE_BITSET_WORD_COUNT(N); \
        for (size_t i = 0; i + 1 < nw; ++i) \
            total += xk_PRIVATE_bitset_popcount_word(me->words[i]); \
        if (nw > 0) \
        { \
            size_t rem = (N) % XK_PRIVATE_BITSET_WORD_WIDTH; \
            XK_BITSET_WORD mask = xk_PRIVATE_bitset_mask(0, rem ? rem : XK_PRIVATE_BITSET_WORD_WIDTH); \
            total += xk_PRIVATE_bitset_popcount_word(me->words[nw - 1] & mask); \
        } \
        return total; \
    } \
    ATTR size_t xkbitsetsize(N)(const xkbitset(N)* me) \
    { \
        (void)me; \
        return (N); \
    } \
    ATTR size_t xkbitsetcapacity(N)(const xkbitset(N)* me) \
    { \
        (void)me; \
        return (N); \
    } \
    ATTR void xkbitsetsetrange(N)(xkbitset(N)* me, size_t start, size_t end) \
    { \
        if (start >= (N)) return; \
        if (end > (N)) end = (N); \
        if (start >= end) return; \
        const size_t W = XK_PRIVATE_BITSET_WORD_WIDTH; \
        size_t sw = start / W, sb = start % W; \
        size_t ew = (end - 1) / W, eb = (end - 1) % W + 1; \
        if (sw == ew) { me->words[sw] |= xk_PRIVATE_bitset_mask(sb, eb); return; } \
        me->words[sw] |= xk_PRIVATE_bitset_mask(sb, W); \
        for (size_t i = sw + 1; i < ew; ++i) \
            me->words[i] = XK_PRIVATE_BITSET_FULLWORD; \
        me->words[ew] |= xk_PRIVATE_bitset_mask(0, eb); \
    } \
    ATTR void xkbitsetresetrange(N)(xkbitset(N)* me, size_t start, size_t end) \
    { \
        if (start >= (N)) return; \
        if (end > (N)) end = (N); \
        if (start >= end) return; \
        const size_t W = XK_PRIVATE_BITSET_WORD_WIDTH; \
        size_t sw = start / W, sb = start % W; \
        size_t ew = (end - 1) / W, eb = (end - 1) % W + 1; \
        if (sw == ew) { me->words[sw] &= ~xk_PRIVATE_bitset_mask(sb, eb); return; } \
        me->words[sw] &= ~xk_PRIVATE_bitset_mask(sb, W); \
        for (size_t i = sw + 1; i < ew; ++i) \
            me->words[i] = 0; \
        me->words[ew] &= ~xk_PRIVATE_bitset_mask(0, eb); \
    } \
    ATTR void xkbitsetfliprange(N)(xkbitset(N)* me, size_t start, size_t end) \
    { \
        if (start >= (N)) return; \
        if (end > (N)) end = (N); \
        if (start >= end) return; \
        const size_t W = XK_PRIVATE_BITSET_WORD_WIDTH; \
        size_t sw = start / W, sb = start % W; \
        size_t ew = (end - 1) / W, eb = (end - 1) % W + 1; \
        if (sw == ew) { me->words[sw] ^= xk_PRIVATE_bitset_mask(sb, eb); return; } \
        me->words[sw] ^= xk_PRIVATE_bitset_mask(sb, W); \
        for (size_t i = sw + 1; i < ew; ++i) \
            me->words[i] = ~me->words[i]; \
        me->words[ew] ^= xk_PRIVATE_bitset_mask(0, eb); \
    } \
    ATTR xkbitset(N) xkbitsetand(N)(const xkbitset(N)* xkrestrict a, \
                                      const xkbitset(N)* xkrestrict b) \
    { \
        xkbitset(N) r; \
        memset(&r, 0, sizeof r); \
        size_t nw = XK_PRIVATE_BITSET_WORD_COUNT(N); \
        for (size_t i = 0; i < nw; ++i) \
            r.words[i] = a->words[i] & b->words[i]; \
        return r; \
    } \
    ATTR xkbitset(N) xkbitsetor(N)(const xkbitset(N)* xkrestrict a, \
                                     const xkbitset(N)* xkrestrict b) \
    { \
        xkbitset(N) r; \
        memset(&r, 0, sizeof r); \
        size_t nw = XK_PRIVATE_BITSET_WORD_COUNT(N); \
        for (size_t i = 0; i < nw; ++i) \
            r.words[i] = a->words[i] | b->words[i]; \
        return r; \
    } \
    ATTR xkbitset(N) xkbitsetxor(N)(const xkbitset(N)* xkrestrict a, \
                                      const xkbitset(N)* xkrestrict b) \
    { \
        xkbitset(N) r; \
        memset(&r, 0, sizeof r); \
        size_t nw = XK_PRIVATE_BITSET_WORD_COUNT(N); \
        for (size_t i = 0; i < nw; ++i) \
            r.words[i] = a->words[i] ^ b->words[i]; \
        return r; \
    } \
    ATTR xkbitset(N) xkbitsetnot(N)(const xkbitset(N)* a) \
    { \
        xkbitset(N) r; \
        memset(&r, 0, sizeof r); \
        size_t nw = XK_PRIVATE_BITSET_WORD_COUNT(N); \
        for (size_t i = 0; i < nw; ++i) \
            r.words[i] = ~a->words[i]; \
        size_t rem = (N) % XK_PRIVATE_BITSET_WORD_WIDTH; \
        if (rem != 0) \
            r.words[nw - 1] &= xk_PRIVATE_bitset_mask(0, rem); \
        return r; \
    } \
    ATTR xkbitset(N) xkbitsetshl(N)(const xkbitset(N)* me, size_t k) \
    { \
        xkbitset(N) r; \
        memset(&r, 0, sizeof r); \
        size_t nw = XK_PRIVATE_BITSET_WORD_COUNT(N); \
        if (k == 0) { memcpy(&r, me, sizeof r); return r; } \
        if (k >= (N)) return r; \
        size_t ws = k / XK_PRIVATE_BITSET_WORD_WIDTH; \
        size_t bs = k % XK_PRIVATE_BITSET_WORD_WIDTH; \
        for (size_t i = 0; i < nw; ++i) \
        { \
            XK_BITSET_WORD v = 0; \
            if (i >= ws) \
            { \
                size_t src = i - ws; \
                v = me->words[src] << bs; \
                if (bs > 0 && src > 0) \
                    v |= me->words[src - 1] >> (XK_PRIVATE_BITSET_WORD_WIDTH - bs); \
            } \
            r.words[i] = v; \
        } \
        size_t rem = (N) % XK_PRIVATE_BITSET_WORD_WIDTH; \
        if (rem != 0) \
            r.words[nw - 1] &= xk_PRIVATE_bitset_mask(0, rem); \
        return r; \
    } \
    ATTR xkbitset(N) xkbitsetshr(N)(const xkbitset(N)* me, size_t k) \
    { \
        xkbitset(N) r; \
        memset(&r, 0, sizeof r); \
        size_t nw = XK_PRIVATE_BITSET_WORD_COUNT(N); \
        if (k == 0) { memcpy(&r, me, sizeof r); return r; } \
        if (k >= (N)) return r; \
        size_t ws = k / XK_PRIVATE_BITSET_WORD_WIDTH; \
        size_t bs = k % XK_PRIVATE_BITSET_WORD_WIDTH; \
        for (size_t i = 0; i < nw; ++i) \
        { \
            XK_BITSET_WORD v = 0; \
            size_t src = i + ws; \
            if (src < nw) \
            { \
                v = me->words[src] >> bs; \
                if (bs > 0 && src + 1 < nw) \
                    v |= me->words[src + 1] << (XK_PRIVATE_BITSET_WORD_WIDTH - bs); \
            } \
            r.words[i] = v; \
        } \
        return r; \
    }

#endif
