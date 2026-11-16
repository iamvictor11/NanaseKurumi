// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__TRANSFORM__XKTRANSFORM_AFFINE_H
#define XK_INTERNAL__TRANSFORM__XKTRANSFORM_AFFINE_H

#include "_xktransform_common.h"
#include "_xktransform_type.h"
#include "_xktransform_vec.h"
#include "_xktransform_mat.h"
#include "_xktransform_quat.h"

// MARK: name
#define xkmat4x4translation(T)      XK_CAT(xk_PUBLIC_mat4x4_translation_, T)
#define xkmat4x4scaling(T)          XK_CAT(xk_PUBLIC_mat4x4_scaling_, T)
#define xkmat4x4rotationx(T)        XK_CAT(xk_PUBLIC_mat4x4_rotationx_, T)
#define xkmat4x4rotationy(T)        XK_CAT(xk_PUBLIC_mat4x4_rotationy_, T)
#define xkmat4x4rotationz(T)        XK_CAT(xk_PUBLIC_mat4x4_rotationz_, T)
#define xkmat4x4rotationaxis(T)     XK_CAT(xk_PUBLIC_mat4x4_rotationaxis_, T)
#define xkmat4x4orientation(T)      XK_CAT(xk_PUBLIC_mat4x4_orientation_, T)
#define xkmat4x4yawpitchroll(T)     XK_CAT(xk_PUBLIC_mat4x4_yawpitchroll_, T)
#define xkmat4x4shearing(T)         XK_CAT(xk_PUBLIC_mat4x4_shearing_, T)
#define xkmat4x4transformvector(T)  XK_CAT(xk_PUBLIC_mat4x4_transformvector_, T)
#define xkmat4x4transformpoint(T)   XK_CAT(xk_PUBLIC_mat4x4_transformpoint_, T)
#define xkmat4x4translate(T)        XK_CAT(xk_PUBLIC_mat4x4_translate_, T)
#define xkmat4x4rotate(T)           XK_CAT(xk_PUBLIC_mat4x4_rotate_, T)
#define xkmat4x4orient(T)           XK_CAT(xk_PUBLIC_mat4x4_orient_, T)
#define xkmat4x4scale(T)            XK_CAT(xk_PUBLIC_mat4x4_scale_, T)
#define xkmat4x4shear(T)            XK_CAT(xk_PUBLIC_mat4x4_shear_, T)
#define xkmat4x4decompose(T)        XK_CAT(xk_PUBLIC_mat4x4_decompose_, T)

// MARK: impl
#define XK_PRIVATE_TRANSFORM_MAT4_AFFINE_IMPL(T, ATTR, SIN, COS, EPS) \
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
    ATTR xkmat(4, 4, T) xkmat4x4orientation(T)(xkquat(T) q) \
    { \
        return xkquattomat4(T)(q); \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4yawpitchroll(T)(T yaw, T pitch, T roll) \
    { \
        xkquat(T) q = xkquatfromyawpitchroll(T)(yaw, pitch, roll); \
        return xkquattomat4(T)(q); \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4shearing(T)(xkvec(3, T) s) \
    { \
        xkmat(4, 4, T) r = xkmat4x4identity(T)(); \
        r.arr[1][0] = s.x; \
        r.arr[2][0] = s.y; \
        r.arr[2][1] = s.z; \
        return r; \
    } \
    ATTR xkvec(3, T) xkmat4x4transformvector(T)(const xkmat(4, 4, T)* me, xkvec(3, T) v) \
    { \
        xkvec(3, T) r; \
        int j; \
        for (j = 0; j < 3; ++j) \
            r.arr[j] = v.x * me->arr[0][j] + v.y * me->arr[1][j] + v.z * me->arr[2][j]; \
        return r; \
    } \
    ATTR xkvec(3, T) xkmat4x4transformpoint(T)(const xkmat(4, 4, T)* me, xkvec(3, T) v) \
    { \
        xkvec(3, T) r; \
        int j; \
        for (j = 0; j < 3; ++j) \
        { \
            r.arr[j] = v.x * me->arr[0][j] + v.y * me->arr[1][j] \
                + v.z * me->arr[2][j] + me->arr[3][j]; \
        } \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4translate(T)(const xkmat(4, 4, T)* me, xkvec(3, T) t) \
    { \
        xkmat(4, 4, T) x = xkmat4x4translation(T)(t); \
        return xkmat4x4mul4x4(T)(&x, me); \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4rotate(T)(const xkmat(4, 4, T)* me, xkvec(3, T) axis, T angle) \
    { \
        xkmat(4, 4, T) x = xkmat4x4rotationaxis(T)(axis, angle); \
        return xkmat4x4mul4x4(T)(&x, me); \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4orient(T)(const xkmat(4, 4, T)* me, xkquat(T) q) \
    { \
        xkmat(4, 4, T) x = xkmat4x4orientation(T)(q); \
        return xkmat4x4mul4x4(T)(&x, me); \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4scale(T)(const xkmat(4, 4, T)* me, xkvec(3, T) s) \
    { \
        xkmat(4, 4, T) x = xkmat4x4scaling(T)(s); \
        return xkmat4x4mul4x4(T)(&x, me); \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4shear(T)(const xkmat(4, 4, T)* me, xkvec(3, T) s) \
    { \
        xkmat(4, 4, T) x = xkmat4x4shearing(T)(s); \
        return xkmat4x4mul4x4(T)(&x, me); \
    } \
    ATTR bool xkmat4x4decompose(T)(const xkmat(4, 4, T)* me, xkvec(3, T)* translation, xkquat(T)* orientation, xkvec(3, T)* scale, xkvec(3, T)* skew, xkvec(4, T)* perspective) \
    { \
        if (translation == NULL || orientation == NULL || scale == NULL || skew == NULL || perspective == NULL) \
            return false; \
        if (me->arr[3][3] < (T)EPS && me->arr[3][3] > -(T)EPS) \
            return false; \
        xkmat(3, 3, T) a; \
        xkmat(3, 3, T) ai; \
        xkvec(3, T) r0; \
        xkvec(3, T) r1; \
        xkvec(3, T) r2; \
        xkvec(3, T) tmp; \
        xkvec(3, T) tr; \
        xkvec(3, T) rhs; \
        xkvec(3, T) pv; \
        T invw; \
        T sx; \
        T sy; \
        T sz; \
        T sxy; \
        T sxz; \
        T syz; \
        T invs; \
        T eps2; \
        T pw; \
        int i, j; \
        invw = (T)1 / me->arr[3][3]; \
        eps2 = (T)EPS * (T)EPS; \
        for (i = 0; i < 3; ++i) \
            for (j = 0; j < 3; ++j) \
                a.arr[i][j] = me->arr[i][j] * invw; \
        r0 = xkvec3make(T)(a.arr[0][0], a.arr[0][1], a.arr[0][2]); \
        r1 = xkvec3make(T)(a.arr[1][0], a.arr[1][1], a.arr[1][2]); \
        r2 = xkvec3make(T)(a.arr[2][0], a.arr[2][1], a.arr[2][2]); \
        tr = xkvec3make(T)(me->arr[3][0], me->arr[3][1], me->arr[3][2]); \
        tr = xkvec3scale(T)(tr, invw); \
        rhs = xkvec3make(T)(me->arr[0][3], me->arr[1][3], me->arr[2][3]); \
        rhs = xkvec3scale(T)(rhs, invw); \
        sx = xkvec3length(T)(r0); \
        if (sx <= (T)EPS) \
            return false; \
        invs = (T)1 / sx; \
        r0 = xkvec3scale(T)(r0, invs); \
        sxy = xkvec3dot(T)(r0, r1); \
        tmp = xkvec3scale(T)(r0, sxy); \
        r1 = xkvec3sub(T)(r1, tmp); \
        sy = xkvec3length(T)(r1); \
        if (sy <= (T)EPS) \
            return false; \
        invs = (T)1 / sy; \
        r1 = xkvec3scale(T)(r1, invs); \
        sxy = sxy * invs; \
        sxz = xkvec3dot(T)(r0, r2); \
        tmp = xkvec3scale(T)(r0, sxz); \
        r2 = xkvec3sub(T)(r2, tmp); \
        syz = xkvec3dot(T)(r1, r2); \
        tmp = xkvec3scale(T)(r1, syz); \
        r2 = xkvec3sub(T)(r2, tmp); \
        sz = xkvec3length(T)(r2); \
        if (sz <= (T)EPS) \
            return false; \
        invs = (T)1 / sz; \
        r2 = xkvec3scale(T)(r2, invs); \
        sxz = sxz * invs; \
        syz = syz * invs; \
        tmp = xkvec3cross(T)(r1, r2); \
        if (xkvec3dot(T)(r0, tmp) < (T)0) \
        { \
            sx = -sx; \
            sy = -sy; \
            sz = -sz; \
            r0 = xkvec3negate(T)(r0); \
            r1 = xkvec3negate(T)(r1); \
            r2 = xkvec3negate(T)(r2); \
        } \
        if (xkvec3lengthsq(T)(rhs) > eps2) \
        { \
            ai = xkmat3x3inverse(T)(&a); \
            pv = xkmat3x3vecmul(T)(&ai, rhs); \
            pw = (T)1 - xkvec3dot(T)(tr, pv); \
            *perspective = xkvec4make(T)(pv.x, pv.y, pv.z, pw); \
        } \
        else \
        { \
            *perspective = xkvec4make(T)((T)0, (T)0, (T)0, (T)1); \
        } \
        a.arr[0][0] = r0.x; \
        a.arr[0][1] = r0.y; \
        a.arr[0][2] = r0.z; \
        a.arr[1][0] = r1.x; \
        a.arr[1][1] = r1.y; \
        a.arr[1][2] = r1.z; \
        a.arr[2][0] = r2.x; \
        a.arr[2][1] = r2.y; \
        a.arr[2][2] = r2.z; \
        *translation = tr; \
        *scale = xkvec3make(T)(sx, sy, sz); \
        *skew = xkvec3make(T)(sxy, sxz, syz); \
        *orientation = xkquatfrommat3(T)(&a); \
        return true; \
    }

// MARK: instantiate
XK_PRIVATE_TRANSFORM_MAT4_AFFINE_IMPL(float, static inline, sinf, cosf, 1e-6f)
XK_PRIVATE_TRANSFORM_MAT4_AFFINE_IMPL(double, static inline, sin, cos, 1e-12)

#endif
