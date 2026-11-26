// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__XKSMALLFLATMAP_H
#define XK_INTERNAL__XKSMALLFLATMAP_H

#include "_xkconf.h"
#include "_xkcompare.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define XK_PRIVATE_SMALLFLATMAP_MIN_CAPACITY 8

#ifndef XK_CAT
#define XK_CAT_(a, b)   a##b
#define XK_CAT(a, b)    XK_CAT_(a, b)
#endif

#define XK_PRIVATE_SMALLFLATMAP_NAME(NAME, K, V, N) \
    XK_CAT(XK_CAT(XK_CAT(NAME, K), XK_CAT(_, V)), XK_CAT(_, N))

#define xksmallflatmapentry(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xksmallflatmap_entry_, K, V, N)
#define xksmallflatmap(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xksmallflatmap_, K, V, N)
#define xksmallflatmapinit(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_init_, K, V, N)
#define xksmallflatmapfree(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_free_, K, V, N)
#define xksmallflatmapreserve(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_reserve_, K, V, N)
#define xksmallflatmapshrink(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_shrink_, K, V, N)
#define xksmallflatmapset(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_set_, K, V, N)
#define xksmallflatmapfind(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_find_, K, V, N)
#define xksmallflatmapfind_const(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_find_const_, K, V, N)
#define xksmallflatmapat(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_at_, K, V, N)
#define xksmallflatmapat_const(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_at_const_, K, V, N)
#define xksmallflatmaperase(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_erase_, K, V, N)
#define xksmallflatmapclear(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_clear_, K, V, N)
#define xksmallflatmapcopy(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_copy_, K, V, N)
#define xksmallflatmapclone(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_clone_, K, V, N)
#define xksmallflatmapmove(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_move_, K, V, N)
#define xksmallflatmapswap(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_swap_, K, V, N)
#define xksmallflatmapcontains(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_contains_, K, V, N)
#define xksmallflatmapsize(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_size_, K, V, N)
#define xksmallflatmapcapacity(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_capacity_, K, V, N)
#define xksmallflatmapempty(K, V, N) \
    XK_PRIVATE_SMALLFLATMAP_NAME(xk_PUBLIC_smallflatmap_empty_, K, V, N)

// MARK: decl
#define xksmallflatmapdecl(K, V, N, ATTR) \
    typedef struct xksmallflatmapentry(K, V, N) \
    { \
        K key; \
        V value; \
    } xksmallflatmapentry(K, V, N); \
    typedef struct xksmallflatmap(K, V, N) \
    { \
        xksmallflatmapentry(K, V, N) storage[((N) ? (N) : 1)]; \
        xksmallflatmapentry(K, V, N)* heap; \
        size_t size; \
        size_t capacity; \
    } xksmallflatmap(K, V, N); \
    ATTR void xksmallflatmapinit(K, V, N)(xksmallflatmap(K, V, N)* me); \
    ATTR void xksmallflatmapfree(K, V, N)(xksmallflatmap(K, V, N)* me); \
    ATTR void xksmallflatmapreserve(K, V, N)(xksmallflatmap(K, V, N)* me, size_t cap); \
    ATTR void xksmallflatmapshrink(K, V, N)(xksmallflatmap(K, V, N)* me); \
    ATTR void xksmallflatmapset(K, V, N)(xksmallflatmap(K, V, N)* me, K key, V value); \
    ATTR V* xksmallflatmapfind(K, V, N)(xksmallflatmap(K, V, N)* me, K key); \
    ATTR const V* xksmallflatmapfind_const(K, V, N)(const xksmallflatmap(K, V, N)* me, K key); \
    ATTR V* xksmallflatmapat(K, V, N)(xksmallflatmap(K, V, N)* me, K key); \
    ATTR const V* xksmallflatmapat_const(K, V, N)(const xksmallflatmap(K, V, N)* me, K key); \
    ATTR int xksmallflatmaperase(K, V, N)(xksmallflatmap(K, V, N)* me, K key); \
    ATTR void xksmallflatmapclear(K, V, N)(xksmallflatmap(K, V, N)* me); \
    ATTR void xksmallflatmapcopy(K, V, N)(xksmallflatmap(K, V, N)* dst, const xksmallflatmap(K, V, N)* src); \
    ATTR xksmallflatmap(K, V, N) xksmallflatmapclone(K, V, N)(const xksmallflatmap(K, V, N)* me); \
    ATTR void xksmallflatmapmove(K, V, N)(xksmallflatmap(K, V, N)* dst, xksmallflatmap(K, V, N)* src); \
    ATTR void xksmallflatmapswap(K, V, N)(xksmallflatmap(K, V, N)* a, xksmallflatmap(K, V, N)* b); \
    ATTR int xksmallflatmapcontains(K, V, N)(const xksmallflatmap(K, V, N)* me, K key); \
    ATTR size_t xksmallflatmapsize(K, V, N)(const xksmallflatmap(K, V, N)* me); \
    ATTR size_t xksmallflatmapcapacity(K, V, N)(const xksmallflatmap(K, V, N)* me); \
    ATTR int xksmallflatmapempty(K, V, N)(const xksmallflatmap(K, V, N)* me);

// MARK: impl
#define xksmallflatmapimpl(K, V, N, ATTR) \
    static inline xksmallflatmapentry(K, V, N)* XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_data_, K, V, N)(xksmallflatmap(K, V, N)* me) \
    { \
        return me->heap ? me->heap : me->storage; \
    } \
    static inline const xksmallflatmapentry(K, V, N)* XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_data_const_, K, V, N)(const xksmallflatmap(K, V, N)* me) \
    { \
        return me->heap ? me->heap : me->storage; \
    } \
    static inline size_t XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_lowerbound_, K, V, N)(const xksmallflatmap(K, V, N)* me, K key) \
    { \
        size_t lo = 0; \
        size_t hi = me->size; \
        while (lo < hi) \
        { \
            size_t mid = lo + (hi - lo) / 2; \
            if (xkcompare(K)(XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_data_const_, K, V, N)(me)[mid].key, key) < 0) \
                lo = mid + 1; \
            else \
                hi = mid; \
        } \
        return lo; \
    } \
    ATTR void xksmallflatmapinit(K, V, N)(xksmallflatmap(K, V, N)* me) \
    { \
        me->heap = NULL; \
        me->size = 0; \
        me->capacity = (size_t)(N); \
    } \
    ATTR void xksmallflatmapfree(K, V, N)(xksmallflatmap(K, V, N)* me) \
    { \
        if (me->heap) xkfree(me->heap); \
        me->heap = NULL; \
        me->size = 0; \
        me->capacity = (size_t)(N); \
    } \
    ATTR void xksmallflatmapreserve(K, V, N)(xksmallflatmap(K, V, N)* me, size_t cap) \
    { \
        if (!me->heap && me->capacity < (size_t)(N)) \
            me->capacity = (size_t)(N); \
        if (cap <= me->capacity) return; \
        const size_t maxcap = (size_t)-1 / sizeof(xksmallflatmapentry(K, V, N)); \
        if (cap > maxcap) xkabort(); \
        size_t nc = me->capacity \
            ? me->capacity \
            : (cap < XK_PRIVATE_SMALLFLATMAP_MIN_CAPACITY ? XK_PRIVATE_SMALLFLATMAP_MIN_CAPACITY : cap); \
        if (nc < cap) \
        { \
            if (nc > maxcap / 2) nc = cap; \
            else \
            { \
                nc *= 2; \
                if (nc < cap) nc = cap; \
            } \
        } \
        xksmallflatmapentry(K, V, N)* p; \
        if (me->heap) \
        { \
            p = (xksmallflatmapentry(K, V, N)*)xkrealloc(me->heap, nc * sizeof(xksmallflatmapentry(K, V, N))); \
            if (!p) xkabort(); \
        } \
        else \
        { \
            p = (xksmallflatmapentry(K, V, N)*)xkrealloc(NULL, nc * sizeof(xksmallflatmapentry(K, V, N))); \
            if (!p) xkabort(); \
            if (me->size) \
                memcpy(p, me->storage, me->size * sizeof(xksmallflatmapentry(K, V, N))); \
        } \
        me->heap = p; \
        me->capacity = nc; \
    } \
    ATTR void xksmallflatmapshrink(K, V, N)(xksmallflatmap(K, V, N)* me) \
    { \
        size_t base = (size_t)(N); \
        size_t target = me->size > base ? me->size : base; \
        if (me->capacity == target) return; \
        if (me->size <= base) \
        { \
            if (me->heap) \
            { \
                if (me->size) \
                    memcpy(me->storage, me->heap, me->size * sizeof(xksmallflatmapentry(K, V, N))); \
                xkfree(me->heap); \
                me->heap = NULL; \
            } \
            me->capacity = base; \
        } \
        else \
        { \
            xksmallflatmapentry(K, V, N)* p = \
                (xksmallflatmapentry(K, V, N)*)xkrealloc(me->heap, me->size * sizeof(xksmallflatmapentry(K, V, N))); \
            if (!p) xkabort(); \
            me->heap = p; \
            me->capacity = me->size; \
        } \
    } \
    ATTR void xksmallflatmapset(K, V, N)(xksmallflatmap(K, V, N)* me, K key, V value) \
    { \
        size_t i = XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_lowerbound_, K, V, N)(me, key); \
        if (i < me->size && \
            xkcompare(K)(XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_data_const_, K, V, N)(me)[i].key, key) == 0) \
        { \
            XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_data_, K, V, N)(me)[i].value = value; \
            return; \
        } \
        if (me->size == me->capacity) \
            xksmallflatmapreserve(K, V, N)(me, me->size + 1); \
        xksmallflatmapentry(K, V, N)* d = \
            XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_data_, K, V, N)(me); \
        if (i < me->size) \
            memmove(&d[i + 1], &d[i], (me->size - i) * sizeof(xksmallflatmapentry(K, V, N))); \
        d[i].key = key; \
        d[i].value = value; \
        ++me->size; \
    } \
    ATTR V* xksmallflatmapfind(K, V, N)(xksmallflatmap(K, V, N)* me, K key) \
    { \
        size_t i = XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_lowerbound_, K, V, N)(me, key); \
        xksmallflatmapentry(K, V, N)* d = \
            XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_data_, K, V, N)(me); \
        if (i >= me->size || xkcompare(K)(d[i].key, key) != 0) \
            return NULL; \
        return &d[i].value; \
    } \
    ATTR const V* xksmallflatmapfind_const(K, V, N)(const xksmallflatmap(K, V, N)* me, K key) \
    { \
        size_t i = XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_lowerbound_, K, V, N)(me, key); \
        const xksmallflatmapentry(K, V, N)* d = \
            XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_data_const_, K, V, N)(me); \
        if (i >= me->size || xkcompare(K)(d[i].key, key) != 0) \
            return NULL; \
        return &d[i].value; \
    } \
    ATTR V* xksmallflatmapat(K, V, N)(xksmallflatmap(K, V, N)* me, K key) \
    { \
        V* p = xksmallflatmapfind(K, V, N)(me, key); \
        xkassert(p != NULL); \
        return p; \
    } \
    ATTR const V* xksmallflatmapat_const(K, V, N)(const xksmallflatmap(K, V, N)* me, K key) \
    { \
        const V* p = xksmallflatmapfind_const(K, V, N)(me, key); \
        xkassert(p != NULL); \
        return p; \
    } \
    ATTR int xksmallflatmaperase(K, V, N)(xksmallflatmap(K, V, N)* me, K key) \
    { \
        size_t i = XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_lowerbound_, K, V, N)(me, key); \
        xksmallflatmapentry(K, V, N)* d = \
            XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_data_, K, V, N)(me); \
        if (i >= me->size || xkcompare(K)(d[i].key, key) != 0) \
            return 0; \
        if (i + 1 < me->size) \
            memmove(&d[i], &d[i + 1], (me->size - i - 1) * sizeof(xksmallflatmapentry(K, V, N))); \
        --me->size; \
        return 1; \
    } \
    ATTR void xksmallflatmapclear(K, V, N)(xksmallflatmap(K, V, N)* me) \
    { \
        me->size = 0; \
    } \
    ATTR void xksmallflatmapcopy(K, V, N)(xksmallflatmap(K, V, N)* dst, const xksmallflatmap(K, V, N)* src) \
    { \
        if (dst == src) return; \
        dst->size = 0; \
        if (src->size > dst->capacity) \
            xksmallflatmapreserve(K, V, N)(dst, src->size); \
        if (src->size) \
            memcpy(XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_data_, K, V, N)(dst), \
                XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_data_const_, K, V, N)(src), \
                src->size * sizeof(xksmallflatmapentry(K, V, N))); \
        dst->size = src->size; \
    } \
    ATTR xksmallflatmap(K, V, N) xksmallflatmapclone(K, V, N)(const xksmallflatmap(K, V, N)* me) \
    { \
        xksmallflatmap(K, V, N) r = {0}; \
        r.capacity = (size_t)(N); \
        if (me->size > (size_t)(N)) \
            xksmallflatmapreserve(K, V, N)(&r, me->size); \
        if (me->size) \
            memcpy(XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_data_, K, V, N)(&r), \
                XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_data_const_, K, V, N)(me), \
                me->size * sizeof(xksmallflatmapentry(K, V, N))); \
        r.size = me->size; \
        return r; \
    } \
    ATTR void xksmallflatmapmove(K, V, N)(xksmallflatmap(K, V, N)* dst, xksmallflatmap(K, V, N)* src) \
    { \
        if (dst == src) return; \
        if (src->heap) \
        { \
            if (dst->heap && dst->heap != src->heap) xkfree(dst->heap); \
            dst->heap = src->heap; \
            dst->size = src->size; \
            dst->capacity = src->capacity; \
            src->heap = NULL; \
            src->size = 0; \
            src->capacity = (size_t)(N); \
        } \
        else \
        { \
            dst->size = 0; \
            if (src->size > dst->capacity) \
                xksmallflatmapreserve(K, V, N)(dst, src->size); \
            if (src->size) \
                memcpy(XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_data_, K, V, N)(dst), \
                    src->storage, src->size * sizeof(xksmallflatmapentry(K, V, N))); \
            dst->size = src->size; \
            src->size = 0; \
            src->capacity = (size_t)(N); \
        } \
    } \
    ATTR void xksmallflatmapswap(K, V, N)(xksmallflatmap(K, V, N)* a, xksmallflatmap(K, V, N)* b) \
    { \
        if (a == b) return; \
        xksmallflatmap(K, V, N) tmp; \
        xksmallflatmapinit(K, V, N)(&tmp); \
        xksmallflatmapmove(K, V, N)(&tmp, a); \
        xksmallflatmapmove(K, V, N)(a, b); \
        xksmallflatmapmove(K, V, N)(b, &tmp); \
    } \
    ATTR int xksmallflatmapcontains(K, V, N)(const xksmallflatmap(K, V, N)* me, K key) \
    { \
        size_t i = XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_lowerbound_, K, V, N)(me, key); \
        return i < me->size && \
            xkcompare(K)(XK_PRIVATE_SMALLFLATMAP_NAME(xk_PRIVATE_smallflatmap_data_const_, K, V, N)(me)[i].key, key) == 0; \
    } \
    ATTR size_t xksmallflatmapsize(K, V, N)(const xksmallflatmap(K, V, N)* me) \
    { \
        return me->size; \
    } \
    ATTR size_t xksmallflatmapcapacity(K, V, N)(const xksmallflatmap(K, V, N)* me) \
    { \
        return me->heap ? me->capacity : (size_t)(N); \
    } \
    ATTR int xksmallflatmapempty(K, V, N)(const xksmallflatmap(K, V, N)* me) \
    { \
        return me->size == 0; \
    }

// MARK: sugar
#define xksmallflatmapforeach(K, V, N, ME, IT) \
    for (xksmallflatmapentry(K, V, N)* IT##_HIDE_base = ((ME)->heap ? (ME)->heap : (ME)->storage), \
        *IT = IT##_HIDE_base, \
        *IT##_HIDE_end = IT##_HIDE_base + (ME)->size; \
        IT != IT##_HIDE_end; ++IT)
#define xksmallflatmapforeach_const(K, V, N, ME, IT) \
    for (const xksmallflatmapentry(K, V, N)* IT##_HIDE_base = ((ME)->heap ? (ME)->heap : (ME)->storage), \
        *IT = IT##_HIDE_base, \
        *IT##_HIDE_end = IT##_HIDE_base + (ME)->size; \
        IT != IT##_HIDE_end; ++IT)
#define xksmallflatmaprforeach(K, V, N, ME, IT) \
    for (xksmallflatmapentry(K, V, N)* IT##_HIDE_base = ((ME)->heap ? (ME)->heap : (ME)->storage), \
        *IT = IT##_HIDE_base + (ME)->size; \
        IT != IT##_HIDE_base && (--IT, 1);)
#define xksmallflatmaprforeach_const(K, V, N, ME, IT) \
    for (const xksmallflatmapentry(K, V, N)* IT##_HIDE_base = ((ME)->heap ? (ME)->heap : (ME)->storage), \
        *IT = IT##_HIDE_base + (ME)->size; \
        IT != IT##_HIDE_base && (--IT, 1);)

#endif
