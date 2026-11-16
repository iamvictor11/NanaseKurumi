// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__XKTRANSFORM_H
#define XK_INTERNAL__XKTRANSFORM_H

#include <stdint.h>

#ifndef XK_CAT
#define XK_CAT_(a, b)   a##b
#define XK_CAT(a, b)    XK_CAT_(a, b)
#endif

#define XK_PRIVATE_TRANSFORM_NAME(A, B, C) \
    XK_CAT(XK_CAT(A, B), XK_CAT(_, C))

#define xkvec2(T)   XK_CAT(xkvec2_, T)
#define xkvec3(T)   XK_CAT(xkvec3_, T)
#define xkvec4(T)   XK_CAT(xkvec4_, T)
#define xkquat(T)   XK_CAT(xkquat_, T)
#define xkmat2x2(T) XK_CAT(xkmat2x2_, T)
#define xkmat2x3(T) XK_CAT(xkmat2x3_, T)
#define xkmat2x4(T) XK_CAT(xkmat2x4_, T)
#define xkmat2(T)   XK_CAT(xkmat2_, T)
#define xkmat3x2(T) XK_CAT(xkmat3x2_, T)
#define xkmat3x3(T) XK_CAT(xkmat3x3_, T)
#define xkmat3x4(T) XK_CAT(xkmat3x4_, T)
#define xkmat3(T)   XK_CAT(xkmat3_, T)
#define xkmat4x2(T) XK_CAT(xkmat4x2_, T)
#define xkmat4x3(T) XK_CAT(xkmat4x3_, T)
#define xkmat4x4(T) XK_CAT(xkmat4x4_, T)
#define xkmat4(T)   XK_CAT(xkmat4_, T)

#define XK_PRIVATE_TRANSFORM_TYPE_DECL(T) \
    typedef union xkvec2(T) \
    { \
        T arr[2]; \
        struct \
        { \
            union { T x, r, s; }; \
            union { T y, g, t; }; \
        }; \
    } xkvec2(T); \
    typedef union xkvec3(T) \
    { \
        T arr[3]; \
        struct \
        { \
            union { T x, r, s; }; \
            union { T y, g, t; }; \
            union { T z, b, p; }; \
        }; \
    } xkvec3(T); \
    typedef union xkvec4(T) \
    { \
        T arr[4]; \
        struct \
        { \
            union { T x, r, s; }; \
            union { T y, g, t; }; \
            union { T z, b, p; }; \
            union { T w, a, q; }; \
        }; \
    } xkvec4(T); \
    typedef struct xkmat2x2(T) \
    { \
        T arr[2][2]; \
    } xkmat2x2(T), xkmat2(T); \
    typedef struct xkmat2x3(T) \
    { \
        T arr[2][3]; \
    } xkmat2x3(T); \
    typedef struct xkmat2x4(T) \
    { \
        T arr[2][4]; \
    } xkmat2x4(T); \
    typedef struct xkmat3x2(T) \
    { \
        T arr[3][2]; \
    } xkmat3x2(T); \
    typedef struct xkmat3x3(T) \
    { \
        T arr[3][3]; \
    } xkmat3x3(T), xkmat3(T); \
    typedef struct xkmat3x4(T) \
    { \
        T arr[3][4]; \
    } xkmat3x4(T); \
    typedef struct xkmat4x2(T) \
    { \
        T arr[4][2]; \
    } xkmat4x2(T); \
    typedef struct xkmat4x3(T) \
    { \
        T arr[4][3]; \
    } xkmat4x3(T); \
    typedef struct xkmat4x4(T) \
    { \
        T arr[4][4]; \
    } xkmat4x4(T), xkmat4(T);
XK_PRIVATE_TRANSFORM_TYPE_DECL(int8_t)
XK_PRIVATE_TRANSFORM_TYPE_DECL(int16_t)
XK_PRIVATE_TRANSFORM_TYPE_DECL(int32_t)
XK_PRIVATE_TRANSFORM_TYPE_DECL(int64_t)
XK_PRIVATE_TRANSFORM_TYPE_DECL(uint8_t)
XK_PRIVATE_TRANSFORM_TYPE_DECL(uint16_t)
XK_PRIVATE_TRANSFORM_TYPE_DECL(uint32_t)
XK_PRIVATE_TRANSFORM_TYPE_DECL(uint64_t)
XK_PRIVATE_TRANSFORM_TYPE_DECL(float)
XK_PRIVATE_TRANSFORM_TYPE_DECL(double)

#endif
