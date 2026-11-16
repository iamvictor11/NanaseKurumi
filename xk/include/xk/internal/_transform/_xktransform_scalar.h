// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__TRANSFORM__XKTRANSFORM_SCALAR_H
#define XK_INTERNAL__TRANSFORM__XKTRANSFORM_SCALAR_H

#include "_xktransform_common.h"

// MARK: name
#define xkradians(T) XK_CAT(xk_PUBLIC_scalar_radians_, T)
#define xkdegrees(T) XK_CAT(xk_PUBLIC_scalar_degrees_, T)

// MARK: impl
#define XK_PRIVATE_TRANSFORM_SCALAR_IMPL(T, ATTR) \
    ATTR T xkradians(T)(T deg) \
    { \
        return deg * (T)(XK_MATH_PI / 180.0); \
    } \
    ATTR T xkdegrees(T)(T rad) \
    { \
        return rad * (T)(180.0 / XK_MATH_PI); \
    }

// MARK: instantiate
XK_PRIVATE_TRANSFORM_SCALAR_IMPL(float, static inline)
XK_PRIVATE_TRANSFORM_SCALAR_IMPL(double, static inline)

#endif
