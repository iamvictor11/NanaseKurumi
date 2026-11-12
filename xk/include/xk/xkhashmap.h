// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_XKHASHMAP_H
#define XK_XKHASHMAP_H

#include "xkconf.h"
#include "xkequal.h"
#include "xkhash.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define XK_PRIVATE_HASHMAP_MIN_CAPACITY 8
#define XK_PRIVATE_HASHMAP_EMPTY 0
#define XK_PRIVATE_HASHMAP_USED 1
#define XK_PRIVATE_HASHMAP_DEAD 2

#ifndef XK_CAT
#define XK_CAT_(a, b)   a##b
#define XK_CAT(a, b)    XK_CAT_(a, b)
#endif

#define XK_PRIVATE_HASHMAP_NAME(NAME, K, V) \
    XK_CAT(XK_CAT(NAME, K), XK_CAT(_, V))

#define xkhashmap(K, V)             XK_PRIVATE_HASHMAP_NAME(xk_DETAIL_hashmap_, K, V)
#define xkhashmapentry(K, V)        XK_PRIVATE_HASHMAP_NAME(xk_DETAIL_hashmap_entry_, K, V)
#define xkhashmapinit(K, V)         XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_init_, K, V)
#define xkhashmapfree(K, V)         XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_free_, K, V)
#define xkhashmapreserve(K, V)      XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_reserve_, K, V)
#define xkhashmapshrink(K, V)       XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_shrink_, K, V)
#define xkhashmapset(K, V)          XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_set_, K, V)
#define xkhashmapfind(K, V)         XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_find_, K, V)
#define xkhashmapfind_const(K, V)   XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_find_const_, K, V)
#define xkhashmapat(K, V)           XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_at_, K, V)
#define xkhashmapat_const(K, V)     XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_at_const_, K, V)
#define xkhashmaperase(K, V)        XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_erase_, K, V)
#define xkhashmapclear(K, V)        XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_clear_, K, V)
#define xkhashmapcopy(K, V)         XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_copy_, K, V)
#define xkhashmapclone(K, V)        XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_clone_, K, V)
#define xkhashmapmove(K, V)         XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_move_, K, V)
#define xkhashmapswap(K, V)         XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_swap_, K, V)
#define xkhashmapcontains(K, V)     XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_contains_, K, V)
#define xkhashmapsize(K, V)         XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_size_, K, V)
#define xkhashmapcapacity(K, V)     XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_capacity_, K, V)
#define xkhashmapempty(K, V)        XK_PRIVATE_HASHMAP_NAME(xk_PUBLIC_hashmap_empty_, K, V)

// MARK: inst
#define xkhashmapinst(K, V) \
    struct xkhashmapentry(K, V) \
    { \
        size_t hash; \
        K key; \
        V value; \
        unsigned char state; \
    }; \
    struct xkhashmap(K, V) \
    { \
        struct xkhashmapentry(K, V)* slots; \
        size_t size; \
        size_t capacity; \
        size_t dead; \
    };

// MARK: decl
#define xkhashmapdecl(K, V, ATTR) \
    struct xkhashmapentry(K, V); \
    typedef struct xkhashmapentry(K, V) xkhashmapentry(K, V); \
    struct xkhashmap(K, V); \
    typedef struct xkhashmap(K, V) xkhashmap(K, V); \
    ATTR void xkhashmapinit(K, V)(xkhashmap(K, V)* me, size_t cap); \
    ATTR void xkhashmapfree(K, V)(xkhashmap(K, V)* me); \
    ATTR void xkhashmapreserve(K, V)(xkhashmap(K, V)* me, size_t cap); \
    ATTR void xkhashmapshrink(K, V)(xkhashmap(K, V)* me); \
    ATTR void xkhashmapset(K, V)(xkhashmap(K, V)* me, K key, V value); \
    ATTR V* xkhashmapfind(K, V)(xkhashmap(K, V)* me, K key); \
    ATTR const V* xkhashmapfind_const(K, V)(const xkhashmap(K, V)* me, K key); \
    ATTR V* xkhashmapat(K, V)(xkhashmap(K, V)* me, K key); \
    ATTR const V* xkhashmapat_const(K, V)(const xkhashmap(K, V)* me, K key); \
    ATTR int xkhashmaperase(K, V)(xkhashmap(K, V)* me, K key); \
    ATTR void xkhashmapclear(K, V)(xkhashmap(K, V)* me); \
    ATTR void xkhashmapcopy(K, V)(xkhashmap(K, V)* dst, const xkhashmap(K, V)* src); \
    ATTR xkhashmap(K, V) xkhashmapclone(K, V)(const xkhashmap(K, V)* me); \
    ATTR void xkhashmapmove(K, V)(xkhashmap(K, V)* dst, xkhashmap(K, V)* src); \
    ATTR void xkhashmapswap(K, V)(xkhashmap(K, V)* a, xkhashmap(K, V)* b); \
    ATTR int xkhashmapcontains(K, V)(const xkhashmap(K, V)* me, K key); \
    ATTR size_t xkhashmapsize(K, V)(const xkhashmap(K, V)* me); \
    ATTR size_t xkhashmapcapacity(K, V)(const xkhashmap(K, V)* me); \
    ATTR int xkhashmapempty(K, V)(const xkhashmap(K, V)* me);

// MARK: impl
#define xkhashmapimpl(K, V, ATTR) \
    static inline size_t XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_capfor_, K, V)(size_t n) \
    { \
        if (n > (size_t)-1 / 2) xkabort(); \
        size_t need = n * 2; \
        size_t cap = XK_PRIVATE_HASHMAP_MIN_CAPACITY; \
        while (cap < need) \
        { \
            if (cap > (size_t)-1 / 2) \
            { \
                cap = need; \
                break; \
            } \
            cap *= 2; \
        } \
        return cap; \
    } \
    static inline void XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_rehash_, K, V)(xkhashmap(K, V)* me, size_t ncap) \
    { \
        if (ncap < XK_PRIVATE_HASHMAP_MIN_CAPACITY) \
            ncap = XK_PRIVATE_HASHMAP_MIN_CAPACITY; \
        if (ncap > (size_t)-1 / sizeof(xkhashmapentry(K, V))) \
            xkabort(); \
        xkhashmapentry(K, V)* ns = \
            (xkhashmapentry(K, V)*)xkrealloc(NULL, ncap * sizeof(xkhashmapentry(K, V))); \
        if (!ns) xkabort(); \
        memset(ns, 0, ncap * sizeof(xkhashmapentry(K, V))); \
        size_t mask = ncap - 1; \
        for (size_t i = 0; i < me->capacity; ++i) \
        { \
            xkhashmapentry(K, V)* e = &me->slots[i]; \
            if (e->state != XK_PRIVATE_HASHMAP_USED) continue; \
            size_t j = e->hash & mask; \
            while (ns[j].state == XK_PRIVATE_HASHMAP_USED) \
                j = (j + 1) & mask; \
            ns[j] = *e; \
        } \
        xkfree(me->slots); \
        me->slots = ns; \
        me->capacity = ncap; \
        me->dead = 0; \
    } \
    static inline xkhashmapentry(K, V)* XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_find_, K, V)(const xkhashmap(K, V)* me, K key, size_t hash) \
    { \
        if (me->capacity == 0) return NULL; \
        size_t mask = me->capacity - 1; \
        size_t i = hash & mask; \
        for (size_t n = 0; n < me->capacity; ++n) \
        { \
            xkhashmapentry(K, V)* e = &me->slots[i]; \
            if (e->state == XK_PRIVATE_HASHMAP_EMPTY) return NULL; \
            if (e->state == XK_PRIVATE_HASHMAP_USED && e->hash == hash \
                && xkequal(K)(e->key, key)) \
                return e; \
            i = (i + 1) & mask; \
        } \
        return NULL; \
    } \
    static inline void XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_make_room_, K, V)(xkhashmap(K, V)* me) \
    { \
        if (me->capacity == 0) \
        { \
            XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_rehash_, K, V)(me, XK_PRIVATE_HASHMAP_MIN_CAPACITY); \
            return; \
        } \
        if (me->size + me->dead + 1 <= me->capacity / 2) \
            return; \
        size_t ncap = me->capacity; \
        if (me->size + 1 > me->capacity / 2) \
            ncap = XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_capfor_, K, V)(me->size + 1); \
        XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_rehash_, K, V)(me, ncap); \
    } \
    ATTR void xkhashmapinit(K, V)(xkhashmap(K, V)* me, size_t cap) \
    { \
        me->slots = NULL; \
        me->size = 0; \
        me->capacity = 0; \
        me->dead = 0; \
        if (cap) xkhashmapreserve(K, V)(me, cap); \
    } \
    ATTR void xkhashmapfree(K, V)(xkhashmap(K, V)* me) \
    { \
        xkfree(me->slots); \
        me->slots = NULL; \
        me->size = 0; \
        me->capacity = 0; \
        me->dead = 0; \
    } \
    ATTR void xkhashmapreserve(K, V)(xkhashmap(K, V)* me, size_t cap) \
    { \
        if (cap == 0) return; \
        size_t ncap = XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_capfor_, K, V)(cap); \
        if (ncap <= me->capacity) return; \
        XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_rehash_, K, V)(me, ncap); \
    } \
    ATTR void xkhashmapshrink(K, V)(xkhashmap(K, V)* me) \
    { \
        if (me->capacity == 0) return; \
        if (me->size == 0) \
        { \
            xkfree(me->slots); \
            me->slots = NULL; \
            me->capacity = 0; \
            me->dead = 0; \
            return; \
        } \
        size_t ncap = XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_capfor_, K, V)(me->size); \
        if (ncap < me->capacity) \
            XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_rehash_, K, V)(me, ncap); \
        else if (me->dead) \
            XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_rehash_, K, V)(me, me->capacity); \
    } \
    ATTR void xkhashmapset(K, V)(xkhashmap(K, V)* me, K key, V value) \
    { \
        size_t hash = xkhash(K)(key); \
        xkhashmapentry(K, V)* e = \
            XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_find_, K, V)(me, key, hash); \
        if (e) \
        { \
            e->value = value; \
            return; \
        } \
        XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_make_room_, K, V)(me); \
        size_t mask = me->capacity - 1; \
        size_t i = hash & mask; \
        while (me->slots[i].state == XK_PRIVATE_HASHMAP_USED) \
            i = (i + 1) & mask; \
        e = &me->slots[i]; \
        if (e->state == XK_PRIVATE_HASHMAP_DEAD) \
            --me->dead; \
        e->hash = hash; \
        e->key = key; \
        e->value = value; \
        e->state = XK_PRIVATE_HASHMAP_USED; \
        ++me->size; \
    } \
    ATTR V* xkhashmapfind(K, V)(xkhashmap(K, V)* me, K key) \
    { \
        xkhashmapentry(K, V)* e = \
            XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_find_, K, V)(me, key, xkhash(K)(key)); \
        return e ? &e->value : NULL; \
    } \
    ATTR const V* xkhashmapfind_const(K, V)(const xkhashmap(K, V)* me, K key) \
    { \
        const xkhashmapentry(K, V)* e = \
            XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_find_, K, V)(me, key, xkhash(K)(key)); \
        return e ? &e->value : NULL; \
    } \
    ATTR V* xkhashmapat(K, V)(xkhashmap(K, V)* me, K key) \
    { \
        V* p = xkhashmapfind(K, V)(me, key); \
        xkassert(p != NULL); \
        return p; \
    } \
    ATTR const V* xkhashmapat_const(K, V)(const xkhashmap(K, V)* me, K key) \
    { \
        const V* p = xkhashmapfind_const(K, V)(me, key); \
        xkassert(p != NULL); \
        return p; \
    } \
    ATTR int xkhashmaperase(K, V)(xkhashmap(K, V)* me, K key) \
    { \
        xkhashmapentry(K, V)* e = \
            XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_find_, K, V)(me, key, xkhash(K)(key)); \
        if (!e) return 0; \
        e->state = XK_PRIVATE_HASHMAP_DEAD; \
        --me->size; \
        ++me->dead; \
        if (me->dead > me->capacity / 4) \
            XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_rehash_, K, V)(me, me->capacity); \
        return 1; \
    } \
    ATTR void xkhashmapclear(K, V)(xkhashmap(K, V)* me) \
    { \
        if (me->capacity) \
            memset(me->slots, 0, me->capacity * sizeof(xkhashmapentry(K, V))); \
        me->size = 0; \
        me->dead = 0; \
    } \
    ATTR void xkhashmapcopy(K, V)(xkhashmap(K, V)* dst, const xkhashmap(K, V)* src) \
    { \
        if (dst == src) return; \
        if (src->capacity == 0) \
        { \
            xkfree(dst->slots); \
            dst->slots = NULL; \
            dst->size = 0; \
            dst->capacity = 0; \
            dst->dead = 0; \
            return; \
        } \
        if (dst->capacity != src->capacity) \
        { \
            if (src->capacity > (size_t)-1 / sizeof(xkhashmapentry(K, V))) \
                xkabort(); \
            xkhashmapentry(K, V)* ns = \
                (xkhashmapentry(K, V)*)xkrealloc(NULL, src->capacity * sizeof(xkhashmapentry(K, V))); \
            if (!ns) xkabort(); \
            xkfree(dst->slots); \
            dst->slots = ns; \
            dst->capacity = src->capacity; \
        } \
        memcpy(dst->slots, src->slots, src->capacity * sizeof(xkhashmapentry(K, V))); \
        dst->size = src->size; \
        dst->dead = src->dead; \
    } \
    ATTR xkhashmap(K, V) xkhashmapclone(K, V)(const xkhashmap(K, V)* me) \
    { \
        xkhashmap(K, V) r; \
        r.slots = NULL; \
        r.size = 0; \
        r.capacity = 0; \
        r.dead = 0; \
        if (me->capacity) \
        { \
            if (me->capacity > (size_t)-1 / sizeof(xkhashmapentry(K, V))) \
                xkabort(); \
            r.slots = (xkhashmapentry(K, V)*)xkrealloc(NULL, me->capacity * sizeof(xkhashmapentry(K, V))); \
            if (!r.slots) xkabort(); \
            memcpy(r.slots, me->slots, me->capacity * sizeof(xkhashmapentry(K, V))); \
            r.size = me->size; \
            r.capacity = me->capacity; \
            r.dead = me->dead; \
        } \
        return r; \
    } \
    ATTR void xkhashmapmove(K, V)(xkhashmap(K, V)* dst, xkhashmap(K, V)* src) \
    { \
        if (dst == src) return; \
        xkfree(dst->slots); \
        dst->slots = src->slots; \
        dst->size = src->size; \
        dst->capacity = src->capacity; \
        dst->dead = src->dead; \
        src->slots = NULL; \
        src->size = 0; \
        src->capacity = 0; \
        src->dead = 0; \
    } \
    ATTR void xkhashmapswap(K, V)(xkhashmap(K, V)* a, xkhashmap(K, V)* b) \
    { \
        xkhashmap(K, V) tmp = *a; \
        *a = *b; \
        *b = tmp; \
    } \
    ATTR int xkhashmapcontains(K, V)(const xkhashmap(K, V)* me, K key) \
    { \
        return XK_PRIVATE_HASHMAP_NAME(xk_PRIVATE_hashmap_find_, K, V)(me, key, xkhash(K)(key)) != NULL; \
    } \
    ATTR size_t xkhashmapsize(K, V)(const xkhashmap(K, V)* me) \
    { \
        return me->size; \
    } \
    ATTR size_t xkhashmapcapacity(K, V)(const xkhashmap(K, V)* me) \
    { \
        return me->capacity / 2; \
    } \
    ATTR int xkhashmapempty(K, V)(const xkhashmap(K, V)* me) \
    { \
        return me->size == 0; \
    }

// MARK: sugar
#define xkhashmapforeach(K, V, ME, IT) \
    for (xkhashmapentry(K, V)* IT = (ME)->slots, *IT##_HIDE_end = (ME)->slots + (ME)->capacity; IT != IT##_HIDE_end; ++IT) \
        if (IT->state == XK_PRIVATE_HASHMAP_USED)
#define xkhashmapforeach_const(K, V, ME, IT) \
    for (const xkhashmapentry(K, V)* IT = (ME)->slots, *IT##_HIDE_end = (ME)->slots + (ME)->capacity; IT != IT##_HIDE_end; ++IT) \
        if (IT->state == XK_PRIVATE_HASHMAP_USED)

#endif
