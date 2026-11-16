// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__XKTRANSFORM_PROJECT_H
#define XK_INTERNAL__XKTRANSFORM_PROJECT_H

#include "_xktransform_common.h"
#include "_xktransform_type.h"
#include "_xktransform_vec.h"
#include "_xktransform_mat.h"

// MARK: name
#define xkmat4x4lookatrh(T)           XK_CAT(xk_PUBLIC_mat4x4_lookatrh_, T)
#define xkmat4x4lookatlh(T)           XK_CAT(xk_PUBLIC_mat4x4_lookatlh_, T)
#define xkmat4x4perspectivefovrh(T)   XK_CAT(xk_PUBLIC_mat4x4_perspectivefovrh_, T)
#define xkmat4x4perspectivefovrhgl(T) XK_CAT(xk_PUBLIC_mat4x4_perspectivefovrhgl_, T)
#define xkmat4x4perspectivefovlh(T)   XK_CAT(xk_PUBLIC_mat4x4_perspectivefovlh_, T)
#define xkmat4x4perspectivefovlhgl(T) XK_CAT(xk_PUBLIC_mat4x4_perspectivefovlhgl_, T)
#define xkmat4x4orthographicrh(T)     XK_CAT(xk_PUBLIC_mat4x4_orthographicrh_, T)
#define xkmat4x4orthographicrhgl(T)   XK_CAT(xk_PUBLIC_mat4x4_orthographicrhgl_, T)
#define xkmat4x4orthographiclh(T)     XK_CAT(xk_PUBLIC_mat4x4_orthographiclh_, T)
#define xkmat4x4orthographiclhgl(T)   XK_CAT(xk_PUBLIC_mat4x4_orthographiclhgl_, T)

// MARK: impl
#define XK_PRIVATE_TRANSFORM_MAT4_PROJECT_IMPL(T, ATTR, SIN, COS) \
    ATTR xkmat(4, 4, T) xkmat4x4lookatrh(T)(xkvec(3, T) eye, xkvec(3, T) at, xkvec(3, T) up) \
    { \
        xkvec(3, T) dir = xkvec3sub(T)(eye, at); \
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
    } \
    ATTR xkmat(4, 4, T) xkmat4x4lookatlh(T)(xkvec(3, T) eye, xkvec(3, T) at, xkvec(3, T) up) \
    { \
        xkvec(3, T) dir = xkvec3sub(T)(at, eye); \
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
    } \
    ATTR xkmat(4, 4, T) xkmat4x4perspectivefovrh(T)(T fovy, T aspect, T znear, T zfar) \
    { \
        xkmat(4, 4, T) r = xkmat4x4zero(T)(); \
        T half = fovy * (T)0.5; \
        T height = (T)COS(half) / (T)SIN(half); \
        T width = height / aspect; \
        r.arr[0][0] = width; \
        r.arr[1][1] = height; \
        r.arr[2][2] = zfar / (znear - zfar); \
        r.arr[2][3] = (T)-1; \
        r.arr[3][2] = znear * zfar / (znear - zfar); \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4perspectivefovrhgl(T)(T fovy, T aspect, T znear, T zfar) \
    { \
        xkmat(4, 4, T) r = xkmat4x4zero(T)(); \
        T half = fovy * (T)0.5; \
        T height = (T)COS(half) / (T)SIN(half); \
        T width = height / aspect; \
        r.arr[0][0] = width; \
        r.arr[1][1] = height; \
        r.arr[2][2] = (zfar + znear) / (znear - zfar); \
        r.arr[2][3] = (T)-1; \
        r.arr[3][2] = (T)2 * znear * zfar / (znear - zfar); \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4perspectivefovlh(T)(T fovy, T aspect, T znear, T zfar) \
    { \
        xkmat(4, 4, T) r = xkmat4x4zero(T)(); \
        T half = fovy * (T)0.5; \
        T height = (T)COS(half) / (T)SIN(half); \
        T width = height / aspect; \
        r.arr[0][0] = width; \
        r.arr[1][1] = height; \
        r.arr[2][2] = zfar / (zfar - znear); \
        r.arr[2][3] = (T)1; \
        r.arr[3][2] = -znear * zfar / (zfar - znear); \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4perspectivefovlhgl(T)(T fovy, T aspect, T znear, T zfar) \
    { \
        xkmat(4, 4, T) r = xkmat4x4zero(T)(); \
        T half = fovy * (T)0.5; \
        T height = (T)COS(half) / (T)SIN(half); \
        T width = height / aspect; \
        r.arr[0][0] = width; \
        r.arr[1][1] = height; \
        r.arr[2][2] = (zfar + znear) / (zfar - znear); \
        r.arr[2][3] = (T)1; \
        r.arr[3][2] = (T)-2 * znear * zfar / (zfar - znear); \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4orthographicrh(T)(T width, T height, T znear, T zfar) \
    { \
        xkmat(4, 4, T) r = xkmat4x4zero(T)(); \
        r.arr[0][0] = (T)2 / width; \
        r.arr[1][1] = (T)2 / height; \
        r.arr[2][2] = (T)1 / (znear - zfar); \
        r.arr[3][2] = znear / (znear - zfar); \
        r.arr[3][3] = (T)1; \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4orthographicrhgl(T)(T width, T height, T znear, T zfar) \
    { \
        xkmat(4, 4, T) r = xkmat4x4zero(T)(); \
        r.arr[0][0] = (T)2 / width; \
        r.arr[1][1] = (T)2 / height; \
        r.arr[2][2] = (T)2 / (znear - zfar); \
        r.arr[3][2] = (zfar + znear) / (znear - zfar); \
        r.arr[3][3] = (T)1; \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4orthographiclh(T)(T width, T height, T znear, T zfar) \
    { \
        xkmat(4, 4, T) r = xkmat4x4zero(T)(); \
        r.arr[0][0] = (T)2 / width; \
        r.arr[1][1] = (T)2 / height; \
        r.arr[2][2] = (T)1 / (zfar - znear); \
        r.arr[3][2] = -znear / (zfar - znear); \
        r.arr[3][3] = (T)1; \
        return r; \
    } \
    ATTR xkmat(4, 4, T) xkmat4x4orthographiclhgl(T)(T width, T height, T znear, T zfar) \
    { \
        xkmat(4, 4, T) r = xkmat4x4zero(T)(); \
        r.arr[0][0] = (T)2 / width; \
        r.arr[1][1] = (T)2 / height; \
        r.arr[2][2] = (T)2 / (zfar - znear); \
        r.arr[3][2] = -(zfar + znear) / (zfar - znear); \
        r.arr[3][3] = (T)1; \
        return r; \
    }

// MARK: instantiate
#define XK_PRIVATE_TRANSFORM_INSTALL_MAT4_PROJECT(T, ATTR, SIN, COS) \
    XK_PRIVATE_TRANSFORM_MAT4_PROJECT_IMPL(T, ATTR, SIN, COS)

XK_PRIVATE_TRANSFORM_INSTALL_MAT4_PROJECT(float, static inline, sinf, cosf)
XK_PRIVATE_TRANSFORM_INSTALL_MAT4_PROJECT(double, static inline, sin, cos)

#endif
