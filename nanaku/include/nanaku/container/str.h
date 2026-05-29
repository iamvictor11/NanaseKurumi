#ifndef NANAKU_CONTAINER_STR_H
#define NANAKU_CONTAINER_STR_H

#include "vector.h"
#include <ctype.h>

#define NK_DEC_STRING(PREFIX, NAME) \
    NK_DEC_VECTOR(PREFIX, NAME, char) \
    const char* PREFIX##NAME##ToCstr(const PREFIX##NAME me); \
    int PREFIX##NAME##ToInt(const PREFIX##NAME me); \
    float PREFIX##NAME##ToFloat(const PREFIX##NAME me); \
    double PREFIX##NAME##ToDouble(const PREFIX##NAME me); \
    size_t PREFIX##NAME##Hash(const PREFIX##NAME me);

#define NK_DEF_STRING(PREFIX, NAME) \
    NK_DEF_VECTOR(PREFIX, NAME, char)

#define NK_IMPL_STRING(PREFIX, NAME, ALLOCATOR) \
    NK_IMPL_VECTOR(PREFIX, NAME, char, ALLOCATOR) \
    const char* PREFIX##NAME##ToCstr(const PREFIX##NAME me) \
    { \
        if (me == NULL || me->data == NULL) return ""; \
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
            else \
            { \
                base = 8; \
                str--; \
            } \
        } \
        long result = 0; \
        const char* digits = "0123456789ABCDEF"; \
        while (*str) \
        { \
            if (*str == '\'') str++; continue; \
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
    size_t PREFIX##NAME##Hash(const PREFIX##NAME me) \
    { \
        const char* str = PREFIX##NAME##ToCstr(me); \
        size_t hash = 5381; \
        int c; \
        while ((c = *str++) != '\0') \
            hash = ((hash << 5) + hash) + (unsigned char)c; \
        return hash; \
    }

#endif
