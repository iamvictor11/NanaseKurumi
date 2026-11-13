// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_XKSTRING_H
#define XK_XKSTRING_H

#include "xkvector.h"
#include "xkequal.h"
#include "xkhash.h"
#include "xkcompare.h"

typedef struct xkstring
{
    char* data;
    size_t size;
    size_t capacity;
} xkstring;

#define XK_PRIVATE_STRING_OVERLAPPING(ME, P, N) \
    ((ME)->data != NULL && \
    (uintptr_t)(P) < (uintptr_t)((ME)->data) + (ME)->size * sizeof(*(ME)->data) && \
    (uintptr_t)(P) + (uintptr_t)(N) * sizeof(*(ME)->data) > (uintptr_t)((ME)->data))

static inline void xkstringinit(xkstring* me, size_t cap)
{
    me->data = (char*)xkrealloc(NULL, cap + 1);
    if (!me->data) xkabort();
    me->data[0] = 0;
    me->size = 0;
    me->capacity = cap;
}
static inline void xkstringfree(xkstring* me)
{
    xkfree(me->data);
    me->data = NULL;
    me->size = 0;
    me->capacity = 0;
}
static inline void xkstringreserve(xkstring* me, size_t cap)
{
    if (cap <= me->capacity) return;
    size_t nc = me->capacity ? me->capacity : cap;
    while (nc < cap)
    {
        if (nc > (size_t)-1 / 2)
        {
            nc = cap;
            break;
        }
        nc *= 2;
    }
    char* p = (char*)xkrealloc(me->data, nc + 1);
    if (!p) xkabort();
    me->data = p;
    me->capacity = nc;
    me->data[me->size] = 0;
}
static inline void xkstringresize(xkstring* me, size_t n)
{
    if (n > me->capacity)
        xkstringreserve(me, n);
    if (n > me->size)
        memset(me->data + me->size, 0, n - me->size);
    me->size = n;
    me->data[me->size] = 0;
}
static inline void xkstringshrink(xkstring* me)
{
    if (me->size == me->capacity) return;
    char* p = (char*)xkrealloc(me->data, me->size + 1);
    if (!p) xkabort();
    me->data = p;
    me->capacity = me->size;
    me->data[me->size] = 0;
}
static inline void xkstringpush(xkstring* me, char e)
{
    if (me->size == me->capacity)
        xkstringreserve(me, me->size + 1);
    me->data[me->size++] = e;
    me->data[me->size] = 0;
}
static inline void xkstringappend(xkstring* me, const char* p, size_t n)
{
    if (n == 0) return;
    if (n > (size_t)-1 - me->size) xkabort();
    char* tmp = NULL;
    if (XK_STRING_OVERLAPPING(me, p, n))
    {
        tmp = (char*)xkrealloc(NULL, n);
        if (!tmp) xkabort();
        memcpy(tmp, p, n);
        p = tmp;
    }
    if (me->size + n > me->capacity)
        xkstringreserve(me, me->size + n);
    memcpy(me->data + me->size, p, n);
    me->size += n;
    me->data[me->size] = 0;
    if (tmp) xkfree(tmp);
}
static inline char xkstringpop(xkstring* me)
{
    assert(me->size > 0);
    char e = me->data[--me->size];
    me->data[me->size] = 0;
    return e;
}
static inline char* xkstringdata(xkstring* me) { return me->data; }
static inline const char* xkstringdata_const(const xkstring* me) { return me->data; }
static inline const char* xkstringc_str(const xkstring* me) { return me->data; }
static inline char xkstringget(const xkstring* me, size_t i)
{
    assert(i < me->size);
    return me->data[i];
}
static inline void xkstringset(xkstring* me, size_t i, char e)
{
    assert(i < me->size);
    me->data[i] = e;
}
static inline char* xkstringat(xkstring* me, size_t i)
{
    assert(i < me->size);
    return &me->data[i];
}
static inline const char* xkstringat_const(const xkstring* me, size_t i)
{
    assert(i < me->size);
    return &me->data[i];
}
static inline char* xkstringfront(xkstring* me)
{
    assert(me->size > 0);
    return &me->data[0];
}
static inline const char* xkstringfront_const(const xkstring* me)
{
    assert(me->size > 0);
    return &me->data[0];
}
static inline char* xkstringback(xkstring* me)
{
    assert(me->size > 0);
    return &me->data[me->size - 1];
}
static inline const char* xkstringback_const(const xkstring* me)
{
    assert(me->size > 0);
    return &me->data[me->size - 1];
}
static inline void xkstringinsert(xkstring* me, size_t i, char e)
{
    assert(i <= me->size);
    if (me->size == me->capacity)
        xkstringreserve(me, me->size + 1);
    memmove(&me->data[i + 1], &me->data[i], me->size - i);
    me->data[i] = e;
    me->size++;
    me->data[me->size] = 0;
}
static inline void xkstringsplice(xkstring* me, size_t i, const char* p, size_t n)
{
    assert(i <= me->size);
    if (n == 0) return;
    if (n > (size_t)-1 - me->size) xkabort();
    char* tmp = NULL;
    if (XK_STRING_OVERLAPPING(me, p, n))
    {
        tmp = (char*)xkrealloc(NULL, n);
        if (!tmp) xkabort();
        memcpy(tmp, p, n);
        p = tmp;
    }
    if (me->size + n > me->capacity)
        xkstringreserve(me, me->size + n);
    memmove(&me->data[i + n], &me->data[i], me->size - i);
    memcpy(&me->data[i], p, n);
    me->size += n;
    me->data[me->size] = 0;
    if (tmp) xkfree(tmp);
}
static inline void xkstringerase(xkstring* me, size_t i)
{
    assert(i < me->size);
    memmove(&me->data[i], &me->data[i + 1], me->size - i - 1);
    me->size--;
    me->data[me->size] = 0;
}
static inline void xkstringcutout(xkstring* me, size_t i, size_t n)
{
    assert(i <= me->size);
    assert(n <= me->size - i);
    if (n == 0) return;
    memmove(&me->data[i], &me->data[i + n], me->size - i - n);
    me->size -= n;
    me->data[me->size] = 0;
}
static inline void xkstringoverwrite(xkstring* me, size_t i, const char* p, size_t n)
{
    if (n == 0) return;
    if (n > (size_t)-1 - i) xkabort();
    char* tmp = NULL;
    if (XK_STRING_OVERLAPPING(me, p, n))
    {
        tmp = (char*)xkrealloc(NULL, n);
        if (!tmp) xkabort();
        memcpy(tmp, p, n);
        p = tmp;
    }
    if (i + n > me->size)
        xkstringresize(me, i + n);
    memmove(&me->data[i], p, n);
    me->data[me->size] = 0;
    if (tmp) xkfree(tmp);
}
static inline void xkstringclear(xkstring* me)
{
    me->size = 0;
    me->data[0] = 0;
}
static inline void xkstringassign(xkstring* me, const char* p, size_t n)
{
    if (n == 0)
    {
        xkstringclear(me);
        return;
    }
    char* tmp = NULL;
    if (XK_STRING_OVERLAPPING(me, p, n))
    {
        tmp = (char*)xkrealloc(NULL, n);
        if (!tmp) xkabort();
        memcpy(tmp, p, n);
        p = tmp;
    }
    xkstringclear(me);
    xkstringappend(me, p, n);
    if (tmp) xkfree(tmp);
}
static inline void xkstringcopy(xkstring* dst, const xkstring* src)
{
    if (dst == src) return;
    xkstringclear(dst);
    if (src->size > dst->capacity)
        xkstringreserve(dst, src->size);
    if (src->size)
        memcpy(dst->data, src->data, src->size);
    dst->size = src->size;
    dst->data[dst->size] = 0;
}
static inline xkstring xkstringclone(const xkstring* me)
{
    xkstring r;
    xkstringinit(&r, me->size);
    if (me->size)
        memcpy(r.data, me->data, me->size);
    r.size = me->size;
    r.data[r.size] = 0;
    return r;
}
static inline xkstring xkstringsub(const xkstring* me, size_t start, size_t n)
{
    assert(start <= me->size);
    assert(n <= me->size - start);
    xkstring r;
    xkstringinit(&r, n);
    if (n) memcpy(r.data, me->data + start, n);
    r.size = n;
    r.data[r.size] = 0;
    return r;
}
static inline void xkstringmove(xkstring* dst, xkstring* src)
{
    if (dst == src) return;
    xkfree(dst->data);
    dst->data = src->data;
    dst->size = src->size;
    dst->capacity = src->capacity;
    src->data = (char*)xkrealloc(NULL, 1);
    if (!src->data) xkabort();
    src->data[0] = 0;
    src->size = 0;
    src->capacity = 0;
}
static inline void xkstringswap(xkstring* a, xkstring* b)
{
    xkstring tmp = *a;
    *a = *b;
    *b = tmp;
}
static inline size_t xkstringfind(const xkstring* me, char e)
{
    for (size_t i = 0; i < me->size; ++i)
        if (me->data[i] == e)
            return i;
    return (size_t)-1;
}
static inline size_t xkstringmatch(const xkstring* me, const char* p, size_t n)
{
    if (n == 0) return 0;
    if (n > me->size) return (size_t)-1;
    for (size_t i = 0; i <= me->size - n; ++i)
        if (memcmp(&me->data[i], p, n) == 0)
            return i;
    return (size_t)-1;
}
static inline int xkstringcontains(const xkstring* me, char e)
{
    return xkstringfind(me, e) != (size_t)-1;
}
static inline int xkstringsuffix(const xkstring* me, const char* p, size_t n)
{
    return n <= me->size && memcmp(me->data, p, n) == 0;
}
static inline int xkstringprefix(const xkstring* me, const char* p, size_t n)
{
    return n <= me->size && memcmp(me->data + me->size - n, p, n) == 0;
}
static inline size_t xkstringsize(const xkstring* me) { return me->size; }
static inline size_t xkstringlength(const xkstring* me) { return me->size; }
static inline size_t xkstringcapacity(const xkstring* me) { return me->capacity; }
static inline int xkstringempty(const xkstring* me) { return me->size == 0; }
static inline xkstring xkstringconcat(const xkstring* a, const xkstring* b)
{
    if (a->size > (size_t)-1 - b->size) xkabort();
    size_t total = a->size + b->size;
    xkstring r;
    xkstringinit(&r, total);
    if (a->size) memcpy(r.data, a->data, a->size);
    if (b->size) memcpy(r.data + a->size, b->data, b->size);
    r.size = total;
    r.data[r.size] = 0;
    return r;
}
static inline xkview(char) xkstringview(const xkstring* me)
{
    xkview(char) r = { me->data, me->size };
    return r;
}
static inline xkspan(char) xkstringspan(xkstring* me)
{
    xkspan(char) r = { me->data, me->size };
    return r;
}

static inline bool xkequal(xkstring)(xkstring a, xkstring b)
{
    if (a.size != b.size) return false;
    return a.size == 0 || memcmp(a.data, b.data, a.size) == 0;
}
static inline int xkcompare(xkstring)(xkstring a, xkstring b)
{
    size_t n = a.size < b.size ? a.size : b.size;
    int r = n ? memcmp(a.data, b.data, n) : 0;
    if (r != 0) return r;
    if (a.size < b.size) return -1;
    if (a.size > b.size) return 1;
    return 0;
}
static inline size_t xkhash(xkstring)(xkstring v)
{
    constexpr uint64_t FNV_OFFSET = 0xCBF29CE484222325ull;
    constexpr uint64_t FNV_PRIME  = 0x100000001B3ull;

    uint64_t h = FNV_OFFSET ^ (uint64_t)v.size;
    for (size_t i = 0; i < v.size; ++i)
    {
        h ^= (uint8_t)v.data[i];
        h *= FNV_PRIME;
    }
    return xk_PRIVATE_hash_mix64(h);
}

#endif
