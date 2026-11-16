// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__TRANSFORM__XKTRANSFORM_COMMON_H
#define XK_INTERNAL__TRANSFORM__XKTRANSFORM_COMMON_H

#include "../_xkconf.h"
#include "../_xkmath.h"
#include <stddef.h>
#include <stdbool.h>
#include <math.h>

// MARK: name
#ifndef XK_CAT
#define XK_CAT_(a, b)   a##b
#define XK_CAT(a, b)    XK_CAT_(a, b)
#endif

// A##B##_##C
#define XK_PRIVATE_TRANSFORM_NAME(A, B, C) \
    XK_CAT(XK_CAT(A, B), XK_CAT(_, C))
// A##B##C##D
#define XK_PRIVATE_TRANSFORM_NAME4(A, B, C, D) \
    XK_CAT(XK_CAT(A, B), XK_CAT(C, D))
// 2x3 from R and C
#define XK_PRIVATE_TRANSFORM_RC(R, C) \
    XK_CAT(XK_CAT(R, x), C)

// xk_PUBLIC_vec3_add_float from N, _add_ and T
#define XK_PRIVATE_TRANSFORM_VEC_FN(N, OP, T) \
    XK_PRIVATE_TRANSFORM_NAME4(xk_PUBLIC_vec, N, OP, T)
// xk_PUBLIC_mat3x4_add_float from R, C, _add_ and T
#define XK_PRIVATE_TRANSFORM_MAT_FN(R, C, OP, T) \
    XK_PRIVATE_TRANSFORM_NAME4(xk_PUBLIC_mat, XK_PRIVATE_TRANSFORM_RC(R, C), OP, T)
// xk_PUBLIC_mat3x4_mul_4x2_float from R, C, K and T
#define XK_PRIVATE_TRANSFORM_MAT_MUL_FN(R, C, K, T) \
    XK_CAT \
    ( \
        XK_CAT \
        ( \
            XK_PRIVATE_TRANSFORM_NAME4 \
            ( \
                xk_PUBLIC_mat, \
                XK_PRIVATE_TRANSFORM_RC(R, C), \
                _mul_, \
                XK_PRIVATE_TRANSFORM_RC(C, K) \
            ), \
            _ \
        ), \
        T \
    )
#endif
