// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_XKFLATMAP_H
#define XK_XKFLATMAP_H

#include "xkconf.h"
#include "xkcompare.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define XK_PRIVATE_FLATMAP_MIN_CAPACITY 8

#ifndef XK_CAT
#define XK_CAT_(a, b)   a##b
#define XK_CAT(a, b)    XK_CAT_(a, b)
#endif

#define XK_PRIVATE_FLATMAP_NAME(NAME, K, V) \
    XK_CAT(XK_CAT(NAME, K), XK_CAT(_, V))

#define xkflatmap(K, V)             XK_PRIVATE_FLATMAP_NAME(xk_DETAIL_flatmap_, K, V)
#define xkflatmapentry(K, V)        XK_PRIVATE_FLATMAP_NAME(xk_DETAIL_flatmap_entry_, K, V)
#define xkflatmapinit(K, V)         XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_init_, K, V)
#define xkflatmapfree(K, V)         XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_free_, K, V)
#define xkflatmapreserve(K, V)      XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_reserve_, K, V)
#define xkflatmapshrink(K, V)       XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_shrink_, K, V)
#define xkflatmapset(K, V)          XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_set_, K, V)
#define xkflatmapfind(K, V)         XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_find_, K, V)
#define xkflatmapfind_const(K, V)   XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_find_const_, K, V)
#define xkflatmapat(K, V)           XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_at_, K, V)
#define xkflatmapat_const(K, V)     XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_at_const_, K, V)
#define xkflatmaperase(K, V)        XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_erase_, K, V)
#define xkflatmapclear(K, V)        XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_clear_, K, V)
#define xkflatmapcopy(K, V)         XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_copy_, K, V)
#define xkflatmapclone(K, V)        XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_clone_, K, V)
#define xkflatmapmove(K, V)         XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_move_, K, V)
#define xkflatmapswap(K, V)         XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_swap_, K, V)
#define xkflatmapcontains(K, V)     XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_contains_, K, V)
#define xkflatmapsize(K, V)         XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_size_, K, V)
#define xkflatmapcapacity(K, V)     XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_capacity_, K, V)
#define xkflatmapempty(K, V)        XK_PRIVATE_FLATMAP_NAME(xk_PUBLIC_flatmap_empty_, K, V)

// MARK: decl
#define xkflatmapdecl(K, V, ATTR) \
    typedef struct xkflatmapentry(K, V) \
    { \
        K key; \
        V value; \
    } xkflatmapentry(K, V); \
    typedef struct xkflatmap(K, V) \
    { \
        xkflatmapentry(K, V)* data; \
        size_t size; \
        size_t capacity; \
    } xkflatmap(K, V); \
    ATTR void xkflatmapinit(K, V)(xkflatmap(K, V)* me, size_t cap); \
    ATTR void xkflatmapfree(K, V)(xkflatmap(K, V)* me); \
    ATTR void xkflatmapreserve(K, V)(xkflatmap(K, V)* me, size_t cap); \
    ATTR void xkflatmapshrink(K, V)(xkflatmap(K, V)* me); \
    ATTR void xkflatmapset(K, V)(xkflatmap(K, V)* me, K key, V value); \
    ATTR V* xkflatmapfind(K, V)(xkflatmap(K, V)* me, K key); \
    ATTR const V* xkflatmapfind_const(K, V)(const xkflatmap(K, V)* me, K key); \
    ATTR V* xkflatmapat(K, V)(xkflatmap(K, V)* me, K key); \
    ATTR const V* xkflatmapat_const(K, V)(const xkflatmap(K, V)* me, K key); \
    ATTR int xkflatmaperase(K, V)(xkflatmap(K, V)* me, K key); \
    ATTR void xkflatmapclear(K, V)(xkflatmap(K, V)* me); \
    ATTR void xkflatmapcopy(K, V)(xkflatmap(K, V)* dst, const xkflatmap(K, V)* src); \
    ATTR xkflatmap(K, V) xkflatmapclone(K, V)(const xkflatmap(K, V)* me); \
    ATTR void xkflatmapmove(K, V)(xkflatmap(K, V)* dst, xkflatmap(K, V)* src); \
    ATTR void xkflatmapswap(K, V)(xkflatmap(K, V)* a, xkflatmap(K, V)* b); \
    ATTR int xkflatmapcontains(K, V)(const xkflatmap(K, V)* me, K key); \
    ATTR size_t xkflatmapsize(K, V)(const xkflatmap(K, V)* me); \
    ATTR size_t xkflatmapcapacity(K, V)(const xkflatmap(K, V)* me); \
    ATTR int xkflatmapempty(K, V)(const xkflatmap(K, V)* me);

// MARK: impl
#define xkflatmapimpl(K, V, ATTR) \
    static inline size_t XK_PRIVATE_FLATMAP_NAME(xk_PRIVATE_flatmap_lowerbound_, K, V)(const xkflatmap(K, V)* me, K key) \
    { \
        size_t lo = 0; \
        size_t hi = me->size; \
        while (lo < hi) \
        { \
            size_t mid = lo + (hi - lo) / 2; \
            if (xkcompare(K)(me->data[mid].key, key) < 0) \
                lo = mid + 1; \
            else \
                hi = mid; \
        } \
        return lo; \
    } \
    ATTR void xkflatmapinit(K, V)(xkflatmap(K, V)* me, size_t cap) \
    { \
        me->data = NULL; \
        me->size = 0; \
        me->capacity = 0; \
        if (cap) xkflatmapreserve(K, V)(me, cap); \
    } \
    ATTR void xkflatmapfree(K, V)(xkflatmap(K, V)* me) \
    { \
        xkfree(me->data); \
        me->data = NULL; \
        me->size = 0; \
        me->capacity = 0; \
    } \
    ATTR void xkflatmapreserve(K, V)(xkflatmap(K, V)* me, size_t cap) \
    { \
        if (cap <= me->capacity) return; \
        const size_t maxcap = (size_t)-1 / sizeof(xkflatmapentry(K, V)); \
        if (cap > maxcap) xkabort(); \
        size_t nc = me->capacity \
            ? me->capacity \
            : (cap < XK_PRIVATE_FLATMAP_MIN_CAPACITY ? XK_PRIVATE_FLATMAP_MIN_CAPACITY : cap); \
        if (nc < cap) \
        { \
            if (nc > maxcap / 2) nc = cap; \
            else \
            { \
                nc *= 2; \
                if (nc < cap) nc = cap; \
            } \
        } \
        xkflatmapentry(K, V)* p = \
            (xkflatmapentry(K, V)*)xkrealloc(me->data, nc * sizeof(xkflatmapentry(K, V))); \
        if (!p) xkabort(); \
        me->data = p; \
        me->capacity = nc; \
    } \
    ATTR void xkflatmapshrink(K, V)(xkflatmap(K, V)* me) \
    { \
        if (me->size == me->capacity) return; \
        if (me->size == 0) \
        { \
            xkfree(me->data); \
            me->data = NULL; \
            me->capacity = 0; \
        } \
        else \
        { \
            xkflatmapentry(K, V)* p = \
                (xkflatmapentry(K, V)*)xkrealloc(me->data, me->size * sizeof(xkflatmapentry(K, V))); \
            if (!p) xkabort(); \
            me->data = p; \
            me->capacity = me->size; \
        } \
    } \
    ATTR void xkflatmapset(K, V)(xkflatmap(K, V)* me, K key, V value) \
    { \
        size_t i = XK_PRIVATE_FLATMAP_NAME(xk_PRIVATE_flatmap_lowerbound_, K, V)(me, key); \
        if (i < me->size && xkcompare(K)(me->data[i].key, key) == 0) \
        { \
            me->data[i].value = value; \
            return; \
        } \
        if (me->size == me->capacity) \
            xkflatmapreserve(K, V)(me, me->size + 1); \
        if (i < me->size) \
            memmove(&me->data[i + 1], &me->data[i], \
                (me->size - i) * sizeof(xkflatmapentry(K, V))); \
        me->data[i].key = key; \
        me->data[i].value = value; \
        ++me->size; \
    } \
    ATTR V* xkflatmapfind(K, V)(xkflatmap(K, V)* me, K key) \
    { \
        size_t i = XK_PRIVATE_FLATMAP_NAME(xk_PRIVATE_flatmap_lowerbound_, K, V)(me, key); \
        if (i >= me->size || xkcompare(K)(me->data[i].key, key) != 0) \
            return NULL; \
        return &me->data[i].value; \
    } \
    ATTR const V* xkflatmapfind_const(K, V)(const xkflatmap(K, V)* me, K key) \
    { \
        size_t i = XK_PRIVATE_FLATMAP_NAME(xk_PRIVATE_flatmap_lowerbound_, K, V)(me, key); \
        if (i >= me->size || xkcompare(K)(me->data[i].key, key) != 0) \
            return NULL; \
        return &me->data[i].value; \
    } \
    ATTR V* xkflatmapat(K, V)(xkflatmap(K, V)* me, K key) \
    { \
        V* p = xkflatmapfind(K, V)(me, key); \
        xkassert(p != NULL); \
        return p; \
    } \
    ATTR const V* xkflatmapat_const(K, V)(const xkflatmap(K, V)* me, K key) \
    { \
        const V* p = xkflatmapfind_const(K, V)(me, key); \
        xkassert(p != NULL); \
        return p; \
    } \
    ATTR int xkflatmaperase(K, V)(xkflatmap(K, V)* me, K key) \
    { \
        size_t i = XK_PRIVATE_FLATMAP_NAME(xk_PRIVATE_flatmap_lowerbound_, K, V)(me, key); \
        if (i >= me->size || xkcompare(K)(me->data[i].key, key) != 0) \
            return 0; \
        if (i + 1 < me->size) \
            memmove(&me->data[i], &me->data[i + 1], \
                (me->size - i - 1) * sizeof(xkflatmapentry(K, V))); \
        --me->size; \
        return 1; \
    } \
    ATTR void xkflatmapclear(K, V)(xkflatmap(K, V)* me) \
    { \
        me->size = 0; \
    } \
    ATTR void xkflatmapcopy(K, V)(xkflatmap(K, V)* dst, const xkflatmap(K, V)* src) \
    { \
        if (dst == src) return; \
        xkflatmapclear(K, V)(dst); \
        if (src->size > dst->capacity) \
            xkflatmapreserve(K, V)(dst, src->size); \
        if (src->size) \
            memcpy(dst->data, src->data, src->size * sizeof(xkflatmapentry(K, V))); \
        dst->size = src->size; \
    } \
    ATTR xkflatmap(K, V) xkflatmapclone(K, V)(const xkflatmap(K, V)* me) \
    { \
        xkflatmap(K, V) r; \
        xkflatmapinit(K, V)(&r, me->size); \
        if (me->size) \
        { \
            memcpy(r.data, me->data, me->size * sizeof(xkflatmapentry(K, V))); \
            r.size = me->size; \
        } \
        return r; \
    } \
    ATTR void xkflatmapmove(K, V)(xkflatmap(K, V)* dst, xkflatmap(K, V)* src) \
    { \
        if (dst == src) return; \
        if (dst->data != src->data) xkfree(dst->data); \
        dst->data = src->data; \
        dst->size = src->size; \
        dst->capacity = src->capacity; \
        src->data = NULL; \
        src->size = 0; \
        src->capacity = 0; \
    } \
    ATTR void xkflatmapswap(K, V)(xkflatmap(K, V)* a, xkflatmap(K, V)* b) \
    { \
        xkflatmap(K, V) tmp = *a; \
        *a = *b; \
        *b = tmp; \
    } \
    ATTR int xkflatmapcontains(K, V)(const xkflatmap(K, V)* me, K key) \
    { \
        size_t i = XK_PRIVATE_FLATMAP_NAME(xk_PRIVATE_flatmap_lowerbound_, K, V)(me, key); \
        return i < me->size && xkcompare(K)(me->data[i].key, key) == 0; \
    } \
    ATTR size_t xkflatmapsize(K, V)(const xkflatmap(K, V)* me) \
    { \
        return me->size; \
    } \
    ATTR size_t xkflatmapcapacity(K, V)(const xkflatmap(K, V)* me) \
    { \
        return me->capacity; \
    } \
    ATTR int xkflatmapempty(K, V)(const xkflatmap(K, V)* me) \
    { \
        return me->size == 0; \
    }

// MARK: sugar
#define xkflatmapforeach(K, V, ME, IT) \
    for (xkflatmapentry(K, V)* IT = (ME)->data, *IT##_HIDE_end = (ME)->data + (ME)->size; IT != IT##_HIDE_end; ++IT)
#define xkflatmapforeach_const(K, V, ME, IT) \
    for (const xkflatmapentry(K, V)* IT = (ME)->data, *IT##_HIDE_end = (ME)->data + (ME)->size; IT != IT##_HIDE_end; ++IT)
#define xkflatmaprforeach(K, V, ME, IT) \
    for (xkflatmapentry(K, V)* IT##_HIDE_start = (ME)->data, *IT = IT##_HIDE_start + (ME)->size; IT != IT##_HIDE_start && (--IT, 1);)
#define xkflatmaprforeach_const(K, V, ME, IT) \
    for (const xkflatmapentry(K, V)* IT##_HIDE_start = (ME)->data, *IT = IT##_HIDE_start + (ME)->size; IT != IT##_HIDE_start && (--IT, 1);)

#endif
