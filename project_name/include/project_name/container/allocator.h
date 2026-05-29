#ifndef PN_CONTAINER_ALLOCATOR_H
#define PN_CONTAINER_ALLOCATOR_H

#include <stddef.h>
#include <stdlib.h>

typedef struct pn_Allocator
{
    void* context;
    void* (*malloc)(void* ctx, size_t size);
    void* (*realloc)(void* ctx, void* ptr, size_t size);
    void  (*free)(void* ctx, void* ptr);
} pn_Allocator;
void* pn_AllocatorDefaultMalloc(void* ctx, size_t size)
{
    (void)ctx;
    return malloc(size);
}
void* pn_AllocatorDefaultRealloc(void* ctx, void* ptr, size_t size)
{
    (void)ctx;
    return realloc(ptr, size);
}
void pn_AllocatorDefaultFree(void* ctx, void* ptr)
{
    (void)ctx;
    free(ptr);
}
#define PN_DEFAULT_ALLOCATOR \
{ \
    .context = NULL, \
    .malloc = pn_AllocatorDefaultMalloc, \
    .realloc = pn_AllocatorDefaultRealloc, \
    .free = pn_AllocatorDefaultFree \
}

#endif
