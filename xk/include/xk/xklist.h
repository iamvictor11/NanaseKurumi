// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_XKLIST_H
#define XK_XKLIST_H

#include "xkconf.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef XK_CAT
#define XK_CAT_(a, b)   a##b
#define XK_CAT(a, b)    XK_CAT_(a, b)
#endif

#define XK_PRIVATE_LIST_NAME(NAME, T, NODE) \
    XK_CAT(XK_CAT(NAME, T), XK_CAT(_, NODE))

#define xklist(T, NODE)             XK_PRIVATE_LIST_NAME(xk_DETAIL_list_, T, NODE)
#define xklistinit(T, NODE)         XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_init_, T, NODE)
#define xklistfree(T, NODE)         XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_free_, T, NODE)
#define xklistclear(T, NODE)        XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_clear_, T, NODE)
#define xklistpushfront(T, NODE)    XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_pushfront_, T, NODE)
#define xklistpushback(T, NODE)     XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_pushback_, T, NODE)
#define xklistinsertbefore(T, NODE) XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_insertbefore_, T, NODE)
#define xklistinsertafter(T, NODE)  XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_insertafter_, T, NODE)
#define xklistpopfront(T, NODE)     XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_popfront_, T, NODE)
#define xklistpopback(T, NODE)      XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_popback_, T, NODE)
#define xklisterase(T, NODE)        XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_erase_, T, NODE)
#define xklistfront(T, NODE)        XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_front_, T, NODE)
#define xklistfront_const(T, NODE)  XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_front_const_, T, NODE)
#define xklistback(T, NODE)         XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_back_, T, NODE)
#define xklistback_const(T, NODE)   XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_back_const_, T, NODE)
#define xklistnext(T, NODE)         XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_next_, T, NODE)
#define xklistnext_const(T, NODE)   XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_next_const_, T, NODE)
#define xklistprev(T, NODE)         XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_prev_, T, NODE)
#define xklistprev_const(T, NODE)   XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_prev_const_, T, NODE)
#define xklistconcat(T, NODE)       XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_concat_, T, NODE)
#define xklistmove(T, NODE)         XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_move_, T, NODE)
#define xklistswap(T, NODE)         XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_swap_, T, NODE)
#define xklistreverse(T, NODE)      XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_reverse_, T, NODE)
#define xklistcontains(T, NODE)     XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_contains_, T, NODE)
#define xklistsize(T, NODE)         XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_size_, T, NODE)
#define xklistempty(T, NODE)        XK_PRIVATE_LIST_NAME(xk_PUBLIC_list_empty_, T, NODE)

typedef struct xklistnode
{
    struct xklistnode* prev;
    struct xklistnode* next;
} xklistnode;

static inline void xklistheadinit(xklistnode* me)
{
    me->prev = NULL;
    me->next = NULL;
}

#define xklistentry(T, NODE, PTR) \
    ((T*)((char*)(PTR) - offsetof(T, NODE)))
#define xklistentry_const(T, NODE, PTR) \
    ((const T*)((const char*)(PTR) - offsetof(T, NODE)))

// MARK: inst
#define xklistinst(T, NODE) \
    struct xklist(T, NODE) \
    { \
        xklistnode* head; \
        xklistnode* tail; \
        size_t size; \
    };

// MARK: decl
#define xklistdecl(T, NODE, ATTR) \
    struct xklist(T, NODE); \
    typedef struct xklist(T, NODE) xklist(T, NODE); \
    ATTR void xklistinit(T, NODE)(xklist(T, NODE)* me); \
    ATTR void xklistfree(T, NODE)(xklist(T, NODE)* me); \
    ATTR void xklistclear(T, NODE)(xklist(T, NODE)* me); \
    ATTR void xklistpushfront(T, NODE)(xklist(T, NODE)* me, T* e); \
    ATTR void xklistpushback(T, NODE)(xklist(T, NODE)* me, T* e); \
    ATTR void xklistinsertbefore(T, NODE)(xklist(T, NODE)* me, T* pos, T* e); \
    ATTR void xklistinsertafter(T, NODE)(xklist(T, NODE)* me, T* pos, T* e); \
    ATTR T* xklistpopfront(T, NODE)(xklist(T, NODE)* me); \
    ATTR T* xklistpopback(T, NODE)(xklist(T, NODE)* me); \
    ATTR void xklisterase(T, NODE)(xklist(T, NODE)* me, T* e); \
    ATTR T* xklistfront(T, NODE)(xklist(T, NODE)* me); \
    ATTR const T* xklistfront_const(T, NODE)(const xklist(T, NODE)* me); \
    ATTR T* xklistback(T, NODE)(xklist(T, NODE)* me); \
    ATTR const T* xklistback_const(T, NODE)(const xklist(T, NODE)* me); \
    ATTR T* xklistnext(T, NODE)(T* e); \
    ATTR const T* xklistnext_const(T, NODE)(const T* e); \
    ATTR T* xklistprev(T, NODE)(T* e); \
    ATTR const T* xklistprev_const(T, NODE)(const T* e); \
    ATTR void xklistconcat(T, NODE)(xklist(T, NODE)* me, xklist(T, NODE)* other); \
    ATTR void xklistmove(T, NODE)(xklist(T, NODE)* dst, xklist(T, NODE)* src); \
    ATTR void xklistswap(T, NODE)(xklist(T, NODE)* a, xklist(T, NODE)* b); \
    ATTR void xklistreverse(T, NODE)(xklist(T, NODE)* me); \
    ATTR int xklistcontains(T, NODE)(const xklist(T, NODE)* me, const T* e); \
    ATTR size_t xklistsize(T, NODE)(const xklist(T, NODE)* me); \
    ATTR int xklistempty(T, NODE)(const xklist(T, NODE)* me);

// MARK: impl
#define xklistimpl(T, NODE, ATTR) \
    ATTR void xklistinit(T, NODE)(xklist(T, NODE)* me) \
    { \
        me->head = NULL; \
        me->tail = NULL; \
        me->size = 0; \
    } \
    ATTR void xklistclear(T, NODE)(xklist(T, NODE)* me) \
    { \
        xklistnode* n = me->head; \
        while (n) \
        { \
            xklistnode* next = n->next; \
            n->prev = NULL; \
            n->next = NULL; \
            n = next; \
        } \
        me->head = NULL; \
        me->tail = NULL; \
        me->size = 0; \
    } \
    ATTR void xklistfree(T, NODE)(xklist(T, NODE)* me) \
    { \
        xklistclear(T, NODE)(me); \
    } \
    ATTR void xklistpushfront(T, NODE)(xklist(T, NODE)* me, T* e) \
    { \
        xkassert(e != NULL); \
        xklistnode* n = &e->NODE; \
        n->prev = NULL; \
        n->next = me->head; \
        if (me->head) me->head->prev = n; \
        else me->tail = n; \
        me->head = n; \
        ++me->size; \
    } \
    ATTR void xklistpushback(T, NODE)(xklist(T, NODE)* me, T* e) \
    { \
        xkassert(e != NULL); \
        xklistnode* n = &e->NODE; \
        n->prev = me->tail; \
        n->next = NULL; \
        if (me->tail) me->tail->next = n; \
        else me->head = n; \
        me->tail = n; \
        ++me->size; \
    } \
    ATTR void xklistinsertbefore(T, NODE)(xklist(T, NODE)* me, T* pos, T* e) \
    { \
        xkassert(pos != NULL); \
        xkassert(e != NULL); \
        xklistnode* p = &pos->NODE; \
        xklistnode* n = &e->NODE; \
        n->prev = p->prev; \
        n->next = p; \
        if (p->prev) p->prev->next = n; \
        else me->head = n; \
        p->prev = n; \
        ++me->size; \
    } \
    ATTR void xklistinsertafter(T, NODE)(xklist(T, NODE)* me, T* pos, T* e) \
    { \
        xkassert(pos != NULL); \
        xkassert(e != NULL); \
        xklistnode* p = &pos->NODE; \
        xklistnode* n = &e->NODE; \
        n->prev = p; \
        n->next = p->next; \
        if (p->next) p->next->prev = n; \
        else me->tail = n; \
        p->next = n; \
        ++me->size; \
    } \
    ATTR T* xklistpopfront(T, NODE)(xklist(T, NODE)* me) \
    { \
        if (!me->head) return NULL; \
        xkassert(me->size > 0); \
        xklistnode* n = me->head; \
        me->head = n->next; \
        if (me->head) me->head->prev = NULL; \
        else me->tail = NULL; \
        n->prev = NULL; \
        n->next = NULL; \
        --me->size; \
        return xklistentry(T, NODE, n); \
    } \
    ATTR T* xklistpopback(T, NODE)(xklist(T, NODE)* me) \
    { \
        if (!me->tail) return NULL; \
        xkassert(me->size > 0); \
        xklistnode* n = me->tail; \
        me->tail = n->prev; \
        if (me->tail) me->tail->next = NULL; \
        else me->head = NULL; \
        n->prev = NULL; \
        n->next = NULL; \
        --me->size; \
        return xklistentry(T, NODE, n); \
    } \
    ATTR void xklisterase(T, NODE)(xklist(T, NODE)* me, T* e) \
    { \
        xkassert(e != NULL); \
        xkassert(me->size > 0); \
        xklistnode* n = &e->NODE; \
        if (n->prev) n->prev->next = n->next; \
        else me->head = n->next; \
        if (n->next) n->next->prev = n->prev; \
        else me->tail = n->prev; \
        n->prev = NULL; \
        n->next = NULL; \
        --me->size; \
    } \
    ATTR T* xklistfront(T, NODE)(xklist(T, NODE)* me) \
    { \
        return me->head ? xklistentry(T, NODE, me->head) : NULL; \
    } \
    ATTR const T* xklistfront_const(T, NODE)(const xklist(T, NODE)* me) \
    { \
        return me->head ? xklistentry_const(T, NODE, me->head) : NULL; \
    } \
    ATTR T* xklistback(T, NODE)(xklist(T, NODE)* me) \
    { \
        return me->tail ? xklistentry(T, NODE, me->tail) : NULL; \
    } \
    ATTR const T* xklistback_const(T, NODE)(const xklist(T, NODE)* me) \
    { \
        return me->tail ? xklistentry_const(T, NODE, me->tail) : NULL; \
    } \
    ATTR T* xklistnext(T, NODE)(T* e) \
    { \
        return e && e->NODE.next ? xklistentry(T, NODE, e->NODE.next) : NULL; \
    } \
    ATTR const T* xklistnext_const(T, NODE)(const T* e) \
    { \
        return e && e->NODE.next ? xklistentry_const(T, NODE, e->NODE.next) : NULL; \
    } \
    ATTR T* xklistprev(T, NODE)(T* e) \
    { \
        return e && e->NODE.prev ? xklistentry(T, NODE, e->NODE.prev) : NULL; \
    } \
    ATTR const T* xklistprev_const(T, NODE)(const T* e) \
    { \
        return e && e->NODE.prev ? xklistentry_const(T, NODE, e->NODE.prev) : NULL; \
    } \
    ATTR void xklistconcat(T, NODE)(xklist(T, NODE)* me, xklist(T, NODE)* other) \
    { \
        if (me == other || other->size == 0) return; \
        if (me->size == 0) \
        { \
            me->head = other->head; \
            me->tail = other->tail; \
            me->size = other->size; \
        } \
        else \
        { \
            me->tail->next = other->head; \
            other->head->prev = me->tail; \
            me->tail = other->tail; \
            me->size += other->size; \
        } \
        other->head = NULL; \
        other->tail = NULL; \
        other->size = 0; \
    } \
    ATTR void xklistmove(T, NODE)(xklist(T, NODE)* dst, xklist(T, NODE)* src) \
    { \
        if (dst == src) return; \
        xklistclear(T, NODE)(dst); \
        dst->head = src->head; \
        dst->tail = src->tail; \
        dst->size = src->size; \
        xklistinit(T, NODE)(src); \
    } \
    ATTR void xklistswap(T, NODE)(xklist(T, NODE)* a, xklist(T, NODE)* b) \
    { \
        xklist(T, NODE) tmp = *a; \
        *a = *b; \
        *b = tmp; \
    } \
    ATTR void xklistreverse(T, NODE)(xklist(T, NODE)* me) \
    { \
        xklistnode* n = me->head; \
        while (n) \
        { \
            xklistnode* next = n->next; \
            n->next = n->prev; \
            n->prev = next; \
            n = next; \
        } \
        xklistnode* tmp = me->head; \
        me->head = me->tail; \
        me->tail = tmp; \
    } \
    ATTR int xklistcontains(T, NODE)(const xklist(T, NODE)* me, const T* e) \
    { \
        if (!e) return 0; \
        const xklistnode* n = me->head; \
        const xklistnode* target = &e->NODE; \
        while (n) \
        { \
            if (n == target) return 1; \
            n = n->next; \
        } \
        return 0; \
    } \
    ATTR size_t xklistsize(T, NODE)(const xklist(T, NODE)* me) \
    { \
        return me->size; \
    } \
    ATTR int xklistempty(T, NODE)(const xklist(T, NODE)* me) \
    { \
        return me->size == 0; \
    }

// MARK: sugar
#define xklistforeach(T, NODE, ME, IT) \
    for (T* IT = xklistfront(T, NODE)(ME); IT != NULL; IT = xklistnext(T, NODE)(IT))
#define xklistforeach_const(T, NODE, ME, IT) \
    for (const T* IT = xklistfront_const(T, NODE)(ME); IT != NULL; IT = xklistnext_const(T, NODE)(IT))
#define xklistrforeach(T, NODE, ME, IT) \
    for (T* IT = xklistback(T, NODE)(ME); IT != NULL; IT = xklistprev(T, NODE)(IT))
#define xklistrforeach_const(T, NODE, ME, IT) \
    for (const T* IT = xklistback_const(T, NODE)(ME); IT != NULL; IT = xklistprev_const(T, NODE)(IT))

#endif
