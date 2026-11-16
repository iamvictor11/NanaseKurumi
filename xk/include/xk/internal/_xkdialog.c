// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__XKDIALOG_C
#define XK_INTERNAL__XKDIALOG_C

#include "_xkdialog.h"
#include "_xkerror.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// MARK: windows
#if defined(_WIN32)
#include <windows.h>
#include <commdlg.h>
#include <wchar.h>

#ifndef OFN_FORCESHOWHIDDEN
#define OFN_FORCESHOWHIDDEN 0x10000000
#endif

static wchar_t* xkdialogopen_utf8_to_wide(const char* s)
{
    int len;
    wchar_t* out;

    if (s == NULL) return NULL;
    len = MultiByteToWideChar(CP_UTF8, 0, s, -1, NULL, 0);
    if (len <= 0) return NULL;
    out = (wchar_t*)malloc((size_t)len * sizeof(wchar_t));
    if (out == NULL) return NULL;
    if (MultiByteToWideChar(CP_UTF8, 0, s, -1, out, len) <= 0)
    {
        free(out);
        return NULL;
    }
    return out;
}
static char* xkdialogopen_wide_to_utf8(const wchar_t* s)
{
    int len;
    char* out;

    if (s == NULL) return NULL;
    len = WideCharToMultiByte(CP_UTF8, 0, s, -1, NULL, 0, NULL, NULL);
    if (len <= 0) return NULL;
    out = (char*)malloc((size_t)len);
    if (out == NULL) return NULL;
    if (WideCharToMultiByte(CP_UTF8, 0, s, -1, out, len, NULL, NULL) <= 0)
    {
        free(out);
        return NULL;
    }
    return out;
}
static wchar_t* xkdialogopen_build_win32_filter(const char* filterList)
{
    static const wchar_t kAll[] = L"All Files\0*.*\0\0";
    wchar_t* wide, *out;
    size_t i, wideLen;

    if (filterList == NULL || filterList[0] == '\0')
    {
        out = (wchar_t*)malloc(sizeof(kAll));
        if (out != NULL) memcpy(out, kAll, sizeof(kAll));
        return out;
    }

    wide = xkdialogopen_utf8_to_wide(filterList);
    if (wide == NULL) return NULL;

    wideLen = wcslen(wide);
    out = (wchar_t*)malloc((wideLen + 2) * sizeof(wchar_t));
    if (out == NULL)
    {
        free(wide);
        return NULL;
    }

    for (i = 0; i < wideLen; ++i)
        out[i] = (wide[i] == L'|') ? L'\0' : wide[i];
    out[wideLen] = L'\0';
    out[wideLen + 1] = L'\0';

    free(wide);
    return out;
}
static xkdialogresult xkdialogopen_parse(const wchar_t* buffer, xkdialogselected* out)
{
    const wchar_t* p = buffer;
    size_t firstLen = wcslen(p);
    size_t i;

    if (firstLen == 0)
    {
        xkpusherror("xkdialogopen: dialog returned empty path!");
        return XK_DIALOG_ERROR;
    }

    if (p[firstLen + 1] == L'\0')
    {
        char** paths = (char**)malloc(sizeof(char*));
        if (paths == NULL)
        {
            xkpusherror("xkdialogopen: out of memory!");
            return XK_DIALOG_ERROR;
        }

        paths[0] = xkdialogopen_wide_to_utf8(p);
        if (paths[0] == NULL)
        {
            free(paths);
            xkpusherror("xkdialogopen: out of memory!");
            return XK_DIALOG_ERROR;
        }

        out->paths = paths;
        out->pathCount = 1;
        return XK_DIALOG_OKAY;
    }
    else
    {
        const wchar_t* dir = p;
        size_t dirLen = firstLen;
        bool dirHasSep = (dir[dirLen - 1] == L'\\' || dir[dirLen - 1] == L'/');
        const wchar_t* q;
        uint32_t count = 0;
        char** paths;

        for (q = buffer + dirLen + 1; *q != L'\0'; q += wcslen(q) + 1)
            ++count;

        if (count == 0)
        {
            xkpusherror("xkdialogopen: dialog returned empty selection!");
            return XK_DIALOG_ERROR;
        }

        paths = (char**)malloc(count * sizeof(char*));
        if (paths == NULL)
        {
            xkpusherror("xkdialogopen: out of memory!");
            return XK_DIALOG_ERROR;
        }

        q = buffer + dirLen + 1;
        for (i = 0; i < count; ++i)
        {
            size_t nameLen = wcslen(q);
            size_t total = dirLen + (dirHasSep ? 0u : 1u) + nameLen + 1u;
            wchar_t* full = (wchar_t*)malloc(total * sizeof(wchar_t));
            size_t pos;

            if (full == NULL)
            {
                xkpusherror("xkdialogopen: out of memory!");
                goto fail;
            }

            memcpy(full, dir, dirLen * sizeof(wchar_t));
            pos = dirLen;
            if (!dirHasSep) full[pos++] = L'\\';
            memcpy(full + pos, q, (nameLen + 1) * sizeof(wchar_t));

            paths[i] = xkdialogopen_wide_to_utf8(full);
            free(full);
            if (paths[i] == NULL)
            {
                xkpusherror("xkdialogopen: out of memory!");
                goto fail;
            }
            q += nameLen + 1;
        }

        out->paths = paths;
        out->pathCount = count;
        return XK_DIALOG_OKAY;

    fail:
        while (i > 0)
            free(paths[--i]);
        free(paths);
        return XK_DIALOG_ERROR;
    }
}

xkdialogresult xkdialogopen(xkdialogflags flags, const char* filterList, const char* currentPath, xkdialogselected* outSelected)
{
    OPENFILENAMEW ofn;
    wchar_t* winFilter = NULL;
    wchar_t* winCurrentPath = NULL;
    wchar_t* buffer = NULL;
    DWORD bufSize = 65536;
    DWORD baseFlags;
    bool multi;
    xkdialogresult result = XK_DIALOG_ERROR;

    if (outSelected == NULL)
    {
        xkpusherror("xkdialogopen: invalid output!");
        return XK_DIALOG_ERROR;
    }
    outSelected->pathCount = 0;
    outSelected->paths = NULL;

    multi = (flags & XK_DIALOG_MULTISELECT) != 0;

    baseFlags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR | OFN_EXPLORER;
    if (multi) baseFlags |= OFN_ALLOWMULTISELECT;
    if (flags & XK_DIALOG_SHOW_HIDDEN) baseFlags |= OFN_FORCESHOWHIDDEN;

    winFilter = xkdialogopen_build_win32_filter(filterList);
    if (winFilter == NULL)
    {
        xkpusherror("xkdialogopen: out of memory!");
        goto cleanup;
    }

    if (currentPath != NULL && currentPath[0] != '\0')
        winCurrentPath = xkdialogopen_utf8_to_wide(currentPath);

    buffer = (wchar_t*)malloc((size_t)bufSize * sizeof(wchar_t));
    if (buffer == NULL)
    {
        xkpusherror("xkdialogopen: out of memory!");
        goto cleanup;
    }

    for (;;)
    {
        BOOL ok;
        DWORD err;

        memset(buffer, 0, (size_t)bufSize * sizeof(wchar_t));

        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrFilter = winFilter;
        ofn.nFilterIndex = 1;
        ofn.lpstrFile = buffer;
        ofn.nMaxFile = bufSize;
        ofn.lpstrInitialDir = winCurrentPath;
        ofn.Flags = baseFlags;

        ok = GetOpenFileNameW(&ofn);
        if (ok)
        {
            result = xkdialogopen_parse(buffer, outSelected);
            goto cleanup;
        }

        err = CommDlgExtendedError();
        if (err == 0)
        {
            result = XK_DIALOG_CANCEL;
            goto cleanup;
        }

        if (multi && err == FNERR_BUFFERTOOSMALL)
        {
            WORD needed = 0;
            DWORD newSize;
            wchar_t* nb;

            memcpy(&needed, buffer, sizeof(needed));
            newSize = (DWORD)needed;
            if (newSize <= bufSize) newSize = bufSize * 2;
            if (newSize > 4u * 1024u * 1024u)
            {
                xkpusherror("xkdialogopen: selection too large!");
                goto cleanup;
            }

            nb = (wchar_t*)realloc(buffer, (size_t)newSize * sizeof(wchar_t));
            if (nb == NULL)
            {
                xkpusherror("xkdialogopen: out of memory!");
                goto cleanup;
            }
            buffer = nb;
            bufSize = newSize;
            continue;
        }

        xkpusherror("xkdialogopen: GetOpenFileName failed!");
        goto cleanup;
    }

cleanup:
    free(buffer);
    free(winCurrentPath);
    free(winFilter);
    return result;
}
xkdialogresult xkdialogsave(
    xkdialogflags flags,
    const char* filterList,
    const char* defaultName, const char* defaultExt,
    const char* currentPath,
    xkdialogselected* outSelected
)
{
    OPENFILENAMEW ofn;
    wchar_t* winFilter = NULL;
    wchar_t* winCurrentPath = NULL;
    wchar_t* winDefaultName = NULL;
    wchar_t* winDefExt = NULL;
    wchar_t* buffer = NULL;
    DWORD bufSize = 65536;
    DWORD baseFlags;
    xkdialogresult result = XK_DIALOG_ERROR;

    if (outSelected == NULL)
    {
        xkpusherror("xkdialogsave: invalid output!");
        return XK_DIALOG_ERROR;
    }
    outSelected->pathCount = 0;
    outSelected->paths = NULL;

    baseFlags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR | OFN_EXPLORER;
    if (flags & XK_DIALOG_SHOW_HIDDEN) baseFlags |= OFN_FORCESHOWHIDDEN;

    winFilter = xkdialogopen_build_win32_filter(filterList);
    if (winFilter == NULL)
    {
        xkpusherror("xkdialogsave: out of memory!");
        goto cleanup;
    }

    if (currentPath != NULL && currentPath[0] != '\0')
        winCurrentPath = xkdialogopen_utf8_to_wide(currentPath);
    if (defaultExt != NULL && defaultExt[0] != '\0')
        winDefExt = xkdialogopen_utf8_to_wide(defaultExt);
    if (defaultName != NULL && defaultName[0] != '\0')
        winDefaultName = xkdialogopen_utf8_to_wide(defaultName);

    buffer = (wchar_t*)malloc((size_t)bufSize * sizeof(wchar_t));
    if (buffer == NULL)
    {
        xkpusherror("xkdialogsave: out of memory!");
        goto cleanup;
    }
    memset(buffer, 0, (size_t)bufSize * sizeof(wchar_t));

    if (winDefaultName != NULL)
    {
        size_t len = wcslen(winDefaultName);
        if (len >= bufSize) len = bufSize - 1;
        memcpy(buffer, winDefaultName, len * sizeof(wchar_t));
        buffer[len] = L'\0';
    }

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = winFilter;
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = buffer;
    ofn.nMaxFile = bufSize;
    ofn.lpstrInitialDir = winCurrentPath;
    ofn.lpstrDefExt = winDefExt;
    ofn.Flags = baseFlags;

    if (GetSaveFileNameW(&ofn))
    {
        char* path;
        char** paths;

        if (buffer[0] == L'\0')
        {
            xkpusherror("xkdialogsave: dialog returned empty path!");
            goto cleanup;
        }

        path = xkdialogopen_wide_to_utf8(buffer);
        if (path == NULL)
        {
            xkpusherror("xkdialogsave: out of memory!");
            goto cleanup;
        }

        paths = (char**)malloc(sizeof(char*));
        if (paths == NULL)
        {
            free(path);
            xkpusherror("xkdialogsave: out of memory!");
            goto cleanup;
        }
        paths[0] = path;

        outSelected->paths = paths;
        outSelected->pathCount = 1;
        result = XK_DIALOG_OKAY;
    }
    else
    {
        DWORD err = CommDlgExtendedError();
        if (err == 0)
        {
            result = XK_DIALOG_CANCEL;
        }
        else
        {
            xkpusherror("xkdialogsave: GetSaveFileName failed!");
            result = XK_DIALOG_ERROR;
        }
    }

cleanup:
    free(buffer);
    free(winCurrentPath);
    free(winDefaultName);
    free(winDefExt);
    free(winFilter);
    return result;
}
void xkdialogclose(xkdialogselected selected)
{
    uint32_t i;
    if (selected.paths == NULL) return;
    for (i = 0; i < selected.pathCount; ++i)
        free(selected.paths[i]);
    free(selected.paths);
}

// MARK: linux
#elif defined(__linux__)

xkdialogresult xkdialogopen(xkdialogflags flags, const char* filterList, const char* currentPath, xkdialogselected* outSelected)
{
    (void)flags; (void)filterList; (void)currentPath;
    if (outSelected != NULL)
    {
        outSelected->pathCount = 0;
        outSelected->paths = NULL;
    }
    xkpusherror("xkdialogopen: this platform is not supported!");
    return XK_DIALOG_ERROR;
}
xkdialogresult xkdialogsave(
    xkdialogflags flags,
    const char* filterList,
    const char* defaultName, const char* defaultExt,
    const char* currentPath,
    xkdialogselected* outSelected
)
{
    (void)flags; (void)filterList; (void)defaultName; (void)defaultExt; (void)currentPath;
    if (outSelected != NULL)
    {
        outSelected->pathCount = 0;
        outSelected->paths = NULL;
    }
    xkpusherror("xkdialogsave: this platform is not supported!");
    return XK_DIALOG_ERROR;
}
void xkdialogclose(xkdialogselected selected)
{
    (void)selected;
}

// MARK: macOS
#elif defined(__APPLE__) && defined(__MACH__)

xkdialogresult xkdialogopen(xkdialogflags flags, const char* filterList, const char* currentPath, xkdialogselected* outSelected)
{
    (void)flags; (void)filterList; (void)currentPath;
    if (outSelected != NULL)
    {
        outSelected->pathCount = 0;
        outSelected->paths = NULL;
    }
    xkpusherror("xkdialogopen: this platform is not supported!");
    return XK_DIALOG_ERROR;
}
xkdialogresult xkdialogsave(
    xkdialogflags flags,
    const char* filterList,
    const char* defaultName, const char* defaultExt,
    const char* currentPath,
    xkdialogselected* outSelected
)
{
    (void)flags; (void)filterList; (void)defaultName; (void)defaultExt; (void)currentPath;
    if (outSelected != NULL)
    {
        outSelected->pathCount = 0;
        outSelected->paths = NULL;
    }
    xkpusherror("xkdialogsave: this platform is not supported!");
    return XK_DIALOG_ERROR;
}
void xkdialogclose(xkdialogselected selected)
{
    (void)selected;
}

#endif

#endif
