// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_XKLIST_H
#define XK_XKLIST_H

#include "xkconf.h"
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

typedef struct xklistnode
{
    struct xklistnode* prev;
    struct xklistnode* next;
} xklistnode;

typedef struct xklist
{
    xklistnode* head;
    xklistnode* tail;
    size_t size;
} xklist;

// MARK: private
static inline void* xk_PRIVATE_list_offset(void* p, size_t off)
{
    return p ? (void*)((char*)p - off) : NULL;
}
static inline const void* xk_PRIVATE_list_offset_const(const void* p, size_t off)
{
    return p ? (const void*)((const char*)p - off) : NULL;
}

// MARK: public
static inline void xklistinit(xklist* me)
{
    me->head = NULL;
    me->tail = NULL;
    me->size = 0;
}
static inline void xklistclear(xklist* me)
{
    xkassert(me != NULL);
    xklistnode* n = me->head;
    while (n)
    {
        xklistnode* next = n->next;
        n->prev = NULL;
        n->next = NULL;
        n = next;
    }
    me->head = NULL;
    me->tail = NULL;
    me->size = 0;
}
static inline void xklistfree(xklist* me)
{
    xklistclear(me);
}
static inline void xklistpushfront(xklist* me, xklistnode* n)
{
    xkassert(me != NULL);
    xkassert(n != NULL);
    n->prev = NULL;
    n->next = me->head;
    if (me->head) me->head->prev = n;
    else me->tail = n;
    me->head = n;
    ++me->size;
}
static inline void xklistpushback(xklist* me, xklistnode* n)
{
    xkassert(me != NULL);
    xkassert(n != NULL);
    n->prev = me->tail;
    n->next = NULL;
    if (me->tail) me->tail->next = n;
    else me->head = n;
    me->tail = n;
    ++me->size;
}
static inline void xklistinsertbefore(xklist* me, xklistnode* pos, xklistnode* n)
{
    xkassert(me != NULL);
    xkassert(pos != NULL);
    xkassert(n != NULL);
    n->prev = pos->prev;
    n->next = pos;
    if (pos->prev) pos->prev->next = n;
    else me->head = n;
    pos->prev = n;
    ++me->size;
}
static inline void xklistinsertafter(xklist* me, xklistnode* pos, xklistnode* n)
{
    xkassert(me != NULL);
    xkassert(pos != NULL);
    xkassert(n != NULL);
    n->prev = pos;
    n->next = pos->next;
    if (pos->next) pos->next->prev = n;
    else me->tail = n;
    pos->next = n;
    ++me->size;
}
static inline xklistnode* xklistpopfront(xklist* me)
{
    xkassert(me != NULL);
    if (!me->head) return NULL;
    xkassert(me->size > 0);
    xklistnode* n = me->head;
    me->head = n->next;
    if (me->head) me->head->prev = NULL;
    else me->tail = NULL;
    n->prev = NULL;
    n->next = NULL;
    --me->size;
    return n;
}
static inline xklistnode* xklistpopback(xklist* me)
{
    xkassert(me != NULL);
    if (!me->tail) return NULL;
    xkassert(me->size > 0);
    xklistnode* n = me->tail;
    me->tail = n->prev;
    if (me->tail) me->tail->next = NULL;
    else me->head = NULL;
    n->prev = NULL;
    n->next = NULL;
    --me->size;
    return n;
}
static inline void xklisterase(xklist* me, xklistnode* n)
{
    xkassert(me != NULL);
    xkassert(n != NULL);
    xkassert(me->size > 0);
    if (n->prev) n->prev->next = n->next;
    else me->head = n->next;
    if (n->next) n->next->prev = n->prev;
    else me->tail = n->prev;
    n->prev = NULL;
    n->next = NULL;
    --me->size;
}
static inline xklistnode* xklistfront(xklist* me)
{
    xkassert(me != NULL);
    return me->head;
}
static inline const xklistnode* xklistfront_const(const xklist* me)
{
    xkassert(me != NULL);
    return me->head;
}
static inline xklistnode* xklistback(xklist* me)
{
    xkassert(me != NULL);
    return me->tail;
}
static inline const xklistnode* xklistback_const(const xklist* me)
{
    xkassert(me != NULL);
    return me->tail;
}
static inline xklistnode* xklistnext(xklistnode* n)
{
    return n ? n->next : NULL;
}
static inline const xklistnode* xklistnext_const(const xklistnode* n)
{
    return n ? n->next : NULL;
}
static inline xklistnode* xklistprev(xklistnode* n)
{
    return n ? n->prev : NULL;
}
static inline const xklistnode* xklistprev_const(const xklistnode* n)
{
    return n ? n->prev : NULL;
}
static inline void xklistconcat(xklist* me, xklist* other)
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
        other->head->prev = me->tail;
        me->tail = other->tail;
        me->size += other->size;
    }
    other->head = NULL;
    other->tail = NULL;
    other->size = 0;
}
static inline void xklistmove(xklist* dst, xklist* src)
{
    xkassert(dst != NULL);
    xkassert(src != NULL);
    if (dst == src) return;
    xklistclear(dst);
    dst->head = src->head;
    dst->tail = src->tail;
    dst->size = src->size;
    xklistinit(src);
}
static inline void xklistswap(xklist* a, xklist* b)
{
    xkassert(a != NULL);
    xkassert(b != NULL);
    xklist tmp = *a;
    *a = *b;
    *b = tmp;
}
static inline void xklistreverse(xklist* me)
{
    xkassert(me != NULL);
    xklistnode* n = me->head;
    while (n)
    {
        xklistnode* next = n->next;
        n->next = n->prev;
        n->prev = next;
        n = next;
    }
    xklistnode* tmp = me->head;
    me->head = me->tail;
    me->tail = tmp;
}
static inline int xklistcontains(const xklist* me, const xklistnode* n)
{
    if (!me || !n) return 0;
    const xklistnode* p = me->head;
    while (p)
    {
        if (p == n) return 1;
        p = p->next;
    }
    return 0;
}
static inline size_t xklistsize(const xklist* me)
{
    return me->size;
}
static inline int xklistempty(const xklist* me)
{
    return me->size == 0;
}

#define xklisthost(T, NODE, PTR) \
    ((T*)xk_PRIVATE_list_offset((void*)(PTR), offsetof(T, NODE)))
#define xklisthost_const(T, NODE, PTR) \
    ((const T*)xk_PRIVATE_list_offset_const((const void*)(PTR), offsetof(T, NODE)))

// MARK: sugar
#define xklistforeach(T, NODE, ME, IT) \
    for (T* IT = xklisthost(T, NODE, xklistfront(ME)); IT != NULL; IT = xklisthost(T, NODE, xklistnext(&IT->NODE)))
#define xklistforeach_const(T, NODE, ME, IT) \
    for (const T* IT = xklisthost_const(T, NODE, xklistfront_const(ME)); IT != NULL; IT = xklisthost_const(T, NODE, xklistnext_const(&IT->NODE)))
#define xklistrforeach(T, NODE, ME, IT) \
    for (T* IT = xklisthost(T, NODE, xklistback(ME)); IT != NULL; IT = xklisthost(T, NODE, xklistprev(&IT->NODE)))
#define xklistrforeach_const(T, NODE, ME, IT) \
    for (const T* IT = xklisthost_const(T, NODE, xklistback_const(ME)); IT != NULL; IT = xklisthost_const(T, NODE, xklistprev_const(&IT->NODE)))

#endif