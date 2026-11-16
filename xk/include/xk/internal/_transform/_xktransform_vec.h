// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__TRANSFORM__XKTRANSFORM_VEC_H
#define XK_INTERNAL__TRANSFORM__XKTRANSFORM_VEC_H

#include "_xktransform_common.h"
#include "_xktransform_type.h"

// MARK: name
#define xkvec2make(T)       XK_CAT(xk_PUBLIC_vec2_make_, T)
#define xkvec2zero(T)       XK_CAT(xk_PUBLIC_vec2_zero_, T)
#define xkvec2one(T)        XK_CAT(xk_PUBLIC_vec2_one_, T)
#define xkvec2set(T)        XK_CAT(xk_PUBLIC_vec2_set_, T)
#define xkvec2add(T)        XK_CAT(xk_PUBLIC_vec2_add_, T)
#define xkvec2sub(T)        XK_CAT(xk_PUBLIC_vec2_sub_, T)
#define xkvec2mul(T)        XK_CAT(xk_PUBLIC_vec2_mul_, T)
#define xkvec2div(T)        XK_CAT(xk_PUBLIC_vec2_div_, T)
#define xkvec2scale(T)      XK_CAT(xk_PUBLIC_vec2_scale_, T)
#define xkvec2negate(T)     XK_CAT(xk_PUBLIC_vec2_negate_, T)
#define xkvec2min(T)        XK_CAT(xk_PUBLIC_vec2_min_, T)
#define xkvec2max(T)        XK_CAT(xk_PUBLIC_vec2_max_, T)
#define xkvec2clamp(T)      XK_CAT(xk_PUBLIC_vec2_clamp_, T)
#define xkvec2equals(T)     XK_CAT(xk_PUBLIC_vec2_equals_, T)
#define xkvec2dot(T)        XK_CAT(xk_PUBLIC_vec2_dot_, T)
#define xkvec2lengthsq(T)   XK_CAT(xk_PUBLIC_vec2_lengthsq_, T)
#define xkvec2length(T)     XK_CAT(xk_PUBLIC_vec2_length_, T)
#define xkvec2distancesq(T) XK_CAT(xk_PUBLIC_vec2_distancesq_, T)
#define xkvec2distance(T)   XK_CAT(xk_PUBLIC_vec2_distance_, T)
#define xkvec2normalize(T)  XK_CAT(xk_PUBLIC_vec2_normalize_, T)
#define xkvec2lerp(T)       XK_CAT(xk_PUBLIC_vec2_lerp_, T)

#define xkvec3make(T)       XK_CAT(xk_PUBLIC_vec3_make_, T)
#define xkvec3zero(T)       XK_CAT(xk_PUBLIC_vec3_zero_, T)
#define xkvec3one(T)        XK_CAT(xk_PUBLIC_vec3_one_, T)
#define xkvec3set(T)        XK_CAT(xk_PUBLIC_vec3_set_, T)
#define xkvec3add(T)        XK_CAT(xk_PUBLIC_vec3_add_, T)
#define xkvec3sub(T)        XK_CAT(xk_PUBLIC_vec3_sub_, T)
#define xkvec3mul(T)        XK_CAT(xk_PUBLIC_vec3_mul_, T)
#define xkvec3div(T)        XK_CAT(xk_PUBLIC_vec3_div_, T)
#define xkvec3scale(T)      XK_CAT(xk_PUBLIC_vec3_scale_, T)
#define xkvec3negate(T)     XK_CAT(xk_PUBLIC_vec3_negate_, T)
#define xkvec3cross(T)      XK_CAT(xk_PUBLIC_vec3_cross_, T)
#define xkvec3min(T)        XK_CAT(xk_PUBLIC_vec3_min_, T)
#define xkvec3max(T)        XK_CAT(xk_PUBLIC_vec3_max_, T)
#define xkvec3clamp(T)      XK_CAT(xk_PUBLIC_vec3_clamp_, T)
#define xkvec3equals(T)     XK_CAT(xk_PUBLIC_vec3_equals_, T)
#define xkvec3dot(T)        XK_CAT(xk_PUBLIC_vec3_dot_, T)
#define xkvec3lengthsq(T)   XK_CAT(xk_PUBLIC_vec3_lengthsq_, T)
#define xkvec3length(T)     XK_CAT(xk_PUBLIC_vec3_length_, T)
#define xkvec3distancesq(T) XK_CAT(xk_PUBLIC_vec3_distancesq_, T)
#define xkvec3distance(T)   XK_CAT(xk_PUBLIC_vec3_distance_, T)
#define xkvec3normalize(T)  XK_CAT(xk_PUBLIC_vec3_normalize_, T)
#define xkvec3lerp(T)       XK_CAT(xk_PUBLIC_vec3_lerp_, T)

#define xkvec4make(T)       XK_CAT(xk_PUBLIC_vec4_make_, T)
#define xkvec4zero(T)       XK_CAT(xk_PUBLIC_vec4_zero_, T)
#define xkvec4one(T)        XK_CAT(xk_PUBLIC_vec4_one_, T)
#define xkvec4set(T)        XK_CAT(xk_PUBLIC_vec4_set_, T)
#define xkvec4add(T)        XK_CAT(xk_PUBLIC_vec4_add_, T)
#define xkvec4sub(T)        XK_CAT(xk_PUBLIC_vec4_sub_, T)
#define xkvec4mul(T)        XK_CAT(xk_PUBLIC_vec4_mul_, T)
#define xkvec4div(T)        XK_CAT(xk_PUBLIC_vec4_div_, T)
#define xkvec4scale(T)      XK_CAT(xk_PUBLIC_vec4_scale_, T)
#define xkvec4negate(T)     XK_CAT(xk_PUBLIC_vec4_negate_, T)
#define xkvec4min(T)        XK_CAT(xk_PUBLIC_vec4_min_, T)
#define xkvec4max(T)        XK_CAT(xk_PUBLIC_vec4_max_, T)
#define xkvec4clamp(T)      XK_CAT(xk_PUBLIC_vec4_clamp_, T)
#define xkvec4equals(T)     XK_CAT(xk_PUBLIC_vec4_equals_, T)
#define xkvec4dot(T)        XK_CAT(xk_PUBLIC_vec4_dot_, T)
#define xkvec4lengthsq(T)   XK_CAT(xk_PUBLIC_vec4_lengthsq_, T)
#define xkvec4length(T)     XK_CAT(xk_PUBLIC_vec4_length_, T)
#define xkvec4distancesq(T) XK_CAT(xk_PUBLIC_vec4_distancesq_, T)
#define xkvec4distance(T)   XK_CAT(xk_PUBLIC_vec4_distance_, T)
#define xkvec4normalize(T)  XK_CAT(xk_PUBLIC_vec4_normalize_, T)
#define xkvec4lerp(T)       XK_CAT(xk_PUBLIC_vec4_lerp_, T)

#define xkvec2to3(T) XK_CAT(xk_PUBLIC_vec2_to3_, T)
#define xkvec2to4(T) XK_CAT(xk_PUBLIC_vec2_to4_, T)
#define xkvec3to2(T) XK_CAT(xk_PUBLIC_vec3_to2_, T)
#define xkvec3to4(T) XK_CAT(xk_PUBLIC_vec3_to4_, T)
#define xkvec4to2(T) XK_CAT(xk_PUBLIC_vec4_to2_, T)
#define xkvec4to3(T) XK_CAT(xk_PUBLIC_vec4_to3_, T)

// MARK: impl
#define XK_PRIVATE_TRANSFORM_VEC_COMMON_IMPL(N, T, ATTR, SQRT, EPS) \
    ATTR xkvec(N, T) XK_PRIVATE_TRANSFORM_VEC_FN(N, _zero_, T)(void) \
    { \
        xkvec(N, T) r; \
        int i; \
        for (i = 0; i < (N); ++i) \
            r.arr[i] = (T)0; \
        return r; \
    } \
    ATTR xkvec(N, T) XK_PRIVATE_TRANSFORM_VEC_FN(N, _one_, T)(void) \
    { \
        xkvec(N, T) r; \
        int i; \
        for (i = 0; i < (N); ++i) \
            r.arr[i] = (T)1; \
        return r; \
    } \
    ATTR xkvec(N, T) XK_PRIVATE_TRANSFORM_VEC_FN(N, _set_, T)(T v) \
    { \
        xkvec(N, T) r; \
        int i; \
        for (i = 0; i < (N); ++i) \
            r.arr[i] = v; \
        return r; \
    } \
    ATTR xkvec(N, T) XK_PRIVATE_TRANSFORM_VEC_FN(N, _add_, T)(xkvec(N, T) a, xkvec(N, T) b) \
    { \
        xkvec(N, T) r; \
        int i; \
        for (i = 0; i < (N); ++i) \
            r.arr[i] = a.arr[i] + b.arr[i]; \
        return r; \
    } \
    ATTR xkvec(N, T) XK_PRIVATE_TRANSFORM_VEC_FN(N, _sub_, T)(xkvec(N, T) a, xkvec(N, T) b) \
    { \
        xkvec(N, T) r; \
        int i; \
        for (i = 0; i < (N); ++i) \
            r.arr[i] = a.arr[i] - b.arr[i]; \
        return r; \
    } \
    ATTR xkvec(N, T) XK_PRIVATE_TRANSFORM_VEC_FN(N, _mul_, T)(xkvec(N, T) a, xkvec(N, T) b) \
    { \
        xkvec(N, T) r; \
        int i; \
        for (i = 0; i < (N); ++i) \
            r.arr[i] = a.arr[i] * b.arr[i]; \
        return r; \
    } \
    ATTR xkvec(N, T) XK_PRIVATE_TRANSFORM_VEC_FN(N, _div_, T)(xkvec(N, T) a, xkvec(N, T) b) \
    { \
        xkvec(N, T) r; \
        int i; \
        for (i = 0; i < (N); ++i) \
            r.arr[i] = a.arr[i] / b.arr[i]; \
        return r; \
    } \
    ATTR xkvec(N, T) XK_PRIVATE_TRANSFORM_VEC_FN(N, _scale_, T)(xkvec(N, T) me, T s) \
    { \
        xkvec(N, T) r; \
        int i; \
        for (i = 0; i < (N); ++i) \
            r.arr[i] = me.arr[i] * s; \
        return r; \
    } \
    ATTR xkvec(N, T) XK_PRIVATE_TRANSFORM_VEC_FN(N, _negate_, T)(xkvec(N, T) me) \
    { \
        xkvec(N, T) r; \
        int i; \
        for (i = 0; i < (N); ++i) \
            r.arr[i] = -me.arr[i]; \
        return r; \
    } \
    ATTR xkvec(N, T) XK_PRIVATE_TRANSFORM_VEC_FN(N, _min_, T)(xkvec(N, T) a, xkvec(N, T) b) \
    { \
        xkvec(N, T) r; \
        int i; \
        for (i = 0; i < (N); ++i) \
            r.arr[i] = a.arr[i] < b.arr[i] ? a.arr[i] : b.arr[i]; \
        return r; \
    } \
    ATTR xkvec(N, T) XK_PRIVATE_TRANSFORM_VEC_FN(N, _max_, T)(xkvec(N, T) a, xkvec(N, T) b) \
    { \
        xkvec(N, T) r; \
        int i; \
        for (i = 0; i < (N); ++i) \
            r.arr[i] = a.arr[i] > b.arr[i] ? a.arr[i] : b.arr[i]; \
        return r; \
    } \
    ATTR xkvec(N, T) XK_PRIVATE_TRANSFORM_VEC_FN(N, _clamp_, T)(xkvec(N, T) me, xkvec(N, T) lo, xkvec(N, T) hi) \
    { \
        xkvec(N, T) r; \
        int i; \
        for (i = 0; i < (N); ++i) \
            r.arr[i] = me.arr[i] < lo.arr[i] \
                ? lo.arr[i] \
                : (me.arr[i] > hi.arr[i] ? hi.arr[i] : me.arr[i]); \
        return r; \
    } \
    ATTR bool XK_PRIVATE_TRANSFORM_VEC_FN(N, _equals_, T)(xkvec(N, T) a, xkvec(N, T) b) \
    { \
        int i; \
        for (i = 0; i < (N); ++i) \
        { \
            if (a.arr[i] != b.arr[i]) \
                return false; \
        } \
        return true; \
    } \
    ATTR T XK_PRIVATE_TRANSFORM_VEC_FN(N, _dot_, T)(xkvec(N, T) a, xkvec(N, T) b) \
    { \
        T r = (T)0; \
        int i; \
        for (i = 0; i < (N); ++i) \
            r += a.arr[i] * b.arr[i]; \
        return r; \
    } \
    ATTR T XK_PRIVATE_TRANSFORM_VEC_FN(N, _lengthsq_, T)(xkvec(N, T) me) \
    { \
        return XK_PRIVATE_TRANSFORM_VEC_FN(N, _dot_, T)(me, me); \
    } \
    ATTR T XK_PRIVATE_TRANSFORM_VEC_FN(N, _length_, T)(xkvec(N, T) me) \
    { \
        T lensq = XK_PRIVATE_TRANSFORM_VEC_FN(N, _lengthsq_, T)(me); \
        return (T)SQRT(lensq); \
    } \
    ATTR T XK_PRIVATE_TRANSFORM_VEC_FN(N, _distancesq_, T)(xkvec(N, T) a, xkvec(N, T) b) \
    { \
        T r = (T)0; \
        T d; \
        int i; \
        for (i = 0; i < (N); ++i) \
        { \
            d = a.arr[i] - b.arr[i]; \
            r += d * d; \
        } \
        return r; \
    } \
    ATTR T XK_PRIVATE_TRANSFORM_VEC_FN(N, _distance_, T)(xkvec(N, T) a, xkvec(N, T) b) \
    { \
        T dsq = XK_PRIVATE_TRANSFORM_VEC_FN(N, _distancesq_, T)(a, b); \
        return (T)SQRT(dsq); \
    } \
    ATTR xkvec(N, T) XK_PRIVATE_TRANSFORM_VEC_FN(N, _normalize_, T)(xkvec(N, T) me) \
    { \
        T lensq = XK_PRIVATE_TRANSFORM_VEC_FN(N, _lengthsq_, T)(me); \
        T len; \
        T inv; \
        if (lensq <= (T)EPS) \
            return XK_PRIVATE_TRANSFORM_VEC_FN(N, _zero_, T)(); \
        len = (T)SQRT(lensq); \
        inv = (T)1 / len; \
        return XK_PRIVATE_TRANSFORM_VEC_FN(N, _scale_, T)(me, inv); \
    } \
    ATTR xkvec(N, T) XK_PRIVATE_TRANSFORM_VEC_FN(N, _lerp_, T)(xkvec(N, T) a, xkvec(N, T) b, T t) \
    { \
        xkvec(N, T) r; \
        int i; \
        for (i = 0; i < (N); ++i) \
            r.arr[i] = a.arr[i] + (b.arr[i] - a.arr[i]) * t; \
        return r; \
    }

// MARK: vec2 impl
#define XK_PRIVATE_TRANSFORM_VEC2_IMPL(T, ATTR, SQRT, EPS) \
    XK_PRIVATE_TRANSFORM_VEC_COMMON_IMPL(2, T, ATTR, SQRT, EPS) \
    ATTR xkvec(2, T) xkvec2make(T)(T x, T y) \
    { \
        xkvec(2, T) r; \
        r.x = x; \
        r.y = y; \
        return r; \
    }

// MARK: vec3 impl
#define XK_PRIVATE_TRANSFORM_VEC3_IMPL(T, ATTR, SQRT, EPS) \
    XK_PRIVATE_TRANSFORM_VEC_COMMON_IMPL(3, T, ATTR, SQRT, EPS) \
    ATTR xkvec(3, T) xkvec3make(T)(T x, T y, T z) \
    { \
        xkvec(3, T) r; \
        r.x = x; \
        r.y = y; \
        r.z = z; \
        return r; \
    } \
    ATTR xkvec(3, T) xkvec3cross(T)(xkvec(3, T) a, xkvec(3, T) b) \
    { \
        xkvec(3, T) r; \
        r.x = a.y * b.z - a.z * b.y; \
        r.y = a.z * b.x - a.x * b.z; \
        r.z = a.x * b.y - a.y * b.x; \
        return r; \
    }

// MARK: vec4 impl
#define XK_PRIVATE_TRANSFORM_VEC4_IMPL(T, ATTR, SQRT, EPS) \
    XK_PRIVATE_TRANSFORM_VEC_COMMON_IMPL(4, T, ATTR, SQRT, EPS) \
    ATTR xkvec(4, T) xkvec4make(T)(T x, T y, T z, T w) \
    { \
        xkvec(4, T) r; \
        r.x = x; \
        r.y = y; \
        r.z = z; \
        r.w = w; \
        return r; \
    }

// MARK: convert impl
#define XK_PRIVATE_TRANSFORM_CONVERT_IMPL(T, ATTR) \
    ATTR xkvec(3, T) xkvec2to3(T)(xkvec(2, T) me, T z) \
    { \
        xkvec(3, T) r; \
        r.x = me.x; \
        r.y = me.y; \
        r.z = z; \
        return r; \
    } \
    ATTR xkvec(4, T) xkvec2to4(T)(xkvec(2, T) me, T z, T w) \
    { \
        xkvec(4, T) r; \
        r.x = me.x; \
        r.y = me.y; \
        r.z = z; \
        r.w = w; \
        return r; \
    } \
    ATTR xkvec(2, T) xkvec3to2(T)(xkvec(3, T) me) \
    { \
        xkvec(2, T) r; \
        r.x = me.x; \
        r.y = me.y; \
        return r; \
    } \
    ATTR xkvec(4, T) xkvec3to4(T)(xkvec(3, T) me, T w) \
    { \
        xkvec(4, T) r; \
        r.x = me.x; \
        r.y = me.y; \
        r.z = me.z; \
        r.w = w; \
        return r; \
    } \
    ATTR xkvec(2, T) xkvec4to2(T)(xkvec(4, T) me) \
    { \
        xkvec(2, T) r; \
        r.x = me.x; \
        r.y = me.y; \
        return r; \
    } \
    ATTR xkvec(3, T) xkvec4to3(T)(xkvec(4, T) me) \
    { \
        xkvec(3, T) r; \
        r.x = me.x; \
        r.y = me.y; \
        r.z = me.z; \
        return r; \
    }

// MARK: instantiate
#define XK_PRIVATE_TRANSFORM_INSTALL_VEC(T, ATTR, SQRT, EPS) \
    XK_PRIVATE_TRANSFORM_VEC2_IMPL(T, ATTR, SQRT, EPS) \
    XK_PRIVATE_TRANSFORM_VEC3_IMPL(T, ATTR, SQRT, EPS) \
    XK_PRIVATE_TRANSFORM_VEC4_IMPL(T, ATTR, SQRT, EPS) \
    XK_PRIVATE_TRANSFORM_CONVERT_IMPL(T, ATTR)

XK_PRIVATE_TRANSFORM_INSTALL_VEC(float, static inline, sqrtf, 1e-6f)
XK_PRIVATE_TRANSFORM_INSTALL_VEC(double, static inline, sqrt, 1e-12)

#endif
