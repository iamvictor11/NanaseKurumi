// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__XKTRANSFORM_TYPE_H
#define XK_INTERNAL__XKTRANSFORM_TYPE_H

#include "_xktransform_common.h"

// MARK: name
#define xkvec(N, T) \
    XK_PRIVATE_TRANSFORM_NAME(xkvec, N, T)
#define xkvec2(T) xkvec(2, T)
#define xkvec3(T) xkvec(3, T)
#define xkvec4(T) xkvec(4, T)
#define xkmat(R, C, T) \
    XK_PRIVATE_TRANSFORM_NAME(xkmat, XK_PRIVATE_TRANSFORM_RC(R, C), T)
#define xkmat2x2(T) xkmat(2, 2, T)
#define xkmat2x3(T) xkmat(2, 3, T)
#define xkmat2x4(T) xkmat(2, 4, T)
#define xkmat3x2(T) xkmat(3, 2, T)
#define xkmat3x3(T) xkmat(3, 3, T)
#define xkmat3x4(T) xkmat(3, 4, T)
#define xkmat4x2(T) xkmat(4, 2, T)
#define xkmat4x3(T) xkmat(4, 3, T)
#define xkmat4x4(T) xkmat(4, 4, T)
#define xkmat2(T) xkmat(2, 2, T)
#define xkmat3(T) xkmat(3, 3, T)
#define xkmat4(T) xkmat(4, 4, T)
#define xkquat(T) XK_CAT(xkquat_, T)

// MARK: type
#define XK_PRIVATE_TRANSFORM_TYPE_DECL(T) \
    typedef union xkvec(2, T) \
    { \
        T arr[2]; \
        struct \
        { \
            union { T x, r, s; }; \
            union { T y, g, t; }; \
        }; \
    } xkvec(2, T); \
    typedef union xkvec(3, T) \
    { \
        T arr[3]; \
        struct \
        { \
            union { T x, r, s; }; \
            union { T y, g, t; }; \
            union { T z, b, p; }; \
        }; \
    } xkvec(3, T); \
    typedef union xkvec(4, T) \
    { \
        T arr[4]; \
        struct \
        { \
            union { T x, r, s; }; \
            union { T y, g, t; }; \
            union { T z, b, p; }; \
            union { T w, a, q; }; \
        }; \
    } xkvec(4, T); \
    typedef struct xkmat(2, 2, T) \
    { \
        T arr[2][2]; \
    } xkmat(2, 2, T); \
    typedef struct xkmat(2, 3, T) \
    { \
        T arr[2][3]; \
    } xkmat(2, 3, T); \
    typedef struct xkmat(2, 4, T) \
    { \
        T arr[2][4]; \
    } xkmat(2, 4, T); \
    typedef struct xkmat(3, 2, T) \
    { \
        T arr[3][2]; \
    } xkmat(3, 2, T); \
    typedef struct xkmat(3, 3, T) \
    { \
        T arr[3][3]; \
    } xkmat(3, 3, T); \
    typedef struct xkmat(3, 4, T) \
    { \
        T arr[3][4]; \
    } xkmat(3, 4, T); \
    typedef struct xkmat(4, 2, T) \
    { \
        T arr[4][2]; \
    } xkmat(4, 2, T); \
    typedef struct xkmat(4, 3, T) \
    { \
        T arr[4][3]; \
    } xkmat(4, 3, T); \
    typedef struct xkmat(4, 4, T) \
    { \
        T arr[4][4]; \
    } xkmat(4, 4, T);

#define XK_PRIVATE_TRANSFORM_QUAT_TYPE_DECL(T) \
    typedef union xkquat(T) \
    { \
        T arr[4]; \
        struct \
        { \
            union { T x, r; }; \
            union { T y, g; }; \
            union { T z, b; }; \
            union { T w, a; }; \
        }; \
    } xkquat(T);

XK_PRIVATE_TRANSFORM_TYPE_DECL(float)
XK_PRIVATE_TRANSFORM_TYPE_DECL(double)

XK_PRIVATE_TRANSFORM_QUAT_TYPE_DECL(float)
XK_PRIVATE_TRANSFORM_QUAT_TYPE_DECL(double)

#endif
