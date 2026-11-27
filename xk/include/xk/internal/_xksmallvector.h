// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__XKSMALLVECTOR_H
#define XK_INTERNAL__XKSMALLVECTOR_H

#include "_xkconf.h"
#include "_xkvector.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef XK_CAT
#define XK_CAT_(a, b)   a##b
#define XK_CAT(a, b)    XK_CAT_(a, b)
#endif

#define XK_PRIVATE_SMALLVECTOR_MIN_CAPACITY 8

#define XK_PRIVATE_SMALLVECTOR_NAME(NAME, T, N) \
    XK_CAT(XK_CAT(NAME, T), XK_CAT(_, N))

#define XK_PRIVATE_SMALLVECTOR_OVERLAPPING(D, CAP, P, N) \
    ((CAP) > 0 && \
    (uintptr_t)(P) < (uintptr_t)(D) + (CAP) * sizeof(*(D)) && \
    (uintptr_t)(P) + (uintptr_t)(N) * sizeof(*(D)) > (uintptr_t)(D))

#define xksmallvector(T, N)              XK_PRIVATE_SMALLVECTOR_NAME(xksmallvector_, T, N)
#define xksmallvectorinit(T, N)          XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_init_, T, N)
#define xksmallvectorfree(T, N)          XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_free_, T, N)
#define xksmallvectorreserve(T, N)       XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_reserve_, T, N)
#define xksmallvectorresize(T, N)        XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_resize_, T, N)
#define xksmallvectorshrink(T, N)        XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_shrink_, T, N)
#define xksmallvectorpushfront(T, N)     XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_pushfront_, T, N)
#define xksmallvectorpushback(T, N)      XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_pushback_, T, N)
#define xksmallvectoremplacefront(T, N)  XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_emplacefront_, T, N)
#define xksmallvectoremplaceback(T, N)   XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_emplaceback_, T, N)
#define xksmallvectorappend(T, N)        XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_append_, T, N)
#define xksmallvectorpopfront(T, N)      XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_popfront_, T, N)
#define xksmallvectorpopback(T, N)       XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_popback_, T, N)
#define xksmallvectordata(T, N)          XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_data_, T, N)
#define xksmallvectordata_const(T, N)    XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_data_const_, T, N)
#define xksmallvectorget(T, N)           XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_get_, T, N)
#define xksmallvectorset(T, N)           XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_set_, T, N)
#define xksmallvectorat(T, N)            XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_at_, T, N)
#define xksmallvectorat_const(T, N)      XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_at_const_, T, N)
#define xksmallvectorfront(T, N)         XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_front_, T, N)
#define xksmallvectorfront_const(T, N)   XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_front_const_, T, N)
#define xksmallvectorback(T, N)          XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_back_, T, N)
#define xksmallvectorback_const(T, N)    XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_back_const_, T, N)
#define xksmallvectorinsertbefore(T, N)  XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_insertbefore_, T, N)
#define xksmallvectorinsertafter(T, N)   XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_insertafter_, T, N)
#define xksmallvectorerase(T, N)         XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_erase_, T, N)
#define xksmallvectorcutout(T, N)        XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_cutout_, T, N)
#define xksmallvectoroverwrite(T, N)     XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_overwrite_, T, N)
#define xksmallvectorclear(T, N)         XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_clear_, T, N)
#define xksmallvectorassign(T, N)        XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_assign_, T, N)
#define xksmallvectorcopy(T, N)          XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_copy_, T, N)
#define xksmallvectorclone(T, N)         XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_clone_, T, N)
#define xksmallvectormove(T, N)          XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_move_, T, N)
#define xksmallvectorswap(T, N)          XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_swap_, T, N)
#define xksmallvectorsize(T, N)          XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_size_, T, N)
#define xksmallvectorcapacity(T, N)      XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_capacity_, T, N)
#define xksmallvectorempty(T, N)         XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_empty_, T, N)
#define xksmallvectorview(T, N)          XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_view_, T, N)
#define xksmallvectorspan(T, N)          XK_PRIVATE_SMALLVECTOR_NAME(xk_PUBLIC_smallvector_span_, T, N)

// MARK: decl
#define xksmallvectordecl(T, N, ATTR) \
    typedef struct xksmallvector(T, N) \
    { \
        union \
        { \
        T storage[((N) ? (N) : 1)]; \
        T* heap; \
        }; \
        size_t size; \
        size_t capacity; \
    } xksmallvector(T, N); \
    ATTR void xksmallvectorinit(T, N)(xksmallvector(T, N)* me); \
    ATTR void xksmallvectorfree(T, N)(xksmallvector(T, N)* me); \
    ATTR void xksmallvectorreserve(T, N)(xksmallvector(T, N)* me, size_t cap); \
    ATTR void xksmallvectorresize(T, N)(xksmallvector(T, N)* me, size_t n); \
    ATTR void xksmallvectorshrink(T, N)(xksmallvector(T, N)* me); \
    ATTR void xksmallvectorpushfront(T, N)(xksmallvector(T, N)* me, T e); \
    ATTR void xksmallvectorpushback(T, N)(xksmallvector(T, N)* me, T e); \
    ATTR T* xksmallvectoremplacefront(T, N)(xksmallvector(T, N)* me); \
    ATTR T* xksmallvectoremplaceback(T, N)(xksmallvector(T, N)* me); \
    ATTR void xksmallvectorappend(T, N)(xksmallvector(T, N)* me, const T* p, size_t n); \
    ATTR void xksmallvectorpopfront(T, N)(xksmallvector(T, N)* me); \
    ATTR void xksmallvectorpopback(T, N)(xksmallvector(T, N)* me); \
    ATTR T* xksmallvectordata(T, N)(xksmallvector(T, N)* me); \
    ATTR const T* xksmallvectordata_const(T, N)(const xksmallvector(T, N)* me); \
    ATTR T xksmallvectorget(T, N)(const xksmallvector(T, N)* me, size_t i); \
    ATTR void xksmallvectorset(T, N)(xksmallvector(T, N)* me, size_t i, T e); \
    ATTR T* xksmallvectorat(T, N)(xksmallvector(T, N)* me, size_t i); \
    ATTR const T* xksmallvectorat_const(T, N)(const xksmallvector(T, N)* me, size_t i); \
    ATTR T* xksmallvectorfront(T, N)(xksmallvector(T, N)* me); \
    ATTR const T* xksmallvectorfront_const(T, N)(const xksmallvector(T, N)* me); \
    ATTR T* xksmallvectorback(T, N)(xksmallvector(T, N)* me); \
    ATTR const T* xksmallvectorback_const(T, N)(const xksmallvector(T, N)* me); \
    ATTR void xksmallvectorinsertbefore(T, N)(xksmallvector(T, N)* me, size_t i, T e); \
    ATTR void xksmallvectorinsertafter(T, N)(xksmallvector(T, N)* me, size_t i, T e); \
    ATTR void xksmallvectorerase(T, N)(xksmallvector(T, N)* me, size_t i); \
    ATTR void xksmallvectorcutout(T, N)(xksmallvector(T, N)* me, size_t i, size_t n); \
    ATTR void xksmallvectoroverwrite(T, N)(xksmallvector(T, N)* me, size_t i, const T* p, size_t n); \
    ATTR void xksmallvectorclear(T, N)(xksmallvector(T, N)* me); \
    ATTR void xksmallvectorassign(T, N)(xksmallvector(T, N)* me, const T* p, size_t n); \
    ATTR void xksmallvectorcopy(T, N)(xksmallvector(T, N)* dst, const xksmallvector(T, N)* src); \
    ATTR xksmallvector(T, N) xksmallvectorclone(T, N)(const xksmallvector(T, N)* me); \
    ATTR void xksmallvectormove(T, N)(xksmallvector(T, N)* dst, xksmallvector(T, N)* src); \
    ATTR void xksmallvectorswap(T, N)(xksmallvector(T, N)* a, xksmallvector(T, N)* b); \
    ATTR size_t xksmallvectorsize(T, N)(const xksmallvector(T, N)* me); \
    ATTR size_t xksmallvectorcapacity(T, N)(const xksmallvector(T, N)* me); \
    ATTR int xksmallvectorempty(T, N)(const xksmallvector(T, N)* me); \
    ATTR xkview(T) xksmallvectorview(T, N)(const xksmallvector(T, N)* me); \
    ATTR xkspan(T) xksmallvectorspan(T, N)(xksmallvector(T, N)* me);

// MARK: impl
#define xksmallvectorimpl(T, N, ATTR) \
    static inline T* XK_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(xksmallvector(T, N)* me) \
    { \
        return me->capacity > (size_t)(N) ? me->heap : me->storage; \
    } \
    static inline const T* XK_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_const_, T, N)(const xksmallvector(T, N)* me) \
    { \
        return me->capacity > (size_t)(N) ? me->heap : me->storage; \
    } \
    ATTR void xksmallvectorinit(T, N)(xksmallvector(T, N)* me) \
    { \
        me->size = 0; \
        me->capacity = (size_t)(N); \
    } \
    ATTR void xksmallvectorfree(T, N)(xksmallvector(T, N)* me) \
    { \
        if (me->capacity > (size_t)(N)) xkfree(me->heap); \
        me->size = 0; \
        me->capacity = (size_t)(N); \
    } \
    ATTR void xksmallvectorreserve(T, N)(xksmallvector(T, N)* me, size_t cap) \
    { \
        if (me->capacity < (size_t)(N)) \
            me->capacity = (size_t)(N); \
        if (cap <= me->capacity) return; \
        const size_t maxcap = (size_t)-1 / sizeof(T); \
        if (cap > maxcap) xkabort(); \
        size_t nc = me->capacity \
            ? me->capacity \
            : (cap < XK_PRIVATE_SMALLVECTOR_MIN_CAPACITY ? XK_PRIVATE_SMALLVECTOR_MIN_CAPACITY : cap); \
        if (nc < cap) \
        { \
            if (nc > maxcap / 2) nc = cap; \
            else \
            { \
                nc *= 2; \
                if (nc < cap) nc = cap; \
            } \
        } \
        T* p; \
        if (me->capacity > (size_t)(N)) \
        { \
            p = (T*)xkrealloc(me->heap, nc * sizeof(T)); \
            if (!p) xkabort(); \
        } \
        else \
        { \
            p = (T*)xkrealloc(NULL, nc * sizeof(T)); \
            if (!p) xkabort(); \
            if (me->size) memcpy(p, me->storage, me->size * sizeof(T)); \
        } \
        me->heap = p; \
        me->capacity = nc; \
    } \
    ATTR void xksmallvectorresize(T, N)(xksmallvector(T, N)* me, size_t n) \
    { \
        if (n > me->capacity) xksmallvectorreserve(T, N)(me, n); \
        if (n > me->size) \
            memset(xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me) + me->size, \
                0, (n - me->size) * sizeof(T)); \
        me->size = n; \
    } \
    ATTR void xksmallvectorshrink(T, N)(xksmallvector(T, N)* me) \
    { \
        size_t base = (size_t)(N); \
        size_t target = me->size > base ? me->size : base; \
        if (me->capacity == target) return; \
        if (me->size <= base) \
        { \
            if (me->capacity > base) \
            { \
                T* h = me->heap; \
                if (me->size) memcpy(me->storage, h, me->size * sizeof(T)); \
                xkfree(h); \
            } \
            me->capacity = base; \
        } \
        else \
        { \
            T* p = (T*)xkrealloc(me->heap, me->size * sizeof(T)); \
            if (!p) xkabort(); \
            me->heap = p; \
            me->capacity = me->size; \
        } \
    } \
    ATTR void xksmallvectorpushfront(T, N)(xksmallvector(T, N)* me, T e) \
    { \
        *xksmallvectoremplacefront(T, N)(me) = e; \
    } \
    ATTR void xksmallvectorpushback(T, N)(xksmallvector(T, N)* me, T e) \
    { \
        *xksmallvectoremplaceback(T, N)(me) = e; \
    } \
    ATTR T* xksmallvectoremplacefront(T, N)(xksmallvector(T, N)* me) \
    { \
        if (me->size == me->capacity) \
            xksmallvectorreserve(T, N)(me, me->size + 1); \
        T* d = xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me); \
        if (me->size) \
            memmove(&d[1], &d[0], me->size * sizeof(T)); \
        ++me->size; \
        return &d[0]; \
    } \
    ATTR T* xksmallvectoremplaceback(T, N)(xksmallvector(T, N)* me) \
    { \
        if (me->size == me->capacity) \
            xksmallvectorreserve(T, N)(me, me->size + 1); \
        T* d = xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me); \
        return &d[me->size++]; \
    } \
    ATTR void xksmallvectorappend(T, N)(xksmallvector(T, N)* me, const T* p, size_t n) \
    { \
        if (n == 0) return; \
        if (n > (size_t)-1 / sizeof(T) || n > (size_t)-1 - me->size) \
            xkabort(); \
        T* d = xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me); \
        T* tmp = NULL; \
        if (XK_PRIVATE_SMALLVECTOR_OVERLAPPING(d, me->capacity, p, n)) \
        { \
            tmp = (T*)xkrealloc(NULL, n * sizeof(T)); \
            if (!tmp) xkabort(); \
            memcpy(tmp, p, n * sizeof(T)); \
            p = tmp; \
        } \
        if (me->size + n > me->capacity) \
            xksmallvectorreserve(T, N)(me, me->size + n); \
        d = xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me); \
        memcpy(d + me->size, p, n * sizeof(T)); \
        me->size += n; \
        if (tmp) xkfree(tmp); \
    } \
    ATTR void xksmallvectorpopfront(T, N)(xksmallvector(T, N)* me) \
    { \
        xkassert(me->size > 0); \
        T* d = xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me); \
        if (me->size > 1) \
            memmove(&d[0], &d[1], (me->size - 1) * sizeof(T)); \
        --me->size; \
    } \
    ATTR void xksmallvectorpopback(T, N)(xksmallvector(T, N)* me) \
    { \
        xkassert(me->size > 0); \
        --me->size; \
    } \
    ATTR T* xksmallvectordata(T, N)(xksmallvector(T, N)* me) \
    { \
        return xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me); \
    } \
    ATTR const T* xksmallvectordata_const(T, N)(const xksmallvector(T, N)* me) \
    { \
        return xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_const_, T, N)(me); \
    } \
    ATTR T xksmallvectorget(T, N)(const xksmallvector(T, N)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        return xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_const_, T, N)(me)[i]; \
    } \
    ATTR void xksmallvectorset(T, N)(xksmallvector(T, N)* me, size_t i, T e) \
    { \
        xkassert(i < me->size); \
        xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me)[i] = e; \
    } \
    ATTR T* xksmallvectorat(T, N)(xksmallvector(T, N)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        return &xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me)[i]; \
    } \
    ATTR const T* xksmallvectorat_const(T, N)(const xksmallvector(T, N)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        return &xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_const_, T, N)(me)[i]; \
    } \
    ATTR T* xksmallvectorfront(T, N)(xksmallvector(T, N)* me) \
    { \
        xkassert(me->size > 0); \
        return &xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me)[0]; \
    } \
    ATTR const T* xksmallvectorfront_const(T, N)(const xksmallvector(T, N)* me) \
    { \
        xkassert(me->size > 0); \
        return &xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_const_, T, N)(me)[0]; \
    } \
    ATTR T* xksmallvectorback(T, N)(xksmallvector(T, N)* me) \
    { \
        xkassert(me->size > 0); \
        return &xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me)[me->size - 1]; \
    } \
    ATTR const T* xksmallvectorback_const(T, N)(const xksmallvector(T, N)* me) \
    { \
        xkassert(me->size > 0); \
        return &xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_const_, T, N)(me)[me->size - 1]; \
    } \
    ATTR void xksmallvectorinsertbefore(T, N)(xksmallvector(T, N)* me, size_t i, T e) \
    { \
        xkassert(i <= me->size); \
        if (me->size == me->capacity) \
            xksmallvectorreserve(T, N)(me, me->size + 1); \
        T* d = xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me); \
        memmove(&d[i + 1], &d[i], (me->size - i) * sizeof(T)); \
        d[i] = e; \
        me->size++; \
    } \
    ATTR void xksmallvectorinsertafter(T, N)(xksmallvector(T, N)* me, size_t i, T e) \
    { \
        xkassert(i < me->size); \
        xksmallvectorinsertbefore(T, N)(me, i + 1, e); \
    } \
    ATTR void xksmallvectorerase(T, N)(xksmallvector(T, N)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        T* d = xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me); \
        if (i + 1 < me->size) \
            memmove(&d[i], &d[i + 1], (me->size - i - 1) * sizeof(T)); \
        me->size--; \
    } \
    ATTR void xksmallvectorcutout(T, N)(xksmallvector(T, N)* me, size_t i, size_t n) \
    { \
        xkassert(i <= me->size); \
        xkassert(n <= me->size - i); \
        if (n == 0) return; \
        T* d = xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me); \
        if (i + n < me->size) \
            memmove(&d[i], &d[i + n], (me->size - i - n) * sizeof(T)); \
        me->size -= n; \
    } \
    ATTR void xksmallvectoroverwrite(T, N)(xksmallvector(T, N)* me, size_t i, const T* p, size_t n) \
    { \
        if (n == 0) return; \
        if (n > (size_t)-1 / sizeof(T) || n > (size_t)-1 - i) \
            xkabort(); \
        T* d = xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me); \
        T* tmp = NULL; \
        if (XK_PRIVATE_SMALLVECTOR_OVERLAPPING(d, me->capacity, p, n)) \
        { \
            tmp = (T*)xkrealloc(NULL, n * sizeof(T)); \
            if (!tmp) xkabort(); \
            memcpy(tmp, p, n * sizeof(T)); \
            p = tmp; \
        } \
        if (i + n > me->size) \
            xksmallvectorresize(T, N)(me, i + n); \
        d = xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me); \
        memmove(&d[i], p, n * sizeof(T)); \
        if (tmp) xkfree(tmp); \
    } \
    ATTR void xksmallvectorclear(T, N)(xksmallvector(T, N)* me) \
    { \
        me->size = 0; \
    } \
    ATTR void xksmallvectorassign(T, N)(xksmallvector(T, N)* me, const T* p, size_t n) \
    { \
        if (n == 0) \
        { \
            me->size = 0; \
            return; \
        } \
        if (n > (size_t)-1 / sizeof(T)) xkabort(); \
        T* d = xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me); \
        T* tmp = NULL; \
        if (XK_PRIVATE_SMALLVECTOR_OVERLAPPING(d, me->capacity, p, n)) \
        { \
            tmp = (T*)xkrealloc(NULL, n * sizeof(T)); \
            if (!tmp) xkabort(); \
            memcpy(tmp, p, n * sizeof(T)); \
            p = tmp; \
        } \
        me->size = 0; \
        if (n > me->capacity) xksmallvectorreserve(T, N)(me, n); \
        d = xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me); \
        memcpy(d, p, n * sizeof(T)); \
        me->size = n; \
        if (tmp) xkfree(tmp); \
    } \
    ATTR void xksmallvectorcopy(T, N)(xksmallvector(T, N)* dst, const xksmallvector(T, N)* src) \
    { \
        if (dst == src) return; \
        dst->size = 0; \
        if (src->size > dst->capacity) \
            xksmallvectorreserve(T, N)(dst, src->size); \
        if (src->size) \
            memcpy(xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(dst), \
                xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_const_, T, N)(src), \
                src->size * sizeof(T)); \
        dst->size = src->size; \
    } \
    ATTR xksmallvector(T, N) xksmallvectorclone(T, N)(const xksmallvector(T, N)* me) \
    { \
        xksmallvector(T, N) r = {0}; \
        r.capacity = (size_t)(N); \
        if (me->size > (size_t)(N)) \
            xksmallvectorreserve(T, N)(&r, me->size); \
        if (me->size) \
            memcpy(xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(&r), \
                xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_const_, T, N)(me), \
                me->size * sizeof(T)); \
        r.size = me->size; \
        return r; \
    } \
    ATTR void xksmallvectormove(T, N)(xksmallvector(T, N)* dst, xksmallvector(T, N)* src) \
    { \
        if (dst == src) return; \
        if (src->capacity > (size_t)(N)) \
        { \
            if (dst->capacity > (size_t)(N) && dst->heap != src->heap) \
                xkfree(dst->heap); \
            dst->heap = src->heap; \
            dst->size = src->size; \
            dst->capacity = src->capacity; \
            src->size = 0; \
            src->capacity = (size_t)(N); \
        } \
        else \
        { \
            dst->size = 0; \
            if (src->size > dst->capacity) \
                xksmallvectorreserve(T, N)(dst, src->size); \
            if (src->size) \
                memcpy(xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(dst), \
                    src->storage, src->size * sizeof(T)); \
            dst->size = src->size; \
            src->size = 0; \
            src->capacity = (size_t)(N); \
        } \
    } \
    ATTR void xksmallvectorswap(T, N)(xksmallvector(T, N)* a, xksmallvector(T, N)* b) \
    { \
        if (a == b) return; \
        xksmallvector(T, N) tmp; \
        xksmallvectorinit(T, N)(&tmp); \
        xksmallvectormove(T, N)(&tmp, a); \
        xksmallvectormove(T, N)(a, b); \
        xksmallvectormove(T, N)(b, &tmp); \
    } \
    ATTR size_t xksmallvectorsize(T, N)(const xksmallvector(T, N)* me) \
    { \
        return me->size; \
    } \
    ATTR size_t xksmallvectorcapacity(T, N)(const xksmallvector(T, N)* me) \
    { \
        return me->capacity > (size_t)(N) ? me->capacity : (size_t)(N); \
    } \
    ATTR int xksmallvectorempty(T, N)(const xksmallvector(T, N)* me) \
    { \
        return me->size == 0; \
    } \
    ATTR xkview(T) xksmallvectorview(T, N)(const xksmallvector(T, N)* me) \
    { \
        xkview(T) r = { xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_const_, T, N)(me), me->size }; \
        return r; \
    } \
    ATTR xkspan(T) xksmallvectorspan(T, N)(xksmallvector(T, N)* me) \
    { \
        xkspan(T) r = { xk_PRIVATE_SMALLVECTOR_NAME(xk_PRIVATE_smallvector_data_, T, N)(me), me->size }; \
        return r; \
    }

// MARK: sugar
#define xksmallvectorforeach(T, N, ME, IT) \
    for (T* IT##_HIDE_base = ((ME)->capacity > (size_t)(N) ? (ME)->heap : (ME)->storage), *IT = IT##_HIDE_base, *IT##_HIDE_end = IT##_HIDE_base + (ME)->size; IT != IT##_HIDE_end; ++IT)
#define xksmallvectorforeach_const(T, N, ME, IT) \
    for (const T* IT##_HIDE_base = ((ME)->capacity > (size_t)(N) ? (ME)->heap : (ME)->storage), *IT = IT##_HIDE_base, *IT##_HIDE_end = IT##_HIDE_base + (ME)->size; IT != IT##_HIDE_end; ++IT)
#define xksmallvectorrforeach(T, N, ME, IT) \
    for (T* IT##_HIDE_base = ((ME)->capacity > (size_t)(N) ? (ME)->heap : (ME)->storage), *IT = IT##_HIDE_base + (ME)->size; IT != IT##_HIDE_base && (--IT, 1);)
#define xksmallvectorrforeach_const(T, N, ME, IT) \
    for (const T* IT##_HIDE_base = ((ME)->capacity > (size_t)(N) ? (ME)->heap : (ME)->storage), *IT = IT##_HIDE_base + (ME)->size; IT != IT##_HIDE_base && (--IT, 1);)

#endif
