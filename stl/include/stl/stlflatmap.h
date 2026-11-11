// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef STL_STLFLATMAP_H
#define STL_STLFLATMAP_H

#include "stlconf.h"
#include "stlcompare.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define STL_PRIVATE_FLATMAP_MIN_CAPACITY 8

#ifndef STL_CAT
#define STL_CAT_(a, b)  a##b
#define STL_CAT(a, b)   STL_CAT_(a, b)
#endif

#define STL_PRIVATE_FLATMAP_NAME(NAME, K, V) \
    STL_CAT(STL_CAT(NAME, K), STL_CAT(_, V))

#define stlflatmap(K, V)            STL_PRIVATE_FLATMAP_NAME(stl_DETAIL_flatmap_, K, V)
#define stlflatmapentry(K, V)       STL_PRIVATE_FLATMAP_NAME(stl_DETAIL_flatmap_entry_, K, V)
#define stlflatmapinit(K, V)        STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_init_, K, V)
#define stlflatmapfree(K, V)        STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_free_, K, V)
#define stlflatmapreserve(K, V)     STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_reserve_, K, V)
#define stlflatmapshrink(K, V)      STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_shrink_, K, V)
#define stlflatmapset(K, V)         STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_set_, K, V)
#define stlflatmapfind(K, V)        STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_find_, K, V)
#define stlflatmapfind_const(K, V)  STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_find_const_, K, V)
#define stlflatmapat(K, V)          STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_at_, K, V)
#define stlflatmapat_const(K, V)    STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_at_const_, K, V)
#define stlflatmaperase(K, V)       STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_erase_, K, V)
#define stlflatmapclear(K, V)       STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_clear_, K, V)
#define stlflatmapcopy(K, V)        STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_copy_, K, V)
#define stlflatmapclone(K, V)       STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_clone_, K, V)
#define stlflatmapmove(K, V)        STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_move_, K, V)
#define stlflatmapswap(K, V)        STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_swap_, K, V)
#define stlflatmapcontains(K, V)    STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_contains_, K, V)
#define stlflatmapsize(K, V)        STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_size_, K, V)
#define stlflatmapcapacity(K, V)    STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_capacity_, K, V)
#define stlflatmapempty(K, V)       STL_PRIVATE_FLATMAP_NAME(stl_PUBLIC_flatmap_empty_, K, V)

// MARK: inst
#define stlflatmapinst(K, V) \
    struct stlflatmapentry(K, V) \
    { \
        K key; \
        V value; \
    }; \
    struct stlflatmap(K, V) \
    { \
        struct stlflatmapentry(K, V)* data; \
        size_t size; \
        size_t capacity; \
    };

// MARK: decl
#define stlflatmapdecl(K, V, ATTR) \
    struct stlflatmapentry(K, V); \
    typedef struct stlflatmapentry(K, V) stlflatmapentry(K, V); \
    struct stlflatmap(K, V); \
    typedef struct stlflatmap(K, V) stlflatmap(K, V); \
    ATTR void stlflatmapinit(K, V)(stlflatmap(K, V)* me, size_t cap); \
    ATTR void stlflatmapfree(K, V)(stlflatmap(K, V)* me); \
    ATTR void stlflatmapreserve(K, V)(stlflatmap(K, V)* me, size_t cap); \
    ATTR void stlflatmapshrink(K, V)(stlflatmap(K, V)* me); \
    ATTR void stlflatmapset(K, V)(stlflatmap(K, V)* me, K key, V value); \
    ATTR V* stlflatmapfind(K, V)(stlflatmap(K, V)* me, K key); \
    ATTR const V* stlflatmapfind_const(K, V)(const stlflatmap(K, V)* me, K key); \
    ATTR V* stlflatmapat(K, V)(stlflatmap(K, V)* me, K key); \
    ATTR const V* stlflatmapat_const(K, V)(const stlflatmap(K, V)* me, K key); \
    ATTR int stlflatmaperase(K, V)(stlflatmap(K, V)* me, K key); \
    ATTR void stlflatmapclear(K, V)(stlflatmap(K, V)* me); \
    ATTR void stlflatmapcopy(K, V)(stlflatmap(K, V)* dst, const stlflatmap(K, V)* src); \
    ATTR stlflatmap(K, V) stlflatmapclone(K, V)(const stlflatmap(K, V)* me); \
    ATTR void stlflatmapmove(K, V)(stlflatmap(K, V)* dst, stlflatmap(K, V)* src); \
    ATTR void stlflatmapswap(K, V)(stlflatmap(K, V)* a, stlflatmap(K, V)* b); \
    ATTR int stlflatmapcontains(K, V)(const stlflatmap(K, V)* me, K key); \
    ATTR size_t stlflatmapsize(K, V)(const stlflatmap(K, V)* me); \
    ATTR size_t stlflatmapcapacity(K, V)(const stlflatmap(K, V)* me); \
    ATTR int stlflatmapempty(K, V)(const stlflatmap(K, V)* me);

// MARK: impl
#define stlflatmapimpl(K, V, ATTR) \
    static inline size_t STL_PRIVATE_FLATMAP_NAME(stl_PRIVATE_flatmap_lowerbound_, K, V)(const stlflatmap(K, V)* me, K key) \
    { \
        size_t lo = 0; \
        size_t hi = me->size; \
        while (lo < hi) \
        { \
            size_t mid = lo + (hi - lo) / 2; \
            if (stlcompare(K)(me->data[mid].key, key) < 0) \
                lo = mid + 1; \
            else \
                hi = mid; \
        } \
        return lo; \
    } \
    ATTR void stlflatmapinit(K, V)(stlflatmap(K, V)* me, size_t cap) \
    { \
        me->data = NULL; \
        me->size = 0; \
        me->capacity = 0; \
        if (cap) stlflatmapreserve(K, V)(me, cap); \
    } \
    ATTR void stlflatmapfree(K, V)(stlflatmap(K, V)* me) \
    { \
        stlfree(me->data); \
        me->data = NULL; \
        me->size = 0; \
        me->capacity = 0; \
    } \
    ATTR void stlflatmapreserve(K, V)(stlflatmap(K, V)* me, size_t cap) \
    { \
        if (cap <= me->capacity) return; \
        const size_t maxcap = (size_t)-1 / sizeof(stlflatmapentry(K, V)); \
        if (cap > maxcap) stlabort(); \
        size_t nc = me->capacity \
            ? me->capacity \
            : (cap < STL_PRIVATE_FLATMAP_MIN_CAPACITY ? STL_PRIVATE_FLATMAP_MIN_CAPACITY : cap); \
        if (nc < cap) \
        { \
            if (nc > maxcap / 2) nc = cap; \
            else \
            { \
                nc *= 2; \
                if (nc < cap) nc = cap; \
            } \
        } \
        stlflatmapentry(K, V)* p = \
            (stlflatmapentry(K, V)*)stlrealloc(me->data, nc * sizeof(stlflatmapentry(K, V))); \
        if (!p) stlabort(); \
        me->data = p; \
        me->capacity = nc; \
    } \
    ATTR void stlflatmapshrink(K, V)(stlflatmap(K, V)* me) \
    { \
        if (me->size == me->capacity) return; \
        if (me->size == 0) \
        { \
            stlfree(me->data); \
            me->data = NULL; \
            me->capacity = 0; \
        } \
        else \
        { \
            stlflatmapentry(K, V)* p = \
                (stlflatmapentry(K, V)*)stlrealloc(me->data, me->size * sizeof(stlflatmapentry(K, V))); \
            if (!p) stlabort(); \
            me->data = p; \
            me->capacity = me->size; \
        } \
    } \
    ATTR void stlflatmapset(K, V)(stlflatmap(K, V)* me, K key, V value) \
    { \
        size_t i = STL_PRIVATE_FLATMAP_NAME(stl_PRIVATE_flatmap_lowerbound_, K, V)(me, key); \
        if (i < me->size && stlcompare(K)(me->data[i].key, key) == 0) \
        { \
            me->data[i].value = value; \
            return; \
        } \
        if (me->size == me->capacity) \
            stlflatmapreserve(K, V)(me, me->size + 1); \
        if (i < me->size) \
            memmove(&me->data[i + 1], &me->data[i], \
                (me->size - i) * sizeof(stlflatmapentry(K, V))); \
        me->data[i].key = key; \
        me->data[i].value = value; \
        ++me->size; \
    } \
    ATTR V* stlflatmapfind(K, V)(stlflatmap(K, V)* me, K key) \
    { \
        size_t i = STL_PRIVATE_FLATMAP_NAME(stl_PRIVATE_flatmap_lowerbound_, K, V)(me, key); \
        if (i >= me->size || stlcompare(K)(me->data[i].key, key) != 0) \
            return NULL; \
        return &me->data[i].value; \
    } \
    ATTR const V* stlflatmapfind_const(K, V)(const stlflatmap(K, V)* me, K key) \
    { \
        size_t i = STL_PRIVATE_FLATMAP_NAME(stl_PRIVATE_flatmap_lowerbound_, K, V)(me, key); \
        if (i >= me->size || stlcompare(K)(me->data[i].key, key) != 0) \
            return NULL; \
        return &me->data[i].value; \
    } \
    ATTR V* stlflatmapat(K, V)(stlflatmap(K, V)* me, K key) \
    { \
        V* p = stlflatmapfind(K, V)(me, key); \
        stlassert(p != NULL); \
        return p; \
    } \
    ATTR const V* stlflatmapat_const(K, V)(const stlflatmap(K, V)* me, K key) \
    { \
        const V* p = stlflatmapfind_const(K, V)(me, key); \
        stlassert(p != NULL); \
        return p; \
    } \
    ATTR int stlflatmaperase(K, V)(stlflatmap(K, V)* me, K key) \
    { \
        size_t i = STL_PRIVATE_FLATMAP_NAME(stl_PRIVATE_flatmap_lowerbound_, K, V)(me, key); \
        if (i >= me->size || stlcompare(K)(me->data[i].key, key) != 0) \
            return 0; \
        if (i + 1 < me->size) \
            memmove(&me->data[i], &me->data[i + 1], \
                (me->size - i - 1) * sizeof(stlflatmapentry(K, V))); \
        --me->size; \
        return 1; \
    } \
    ATTR void stlflatmapclear(K, V)(stlflatmap(K, V)* me) \
    { \
        me->size = 0; \
    } \
    ATTR void stlflatmapcopy(K, V)(stlflatmap(K, V)* dst, const stlflatmap(K, V)* src) \
    { \
        if (dst == src) return; \
        stlflatmapclear(K, V)(dst); \
        if (src->size > dst->capacity) \
            stlflatmapreserve(K, V)(dst, src->size); \
        if (src->size) \
            memcpy(dst->data, src->data, src->size * sizeof(stlflatmapentry(K, V))); \
        dst->size = src->size; \
    } \
    ATTR stlflatmap(K, V) stlflatmapclone(K, V)(const stlflatmap(K, V)* me) \
    { \
        stlflatmap(K, V) r; \
        stlflatmapinit(K, V)(&r, me->size); \
        if (me->size) \
        { \
            memcpy(r.data, me->data, me->size * sizeof(stlflatmapentry(K, V))); \
            r.size = me->size; \
        } \
        return r; \
    } \
    ATTR void stlflatmapmove(K, V)(stlflatmap(K, V)* dst, stlflatmap(K, V)* src) \
    { \
        if (dst == src) return; \
        if (dst->data != src->data) stlfree(dst->data); \
        dst->data = src->data; \
        dst->size = src->size; \
        dst->capacity = src->capacity; \
        src->data = NULL; \
        src->size = 0; \
        src->capacity = 0; \
    } \
    ATTR void stlflatmapswap(K, V)(stlflatmap(K, V)* a, stlflatmap(K, V)* b) \
    { \
        stlflatmap(K, V) tmp = *a; \
        *a = *b; \
        *b = tmp; \
    } \
    ATTR int stlflatmapcontains(K, V)(const stlflatmap(K, V)* me, K key) \
    { \
        size_t i = STL_PRIVATE_FLATMAP_NAME(stl_PRIVATE_flatmap_lowerbound_, K, V)(me, key); \
        return i < me->size && stlcompare(K)(me->data[i].key, key) == 0; \
    } \
    ATTR size_t stlflatmapsize(K, V)(const stlflatmap(K, V)* me) \
    { \
        return me->size; \
    } \
    ATTR size_t stlflatmapcapacity(K, V)(const stlflatmap(K, V)* me) \
    { \
        return me->capacity; \
    } \
    ATTR int stlflatmapempty(K, V)(const stlflatmap(K, V)* me) \
    { \
        return me->size == 0; \
    }

// MARK: sugar
#define stlflatmapforeach(K, V, ME, IT) \
    for (stlflatmapentry(K, V)* IT = (ME)->data, *IT##_HIDE_end = (ME)->data + (ME)->size; IT != IT##_HIDE_end; ++IT)
#define stlflatmapforeach_const(K, V, ME, IT) \
    for (const stlflatmapentry(K, V)* IT = (ME)->data, *IT##_HIDE_end = (ME)->data + (ME)->size; IT != IT##_HIDE_end; ++IT)
#define stlflatmaprforeach(K, V, ME, IT) \
    for (stlflatmapentry(K, V)* IT##_HIDE_start = (ME)->data, *IT = IT##_HIDE_start + (ME)->size; IT != IT##_HIDE_start && (--IT, 1);)
#define stlflatmaprforeach_const(K, V, ME, IT) \
    for (const stlflatmapentry(K, V)* IT##_HIDE_start = (ME)->data, *IT = IT##_HIDE_start + (ME)->size; IT != IT##_HIDE_start && (--IT, 1);)

#endif
