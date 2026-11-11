// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef STL_STLHASHMAP_H
#define STL_STLHASHMAP_H

#include "stlconf.h"
#include "stlequal.h"
#include "stlhash.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define STL_PRIVATE_HASHMAP_MIN_CAPACITY 8
#define STL_PRIVATE_HASHMAP_EMPTY 0
#define STL_PRIVATE_HASHMAP_USED 1
#define STL_PRIVATE_HASHMAP_DEAD 2

#ifndef STL_CAT
#define STL_CAT_(a, b)  a##b
#define STL_CAT(a, b)   STL_CAT_(a, b)
#endif

#define STL_PRIVATE_HASHMAP_NAME(NAME, K, V) \
    STL_CAT(STL_CAT(NAME, K), STL_CAT(_, V))

#define stlhashmap(K, V)            STL_PRIVATE_HASHMAP_NAME(stl_DETAIL_hashmap_, K, V)
#define stlhashmapentry(K, V)       STL_PRIVATE_HASHMAP_NAME(stl_DETAIL_hashmap_entry_, K, V)
#define stlhashmapinit(K, V)        STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_init_, K, V)
#define stlhashmapfree(K, V)        STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_free_, K, V)
#define stlhashmapreserve(K, V)     STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_reserve_, K, V)
#define stlhashmapshrink(K, V)      STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_shrink_, K, V)
#define stlhashmapset(K, V)         STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_set_, K, V)
#define stlhashmapfind(K, V)        STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_find_, K, V)
#define stlhashmapfind_const(K, V)  STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_find_const_, K, V)
#define stlhashmapat(K, V)          STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_at_, K, V)
#define stlhashmapat_const(K, V)    STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_at_const_, K, V)
#define stlhashmaperase(K, V)       STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_erase_, K, V)
#define stlhashmapclear(K, V)       STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_clear_, K, V)
#define stlhashmapcopy(K, V)        STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_copy_, K, V)
#define stlhashmapclone(K, V)       STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_clone_, K, V)
#define stlhashmapmove(K, V)        STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_move_, K, V)
#define stlhashmapswap(K, V)        STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_swap_, K, V)
#define stlhashmapcontains(K, V)    STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_contains_, K, V)
#define stlhashmapsize(K, V)        STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_size_, K, V)
#define stlhashmapcapacity(K, V)    STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_capacity_, K, V)
#define stlhashmapempty(K, V)       STL_PRIVATE_HASHMAP_NAME(stl_PUBLIC_hashmap_empty_, K, V)

// MARK: inst
#define stlhashmapinst(K, V) \
    struct stlhashmapentry(K, V) \
    { \
        size_t hash; \
        K key; \
        V value; \
        unsigned char state; \
    }; \
    struct stlhashmap(K, V) \
    { \
        struct stlhashmapentry(K, V)* slots; \
        size_t size; \
        size_t capacity; \
        size_t dead; \
    };

// MARK: decl
#define stlhashmapdecl(K, V, ATTR) \
    struct stlhashmapentry(K, V); \
    typedef struct stlhashmapentry(K, V) stlhashmapentry(K, V); \
    struct stlhashmap(K, V); \
    typedef struct stlhashmap(K, V) stlhashmap(K, V); \
    ATTR void stlhashmapinit(K, V)(stlhashmap(K, V)* me, size_t cap); \
    ATTR void stlhashmapfree(K, V)(stlhashmap(K, V)* me); \
    ATTR void stlhashmapreserve(K, V)(stlhashmap(K, V)* me, size_t cap); \
    ATTR void stlhashmapshrink(K, V)(stlhashmap(K, V)* me); \
    ATTR void stlhashmapset(K, V)(stlhashmap(K, V)* me, K key, V value); \
    ATTR V* stlhashmapfind(K, V)(stlhashmap(K, V)* me, K key); \
    ATTR const V* stlhashmapfind_const(K, V)(const stlhashmap(K, V)* me, K key); \
    ATTR V* stlhashmapat(K, V)(stlhashmap(K, V)* me, K key); \
    ATTR const V* stlhashmapat_const(K, V)(const stlhashmap(K, V)* me, K key); \
    ATTR int stlhashmaperase(K, V)(stlhashmap(K, V)* me, K key); \
    ATTR void stlhashmapclear(K, V)(stlhashmap(K, V)* me); \
    ATTR void stlhashmapcopy(K, V)(stlhashmap(K, V)* dst, const stlhashmap(K, V)* src); \
    ATTR stlhashmap(K, V) stlhashmapclone(K, V)(const stlhashmap(K, V)* me); \
    ATTR void stlhashmapmove(K, V)(stlhashmap(K, V)* dst, stlhashmap(K, V)* src); \
    ATTR void stlhashmapswap(K, V)(stlhashmap(K, V)* a, stlhashmap(K, V)* b); \
    ATTR int stlhashmapcontains(K, V)(const stlhashmap(K, V)* me, K key); \
    ATTR size_t stlhashmapsize(K, V)(const stlhashmap(K, V)* me); \
    ATTR size_t stlhashmapcapacity(K, V)(const stlhashmap(K, V)* me); \
    ATTR int stlhashmapempty(K, V)(const stlhashmap(K, V)* me);

// MARK: impl
#define stlhashmapimpl(K, V, ATTR) \
    static inline size_t STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_capfor_, K, V)(size_t n) \
    { \
        if (n > (size_t)-1 / 2) stlabort(); \
        size_t need = n * 2; \
        size_t cap = STL_PRIVATE_HASHMAP_MIN_CAPACITY; \
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
    static inline void STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_rehash_, K, V) \
        (stlhashmap(K, V)* me, size_t ncap) \
    { \
        if (ncap < STL_PRIVATE_HASHMAP_MIN_CAPACITY) \
            ncap = STL_PRIVATE_HASHMAP_MIN_CAPACITY; \
        if (ncap > (size_t)-1 / sizeof(stlhashmapentry(K, V))) \
            stlabort(); \
        stlhashmapentry(K, V)* ns = \
            (stlhashmapentry(K, V)*)stlrealloc(NULL, ncap * sizeof(stlhashmapentry(K, V))); \
        if (!ns) stlabort(); \
        memset(ns, 0, ncap * sizeof(stlhashmapentry(K, V))); \
        size_t mask = ncap - 1; \
        for (size_t i = 0; i < me->capacity; ++i) \
        { \
            stlhashmapentry(K, V)* e = &me->slots[i]; \
            if (e->state != STL_PRIVATE_HASHMAP_USED) continue; \
            size_t j = e->hash & mask; \
            while (ns[j].state == STL_PRIVATE_HASHMAP_USED) \
                j = (j + 1) & mask; \
            ns[j] = *e; \
        } \
        stlfree(me->slots); \
        me->slots = ns; \
        me->capacity = ncap; \
        me->dead = 0; \
    } \
    static inline stlhashmapentry(K, V)* STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_find_, K, V) \
        (const stlhashmap(K, V)* me, K key, size_t hash) \
    { \
        if (me->capacity == 0) return NULL; \
        size_t mask = me->capacity - 1; \
        size_t i = hash & mask; \
        for (size_t n = 0; n < me->capacity; ++n) \
        { \
            stlhashmapentry(K, V)* e = &me->slots[i]; \
            if (e->state == STL_PRIVATE_HASHMAP_EMPTY) return NULL; \
            if (e->state == STL_PRIVATE_HASHMAP_USED && e->hash == hash \
                && stlequal(K)(e->key, key)) \
                return e; \
            i = (i + 1) & mask; \
        } \
        return NULL; \
    } \
    static inline void STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_make_room_, K, V) \
        (stlhashmap(K, V)* me) \
    { \
        if (me->capacity == 0) \
        { \
            STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_rehash_, K, V)(me, STL_PRIVATE_HASHMAP_MIN_CAPACITY); \
            return; \
        } \
        if (me->size + me->dead + 1 <= me->capacity / 2) \
            return; \
        size_t ncap = me->capacity; \
        if (me->size + 1 > me->capacity / 2) \
            ncap = STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_capfor_, K, V)(me->size + 1); \
        STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_rehash_, K, V)(me, ncap); \
    } \
    ATTR void stlhashmapinit(K, V)(stlhashmap(K, V)* me, size_t cap) \
    { \
        me->slots = NULL; \
        me->size = 0; \
        me->capacity = 0; \
        me->dead = 0; \
        if (cap) stlhashmapreserve(K, V)(me, cap); \
    } \
    ATTR void stlhashmapfree(K, V)(stlhashmap(K, V)* me) \
    { \
        stlfree(me->slots); \
        me->slots = NULL; \
        me->size = 0; \
        me->capacity = 0; \
        me->dead = 0; \
    } \
    ATTR void stlhashmapreserve(K, V)(stlhashmap(K, V)* me, size_t cap) \
    { \
        if (cap == 0) return; \
        size_t ncap = STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_capfor_, K, V)(cap); \
        if (ncap <= me->capacity) return; \
        STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_rehash_, K, V)(me, ncap); \
    } \
    ATTR void stlhashmapshrink(K, V)(stlhashmap(K, V)* me) \
    { \
        if (me->capacity == 0) return; \
        if (me->size == 0) \
        { \
            stlfree(me->slots); \
            me->slots = NULL; \
            me->capacity = 0; \
            me->dead = 0; \
            return; \
        } \
        size_t ncap = STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_capfor_, K, V)(me->size); \
        if (ncap < me->capacity) \
            STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_rehash_, K, V)(me, ncap); \
        else if (me->dead) \
            STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_rehash_, K, V)(me, me->capacity); \
    } \
    ATTR void stlhashmapset(K, V)(stlhashmap(K, V)* me, K key, V value) \
    { \
        size_t hash = stlhash(K)(key); \
        stlhashmapentry(K, V)* e = \
            STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_find_, K, V)(me, key, hash); \
        if (e) \
        { \
            e->value = value; \
            return; \
        } \
        STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_make_room_, K, V)(me); \
        size_t mask = me->capacity - 1; \
        size_t i = hash & mask; \
        while (me->slots[i].state == STL_PRIVATE_HASHMAP_USED) \
            i = (i + 1) & mask; \
        e = &me->slots[i]; \
        if (e->state == STL_PRIVATE_HASHMAP_DEAD) \
            --me->dead; \
        e->hash = hash; \
        e->key = key; \
        e->value = value; \
        e->state = STL_PRIVATE_HASHMAP_USED; \
        ++me->size; \
    } \
    ATTR V* stlhashmapfind(K, V)(stlhashmap(K, V)* me, K key) \
    { \
        stlhashmapentry(K, V)* e = \
            STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_find_, K, V)(me, key, stlhash(K)(key)); \
        return e ? &e->value : NULL; \
    } \
    ATTR const V* stlhashmapfind_const(K, V)(const stlhashmap(K, V)* me, K key) \
    { \
        const stlhashmapentry(K, V)* e = \
            STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_find_, K, V)(me, key, stlhash(K)(key)); \
        return e ? &e->value : NULL; \
    } \
    ATTR V* stlhashmapat(K, V)(stlhashmap(K, V)* me, K key) \
    { \
        V* p = stlhashmapfind(K, V)(me, key); \
        stlassert(p != NULL); \
        return p; \
    } \
    ATTR const V* stlhashmapat_const(K, V)(const stlhashmap(K, V)* me, K key) \
    { \
        const V* p = stlhashmapfind_const(K, V)(me, key); \
        stlassert(p != NULL); \
        return p; \
    } \
    ATTR int stlhashmaperase(K, V)(stlhashmap(K, V)* me, K key) \
    { \
        stlhashmapentry(K, V)* e = \
            STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_find_, K, V)(me, key, stlhash(K)(key)); \
        if (!e) return 0; \
        e->state = STL_PRIVATE_HASHMAP_DEAD; \
        --me->size; \
        ++me->dead; \
        if (me->dead > me->capacity / 4) \
            STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_rehash_, K, V)(me, me->capacity); \
        return 1; \
    } \
    ATTR void stlhashmapclear(K, V)(stlhashmap(K, V)* me) \
    { \
        if (me->capacity) \
            memset(me->slots, 0, me->capacity * sizeof(stlhashmapentry(K, V))); \
        me->size = 0; \
        me->dead = 0; \
    } \
    ATTR void stlhashmapcopy(K, V)(stlhashmap(K, V)* dst, const stlhashmap(K, V)* src) \
    { \
        if (dst == src) return; \
        if (src->capacity == 0) \
        { \
            stlfree(dst->slots); \
            dst->slots = NULL; \
            dst->size = 0; \
            dst->capacity = 0; \
            dst->dead = 0; \
            return; \
        } \
        if (dst->capacity != src->capacity) \
        { \
            if (src->capacity > (size_t)-1 / sizeof(stlhashmapentry(K, V))) \
                stlabort(); \
            stlhashmapentry(K, V)* ns = \
                (stlhashmapentry(K, V)*)stlrealloc(NULL, src->capacity * sizeof(stlhashmapentry(K, V))); \
            if (!ns) stlabort(); \
            stlfree(dst->slots); \
            dst->slots = ns; \
            dst->capacity = src->capacity; \
        } \
        memcpy(dst->slots, src->slots, src->capacity * sizeof(stlhashmapentry(K, V))); \
        dst->size = src->size; \
        dst->dead = src->dead; \
    } \
    ATTR stlhashmap(K, V) stlhashmapclone(K, V)(const stlhashmap(K, V)* me) \
    { \
        stlhashmap(K, V) r; \
        r.slots = NULL; \
        r.size = 0; \
        r.capacity = 0; \
        r.dead = 0; \
        if (me->capacity) \
        { \
            if (me->capacity > (size_t)-1 / sizeof(stlhashmapentry(K, V))) \
                stlabort(); \
            r.slots = (stlhashmapentry(K, V)*)stlrealloc(NULL, me->capacity * sizeof(stlhashmapentry(K, V))); \
            if (!r.slots) stlabort(); \
            memcpy(r.slots, me->slots, me->capacity * sizeof(stlhashmapentry(K, V))); \
            r.size = me->size; \
            r.capacity = me->capacity; \
            r.dead = me->dead; \
        } \
        return r; \
    } \
    ATTR void stlhashmapmove(K, V)(stlhashmap(K, V)* dst, stlhashmap(K, V)* src) \
    { \
        if (dst == src) return; \
        stlfree(dst->slots); \
        dst->slots = src->slots; \
        dst->size = src->size; \
        dst->capacity = src->capacity; \
        dst->dead = src->dead; \
        src->slots = NULL; \
        src->size = 0; \
        src->capacity = 0; \
        src->dead = 0; \
    } \
    ATTR void stlhashmapswap(K, V)(stlhashmap(K, V)* a, stlhashmap(K, V)* b) \
    { \
        stlhashmap(K, V) tmp = *a; \
        *a = *b; \
        *b = tmp; \
    } \
    ATTR int stlhashmapcontains(K, V)(const stlhashmap(K, V)* me, K key) \
    { \
        return STL_PRIVATE_HASHMAP_NAME(stl_PRIVATE_hashmap_find_, K, V)(me, key, stlhash(K)(key)) != NULL; \
    } \
    ATTR size_t stlhashmapsize(K, V)(const stlhashmap(K, V)* me) \
    { \
        return me->size; \
    } \
    ATTR size_t stlhashmapcapacity(K, V)(const stlhashmap(K, V)* me) \
    { \
        return me->capacity / 2; \
    } \
    ATTR int stlhashmapempty(K, V)(const stlhashmap(K, V)* me) \
    { \
        return me->size == 0; \
    }

// MARK: sugar
#define stlhashmapforeach(K, V, ME, IT) \
    for (stlhashmapentry(K, V)* IT = (ME)->slots, *IT##_HIDE_end = (ME)->slots + (ME)->capacity; IT != IT##_HIDE_end; ++IT) \
        if (IT->state == STL_PRIVATE_HASHMAP_USED)
#define stlhashmapforeach_const(K, V, ME, IT) \
    for (const stlhashmapentry(K, V)* IT = (ME)->slots, *IT##_HIDE_end = (ME)->slots + (ME)->capacity; IT != IT##_HIDE_end; ++IT) \
        if (IT->state == STL_PRIVATE_HASHMAP_USED)

#endif
