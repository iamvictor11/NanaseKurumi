// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef STL_VECTOR_H
#define STL_VECTOR_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define STL_VECTOR_CAT_(a, b) a##b
#define STL_VECTOR_CAT(a, b)  STL_VECTOR_CAT_(a, b)

#ifndef STL_VECTOR_REALLOC
#define STL_VECTOR_REALLOC realloc
#endif

#ifndef STL_VECTOR_FREE
#define STL_VECTOR_FREE free
#endif

#ifndef STL_VECTOR_ABORT
#define STL_VECTOR_ABORT abort
#endif

#define stlvector(T)            STL_VECTOR_CAT(stl_vector_T_, T)
#define stlvectorinit(T)        STL_VECTOR_CAT(stl_vectorinit_, T)
#define stlvectorfree(T)        STL_VECTOR_CAT(stl_vectorfree_, T)
#define stlvectorreserve(T)     STL_VECTOR_CAT(stl_vectorreserve_, T)
#define stlvectorresize(T)      STL_VECTOR_CAT(stl_vectorresize_, T)
#define stlvectorshrink(T)      STL_VECTOR_CAT(stl_vectorshrink_, T)
#define stlvectorpush(T)        STL_VECTOR_CAT(stl_vectorpush_, T)
#define stlvectorpop(T)         STL_VECTOR_CAT(stl_vectorpop_, T)
#define stlvectordata(T)        STL_VECTOR_CAT(stl_vectordata_, T)
#define stlvectordata_const(T)  STL_VECTOR_CAT(stl_vectordata_const_, T)
#define stlvectorget(T)         STL_VECTOR_CAT(stl_vectorget_, T)
#define stlvectorset(T)         STL_VECTOR_CAT(stl_vectorset_, T)
#define stlvectorat(T)          STL_VECTOR_CAT(stl_vectorat_, T)
#define stlvectorat_const(T)    STL_VECTOR_CAT(stl_vectorat_const_, T)
#define stlvectorfront(T)       STL_VECTOR_CAT(stl_vectorfront_, T)
#define stlvectorfront_const(T) STL_VECTOR_CAT(stl_vectorfront_const_, T)
#define stlvectorback(T)        STL_VECTOR_CAT(stl_vectorback_, T)
#define stlvectorback_const(T)  STL_VECTOR_CAT(stl_vectorback_const_, T)
#define stlvectorinsert(T)      STL_VECTOR_CAT(stl_vectorinsert_, T)
#define stlvectorerase(T)       STL_VECTOR_CAT(stl_vectorerase_, T)
#define stlvectorclear(T)       STL_VECTOR_CAT(stl_vectorclear_, T)
#define stlvectorcopy(T)        STL_VECTOR_CAT(stl_vectorcopy_, T)
#define stlvectorclone(T)       STL_VECTOR_CAT(stl_vectorclone_, T)
#define stlvectormove(T)        STL_VECTOR_CAT(stl_vectormove_, T)
#define stlvectorswap(T)        STL_VECTOR_CAT(stl_vectorswap_, T)
#define stlvectorfind(T)        STL_VECTOR_CAT(stl_vectorfind_, T)
#define stlvectorcontains(T)    STL_VECTOR_CAT(stl_vectorcontains_, T)
#define stlvectorsize(T)        STL_VECTOR_CAT(stl_vectorsize_, T)
#define stlvectorcapacity(T)    STL_VECTOR_CAT(stl_vectorcapacity_, T)
#define stlvectorempty(T)       STL_VECTOR_CAT(stl_vectorempty_, T)

// MARK: inst
#define stlvectorinst(T) \
    struct stlvector(T) \
    { \
        T* data; \
        size_t size; \
        size_t capacity; \
    };

// MARK: decl
#define stlvectordecl(T, ATTR) \
    struct stlvector(T); \
    typedef struct stlvector(T) stlvector(T); \
    ATTR void stlvectorinit(T)(stlvector(T)* me, size_t cap); \
    ATTR void stlvectorfree(T)(stlvector(T)* me); \
    ATTR void stlvectorreserve(T)(stlvector(T)* me, size_t cap); \
    ATTR void stlvectorresize(T)(stlvector(T)* me, size_t n); \
    ATTR void stlvectorshrink(T)(stlvector(T)* me); \
    ATTR void stlvectorpush(T)(stlvector(T)* me, T e); \
    ATTR T stlvectorpop(T)(stlvector(T)* me); \
    ATTR T* stlvectordata(T)(stlvector(T)* me); \
    ATTR const T* stlvectordata_const(T)(const stlvector(T)* me); \
    ATTR T stlvectorget(T)(const stlvector(T)* me, size_t i); \
    ATTR void stlvectorset(T)(stlvector(T)* me, size_t i, T e); \
    ATTR T* stlvectorat(T)(stlvector(T)* me, size_t i); \
    ATTR const T* stlvectorat_const(T)(const stlvector(T)* me, size_t i); \
    ATTR T* stlvectorfront(T)(stlvector(T)* me); \
    ATTR const T* stlvectorfront_const(T)(const stlvector(T)* me); \
    ATTR T* stlvectorback(T)(stlvector(T)* me); \
    ATTR const T* stlvectorback_const(T)(const stlvector(T)* me); \
    ATTR void stlvectorinsert(T)(stlvector(T)* me, size_t i, T e); \
    ATTR void stlvectorerase(T)(stlvector(T)* me, size_t i); \
    ATTR void stlvectorclear(T)(stlvector(T)* me); \
    ATTR void stlvectorcopy(T)(stlvector(T)* dst, const stlvector(T)* src); \
    ATTR stlvector(T) stlvectorclone(T)(const stlvector(T)* me); \
    ATTR void stlvectormove(T)(stlvector(T)* dst, stlvector(T)* src); \
    ATTR void stlvectorswap(T)(stlvector(T)* a, stlvector(T)* b); \
    ATTR size_t stlvectorfind(T)(const stlvector(T)* me, T e); \
    ATTR int stlvectorcontains(T)(const stlvector(T)* me, T e); \
    ATTR size_t stlvectorsize(T)(const stlvector(T)* me); \
    ATTR size_t stlvectorcapacity(T)(const stlvector(T)* me); \
    ATTR int stlvectorempty(T)(const stlvector(T)* me);

// MARK: impl
#define stlvectorimpl(T, ATTR) \
    ATTR void stlvectorinit(T)(stlvector(T)* me, size_t cap) \
    { \
        me->data = NULL; \
        me->size = 0; \
        me->capacity = 0; \
        if (cap) stlvectorreserve(T)(me, cap); \
    } \
    ATTR void stlvectorfree(T)(stlvector(T)* me) \
    { \
        STL_VECTOR_FREE(me->data); \
        me->data = NULL; \
        me->size = 0; \
        me->capacity = 0; \
    } \
    ATTR void stlvectorreserve(T)(stlvector(T)* me, size_t cap) \
    { \
        if (cap <= me->capacity) return; \
        size_t nc = me->capacity ? me->capacity : cap; \
        while (nc < cap) \
        { \
            if (nc > (size_t)-1 / 2) \
            { \
                nc = cap; \
                break; \
            } \
            nc *= 2; \
        } \
        T* p = (T* )STL_VECTOR_REALLOC(me->data, nc * sizeof(T)); \
        if (!p) STL_VECTOR_ABORT(); \
        me->data = p; \
        me->capacity = nc; \
    } \
    ATTR void stlvectorresize(T)(stlvector(T)* me, size_t n) \
    { \
        if (n > me->capacity) \
            stlvectorreserve(T)(me, n); \
        if (n > me->size) \
            memset(me->data + me->size, 0, (n - me->size) * sizeof(T)); \
        me->size = n; \
    } \
    ATTR void stlvectorshrink(T)(stlvector(T)* me) \
    { \
        if (me->size == me->capacity) return; \
        if (me->size == 0) \
        { \
            STL_VECTOR_FREE(me->data); \
            me->data = NULL; \
            me->capacity = 0; \
        } \
        else \
        { \
            T* p = (T* )STL_VECTOR_REALLOC(me->data, me->size * sizeof(T)); \
            if (!p) STL_VECTOR_ABORT(); \
            me->data = p; \
            me->capacity = me->size; \
        } \
    } \
    ATTR void stlvectorpush(T)(stlvector(T)* me, T e) \
    { \
        if (me->size == me->capacity) \
            stlvectorreserve(T)(me, me->size + 1); \
        me->data[me->size++] = e; \
    } \
    ATTR T stlvectorpop(T)(stlvector(T)* me) \
    { \
        assert(me->size > 0); \
        return me->data[--me->size]; \
    } \
    ATTR T* stlvectordata(T)(stlvector(T)* me) \
    { \
        return me->data; \
    } \
    ATTR const T* stlvectordata_const(T)(const stlvector(T)* me) \
    { \
        return me->data; \
    } \
    ATTR T stlvectorget(T)(const stlvector(T)* me, size_t i) \
    { \
        assert(i < me->size); \
        return me->data[i]; \
    } \
    ATTR void stlvectorset(T)(stlvector(T)* me, size_t i, T e) \
    { \
        assert(i < me->size); \
        me->data[i] = e; \
    } \
    ATTR T* stlvectorat(T)(stlvector(T)* me, size_t i) \
    { \
        assert(i < me->size); \
        return &me->data[i]; \
    } \
    ATTR const T* stlvectorat_const(T)(const stlvector(T)* me, size_t i) \
    { \
        assert(i < me->size); \
        return &me->data[i]; \
    } \
    ATTR T* stlvectorfront(T)(stlvector(T)* me) \
    { \
        assert(me->size > 0); \
        return &me->data[0]; \
    } \
    ATTR const T* stlvectorfront_const(T)(const stlvector(T)* me) \
    { \
        assert(me->size > 0); \
        return &me->data[0]; \
    } \
    ATTR T* stlvectorback(T)(stlvector(T)* me) \
    { \
        assert(me->size > 0); \
        return &me->data[me->size - 1]; \
    } \
    ATTR const T* stlvectorback_const(T)(const stlvector(T)* me) \
    { \
        assert(me->size > 0); \
        return &me->data[me->size - 1]; \
    } \
    ATTR void stlvectorinsert(T)(stlvector(T)* me, size_t i, T e) \
    { \
        assert(i <= me->size); \
        if (me->size == me->capacity) \
            stlvectorreserve(T)(me, me->size + 1); \
        memmove(&me->data[i + 1], &me->data[i], (me->size - i) * sizeof(T)); \
        me->data[i] = e; \
        me->size++; \
    } \
    ATTR void stlvectorerase(T)(stlvector(T)* me, size_t i) \
    { \
        assert(i < me->size); \
        memmove(&me->data[i], &me->data[i + 1], (me->size - i - 1) * sizeof(T)); \
        me->size--; \
    } \
    ATTR void stlvectorclear(T)(stlvector(T)* me) \
    { \
        me->size = 0; \
    } \
    ATTR void stlvectorcopy(T)(stlvector(T)* dst, const stlvector(T)* src) \
    { \
        if (dst == src) return; \
        stlvectorclear(T)(dst); \
        if (src->size > dst->capacity) \
            stlvectorreserve(T)(dst, src->size); \
        if (src->size) \
            memcpy(dst->data, src->data, src->size * sizeof(T)); \
        dst->size = src->size; \
    } \
    ATTR stlvector(T) stlvectorclone(T)(const stlvector(T)* me) \
    { \
        stlvector(T) r; \
        stlvectorinit(T)(&r, me->size); \
        if (me->size) \
        { \
            memcpy(r.data, me->data, me->size * sizeof(T)); \
            r.size = me->size; \
        } \
        return r; \
    } \
    ATTR void stlvectormove(T)(stlvector(T)* dst, stlvector(T)* src) \
    { \
        if (dst == src) return; \
        STL_VECTOR_FREE(dst->data); \
        dst->data = src->data; \
        dst->size = src->size; \
        dst->capacity = src->capacity; \
        src->data = NULL; \
        src->size = 0; \
        src->capacity = 0; \
    } \
    ATTR void stlvectorswap(T)(stlvector(T)* a, stlvector(T)* b) \
    { \
        stlvector(T) tmp = *a; \
        *a = *b; \
        *b = tmp; \
    } \
    ATTR size_t stlvectorfind(T)(const stlvector(T)* me, T e) \
    { \
        for (size_t i = 0; i < me->size; ++i) \
            if ((memcmp(&(me->data[i]), &(e), sizeof(me->data[i])) == 0)) \
                return i; \
        return (size_t)-1; \
    } \
    ATTR int stlvectorcontains(T)(const stlvector(T)* me, T e) \
    { \
        return stlvectorfind(T)(me, e) != (size_t)-1; \
    } \
    ATTR size_t stlvectorsize(T)(const stlvector(T)* me) \
    { \
        return me->size; \
    } \
    ATTR size_t stlvectorcapacity(T)(const stlvector(T)* me) \
    { \
        return me->capacity; \
    } \
    ATTR int stlvectorempty(T)(const stlvector(T)* me) \
    { \
        return me->size == 0; \
    }

// MARK: sugar
#define stlvectorforeach(T, ME, IT) \
    for (T* IT = (ME)->data; IT != (ME)->data + (ME)->size; ++IT)
#define stlvectorforeach_const(T, ME, IT) \
    for (const T* IT = (ME)->data; IT != (ME)->data + (ME)->size; ++IT)
#define stlvectorrforeach(T, ME, IT) \
    for (T* IT = (ME)->data + (ME)->size; IT-- != (ME)->data; )
#define stlvectorrforeach_const(T, ME, IT) \
    for (const T* IT = (ME)->data + (ME)->size; IT-- != (ME)->data; )

#endif
