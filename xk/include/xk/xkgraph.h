// SPDX-License-Identifier: MIT
// Copyright (c) 2026 廖宇康(夏空真宇/iamvictor)
// License: MIT (see LICENSE)
#ifndef XK_XKGRAPH_H
#define XK_XKGRAPH_H

#include "xkconf.h"
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

typedef struct xkgraphnode
{
    struct xkgraphnode* prev;
    struct xkgraphnode* next;
} xkgraphnode;

typedef struct xkgraphvertex
{
    xkgraphnode graphlink;
    xkgraphnode* outhead;
    xkgraphnode* outtail;
    xkgraphnode* inhead;
    xkgraphnode* intail;
    size_t outdegree;
    size_t indegree;
    void* graph;
} xkgraphvertex;

typedef struct xkgraphedge
{
    xkgraphnode graphlink;
    xkgraphnode outlink;
    xkgraphnode inlink;
    xkgraphvertex* from;
    xkgraphvertex* to;
    void* graph;
} xkgraphedge;

typedef struct xkgraph
{
    xkgraphnode* vhead;
    xkgraphnode* vtail;
    xkgraphnode* ehead;
    xkgraphnode* etail;
    size_t vertexcount;
    size_t edgecount;
} xkgraph;

// MARK: private
static inline void xk_PRIVATE_graph_list_push(xkgraphnode** head, xkgraphnode** tail, xkgraphnode* n)
{
    n->prev = *tail;
    n->next = NULL;
    if (*tail) (*tail)->next = n;
    else *head = n;
    *tail = n;
}
static inline void xk_PRIVATE_graph_list_remove(xkgraphnode** head, xkgraphnode** tail, xkgraphnode* n)
{
    if (n->prev) n->prev->next = n->next;
    else *head = n->next;
    if (n->next) n->next->prev = n->prev;
    else *tail = n->prev;
    n->prev = NULL;
    n->next = NULL;
}
static inline xkgraphvertex* xk_PRIVATE_graph_vertex_from_node(xkgraphnode* n)
{
    return (xkgraphvertex*)((char*)n - offsetof(xkgraphvertex, graphlink));
}
static inline const xkgraphvertex* xk_PRIVATE_graph_vertex_from_node_const(const xkgraphnode* n)
{
    return (const xkgraphvertex*)((const char*)n - offsetof(xkgraphvertex, graphlink));
}
static inline xkgraphedge* xk_PRIVATE_graph_edge_from_graphlink(xkgraphnode* n)
{
    return (xkgraphedge*)((char*)n - offsetof(xkgraphedge, graphlink));
}
static inline const xkgraphedge* xk_PRIVATE_graph_edge_from_graphlink_const(const xkgraphnode* n)
{
    return (const xkgraphedge*)((const char*)n - offsetof(xkgraphedge, graphlink));
}
static inline xkgraphedge* xk_PRIVATE_graph_edge_from_outlink(xkgraphnode* n)
{
    return (xkgraphedge*)((char*)n - offsetof(xkgraphedge, outlink));
}
static inline const xkgraphedge* xk_PRIVATE_graph_edge_from_outlink_const(const xkgraphnode* n)
{
    return (const xkgraphedge*)((const char*)n - offsetof(xkgraphedge, outlink));
}
static inline xkgraphedge* xk_PRIVATE_graph_edge_from_inlink(xkgraphnode* n)
{
    return (xkgraphedge*)((char*)n - offsetof(xkgraphedge, inlink));
}
static inline const xkgraphedge* xk_PRIVATE_graph_edge_from_inlink_const(const xkgraphnode* n)
{
    return (const xkgraphedge*)((const char*)n - offsetof(xkgraphedge, inlink));
}
static inline void xk_PRIVATE_graph_detach_edge(xkgraphnode** ehead, xkgraphnode** etail, size_t* edgecount, xkgraphedge* e)
{
    xkgraphvertex* from = e->from;
    xkgraphvertex* to = e->to;
    xk_PRIVATE_graph_list_remove(&from->outhead, &from->outtail, &e->outlink);
    --from->outdegree;
    xk_PRIVATE_graph_list_remove(&to->inhead, &to->intail, &e->inlink);
    --to->indegree;
    xk_PRIVATE_graph_list_remove(ehead, etail, &e->graphlink);
    --*edgecount;
    e->from = NULL;
    e->to = NULL;
    e->graph = NULL;
}
static inline void* xk_PRIVATE_graph_offset(void* p, size_t off)
{
    return p ? (void*)((char*)p - off) : NULL;
}

static inline const void* xk_PRIVATE_graph_offset_const(const void* p, size_t off)
{
    return p ? (const void*)((const char*)p - off) : NULL;
}

// MARK: public
static inline void xkgraphinit(xkgraph* me)
{
    me->vhead = NULL;
    me->vtail = NULL;
    me->ehead = NULL;
    me->etail = NULL;
    me->vertexcount = 0;
    me->edgecount = 0;
}
static inline void xkgraphaddvertex(xkgraph* me, xkgraphvertex* v)
{
    xkassert(me != NULL);
    xkassert(v != NULL);
    xkassert(v->graph == NULL);
    v->outhead = NULL;
    v->outtail = NULL;
    v->inhead = NULL;
    v->intail = NULL;
    v->outdegree = 0;
    v->indegree = 0;
    v->graph = me;
    xk_PRIVATE_graph_list_push(&me->vhead, &me->vtail, &v->graphlink);
    ++me->vertexcount;
}
static inline size_t xkgraphremovevertex(xkgraph* me, xkgraphvertex* v)
{
    xkassert(me != NULL);
    xkassert(v != NULL);
    xkassert(v->graph == me);
    size_t removed = 0;
    while (v->outhead)
    {
        xkgraphedge* e = xk_PRIVATE_graph_edge_from_outlink(v->outhead);
        xk_PRIVATE_graph_detach_edge(&me->ehead, &me->etail, &me->edgecount, e);
        ++removed;
    }
    while (v->inhead)
    {
        xkgraphedge* e = xk_PRIVATE_graph_edge_from_inlink(v->inhead);
        xk_PRIVATE_graph_detach_edge(&me->ehead, &me->etail, &me->edgecount, e);
        ++removed;
    }
    xk_PRIVATE_graph_list_remove(&me->vhead, &me->vtail, &v->graphlink);
    v->outhead = NULL;
    v->outtail = NULL;
    v->inhead = NULL;
    v->intail = NULL;
    v->outdegree = 0;
    v->indegree = 0;
    v->graph = NULL;
    --me->vertexcount;
    return removed;
}
static inline void xkgraphaddedge(xkgraph* me, xkgraphvertex* from, xkgraphvertex* to, xkgraphedge* e)
{
    xkassert(me != NULL);
    xkassert(from != NULL);
    xkassert(to != NULL);
    xkassert(e != NULL);
    xkassert(from->graph == me);
    xkassert(to->graph == me);
    xkassert(e->graph == NULL);
    e->from = from;
    e->to = to;
    e->graph = me;
    xk_PRIVATE_graph_list_push(&from->outhead, &from->outtail, &e->outlink);
    ++from->outdegree;
    xk_PRIVATE_graph_list_push(&to->inhead, &to->intail, &e->inlink);
    ++to->indegree;
    xk_PRIVATE_graph_list_push(&me->ehead, &me->etail, &e->graphlink);
    ++me->edgecount;
}
static inline void xkgraphremoveedge(xkgraph* me, xkgraphedge* e)
{
    xkassert(me != NULL);
    xkassert(e != NULL);
    xkassert(e->graph == me);
    xk_PRIVATE_graph_detach_edge(&me->ehead, &me->etail, &me->edgecount, e);
}
static inline int xkgraphcontainsvertex(const xkgraph* me, const xkgraphvertex* v)
{
    if (!me || !v) return 0;
    return v->graph == (const void*)me;
}
static inline int xkgraphcontainsedge(const xkgraph* me, const xkgraphedge* e)
{
    if (!me || !e) return 0;
    return e->graph == (const void*)me;
}
static inline size_t xkgraphvertexcount(const xkgraph* me)
{
    return me->vertexcount;
}
static inline size_t xkgraphedgecount(const xkgraph* me)
{
    return me->edgecount;
}
static inline int xkgraphempty(const xkgraph* me)
{
    return me->vertexcount == 0 && me->edgecount == 0;
}
static inline size_t xkgraphoutdegree(const xkgraphvertex* v)
{
    return v ? v->outdegree : 0;
}
static inline size_t xkgraphindegree(const xkgraphvertex* v)
{
    return v ? v->indegree : 0;
}
static inline size_t xkgraphdegree(const xkgraphvertex* v)
{
    if (!v) return 0;
    size_t d = v->outdegree;
    d += v->indegree;
    return d;
}
static inline xkgraphvertex* xkgraphfirstvertex(xkgraph* me)
{
    xkassert(me != NULL);
    return me->vhead ? xk_PRIVATE_graph_vertex_from_node(me->vhead) : NULL;
}
static inline const xkgraphvertex* xkgraphfirstvertex_const(const xkgraph* me)
{
    xkassert(me != NULL);
    return me->vhead ? xk_PRIVATE_graph_vertex_from_node_const(me->vhead) : NULL;
}
static inline xkgraphvertex* xkgraphnextvertex(xkgraphvertex* v)
{
    return v && v->graphlink.next ? xk_PRIVATE_graph_vertex_from_node(v->graphlink.next) : NULL;
}
static inline const xkgraphvertex* xkgraphnextvertex_const(const xkgraphvertex* v)
{
    return v && v->graphlink.next ? xk_PRIVATE_graph_vertex_from_node_const(v->graphlink.next) : NULL;
}
static inline xkgraphedge* xkgraphfirstedge(xkgraph* me)
{
    xkassert(me != NULL);
    return me->ehead ? xk_PRIVATE_graph_edge_from_graphlink(me->ehead) : NULL;
}
static inline const xkgraphedge* xkgraphfirstedge_const(const xkgraph* me)
{
    xkassert(me != NULL);
    return me->ehead ? xk_PRIVATE_graph_edge_from_graphlink_const(me->ehead) : NULL;
}
static inline xkgraphedge* xkgraphnextedge(xkgraphedge* e)
{
    return e && e->graphlink.next ? xk_PRIVATE_graph_edge_from_graphlink(e->graphlink.next) : NULL;
}
static inline const xkgraphedge* xkgraphnextedge_const(const xkgraphedge* e)
{
    return e && e->graphlink.next ? xk_PRIVATE_graph_edge_from_graphlink_const(e->graphlink.next) : NULL;
}
static inline xkgraphedge* xkgraphfirstoutedge(xkgraphvertex* v)
{
    return v && v->outhead ? xk_PRIVATE_graph_edge_from_outlink(v->outhead) : NULL;
}
static inline const xkgraphedge* xkgraphfirstoutedge_const(const xkgraphvertex* v)
{
    return v && v->outhead ? xk_PRIVATE_graph_edge_from_outlink_const(v->outhead) : NULL;
}
static inline xkgraphedge* xkgraphnextoutedge(xkgraphedge* e)
{
    return e && e->outlink.next ? xk_PRIVATE_graph_edge_from_outlink(e->outlink.next) : NULL;
}
static inline const xkgraphedge* xkgraphnextoutedge_const(const xkgraphedge* e)
{
    return e && e->outlink.next ? xk_PRIVATE_graph_edge_from_outlink_const(e->outlink.next) : NULL;
}
static inline xkgraphedge* xkgraphfirstinedge(xkgraphvertex* v)
{
    return v && v->inhead ? xk_PRIVATE_graph_edge_from_inlink(v->inhead) : NULL;
}
static inline const xkgraphedge* xkgraphfirstinedge_const(const xkgraphvertex* v)
{
    return v && v->inhead ? xk_PRIVATE_graph_edge_from_inlink_const(v->inhead) : NULL;
}
static inline xkgraphedge* xkgraphnextinedge(xkgraphedge* e)
{
    return e && e->inlink.next ? xk_PRIVATE_graph_edge_from_inlink(e->inlink.next) : NULL;
}
static inline const xkgraphedge* xkgraphnextinedge_const(const xkgraphedge* e)
{
    return e && e->inlink.next ? xk_PRIVATE_graph_edge_from_inlink_const(e->inlink.next) : NULL;
}
static inline xkgraphvertex* xkgraphfrom(xkgraphedge* e)
{
    return e ? e->from : NULL;
}
static inline const xkgraphvertex* xkgraphfrom_const(const xkgraphedge* e)
{
    return e ? e->from : NULL;
}
static inline xkgraphvertex* xkgraphto(xkgraphedge* e)
{
    return e ? e->to : NULL;
}
static inline const xkgraphvertex* xkgraphto_const(const xkgraphedge* e)
{
    return e ? e->to : NULL;
}
static inline xkgraphvertex* xkgraphother(xkgraphedge* e, const xkgraphvertex* v)
{
    if (!e || !v) return NULL;
    if (e->from == v) return e->to;
    if (e->to == v) return e->from;
    return NULL;
}
static inline const xkgraphvertex* xkgraphother_const(const xkgraphedge* e, const xkgraphvertex* v)
{
    if (!e || !v) return NULL;
    if (e->from == v) return e->to;
    if (e->to == v) return e->from;
    return NULL;
}
static inline void xkgraphclear(xkgraph* me)
{
    xkassert(me != NULL);
    while (me->ehead)
    {
        xkgraphedge* e = xk_PRIVATE_graph_edge_from_graphlink(me->ehead);
        xk_PRIVATE_graph_detach_edge(&me->ehead, &me->etail, &me->edgecount, e);
    }
    while (me->vhead)
    {
        xkgraphvertex* v = xk_PRIVATE_graph_vertex_from_node(me->vhead);
        xk_PRIVATE_graph_list_remove(&me->vhead, &me->vtail, &v->graphlink);
        v->outhead = NULL;
        v->outtail = NULL;
        v->inhead = NULL;
        v->intail = NULL;
        v->outdegree = 0;
        v->indegree = 0;
        v->graph = NULL;
        --me->vertexcount;
    }
    me->vertexcount = 0;
    me->edgecount = 0;
}
static inline void xkgraphfree(xkgraph* me)
{
    xkgraphclear(me);
}
static inline void xkgraphmove(xkgraph* dst, xkgraph* src)
{
    xkassert(dst != NULL);
    xkassert(src != NULL);
    if (dst == src) return;
    xkgraphclear(dst);
    dst->vhead = src->vhead;
    dst->vtail = src->vtail;
    dst->ehead = src->ehead;
    dst->etail = src->etail;
    dst->vertexcount = src->vertexcount;
    dst->edgecount = src->edgecount;
    for (xkgraphnode* n = dst->vhead; n != NULL; n = n->next)
    {
        xkgraphvertex* v = xk_PRIVATE_graph_vertex_from_node(n);
        v->graph = dst;
    }
    for (xkgraphnode* n = dst->ehead; n != NULL; n = n->next)
    {
        xkgraphedge* e = xk_PRIVATE_graph_edge_from_graphlink(n);
        e->graph = dst;
    }
    xkgraphinit(src);
}
static inline void xkgraphswap(xkgraph* a, xkgraph* b)
{
    xkassert(a != NULL);
    xkassert(b != NULL);
    xkgraph tmp = *a;
    *a = *b;
    *b = tmp;
    for (xkgraphnode* n = a->vhead; n != NULL; n = n->next)
    {
        xkgraphvertex* v = xk_PRIVATE_graph_vertex_from_node(n);
        v->graph = a;
    }
    for (xkgraphnode* n = a->ehead; n != NULL; n = n->next)
    {
        xkgraphedge* e = xk_PRIVATE_graph_edge_from_graphlink(n);
        e->graph = a;
    }
    for (xkgraphnode* n = b->vhead; n != NULL; n = n->next)
    {
        xkgraphvertex* v = xk_PRIVATE_graph_vertex_from_node(n);
        v->graph = b;
    }
    for (xkgraphnode* n = b->ehead; n != NULL; n = n->next)
    {
        xkgraphedge* e = xk_PRIVATE_graph_edge_from_graphlink(n);
        e->graph = b;
    }
}

#define xkgraphvertexhost(V, VNODE, PTR) \
    ((V*)xk_PRIVATE_graph_offset((void*)(PTR), offsetof(V, VNODE)))
#define xkgraphvertexhost_const(V, VNODE, PTR) \
    ((const V*)xk_PRIVATE_graph_offset_const((const void*)(PTR), offsetof(V, VNODE)))
#define xkgraphedgehost(E, ENODE, PTR) \
    ((E*)xk_PRIVATE_graph_offset((void*)(PTR), offsetof(E, ENODE)))
#define xkgraphedgehost_const(E, ENODE, PTR) \
    ((const E*)xk_PRIVATE_graph_offset_const((const void*)(PTR), offsetof(E, ENODE)))

#endif