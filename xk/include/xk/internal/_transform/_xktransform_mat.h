// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__XKTRANSFORM_MAT_H
#define XK_INTERNAL__XKTRANSFORM_MAT_H

#include "_xktransform_common.h"
#include "_xktransform_type.h"

// MARK: name
#define xkmat2x2zero(T)      XK_CAT(xk_PUBLIC_mat2x2_zero_, T)
#define xkmat2x2identity(T)  XK_CAT(xk_PUBLIC_mat2x2_identity_, T)
#define xkmat2x2add(T)       XK_CAT(xk_PUBLIC_mat2x2_add_, T)
#define xkmat2x2sub(T)       XK_CAT(xk_PUBLIC_mat2x2_sub_, T)
#define xkmat2x2scale(T)     XK_CAT(xk_PUBLIC_mat2x2_scale_, T)
#define xkmat2x2negate(T)    XK_CAT(xk_PUBLIC_mat2x2_negate_, T)
#define xkmat2x2transpose(T) XK_CAT(xk_PUBLIC_mat2x2_transpose_, T)
#define xkmat2x2mulvec(T)    XK_CAT(xk_PUBLIC_mat2x2_mulvec_, T)
#define xkmat2x2vecmul(T)    XK_CAT(xk_PUBLIC_mat2x2_vecmul_, T)
#define xkmat2x2det(T)       XK_CAT(xk_PUBLIC_mat2x2_det_, T)
#define xkmat2x2inverse(T)   XK_CAT(xk_PUBLIC_mat2x2_inverse_, T)

#define xkmat2x3zero(T)      XK_CAT(xk_PUBLIC_mat2x3_zero_, T)
#define xkmat2x3add(T)       XK_CAT(xk_PUBLIC_mat2x3_add_, T)
#define xkmat2x3sub(T)       XK_CAT(xk_PUBLIC_mat2x3_sub_, T)
#define xkmat2x3scale(T)     XK_CAT(xk_PUBLIC_mat2x3_scale_, T)
#define xkmat2x3negate(T)    XK_CAT(xk_PUBLIC_mat2x3_negate_, T)
#define xkmat2x3transpose(T) XK_CAT(xk_PUBLIC_mat2x3_transpose_, T)
#define xkmat2x3mulvec(T)    XK_CAT(xk_PUBLIC_mat2x3_mulvec_, T)
#define xkmat2x3vecmul(T)    XK_CAT(xk_PUBLIC_mat2x3_vecmul_, T)

#define xkmat2x4zero(T)      XK_CAT(xk_PUBLIC_mat2x4_zero_, T)
#define xkmat2x4add(T)       XK_CAT(xk_PUBLIC_mat2x4_add_, T)
#define xkmat2x4sub(T)       XK_CAT(xk_PUBLIC_mat2x4_sub_, T)
#define xkmat2x4scale(T)     XK_CAT(xk_PUBLIC_mat2x4_scale_, T)
#define xkmat2x4negate(T)    XK_CAT(xk_PUBLIC_mat2x4_negate_, T)
#define xkmat2x4transpose(T) XK_CAT(xk_PUBLIC_mat2x4_transpose_, T)
#define xkmat2x4mulvec(T)    XK_CAT(xk_PUBLIC_mat2x4_mulvec_, T)
#define xkmat2x4vecmul(T)    XK_CAT(xk_PUBLIC_mat2x4_vecmul_, T)

#define xkmat3x2zero(T)      XK_CAT(xk_PUBLIC_mat3x2_zero_, T)
#define xkmat3x2add(T)       XK_CAT(xk_PUBLIC_mat3x2_add_, T)
#define xkmat3x2sub(T)       XK_CAT(xk_PUBLIC_mat3x2_sub_, T)
#define xkmat3x2scale(T)     XK_CAT(xk_PUBLIC_mat3x2_scale_, T)
#define xkmat3x2negate(T)    XK_CAT(xk_PUBLIC_mat3x2_negate_, T)
#define xkmat3x2transpose(T) XK_CAT(xk_PUBLIC_mat3x2_transpose_, T)
#define xkmat3x2mulvec(T)    XK_CAT(xk_PUBLIC_mat3x2_mulvec_, T)
#define xkmat3x2vecmul(T)    XK_CAT(xk_PUBLIC_mat3x2_vecmul_, T)

#define xkmat3x3zero(T)      XK_CAT(xk_PUBLIC_mat3x3_zero_, T)
#define xkmat3x3identity(T)  XK_CAT(xk_PUBLIC_mat3x3_identity_, T)
#define xkmat3x3add(T)       XK_CAT(xk_PUBLIC_mat3x3_add_, T)
#define xkmat3x3sub(T)       XK_CAT(xk_PUBLIC_mat3x3_sub_, T)
#define xkmat3x3scale(T)     XK_CAT(xk_PUBLIC_mat3x3_scale_, T)
#define xkmat3x3negate(T)    XK_CAT(xk_PUBLIC_mat3x3_negate_, T)
#define xkmat3x3transpose(T) XK_CAT(xk_PUBLIC_mat3x3_transpose_, T)
#define xkmat3x3mulvec(T)    XK_CAT(xk_PUBLIC_mat3x3_mulvec_, T)
#define xkmat3x3vecmul(T)    XK_CAT(xk_PUBLIC_mat3x3_vecmul_, T)
#define xkmat3x3det(T)       XK_CAT(xk_PUBLIC_mat3x3_det_, T)
#define xkmat3x3inverse(T)   XK_CAT(xk_PUBLIC_mat3x3_inverse_, T)

#define xkmat3x4zero(T)      XK_CAT(xk_PUBLIC_mat3x4_zero_, T)
#define xkmat3x4add(T)       XK_CAT(xk_PUBLIC_mat3x4_add_, T)
#define xkmat3x4sub(T)       XK_CAT(xk_PUBLIC_mat3x4_sub_, T)
#define xkmat3x4scale(T)     XK_CAT(xk_PUBLIC_mat3x4_scale_, T)
#define xkmat3x4negate(T)    XK_CAT(xk_PUBLIC_mat3x4_negate_, T)
#define xkmat3x4transpose(T) XK_CAT(xk_PUBLIC_mat3x4_transpose_, T)
#define xkmat3x4mulvec(T)    XK_CAT(xk_PUBLIC_mat3x4_mulvec_, T)
#define xkmat3x4vecmul(T)    XK_CAT(xk_PUBLIC_mat3x4_vecmul_, T)

#define xkmat4x2zero(T)      XK_CAT(xk_PUBLIC_mat4x2_zero_, T)
#define xkmat4x2add(T)       XK_CAT(xk_PUBLIC_mat4x2_add_, T)
#define xkmat4x2sub(T)       XK_CAT(xk_PUBLIC_mat4x2_sub_, T)
#define xkmat4x2scale(T)     XK_CAT(xk_PUBLIC_mat4x2_scale_, T)
#define xkmat4x2negate(T)    XK_CAT(xk_PUBLIC_mat4x2_negate_, T)
#define xkmat4x2transpose(T) XK_CAT(xk_PUBLIC_mat4x2_transpose_, T)
#define xkmat4x2mulvec(T)    XK_CAT(xk_PUBLIC_mat4x2_mulvec_, T)
#define xkmat4x2vecmul(T)    XK_CAT(xk_PUBLIC_mat4x2_vecmul_, T)

#define xkmat4x3zero(T)      XK_CAT(xk_PUBLIC_mat4x3_zero_, T)
#define xkmat4x3add(T)       XK_CAT(xk_PUBLIC_mat4x3_add_, T)
#define xkmat4x3sub(T)       XK_CAT(xk_PUBLIC_mat4x3_sub_, T)
#define xkmat4x3scale(T)     XK_CAT(xk_PUBLIC_mat4x3_scale_, T)
#define xkmat4x3negate(T)    XK_CAT(xk_PUBLIC_mat4x3_negate_, T)
#define xkmat4x3transpose(T) XK_CAT(xk_PUBLIC_mat4x3_transpose_, T)
#define xkmat4x3mulvec(T)    XK_CAT(xk_PUBLIC_mat4x3_mulvec_, T)
#define xkmat4x3vecmul(T)    XK_CAT(xk_PUBLIC_mat4x3_vecmul_, T)

#define xkmat4x4zero(T)      XK_CAT(xk_PUBLIC_mat4x4_zero_, T)
#define xkmat4x4identity(T)  XK_CAT(xk_PUBLIC_mat4x4_identity_, T)
#define xkmat4x4add(T)       XK_CAT(xk_PUBLIC_mat4x4_add_, T)
#define xkmat4x4sub(T)       XK_CAT(xk_PUBLIC_mat4x4_sub_, T)
#define xkmat4x4scale(T)     XK_CAT(xk_PUBLIC_mat4x4_scale_, T)
#define xkmat4x4negate(T)    XK_CAT(xk_PUBLIC_mat4x4_negate_, T)
#define xkmat4x4transpose(T) XK_CAT(xk_PUBLIC_mat4x4_transpose_, T)
#define xkmat4x4mulvec(T)    XK_CAT(xk_PUBLIC_mat4x4_mulvec_, T)
#define xkmat4x4vecmul(T)    XK_CAT(xk_PUBLIC_mat4x4_vecmul_, T)
#define xkmat4x4det(T)       XK_CAT(xk_PUBLIC_mat4x4_det_, T)
#define xkmat4x4inverse(T)   XK_CAT(xk_PUBLIC_mat4x4_inverse_, T)

// MARK: mul name
#define xkmat2x2mul2x2(T) XK_CAT(xk_PUBLIC_mat2x2_mul_2x2_, T)
#define xkmat2x2mul2x3(T) XK_CAT(xk_PUBLIC_mat2x2_mul_2x3_, T)
#define xkmat2x2mul2x4(T) XK_CAT(xk_PUBLIC_mat2x2_mul_2x4_, T)
#define xkmat2x3mul3x2(T) XK_CAT(xk_PUBLIC_mat2x3_mul_3x2_, T)
#define xkmat2x3mul3x3(T) XK_CAT(xk_PUBLIC_mat2x3_mul_3x3_, T)
#define xkmat2x3mul3x4(T) XK_CAT(xk_PUBLIC_mat2x3_mul_3x4_, T)
#define xkmat2x4mul4x2(T) XK_CAT(xk_PUBLIC_mat2x4_mul_4x2_, T)
#define xkmat2x4mul4x3(T) XK_CAT(xk_PUBLIC_mat2x4_mul_4x3_, T)
#define xkmat2x4mul4x4(T) XK_CAT(xk_PUBLIC_mat2x4_mul_4x4_, T)
#define xkmat3x2mul2x2(T) XK_CAT(xk_PUBLIC_mat3x2_mul_2x2_, T)
#define xkmat3x2mul2x3(T) XK_CAT(xk_PUBLIC_mat3x2_mul_2x3_, T)
#define xkmat3x2mul2x4(T) XK_CAT(xk_PUBLIC_mat3x2_mul_2x4_, T)
#define xkmat3x3mul3x2(T) XK_CAT(xk_PUBLIC_mat3x3_mul_3x2_, T)
#define xkmat3x3mul3x3(T) XK_CAT(xk_PUBLIC_mat3x3_mul_3x3_, T)
#define xkmat3x3mul3x4(T) XK_CAT(xk_PUBLIC_mat3x3_mul_3x4_, T)
#define xkmat3x4mul4x2(T) XK_CAT(xk_PUBLIC_mat3x4_mul_4x2_, T)
#define xkmat3x4mul4x3(T) XK_CAT(xk_PUBLIC_mat3x4_mul_4x3_, T)
#define xkmat3x4mul4x4(T) XK_CAT(xk_PUBLIC_mat3x4_mul_4x4_, T)
#define xkmat4x2mul2x2(T) XK_CAT(xk_PUBLIC_mat4x2_mul_2x2_, T)
#define xkmat4x2mul2x3(T) XK_CAT(xk_PUBLIC_mat4x2_mul_2x3_, T)
#define xkmat4x2mul2x4(T) XK_CAT(xk_PUBLIC_mat4x2_mul_2x4_, T)
#define xkmat4x3mul3x2(T) XK_CAT(xk_PUBLIC_mat4x3_mul_3x2_, T)
#define xkmat4x3mul3x3(T) XK_CAT(xk_PUBLIC_mat4x3_mul_3x3_, T)
#define xkmat4x3mul3x4(T) XK_CAT(xk_PUBLIC_mat4x3_mul_3x4_, T)
#define xkmat4x4mul4x2(T) XK_CAT(xk_PUBLIC_mat4x4_mul_4x2_, T)
#define xkmat4x4mul4x3(T) XK_CAT(xk_PUBLIC_mat4x4_mul_4x3_, T)
#define xkmat4x4mul4x4(T) XK_CAT(xk_PUBLIC_mat4x4_mul_4x4_, T)

// MARK: impl
#define XK_PRIVATE_TRANSFORM_MAT_COMMON_IMPL(R, C, T, ATTR) \
    ATTR xkmat(R, C, T) XK_PRIVATE_TRANSFORM_MAT_FN(R, C, _zero_, T)(void) \
    { \
        xkmat(R, C, T) r; \
        int i, j; \
        for (i = 0; i < (R); ++i) \
        { \
            for (j = 0; j < (C); ++j) \
                r.arr[i][j] = (T)0; \
        } \
        return r; \
    } \
    ATTR xkmat(R, C, T) XK_PRIVATE_TRANSFORM_MAT_FN(R, C, _add_, T) \
    ( \
        const xkmat(R, C, T)* a, \
        const xkmat(R, C, T)* b \
    ) \
    { \
        xkmat(R, C, T) r; \
        int i, j; \
        for (i = 0; i < (R); ++i) \
        { \
            for (j = 0; j < (C); ++j) \
                r.arr[i][j] = a->arr[i][j] + b->arr[i][j]; \
        } \
        return r; \
    } \
    ATTR xkmat(R, C, T) XK_PRIVATE_TRANSFORM_MAT_FN(R, C, _sub_, T) \
    ( \
        const xkmat(R, C, T)* a, \
        const xkmat(R, C, T)* b \
    ) \
    { \
        xkmat(R, C, T) r; \
        int i, j; \
        for (i = 0; i < (R); ++i) \
        { \
            for (j = 0; j < (C); ++j) \
                r.arr[i][j] = a->arr[i][j] - b->arr[i][j]; \
        } \
        return r; \
    } \
    ATTR xkmat(R, C, T) XK_PRIVATE_TRANSFORM_MAT_FN(R, C, _scale_, T) \
    ( \
        const xkmat(R, C, T)* me, \
        T s \
    ) \
    { \
        xkmat(R, C, T) r; \
        int i, j; \
        for (i = 0; i < (R); ++i) \
        { \
            for (j = 0; j < (C); ++j) \
                r.arr[i][j] = me->arr[i][j] * s; \
        } \
        return r; \
    } \
    ATTR xkmat(R, C, T) XK_PRIVATE_TRANSFORM_MAT_FN(R, C, _negate_, T) \
    ( \
        const xkmat(R, C, T)* me \
    ) \
    { \
        xkmat(R, C, T) r; \
        int i, j; \
        for (i = 0; i < (R); ++i) \
        { \
            for (j = 0; j < (C); ++j) \
                r.arr[i][j] = -me->arr[i][j]; \
        } \
        return r; \
    } \
    ATTR xkmat(C, R, T) XK_PRIVATE_TRANSFORM_MAT_FN(R, C, _transpose_, T) \
    ( \
        const xkmat(R, C, T)* me \
    ) \
    { \
        xkmat(C, R, T) r; \
        int i, j; \
        for (i = 0; i < (R); ++i) \
        { \
            for (j = 0; j < (C); ++j) \
                r.arr[j][i] = me->arr[i][j]; \
        } \
        return r; \
    } \
    ATTR xkvec(C, T) XK_PRIVATE_TRANSFORM_MAT_FN(R, C, _mulvec_, T) \
    ( \
        const xkmat(R, C, T)* me, \
        xkvec(R, T) v \
    ) \
    { \
        xkvec(C, T) r; \
        int i, j; \
        for (j = 0; j < (C); ++j) \
        { \
            T s = (T)0; \
            for (i = 0; i < (R); ++i) \
                s += v.arr[i] * me->arr[i][j]; \
            r.arr[j] = s; \
        } \
        return r; \
    } \
    ATTR xkvec(R, T) XK_PRIVATE_TRANSFORM_MAT_FN(R, C, _vecmul_, T) \
    ( \
        const xkmat(R, C, T)* me, \
        xkvec(C, T) v \
    ) \
    { \
        xkvec(R, T) r; \
        int i, j; \
        for (i = 0; i < (R); ++i) \
        { \
            T s = (T)0; \
            for (j = 0; j < (C); ++j) \
                s += me->arr[i][j] * v.arr[j]; \
            r.arr[i] = s; \
        } \
        return r; \
    }

#define XK_PRIVATE_TRANSFORM_MAT_SQUARE_IMPL(N, T, ATTR) \
    ATTR xkmat(N, N, T) XK_PRIVATE_TRANSFORM_MAT_FN(N, N, _identity_, T)(void) \
    { \
        xkmat(N, N, T) r; \
        int i, j; \
        for (i = 0; i < (N); ++i) \
        { \
            for (j = 0; j < (N); ++j) \
                r.arr[i][j] = (i == j) ? (T)1 : (T)0; \
        } \
        return r; \
    }

#define XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(R, C, K, T, ATTR) \
    ATTR xkmat(R, K, T) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_FN(R, C, K, T) \
    ( \
        const xkmat(R, C, T)* a, \
        const xkmat(C, K, T)* b \
    ) \
    { \
        xkmat(R, K, T) r; \
        int i, j, k; \
        for (i = 0; i < (R); ++i) \
        { \
            for (j = 0; j < (K); ++j) \
            { \
                T s = (T)0; \
                for (k = 0; k < (C); ++k) \
                    s += a->arr[i][k] * b->arr[k][j]; \
                r.arr[i][j] = s; \
            } \
        } \
        return r; \
    }

// MARK: det inverse
#define XK_PRIVATE_TRANSFORM_MAT_DETINV_IMPL(N, T, ATTR, EPS, FABS) \
    ATTR T XK_PRIVATE_TRANSFORM_MAT_FN(N, N, _det_, T)(const xkmat(N, N, T)* me) \
    { \
        T a[N][N]; \
        T d = (T)1; \
        int i, j, col; \
        for (i = 0; i < (N); ++i) \
        { \
            for (j = 0; j < (N); ++j) \
                a[i][j] = me->arr[i][j]; \
        } \
        for (col = 0; col < (N); ++col) \
        { \
            int pivot = col; \
            T best = FABS(a[col][col]); \
            for (i = col + 1; i < (N); ++i) \
            { \
                T v = FABS(a[i][col]); \
                if (v > best) \
                { \
                    best = v; \
                    pivot = i; \
                } \
            } \
            if (best <= (T)EPS) \
                return (T)0; \
            if (pivot != col) \
            { \
                for (j = 0; j < (N); ++j) \
                { \
                    T t = a[col][j]; \
                    a[col][j] = a[pivot][j]; \
                    a[pivot][j] = t; \
                } \
                d = -d; \
            } \
            d *= a[col][col]; \
            for (i = col + 1; i < (N); ++i) \
            { \
                T factor = a[i][col] / a[col][col]; \
                if (factor == (T)0) \
                    continue; \
                for (j = col; j < (N); ++j) \
                    a[i][j] -= factor * a[col][j]; \
            } \
        } \
        return d; \
    } \
    ATTR xkmat(N, N, T) XK_PRIVATE_TRANSFORM_MAT_FN(N, N, _inverse_, T) \
    ( \
        const xkmat(N, N, T)* me \
    ) \
    { \
        T a[N][2 * (N)]; \
        xkmat(N, N, T) r; \
        int i, j, col; \
        for (i = 0; i < (N); ++i) \
        { \
            for (j = 0; j < (N); ++j) \
            { \
                a[i][j] = me->arr[i][j]; \
                a[i][j + (N)] = (i == j) ? (T)1 : (T)0; \
            } \
        } \
        for (col = 0; col < (N); ++col) \
        { \
            int pivot = col; \
            T best = FABS(a[col][col]); \
            T inv; \
            for (i = col + 1; i < (N); ++i) \
            { \
                T v = FABS(a[i][col]); \
                if (v > best) \
                { \
                    best = v; \
                    pivot = i; \
                } \
            } \
            if (best <= (T)EPS) \
                return XK_PRIVATE_TRANSFORM_MAT_FN(N, N, _zero_, T)(); \
            if (pivot != col) \
            { \
                for (j = 0; j < 2 * (N); ++j) \
                { \
                    T t = a[col][j]; \
                    a[col][j] = a[pivot][j]; \
                    a[pivot][j] = t; \
                } \
            } \
            inv = (T)1 / a[col][col]; \
            for (j = 0; j < 2 * (N); ++j) \
                a[col][j] *= inv; \
            for (i = 0; i < (N); ++i) \
            { \
                T factor; \
                if (i == col) \
                    continue; \
                factor = a[i][col]; \
                if (factor == (T)0) \
                    continue; \
                for (j = 0; j < 2 * (N); ++j) \
                    a[i][j] -= factor * a[col][j]; \
            } \
        } \
        for (i = 0; i < (N); ++i) \
        { \
            for (j = 0; j < (N); ++j) \
                r.arr[i][j] = a[i][j + (N)]; \
        } \
        return r; \
    }

// MARK: instantiate
#define XK_PRIVATE_TRANSFORM_INSTALL_MAT(T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_COMMON_IMPL(2, 2, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_COMMON_IMPL(2, 3, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_COMMON_IMPL(2, 4, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_COMMON_IMPL(3, 2, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_COMMON_IMPL(3, 3, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_COMMON_IMPL(3, 4, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_COMMON_IMPL(4, 2, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_COMMON_IMPL(4, 3, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_COMMON_IMPL(4, 4, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_SQUARE_IMPL(2, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_SQUARE_IMPL(3, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_SQUARE_IMPL(4, T, ATTR)

#define XK_PRIVATE_TRANSFORM_INSTALL_MAT_MUL(T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(2, 2, 2, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(2, 2, 3, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(2, 2, 4, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(2, 3, 2, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(2, 3, 3, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(2, 3, 4, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(2, 4, 2, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(2, 4, 3, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(2, 4, 4, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(3, 2, 2, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(3, 2, 3, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(3, 2, 4, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(3, 3, 2, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(3, 3, 3, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(3, 3, 4, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(3, 4, 2, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(3, 4, 3, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(3, 4, 4, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(4, 2, 2, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(4, 2, 3, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(4, 2, 4, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(4, 3, 2, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(4, 3, 3, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(4, 3, 4, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(4, 4, 2, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(4, 4, 3, T, ATTR) \
    XK_PRIVATE_TRANSFORM_MAT_MUL_IMPL(4, 4, 4, T, ATTR)

#define XK_PRIVATE_TRANSFORM_INSTALL_MAT_DETINV(T, ATTR, EPS, FABS) \
    XK_PRIVATE_TRANSFORM_MAT_DETINV_IMPL(2, T, ATTR, EPS, FABS) \
    XK_PRIVATE_TRANSFORM_MAT_DETINV_IMPL(3, T, ATTR, EPS, FABS) \
    XK_PRIVATE_TRANSFORM_MAT_DETINV_IMPL(4, T, ATTR, EPS, FABS)

XK_PRIVATE_TRANSFORM_INSTALL_MAT(float, static inline)
XK_PRIVATE_TRANSFORM_INSTALL_MAT(double, static inline)
XK_PRIVATE_TRANSFORM_INSTALL_MAT_MUL(float, static inline)
XK_PRIVATE_TRANSFORM_INSTALL_MAT_MUL(double, static inline)
XK_PRIVATE_TRANSFORM_INSTALL_MAT_DETINV(float, static inline, 1e-6f, fabsf)
XK_PRIVATE_TRANSFORM_INSTALL_MAT_DETINV(double, static inline, 1e-12, fabs)

#endif
