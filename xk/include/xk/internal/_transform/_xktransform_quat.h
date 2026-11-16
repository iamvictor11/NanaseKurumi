// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__XKTRANSFORM_QUAT_H
#define XK_INTERNAL__XKTRANSFORM_QUAT_H

#include "_xktransform_common.h"
#include "_xktransform_type.h"
#include "_xktransform_vec.h"
#include "_xktransform_mat.h"

// MARK: name
#define xkquatmake(T)             XK_CAT(xk_PUBLIC_quat_make_, T)
#define xkquatzero(T)             XK_CAT(xk_PUBLIC_quat_zero_, T)
#define xkquatidentity(T)         XK_CAT(xk_PUBLIC_quat_identity_, T)
#define xkquatadd(T)              XK_CAT(xk_PUBLIC_quat_add_, T)
#define xkquatsub(T)              XK_CAT(xk_PUBLIC_quat_sub_, T)
#define xkquatmul(T)              XK_CAT(xk_PUBLIC_quat_mul_, T)
#define xkquatscale(T)            XK_CAT(xk_PUBLIC_quat_scale_, T)
#define xkquatnegate(T)           XK_CAT(xk_PUBLIC_quat_negate_, T)
#define xkquatdot(T)              XK_CAT(xk_PUBLIC_quat_dot_, T)
#define xkquatlengthsq(T)         XK_CAT(xk_PUBLIC_quat_lengthsq_, T)
#define xkquatlength(T)           XK_CAT(xk_PUBLIC_quat_length_, T)
#define xkquatnormalize(T)        XK_CAT(xk_PUBLIC_quat_normalize_, T)
#define xkquatconjugate(T)        XK_CAT(xk_PUBLIC_quat_conjugate_, T)
#define xkquatinverse(T)          XK_CAT(xk_PUBLIC_quat_inverse_, T)
#define xkquatrotate(T)           XK_CAT(xk_PUBLIC_quat_rotate_, T)
#define xkquatfromaxisangle(T)    XK_CAT(xk_PUBLIC_quat_fromaxisangle_, T)
#define xkquatfromyawpitchroll(T) XK_CAT(xk_PUBLIC_quat_fromyawpitchroll_, T)
#define xkquattomat3(T)           XK_CAT(xk_PUBLIC_quat_tomat3_, T)
#define xkquattomat4(T)           XK_CAT(xk_PUBLIC_quat_tomat4_, T)
#define xkquatfrommat3(T)         XK_CAT(xk_PUBLIC_quat_frommat3_, T)
#define xkquatfrommat4(T)         XK_CAT(xk_PUBLIC_quat_frommat4_, T)
#define xkquatlerp(T)             XK_CAT(xk_PUBLIC_quat_lerp_, T)
#define xkquatslerp(T)            XK_CAT(xk_PUBLIC_quat_slerp_, T)
#define xkquatequals(T)           XK_CAT(xk_PUBLIC_quat_equals_, T)

// MARK: impl
#define XK_PRIVATE_TRANSFORM_QUAT_IMPL(T, ATTR, SQRT, SIN, COS, ACOS, EPS) \
    ATTR xkquat(T) xkquatmake(T)(T x, T y, T z, T w) \
    { \
        xkquat(T) r; \
        r.x = x; \
        r.y = y; \
        r.z = z; \
        r.w = w; \
        return r; \
    } \
    ATTR xkquat(T) xkquatzero(T)(void) \
    { \
        return xkquatmake(T)((T)0, (T)0, (T)0, (T)0); \
    } \
    ATTR xkquat(T) xkquatidentity(T)(void) \
    { \
        return xkquatmake(T)((T)0, (T)0, (T)0, (T)1); \
    } \
    ATTR xkquat(T) xkquatadd(T)(xkquat(T) a, xkquat(T) b) \
    { \
        xkquat(T) r; \
        r.x = a.x + b.x; \
        r.y = a.y + b.y; \
        r.z = a.z + b.z; \
        r.w = a.w + b.w; \
        return r; \
    } \
    ATTR xkquat(T) xkquatsub(T)(xkquat(T) a, xkquat(T) b) \
    { \
        xkquat(T) r; \
        r.x = a.x - b.x; \
        r.y = a.y - b.y; \
        r.z = a.z - b.z; \
        r.w = a.w - b.w; \
        return r; \
    } \
    ATTR xkquat(T) xkquatmul(T)(xkquat(T) a, xkquat(T) b) \
    { \
        xkquat(T) r; \
        r.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y; \
        r.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x; \
        r.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w; \
        r.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z; \
        return r; \
    } \
    ATTR xkquat(T) xkquatscale(T)(xkquat(T) me, T s) \
    { \
        xkquat(T) r; \
        r.x = me.x * s; \
        r.y = me.y * s; \
        r.z = me.z * s; \
        r.w = me.w * s; \
        return r; \
    } \
    ATTR xkquat(T) xkquatnegate(T)(xkquat(T) me) \
    { \
        xkquat(T) r; \
        r.x = -me.x; \
        r.y = -me.y; \
        r.z = -me.z; \
        r.w = -me.w; \
        return r; \
    } \
    ATTR T xkquatdot(T)(xkquat(T) a, xkquat(T) b) \
    { \
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; \
    } \
    ATTR T xkquatlengthsq(T)(xkquat(T) me) \
    { \
        return xkquatdot(T)(me, me); \
    } \
    ATTR T xkquatlength(T)(xkquat(T) me) \
    { \
        return (T)SQRT(xkquatlengthsq(T)(me)); \
    } \
    ATTR xkquat(T) xkquatnormalize(T)(xkquat(T) me) \
    { \
        T lensq = xkquatlengthsq(T)(me); \
        T len; \
        T inv; \
        if (lensq <= (T)EPS) \
            return xkquatidentity(T)(); \
        len = (T)SQRT(lensq); \
        inv = (T)1 / len; \
        return xkquatscale(T)(me, inv); \
    } \
    ATTR xkquat(T) xkquatconjugate(T)(xkquat(T) me) \
    { \
        xkquat(T) r; \
        r.x = -me.x; \
        r.y = -me.y; \
        r.z = -me.z; \
        r.w = me.w; \
        return r; \
    } \
    ATTR xkquat(T) xkquatinverse(T)(xkquat(T) me) \
    { \
        T lensq = xkquatlengthsq(T)(me); \
        T inv; \
        xkquat(T) c; \
        if (lensq <= (T)EPS) \
            return xkquatidentity(T)(); \
        inv = (T)1 / lensq; \
        c = xkquatconjugate(T)(me); \
        return xkquatscale(T)(c, inv); \
    } \
    ATTR xkvec(3, T) xkquatrotate(T)(xkquat(T) q, xkvec(3, T) v) \
    { \
        xkvec(3, T) t; \
        xkvec(3, T) r; \
        t.x = (T)2 * (q.y * v.z - q.z * v.y); \
        t.y = (T)2 * (q.z * v.x - q.x * v.z); \
        t.z = (T)2 * (q.x * v.y - q.y * v.x); \
        r.x = v.x + q.w * t.x + (q.y * t.z - q.z * t.y); \
        r.y = v.y + q.w * t.y + (q.z * t.x - q.x * t.z); \
        r.z = v.z + q.w * t.z + (q.x * t.y - q.y * t.x); \
        return r; \
    } \
    ATTR xkquat(T) xkquatfromaxisangle(T)(xkvec(3, T) axis, T angle) \
    { \
        xkvec(3, T) n = xkvec3normalize(T)(axis); \
        T half = angle * (T)0.5; \
        T s = (T)SIN(half); \
        T c = (T)COS(half); \
        return xkquatmake(T)(n.x * s, n.y * s, n.z * s, c); \
    } \
    ATTR xkquat(T) xkquatfromyawpitchroll(T)(T yaw, T pitch, T roll) \
    { \
        xkquat(T) qy; \
        xkquat(T) qp; \
        xkquat(T) qr; \
        xkquat(T) qyp; \
        T hy = yaw * (T)0.5; \
        T hp = pitch * (T)0.5; \
        T hr = roll * (T)0.5; \
        T sy = (T)SIN(hy); \
        T cy = (T)COS(hy); \
        T sp = (T)SIN(hp); \
        T cp = (T)COS(hp); \
        T sr = (T)SIN(hr); \
        T cr = (T)COS(hr); \
        qy = xkquatmake(T)((T)0, sy, (T)0, cy); \
        qp = xkquatmake(T)(sp, (T)0, (T)0, cp); \
        qr = xkquatmake(T)((T)0, (T)0, sr, cr); \
        qyp = xkquatmul(T)(qy, qp); \
        return xkquatmul(T)(qyp, qr); \
    } \
    ATTR xkmat(3, 3, T) xkquattomat3(T)(xkquat(T) me) \
    { \
        xkmat(3, 3, T) r; \
        T x = me.x; \
        T y = me.y; \
        T z = me.z; \
        T w = me.w; \
        T xx = x * x; \
        T yy = y * y; \
        T zz = z * z; \
        T xy = x * y; \
        T xz = x * z; \
        T yz = y * z; \
        T wx = w * x; \
        T wy = w * y; \
        T wz = w * z; \
        r.arr[0][0] = (T)1 - (T)2 * (yy + zz); \
        r.arr[0][1] = (T)2 * (xy + wz); \
        r.arr[0][2] = (T)2 * (xz - wy); \
        r.arr[1][0] = (T)2 * (xy - wz); \
        r.arr[1][1] = (T)1 - (T)2 * (xx + zz); \
        r.arr[1][2] = (T)2 * (yz + wx); \
        r.arr[2][0] = (T)2 * (xz + wy); \
        r.arr[2][1] = (T)2 * (yz - wx); \
        r.arr[2][2] = (T)1 - (T)2 * (xx + yy); \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkquattomat4(T)(xkquat(T) me) \
    { \
        xkmat(3, 3, T) m3 = xkquattomat3(T)(me); \
        xkmat(4, 4, T) r; \
        int i, j; \
        for (i = 0; i < 4; ++i) \
        { \
            for (j = 0; j < 4; ++j) \
                r.arr[i][j] = (i == j) ? (T)1 : (T)0; \
        } \
        for (i = 0; i < 3; ++i) \
        { \
            for (j = 0; j < 3; ++j) \
                r.arr[i][j] = m3.arr[i][j]; \
        } \
        return r; \
    } \
    ATTR xkquat(T) xkquatfrommat3(T)(const xkmat(3, 3, T)* me) \
    { \
        xkquat(T) q; \
        T r00 = me->arr[0][0]; \
        T r01 = me->arr[1][0]; \
        T r02 = me->arr[2][0]; \
        T r10 = me->arr[0][1]; \
        T r11 = me->arr[1][1]; \
        T r12 = me->arr[2][1]; \
        T r20 = me->arr[0][2]; \
        T r21 = me->arr[1][2]; \
        T r22 = me->arr[2][2]; \
        T tr = r00 + r11 + r22; \
        if (tr > (T)0) \
        { \
            T s = (T)SQRT(tr + (T)1) * (T)2; \
            q.w = s * (T)0.25; \
            q.x = (r21 - r12) / s; \
            q.y = (r02 - r20) / s; \
            q.z = (r10 - r01) / s; \
        } \
        else if (r00 > r11 && r00 > r22) \
        { \
            T s = (T)SQRT((T)1 + r00 - r11 - r22) * (T)2; \
            q.w = (r21 - r12) / s; \
            q.x = s * (T)0.25; \
            q.y = (r01 + r10) / s; \
            q.z = (r02 + r20) / s; \
        } \
        else if (r11 > r22) \
        { \
            T s = (T)SQRT((T)1 + r11 - r00 - r22) * (T)2; \
            q.w = (r02 - r20) / s; \
            q.x = (r01 + r10) / s; \
            q.y = s * (T)0.25; \
            q.z = (r12 + r21) / s; \
        } \
        else \
        { \
            T s = (T)SQRT((T)1 + r22 - r00 - r11) * (T)2; \
            q.w = (r10 - r01) / s; \
            q.x = (r02 + r20) / s; \
            q.y = (r12 + r21) / s; \
            q.z = s * (T)0.25; \
        } \
        return q; \
    } \
    ATTR xkquat(T) xkquatfrommat4(T)(const xkmat(4, 4, T)* me) \
    { \
        xkmat(3, 3, T) m3; \
        int i, j; \
        for (i = 0; i < 3; ++i) \
        { \
            for (j = 0; j < 3; ++j) \
                m3.arr[i][j] = me->arr[i][j]; \
        } \
        return xkquatfrommat3(T)(&m3); \
    } \
    ATTR xkquat(T) xkquatlerp(T)(xkquat(T) a, xkquat(T) b, T t) \
    { \
        xkquat(T) r; \
        r.x = a.x + (b.x - a.x) * t; \
        r.y = a.y + (b.y - a.y) * t; \
        r.z = a.z + (b.z - a.z) * t; \
        r.w = a.w + (b.w - a.w) * t; \
        return r; \
    } \
    ATTR xkquat(T) xkquatslerp(T)(xkquat(T) a, xkquat(T) b, T t) \
    { \
        T d = xkquatdot(T)(a, b); \
        T theta; \
        T s; \
        T wa; \
        T wb; \
        xkquat(T) r; \
        if (d < (T)0) \
        { \
            b = xkquatnegate(T)(b); \
            d = -d; \
        } \
        if (d > (T)1 - (T)EPS) \
            return xkquatlerp(T)(a, b, t); \
        theta = (T)ACOS(d); \
        s = (T)SIN(theta); \
        wa = (T)SIN(((T)1 - t) * theta) / s; \
        wb = (T)SIN(t * theta) / s; \
        r.x = a.x * wa + b.x * wb; \
        r.y = a.y * wa + b.y * wb; \
        r.z = a.z * wa + b.z * wb; \
        r.w = a.w * wa + b.w * wb; \
        return r; \
    } \
    ATTR bool xkquatequals(T)(xkquat(T) a, xkquat(T) b) \
    { \
        return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w; \
    }

// MARK: instantiate
#define XK_PRIVATE_TRANSFORM_INSTALL_QUAT(T, ATTR, SQRT, SIN, COS, ACOS, EPS) \
    XK_PRIVATE_TRANSFORM_QUAT_IMPL(T, ATTR, SQRT, SIN, COS, ACOS, EPS)

XK_PRIVATE_TRANSFORM_INSTALL_QUAT(float, static inline, sqrtf, sinf, cosf, acosf, 1e-6f)
XK_PRIVATE_TRANSFORM_INSTALL_QUAT(double, static inline, sqrt, sin, cos, acos, 1e-12)

#endif
