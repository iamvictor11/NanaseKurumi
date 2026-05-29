#ifndef NANAKU_CONTAINER_ALLOCATOR_H
#define NANAKU_CONTAINER_ALLOCATOR_H

#include <stddef.h>
#include <stdlib.h>

typedef struct nkAllocator
{
    void* context;
    void* (*malloc)(void* ctx, size_t size);
    void* (*realloc)(void* ctx, void* ptr, size_t size);
    void  (*free)(void* ctx, void* ptr);
} nkAllocator;
void* nkAllocatorDefaultMalloc(void* ctx, size_t size)
{
    (void)ctx;
    return malloc(size);
}
void* nkAllocatorDefaultRealloc(void* ctx, void* ptr, size_t size)
{
    (void)ctx;
    return realloc(ptr, size);
}
void nkAllocatorDefaultFree(void* ctx, void* ptr)
{
    (void)ctx;
    free(ptr);
}
#define NK_DEFAULT_ALLOCATOR \
{ \
    .context = NULL, \
    .malloc = nkAllocatorDefaultMalloc, \
    .realloc = nkAllocatorDefaultRealloc, \
    .free = nkAllocatorDefaultFree \
}

#endif
