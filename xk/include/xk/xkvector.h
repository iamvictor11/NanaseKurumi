// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_XKVECTOR_H
#define XK_XKVECTOR_H

#include "xkconf.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef XK_CAT
#define XK_CAT_(a, b)   a##b
#define XK_CAT(a, b)    XK_CAT_(a, b)
#endif

#define XK_PRIVATE_VECTOR_MIN_CAPACITY 8

#define XK_PRIVATE_VECTOR_OVERLAPPING(ME, P, N) \
    ((ME)->data != NULL && \
    (uintptr_t)(P) < (uintptr_t)((ME)->data) + (ME)->size * sizeof(*(ME)->data) && \
    (uintptr_t)(P) + (uintptr_t)(N) * sizeof(*(ME)->data) > (uintptr_t)((ME)->data))

#define xkvector(T)             XK_CAT(xk_DETAIL_vector_, T)
#define xkview(T)               XK_CAT(xk_DETAIL_view_, T)
#define xkspan(T)               XK_CAT(xk_DETAIL_span_, T)
#define xkvectorinit(T)         XK_CAT(xk_PUBLIC_vector_init_, T)
#define xkvectorfree(T)         XK_CAT(xk_PUBLIC_vector_free_, T)
#define xkvectorreserve(T)      XK_CAT(xk_PUBLIC_vector_reserve_, T)
#define xkvectorresize(T)       XK_CAT(xk_PUBLIC_vector_resize_, T)
#define xkvectorshrink(T)       XK_CAT(xk_PUBLIC_vector_shrink_, T)
#define xkvectorpushfront(T)    XK_CAT(xk_PUBLIC_vector_pushfront_, T)
#define xkvectorpushback(T)     XK_CAT(xk_PUBLIC_vector_pushback_, T)
#define xkvectoremplacefront(T) XK_CAT(xk_PUBLIC_vector_emplacefront_, T)
#define xkvectoremplaceback(T)  XK_CAT(xk_PUBLIC_vector_emplaceback_, T)
#define xkvectorappend(T)       XK_CAT(xk_PUBLIC_vector_append_, T)
#define xkvectorpopfront(T)     XK_CAT(xk_PUBLIC_vector_popfront_, T)
#define xkvectorpopback(T)      XK_CAT(xk_PUBLIC_vector_popback_, T)
#define xkvectordata(T)         XK_CAT(xk_PUBLIC_vector_data_, T)
#define xkvectordata_const(T)   XK_CAT(xk_PUBLIC_vector_data_const_, T)
#define xkvectorget(T)          XK_CAT(xk_PUBLIC_vector_get_, T)
#define xkvectorset(T)          XK_CAT(xk_PUBLIC_vector_set_, T)
#define xkvectorat(T)           XK_CAT(xk_PUBLIC_vector_at_, T)
#define xkvectorat_const(T)     XK_CAT(xk_PUBLIC_vector_at_const_, T)
#define xkvectorfront(T)        XK_CAT(xk_PUBLIC_vector_front_, T)
#define xkvectorfront_const(T)  XK_CAT(xk_PUBLIC_vector_front_const_, T)
#define xkvectorback(T)         XK_CAT(xk_PUBLIC_vector_back_, T)
#define xkvectorback_const(T)   XK_CAT(xk_PUBLIC_vector_back_const_, T)
#define xkvectorinsertbefore(T) XK_CAT(xk_PUBLIC_vector_insertbefore_, T)
#define xkvectorinsertafter(T)  XK_CAT(xk_PUBLIC_vector_insertafter_, T)
#define xkvectorerase(T)        XK_CAT(xk_PUBLIC_vector_erase_, T)
#define xkvectorcutout(T)       XK_CAT(xk_PUBLIC_vector_cutout_, T)
#define xkvectoroverwrite(T)    XK_CAT(xk_PUBLIC_vector_overwrite_, T)
#define xkvectorclear(T)        XK_CAT(xk_PUBLIC_vector_clear_, T)
#define xkvectorassign(T)       XK_CAT(xk_PUBLIC_vector_assign_, T)
#define xkvectorcopy(T)         XK_CAT(xk_PUBLIC_vector_copy_, T)
#define xkvectorclone(T)        XK_CAT(xk_PUBLIC_vector_clone_, T)
#define xkvectormove(T)         XK_CAT(xk_PUBLIC_vector_move_, T)
#define xkvectorswap(T)         XK_CAT(xk_PUBLIC_vector_swap_, T)
#define xkvectorsize(T)         XK_CAT(xk_PUBLIC_vector_size_, T)
#define xkvectorcapacity(T)     XK_CAT(xk_PUBLIC_vector_capacity_, T)
#define xkvectorempty(T)        XK_CAT(xk_PUBLIC_vector_empty_, T)
#define xkvectorview(T)         XK_CAT(xk_PUBLIC_vector_view_, T)
#define xkvectorspan(T)         XK_CAT(xk_PUBLIC_vector_span_, T)

// MARK: decl
#define xkvectordecl(T, ATTR) \
    typedef struct xkvector(T) \
    { \
        T* data; \
        size_t size; \
        size_t capacity; \
    } xkvector(T); \
    typedef struct xkview(T) \
    { \
        const T* data; \
        size_t size; \
    } xkview(T); \
    typedef struct xkspan(T) \
    { \
        T* data; \
        size_t size; \
    } xkspan(T); \
    ATTR void xkvectorinit(T)(xkvector(T)* me, size_t cap); \
    ATTR void xkvectorfree(T)(xkvector(T)* me); \
    ATTR void xkvectorreserve(T)(xkvector(T)* me, size_t cap); \
    ATTR void xkvectorresize(T)(xkvector(T)* me, size_t n); \
    ATTR void xkvectorshrink(T)(xkvector(T)* me); \
    ATTR void xkvectorpushfront(T)(xkvector(T)* me, T e); \
    ATTR void xkvectorpushback(T)(xkvector(T)* me, T e); \
    ATTR T* xkvectoremplacefront(T)(xkvector(T)* me); \
    ATTR T* xkvectoremplaceback(T)(xkvector(T)* me); \
    ATTR void xkvectorappend(T)(xkvector(T)* me, const T* p, size_t n); \
    ATTR void xkvectorpopfront(T)(xkvector(T)* me); \
    ATTR void xkvectorpopback(T)(xkvector(T)* me); \
    ATTR T* xkvectordata(T)(xkvector(T)* me); \
    ATTR const T* xkvectordata_const(T)(const xkvector(T)* me); \
    ATTR T xkvectorget(T)(const xkvector(T)* me, size_t i); \
    ATTR void xkvectorset(T)(xkvector(T)* me, size_t i, T e); \
    ATTR T* xkvectorat(T)(xkvector(T)* me, size_t i); \
    ATTR const T* xkvectorat_const(T)(const xkvector(T)* me, size_t i); \
    ATTR T* xkvectorfront(T)(xkvector(T)* me); \
    ATTR const T* xkvectorfront_const(T)(const xkvector(T)* me); \
    ATTR T* xkvectorback(T)(xkvector(T)* me); \
    ATTR const T* xkvectorback_const(T)(const xkvector(T)* me); \
    ATTR void xkvectorinsertbefore(T)(xkvector(T)* me, size_t i, T e); \
    ATTR void xkvectorinsertafter(T)(xkvector(T)* me, size_t i, T e); \
    ATTR void xkvectorerase(T)(xkvector(T)* me, size_t i); \
    ATTR void xkvectorcutout(T)(xkvector(T)* me, size_t i, size_t n); \
    ATTR void xkvectoroverwrite(T)(xkvector(T)* me, size_t i, const T* p, size_t n); \
    ATTR void xkvectorclear(T)(xkvector(T)* me); \
    ATTR void xkvectorassign(T)(xkvector(T)* me, const T* p, size_t n); \
    ATTR void xkvectorcopy(T)(xkvector(T)* dst, const xkvector(T)* src); \
    ATTR xkvector(T) xkvectorclone(T)(const xkvector(T)* me); \
    ATTR void xkvectormove(T)(xkvector(T)* dst, xkvector(T)* src); \
    ATTR void xkvectorswap(T)(xkvector(T)* a, xkvector(T)* b); \
    ATTR size_t xkvectorsize(T)(const xkvector(T)* me); \
    ATTR size_t xkvectorcapacity(T)(const xkvector(T)* me); \
    ATTR int xkvectorempty(T)(const xkvector(T)* me); \
    ATTR xkview(T) xkvectorview(T)(const xkvector(T)* me); \
    ATTR xkspan(T) xkvectorspan(T)(xkvector(T)* me);

// MARK: impl
#define xkvectorimpl(T, ATTR) \
    ATTR void xkvectorinit(T)(xkvector(T)* me, size_t cap) \
    { \
        me->data = NULL; \
        me->size = 0; \
        me->capacity = 0; \
        if (cap) xkvectorreserve(T)(me, cap); \
    } \
    ATTR void xkvectorfree(T)(xkvector(T)* me) \
    { \
        xkfree(me->data); \
        me->data = NULL; \
        me->size = 0; \
        me->capacity = 0; \
    } \
    ATTR void xkvectorreserve(T)(xkvector(T)* me, size_t cap) \
    { \
        if (cap <= me->capacity) return; \
        const size_t maxcap = (size_t)-1 / sizeof(T); \
        if (cap > maxcap) xkabort(); \
        size_t nc = me->capacity \
            ? me->capacity \
            : (cap < XK_PRIVATE_VECTOR_MIN_CAPACITY ? XK_PRIVATE_VECTOR_MIN_CAPACITY : cap); \
        if (nc < cap) \
        { \
            if (nc > maxcap / 2) nc = cap; \
            else \
            { \
                nc *= 2; \
                if (nc < cap) nc = cap; \
            } \
        } \
        T* p = (T*)xkrealloc(me->data, nc * sizeof(T)); \
        if (!p) xkabort(); \
        me->data = p; \
        me->capacity = nc; \
    } \
    ATTR void xkvectorresize(T)(xkvector(T)* me, size_t n) \
    { \
        if (n > me->capacity) \
            xkvectorreserve(T)(me, n); \
        if (n > me->size) \
            memset(me->data + me->size, 0, (n - me->size) * sizeof(T)); \
        me->size = n; \
    } \
    ATTR void xkvectorshrink(T)(xkvector(T)* me) \
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
            T* p = (T*)xkrealloc(me->data, me->size * sizeof(T)); \
            if (!p) xkabort(); \
            me->data = p; \
            me->capacity = me->size; \
        } \
    } \
    ATTR void xkvectorpushfront(T)(xkvector(T)* me, T e) \
    { \
        *xkvectoremplacefront(T)(me) = e; \
    } \
    ATTR void xkvectorpushback(T)(xkvector(T)* me, T e) \
    { \
        *xkvectoremplaceback(T)(me) = e; \
    } \
    ATTR T* xkvectoremplacefront(T)(xkvector(T)* me) \
    { \
        if (me->size == me->capacity) \
            xkvectorreserve(T)(me, me->size + 1); \
        if (me->size) \
            memmove(&me->data[1], &me->data[0], me->size * sizeof(T)); \
        ++me->size; \
        return &me->data[0]; \
    } \
    ATTR T* xkvectoremplaceback(T)(xkvector(T)* me) \
    { \
        if (me->size == me->capacity) \
            xkvectorreserve(T)(me, me->size + 1); \
        return &me->data[me->size++]; \
    } \
    ATTR void xkvectorappend(T)(xkvector(T)* me, const T* p, size_t n) \
    { \
        if (n == 0) return; \
        if (n > (size_t)-1 / sizeof(T) || n > (size_t)-1 - me->size) \
            xkabort(); \
        T* tmp = NULL; \
        if (XK_PRIVATE_VECTOR_OVERLAPPING(me, p, n)) \
        { \
            tmp = (T*)xkrealloc(NULL, n * sizeof(T)); \
            if (!tmp) xkabort(); \
            memcpy(tmp, p, n * sizeof(T)); \
            p = tmp; \
        } \
        if (me->size + n > me->capacity) \
            xkvectorreserve(T)(me, me->size + n); \
        memcpy(me->data + me->size, p, n * sizeof(T)); \
        me->size += n; \
        if (tmp) xkfree(tmp); \
    } \
    ATTR void xkvectorpopfront(T)(xkvector(T)* me) \
    { \
        xkassert(me->size > 0); \
        if (me->size > 1) \
            memmove(&me->data[0], &me->data[1], (me->size - 1) * sizeof(T)); \
        --me->size; \
    } \
    ATTR void xkvectorpopback(T)(xkvector(T)* me) \
    { \
        xkassert(me->size > 0); \
        --me->size; \
    } \
    ATTR T* xkvectordata(T)(xkvector(T)* me) \
    { \
        return me->data; \
    } \
    ATTR const T* xkvectordata_const(T)(const xkvector(T)* me) \
    { \
        return me->data; \
    } \
    ATTR T xkvectorget(T)(const xkvector(T)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        return me->data[i]; \
    } \
    ATTR void xkvectorset(T)(xkvector(T)* me, size_t i, T e) \
    { \
        xkassert(i < me->size); \
        me->data[i] = e; \
    } \
    ATTR T* xkvectorat(T)(xkvector(T)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        return &me->data[i]; \
    } \
    ATTR const T* xkvectorat_const(T)(const xkvector(T)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        return &me->data[i]; \
    } \
    ATTR T* xkvectorfront(T)(xkvector(T)* me) \
    { \
        xkassert(me->size > 0); \
        return &me->data[0]; \
    } \
    ATTR const T* xkvectorfront_const(T)(const xkvector(T)* me) \
    { \
        xkassert(me->size > 0); \
        return &me->data[0]; \
    } \
    ATTR T* xkvectorback(T)(xkvector(T)* me) \
    { \
        xkassert(me->size > 0); \
        return &me->data[me->size - 1]; \
    } \
    ATTR const T* xkvectorback_const(T)(const xkvector(T)* me) \
    { \
        xkassert(me->size > 0); \
        return &me->data[me->size - 1]; \
    } \
    ATTR void xkvectorinsertbefore(T)(xkvector(T)* me, size_t i, T e) \
    { \
        xkassert(i <= me->size); \
        if (me->size == me->capacity) \
            xkvectorreserve(T)(me, me->size + 1); \
        memmove(&me->data[i + 1], &me->data[i], (me->size - i) * sizeof(T)); \
        me->data[i] = e; \
        me->size++; \
    } \
    ATTR void xkvectorinsertafter(T)(xkvector(T)* me, size_t i, T e) \
    { \
        xkassert(i < me->size); \
        size_t pos = i + 1; \
        xkvectorinsertbefore(T)(me, pos, e); \
    } \
    ATTR void xkvectorerase(T)(xkvector(T)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        if (i + 1 < me->size) \
            memmove(&me->data[i], &me->data[i + 1], (me->size - i - 1) * sizeof(T)); \
        me->size--; \
    } \
    ATTR void xkvectorcutout(T)(xkvector(T)* me, size_t i, size_t n) \
    { \
        xkassert(i <= me->size); \
        xkassert(n <= me->size - i); \
        if (n == 0) return; \
        if (i + n < me->size) \
            memmove(&me->data[i], &me->data[i + n], (me->size - i - n) * sizeof(T)); \
        me->size -= n; \
    } \
    ATTR void xkvectoroverwrite(T)(xkvector(T)* me, size_t i, const T* p, size_t n) \
    { \
        if (n == 0) return; \
        if (n > (size_t)-1 / sizeof(T) || n > (size_t)-1 - i) \
            xkabort(); \
        T* tmp = NULL; \
        if (XK_PRIVATE_VECTOR_OVERLAPPING(me, p, n)) \
        { \
            tmp = (T*)xkrealloc(NULL, n * sizeof(T)); \
            if (!tmp) xkabort(); \
            memcpy(tmp, p, n * sizeof(T)); \
            p = tmp; \
        } \
        if (i + n > me->size) \
            xkvectorresize(T)(me, i + n); \
        memmove(&me->data[i], p, n * sizeof(T)); \
        if (tmp) xkfree(tmp); \
    } \
    ATTR void xkvectorclear(T)(xkvector(T)* me) \
    { \
        me->size = 0; \
    } \
    ATTR void xkvectorassign(T)(xkvector(T)* me, const T* p, size_t n) \
    { \
        if (n == 0) \
        { \
            xkvectorclear(T)(me); \
            return; \
        } \
        if (n > (size_t)-1 / sizeof(T)) xkabort(); \
        T* tmp = NULL; \
        if (XK_PRIVATE_VECTOR_OVERLAPPING(me, p, n)) \
        { \
            tmp = (T*)xkrealloc(NULL, n * sizeof(T)); \
            if (!tmp) xkabort(); \
            memcpy(tmp, p, n * sizeof(T)); \
            p = tmp; \
        } \
        xkvectorclear(T)(me); \
        xkvectorappend(T)(me, p, n); \
        if (tmp) xkfree(tmp); \
    } \
    ATTR void xkvectorcopy(T)(xkvector(T)* dst, const xkvector(T)* src) \
    { \
        if (dst == src) return; \
        xkvectorclear(T)(dst); \
        if (src->size > dst->capacity) \
            xkvectorreserve(T)(dst, src->size); \
        if (src->size) \
            memcpy(dst->data, src->data, src->size * sizeof(T)); \
        dst->size = src->size; \
    } \
    ATTR xkvector(T) xkvectorclone(T)(const xkvector(T)* me) \
    { \
        xkvector(T) r; \
        xkvectorinit(T)(&r, me->size); \
        if (me->size) \
        { \
            memcpy(r.data, me->data, me->size * sizeof(T)); \
            r.size = me->size; \
        } \
        return r; \
    } \
    ATTR void xkvectormove(T)(xkvector(T)* dst, xkvector(T)* src) \
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
    ATTR void xkvectorswap(T)(xkvector(T)* a, xkvector(T)* b) \
    { \
        xkvector(T) tmp = *a; \
        *a = *b; \
        *b = tmp; \
    } \
    ATTR size_t xkvectorsize(T)(const xkvector(T)* me) \
    { \
        return me->size; \
    } \
    ATTR size_t xkvectorcapacity(T)(const xkvector(T)* me) \
    { \
        return me->capacity; \
    } \
    ATTR int xkvectorempty(T)(const xkvector(T)* me) \
    { \
        return me->size == 0; \
    } \
    ATTR xkview(T) xkvectorview(T)(const xkvector(T)* me) \
    { \
        xkview(T) r = { me->data, me->size }; \
        return r; \
    } \
    ATTR xkspan(T) xkvectorspan(T)(xkvector(T)* me) \
    { \
        xkspan(T) r = { me->data, me->size }; \
        return r; \
    }

// MARK: sugar
#define xkvectorforeach(T, ME, IT) \
    for (T* IT = (ME)->data, *IT##_HIDE_end = (ME)->data + (ME)->size; IT != IT##_HIDE_end; ++IT)
#define xkvectorforeach_const(T, ME, IT) \
    for (const T* IT = (ME)->data, *IT##_HIDE_end = (ME)->data + (ME)->size; IT != IT##_HIDE_end; ++IT)
#define xkvectorrforeach(T, ME, IT) \
    for (T* IT##_HIDE_start = (ME)->data, *IT = IT##_HIDE_start + (ME)->size; IT != IT##_HIDE_start && (--IT, 1);)
#define xkvectorrforeach_const(T, ME, IT) \
    for (const T* IT##_HIDE_start = (ME)->data, *IT = IT##_HIDE_start + (ME)->size; IT != IT##_HIDE_start && (--IT, 1);)

#include <stdbool.h>
#include <stdint.h>
xkvectordecl(bool, static inline)
xkvectorimpl(bool, static inline)
xkvectordecl(char, static inline)
xkvectorimpl(char, static inline)
xkvectordecl(short, static inline)
xkvectorimpl(short, static inline)
xkvectordecl(int, static inline)
xkvectorimpl(int, static inline)
xkvectordecl(long, static inline)
xkvectorimpl(long, static inline)
xkvectordecl(float, static inline)
xkvectorimpl(float, static inline)
xkvectordecl(double, static inline)
xkvectorimpl(double, static inline)
xkvectordecl(int8_t, static inline)
xkvectorimpl(int8_t, static inline)
xkvectordecl(int16_t, static inline)
xkvectorimpl(int16_t, static inline)
xkvectordecl(int32_t, static inline)
xkvectorimpl(int32_t, static inline)
xkvectordecl(int64_t, static inline)
xkvectorimpl(int64_t, static inline)
xkvectordecl(uint8_t, static inline)
xkvectorimpl(uint8_t, static inline)
xkvectordecl(uint16_t, static inline)
xkvectorimpl(uint16_t, static inline)
xkvectordecl(uint32_t, static inline)
xkvectorimpl(uint32_t, static inline)
xkvectordecl(uint64_t, static inline)
xkvectorimpl(uint64_t, static inline)
xkvectordecl(intptr_t, static inline)
xkvectorimpl(intptr_t, static inline)
xkvectordecl(uintptr_t, static inline)
xkvectorimpl(uintptr_t, static inline)
xkvectordecl(intmax_t, static inline)
xkvectorimpl(intmax_t, static inline)
xkvectordecl(uintmax_t, static inline)
xkvectorimpl(uintmax_t, static inline)
xkvectordecl(int_least8_t, static inline)
xkvectorimpl(int_least8_t, static inline)
xkvectordecl(int_least16_t, static inline)
xkvectorimpl(int_least16_t, static inline)
xkvectordecl(int_least32_t, static inline)
xkvectorimpl(int_least32_t, static inline)
xkvectordecl(int_least64_t, static inline)
xkvectorimpl(int_least64_t, static inline)
xkvectordecl(uint_least8_t, static inline)
xkvectorimpl(uint_least8_t, static inline)
xkvectordecl(uint_least16_t, static inline)
xkvectorimpl(uint_least16_t, static inline)
xkvectordecl(uint_least32_t, static inline)
xkvectorimpl(uint_least32_t, static inline)
xkvectordecl(uint_least64_t, static inline)
xkvectorimpl(uint_least64_t, static inline)
xkvectordecl(int_fast8_t, static inline)
xkvectorimpl(int_fast8_t, static inline)
xkvectordecl(int_fast16_t, static inline)
xkvectorimpl(int_fast16_t, static inline)
xkvectordecl(int_fast32_t, static inline)
xkvectorimpl(int_fast32_t, static inline)
xkvectordecl(int_fast64_t, static inline)
xkvectorimpl(int_fast64_t, static inline)
xkvectordecl(uint_fast8_t, static inline)
xkvectorimpl(uint_fast8_t, static inline)
xkvectordecl(uint_fast16_t, static inline)
xkvectorimpl(uint_fast16_t, static inline)
xkvectordecl(uint_fast32_t, static inline)
xkvectorimpl(uint_fast32_t, static inline)
xkvectordecl(uint_fast64_t, static inline)
xkvectorimpl(uint_fast64_t, static inline)
xkvectordecl(size_t, static inline)
xkvectorimpl(size_t, static inline)
xkvectordecl(ptrdiff_t, static inline)
xkvectorimpl(ptrdiff_t, static inline)
xkvectordecl(wchar_t, static inline)
xkvectorimpl(wchar_t, static inline)


#endif