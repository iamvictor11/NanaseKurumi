// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__XKDIALOG_H
#define XK_INTERNAL__XKDIALOG_H

#include "_xkconf.h"
#include <stddef.h>
#include <stdint.h>

typedef enum xkdialogresult
{
    XK_DIALOG_ERROR = -1,
    XK_DIALOG_OKAY = 0,
    XK_DIALOG_CANCEL = 1
} xkdialogresult;
typedef enum xkdialogflagbits
{
    XK_DIALOG_MULTISELECT = 1u << 0u,
    XK_DIALOG_SHOW_HIDDEN = 1u << 1u
} xkdialogflagbits;
typedef uint32_t xkdialogflags;
typedef struct xkdialogselected
{
    uint32_t pathCount;
    char** paths;
} xkdialogselected;
xkdialogresult xkdialogopen(xkdialogflags flags, const char* filterList, const char* currentPath, xkdialogselected* outSelected);
void xkdialogclose(xkdialogselected selected);
xkdialogresult xkdialogsave(
    xkdialogflags flags,
    const char* filterList,
    const char* defaultName, const char* defaultExt,
    const char* currentPath,
    xkdialogselected* outSelected
);

#endif
