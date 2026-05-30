#ifndef PNX_CONTAINER_ALLOCATOR_H
#define PNX_CONTAINER_ALLOCATOR_H

#include <stddef.h>
#include <stdlib.h>

#define PNX_DEC_ALLOCATOR(ATTR, SPREFIX, LPREFIX) \
    typedef struct LPREFIX##Allocator LPREFIX##Allocator; \
    ATTR void* SPREFIX##AllocatorDefaultMalloc(void* ctx, size_t size); \
    ATTR void* SPREFIX##AllocatorDefaultRealloc(void* ctx, void* ptr, size_t size); \
    ATTR void SPREFIX##AllocatorDefaultFree(void* ctx, void* ptr); \
    ATTR LPREFIX##Allocator SPREFIX##DefaultAllocator(void);
#define PNX_DEF_ALLOCATOR(ATTR, SPREFIX, LPREFIX) \
    typedef struct LPREFIX##Allocator \
    { \
        void* context; \
        void* (*malloc)(void* ctx, size_t size); \
        void* (*realloc)(void* ctx, void* ptr, size_t size); \
        void  (*free)(void* ctx, void* ptr); \
    } LPREFIX##Allocator;
#define PNX_IMPL_ALLOCATOR(ATTR, SPREFIX, LPREFIX) \
    ATTR void* SPREFIX##AllocatorDefaultMalloc(void* ctx, size_t size) \
    { \
        (void)ctx; \
        return malloc(size); \
    } \
    ATTR void* SPREFIX##AllocatorDefaultRealloc(void* ctx, void* ptr, size_t size) \
    { \
        (void)ctx; \
        return realloc(ptr, size); \
    } \
    ATTR void SPREFIX##AllocatorDefaultFree(void* ctx, void* ptr) \
    { \
        (void)ctx; \
        free(ptr); \
    } \
    ATTR LPREFIX##Allocator SPREFIX##DefaultAllocator(void) \
    { \
        LPREFIX##Allocator allocator = \
        { \
            .context = NULL, \
            .malloc = SPREFIX##AllocatorDefaultMalloc, \
            .realloc = SPREFIX##AllocatorDefaultRealloc, \
            .free = SPREFIX##AllocatorDefaultFree \
        }; \
        return allocator; \
    }

#endif
