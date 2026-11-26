// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__XKFIXEDVECTOR_H
#define XK_INTERNAL__XKFIXEDVECTOR_H

#include "_xkconf.h"
#include "_xkvector.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef XK_CAT
#define XK_CAT_(a, b)   a##b
#define XK_CAT(a, b)    XK_CAT_(a, b)
#endif

#define XK_PRIVATE_FIXEDVECTOR_NAME(NAME, T, N) \
    XK_CAT(XK_CAT(NAME, T), XK_CAT(_, N))

#define xkfixedvector(T, N)              XK_PRIVATE_FIXEDVECTOR_NAME(xkfixedvector_, T, N)
#define xkfixedvectorinit(T, N)          XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_init_, T, N)
#define xkfixedvectorresize(T, N)        XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_resize_, T, N)
#define xkfixedvectorpushfront(T, N)     XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_pushfront_, T, N)
#define xkfixedvectorpushback(T, N)      XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_pushback_, T, N)
#define xkfixedvectoremplacefront(T, N)  XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_emplacefront_, T, N)
#define xkfixedvectoremplaceback(T, N)   XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_emplaceback_, T, N)
#define xkfixedvectorappend(T, N)        XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_append_, T, N)
#define xkfixedvectorpopfront(T, N)      XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_popfront_, T, N)
#define xkfixedvectorpopback(T, N)       XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_popback_, T, N)
#define xkfixedvectordata(T, N)          XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_data_, T, N)
#define xkfixedvectordata_const(T, N)    XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_data_const_, T, N)
#define xkfixedvectorget(T, N)           XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_get_, T, N)
#define xkfixedvectorset(T, N)           XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_set_, T, N)
#define xkfixedvectorat(T, N)            XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_at_, T, N)
#define xkfixedvectorat_const(T, N)      XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_at_const_, T, N)
#define xkfixedvectorfront(T, N)         XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_front_, T, N)
#define xkfixedvectorfront_const(T, N)   XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_front_const_, T, N)
#define xkfixedvectorback(T, N)          XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_back_, T, N)
#define xkfixedvectorback_const(T, N)    XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_back_const_, T, N)
#define xkfixedvectorinsertbefore(T, N)  XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_insertbefore_, T, N)
#define xkfixedvectorinsertafter(T, N)   XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_insertafter_, T, N)
#define xkfixedvectorerase(T, N)         XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_erase_, T, N)
#define xkfixedvectorcutout(T, N)        XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_cutout_, T, N)
#define xkfixedvectoroverwrite(T, N)     XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_overwrite_, T, N)
#define xkfixedvectorclear(T, N)         XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_clear_, T, N)
#define xkfixedvectorassign(T, N)        XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_assign_, T, N)
#define xkfixedvectorcopy(T, N)          XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_copy_, T, N)
#define xkfixedvectorclone(T, N)         XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_clone_, T, N)
#define xkfixedvectormove(T, N)          XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_move_, T, N)
#define xkfixedvectorswap(T, N)          XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_swap_, T, N)
#define xkfixedvectorsize(T, N)          XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_size_, T, N)
#define xkfixedvectorcapacity(T, N)      XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_capacity_, T, N)
#define xkfixedvectorempty(T, N)         XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_empty_, T, N)
#define xkfixedvectorfull(T, N)          XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_full_, T, N)
#define xkfixedvectorview(T, N)          XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_view_, T, N)
#define xkfixedvectorspan(T, N)          XK_PRIVATE_FIXEDVECTOR_NAME(xk_PUBLIC_fixedvector_span_, T, N)

// MARK: decl
#define xkfixedvectordecl(T, N, ATTR) \
    typedef struct xkfixedvector(T, N) \
    { \
        T data[(N) ? (N) : 1]; \
        size_t size; \
    } xkfixedvector(T, N); \
    ATTR void xkfixedvectorinit(T, N)(xkfixedvector(T, N)* me); \
    ATTR void xkfixedvectorresize(T, N)(xkfixedvector(T, N)* me, size_t n); \
    ATTR void xkfixedvectorpushfront(T, N)(xkfixedvector(T, N)* me, T e); \
    ATTR void xkfixedvectorpushback(T, N)(xkfixedvector(T, N)* me, T e); \
    ATTR T* xkfixedvectoremplacefront(T, N)(xkfixedvector(T, N)* me); \
    ATTR T* xkfixedvectoremplaceback(T, N)(xkfixedvector(T, N)* me); \
    ATTR void xkfixedvectorappend(T, N)(xkfixedvector(T, N)* me, const T* p, size_t n); \
    ATTR void xkfixedvectorpopfront(T, N)(xkfixedvector(T, N)* me); \
    ATTR void xkfixedvectorpopback(T, N)(xkfixedvector(T, N)* me); \
    ATTR T* xkfixedvectordata(T, N)(xkfixedvector(T, N)* me); \
    ATTR const T* xkfixedvectordata_const(T, N)(const xkfixedvector(T, N)* me); \
    ATTR T xkfixedvectorget(T, N)(const xkfixedvector(T, N)* me, size_t i); \
    ATTR void xkfixedvectorset(T, N)(xkfixedvector(T, N)* me, size_t i, T e); \
    ATTR T* xkfixedvectorat(T, N)(xkfixedvector(T, N)* me, size_t i); \
    ATTR const T* xkfixedvectorat_const(T, N)(const xkfixedvector(T, N)* me, size_t i); \
    ATTR T* xkfixedvectorfront(T, N)(xkfixedvector(T, N)* me); \
    ATTR const T* xkfixedvectorfront_const(T, N)(const xkfixedvector(T, N)* me); \
    ATTR T* xkfixedvectorback(T, N)(xkfixedvector(T, N)* me); \
    ATTR const T* xkfixedvectorback_const(T, N)(const xkfixedvector(T, N)* me); \
    ATTR void xkfixedvectorinsertbefore(T, N)(xkfixedvector(T, N)* me, size_t i, T e); \
    ATTR void xkfixedvectorinsertafter(T, N)(xkfixedvector(T, N)* me, size_t i, T e); \
    ATTR void xkfixedvectorerase(T, N)(xkfixedvector(T, N)* me, size_t i); \
    ATTR void xkfixedvectorcutout(T, N)(xkfixedvector(T, N)* me, size_t i, size_t n); \
    ATTR void xkfixedvectoroverwrite(T, N)(xkfixedvector(T, N)* me, size_t i, const T* p, size_t n); \
    ATTR void xkfixedvectorclear(T, N)(xkfixedvector(T, N)* me); \
    ATTR void xkfixedvectorassign(T, N)(xkfixedvector(T, N)* me, const T* p, size_t n); \
    ATTR void xkfixedvectorcopy(T, N)(xkfixedvector(T, N)* dst, const xkfixedvector(T, N)* src); \
    ATTR xkfixedvector(T, N) xkfixedvectorclone(T, N)(const xkfixedvector(T, N)* me); \
    ATTR void xkfixedvectormove(T, N)(xkfixedvector(T, N)* dst, xkfixedvector(T, N)* src); \
    ATTR void xkfixedvectorswap(T, N)(xkfixedvector(T, N)* a, xkfixedvector(T, N)* b); \
    ATTR size_t xkfixedvectorsize(T, N)(const xkfixedvector(T, N)* me); \
    ATTR size_t xkfixedvectorcapacity(T, N)(const xkfixedvector(T, N)* me); \
    ATTR int xkfixedvectorempty(T, N)(const xkfixedvector(T, N)* me); \
    ATTR int xkfixedvectorfull(T, N)(const xkfixedvector(T, N)* me); \
    ATTR xkview(T) xkfixedvectorview(T, N)(const xkfixedvector(T, N)* me); \
    ATTR xkspan(T) xkfixedvectorspan(T, N)(xkfixedvector(T, N)* me);

// MARK: impl
#define xkfixedvectorimpl(T, N, ATTR) \
    ATTR void xkfixedvectorinit(T, N)(xkfixedvector(T, N)* me) \
    { \
        me->size = 0; \
    } \
    ATTR void xkfixedvectorresize(T, N)(xkfixedvector(T, N)* me, size_t n) \
    { \
        if (n > (size_t)(N)) xkabort(); \
        if (n > me->size) \
            memset(me->data + me->size, 0, (n - me->size) * sizeof(T)); \
        me->size = n; \
    } \
    ATTR void xkfixedvectorpushfront(T, N)(xkfixedvector(T, N)* me, T e) \
    { \
        *xkfixedvectoremplacefront(T, N)(me) = e; \
    } \
    ATTR void xkfixedvectorpushback(T, N)(xkfixedvector(T, N)* me, T e) \
    { \
        *xkfixedvectoremplaceback(T, N)(me) = e; \
    } \
    ATTR T* xkfixedvectoremplacefront(T, N)(xkfixedvector(T, N)* me) \
    { \
        if (me->size >= (size_t)(N)) xkabort(); \
        if (me->size) \
            memmove(&me->data[1], &me->data[0], me->size * sizeof(T)); \
        ++me->size; \
        return &me->data[0]; \
    } \
    ATTR T* xkfixedvectoremplaceback(T, N)(xkfixedvector(T, N)* me) \
    { \
        if (me->size >= (size_t)(N)) xkabort(); \
        return &me->data[me->size++]; \
    } \
    ATTR void xkfixedvectorappend(T, N)(xkfixedvector(T, N)* me, const T* p, size_t n) \
    { \
        if (n == 0) return; \
        if (me->size > (size_t)(N) || n > (size_t)(N) - me->size) \
            xkabort(); \
        memmove(me->data + me->size, p, n * sizeof(T)); \
        me->size += n; \
    } \
    ATTR void xkfixedvectorpopfront(T, N)(xkfixedvector(T, N)* me) \
    { \
        xkassert(me->size > 0); \
        if (me->size > 1) \
            memmove(&me->data[0], &me->data[1], (me->size - 1) * sizeof(T)); \
        --me->size; \
    } \
    ATTR void xkfixedvectorpopback(T, N)(xkfixedvector(T, N)* me) \
    { \
        xkassert(me->size > 0); \
        --me->size; \
    } \
    ATTR T* xkfixedvectordata(T, N)(xkfixedvector(T, N)* me) \
    { \
        return me->data; \
    } \
    ATTR const T* xkfixedvectordata_const(T, N)(const xkfixedvector(T, N)* me) \
    { \
        return me->data; \
    } \
    ATTR T xkfixedvectorget(T, N)(const xkfixedvector(T, N)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        return me->data[i]; \
    } \
    ATTR void xkfixedvectorset(T, N)(xkfixedvector(T, N)* me, size_t i, T e) \
    { \
        xkassert(i < me->size); \
        me->data[i] = e; \
    } \
    ATTR T* xkfixedvectorat(T, N)(xkfixedvector(T, N)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        return &me->data[i]; \
    } \
    ATTR const T* xkfixedvectorat_const(T, N)(const xkfixedvector(T, N)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        return &me->data[i]; \
    } \
    ATTR T* xkfixedvectorfront(T, N)(xkfixedvector(T, N)* me) \
    { \
        xkassert(me->size > 0); \
        return &me->data[0]; \
    } \
    ATTR const T* xkfixedvectorfront_const(T, N)(const xkfixedvector(T, N)* me) \
    { \
        xkassert(me->size > 0); \
        return &me->data[0]; \
    } \
    ATTR T* xkfixedvectorback(T, N)(xkfixedvector(T, N)* me) \
    { \
        xkassert(me->size > 0); \
        return &me->data[me->size - 1]; \
    } \
    ATTR const T* xkfixedvectorback_const(T, N)(const xkfixedvector(T, N)* me) \
    { \
        xkassert(me->size > 0); \
        return &me->data[me->size - 1]; \
    } \
    ATTR void xkfixedvectorinsertbefore(T, N)(xkfixedvector(T, N)* me, size_t i, T e) \
    { \
        xkassert(i <= me->size); \
        if (me->size >= (size_t)(N)) xkabort(); \
        memmove(&me->data[i + 1], &me->data[i], (me->size - i) * sizeof(T)); \
        me->data[i] = e; \
        me->size++; \
    } \
    ATTR void xkfixedvectorinsertafter(T, N)(xkfixedvector(T, N)* me, size_t i, T e) \
    { \
        xkassert(i < me->size); \
        xkfixedvectorinsertbefore(T, N)(me, i + 1, e); \
    } \
    ATTR void xkfixedvectorerase(T, N)(xkfixedvector(T, N)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        if (i + 1 < me->size) \
            memmove(&me->data[i], &me->data[i + 1], (me->size - i - 1) * sizeof(T)); \
        me->size--; \
    } \
    ATTR void xkfixedvectorcutout(T, N)(xkfixedvector(T, N)* me, size_t i, size_t n) \
    { \
        xkassert(i <= me->size); \
        xkassert(n <= me->size - i); \
        if (n == 0) return; \
        if (i + n < me->size) \
            memmove(&me->data[i], &me->data[i + n], (me->size - i - n) * sizeof(T)); \
        me->size -= n; \
    } \
    ATTR void xkfixedvectoroverwrite(T, N)(xkfixedvector(T, N)* me, size_t i, const T* p, size_t n) \
    { \
        if (n == 0) return; \
        if (i > (size_t)(N) || n > (size_t)(N) - i) xkabort(); \
        size_t oldsize = me->size; \
        memmove(&me->data[i], p, n * sizeof(T)); \
        if (i > oldsize) \
            memset(&me->data[oldsize], 0, (i - oldsize) * sizeof(T)); \
        if (i + n > oldsize) \
            me->size = i + n; \
    } \
    ATTR void xkfixedvectorclear(T, N)(xkfixedvector(T, N)* me) \
    { \
        me->size = 0; \
    } \
    ATTR void xkfixedvectorassign(T, N)(xkfixedvector(T, N)* me, const T* p, size_t n) \
    { \
        if (n > (size_t)(N)) xkabort(); \
        if (n) memmove(me->data, p, n * sizeof(T)); \
        me->size = n; \
    } \
    ATTR void xkfixedvectorcopy(T, N)(xkfixedvector(T, N)* dst, const xkfixedvector(T, N)* src) \
    { \
        if (dst == src) return; \
        if (src->size > (size_t)(N)) xkabort(); \
        if (src->size) \
            memcpy(dst->data, src->data, src->size * sizeof(T)); \
        dst->size = src->size; \
    } \
    ATTR xkfixedvector(T, N) xkfixedvectorclone(T, N)(const xkfixedvector(T, N)* me) \
    { \
        if (me->size > (size_t)(N)) xkabort(); \
        xkfixedvector(T, N) r = {0}; \
        r.size = me->size; \
        if (me->size) \
            memcpy(r.data, me->data, me->size * sizeof(T)); \
        return r; \
    } \
    ATTR void xkfixedvectormove(T, N)(xkfixedvector(T, N)* dst, xkfixedvector(T, N)* src) \
    { \
        if (dst == src) return; \
        if (src->size > (size_t)(N)) xkabort(); \
        if (src->size) \
            memcpy(dst->data, src->data, src->size * sizeof(T)); \
        dst->size = src->size; \
        src->size = 0; \
    } \
    ATTR void xkfixedvectorswap(T, N)(xkfixedvector(T, N)* a, xkfixedvector(T, N)* b) \
    { \
        if (a == b) return; \
        size_t na = a->size; \
        size_t nb = b->size; \
        xkfixedvector(T, N) tmp; \
        tmp.size = na; \
        if (na) memcpy(tmp.data, a->data, na * sizeof(T)); \
        a->size = nb; \
        if (nb) memcpy(a->data, b->data, nb * sizeof(T)); \
        b->size = na; \
        if (na) memcpy(b->data, tmp.data, na * sizeof(T)); \
    } \
    ATTR size_t xkfixedvectorsize(T, N)(const xkfixedvector(T, N)* me) \
    { \
        return me->size; \
    } \
    ATTR size_t xkfixedvectorcapacity(T, N)(const xkfixedvector(T, N)* me) \
    { \
        (void)me; \
        return (size_t)(N); \
    } \
    ATTR int xkfixedvectorempty(T, N)(const xkfixedvector(T, N)* me) \
    { \
        return me->size == 0; \
    } \
    ATTR int xkfixedvectorfull(T, N)(const xkfixedvector(T, N)* me) \
    { \
        return me->size == (size_t)(N); \
    } \
    ATTR xkview(T) xkfixedvectorview(T, N)(const xkfixedvector(T, N)* me) \
    { \
        xkview(T) r = { me->data, me->size }; \
        return r; \
    } \
    ATTR xkspan(T) xkfixedvectorspan(T, N)(xkfixedvector(T, N)* me) \
    { \
        xkspan(T) r = { me->data, me->size }; \
        return r; \
    }

// MARK: sugar
#define xkfixedvectorforeach(T, ME, IT) \
    for (T* IT = (ME)->data, *IT##_HIDE_end = (ME)->data + (ME)->size; IT != IT##_HIDE_end; ++IT)
#define xkfixedvectorforeach_const(T, ME, IT) \
    for (const T* IT = (ME)->data, *IT##_HIDE_end = (ME)->data + (ME)->size; IT != IT##_HIDE_end; ++IT)
#define xkfixedvectorrforeach(T, ME, IT) \
    for (T* IT##_HIDE_start = (ME)->data, *IT = IT##_HIDE_start + (ME)->size; IT != IT##_HIDE_start && (--IT, 1);)
#define xkfixedvectorrforeach_const(T, ME, IT) \
    for (const T* IT##_HIDE_start = (ME)->data, *IT = IT##_HIDE_start + (ME)->size; IT != IT##_HIDE_start && (--IT, 1);)

#endif
