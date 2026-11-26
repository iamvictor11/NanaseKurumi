// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__XKFIXEDSTRING_H
#define XK_INTERNAL__XKFIXEDSTRING_H

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

#define xkfixedstring(N)                XK_CAT(xkfixedstring_, N)
#define xkfixedstringinit(N)            XK_CAT(xk_PUBLIC_fixedstring_init_, N)
#define xkfixedstringresize(N)          XK_CAT(xk_PUBLIC_fixedstring_resize_, N)
#define xkfixedstringpush(N)            XK_CAT(xk_PUBLIC_fixedstring_push_, N)
#define xkfixedstringappend(N)          XK_CAT(xk_PUBLIC_fixedstring_append_, N)
#define xkfixedstringpop(N)             XK_CAT(xk_PUBLIC_fixedstring_pop_, N)
#define xkfixedstringdata(N)            XK_CAT(xk_PUBLIC_fixedstring_data_, N)
#define xkfixedstringdata_const(N)      XK_CAT(xk_PUBLIC_fixedstring_data_const_, N)
#define xkfixedstringc_str(N)           XK_CAT(xk_PUBLIC_fixedstring_c_str_, N)
#define xkfixedstringget(N)             XK_CAT(xk_PUBLIC_fixedstring_get_, N)
#define xkfixedstringset(N)             XK_CAT(xk_PUBLIC_fixedstring_set_, N)
#define xkfixedstringat(N)              XK_CAT(xk_PUBLIC_fixedstring_at_, N)
#define xkfixedstringat_const(N)        XK_CAT(xk_PUBLIC_fixedstring_at_const_, N)
#define xkfixedstringfront(N)           XK_CAT(xk_PUBLIC_fixedstring_front_, N)
#define xkfixedstringfront_const(N)     XK_CAT(xk_PUBLIC_fixedstring_front_const_, N)
#define xkfixedstringback(N)            XK_CAT(xk_PUBLIC_fixedstring_back_, N)
#define xkfixedstringback_const(N)      XK_CAT(xk_PUBLIC_fixedstring_back_const_, N)
#define xkfixedstringinsert(N)          XK_CAT(xk_PUBLIC_fixedstring_insert_, N)
#define xkfixedstringsplice(N)          XK_CAT(xk_PUBLIC_fixedstring_splice_, N)
#define xkfixedstringerase(N)           XK_CAT(xk_PUBLIC_fixedstring_erase_, N)
#define xkfixedstringcutout(N)          XK_CAT(xk_PUBLIC_fixedstring_cutout_, N)
#define xkfixedstringoverwrite(N)       XK_CAT(xk_PUBLIC_fixedstring_overwrite_, N)
#define xkfixedstringclear(N)           XK_CAT(xk_PUBLIC_fixedstring_clear_, N)
#define xkfixedstringassign(N)          XK_CAT(xk_PUBLIC_fixedstring_assign_, N)
#define xkfixedstringcopy(N)            XK_CAT(xk_PUBLIC_fixedstring_copy_, N)
#define xkfixedstringclone(N)           XK_CAT(xk_PUBLIC_fixedstring_clone_, N)
#define xkfixedstringsub(N)             XK_CAT(xk_PUBLIC_fixedstring_sub_, N)
#define xkfixedstringconcat(N)          XK_CAT(xk_PUBLIC_fixedstring_concat_, N)
#define xkfixedstringmove(N)            XK_CAT(xk_PUBLIC_fixedstring_move_, N)
#define xkfixedstringswap(N)            XK_CAT(xk_PUBLIC_fixedstring_swap_, N)
#define xkfixedstringfind(N)            XK_CAT(xk_PUBLIC_fixedstring_find_, N)
#define xkfixedstringmatch(N)           XK_CAT(xk_PUBLIC_fixedstring_match_, N)
#define xkfixedstringcontains(N)        XK_CAT(xk_PUBLIC_fixedstring_contains_, N)
#define xkfixedstringprefix(N)          XK_CAT(xk_PUBLIC_fixedstring_prefix_, N)
#define xkfixedstringsuffix(N)          XK_CAT(xk_PUBLIC_fixedstring_suffix_, N)
#define xkfixedstringsize(N)            XK_CAT(xk_PUBLIC_fixedstring_size_, N)
#define xkfixedstringlength(N)          XK_CAT(xk_PUBLIC_fixedstring_length_, N)
#define xkfixedstringcapacity(N)        XK_CAT(xk_PUBLIC_fixedstring_capacity_, N)
#define xkfixedstringempty(N)           XK_CAT(xk_PUBLIC_fixedstring_empty_, N)
#define xkfixedstringfull(N)            XK_CAT(xk_PUBLIC_fixedstring_full_, N)
#define xkfixedstringview(N)            XK_CAT(xk_PUBLIC_fixedstring_view_, N)
#define xkfixedstringspan(N)            XK_CAT(xk_PUBLIC_fixedstring_span_, N)

// MARK: decl
#define xkfixedstringdecl(N, ATTR) \
    typedef struct xkfixedstring(N) \
    { \
        char data[((N) ? ((N) + 1) : 1)]; \
        size_t size; \
    } xkfixedstring(N); \
    ATTR void xkfixedstringinit(N)(xkfixedstring(N)* me); \
    ATTR void xkfixedstringresize(N)(xkfixedstring(N)* me, size_t n); \
    ATTR void xkfixedstringpush(N)(xkfixedstring(N)* me, char e); \
    ATTR void xkfixedstringappend(N)(xkfixedstring(N)* me, const char* p, size_t n); \
    ATTR char xkfixedstringpop(N)(xkfixedstring(N)* me); \
    ATTR char* xkfixedstringdata(N)(xkfixedstring(N)* me); \
    ATTR const char* xkfixedstringdata_const(N)(const xkfixedstring(N)* me); \
    ATTR const char* xkfixedstringc_str(N)(const xkfixedstring(N)* me); \
    ATTR char xkfixedstringget(N)(const xkfixedstring(N)* me, size_t i); \
    ATTR void xkfixedstringset(N)(xkfixedstring(N)* me, size_t i, char e); \
    ATTR char* xkfixedstringat(N)(xkfixedstring(N)* me, size_t i); \
    ATTR const char* xkfixedstringat_const(N)(const xkfixedstring(N)* me, size_t i); \
    ATTR char* xkfixedstringfront(N)(xkfixedstring(N)* me); \
    ATTR const char* xkfixedstringfront_const(N)(const xkfixedstring(N)* me); \
    ATTR char* xkfixedstringback(N)(xkfixedstring(N)* me); \
    ATTR const char* xkfixedstringback_const(N)(const xkfixedstring(N)* me); \
    ATTR void xkfixedstringinsert(N)(xkfixedstring(N)* me, size_t i, char e); \
    ATTR void xkfixedstringsplice(N)(xkfixedstring(N)* me, size_t i, const char* p, size_t n); \
    ATTR void xkfixedstringerase(N)(xkfixedstring(N)* me, size_t i); \
    ATTR void xkfixedstringcutout(N)(xkfixedstring(N)* me, size_t i, size_t n); \
    ATTR void xkfixedstringoverwrite(N)(xkfixedstring(N)* me, size_t i, const char* p, size_t n); \
    ATTR void xkfixedstringclear(N)(xkfixedstring(N)* me); \
    ATTR void xkfixedstringassign(N)(xkfixedstring(N)* me, const char* p, size_t n); \
    ATTR void xkfixedstringcopy(N)(xkfixedstring(N)* dst, const xkfixedstring(N)* src); \
    ATTR xkfixedstring(N) xkfixedstringclone(N)(const xkfixedstring(N)* me); \
    ATTR xkfixedstring(N) xkfixedstringsub(N)(const xkfixedstring(N)* me, size_t start, size_t n); \
    ATTR xkfixedstring(N) xkfixedstringconcat(N)(const xkfixedstring(N)* a, const xkfixedstring(N)* b); \
    ATTR void xkfixedstringmove(N)(xkfixedstring(N)* dst, xkfixedstring(N)* src); \
    ATTR void xkfixedstringswap(N)(xkfixedstring(N)* a, xkfixedstring(N)* b); \
    ATTR size_t xkfixedstringfind(N)(const xkfixedstring(N)* me, char e); \
    ATTR size_t xkfixedstringmatch(N)(const xkfixedstring(N)* me, const char* p, size_t n); \
    ATTR int xkfixedstringcontains(N)(const xkfixedstring(N)* me, char e); \
    ATTR int xkfixedstringprefix(N)(const xkfixedstring(N)* me, const char* p, size_t n); \
    ATTR int xkfixedstringsuffix(N)(const xkfixedstring(N)* me, const char* p, size_t n); \
    ATTR size_t xkfixedstringsize(N)(const xkfixedstring(N)* me); \
    ATTR size_t xkfixedstringlength(N)(const xkfixedstring(N)* me); \
    ATTR size_t xkfixedstringcapacity(N)(const xkfixedstring(N)* me); \
    ATTR int xkfixedstringempty(N)(const xkfixedstring(N)* me); \
    ATTR int xkfixedstringfull(N)(const xkfixedstring(N)* me); \
    ATTR xkview(char) xkfixedstringview(N)(const xkfixedstring(N)* me); \
    ATTR xkspan(char) xkfixedstringspan(N)(xkfixedstring(N)* me); \
    ATTR bool xkequal(xkfixedstring(N))(xkfixedstring(N) a, xkfixedstring(N) b); \
    ATTR int xkcompare(xkfixedstring(N))(xkfixedstring(N) a, xkfixedstring(N) b); \
    ATTR size_t xkhash(xkfixedstring(N))(xkfixedstring(N) v);

// MARK: impl
#define xkfixedstringimpl(N, ATTR) \
    ATTR void xkfixedstringinit(N)(xkfixedstring(N)* me) \
    { \
        me->size = 0; \
        me->data[0] = 0; \
    } \
    ATTR void xkfixedstringresize(N)(xkfixedstring(N)* me, size_t n) \
    { \
        if (n > (size_t)(N)) xkabort(); \
        if (n > me->size) \
            memset(me->data + me->size, 0, n - me->size); \
        me->size = n; \
        me->data[me->size] = 0; \
    } \
    ATTR void xkfixedstringpush(N)(xkfixedstring(N)* me, char e) \
    { \
        if (me->size >= (size_t)(N)) xkabort(); \
        me->data[me->size++] = e; \
        me->data[me->size] = 0; \
    } \
    ATTR void xkfixedstringappend(N)(xkfixedstring(N)* me, const char* p, size_t n) \
    { \
        if (n == 0) return; \
        if (me->size > (size_t)(N) || n > (size_t)(N) - me->size) \
            xkabort(); \
        memmove(me->data + me->size, p, n); \
        me->size += n; \
        me->data[me->size] = 0; \
    } \
    ATTR char xkfixedstringpop(N)(xkfixedstring(N)* me) \
    { \
        xkassert(me->size > 0); \
        char e = me->data[--me->size]; \
        me->data[me->size] = 0; \
        return e; \
    } \
    ATTR char* xkfixedstringdata(N)(xkfixedstring(N)* me) \
    { \
        return me->data; \
    } \
    ATTR const char* xkfixedstringdata_const(N)(const xkfixedstring(N)* me) \
    { \
        return me->data; \
    } \
    ATTR const char* xkfixedstringc_str(N)(const xkfixedstring(N)* me) \
    { \
        return me->data; \
    } \
    ATTR char xkfixedstringget(N)(const xkfixedstring(N)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        return me->data[i]; \
    } \
    ATTR void xkfixedstringset(N)(xkfixedstring(N)* me, size_t i, char e) \
    { \
        xkassert(i < me->size); \
        me->data[i] = e; \
    } \
    ATTR char* xkfixedstringat(N)(xkfixedstring(N)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        return &me->data[i]; \
    } \
    ATTR const char* xkfixedstringat_const(N)(const xkfixedstring(N)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        return &me->data[i]; \
    } \
    ATTR char* xkfixedstringfront(N)(xkfixedstring(N)* me) \
    { \
        xkassert(me->size > 0); \
        return &me->data[0]; \
    } \
    ATTR const char* xkfixedstringfront_const(N)(const xkfixedstring(N)* me) \
    { \
        xkassert(me->size > 0); \
        return &me->data[0]; \
    } \
    ATTR char* xkfixedstringback(N)(xkfixedstring(N)* me) \
    { \
        xkassert(me->size > 0); \
        return &me->data[me->size - 1]; \
    } \
    ATTR const char* xkfixedstringback_const(N)(const xkfixedstring(N)* me) \
    { \
        xkassert(me->size > 0); \
        return &me->data[me->size - 1]; \
    } \
    ATTR void xkfixedstringinsert(N)(xkfixedstring(N)* me, size_t i, char e) \
    { \
        xkassert(i <= me->size); \
        if (me->size >= (size_t)(N)) xkabort(); \
        memmove(&me->data[i + 1], &me->data[i], me->size - i); \
        me->data[i] = e; \
        me->size++; \
        me->data[me->size] = 0; \
    } \
    ATTR void xkfixedstringsplice(N)(xkfixedstring(N)* me, size_t i, const char* p, size_t n) \
    { \
        xkassert(i <= me->size); \
        if (n == 0) return; \
        if (me->size > (size_t)(N) || n > (size_t)(N) - me->size) \
            xkabort(); \
        char tmp[((N) ? (N) : 1)]; \
        memcpy(tmp, p, n); \
        memmove(&me->data[i + n], &me->data[i], me->size - i); \
        memcpy(&me->data[i], tmp, n); \
        me->size += n; \
        me->data[me->size] = 0; \
    } \
    ATTR void xkfixedstringerase(N)(xkfixedstring(N)* me, size_t i) \
    { \
        xkassert(i < me->size); \
        if (i + 1 < me->size) \
            memmove(&me->data[i], &me->data[i + 1], me->size - i - 1); \
        me->size--; \
        me->data[me->size] = 0; \
    } \
    ATTR void xkfixedstringcutout(N)(xkfixedstring(N)* me, size_t i, size_t n) \
    { \
        xkassert(i <= me->size); \
        xkassert(n <= me->size - i); \
        if (n == 0) return; \
        memmove(&me->data[i], &me->data[i + n], me->size - i - n); \
        me->size -= n; \
        me->data[me->size] = 0; \
    } \
    ATTR void xkfixedstringoverwrite(N)(xkfixedstring(N)* me, size_t i, const char* p, size_t n) \
    { \
        if (n == 0) return; \
        if (i > (size_t)(N) || n > (size_t)(N) - i) xkabort(); \
        size_t oldsize = me->size; \
        memmove(&me->data[i], p, n); \
        if (i > oldsize) \
            memset(&me->data[oldsize], 0, i - oldsize); \
        if (i + n > oldsize) \
            me->size = i + n; \
        me->data[me->size] = 0; \
    } \
    ATTR void xkfixedstringclear(N)(xkfixedstring(N)* me) \
    { \
        me->size = 0; \
        me->data[0] = 0; \
    } \
    ATTR void xkfixedstringassign(N)(xkfixedstring(N)* me, const char* p, size_t n) \
    { \
        if (n > (size_t)(N)) xkabort(); \
        if (n) memmove(me->data, p, n); \
        me->size = n; \
        me->data[me->size] = 0; \
    } \
    ATTR void xkfixedstringcopy(N)(xkfixedstring(N)* dst, const xkfixedstring(N)* src) \
    { \
        if (dst == src) return; \
        if (src->size > (size_t)(N)) xkabort(); \
        if (src->size) \
            memcpy(dst->data, src->data, src->size); \
        dst->size = src->size; \
        dst->data[dst->size] = 0; \
    } \
    ATTR xkfixedstring(N) xkfixedstringclone(N)(const xkfixedstring(N)* me) \
    { \
        if (me->size > (size_t)(N)) xkabort(); \
        xkfixedstring(N) r = {0}; \
        r.size = me->size; \
        if (me->size) memcpy(r.data, me->data, me->size); \
        r.data[r.size] = 0; \
        return r; \
    } \
    ATTR xkfixedstring(N) xkfixedstringsub(N)(const xkfixedstring(N)* me, size_t start, size_t n) \
    { \
        xkassert(start <= me->size); \
        xkassert(n <= me->size - start); \
        xkfixedstring(N) r = {0}; \
        r.size = n; \
        if (n) memcpy(r.data, me->data + start, n); \
        r.data[r.size] = 0; \
        return r; \
    } \
    ATTR xkfixedstring(N) xkfixedstringconcat(N)(const xkfixedstring(N)* a, const xkfixedstring(N)* b) \
    { \
        if (a->size > (size_t)(N) || b->size > (size_t)(N) - a->size) \
            xkabort(); \
        xkfixedstring(N) r = {0}; \
        r.size = a->size + b->size; \
        if (a->size) memcpy(r.data, a->data, a->size); \
        if (b->size) memcpy(r.data + a->size, b->data, b->size); \
        r.data[r.size] = 0; \
        return r; \
    } \
    ATTR void xkfixedstringmove(N)(xkfixedstring(N)* dst, xkfixedstring(N)* src) \
    { \
        if (dst == src) return; \
        if (src->size > (size_t)(N)) xkabort(); \
        if (src->size) memcpy(dst->data, src->data, src->size); \
        dst->size = src->size; \
        dst->data[dst->size] = 0; \
        src->size = 0; \
        src->data[0] = 0; \
    } \
    ATTR void xkfixedstringswap(N)(xkfixedstring(N)* a, xkfixedstring(N)* b) \
    { \
        xkfixedstring(N) tmp = *a; \
        *a = *b; \
        *b = tmp; \
    } \
    ATTR size_t xkfixedstringfind(N)(const xkfixedstring(N)* me, char e) \
    { \
        for (size_t i = 0; i < me->size; ++i) \
            if (me->data[i] == e) \
                return i; \
        return (size_t)-1; \
    } \
    ATTR size_t xkfixedstringmatch(N)(const xkfixedstring(N)* me, const char* p, size_t n) \
    { \
        if (n == 0) return 0; \
        if (n > me->size) return (size_t)-1; \
        for (size_t i = 0; i <= me->size - n; ++i) \
            if (memcmp(&me->data[i], p, n) == 0) \
                return i; \
        return (size_t)-1; \
    } \
    ATTR int xkfixedstringcontains(N)(const xkfixedstring(N)* me, char e) \
    { \
        return xkfixedstringfind(N)(me, e) != (size_t)-1; \
    } \
    ATTR int xkfixedstringprefix(N)(const xkfixedstring(N)* me, const char* p, size_t n) \
    { \
        return n <= me->size && memcmp(me->data, p, n) == 0; \
    } \
    ATTR int xkfixedstringsuffix(N)(const xkfixedstring(N)* me, const char* p, size_t n) \
    { \
        return n <= me->size && memcmp(me->data + me->size - n, p, n) == 0; \
    } \
    ATTR size_t xkfixedstringsize(N)(const xkfixedstring(N)* me) \
    { \
        return me->size; \
    } \
    ATTR size_t xkfixedstringlength(N)(const xkfixedstring(N)* me) \
    { \
        return me->size; \
    } \
    ATTR size_t xkfixedstringcapacity(N)(const xkfixedstring(N)* me) \
    { \
        (void)me; \
        return (size_t)(N); \
    } \
    ATTR int xkfixedstringempty(N)(const xkfixedstring(N)* me) \
    { \
        return me->size == 0; \
    } \
    ATTR int xkfixedstringfull(N)(const xkfixedstring(N)* me) \
    { \
        return me->size == (size_t)(N); \
    } \
    ATTR xkview(char) xkfixedstringview(N)(const xkfixedstring(N)* me) \
    { \
        xkview(char) r = { me->data, me->size }; \
        return r; \
    } \
    ATTR xkspan(char) xkfixedstringspan(N)(xkfixedstring(N)* me) \
    { \
        xkspan(char) r = { me->data, me->size }; \
        return r; \
    } \
    ATTR bool xkequal(xkfixedstring(N))(xkfixedstring(N) a, xkfixedstring(N) b) \
    { \
        if (a.size != b.size) return false; \
        return a.size == 0 || memcmp(a.data, b.data, a.size) == 0; \
    } \
    ATTR int xkcompare(xkfixedstring(N))(xkfixedstring(N) a, xkfixedstring(N) b) \
    { \
        size_t n = a.size < b.size ? a.size : b.size; \
        int r = n ? memcmp(a.data, b.data, n) : 0; \
        if (r != 0) return r; \
        if (a.size < b.size) return -1; \
        if (a.size > b.size) return 1; \
        return 0; \
    } \
    ATTR size_t xkhash(xkfixedstring(N))(xkfixedstring(N) v) \
    { \
        const uint64_t FNV_OFFSET = 0xCBF29CE484222325ull; \
        const uint64_t FNV_PRIME  = 0x100000001B3ull; \
        uint64_t h = FNV_OFFSET ^ (uint64_t)(v.size); \
        for (size_t i = 0; i < v.size; ++i) \
        { \
            h ^= (uint8_t)v.data[i]; \
            h *= FNV_PRIME; \
        } \
        return xk_PRIVATE_hash_mix64(h); \
    }

#endif
