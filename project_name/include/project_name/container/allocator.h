#ifndef PNX_CONTAINER_ALLOCATOR_H
#define PNX_CONTAINER_ALLOCATOR_H

#include <stddef.h>
#include <stdlib.h>

typedef struct pnxAllocator
{
    void* context;
    void* (*malloc)(void* ctx, size_t size);
    void* (*realloc)(void* ctx, void* ptr, size_t size);
    void  (*free)(void* ctx, void* ptr);
} pnxAllocator;
void* pnxAllocatorDefaultMalloc(void* ctx, size_t size)
{
    (void)ctx;
    return malloc(size);
}
void* pnxAllocatorDefaultRealloc(void* ctx, void* ptr, size_t size)
{
    (void)ctx;
    return realloc(ptr, size);
}
void pnxAllocatorDefaultFree(void* ctx, void* ptr)
{
    (void)ctx;
    free(ptr);
}
#define PNX_DEFAULT_ALLOCATOR \
{ \
    .context = NULL, \
    .malloc = pnxAllocatorDefaultMalloc, \
    .realloc = pnxAllocatorDefaultRealloc, \
    .free = pnxAllocatorDefaultFree \
}

#endif
