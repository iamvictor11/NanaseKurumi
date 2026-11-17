// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__TRANSFORM__XKTRANSFORM_PROJECT_H
#define XK_INTERNAL__TRANSFORM__XKTRANSFORM_PROJECT_H

#include "_xktransform_common.h"
#include "_xktransform_type.h"
#include "_xktransform_vec.h"
#include "_xktransform_mat.h"

// MARK: name
#define xkmat4x4lookatRH(T)           XK_CAT(xk_PUBLIC_mat4x4_lookatRH_, T)
#define xkmat4x4lookatLH(T)           XK_CAT(xk_PUBLIC_mat4x4_lookatLH_, T)
#define xkmat4x4frustumRH(T)          XK_CAT(xk_PUBLIC_mat4x4_frustumRH_, T)
#define xkmat4x4frustumRHgl(T)        XK_CAT(xk_PUBLIC_mat4x4_frustumRHgl_, T)
#define xkmat4x4frustumLH(T)          XK_CAT(xk_PUBLIC_mat4x4_frustumLH_, T)
#define xkmat4x4frustumLHgl(T)        XK_CAT(xk_PUBLIC_mat4x4_frustumLHgl_, T)
#define xkmat4x4perspectivefovRH(T)   XK_CAT(xk_PUBLIC_mat4x4_perspectivefovRH_, T)
#define xkmat4x4perspectivefovRHgl(T) XK_CAT(xk_PUBLIC_mat4x4_perspectivefovRHgl_, T)
#define xkmat4x4perspectivefovLH(T)   XK_CAT(xk_PUBLIC_mat4x4_perspectivefovLH_, T)
#define xkmat4x4perspectivefovLHgl(T) XK_CAT(xk_PUBLIC_mat4x4_perspectivefovLHgl_, T)
#define xkmat4x4orthographicRH(T)     XK_CAT(xk_PUBLIC_mat4x4_orthographicRH_, T)
#define xkmat4x4orthographicRHgl(T)   XK_CAT(xk_PUBLIC_mat4x4_orthographicRHgl_, T)
#define xkmat4x4orthographicLH(T)     XK_CAT(xk_PUBLIC_mat4x4_orthographicLH_, T)
#define xkmat4x4orthographicLHgl(T)   XK_CAT(xk_PUBLIC_mat4x4_orthographicLHgl_, T)
#define xkmat4x4perspective(T)        XK_CAT(xk_PUBLIC_mat4x4_perspective_, T)
#define xkmat4x4perspectivevec(T)     XK_CAT(xk_PUBLIC_mat4x4_perspectivevec_, T)

// MARK: impl
// lookat only differs in which way the z axis points.
#define XK_PRIVATE_TRANSFORM_MAT4_LOOKAT(NAME, T, ATTR, DIR) \
    ATTR xkmat(4, 4, T) NAME(T)(xkvec(3, T) eye, xkvec(3, T) at, xkvec(3, T) up) \
    { \
        xkvec(3, T) dir = DIR; \
        xkvec(3, T) zaxis = xkvec3normalize(T)(dir); \
        xkvec(3, T) side = xkvec3cross(T)(up, zaxis); \
        xkvec(3, T) xaxis = xkvec3normalize(T)(side); \
        xkvec(3, T) yaxis = xkvec3cross(T)(zaxis, xaxis); \
        xkmat(4, 4, T) r = xkmat4x4identity(T)(); \
        r.arr[0][0] = xaxis.x; \
        r.arr[0][1] = yaxis.x; \
        r.arr[0][2] = zaxis.x; \
        r.arr[1][0] = xaxis.y; \
        r.arr[1][1] = yaxis.y; \
        r.arr[1][2] = zaxis.y; \
        r.arr[2][0] = xaxis.z; \
        r.arr[2][1] = yaxis.z; \
        r.arr[2][2] = zaxis.z; \
        r.arr[3][0] = -xkvec3dot(T)(xaxis, eye); \
        r.arr[3][1] = -xkvec3dot(T)(yaxis, eye); \
        r.arr[3][2] = -xkvec3dot(T)(zaxis, eye); \
        return r; \
    }

// perspectivefov only differs in which frustum it feeds, the bounds come from the same fovy.
#define XK_PRIVATE_TRANSFORM_MAT4_PFOV(NAME, FRUSTUM, T, ATTR, SIN, COS) \
    ATTR xkmat(4, 4, T) NAME(T)(T fovy, T aspect, T znear, T zfar) \
    { \
        T half = fovy * (T)0.5; \
        T top = znear * (T)SIN(half) / (T)COS(half); \
        T right = top * aspect; \
        T left = -right; \
        T bottom = -top; \
        return FRUSTUM(T)(left, right, bottom, top, znear, zfar); \
    }

#define XK_PRIVATE_TRANSFORM_MAT4_PROJECT_IMPL(T, ATTR, SIN, COS) \
    XK_PRIVATE_TRANSFORM_MAT4_LOOKAT(xkmat4x4lookatRH, T, ATTR, xkvec3sub(T)(eye, at)) \
    XK_PRIVATE_TRANSFORM_MAT4_LOOKAT(xkmat4x4lookatLH, T, ATTR, xkvec3sub(T)(at, eye)) \
    ATTR xkmat(4, 4, T) xkmat4x4frustumRH(T)(T left, T right, T bottom, T top, T znear, T zfar) \
    { \
        xkmat(4, 4, T) r = xkmat4x4zero(T)(); \
        r.arr[0][0] = (T)2 * znear / (right - left); \
        r.arr[1][1] = (T)2 * znear / (top - bottom); \
        r.arr[2][0] = (right + left) / (right - left); \
        r.arr[2][1] = (top + bottom) / (top - bottom); \
        r.arr[2][2] = zfar / (znear - zfar); \
        r.arr[2][3] = (T)-1; \
        r.arr[3][2] = znear * zfar / (znear - zfar); \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4frustumRHgl(T)(T left, T right, T bottom, T top, T znear, T zfar) \
    { \
        xkmat(4, 4, T) r = xkmat4x4zero(T)(); \
        r.arr[0][0] = (T)2 * znear / (right - left); \
        r.arr[1][1] = (T)2 * znear / (top - bottom); \
        r.arr[2][0] = (right + left) / (right - left); \
        r.arr[2][1] = (top + bottom) / (top - bottom); \
        r.arr[2][2] = (zfar + znear) / (znear - zfar); \
        r.arr[2][3] = (T)-1; \
        r.arr[3][2] = (T)2 * znear * zfar / (znear - zfar); \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4frustumLH(T)(T left, T right, T bottom, T top, T znear, T zfar) \
    { \
        xkmat(4, 4, T) r = xkmat4x4zero(T)(); \
        r.arr[0][0] = (T)2 * znear / (right - left); \
        r.arr[1][1] = (T)2 * znear / (top - bottom); \
        r.arr[2][0] = (right + left) / (right - left); \
        r.arr[2][1] = (top + bottom) / (top - bottom); \
        r.arr[2][2] = zfar / (zfar - znear); \
        r.arr[2][3] = (T)1; \
        r.arr[3][2] = -znear * zfar / (zfar - znear); \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4frustumLHgl(T)(T left, T right, T bottom, T top, T znear, T zfar) \
    { \
        xkmat(4, 4, T) r = xkmat4x4zero(T)(); \
        r.arr[0][0] = (T)2 * znear / (right - left); \
        r.arr[1][1] = (T)2 * znear / (top - bottom); \
        r.arr[2][0] = (right + left) / (right - left); \
        r.arr[2][1] = (top + bottom) / (top - bottom); \
        r.arr[2][2] = (zfar + znear) / (zfar - znear); \
        r.arr[2][3] = (T)1; \
        r.arr[3][2] = (T)-2 * znear * zfar / (zfar - znear); \
        return r; \
    } \
    XK_PRIVATE_TRANSFORM_MAT4_PFOV(xkmat4x4perspectivefovRH, xkmat4x4frustumRH, T, ATTR, SIN, COS) \
    XK_PRIVATE_TRANSFORM_MAT4_PFOV(xkmat4x4perspectivefovRHgl, xkmat4x4frustumRHgl, T, ATTR, SIN, COS) \
    XK_PRIVATE_TRANSFORM_MAT4_PFOV(xkmat4x4perspectivefovLH, xkmat4x4frustumLH, T, ATTR, SIN, COS) \
    XK_PRIVATE_TRANSFORM_MAT4_PFOV(xkmat4x4perspectivefovLHgl, xkmat4x4frustumLHgl, T, ATTR, SIN, COS) \
    ATTR xkmat(4, 4, T) xkmat4x4orthographicRH(T)(T left, T right, T bottom, T top, T znear, T zfar) \
    { \
        xkmat(4, 4, T) r = xkmat4x4zero(T)(); \
        r.arr[0][0] = (T)2 / (right - left); \
        r.arr[1][1] = (T)2 / (top - bottom); \
        r.arr[2][2] = (T)1 / (znear - zfar); \
        r.arr[3][0] = -(right + left) / (right - left); \
        r.arr[3][1] = -(top + bottom) / (top - bottom); \
        r.arr[3][2] = znear / (znear - zfar); \
        r.arr[3][3] = (T)1; \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4orthographicRHgl(T)(T left, T right, T bottom, T top, T znear, T zfar) \
    { \
        xkmat(4, 4, T) r = xkmat4x4zero(T)(); \
        r.arr[0][0] = (T)2 / (right - left); \
        r.arr[1][1] = (T)2 / (top - bottom); \
        r.arr[2][2] = (T)2 / (znear - zfar); \
        r.arr[3][0] = -(right + left) / (right - left); \
        r.arr[3][1] = -(top + bottom) / (top - bottom); \
        r.arr[3][2] = (zfar + znear) / (znear - zfar); \
        r.arr[3][3] = (T)1; \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4orthographicLH(T)(T left, T right, T bottom, T top, T znear, T zfar) \
    { \
        xkmat(4, 4, T) r = xkmat4x4zero(T)(); \
        r.arr[0][0] = (T)2 / (right - left); \
        r.arr[1][1] = (T)2 / (top - bottom); \
        r.arr[2][2] = (T)1 / (zfar - znear); \
        r.arr[3][0] = -(right + left) / (right - left); \
        r.arr[3][1] = -(top + bottom) / (top - bottom); \
        r.arr[3][2] = -znear / (zfar - znear); \
        r.arr[3][3] = (T)1; \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4orthographicLHgl(T)(T left, T right, T bottom, T top, T znear, T zfar) \
    { \
        xkmat(4, 4, T) r = xkmat4x4zero(T)(); \
        r.arr[0][0] = (T)2 / (right - left); \
        r.arr[1][1] = (T)2 / (top - bottom); \
        r.arr[2][2] = (T)2 / (zfar - znear); \
        r.arr[3][0] = -(right + left) / (right - left); \
        r.arr[3][1] = -(top + bottom) / (top - bottom); \
        r.arr[3][2] = -(zfar + znear) / (zfar - znear); \
        r.arr[3][3] = (T)1; \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4perspectivevec(T)(xkvec(4, T) p) \
    { \
        xkmat(4, 4, T) r = xkmat4x4identity(T)(); \
        r.arr[0][3] = p.x; \
        r.arr[1][3] = p.y; \
        r.arr[2][3] = p.z; \
        r.arr[3][3] = p.w; \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4perspective(T)(xkvec(2, T) origin, T distance) \
    { \
        xkmat(4, 4, T) r = xkmat4x4identity(T)(); \
        r.arr[2][0] = -origin.x / distance; \
        r.arr[2][1] = -origin.y / distance; \
        r.arr[2][3] = (T)-1 / distance; \
        return r; \
    }
// MARK: instantiate
XK_PRIVATE_TRANSFORM_MAT4_PROJECT_IMPL(float, static inline, sinf, cosf)
XK_PRIVATE_TRANSFORM_MAT4_PROJECT_IMPL(double, static inline, sin, cos)

#endif
