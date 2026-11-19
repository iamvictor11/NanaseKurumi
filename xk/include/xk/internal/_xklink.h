// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_INTERNAL__XKLINK_H
#define XK_INTERNAL__XKLINK_H

#include "_xkconf.h"
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

typedef struct xklinknode
{
    struct xklinknode* next;
} xklinknode;

typedef struct xklink
{
    xklinknode* head;
    xklinknode* tail;
    size_t size;
} xklink;

// MARK: private
static inline void* xk_PRIVATE_link_offset(void* p, size_t off)
{
    return p ? (void*)((char*)p - off) : NULL;
}
static inline const void* xk_PRIVATE_link_offset_const(const void* p, size_t off)
{
    return p ? (const void*)((const char*)p - off) : NULL;
}

// MARK: public
static inline void xklinkinit(xklink* me)
{
    me->head = NULL;
    me->tail = NULL;
    me->size = 0;
}
static inline void xklinkclear(xklink* me)
{
    xkassert(me != NULL);
    xklinknode* n = me->head;
    while (n)
    {
        xklinknode* next = n->next;
        n->next = NULL;
        n = next;
    }
    me->head = NULL;
    me->tail = NULL;
    me->size = 0;
}
static inline void xklinkfree(xklink* me)
{
    xklinkclear(me);
}
static inline void xklinkpushfront(xklink* me, xklinknode* n)
{
    xkassert(me != NULL);
    xkassert(n != NULL);
    n->next = me->head;
    if (!me->head) me->tail = n;
    me->head = n;
    ++me->size;
}
static inline void xklinkpushback(xklink* me, xklinknode* n)
{
    xkassert(me != NULL);
    xkassert(n != NULL);
    n->next = NULL;
    if (me->tail) me->tail->next = n;
    else me->head = n;
    me->tail = n;
    ++me->size;
}
static inline void xklinkinsertbefore(xklink* me, xklinknode* pos, xklinknode* n)
{
    xkassert(me != NULL);
    xkassert(pos != NULL);
    xkassert(n != NULL);
    if (me->head == pos)
    {
        n->next = pos;
        me->head = n;
    }
    else
    {
        xklinknode* prev = me->head;
        while (prev != NULL && prev->next != pos) prev = prev->next;
        xkassert(prev != NULL);
        n->next = pos;
        prev->next = n;
    }
    ++me->size;
}
static inline void xklinkinsertafter(xklink* me, xklinknode* pos, xklinknode* n)
{
    xkassert(me != NULL);
    xkassert(pos != NULL);
    xkassert(n != NULL);
    n->next = pos->next;
    pos->next = n;
    if (me->tail == pos) me->tail = n;
    ++me->size;
}
static inline xklinknode* xklinkpopfront(xklink* me)
{
    xkassert(me != NULL);
    if (!me->head) return NULL;
    xkassert(me->size > 0);
    xklinknode* n = me->head;
    me->head = n->next;
    if (!me->head) me->tail = NULL;
    n->next = NULL;
    --me->size;
    return n;
}
static inline xklinknode* xklinkpopback(xklink* me)
{
    xkassert(me != NULL);
    if (!me->head) return NULL;
    xkassert(me->size > 0);
    xklinknode* n;
    if (me->head == me->tail)
    {
        n = me->head;
        me->head = NULL;
        me->tail = NULL;
    }
    else
    {
        xklinknode* prev = me->head;
        while (prev->next != me->tail) prev = prev->next;
        n = me->tail;
        prev->next = NULL;
        me->tail = prev;
    }
    n->next = NULL;
    --me->size;
    return n;
}
static inline void xklinkerase(xklink* me, xklinknode* n)
{
    xkassert(me != NULL);
    xkassert(n != NULL);
    xkassert(me->size > 0);
    if (me->head == n)
    {
        me->head = n->next;
        if (me->tail == n) me->tail = NULL;
    }
    else
    {
        xklinknode* prev = me->head;
        while (prev != NULL && prev->next != n) prev = prev->next;
        xkassert(prev != NULL);
        prev->next = n->next;
        if (me->tail == n) me->tail = prev;
    }
    n->next = NULL;
    --me->size;
}
static inline xklinknode* xklinkfront(xklink* me)
{
    xkassert(me != NULL);
    return me->head;
}
static inline const xklinknode* xklinkfront_const(const xklink* me)
{
    xkassert(me != NULL);
    return me->head;
}
static inline xklinknode* xklinkback(xklink* me)
{
    xkassert(me != NULL);
    return me->tail;
}
static inline const xklinknode* xklinkback_const(const xklink* me)
{
    xkassert(me != NULL);
    return me->tail;
}
static inline xklinknode* xklinknext(xklinknode* n)
{
    return n ? n->next : NULL;
}
static inline const xklinknode* xklinknext_const(const xklinknode* n)
{
    return n ? n->next : NULL;
}
static inline void xklinkconcat(xklink* me, xklink* other)
{
    xkassert(me != NULL);
    xkassert(other != NULL);
    if (me == other || other->size == 0) return;
    if (me->size == 0)
    {
        me->head = other->head;
        me->tail = other->tail;
        me->size = other->size;
    }
    else
    {
        me->tail->next = other->head;
        me->tail = other->tail;
        me->size += other->size;
    }
    other->head = NULL;
    other->tail = NULL;
    other->size = 0;
}
static inline void xklinkmove(xklink* dst, xklink* src)
{
    xkassert(dst != NULL);
    xkassert(src != NULL);
    if (dst == src) return;
    xklinkclear(dst);
    dst->head = src->head;
    dst->tail = src->tail;
    dst->size = src->size;
    xklinkinit(src);
}
static inline void xklinkswap(xklink* a, xklink* b)
{
    xkassert(a != NULL);
    xkassert(b != NULL);
    xklink tmp = *a;
    *a = *b;
    *b = tmp;
}
static inline void xklinkreverse(xklink* me)
{
    xkassert(me != NULL);
    xklinknode* prev = NULL;
    xklinknode* n = me->head;
    me->tail = me->head;
    while (n)
    {
        xklinknode* next = n->next;
        n->next = prev;
        prev = n;
        n = next;
    }
    me->head = prev;
}
static inline int xklinkcontains(const xklink* me, const xklinknode* n)
{
    if (!me || !n) return 0;
    const xklinknode* p = me->head;
    while (p)
    {
        if (p == n) return 1;
        p = p->next;
    }
    return 0;
}
static inline size_t xklinksize(const xklink* me)
{
    return me->size;
}
static inline int xklinkempty(const xklink* me)
{
    return me->size == 0;
}

#define xklinkhost(T, NODE, PTR) \
    ((T*)xk_PRIVATE_link_offset((void*)(PTR), offsetof(T, NODE)))
#define xklinkhost_const(T, NODE, PTR) \
    ((const T*)xk_PRIVATE_link_offset_const((const void*)(PTR), offsetof(T, NODE)))

// MARK: sugar
#define xklinkforeach(T, NODE, ME, IT) \
    for (T* IT = xklinkhost(T, NODE, xklinkfront(ME)); IT != NULL; IT = xklinkhost(T, NODE, xklinknext(&IT->NODE)))
#define xklinkforeach_const(T, NODE, ME, IT) \
    for (const T* IT = xklinkhost_const(T, NODE, xklinkfront_const(ME)); IT != NULL; IT = xklinkhost_const(T, NODE, xklinknext_const(&IT->NODE)))

#endif
