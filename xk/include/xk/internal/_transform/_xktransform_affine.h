// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__XKTRANSFORM_AFFINE_H
#define XK_INTERNAL__XKTRANSFORM_AFFINE_H

#include "_xktransform_common.h"
#include "_xktransform_type.h"
#include "_xktransform_vec.h"
#include "_xktransform_mat.h"
#include "_xktransform_quat.h"

// MARK: name
#define xkmat4x4translation(T)          XK_CAT(xk_PUBLIC_mat4x4_translation_, T)
#define xkmat4x4scaling(T)              XK_CAT(xk_PUBLIC_mat4x4_scaling_, T)
#define xkmat4x4rotationx(T)            XK_CAT(xk_PUBLIC_mat4x4_rotationx_, T)
#define xkmat4x4rotationy(T)            XK_CAT(xk_PUBLIC_mat4x4_rotationy_, T)
#define xkmat4x4rotationz(T)            XK_CAT(xk_PUBLIC_mat4x4_rotationz_, T)
#define xkmat4x4rotationaxis(T)         XK_CAT(xk_PUBLIC_mat4x4_rotationaxis_, T)
#define xkmat4x4rotationquat(T)         XK_CAT(xk_PUBLIC_mat4x4_rotationquat_, T)
#define xkmat4x4rotationyawpitchroll(T) XK_CAT(xk_PUBLIC_mat4x4_rotationyawpitchroll_, T)
#define xkmat4x4transformvector(T)      XK_CAT(xk_PUBLIC_mat4x4_transformvector_, T)
#define xkmat4x4transformpoint(T)       XK_CAT(xk_PUBLIC_mat4x4_transformpoint_, T)

// MARK: impl
#define XK_PRIVATE_TRANSFORM_MAT4_AFFINE_IMPL(T, ATTR, SIN, COS) \
    ATTR xkmat(4, 4, T) xkmat4x4translation(T)(xkvec(3, T) t) \
    { \
        xkmat(4, 4, T) r = xkmat4x4identity(T)(); \
        r.arr[3][0] = t.x; \
        r.arr[3][1] = t.y; \
        r.arr[3][2] = t.z; \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4scaling(T)(xkvec(3, T) s) \
    { \
        xkmat(4, 4, T) r = xkmat4x4identity(T)(); \
        r.arr[0][0] = s.x; \
        r.arr[1][1] = s.y; \
        r.arr[2][2] = s.z; \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4rotationx(T)(T angle) \
    { \
        xkmat(4, 4, T) r = xkmat4x4identity(T)(); \
        T s = (T)SIN(angle); \
        T c = (T)COS(angle); \
        r.arr[1][1] = c; \
        r.arr[1][2] = s; \
        r.arr[2][1] = -s; \
        r.arr[2][2] = c; \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4rotationy(T)(T angle) \
    { \
        xkmat(4, 4, T) r = xkmat4x4identity(T)(); \
        T s = (T)SIN(angle); \
        T c = (T)COS(angle); \
        r.arr[0][0] = c; \
        r.arr[0][2] = -s; \
        r.arr[2][0] = s; \
        r.arr[2][2] = c; \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4rotationz(T)(T angle) \
    { \
        xkmat(4, 4, T) r = xkmat4x4identity(T)(); \
        T s = (T)SIN(angle); \
        T c = (T)COS(angle); \
        r.arr[0][0] = c; \
        r.arr[0][1] = s; \
        r.arr[1][0] = -s; \
        r.arr[1][1] = c; \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4rotationaxis(T)(xkvec(3, T) axis, T angle) \
    { \
        xkvec(3, T) n = xkvec3normalize(T)(axis); \
        xkmat(4, 4, T) r = xkmat4x4identity(T)(); \
        T s = (T)SIN(angle); \
        T c = (T)COS(angle); \
        T k = (T)1 - c; \
        r.arr[0][0] = c + k * n.x * n.x; \
        r.arr[1][1] = c + k * n.y * n.y; \
        r.arr[2][2] = c + k * n.z * n.z; \
        r.arr[0][1] = k * n.x * n.y + s * n.z; \
        r.arr[0][2] = k * n.x * n.z - s * n.y; \
        r.arr[1][0] = k * n.x * n.y - s * n.z; \
        r.arr[1][2] = k * n.y * n.z + s * n.x; \
        r.arr[2][0] = k * n.x * n.z + s * n.y; \
        r.arr[2][1] = k * n.y * n.z - s * n.x; \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4rotationquat(T)(xkquat(T) q) \
    { \
        return xkquattomat4(T)(q); \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4rotationyawpitchroll(T)(T yaw, T pitch, T roll) \
    { \
        xkquat(T) q = xkquatfromyawpitchroll(T)(yaw, pitch, roll); \
        return xkquattomat4(T)(q); \
    } \
    ATTR xkvec(3, T) xkmat4x4transformvector(T) \
    ( \
        const xkmat(4, 4, T)* me, \
        xkvec(3, T) v \
    ) \
    { \
        xkvec(3, T) r; \
        int j; \
        for (j = 0; j < 3; ++j) \
            r.arr[j] = v.x * me->arr[0][j] + v.y * me->arr[1][j] + v.z * me->arr[2][j]; \
        return r; \
    } \
    ATTR xkvec(3, T) xkmat4x4transformpoint(T) \
    ( \
        const xkmat(4, 4, T)* me, \
        xkvec(3, T) v \
    ) \
    { \
        xkvec(3, T) r; \
        int j; \
        for (j = 0; j < 3; ++j) \
        { \
            r.arr[j] = v.x * me->arr[0][j] + v.y * me->arr[1][j] \
                + v.z * me->arr[2][j] + me->arr[3][j]; \
        } \
        return r; \
    }

// MARK: instantiate
#define XK_PRIVATE_TRANSFORM_INSTALL_MAT4_AFFINE(T, ATTR, SIN, COS) \
    XK_PRIVATE_TRANSFORM_MAT4_AFFINE_IMPL(T, ATTR, SIN, COS)

XK_PRIVATE_TRANSFORM_INSTALL_MAT4_AFFINE(float, static inline, sinf, cosf)
XK_PRIVATE_TRANSFORM_INSTALL_MAT4_AFFINE(double, static inline, sin, cos)

#endif
