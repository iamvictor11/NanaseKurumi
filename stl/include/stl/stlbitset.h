// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef STL_STLBITSET_H
#define STL_STLBITSET_H

#include "stlconf.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#ifndef STL_BITSET_WORD
#define STL_BITSET_WORD uint64_t
#endif

#if defined(_MSC_VER) && !defined(__clang__)
#   include <intrin.h>
#endif

#ifndef STL_CAT
#define STL_CAT_(a, b)  a##b
#define STL_CAT(a, b)   STL_CAT_(a, b)
#endif

#define STL_PRIVATE_BITSET_WORD_WIDTH       (sizeof(STL_BITSET_WORD) * 8)
#define STL_PRIVATE_BITSET_WORD_COUNT(N)    (((N) + STL_PRIVATE_BITSET_WORD_WIDTH - 1) / STL_PRIVATE_BITSET_WORD_WIDTH)
#define STL_PRIVATE_BITSET_FULLWORD         (~(STL_BITSET_WORD)0)

static inline size_t stl_PRIVATE_bitset_popcount_word(STL_BITSET_WORD w)
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
        while (w) { w &= (STL_BITSET_WORD)(w - 1); ++c; }
        return c;
    }
#endif
}
static inline STL_BITSET_WORD stl_PRIVATE_bitset_mask(size_t lo, size_t hi)
{
    const size_t W = STL_PRIVATE_BITSET_WORD_WIDTH;
    STL_BITSET_WORD left  = (lo == 0)
        ? STL_PRIVATE_BITSET_FULLWORD
        : (STL_PRIVATE_BITSET_FULLWORD << lo);
    STL_BITSET_WORD right = (hi >= W)
        ? STL_PRIVATE_BITSET_FULLWORD
        : (((STL_BITSET_WORD)1 << hi) - 1);
    return left & right;
}

#define stlbitset(N)            STL_CAT(stl_DETAIL_bitset_, N)
#define stlbitsetget(N)         STL_CAT(stl_PUBLIC_bitset_get_, N)
#define stlbitsetset(N)         STL_CAT(stl_PUBLIC_bitset_set_, N)
#define stlbitsetreset(N)       STL_CAT(stl_PUBLIC_bitset_reset_, N)
#define stlbitsetflip(N)        STL_CAT(stl_PUBLIC_bitset_flip_, N)
#define stlbitsettest(N)        STL_CAT(stl_PUBLIC_bitset_test_, N)
#define stlbitsetsetall(N)      STL_CAT(stl_PUBLIC_bitset_setall_, N)
#define stlbitsetresetall(N)    STL_CAT(stl_PUBLIC_bitset_resetall_, N)
#define stlbitsetflipall(N)     STL_CAT(stl_PUBLIC_bitset_flipall_, N)
#define stlbitsetall(N)         STL_CAT(stl_PUBLIC_bitset_all_, N)
#define stlbitsetany(N)         STL_CAT(stl_PUBLIC_bitset_any_, N)
#define stlbitsetnone(N)        STL_CAT(stl_PUBLIC_bitset_none_, N)
#define stlbitsetcount(N)       STL_CAT(stl_PUBLIC_bitset_count_, N)
#define stlbitsetsize(N)        STL_CAT(stl_PUBLIC_bitset_size_, N)
#define stlbitsetcapacity(N)    STL_CAT(stl_PUBLIC_bitset_capacity_, N)
#define stlbitsetsetrange(N)    STL_CAT(stl_PUBLIC_bitset_setrange_, N)
#define stlbitsetresetrange(N)  STL_CAT(stl_PUBLIC_bitset_resetrange_, N)
#define stlbitsetfliprange(N)   STL_CAT(stl_PUBLIC_bitset_fliprange_, N)
#define stlbitsetand(N)         STL_CAT(stl_PUBLIC_bitset_and_, N)
#define stlbitsetor(N)          STL_CAT(stl_PUBLIC_bitset_or_, N)
#define stlbitsetxor(N)         STL_CAT(stl_PUBLIC_bitset_xor_, N)
#define stlbitsetnot(N)         STL_CAT(stl_PUBLIC_bitset_not_, N)
#define stlbitsetshl(N)         STL_CAT(stl_PUBLIC_bitset_shl_, N)
#define stlbitsetshr(N)         STL_CAT(stl_PUBLIC_bitset_shr_, N)

// MARK: inst
#define stlbitsetinst(N) \
    struct stlbitset(N) \
    { \
        STL_BITSET_WORD words[STL_PRIVATE_BITSET_WORD_COUNT(N) ? STL_PRIVATE_BITSET_WORD_COUNT(N) : 1]; \
    };

// MARK: decl
#define stlbitsetdecl(N, ATTR) \
    struct stlbitset(N); \
    typedef struct stlbitset(N) stlbitset(N); \
    ATTR int stlbitsetget(N)(const stlbitset(N)* me, size_t pos); \
    ATTR void stlbitsetset(N)(stlbitset(N)* me, size_t pos, int val); \
    ATTR void stlbitsetreset(N)(stlbitset(N)* me, size_t pos); \
    ATTR void stlbitsetflip(N)(stlbitset(N)* me, size_t pos); \
    ATTR int stlbitsettest(N)(const stlbitset(N)* me, size_t pos); \
    ATTR void stlbitsetsetall(N)(stlbitset(N)* me); \
    ATTR void stlbitsetresetall(N)(stlbitset(N)* me); \
    ATTR void stlbitsetflipall(N)(stlbitset(N)* me); \
    ATTR int stlbitsetall(N)(const stlbitset(N)* me); \
    ATTR int stlbitsetany(N)(const stlbitset(N)* me); \
    ATTR int stlbitsetnone(N)(const stlbitset(N)* me); \
    ATTR size_t stlbitsetcount(N)(const stlbitset(N)* me); \
    ATTR size_t stlbitsetsize(N)(const stlbitset(N)* me); \
    ATTR size_t stlbitsetcapacity(N)(const stlbitset(N)* me); \
    ATTR void stlbitsetsetrange(N)(stlbitset(N)* me, size_t start, size_t end); \
    ATTR void stlbitsetresetrange(N)(stlbitset(N)* me, size_t start, size_t end); \
    ATTR void stlbitsetfliprange(N)(stlbitset(N)* me, size_t start, size_t end); \
    ATTR stlbitset(N) stlbitsetand(N)(const stlbitset(N)* stlrestrict a, const stlbitset(N)* stlrestrict b); \
    ATTR stlbitset(N) stlbitsetor(N)(const stlbitset(N)* stlrestrict a, const stlbitset(N)* stlrestrict b); \
    ATTR stlbitset(N) stlbitsetxor(N)(const stlbitset(N)* stlrestrict a, const stlbitset(N)* stlrestrict b); \
    ATTR stlbitset(N) stlbitsetnot(N)(const stlbitset(N)* a); \
    ATTR stlbitset(N) stlbitsetshl(N)(const stlbitset(N)* me, size_t k); \
    ATTR stlbitset(N) stlbitsetshr(N)(const stlbitset(N)* me, size_t k);

// MARK: impl
#define stlbitsetimpl(N, ATTR) \
    ATTR int stlbitsetget(N)(const stlbitset(N)* me, size_t pos) \
    { \
        stlassert(pos < (N)); \
        return (int)((me->words[pos / STL_PRIVATE_BITSET_WORD_WIDTH] \
                    >> (pos % STL_PRIVATE_BITSET_WORD_WIDTH)) & 1); \
    } \
    ATTR void stlbitsetset(N)(stlbitset(N)* me, size_t pos, int val) \
    { \
        stlassert(pos < (N)); \
        size_t w = pos / STL_PRIVATE_BITSET_WORD_WIDTH; \
        size_t b = pos % STL_PRIVATE_BITSET_WORD_WIDTH; \
        if (val) me->words[w] |=  ((STL_BITSET_WORD)1 << b); \
        else me->words[w] &= ~((STL_BITSET_WORD)1 << b); \
    } \
    ATTR void stlbitsetreset(N)(stlbitset(N)* me, size_t pos) \
    { \
        stlassert(pos < (N)); \
        me->words[pos / STL_PRIVATE_BITSET_WORD_WIDTH] &= ~((STL_BITSET_WORD)1 << (pos % STL_PRIVATE_BITSET_WORD_WIDTH)); \
    } \
    ATTR void stlbitsetflip(N)(stlbitset(N)* me, size_t pos) \
    { \
        stlassert(pos < (N)); \
        me->words[pos / STL_PRIVATE_BITSET_WORD_WIDTH] ^= ((STL_BITSET_WORD)1 << (pos % STL_PRIVATE_BITSET_WORD_WIDTH)); \
    } \
    ATTR int stlbitsettest(N)(const stlbitset(N)* me, size_t pos) \
    { \
        stlassert(pos < (N)); \
        return (int)((me->words[pos / STL_PRIVATE_BITSET_WORD_WIDTH] >> (pos % STL_PRIVATE_BITSET_WORD_WIDTH)) & 1); \
    } \
    ATTR void stlbitsetsetall(N)(stlbitset(N)* me) \
    { \
        memset(me->words, 0xFF, sizeof(me->words)); \
        size_t rem = (N) % STL_PRIVATE_BITSET_WORD_WIDTH; \
        if (rem != 0) \
            me->words[STL_PRIVATE_BITSET_WORD_COUNT(N) - 1] &= stl_PRIVATE_bitset_mask(0, rem); \
    } \
    ATTR void stlbitsetresetall(N)(stlbitset(N)* me) \
    { \
        memset(me->words, 0, sizeof(me->words)); \
    } \
    ATTR void stlbitsetflipall(N)(stlbitset(N)* me) \
    { \
        size_t nw = STL_PRIVATE_BITSET_WORD_COUNT(N); \
        for (size_t i = 0; i < nw; ++i) \
            me->words[i] = ~me->words[i]; \
        size_t rem = (N) % STL_PRIVATE_BITSET_WORD_WIDTH; \
        if (rem != 0) \
            me->words[nw - 1] &= stl_PRIVATE_bitset_mask(0, rem); \
    } \
    ATTR int stlbitsetall(N)(const stlbitset(N)* me) \
    { \
        size_t nw = STL_PRIVATE_BITSET_WORD_COUNT(N); \
        for (size_t i = 0; i + 1 < nw; ++i) \
            if (me->words[i] != STL_PRIVATE_BITSET_FULLWORD) return 0; \
        if (nw > 0) \
        { \
            size_t rem = (N) % STL_PRIVATE_BITSET_WORD_WIDTH; \
            STL_BITSET_WORD mask = stl_PRIVATE_bitset_mask(0, rem ? rem : STL_PRIVATE_BITSET_WORD_WIDTH); \
            if ((me->words[nw - 1] & mask) != mask) return 0; \
        } \
        return 1; \
    } \
    ATTR int stlbitsetany(N)(const stlbitset(N)* me) \
    { \
        size_t nw = STL_PRIVATE_BITSET_WORD_COUNT(N); \
        for (size_t i = 0; i + 1 < nw; ++i) \
            if (me->words[i]) return 1; \
        if (nw > 0) \
        { \
            size_t rem = (N) % STL_PRIVATE_BITSET_WORD_WIDTH; \
            STL_BITSET_WORD mask = stl_PRIVATE_bitset_mask(0, rem ? rem : STL_PRIVATE_BITSET_WORD_WIDTH); \
            if (me->words[nw - 1] & mask) return 1; \
        } \
        return 0; \
    } \
    ATTR int stlbitsetnone(N)(const stlbitset(N)* me) \
    { \
        return !stlbitsetany(N)(me); \
    } \
    ATTR size_t stlbitsetcount(N)(const stlbitset(N)* me) \
    { \
        size_t total = 0; \
        size_t nw = STL_PRIVATE_BITSET_WORD_COUNT(N); \
        for (size_t i = 0; i + 1 < nw; ++i) \
            total += stl_PRIVATE_bitset_popcount_word(me->words[i]); \
        if (nw > 0) \
        { \
            size_t rem = (N) % STL_PRIVATE_BITSET_WORD_WIDTH; \
            STL_BITSET_WORD mask = stl_PRIVATE_bitset_mask(0, rem ? rem : STL_PRIVATE_BITSET_WORD_WIDTH); \
            total += stl_PRIVATE_bitset_popcount_word(me->words[nw - 1] & mask); \
        } \
        return total; \
    } \
    ATTR size_t stlbitsetsize(N)(const stlbitset(N)* me) \
    { \
        (void)me; \
        return (N); \
    } \
    ATTR size_t stlbitsetcapacity(N)(const stlbitset(N)* me) \
    { \
        (void)me; \
        return (N); \
    } \
    ATTR void stlbitsetsetrange(N)(stlbitset(N)* me, size_t start, size_t end) \
    { \
        if (start >= (N)) return; \
        if (end > (N)) end = (N); \
        if (start >= end) return; \
        const size_t W = STL_PRIVATE_BITSET_WORD_WIDTH; \
        size_t sw = start / W, sb = start % W; \
        size_t ew = (end - 1) / W, eb = (end - 1) % W + 1; \
        if (sw == ew) { me->words[sw] |= stl_PRIVATE_bitset_mask(sb, eb); return; } \
        me->words[sw] |= stl_PRIVATE_bitset_mask(sb, W); \
        for (size_t i = sw + 1; i < ew; ++i) \
            me->words[i] = STL_PRIVATE_BITSET_FULLWORD; \
        me->words[ew] |= stl_PRIVATE_bitset_mask(0, eb); \
    } \
    ATTR void stlbitsetresetrange(N)(stlbitset(N)* me, size_t start, size_t end) \
    { \
        if (start >= (N)) return; \
        if (end > (N)) end = (N); \
        if (start >= end) return; \
        const size_t W = STL_PRIVATE_BITSET_WORD_WIDTH; \
        size_t sw = start / W, sb = start % W; \
        size_t ew = (end - 1) / W, eb = (end - 1) % W + 1; \
        if (sw == ew) { me->words[sw] &= ~stl_PRIVATE_bitset_mask(sb, eb); return; } \
        me->words[sw] &= ~stl_PRIVATE_bitset_mask(sb, W); \
        for (size_t i = sw + 1; i < ew; ++i) \
            me->words[i] = 0; \
        me->words[ew] &= ~stl_PRIVATE_bitset_mask(0, eb); \
    } \
    ATTR void stlbitsetfliprange(N)(stlbitset(N)* me, size_t start, size_t end) \
    { \
        if (start >= (N)) return; \
        if (end > (N)) end = (N); \
        if (start >= end) return; \
        const size_t W = STL_PRIVATE_BITSET_WORD_WIDTH; \
        size_t sw = start / W, sb = start % W; \
        size_t ew = (end - 1) / W, eb = (end - 1) % W + 1; \
        if (sw == ew) { me->words[sw] ^= stl_PRIVATE_bitset_mask(sb, eb); return; } \
        me->words[sw] ^= stl_PRIVATE_bitset_mask(sb, W); \
        for (size_t i = sw + 1; i < ew; ++i) \
            me->words[i] = ~me->words[i]; \
        me->words[ew] ^= stl_PRIVATE_bitset_mask(0, eb); \
    } \
    ATTR stlbitset(N) stlbitsetand(N)(const stlbitset(N)* stlrestrict a, \
                                      const stlbitset(N)* stlrestrict b) \
    { \
        stlbitset(N) r; \
        memset(&r, 0, sizeof r); \
        size_t nw = STL_PRIVATE_BITSET_WORD_COUNT(N); \
        for (size_t i = 0; i < nw; ++i) \
            r.words[i] = a->words[i] & b->words[i]; \
        return r; \
    } \
    ATTR stlbitset(N) stlbitsetor(N)(const stlbitset(N)* stlrestrict a, \
                                     const stlbitset(N)* stlrestrict b) \
    { \
        stlbitset(N) r; \
        memset(&r, 0, sizeof r); \
        size_t nw = STL_PRIVATE_BITSET_WORD_COUNT(N); \
        for (size_t i = 0; i < nw; ++i) \
            r.words[i] = a->words[i] | b->words[i]; \
        return r; \
    } \
    ATTR stlbitset(N) stlbitsetxor(N)(const stlbitset(N)* stlrestrict a, \
                                      const stlbitset(N)* stlrestrict b) \
    { \
        stlbitset(N) r; \
        memset(&r, 0, sizeof r); \
        size_t nw = STL_PRIVATE_BITSET_WORD_COUNT(N); \
        for (size_t i = 0; i < nw; ++i) \
            r.words[i] = a->words[i] ^ b->words[i]; \
        return r; \
    } \
    ATTR stlbitset(N) stlbitsetnot(N)(const stlbitset(N)* a) \
    { \
        stlbitset(N) r; \
        memset(&r, 0, sizeof r); \
        size_t nw = STL_PRIVATE_BITSET_WORD_COUNT(N); \
        for (size_t i = 0; i < nw; ++i) \
            r.words[i] = ~a->words[i]; \
        size_t rem = (N) % STL_PRIVATE_BITSET_WORD_WIDTH; \
        if (rem != 0) \
            r.words[nw - 1] &= stl_PRIVATE_bitset_mask(0, rem); \
        return r; \
    } \
    ATTR stlbitset(N) stlbitsetshl(N)(const stlbitset(N)* me, size_t k) \
    { \
        stlbitset(N) r; \
        memset(&r, 0, sizeof r); \
        size_t nw = STL_PRIVATE_BITSET_WORD_COUNT(N); \
        if (k == 0) { memcpy(&r, me, sizeof r); return r; } \
        if (k >= (N)) return r; \
        size_t ws = k / STL_PRIVATE_BITSET_WORD_WIDTH; \
        size_t bs = k % STL_PRIVATE_BITSET_WORD_WIDTH; \
        for (size_t i = 0; i < nw; ++i) \
        { \
            STL_BITSET_WORD v = 0; \
            if (i >= ws) \
            { \
                size_t src = i - ws; \
                v = me->words[src] << bs; \
                if (bs > 0 && src > 0) \
                    v |= me->words[src - 1] >> (STL_PRIVATE_BITSET_WORD_WIDTH - bs); \
            } \
            r.words[i] = v; \
        } \
        size_t rem = (N) % STL_PRIVATE_BITSET_WORD_WIDTH; \
        if (rem != 0) \
            r.words[nw - 1] &= stl_PRIVATE_bitset_mask(0, rem); \
        return r; \
    } \
    ATTR stlbitset(N) stlbitsetshr(N)(const stlbitset(N)* me, size_t k) \
    { \
        stlbitset(N) r; \
        memset(&r, 0, sizeof r); \
        size_t nw = STL_PRIVATE_BITSET_WORD_COUNT(N); \
        if (k == 0) { memcpy(&r, me, sizeof r); return r; } \
        if (k >= (N)) return r; \
        size_t ws = k / STL_PRIVATE_BITSET_WORD_WIDTH; \
        size_t bs = k % STL_PRIVATE_BITSET_WORD_WIDTH; \
        for (size_t i = 0; i < nw; ++i) \
        { \
            STL_BITSET_WORD v = 0; \
            size_t src = i + ws; \
            if (src < nw) \
            { \
                v = me->words[src] >> bs; \
                if (bs > 0 && src + 1 < nw) \
                    v |= me->words[src + 1] << (STL_PRIVATE_BITSET_WORD_WIDTH - bs); \
            } \
            r.words[i] = v; \
        } \
        return r; \
    }

#endif
