// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__XKSMALLSTRING_H
#define XK_INTERNAL__XKSMALLSTRING_H

#include "_xkconf.h"
#include "_xkvector.h"
#include "_xkequal.h"
#include "_xkcompare.h"
#include "_xkhash.h"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef XK_CAT
#define XK_CAT_(a, b)   a##b
#define XK_CAT(a, b)    XK_CAT_(a, b)
#endif

#define XK_PRIVATE_SMALLSTRING_OVERLAPPING(D, CAP, P, N) \
    ((N) > 0 && \
    (uintptr_t)(P) < (uintptr_t)(D) + (size_t)(CAP) + 1 && \
    (uintptr_t)(P) + (uintptr_t)(N) > (uintptr_t)(D))

#define xksmallstring(N)                XK_CAT(xksmallstring_, N)
#define xksmallstringinit(N)            XK_CAT(xk_PUBLIC_smallstring_init_, N)
#define xksmallstringfree(N)            XK_CAT(xk_PUBLIC_smallstring_free_, N)
#define xksmallstringreserve(N)         XK_CAT(xk_PUBLIC_smallstring_reserve_, N)
#define xksmallstringresize(N)          XK_CAT(xk_PUBLIC_smallstring_resize_, N)
#define xksmallstringshrink(N)          XK_CAT(xk_PUBLIC_smallstring_shrink_, N)
#define xksmallstringpush(N)            XK_CAT(xk_PUBLIC_smallstring_push_, N)
#define xksmallstringappend(N)          XK_CAT(xk_PUBLIC_smallstring_append_, N)
#define xksmallstringpop(N)             XK_CAT(xk_PUBLIC_smallstring_pop_, N)
#define xksmallstringdata(N)            XK_CAT(xk_PUBLIC_smallstring_data_, N)
#define xksmallstringdata_const(N)      XK_CAT(xk_PUBLIC_smallstring_data_const_, N)
#define xksmallstringc_str(N)           XK_CAT(xk_PUBLIC_smallstring_c_str_, N)
#define xksmallstringget(N)             XK_CAT(xk_PUBLIC_smallstring_get_, N)
#define xksmallstringset(N)             XK_CAT(xk_PUBLIC_smallstring_set_, N)
#define xksmallstringat(N)              XK_CAT(xk_PUBLIC_smallstring_at_, N)
#define xksmallstringat_const(N)        XK_CAT(xk_PUBLIC_smallstring_at_const_, N)
#define xksmallstringfront(N)           XK_CAT(xk_PUBLIC_smallstring_front_, N)
#define xksmallstringfront_const(N)     XK_CAT(xk_PUBLIC_smallstring_front_const_, N)
#define xksmallstringback(N)            XK_CAT(xk_PUBLIC_smallstring_back_, N)
#define xksmallstringback_const(N)      XK_CAT(xk_PUBLIC_smallstring_back_const_, N)
#define xksmallstringinsert(N)          XK_CAT(xk_PUBLIC_smallstring_insert_, N)
#define xksmallstringsplice(N)          XK_CAT(xk_PUBLIC_smallstring_splice_, N)
#define xksmallstringerase(N)           XK_CAT(xk_PUBLIC_smallstring_erase_, N)
#define xksmallstringcutout(N)          XK_CAT(xk_PUBLIC_smallstring_cutout_, N)
#define xksmallstringoverwrite(N)       XK_CAT(xk_PUBLIC_smallstring_overwrite_, N)
#define xksmallstringclear(N)           XK_CAT(xk_PUBLIC_smallstring_clear_, N)
#define xksmallstringassign(N)          XK_CAT(xk_PUBLIC_smallstring_assign_, N)
#define xksmallstringcopy(N)            XK_CAT(xk_PUBLIC_smallstring_copy_, N)
#define xksmallstringclone(N)           XK_CAT(xk_PUBLIC_smallstring_clone_, N)
#define xksmallstringsub(N)             XK_CAT(xk_PUBLIC_smallstring_sub_, N)
#define xksmallstringconcat(N)          XK_CAT(xk_PUBLIC_smallstring_concat_, N)
#define xksmallstringmove(N)            XK_CAT(xk_PUBLIC_smallstring_move_, N)
#define xksmallstringswap(N)            XK_CAT(xk_PUBLIC_smallstring_swap_, N)
#define xksmallstringfind(N)            XK_CAT(xk_PUBLIC_smallstring_find_, N)
#define xksmallstringmatch(N)           XK_CAT(xk_PUBLIC_smallstring_match_, N)
#define xksmallstringcontains(N)        XK_CAT(xk_PUBLIC_smallstring_contains_, N)
#define xksmallstringprefix(N)          XK_CAT(xk_PUBLIC_smallstring_prefix_, N)
#define xksmallstringsuffix(N)          XK_CAT(xk_PUBLIC_smallstring_suffix_, N)
#define xksmallstringsize(N)            XK_CAT(xk_PUBLIC_smallstring_size_, N)
#define xksmallstringlength(N)          XK_CAT(xk_PUBLIC_smallstring_length_, N)
#define xksmallstringcapacity(N)        XK_CAT(xk_PUBLIC_smallstring_capacity_, N)
#define xksmallstringempty(N)           XK_CAT(xk_PUBLIC_smallstring_empty_, N)
#define xksmallstringview(N)            XK_CAT(xk_PUBLIC_smallstring_view_, N)
#define xksmallstringspan(N)            XK_CAT(xk_PUBLIC_smallstring_span_, N)

// MARK: decl
#define xksmallstringdecl(N, ATTR) \
    typedef struct xksmallstring(N) \
    { \
        char storage[((N) ? ((N) + 1) : 1)]; \
        char* heap; \
        size_t size; \
        size_t capacity; \
    } xksmallstring(N); \
    ATTR void xksmallstringinit(N)(xksmallstring(N)* me); \
    ATTR void xksmallstringfree(N)(xksmallstring(N)* me); \
    ATTR void xksmallstringreserve(N)(xksmallstring(N)* me, size_t cap); \
    ATTR void xksmallstringresize(N)(xksmallstring(N)* me, size_t n); \
    ATTR void xksmallstringshrink(N)(xksmallstring(N)* me); \
    ATTR void xksmallstringpush(N)(xksmallstring(N)* me, char e); \
    ATTR void xksmallstringappend(N)(xksmallstring(N)* me, const char* p, size_t n); \
    ATTR char xksmallstringpop(N)(xksmallstring(N)* me); \
    ATTR char* xksmallstringdata(N)(xksmallstring(N)* me); \
    ATTR const char* xksmallstringdata_const(N)(const xksmallstring(N)* me); \
    ATTR const char* xksmallstringc_str(N)(const xksmallstring(N)* me); \
    ATTR char xksmallstringget(N)(const xksmallstring(N)* me, size_t i); \
    ATTR void xksmallstringset(N)(xksmallstring(N)* me, size_t i, char e); \
    ATTR char* xksmallstringat(N)(xksmallstring(N)* me, size_t i); \
    ATTR const char* xksmallstringat_const(N)(const xksmallstring(N)* me, size_t i); \
    ATTR char* xksmallstringfront(N)(xksmallstring(N)* me); \
    ATTR const char* xksmallstringfront_const(N)(const xksmallstring(N)* me); \
    ATTR char* xksmallstringback(N)(xksmallstring(N)* me); \
    ATTR const char* xksmallstringback_const(N)(const xksmallstring(N)* me); \
    ATTR void xksmallstringinsert(N)(xksmallstring(N)* me, size_t i, char e); \
    ATTR void xksmallstringsplice(N)(xksmallstring(N)* me, size_t i, const char* p, size_t n); \
    ATTR void xksmallstringerase(N)(xksmallstring(N)* me, size_t i); \
    ATTR void xksmallstringcutout(N)(xksmallstring(N)* me, size_t i, size_t n); \
    ATTR void xksmallstringoverwrite(N)(xksmallstring(N)* me, size_t i, const char* p, size_t n); \
    ATTR void xksmallstringclear(N)(xksmallstring(N)* me); \
    ATTR void xksmallstringassign(N)(xksmallstring(N)* me, const char* p, size_t n); \
    ATTR void xksmallstringcopy(N)(xksmallstring(N)* dst, const xksmallstring(N)* src); \
    ATTR xksmallstring(N) xksmallstringclone(N)(const xksmallstring(N)* me); \
    ATTR xksmallstring(N) xksmallstringsub(N)(const xksmallstring(N)* me, size_t start, size_t n); \
    ATTR xksmallstring(N) xksmallstringconcat(N)(const xksmallstring(N)* a, const xksmallstring(N)* b); \
    ATTR void xksmallstringmove(N)(xksmallstring(N)* dst, xksmallstring(N)* src); \
    ATTR void xksmallstringswap(N)(xksmallstring(N)* a, xksmallstring(N)* b); \
    ATTR size_t xksmallstringfind(N)(const xksmallstring(N)* me, char e); \
    ATTR size_t xksmallstringmatch(N)(const xksmallstring(N)* me, const char* p, size_t n); \
    ATTR int xksmallstringcontains(N)(const xksmallstring(N)* me, char e); \
    ATTR int xksmallstringprefix(N)(const xksmallstring(N)* me, const char* p, size_t n); \
    ATTR int xksmallstringsuffix(N)(const xksmallstring(N)* me, const char* p, size_t n); \
    ATTR size_t xksmallstringsize(N)(const xksmallstring(N)* me); \
    ATTR size_t xksmallstringlength(N)(const xksmallstring(N)* me); \
    ATTR size_t xksmallstringcapacity(N)(const xksmallstring(N)* me); \
    ATTR int xksmallstringempty(N)(const xksmallstring(N)* me); \
    ATTR xkview(char) xksmallstringview(N)(const xksmallstring(N)* me); \
    ATTR xkspan(char) xksmallstringspan(N)(xksmallstring(N)* me); \
    ATTR bool xkequal(xksmallstring(N))(xksmallstring(N) a, xksmallstring(N) b); \
    ATTR int xkcompare(xksmallstring(N))(xksmallstring(N) a, xksmallstring(N) b); \
    ATTR size_t xkhash(xksmallstring(N))(xksmallstring(N) v);

// MARK: impl
#define xksmallstringimpl(N, ATTR) \
    static inline char* XK_CAT(xk_PRIVATE_smallstring_data_, N)(xksmallstring(N)* me) \
    { \
        return me->heap ? me->heap : me->storage; \
    } \
    static inline const char* XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(const xksmallstring(N)* me) \
    { \
        return me->heap ? me->heap : me->storage; \
    } \
    ATTR void xksmallstringinit(N)(xksmallstring(N)* me) \
    { \
        me->heap = NULL; \
        me->size = 0; \
        me->capacity = (size_t)(N); \
        me->storage[0] = 0; \
    } \
    ATTR void xksmallstringfree(N)(xksmallstring(N)* me) \
    { \
        if (me->heap) xkfree(me->heap); \
        me->heap = NULL; \
        me->size = 0; \
        me->capacity = (size_t)(N); \
        me->storage[0] = 0; \
    } \
    ATTR void xksmallstringreserve(N)(xksmallstring(N)* me, size_t cap) \
    { \
        if (!me->heap && me->capacity < (size_t)(N)) \
            me->capacity = (size_t)(N); \
        if (cap <= me->capacity) return; \
        if (cap > (size_t)-1 - 1) xkabort(); \
        size_t nc = me->capacity ? me->capacity : cap; \
        while (nc < cap) \
        { \
            if (nc > ((size_t)-1 - 1) / 2) \
            { \
                nc = cap; \
                break; \
            } \
            nc *= 2; \
        } \
        if (nc > (size_t)-1 - 1) xkabort(); \
        char* p; \
        if (me->heap) \
        { \
            p = (char*)xkrealloc(me->heap, nc + 1); \
            if (!p) xkabort(); \
        } \
        else \
        { \
            p = (char*)xkrealloc(NULL, nc + 1); \
            if (!p) xkabort(); \
            memcpy(p, me->storage, me->size + 1); \
        } \
        me->heap = p; \
        me->capacity = nc; \
        me->heap[me->size] = 0; \
    } \
    ATTR void xksmallstringresize(N)(xksmallstring(N)* me, size_t n) \
    { \
        if (n > me->capacity) xksmallstringreserve(N)(me, n); \
        char* d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(me); \
        if (n > me->size) \
            memset(d + me->size, 0, n - me->size); \
        me->size = n; \
        d[me->size] = 0; \
    } \
    ATTR void xksmallstringshrink(N)(xksmallstring(N)* me) \
    { \
        size_t base = (size_t)(N); \
        size_t target = me->size > base ? me->size : base; \
        if (me->capacity == target) return; \
        if (me->size <= base) \
        { \
            if (me->heap) \
            { \
                memcpy(me->storage, me->heap, me->size); \
                me->storage[me->size] = 0; \
                xkfree(me->heap); \
                me->heap = NULL; \
            } \
            me->capacity = base; \
        } \
        else \
        { \
            char* p = (char*)xkrealloc(me->heap, me->size + 1); \
            if (!p) xkabort(); \
            me->heap = p; \
            me->capacity = me->size; \
            me->heap[me->size] = 0; \
        } \
    } \
    ATTR void xksmallstringpush(N)(xksmallstring(N)* me, char e) \
    { \
        if (me->size == me->capacity) \
            xksmallstringreserve(N)(me, me->size + 1); \
        char* d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(me); \
        d[me->size++] = e; \
        d[me->size] = 0; \
    } \
    ATTR void xksmallstringappend(N)(xksmallstring(N)* me, const char* p, size_t n) \
    { \
        if (n == 0) return; \
        if (n > (size_t)-1 - 1 || n > (size_t)-1 - me->size) xkabort(); \
        char* d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(me); \
        char* tmp = NULL; \
        if (XK_PRIVATE_SMALLSTRING_OVERLAPPING(d, me->capacity, p, n)) \
        { \
            tmp = (char*)xkrealloc(NULL, n); \
            if (!tmp) xkabort(); \
            memcpy(tmp, p, n); \
            p = tmp; \
        } \
        if (me->size + n > me->capacity) \
            xksmallstringreserve(N)(me, me->size + n); \
        d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(me); \
        memcpy(d + me->size, p, n); \
        me->size += n; \
        d[me->size] = 0; \
        if (tmp) xkfree(tmp); \
    } \
    ATTR char xksmallstringpop(N)(xksmallstring(N)* me) \
    { \
        xkassert(me->size > 0); \
        char* d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(me); \
        char e = d[--me->size]; \
        d[me->size] = 0; \
        return e; \
    } \
    ATTR char* xksmallstringdata(N)(xksmallstring(N)* me) \
    { \
        return XK_CAT(xk_PRIVATE_smallstring_data_, N)(me); \
    } \
    ATTR const char* xksmallstringdata_const(N)(const xksmallstring(N)* me) \
    { \
        return XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(me); \
    } \
    ATTR const char* xksmallstringc_str(N)(const xksmallstring(N)* me) \
    { \
        return XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(me); \
    } \
    ATTR char xksmallstringget(N)(const xksmallstring(N)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        return XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(me)[i]; \
    } \
    ATTR void xksmallstringset(N)(xksmallstring(N)* me, size_t i, char e) \
    { \
        xkassert(i < me->size); \
        XK_CAT(xk_PRIVATE_smallstring_data_, N)(me)[i] = e; \
    } \
    ATTR char* xksmallstringat(N)(xksmallstring(N)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        return &XK_CAT(xk_PRIVATE_smallstring_data_, N)(me)[i]; \
    } \
    ATTR const char* xksmallstringat_const(N)(const xksmallstring(N)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        return &XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(me)[i]; \
    } \
    ATTR char* xksmallstringfront(N)(xksmallstring(N)* me) \
    { \
        xkassert(me->size > 0); \
        return &XK_CAT(xk_PRIVATE_smallstring_data_, N)(me)[0]; \
    } \
    ATTR const char* xksmallstringfront_const(N)(const xksmallstring(N)* me) \
    { \
        xkassert(me->size > 0); \
        return &XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(me)[0]; \
    } \
    ATTR char* xksmallstringback(N)(xksmallstring(N)* me) \
    { \
        xkassert(me->size > 0); \
        return &XK_CAT(xk_PRIVATE_smallstring_data_, N)(me)[me->size - 1]; \
    } \
    ATTR const char* xksmallstringback_const(N)(const xksmallstring(N)* me) \
    { \
        xkassert(me->size > 0); \
        return &XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(me)[me->size - 1]; \
    } \
    ATTR void xksmallstringinsert(N)(xksmallstring(N)* me, size_t i, char e) \
    { \
        xkassert(i <= me->size); \
        if (me->size == me->capacity) \
            xksmallstringreserve(N)(me, me->size + 1); \
        char* d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(me); \
        memmove(&d[i + 1], &d[i], me->size - i); \
        d[i] = e; \
        me->size++; \
        d[me->size] = 0; \
    } \
    ATTR void xksmallstringsplice(N)(xksmallstring(N)* me, size_t i, const char* p, size_t n) \
    { \
        xkassert(i <= me->size); \
        if (n == 0) return; \
        if (n > (size_t)-1 - 1 || n > (size_t)-1 - me->size) xkabort(); \
        char* d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(me); \
        char* tmp = NULL; \
        if (XK_PRIVATE_SMALLSTRING_OVERLAPPING(d, me->capacity, p, n)) \
        { \
            tmp = (char*)xkrealloc(NULL, n); \
            if (!tmp) xkabort(); \
            memcpy(tmp, p, n); \
            p = tmp; \
        } \
        if (me->size + n > me->capacity) \
            xksmallstringreserve(N)(me, me->size + n); \
        d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(me); \
        memmove(&d[i + n], &d[i], me->size - i); \
        memcpy(&d[i], p, n); \
        me->size += n; \
        d[me->size] = 0; \
        if (tmp) xkfree(tmp); \
    } \
    ATTR void xksmallstringerase(N)(xksmallstring(N)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        char* d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(me); \
        memmove(&d[i], &d[i + 1], me->size - i - 1); \
        me->size--; \
        d[me->size] = 0; \
    } \
    ATTR void xksmallstringcutout(N)(xksmallstring(N)* me, size_t i, size_t n) \
    { \
        xkassert(i <= me->size); \
        xkassert(n <= me->size - i); \
        if (n == 0) return; \
        char* d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(me); \
        memmove(&d[i], &d[i + n], me->size - i - n); \
        me->size -= n; \
        d[me->size] = 0; \
    } \
    ATTR void xksmallstringoverwrite(N)(xksmallstring(N)* me, size_t i, const char* p, size_t n) \
    { \
        if (n == 0) return; \
        if (n > (size_t)-1 - 1 || n > (size_t)-1 - i) xkabort(); \
        char* d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(me); \
        char* tmp = NULL; \
        if (XK_PRIVATE_SMALLSTRING_OVERLAPPING(d, me->capacity, p, n)) \
        { \
            tmp = (char*)xkrealloc(NULL, n); \
            if (!tmp) xkabort(); \
            memcpy(tmp, p, n); \
            p = tmp; \
        } \
        if (i + n > me->size) \
            xksmallstringresize(N)(me, i + n); \
        d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(me); \
        memmove(&d[i], p, n); \
        d[me->size] = 0; \
        if (tmp) xkfree(tmp); \
    } \
    ATTR void xksmallstringclear(N)(xksmallstring(N)* me) \
    { \
        char* d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(me); \
        me->size = 0; \
        d[0] = 0; \
    } \
    ATTR void xksmallstringassign(N)(xksmallstring(N)* me, const char* p, size_t n) \
    { \
        if (n == 0) \
        { \
            xksmallstringclear(N)(me); \
            return; \
        } \
        if (n > (size_t)-1 - 1) xkabort(); \
        char* d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(me); \
        char* tmp = NULL; \
        if (XK_PRIVATE_SMALLSTRING_OVERLAPPING(d, me->capacity, p, n)) \
        { \
            tmp = (char*)xkrealloc(NULL, n); \
            if (!tmp) xkabort(); \
            memcpy(tmp, p, n); \
            p = tmp; \
        } \
        me->size = 0; \
        if (n > me->capacity) xksmallstringreserve(N)(me, n); \
        d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(me); \
        memcpy(d, p, n); \
        me->size = n; \
        d[me->size] = 0; \
        if (tmp) xkfree(tmp); \
    } \
    ATTR void xksmallstringcopy(N)(xksmallstring(N)* dst, const xksmallstring(N)* src) \
    { \
        if (dst == src) return; \
        dst->size = 0; \
        if (src->size > dst->capacity) \
            xksmallstringreserve(N)(dst, src->size); \
        char* d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(dst); \
        if (src->size) \
            memcpy(d, XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(src), src->size); \
        dst->size = src->size; \
        d[dst->size] = 0; \
    } \
    ATTR xksmallstring(N) xksmallstringclone(N)(const xksmallstring(N)* me) \
    { \
        xksmallstring(N) r; \
        xksmallstringinit(N)(&r); \
        if (me->size > (size_t)(N)) \
            xksmallstringreserve(N)(&r, me->size); \
        char* d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(&r); \
        if (me->size) \
            memcpy(d, XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(me), me->size); \
        r.size = me->size; \
        d[r.size] = 0; \
        return r; \
    } \
    ATTR xksmallstring(N) xksmallstringsub(N)(const xksmallstring(N)* me, size_t start, size_t n) \
    { \
        xkassert(start <= me->size); \
        xkassert(n <= me->size - start); \
        xksmallstring(N) r; \
        xksmallstringinit(N)(&r); \
        if (n > (size_t)(N)) xksmallstringreserve(N)(&r, n); \
        char* d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(&r); \
        if (n) memcpy(d, XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(me) + start, n); \
        r.size = n; \
        d[r.size] = 0; \
        return r; \
    } \
    ATTR xksmallstring(N) xksmallstringconcat(N)(const xksmallstring(N)* a, const xksmallstring(N)* b) \
    { \
        if (a->size > (size_t)-1 - b->size) xkabort(); \
        size_t total = a->size + b->size; \
        if (total > (size_t)-1 - 1) xkabort(); \
        xksmallstring(N) r; \
        xksmallstringinit(N)(&r); \
        if (total > (size_t)(N)) xksmallstringreserve(N)(&r, total); \
        char* d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(&r); \
        if (a->size) memcpy(d, XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(a), a->size); \
        if (b->size) memcpy(d + a->size, XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(b), b->size); \
        r.size = total; \
        d[r.size] = 0; \
        return r; \
    } \
    ATTR void xksmallstringmove(N)(xksmallstring(N)* dst, xksmallstring(N)* src) \
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
            src->storage[0] = 0; \
        } \
        else \
        { \
            dst->size = 0; \
            if (src->size > dst->capacity) \
                xksmallstringreserve(N)(dst, src->size); \
            char* d = XK_CAT(xk_PRIVATE_smallstring_data_, N)(dst); \
            if (src->size) memcpy(d, src->storage, src->size); \
            dst->size = src->size; \
            d[dst->size] = 0; \
            src->size = 0; \
            src->capacity = (size_t)(N); \
            src->storage[0] = 0; \
        } \
    } \
    ATTR void xksmallstringswap(N)(xksmallstring(N)* a, xksmallstring(N)* b) \
    { \
        if (a == b) return; \
        xksmallstring(N) tmp; \
        xksmallstringinit(N)(&tmp); \
        xksmallstringmove(N)(&tmp, a); \
        xksmallstringmove(N)(a, b); \
        xksmallstringmove(N)(b, &tmp); \
    } \
    ATTR size_t xksmallstringfind(N)(const xksmallstring(N)* me, char e) \
    { \
        const char* d = XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(me); \
        for (size_t i = 0; i < me->size; ++i) \
            if (d[i] == e) \
                return i; \
        return (size_t)-1; \
    } \
    ATTR size_t xksmallstringmatch(N)(const xksmallstring(N)* me, const char* p, size_t n) \
    { \
        if (n == 0) return 0; \
        if (n > me->size) return (size_t)-1; \
        const char* d = XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(me); \
        for (size_t i = 0; i <= me->size - n; ++i) \
            if (memcmp(&d[i], p, n) == 0) \
                return i; \
        return (size_t)-1; \
    } \
    ATTR int xksmallstringcontains(N)(const xksmallstring(N)* me, char e) \
    { \
        return xksmallstringfind(N)(me, e) != (size_t)-1; \
    } \
    ATTR int xksmallstringprefix(N)(const xksmallstring(N)* me, const char* p, size_t n) \
    { \
        return n <= me->size && \
            memcmp(XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(me), p, n) == 0; \
    } \
    ATTR int xksmallstringsuffix(N)(const xksmallstring(N)* me, const char* p, size_t n) \
    { \
        return n <= me->size && \
            memcmp(XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(me) + me->size - n, p, n) == 0; \
    } \
    ATTR size_t xksmallstringsize(N)(const xksmallstring(N)* me) \
    { \
        return me->size; \
    } \
    ATTR size_t xksmallstringlength(N)(const xksmallstring(N)* me) \
    { \
        return me->size; \
    } \
    ATTR size_t xksmallstringcapacity(N)(const xksmallstring(N)* me) \
    { \
        return me->heap ? me->capacity : (size_t)(N); \
    } \
    ATTR int xksmallstringempty(N)(const xksmallstring(N)* me) \
    { \
        return me->size == 0; \
    } \
    ATTR xkview(char) xksmallstringview(N)(const xksmallstring(N)* me) \
    { \
        xkview(char) r = { XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(me), me->size }; \
        return r; \
    } \
    ATTR xkspan(char) xksmallstringspan(N)(xksmallstring(N)* me) \
    { \
        xkspan(char) r = { XK_CAT(xk_PRIVATE_smallstring_data_, N)(me), me->size }; \
        return r; \
    } \
    ATTR bool xkequal(xksmallstring(N))(xksmallstring(N) a, xksmallstring(N) b) \
    { \
        if (a.size != b.size) return false; \
        return a.size == 0 || \
            memcmp(XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(&a), \
                XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(&b), a.size) == 0; \
    } \
    ATTR int xkcompare(xksmallstring(N))(xksmallstring(N) a, xksmallstring(N) b) \
    { \
        size_t n = a.size < b.size ? a.size : b.size; \
        int r = n ? memcmp(XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(&a), \
            XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(&b), n) : 0; \
        if (r != 0) return r; \
        if (a.size < b.size) return -1; \
        if (a.size > b.size) return 1; \
        return 0; \
    } \
    ATTR size_t xkhash(xksmallstring(N))(xksmallstring(N) v) \
    { \
        const uint64_t FNV_OFFSET = 0xCBF29CE484222325ull; \
        const uint64_t FNV_PRIME  = 0x100000001B3ull; \
        const char* d = XK_CAT(xk_PRIVATE_smallstring_data_const_, N)(&v); \
        uint64_t h = FNV_OFFSET ^ (uint64_t)(v.size); \
        for (size_t i = 0; i < v.size; ++i) \
        { \
            h ^= (uint8_t)d[i]; \
            h *= FNV_PRIME; \
        } \
        return xk_PRIVATE_hash_mix64(h); \
    }

#endif
