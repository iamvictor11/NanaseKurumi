#ifndef NANAKU_CONTAINER_STR_H
#define NANAKU_CONTAINER_STR_H

#include "vector.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

#pragma region Dec
#define NK_DEC_STRING(PREFIX, NAME) \
    NK_DEC_VECTOR(PREFIX, NAME, char) \
    /* 创建 */ \
    PREFIX##NAME PREFIX##NAME##CreateFromCstr(const char* cstr); \
    PREFIX##NAME PREFIX##NAME##CreateFromFormat(const char* format, ...); \
    PREFIX##NAME PREFIX##NAME##CreateFromVFormat(const char* format, va_list args); \
    /* 写入 */ \
    void PREFIX##NAME##AssignFromCstr(PREFIX##NAME me, const char* cstr); \
    void PREFIX##NAME##AssignFromFormat(PREFIX##NAME me, const char* format, ...); \
    void PREFIX##NAME##AssignFromVFormat(PREFIX##NAME me, const char* format, va_list args); \
    void PREFIX##NAME##AppendFromCstr(PREFIX##NAME me, const char* cstr); \
    void PREFIX##NAME##AppendFromFormat(PREFIX##NAME me, const char* format, ...); \
    void PREFIX##NAME##AppendFromVFormat(PREFIX##NAME me, const char* format, va_list args); \
    /* 转换 */ \
    const char* PREFIX##NAME##ToCstr(const PREFIX##NAME me); \
    int PREFIX##NAME##ToInt(const PREFIX##NAME me); \
    float PREFIX##NAME##ToFloat(const PREFIX##NAME me); \
    double PREFIX##NAME##ToDouble(const PREFIX##NAME me); \
    /* 哈希 */ \
    size_t PREFIX##NAME##Hash(const PREFIX##NAME me);
#pragma endregion
#pragma region Def
#define NK_DEF_STRING(PREFIX, NAME) \
    NK_DEF_VECTOR(PREFIX, NAME, char)
#pragma endregion
#pragma region Impl
#define NK_IMPL_STRING(PREFIX, NAME, ALLOCATOR) \
    NK_IMPL_VECTOR(PREFIX, NAME, char, ALLOCATOR) \
    /* 创建 */ \
    PREFIX##NAME PREFIX##NAME##CreateFromCstr(const char* cstr) \
    { \
        PREFIX##NAME me = PREFIX##NAME##Create(NULL); \
        if (me == NULL) return NULL; \
        PREFIX##NAME##AssignFromCstr(me, cstr); \
        return me; \
    } \
    PREFIX##NAME PREFIX##NAME##CreateFromFormat(const char* format, ...) \
    { \
        va_list args; \
        va_start(args, format); \
        PREFIX##NAME me = PREFIX##NAME##CreateFromVFormat(format, args); \
        va_end(args); \
        return me; \
    } \
    PREFIX##NAME PREFIX##NAME##CreateFromVFormat(const char* format, va_list args) \
    { \
        PREFIX##NAME me = PREFIX##NAME##Create(NULL); \
        PREFIX##NAME##AssignFromVFormat(me, format, args); \
        return me; \
    } \
    /* 写入 */ \
    void PREFIX##NAME##AssignFromCstr(PREFIX##NAME me, const char* cstr) \
    { \
        if (cstr != NULL) \
            PREFIX##NAME##Assign(me, strlen(cstr), cstr); \
    } \
    void PREFIX##NAME##AppendFromCstr(PREFIX##NAME me, const char* cstr) \
    { \
        if (cstr != NULL) \
            PREFIX##NAME##Append(me, strlen(cstr), cstr); \
    } \
    void PREFIX##NAME##AssignFromFormat(PREFIX##NAME me, const char* format, ...) \
    { \
        va_list args; \
        va_start(args, format); \
        PREFIX##NAME##AssignFromVFormat(me, format, args); \
        va_end(args); \
    } \
    void PREFIX##NAME##AssignFromVFormat(PREFIX##NAME me, const char* format, va_list args) \
    { \
        if (format == NULL) return; \
        va_list args_copy; \
        va_copy(args_copy, args); \
        int len = vsnprintf(NULL, 0, format, args_copy); \
        va_end(args_copy); \
        if (len < 0) return; \
        PREFIX##NAME##Reserve(me, len + 1); \
        me->size = len; \
        vsnprintf(me->data, len + 1, format, args); \
    } \
    void PREFIX##NAME##AppendFromFormat(PREFIX##NAME me, const char* format, ...) \
    { \
        va_list args; \
        va_start(args, format); \
        PREFIX##NAME##AppendFromVFormat(me, format, args); \
        va_end(args); \
    } \
    void PREFIX##NAME##AppendFromVFormat(PREFIX##NAME me, const char* format, va_list args) \
    { \
        if (format == NULL) return; \
        va_list args_copy; \
        va_copy(args_copy, args); \
        int len = vsnprintf(NULL, 0, format, args_copy); \
        va_end(args_copy); \
        if (len < 0) return; \
        size_t old_size = me->size; \
        PREFIX##NAME##Reserve(me, old_size + len + 1); \
        vsnprintf(me->data + old_size, len + 1, format, args); \
        me->size = old_size + len; \
    } \
    /* 转换 */ \
    const char* PREFIX##NAME##ToCstr(const PREFIX##NAME me) \
    { \
        if (me->data == NULL) return ""; \
        if (me->size == me->capacity) \
            PREFIX##NAME##Reserve(me, me->size + 1); \
        me->data[me->size] = '\0'; \
        return me->data; \
    } \
    int PREFIX##NAME##ToInt(const PREFIX##NAME me) \
    { \
        const char* str = PREFIX##NAME##ToCstr(me); \
        while (isspace((unsigned char)*str)) str++; \
        int sign = 1; \
        if (*str == '+' || *str == '-') \
        { \
            if (*str == '-') sign = -1; \
            str++; \
        } \
        int base = 10; \
        if (*str == '0') \
        { \
            str++; \
            if (*str == 'b' || *str == 'B') \
            { \
                base = 2; \
                str++; \
            } \
            else if (*str == 'o' || *str == 'O') \
            { \
                base = 8; \
                str++; \
            } \
            else if (*str == 'x' || *str == 'X') \
            { \
                base = 16; \
                str++; \
            } \
        } \
        long result = 0; \
        const char* digits = "0123456789ABCDEF"; \
        while (*str) \
        { \
            if (*str == '\'') {str++; continue;} \
            int digit = -1; \
            for (int i = 0; i < base; i++) \
                if (toupper((unsigned char)*str) == digits[i]) \
                { \
                    digit = i; \
                    break; \
                } \
            if (digit == -1) break; \
            result = result * base + digit; \
            str++; \
        } \
        return (int)(result * sign); \
    } \
    float PREFIX##NAME##ToFloat(const PREFIX##NAME me) \
    { \
        return (float)PREFIX##NAME##ToDouble(me);\
    } \
    double PREFIX##NAME##ToDouble(const PREFIX##NAME me) \
    { \
        const char* str = PREFIX##NAME##ToCstr(me); \
        if (str == NULL) return 0.0f; \
        size_t len = strlen(str); \
        char* buf = (char*)malloc(len + 1); \
        if (!buf) return 0.0f; \
        size_t j = 0; \
        for (size_t i = 0; i < len; i++) \
        { \
            if (str[i] == '\'') continue; \
            buf[j++] = str[i]; \
        } \
        buf[j] = '\0'; \
        double val = strtod(buf, NULL); \
        free(buf); \
        return val; \
    } \
    /* 哈希 */ \
    size_t PREFIX##NAME##Hash(const PREFIX##NAME me) \
    { \
        const char* str = PREFIX##NAME##ToCstr(me); \
        size_t hash = 5381; \
        int c; \
        while ((c = *str++) != '\0') \
            hash = ((hash << 5) + hash) + (unsigned char)c; \
        return hash; \
    }
#pragma endregion
#pragma region Sugar
#define NK_STRING_FOREACH(TYPE, CONTAINER, ELEM_PTR_NAME) NK_VECTOR_FOREACH(TYPE, CONTAINER, ELEM_PTR_NAME)
#define NK_STRING_RFOREACH(TYPE, CONTAINER, ELEM_PTR_NAME) NK_VECTOR_RFOREACH(TYPE, CONTAINER, ELEM_PTR_NAME)
#pragma endregion

#endif
