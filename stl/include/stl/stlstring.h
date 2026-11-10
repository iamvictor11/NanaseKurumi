// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef STL_STRING_H
#define STL_STRING_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#ifndef STL_STRING_REALLOC
#define STL_STRING_REALLOC realloc
#endif

#ifndef STL_STRING_FREE
#define STL_STRING_FREE free
#endif

#ifndef STL_STRING_ABORT
#define STL_STRING_ABORT abort
#endif

typedef struct stlstring
{
    char* data;
    size_t size;
    size_t capacity;
} stlstring;

#define STL_VECTOR_OVERLAPPING(ME, P, N) \
    ((ME)->data != NULL && \
    (uintptr_t)(P) < (uintptr_t)((ME)->data) + (ME)->size * sizeof(*(ME)->data) && \
    (uintptr_t)(P) + (uintptr_t)(N) * sizeof(*(ME)->data) > (uintptr_t)((ME)->data))

static inline void stlstringinit(stlstring* me, size_t cap)
{
    me->data = (char*)STL_STRING_REALLOC(NULL, cap + 1);
    if (!me->data) STL_STRING_ABORT();
    me->data[0] = 0;
    me->size = 0;
    me->capacity = cap;
}
static inline void stlstringfree(stlstring* me)
{
    STL_STRING_FREE(me->data);
    me->data = NULL;
    me->size = 0;
    me->capacity = 0;
}
static inline void stlstringreserve(stlstring* me, size_t cap)
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
    char* p = (char*)STL_STRING_REALLOC(me->data, nc + 1);
    if (!p) STL_STRING_ABORT();
    me->data = p;
    me->capacity = nc;
    me->data[me->size] = 0;
}
static inline void stlstringresize(stlstring* me, size_t n)
{
    if (n > me->capacity)
        stlstringreserve(me, n);
    if (n > me->size)
        memset(me->data + me->size, 0, n - me->size);
    me->size = n;
    me->data[me->size] = 0;
}
static inline void stlstringshrink(stlstring* me)
{
    if (me->size == me->capacity) return;
    char* p = (char*)STL_STRING_REALLOC(me->data, me->size + 1);
    if (!p) STL_STRING_ABORT();
    me->data = p;
    me->capacity = me->size;
    me->data[me->size] = 0;
}
static inline void stlstringpush(stlstring* me, char e)
{
    if (me->size == me->capacity)
        stlstringreserve(me, me->size + 1);
    me->data[me->size++] = e;
    me->data[me->size] = 0;
}
static inline void stlstringappend(stlstring* me, const char* p, size_t n)
{
    if (n == 0) return;
    if (n > (size_t)-1 - me->size) STL_STRING_ABORT();
    char* tmp = NULL;
    if (STL_STRING_OVERLAPPING(me, p, n))
    {
        tmp = (char*)STL_STRING_REALLOC(NULL, n);
        if (!tmp) STL_STRING_ABORT();
        memcpy(tmp, p, n);
        p = tmp;
    }
    if (me->size + n > me->capacity)
        stlstringreserve(me, me->size + n);
    memcpy(me->data + me->size, p, n);
    me->size += n;
    me->data[me->size] = 0;
    if (tmp) STL_STRING_FREE(tmp);
}
static inline void stlstringappend_cstr(stlstring* me, const char* p)
{
    stlstringappend(me, p, strlen(p));
}
static inline char stlstringpop(stlstring* me)
{
    assert(me->size > 0);
    char e = me->data[--me->size];
    me->data[me->size] = 0;
    return e;
}
static inline char* stlstringdata(stlstring* me) { return me->data; }
static inline const char* stlstringdata_const(const stlstring* me) { return me->data; }
static inline const char* stlstringc_str(const stlstring* me) { return me->data; }
static inline char stlstringget(const stlstring* me, size_t i)
{
    assert(i < me->size);
    return me->data[i];
}
static inline void stlstringset(stlstring* me, size_t i, char e)
{
    assert(i < me->size);
    me->data[i] = e;
}
static inline char* stlstringat(stlstring* me, size_t i)
{
    assert(i < me->size);
    return &me->data[i];
}
static inline const char* stlstringat_const(const stlstring* me, size_t i)
{
    assert(i < me->size);
    return &me->data[i];
}
static inline char* stlstringfront(stlstring* me)
{
    assert(me->size > 0);
    return &me->data[0];
}
static inline const char* stlstringfront_const(const stlstring* me)
{
    assert(me->size > 0);
    return &me->data[0];
}
static inline char* stlstringback(stlstring* me)
{
    assert(me->size > 0);
    return &me->data[me->size - 1];
}
static inline const char* stlstringback_const(const stlstring* me)
{
    assert(me->size > 0);
    return &me->data[me->size - 1];
}
static inline void stlstringinsert(stlstring* me, size_t i, char e)
{
    assert(i <= me->size);
    if (me->size == me->capacity)
        stlstringreserve(me, me->size + 1);
    memmove(&me->data[i + 1], &me->data[i], me->size - i);
    me->data[i] = e;
    me->size++;
    me->data[me->size] = 0;
}
static inline void stlstringsplice(stlstring* me, size_t i, const char* p, size_t n)
{
    assert(i <= me->size);
    if (n == 0) return;
    if (n > (size_t)-1 - me->size) STL_STRING_ABORT();
    char* tmp = NULL;
    if (STL_STRING_OVERLAPPING(me, p, n))
    {
        tmp = (char*)STL_STRING_REALLOC(NULL, n);
        if (!tmp) STL_STRING_ABORT();
        memcpy(tmp, p, n);
        p = tmp;
    }
    if (me->size + n > me->capacity)
        stlstringreserve(me, me->size + n);
    memmove(&me->data[i + n], &me->data[i], me->size - i);
    memcpy(&me->data[i], p, n);
    me->size += n;
    me->data[me->size] = 0;
    if (tmp) STL_STRING_FREE(tmp);
}
static inline void stlstringerase(stlstring* me, size_t i)
{
    assert(i < me->size);
    memmove(&me->data[i], &me->data[i + 1], me->size - i - 1);
    me->size--;
    me->data[me->size] = 0;
}
static inline void stlstringcutout(stlstring* me, size_t i, size_t n)
{
    assert(i <= me->size);
    assert(n <= me->size - i);
    if (n == 0) return;
    memmove(&me->data[i], &me->data[i + n], me->size - i - n);
    me->size -= n;
    me->data[me->size] = 0;
}
static inline void stlstringoverwrite(stlstring* me, size_t i, const char* p, size_t n)
{
    if (n == 0) return;
    if (n > (size_t)-1 - i) STL_STRING_ABORT();
    char* tmp = NULL;
    if (STL_STRING_OVERLAPPING(me, p, n))
    {
        tmp = (char*)STL_STRING_REALLOC(NULL, n);
        if (!tmp) STL_STRING_ABORT();
        memcpy(tmp, p, n);
        p = tmp;
    }
    if (i + n > me->size)
        stlstringresize(me, i + n);
    memmove(&me->data[i], p, n);
    me->data[me->size] = 0;
    if (tmp) STL_STRING_FREE(tmp);
}
static inline void stlstringclear(stlstring* me)
{
    me->size = 0;
    me->data[0] = 0;
}
static inline void stlstringassign(stlstring* me, const char* p, size_t n)
{
    if (n == 0)
    {
        stlstringclear(me);
        return;
    }
    char* tmp = NULL;
    if (STL_STRING_OVERLAPPING(me, p, n))
    {
        tmp = (char*)STL_STRING_REALLOC(NULL, n);
        if (!tmp) STL_STRING_ABORT();
        memcpy(tmp, p, n);
        p = tmp;
    }
    stlstringclear(me);
    stlstringappend(me, p, n);
    if (tmp) STL_STRING_FREE(tmp);
}
static inline void stlstringcopy(stlstring* dst, const stlstring* src)
{
    if (dst == src) return;
    stlstringclear(dst);
    if (src->size > dst->capacity)
        stlstringreserve(dst, src->size);
    if (src->size)
        memcpy(dst->data, src->data, src->size);
    dst->size = src->size;
    dst->data[dst->size] = 0;
}
static inline stlstring stlstringclone(const stlstring* me)
{
    stlstring r;
    stlstringinit(&r, me->size);
    if (me->size)
        memcpy(r.data, me->data, me->size);
    r.size = me->size;
    r.data[r.size] = 0;
    return r;
}
static inline stlstring stlstringsub(const stlstring* me, size_t start, size_t n)
{
    assert(start <= me->size);
    assert(n <= me->size - start);
    stlstring r;
    stlstringinit(&r, n);
    if (n) memcpy(r.data, me->data + start, n);
    r.size = n;
    r.data[r.size] = 0;
    return r;
}
static inline void stlstringmove(stlstring* dst, stlstring* src)
{
    if (dst == src) return;
    STL_STRING_FREE(dst->data);
    dst->data = src->data;
    dst->size = src->size;
    dst->capacity = src->capacity;
    src->data = (char*)STL_STRING_REALLOC(NULL, 1);
    if (!src->data) STL_STRING_ABORT();
    src->data[0] = 0;
    src->size = 0;
    src->capacity = 0;
}
static inline void stlstringswap(stlstring* a, stlstring* b)
{
    stlstring tmp = *a;
    *a = *b;
    *b = tmp;
}
static inline size_t stlstringfind(const stlstring* me, char e)
{
    for (size_t i = 0; i < me->size; ++i)
        if (me->data[i] == e)
            return i;
    return (size_t)-1;
}
static inline size_t stlstringmatch(const stlstring* me, const char* p, size_t n)
{
    if (n == 0) return 0;
    if (n > me->size) return (size_t)-1;
    for (size_t i = 0; i <= me->size - n; ++i)
        if (memcmp(&me->data[i], p, n) == 0)
            return i;
    return (size_t)-1;
}
static inline int stlstringcontains(const stlstring* me, char e)
{
    return stlstringfind(me, e) != (size_t)-1;
}
static inline int stlstringsuffix(const stlstring* me, const char* p, size_t n)
{
    return n <= me->size && memcmp(me->data, p, n) == 0;
}
static inline int stlstringprefix(const stlstring* me, const char* p, size_t n)
{
    return n <= me->size && memcmp(me->data + me->size - n, p, n) == 0;
}
static inline int stlstringcompare(const stlstring* a, const stlstring* b)
{
    size_t n = a->size < b->size ? a->size : b->size;
    int r = n ? memcmp(a->data, b->data, n) : 0;
    if (r != 0) return r;
    if (a->size < b->size) return -1;
    if (a->size > b->size) return 1;
    return 0;
}
static inline size_t stlstringsize(const stlstring* me) { return me->size; }
static inline size_t stlstringlength(const stlstring* me) { return me->size; }
static inline size_t stlstringcapacity(const stlstring* me) { return me->capacity; }
static inline int stlstringempty(const stlstring* me) { return me->size == 0; }
static inline stlstring stlstringconcat(const stlstring* a, const stlstring* b)
{
    if (a->size > (size_t)-1 - b->size) STL_STRING_ABORT();
    size_t total = a->size + b->size;
    stlstring r;
    stlstringinit(&r, total);
    if (a->size) memcpy(r.data, a->data, a->size);
    if (b->size) memcpy(r.data + a->size, b->data, b->size);
    r.size = total;
    r.data[r.size] = 0;
    return r;
}

#endif
