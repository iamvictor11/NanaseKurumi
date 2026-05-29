#ifndef PN_CONTAINER_LIST_H
#define PN_CONTAINER_LIST_H

#include "allocator.h"
#include <stdbool.h>
#include <stddef.h>

#pragma region Dec
#define PN_DEC_LIST(PREFIX, NAME, TYPE) \
    typedef struct TYPE TYPE; \
	typedef struct PREFIX##NAME##Def PREFIX##NAME##Def; \
	typedef struct PREFIX##NAME##_T PREFIX##NAME##_T; \
	typedef PREFIX##NAME##_T* PREFIX##NAME; \
	typedef struct PREFIX##NAME##Node PREFIX##NAME##Node; \
	typedef void(*PREFIX##NAME##Signal)(const PREFIX##NAME container, TYPE* element); \
	typedef bool(*PREFIX##NAME##Equalor)(const TYPE* curr, const TYPE* goal); \
	typedef bool(*PREFIX##NAME##RemoveIfCallback)(const TYPE* curr); \
	typedef void(*PREFIX##NAME##ForeachCallback)(TYPE* curr); \
	/* 创建销毁 */ \
	PREFIX##NAME PREFIX##NAME##Create(const PREFIX##NAME##Def* def); \
	void PREFIX##NAME##Destroy(PREFIX##NAME me); \
	/* 访问 */ \
	TYPE* PREFIX##NAME##Front(PREFIX##NAME me); \
	TYPE* PREFIX##NAME##Back(PREFIX##NAME me); \
	/* 属性 */ \
	size_t PREFIX##NAME##Size(PREFIX##NAME me); \
	bool PREFIX##NAME##Empty(PREFIX##NAME me); \
	/* 增删改 */ \
	size_t PREFIX##NAME##PushFront(PREFIX##NAME me, TYPE* element); \
	size_t PREFIX##NAME##PushBack(PREFIX##NAME me, TYPE* element); \
	void PREFIX##NAME##PopFront(PREFIX##NAME me); \
	void PREFIX##NAME##PopBack(PREFIX##NAME me); \
	void PREFIX##NAME##InsertAfter(PREFIX##NAME me, TYPE* index, TYPE* element); \
	void PREFIX##NAME##InsertBefore(PREFIX##NAME me, TYPE* index, TYPE* element); \
	void PREFIX##NAME##Erase(PREFIX##NAME me, TYPE* element); \
	TYPE* PREFIX##NAME##Find(PREFIX##NAME me, const TYPE* goal, PREFIX##NAME##Equalor equalor); \
	bool PREFIX##NAME##Contains(PREFIX##NAME me, const TYPE* goal, PREFIX##NAME##Equalor equalor); \
	/* 批处理 */ \
	void PREFIX##NAME##Foreach(PREFIX##NAME me, PREFIX##NAME##ForeachCallback processor); \
	void PREFIX##NAME##RForeach(PREFIX##NAME me, PREFIX##NAME##ForeachCallback processor); \
	void PREFIX##NAME##RemoveIf(PREFIX##NAME me, PREFIX##NAME##RemoveIfCallback predicate); \
	void PREFIX##NAME##Clear(PREFIX##NAME me); \
	/* 交换 */ \
	void PREFIX##NAME##Swap(PREFIX##NAME me, PREFIX##NAME other);
#pragma endregion
#pragma region Def
#define PN_DEF_LIST(PREFIX, NAME, TYPE) \
	typedef struct PREFIX##NAME##Def \
	{ \
		PREFIX##NAME##Signal insertSignal; \
		PREFIX##NAME##Signal removeSignal; \
	} PREFIX##NAME##Def; \
	PREFIX##NAME##Def PREFIX##Null##NAME##Def() \
	{ \
		PREFIX##NAME##Def def; \
		def.insertSignal = NULL; \
		def.removeSignal = NULL; \
		return def; \
	}; \
	typedef struct PREFIX##NAME##Node \
	{ \
		TYPE* next; \
		TYPE* prev; \
	} PREFIX##NAME##Node; \
	typedef struct PREFIX##NAME##_T \
	{ \
		TYPE* head; \
		TYPE* tail; \
		size_t size; \
		PREFIX##NAME##Signal insertSignal; \
		PREFIX##NAME##Signal removeSignal; \
	} PREFIX##NAME##_T;
#pragma endregion
#pragma region Impl
#define PN_IMPL_LIST(PREFIX, NAME, TYPE, NODE_NAME, ALLOCATOR) \
	static inline PREFIX##NAME##Node* PREFIX##NAME##_GetNode(TYPE* e) { return &((e)->NODE_NAME); } \
	/* 创建销毁 */ \
	PREFIX##NAME PREFIX##NAME##Create(const PREFIX##NAME##Def* def) \
	{ \
		PREFIX##NAME me = (PREFIX##NAME)(ALLOCATOR)->malloc((ALLOCATOR)->context, sizeof(PREFIX##NAME##_T)); \
		if (me == NULL) return NULL; \
		me->head = NULL; \
		me->tail = NULL; \
		me->size = 0; \
		me->insertSignal = def ? def->insertSignal : NULL; \
		me->removeSignal = def ? def->removeSignal : NULL; \
		return me; \
	} \
	void PREFIX##NAME##Destroy(PREFIX##NAME me) \
	{ \
		PREFIX##NAME##Clear(me); \
		(ALLOCATOR)->free((ALLOCATOR)->context, me); \
	} \
	/* 访问 */ \
	TYPE* PREFIX##NAME##Front(PREFIX##NAME me) { return me->head; } \
	TYPE* PREFIX##NAME##Back(PREFIX##NAME me) { return me->tail; } \
	/* 属性 */ \
	size_t PREFIX##NAME##Size(PREFIX##NAME me) { return me->size; } \
	bool PREFIX##NAME##Empty(PREFIX##NAME me) { return me->size == 0; } \
	/* 增删改 */ \
	size_t PREFIX##NAME##PushFront(PREFIX##NAME me, TYPE* element) \
	{ \
		PREFIX##NAME##Node* n = PREFIX##NAME##_GetNode(element); \
		n->prev = NULL; \
		n->next = me->head; \
		if (me->head) PREFIX##NAME##_GetNode(me->head)->prev = element; \
		me->head = element; \
		if (me->tail == NULL) me->tail = element; \
		me->size += 1; \
		if (me->insertSignal) me->insertSignal(me, element); \
		return me->size - 1; \
	} \
	size_t PREFIX##NAME##PushBack(PREFIX##NAME me, TYPE* element) \
	{ \
		PREFIX##NAME##Node* n = PREFIX##NAME##_GetNode(element); \
		n->next = NULL; \
		n->prev = me->tail; \
		if (me->tail) PREFIX##NAME##_GetNode(me->tail)->next = element; \
		me->tail = element; \
		if (me->head == NULL) me->head = element; \
		me->size += 1; \
		if (me->insertSignal) me->insertSignal(me, element); \
		return me->size - 1; \
	} \
	void PREFIX##NAME##PopFront(PREFIX##NAME me) \
	{ \
		if (me->head == NULL) return; \
		TYPE* old = me->head; \
		TYPE* next = PREFIX##NAME##_GetNode(old)->next; \
		if (me->removeSignal) me->removeSignal(me, old); \
		if (next) PREFIX##NAME##_GetNode(next)->prev = NULL; \
		me->head = next; \
		if (me->head == NULL) me->tail = NULL; \
		me->size -= 1; \
	} \
	void PREFIX##NAME##PopBack(PREFIX##NAME me) \
	{ \
		if (me->tail == NULL) return; \
		TYPE* old = me->tail; \
		TYPE* prev = PREFIX##NAME##_GetNode(old)->prev; \
		if (me->removeSignal) me->removeSignal(me, old); \
		if (prev) PREFIX##NAME##_GetNode(prev)->next = NULL; \
		me->tail = prev; \
		if (me->tail == NULL) me->head = NULL; \
		me->size -= 1; \
	} \
	void PREFIX##NAME##InsertAfter(PREFIX##NAME me, TYPE* index, TYPE* element) \
	{ \
		if (index == NULL) { PREFIX##NAME##PushFront(me, element); return; } \
		if (index == me->tail) { PREFIX##NAME##PushBack(me, element); return; } \
		TYPE* next = PREFIX##NAME##_GetNode(index)->next; \
		PREFIX##NAME##_GetNode(element)->prev = index; \
		PREFIX##NAME##_GetNode(element)->next = next; \
		PREFIX##NAME##_GetNode(index)->next = element; \
		PREFIX##NAME##_GetNode(next)->prev = element; \
		me->size += 1; \
		if (me->insertSignal) me->insertSignal(me, element); \
	} \
	void PREFIX##NAME##InsertBefore(PREFIX##NAME me, TYPE* index, TYPE* element) \
	{ \
		if (index == NULL) { PREFIX##NAME##PushBack(me, element); return; } \
		if (index == me->head) { PREFIX##NAME##PushFront(me, element); return; } \
		TYPE* prev = PREFIX##NAME##_GetNode(index)->prev; \
		PREFIX##NAME##_GetNode(element)->next = index; \
		PREFIX##NAME##_GetNode(element)->prev = prev; \
		PREFIX##NAME##_GetNode(prev)->next = element; \
		PREFIX##NAME##_GetNode(index)->prev = element; \
		me->size += 1; \
		if (me->insertSignal) me->insertSignal(me, element); \
	} \
	void PREFIX##NAME##Erase(PREFIX##NAME me, TYPE* element) \
	{ \
		if (element == NULL) return; \
		TYPE* prev = PREFIX##NAME##_GetNode(element)->prev; \
		TYPE* next = PREFIX##NAME##_GetNode(element)->next; \
		if (me->removeSignal) me->removeSignal(me, element); \
		if (prev) PREFIX##NAME##_GetNode(prev)->next = next; \
		if (next) PREFIX##NAME##_GetNode(next)->prev = prev; \
		if (me->head == element) me->head = next; \
		if (me->tail == element) me->tail = prev; \
		PREFIX##NAME##_GetNode(element)->next = NULL; \
		PREFIX##NAME##_GetNode(element)->prev = NULL; \
		me->size -= 1; \
	} \
	TYPE* PREFIX##NAME##Find(PREFIX##NAME me, const TYPE* goal, PREFIX##NAME##Equalor equalor) \
	{ \
		for (TYPE* it = me->head; it != NULL; it = PREFIX##NAME##_GetNode(it)->next) \
			if (equalor(it, goal)) return it; \
		return NULL; \
	} \
	bool PREFIX##NAME##Contains(PREFIX##NAME me, const TYPE* goal, PREFIX##NAME##Equalor equalor) \
	{ \
		return PREFIX##NAME##Find(me, goal, equalor) != NULL; \
	} \
	/* 批处理 */ \
	void PREFIX##NAME##Foreach(PREFIX##NAME me, PREFIX##NAME##ForeachCallback processor) \
	{ \
		for (TYPE* it = me->head; it != NULL; it = PREFIX##NAME##_GetNode(it)->next) processor(it); \
	} \
	void PREFIX##NAME##RForeach(PREFIX##NAME me, PREFIX##NAME##ForeachCallback processor) \
	{ \
		for (TYPE* it = me->tail; it != NULL; it = PREFIX##NAME##_GetNode(it)->prev) processor(it); \
	} \
	void PREFIX##NAME##RemoveIf(PREFIX##NAME me, PREFIX##NAME##RemoveIfCallback predicate) \
	{ \
		TYPE* it = me->head; \
		while (it != NULL) \
		{ \
			TYPE* next = PREFIX##NAME##_GetNode(it)->next; \
			if (predicate(it)) PREFIX##NAME##Erase(me, it); \
			it = next; \
		} \
	} \
	void PREFIX##NAME##Clear(PREFIX##NAME me) \
	{ \
		TYPE* it = me->head; \
		while (it != NULL) \
		{ \
			TYPE* next = PREFIX##NAME##_GetNode(it)->next; \
			if (me->removeSignal) me->removeSignal(me, it); \
			PREFIX##NAME##_GetNode(it)->next = NULL; \
			PREFIX##NAME##_GetNode(it)->prev = NULL; \
			it = next; \
		} \
		me->head = NULL; \
		me->tail = NULL; \
		me->size = 0; \
	} \
	/* 交换 */ \
	void PREFIX##NAME##Swap(PREFIX##NAME me, PREFIX##NAME other) \
	{ \
		TYPE* t_head = me->head; \
		TYPE* t_tail = me->tail; \
		size_t t_size = me->size; \
		PREFIX##NAME##Signal t_ins = me->insertSignal; \
		PREFIX##NAME##Signal t_rem = me->removeSignal; \
		me->head = other->head; me->tail = other->tail; me->size = other->size; me->insertSignal = other->insertSignal; me->removeSignal = other->removeSignal; \
		other->head = t_head; other->tail = t_tail; other->size = t_size; other->insertSignal = t_ins; other->removeSignal = t_rem; \
	}
#pragma endregion
#pragma region Sugar
#define PN_LIST_FOREACH(TYPE, NODE_NAME, CONTAINER, ELEM_PTR_NAME) \
	for (TYPE* ELEM_PTR_NAME = (CONTAINER)->head; ELEM_PTR_NAME != NULL; ELEM_PTR_NAME = (ELEM_PTR_NAME)->NODE_NAME.next)
#define PN_LIST_RFOREACH(TYPE, NODE_NAME, CONTAINER, ELEM_PTR_NAME) \
	for (TYPE* ELEM_PTR_NAME = (CONTAINER)->tail; ELEM_PTR_NAME != NULL; ELEM_PTR_NAME = (ELEM_PTR_NAME)->NODE_NAME.prev)
#pragma endregion

#endif
