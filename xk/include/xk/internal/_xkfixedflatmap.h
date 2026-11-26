// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__XKFIXEDFLATMAP_H
#define XK_INTERNAL__XKFIXEDFLATMAP_H

#include "_xkconf.h"
#include "_xkcompare.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef XK_CAT
#define XK_CAT_(a, b)   a##b
#define XK_CAT(a, b)    XK_CAT_(a, b)
#endif

#define XK_PRIVATE_FIXEDFLATMAP_NAME(NAME, K, V, N) \
    XK_CAT(XK_CAT(XK_CAT(NAME, K), XK_CAT(_, V)), XK_CAT(_, N))

#define xkfixedflatmapentry(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xkfixedflatmap_entry_, K, V, N)
#define xkfixedflatmap(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xkfixedflatmap_, K, V, N)
#define xkfixedflatmapinit(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PUBLIC_fixedflatmap_init_, K, V, N)
#define xkfixedflatmapset(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PUBLIC_fixedflatmap_set_, K, V, N)
#define xkfixedflatmapfind(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PUBLIC_fixedflatmap_find_, K, V, N)
#define xkfixedflatmapfind_const(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PUBLIC_fixedflatmap_find_const_, K, V, N)
#define xkfixedflatmapat(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PUBLIC_fixedflatmap_at_, K, V, N)
#define xkfixedflatmapat_const(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PUBLIC_fixedflatmap_at_const_, K, V, N)
#define xkfixedflatmaperase(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PUBLIC_fixedflatmap_erase_, K, V, N)
#define xkfixedflatmapclear(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PUBLIC_fixedflatmap_clear_, K, V, N)
#define xkfixedflatmapcopy(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PUBLIC_fixedflatmap_copy_, K, V, N)
#define xkfixedflatmapclone(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PUBLIC_fixedflatmap_clone_, K, V, N)
#define xkfixedflatmapmove(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PUBLIC_fixedflatmap_move_, K, V, N)
#define xkfixedflatmapswap(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PUBLIC_fixedflatmap_swap_, K, V, N)
#define xkfixedflatmapcontains(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PUBLIC_fixedflatmap_contains_, K, V, N)
#define xkfixedflatmapsize(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PUBLIC_fixedflatmap_size_, K, V, N)
#define xkfixedflatmapcapacity(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PUBLIC_fixedflatmap_capacity_, K, V, N)
#define xkfixedflatmapempty(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PUBLIC_fixedflatmap_empty_, K, V, N)
#define xkfixedflatmapfull(K, V, N) \
    XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PUBLIC_fixedflatmap_full_, K, V, N)

// MARK: decl
#define xkfixedflatmapdecl(K, V, N, ATTR) \
    typedef struct xkfixedflatmapentry(K, V, N) \
    { \
        K key; \
        V value; \
    } xkfixedflatmapentry(K, V, N); \
    typedef struct xkfixedflatmap(K, V, N) \
    { \
        xkfixedflatmapentry(K, V, N) data[((N) ? (N) : 1)]; \
        size_t size; \
    } xkfixedflatmap(K, V, N); \
    ATTR void xkfixedflatmapinit(K, V, N)(xkfixedflatmap(K, V, N)* me); \
    ATTR void xkfixedflatmapset(K, V, N)(xkfixedflatmap(K, V, N)* me, K key, V value); \
    ATTR V* xkfixedflatmapfind(K, V, N)(xkfixedflatmap(K, V, N)* me, K key); \
    ATTR const V* xkfixedflatmapfind_const(K, V, N)(const xkfixedflatmap(K, V, N)* me, K key); \
    ATTR V* xkfixedflatmapat(K, V, N)(xkfixedflatmap(K, V, N)* me, K key); \
    ATTR const V* xkfixedflatmapat_const(K, V, N)(const xkfixedflatmap(K, V, N)* me, K key); \
    ATTR int xkfixedflatmaperase(K, V, N)(xkfixedflatmap(K, V, N)* me, K key); \
    ATTR void xkfixedflatmapclear(K, V, N)(xkfixedflatmap(K, V, N)* me); \
    ATTR void xkfixedflatmapcopy(K, V, N)(xkfixedflatmap(K, V, N)* dst, const xkfixedflatmap(K, V, N)* src); \
    ATTR xkfixedflatmap(K, V, N) xkfixedflatmapclone(K, V, N)(const xkfixedflatmap(K, V, N)* me); \
    ATTR void xkfixedflatmapmove(K, V, N)(xkfixedflatmap(K, V, N)* dst, xkfixedflatmap(K, V, N)* src); \
    ATTR void xkfixedflatmapswap(K, V, N)(xkfixedflatmap(K, V, N)* a, xkfixedflatmap(K, V, N)* b); \
    ATTR int xkfixedflatmapcontains(K, V, N)(const xkfixedflatmap(K, V, N)* me, K key); \
    ATTR size_t xkfixedflatmapsize(K, V, N)(const xkfixedflatmap(K, V, N)* me); \
    ATTR size_t xkfixedflatmapcapacity(K, V, N)(const xkfixedflatmap(K, V, N)* me); \
    ATTR int xkfixedflatmapempty(K, V, N)(const xkfixedflatmap(K, V, N)* me); \
    ATTR int xkfixedflatmapfull(K, V, N)(const xkfixedflatmap(K, V, N)* me);

// MARK: impl
#define xkfixedflatmapimpl(K, V, N, ATTR) \
    static inline size_t XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PRIVATE_fixedflatmap_lowerbound_, K, V, N)(const xkfixedflatmap(K, V, N)* me, K key) \
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
    ATTR void xkfixedflatmapinit(K, V, N)(xkfixedflatmap(K, V, N)* me) \
    { \
        me->size = 0; \
    } \
    ATTR void xkfixedflatmapset(K, V, N)(xkfixedflatmap(K, V, N)* me, K key, V value) \
    { \
        size_t i = XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PRIVATE_fixedflatmap_lowerbound_, K, V, N)(me, key); \
        if (i < me->size && xkcompare(K)(me->data[i].key, key) == 0) \
        { \
            me->data[i].value = value; \
            return; \
        } \
        if (me->size >= (size_t)(N)) \
            xkabort(); \
        if (i < me->size) \
            memmove(&me->data[i + 1], &me->data[i], \
                (me->size - i) * sizeof(xkfixedflatmapentry(K, V, N))); \
        me->data[i].key = key; \
        me->data[i].value = value; \
        ++me->size; \
    } \
    ATTR V* xkfixedflatmapfind(K, V, N)(xkfixedflatmap(K, V, N)* me, K key) \
    { \
        size_t i = XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PRIVATE_fixedflatmap_lowerbound_, K, V, N)(me, key); \
        if (i >= me->size || xkcompare(K)(me->data[i].key, key) != 0) \
            return NULL; \
        return &me->data[i].value; \
    } \
    ATTR const V* xkfixedflatmapfind_const(K, V, N)(const xkfixedflatmap(K, V, N)* me, K key) \
    { \
        size_t i = XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PRIVATE_fixedflatmap_lowerbound_, K, V, N)(me, key); \
        if (i >= me->size || xkcompare(K)(me->data[i].key, key) != 0) \
            return NULL; \
        return &me->data[i].value; \
    } \
    ATTR V* xkfixedflatmapat(K, V, N)(xkfixedflatmap(K, V, N)* me, K key) \
    { \
        V* p = xkfixedflatmapfind(K, V, N)(me, key); \
        xkassert(p != NULL); \
        return p; \
    } \
    ATTR const V* xkfixedflatmapat_const(K, V, N)(const xkfixedflatmap(K, V, N)* me, K key) \
    { \
        const V* p = xkfixedflatmapfind_const(K, V, N)(me, key); \
        xkassert(p != NULL); \
        return p; \
    } \
    ATTR int xkfixedflatmaperase(K, V, N)(xkfixedflatmap(K, V, N)* me, K key) \
    { \
        size_t i = XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PRIVATE_fixedflatmap_lowerbound_, K, V, N)(me, key); \
        if (i >= me->size || xkcompare(K)(me->data[i].key, key) != 0) \
            return 0; \
        if (i + 1 < me->size) \
            memmove(&me->data[i], &me->data[i + 1], \
                (me->size - i - 1) * sizeof(xkfixedflatmapentry(K, V, N))); \
        --me->size; \
        return 1; \
    } \
    ATTR void xkfixedflatmapclear(K, V, N)(xkfixedflatmap(K, V, N)* me) \
    { \
        me->size = 0; \
    } \
    ATTR void xkfixedflatmapcopy(K, V, N)(xkfixedflatmap(K, V, N)* dst, const xkfixedflatmap(K, V, N)* src) \
    { \
        if (dst == src) return; \
        if (src->size > (size_t)(N)) xkabort(); \
        if (src->size) \
            memcpy(dst->data, src->data, src->size * sizeof(xkfixedflatmapentry(K, V, N))); \
        dst->size = src->size; \
    } \
    ATTR xkfixedflatmap(K, V, N) xkfixedflatmapclone(K, V, N)(const xkfixedflatmap(K, V, N)* me) \
    { \
        if (me->size > (size_t)(N)) xkabort(); \
        xkfixedflatmap(K, V, N) r = {0}; \
        r.size = me->size; \
        if (me->size) \
            memcpy(r.data, me->data, me->size * sizeof(xkfixedflatmapentry(K, V, N))); \
        return r; \
    } \
    ATTR void xkfixedflatmapmove(K, V, N)(xkfixedflatmap(K, V, N)* dst, xkfixedflatmap(K, V, N)* src) \
    { \
        if (dst == src) return; \
        if (src->size > (size_t)(N)) xkabort(); \
        if (src->size) \
            memcpy(dst->data, src->data, src->size * sizeof(xkfixedflatmapentry(K, V, N))); \
        dst->size = src->size; \
        src->size = 0; \
    } \
    ATTR void xkfixedflatmapswap(K, V, N)(xkfixedflatmap(K, V, N)* a, xkfixedflatmap(K, V, N)* b) \
    { \
        if (a == b) return; \
        size_t na = a->size; \
        size_t nb = b->size; \
        xkfixedflatmap(K, V, N) tmp; \
        tmp.size = na; \
        if (na) memcpy(tmp.data, a->data, na * sizeof(xkfixedflatmapentry(K, V, N))); \
        a->size = nb; \
        if (nb) memcpy(a->data, b->data, nb * sizeof(xkfixedflatmapentry(K, V, N))); \
        b->size = na; \
        if (na) memcpy(b->data, tmp.data, na * sizeof(xkfixedflatmapentry(K, V, N))); \
    } \
    ATTR int xkfixedflatmapcontains(K, V, N)(const xkfixedflatmap(K, V, N)* me, K key) \
    { \
        size_t i = XK_PRIVATE_FIXEDFLATMAP_NAME(xk_PRIVATE_fixedflatmap_lowerbound_, K, V, N)(me, key); \
        return i < me->size && xkcompare(K)(me->data[i].key, key) == 0; \
    } \
    ATTR size_t xkfixedflatmapsize(K, V, N)(const xkfixedflatmap(K, V, N)* me) \
    { \
        return me->size; \
    } \
    ATTR size_t xkfixedflatmapcapacity(K, V, N)(const xkfixedflatmap(K, V, N)* me) \
    { \
        (void)me; \
        return (size_t)(N); \
    } \
    ATTR int xkfixedflatmapempty(K, V, N)(const xkfixedflatmap(K, V, N)* me) \
    { \
        return me->size == 0; \
    } \
    ATTR int xkfixedflatmapfull(K, V, N)(const xkfixedflatmap(K, V, N)* me) \
    { \
        return me->size == (size_t)(N); \
    }

// MARK: sugar
#define xkfixedflatmapforeach(K, V, N, ME, IT) \
    for (xkfixedflatmapentry(K, V, N)* IT = (ME)->data, *IT##_HIDE_end = (ME)->data + (ME)->size; IT != IT##_HIDE_end; ++IT)
#define xkfixedflatmapforeach_const(K, V, N, ME, IT) \
    for (const xkfixedflatmapentry(K, V, N)* IT = (ME)->data, *IT##_HIDE_end = (ME)->data + (ME)->size; IT != IT##_HIDE_end; ++IT)
#define xkfixedflatmaprforeach(K, V, N, ME, IT) \
    for (xkfixedflatmapentry(K, V, N)* IT##_HIDE_start = (ME)->data, *IT = IT##_HIDE_start + (ME)->size; IT != IT##_HIDE_start && (--IT, 1);)
#define xkfixedflatmaprforeach_const(K, V, N, ME, IT) \
    for (const xkfixedflatmapentry(K, V, N)* IT##_HIDE_start = (ME)->data, *IT = IT##_HIDE_start + (ME)->size; IT != IT##_HIDE_start && (--IT, 1);)

#endif
