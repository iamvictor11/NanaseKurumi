#ifndef NANAKU_CONTAINER_VECTOR_H
#define NANAKU_CONTAINER_VECTOR_H

#include "allocator.h"
#include <stdbool.h>
#include <string.h>

#pragma region Konst
#define NK_VECTOR_GROWTH_FACTOR 2
#pragma endregion
#pragma region Dec
#define NK_DEC_VECTOR(PREFIX, NAME, TYPE) \
    typedef struct PREFIX##NAME##Def PREFIX##NAME##Def; \
    typedef struct PREFIX##NAME##_T PREFIX##NAME##_T; \
    typedef PREFIX##NAME##_T* PREFIX##NAME; \
    /* 回调 */ \
    typedef void(*PREFIX##NAME##Signal)(const PREFIX##NAME container, TYPE* element); \
    typedef bool(*PREFIX##NAME##Equalor)(const TYPE* curr, const TYPE* goal); \
    typedef bool(*PREFIX##NAME##RemoveIfCallback)(const TYPE* curr); \
    typedef void(*PREFIX##NAME##ForeachCallback)(TYPE* curr); \
    typedef int(*PREFIX##NAME##Comparator)(const TYPE* left, const TYPE* right); \
    /* 创建销毁 */ \
    PREFIX##NAME PREFIX##NAME##Create(const PREFIX##NAME##Def* def); \
    PREFIX##NAME PREFIX##NAME##Copy(const PREFIX##NAME src); \
    void PREFIX##NAME##CopyTo(PREFIX##NAME me, const PREFIX##NAME dst); \
    PREFIX##NAME PREFIX##NAME##Move(const PREFIX##NAME src); \
    void PREFIX##NAME##MoveTo(PREFIX##NAME me, const PREFIX##NAME dst); \
    void PREFIX##NAME##Destroy(PREFIX##NAME me); \
    /* 访问 */ \
    TYPE* PREFIX##NAME##At(PREFIX##NAME me, size_t index); \
    TYPE* PREFIX##NAME##Front(PREFIX##NAME me); \
    TYPE* PREFIX##NAME##Back(PREFIX##NAME me); \
    TYPE* PREFIX##NAME##Find(PREFIX##NAME me, const TYPE* goal, PREFIX##NAME##Equalor equalor, size_t* out_index); \
    bool PREFIX##NAME##Contains(PREFIX##NAME me, const TYPE* goal, PREFIX##NAME##Equalor equalor); \
    /* 属性 */ \
    TYPE* PREFIX##NAME##Data(PREFIX##NAME me); \
    size_t PREFIX##NAME##Size(PREFIX##NAME me); \
    size_t PREFIX##NAME##Capacity(PREFIX##NAME me); \
    /* 状态 */ \
    bool PREFIX##NAME##Empty(PREFIX##NAME me); \
    /* 批处理 */ \
    void PREFIX##NAME##Assign(PREFIX##NAME me, size_t count, const TYPE* elements); \
    void PREFIX##NAME##Append(PREFIX##NAME me, size_t count, const TYPE* elements); \
    void PREFIX##NAME##InsertRange(PREFIX##NAME me, size_t index, size_t count, const TYPE* elements); \
    void PREFIX##NAME##EraseRange(PREFIX##NAME me, size_t index, size_t count); \
    void PREFIX##NAME##RemoveIf(PREFIX##NAME me, PREFIX##NAME##RemoveIfCallback predicate); \
    void PREFIX##NAME##Foreach(PREFIX##NAME me, PREFIX##NAME##ForeachCallback processor); \
    void PREFIX##NAME##RForeach(PREFIX##NAME me, PREFIX##NAME##ForeachCallback processor); \
    /* 排序 */ \
    void PREFIX##NAME##BubbleSort(PREFIX##NAME me, PREFIX##NAME##Comparator comparator); \
    /* 容量 */ \
    void PREFIX##NAME##Reserve(PREFIX##NAME me, size_t capacity); \
    void PREFIX##NAME##Resize(PREFIX##NAME me, size_t size); \
    void PREFIX##NAME##ShrinkToFit(PREFIX##NAME me); \
    void PREFIX##NAME##Clear(PREFIX##NAME me); \
    /* 增删改 */ \
    void PREFIX##NAME##Insert(PREFIX##NAME me, size_t index, const TYPE* element); \
    void PREFIX##NAME##InsertLiteral(PREFIX##NAME me, size_t index, TYPE literal); \
    void PREFIX##NAME##Erase(PREFIX##NAME me, size_t index); \
    size_t PREFIX##NAME##Push(PREFIX##NAME me, const TYPE* element); \
    size_t PREFIX##NAME##PushLiteral(PREFIX##NAME me, TYPE literal); \
    void PREFIX##NAME##Pop(PREFIX##NAME me); \
    void PREFIX##NAME##Set(PREFIX##NAME me, size_t index, const TYPE* element); \
    void PREFIX##NAME##SetLiteral(PREFIX##NAME me, size_t index, TYPE literal); \
    /* 交换 */ \
    void PREFIX##NAME##Swap(PREFIX##NAME me, PREFIX##NAME other);
#pragma endregion
#pragma region Def
#define NK_DEF_VECTOR(PREFIX, NAME, TYPE) \
    typedef struct PREFIX##NAME##Def \
    { \
        size_t size; \
        size_t capacity; \
        TYPE initial; \
        PREFIX##NAME##Signal insertSignal; \
        PREFIX##NAME##Signal removeSignal; \
    } PREFIX##NAME##Def; \
    PREFIX##NAME##Def PREFIX##Null##NAME##Def() \
    { \
        PREFIX##NAME##Def def; \
        def.size = 0; \
        def.capacity = 0; \
        def.insertSignal = NULL; \
        def.removeSignal = NULL; \
        return def; \
    }; \
    typedef struct PREFIX##NAME##_T \
    { \
        TYPE* data; \
        size_t size; \
        size_t capacity; \
        PREFIX##NAME##Signal insertSignal; \
        PREFIX##NAME##Signal removeSignal; \
    } PREFIX##NAME##_T;
#pragma endregion
#pragma region Impl
#define NK_IMPL_VECTOR(PREFIX, NAME, TYPE, ALLOCATOR) \
    /* 创建销毁 */ \
    PREFIX##NAME PREFIX##NAME##Create(const PREFIX##NAME##Def* def) \
    { \
        PREFIX##NAME me = (PREFIX##NAME)(ALLOCATOR)->malloc((ALLOCATOR)->context, sizeof(PREFIX##NAME##_T)); \
        if (me == NULL) return NULL; \
        me->data = NULL; \
        me->size = 0; \
        me->capacity = 0; \
        me->insertSignal = def ? def->insertSignal : NULL; \
        me->removeSignal = def ? def->removeSignal : NULL; \
        if (def && def->capacity > 0) \
            PREFIX##NAME##Reserve(me, def->capacity); \
        if (def && def->size > 0) \
        { \
            if (me->capacity < def->size) \
                PREFIX##NAME##Reserve(me, def->size); \
            for (size_t i = 0; i < def->size; i++) \
            { \
                me->data[i] = def->initial; \
                if (me->insertSignal) me->insertSignal(me, &me->data[i]); \
            } \
            me->size = def->size; \
        } \
        return me; \
    } \
    PREFIX##NAME PREFIX##NAME##Copy(const PREFIX##NAME src) \
    { \
        if (src == NULL) return NULL; \
        PREFIX##NAME me = (PREFIX##NAME)(ALLOCATOR)->malloc((ALLOCATOR)->context, sizeof(PREFIX##NAME##_T)); \
        if (me == NULL) return NULL; \
        me->data = NULL; \
        me->size = 0; \
        me->capacity = 0; \
        me->insertSignal = src->insertSignal; \
        me->removeSignal = src->removeSignal; \
        if (src->capacity > 0) \
            PREFIX##NAME##Reserve(me, src->capacity); \
        if (src->size > 0) \
        { \
            me->size = src->size; \
            for (size_t i = 0; i < src->size; i++) \
                me->data[i] = src->data[i]; \
        } \
        return me; \
    } \
    void PREFIX##NAME##CopyTo(PREFIX##NAME me, const PREFIX##NAME src) \
    { \
        if (src == NULL || me == src) return; \
        PREFIX##NAME##Clear(me); \
        if (src->capacity > 0) \
            PREFIX##NAME##Reserve(me, src->capacity); \
        me->insertSignal = src->insertSignal; \
        me->removeSignal = src->removeSignal; \
        if (src->size > 0) \
            for (size_t i = 0; i < src->size; i++) \
                me->data[i] = src->data[i]; \
        me->size = src->size; \
    } \
    PREFIX##NAME PREFIX##NAME##Move(const PREFIX##NAME src) \
    { \
        if (src == NULL) return NULL; \
        PREFIX##NAME me = (PREFIX##NAME)(ALLOCATOR)->malloc((ALLOCATOR)->context, sizeof(PREFIX##NAME##_T)); \
        if (me == NULL) return NULL; \
        me->data = src->data; \
        me->size = src->size; \
        me->capacity = src->capacity; \
        me->insertSignal = src->insertSignal; \
        me->removeSignal = src->removeSignal; \
        src->data = NULL; \
        src->size = 0; \
        src->capacity = 0; \
        src->insertSignal = NULL; \
        src->removeSignal = NULL; \
        return me; \
    } \
    void PREFIX##NAME##MoveTo(PREFIX##NAME me, const PREFIX##NAME src) \
    { \
        if (src == NULL || me == src) return; \
        PREFIX##NAME##Destroy(me); \
        me->data = src->data; \
        me->size = src->size; \
        me->capacity = src->capacity; \
        me->insertSignal = src->insertSignal; \
        me->removeSignal = src->removeSignal; \
        src->data = NULL; \
        src->size = 0; \
        src->capacity = 0; \
        src->insertSignal = NULL; \
        src->removeSignal = NULL; \
    } \
    void PREFIX##NAME##Destroy(PREFIX##NAME me) \
    { \
        if (me->data != NULL && me->removeSignal != NULL) \
            for (size_t i = 0; i < me->size; i++) \
                me->removeSignal(me, &me->data[i]); \
        if (me->data != NULL) \
        { \
            (ALLOCATOR)->free((ALLOCATOR)->context, me->data); \
            me->data = NULL; \
        } \
        me->size = 0; \
        me->capacity = 0; \
    } \
    /* 访问 */ \
    TYPE* PREFIX##NAME##At(PREFIX##NAME me, size_t index) \
    { \
        return &me->data[index]; \
    } \
    TYPE* PREFIX##NAME##Front(PREFIX##NAME me) \
    { \
        return &me->data[0]; \
    } \
    TYPE* PREFIX##NAME##Back(PREFIX##NAME me) \
    { \
        return &me->data[me->size - 1]; \
    } \
    TYPE* PREFIX##NAME##Find(PREFIX##NAME me, const TYPE* goal, PREFIX##NAME##Equalor equalor, size_t* out_index) \
    { \
        for (size_t i = 0; i < me->size; i++) \
            if (equalor(&me->data[i], goal)) \
            { \
                if (out_index) *out_index = i; \
                return &me->data[i]; \
            } \
        return NULL; \
    } \
    bool PREFIX##NAME##Contains(PREFIX##NAME me, const TYPE* goal, PREFIX##NAME##Equalor equalor) \
    { \
        return PREFIX##NAME##Find(me, goal, equalor, NULL) != NULL; \
    } \
    /* 属性 */ \
    TYPE* PREFIX##NAME##Data(PREFIX##NAME me) \
    { \
        return me->data; \
    } \
    size_t PREFIX##NAME##Size(PREFIX##NAME me) \
    { \
        return me->size; \
    } \
    size_t PREFIX##NAME##Capacity(PREFIX##NAME me) \
    { \
        return me->capacity; \
    } \
    /* 状态 */ \
    bool PREFIX##NAME##Empty(PREFIX##NAME me) \
    { \
        return me->size == 0; \
    } \
    /* 批处理 */ \
    void PREFIX##NAME##Assign(PREFIX##NAME me, size_t count, const TYPE* elements) \
    { \
        PREFIX##NAME##Clear(me); \
        if (count == 0) return; \
        PREFIX##NAME##Reserve(me, count); \
        for (size_t i = 0; i < count; i++) \
            me->data[i] = elements[i]; \
        me->size = count; \
    } \
    void PREFIX##NAME##Append(PREFIX##NAME me, size_t count, const TYPE* elements) \
    { \
        if (count == 0) return; \
        size_t required = me->size + count; \
        if (required > me->capacity) \
        { \
            size_t newCapacity = me->capacity ? me->capacity : 1; \
            while (newCapacity < required) newCapacity *= NK_VECTOR_GROWTH_FACTOR; \
            PREFIX##NAME##Reserve(me, newCapacity); \
        } \
        for (size_t i = 0; i < count; i++) \
            me->data[me->size + i] = elements[i]; \
        me->size = required; \
    } \
    void PREFIX##NAME##InsertRange(PREFIX##NAME me, size_t index, size_t count, const TYPE* elements) \
    { \
        if (count == 0) return; \
        if (index > me->size) index = me->size; \
        size_t required = me->size + count; \
        if (required > me->capacity) \
        { \
            size_t newCapacity = me->capacity ? me->capacity : 1; \
            while (newCapacity < required) newCapacity *= NK_VECTOR_GROWTH_FACTOR; \
            PREFIX##NAME##Reserve(me, newCapacity); \
        } \
        if (index < me->size) \
            memmove(&me->data[index + count], &me->data[index], (me->size - index) * sizeof(TYPE)); \
        for (size_t i = 0; i < count; i++) \
            me->data[index + i] = elements[i]; \
        me->size = required; \
    } \
    void PREFIX##NAME##EraseRange(PREFIX##NAME me, size_t index, size_t count) \
    { \
        if (count == 0) return; \
        if (count > me->size - index) count = me->size - index; \
        if (me->removeSignal != NULL) \
            for (size_t i = 0; i < count; i++) \
                me->removeSignal(me, &me->data[index + i]); \
        size_t tail = me->size - (index + count); \
        if (tail > 0) \
            memmove(&me->data[index], &me->data[index + count], tail * sizeof(TYPE)); \
        me->size -= count; \
    } \
    void PREFIX##NAME##RemoveIf(PREFIX##NAME me, PREFIX##NAME##RemoveIfCallback predicate) \
    { \
        size_t write = 0; \
        for (size_t read = 0; read < me->size; read++) \
        { \
            if (predicate(&me->data[read])) \
            { \
                if (me->removeSignal != NULL) me->removeSignal(me, &me->data[read]); \
                continue; \
            } \
            if (write != read) \
                me->data[write] = me->data[read]; \
            write++; \
        } \
        me->size = write; \
    } \
    void PREFIX##NAME##Foreach(PREFIX##NAME me, PREFIX##NAME##ForeachCallback processor) \
    { \
        for (size_t i = 0; i < me->size; i++) \
            processor(&me->data[i]); \
    } \
    void PREFIX##NAME##RForeach(PREFIX##NAME me, PREFIX##NAME##ForeachCallback processor) \
    { \
        for (size_t i = me->size; i > 0; i--) \
            processor(&me->data[i - 1]); \
    } \
    /* 排序 */ \
    void PREFIX##NAME##BubbleSort(PREFIX##NAME me, PREFIX##NAME##Comparator comparator) \
    { \
        if (me->size < 2) return; \
        for (size_t i = 0; i < me->size - 1; i++) \
            for (size_t j = 0; j < me->size - 1 - i; j++) \
                if (comparator(&me->data[j], &me->data[j + 1]) > 0) \
                { \
                    TYPE temp = me->data[j]; \
                    me->data[j] = me->data[j + 1]; \
                    me->data[j + 1] = temp; \
                } \
    } \
    /* 容量 */ \
    void PREFIX##NAME##Reserve(PREFIX##NAME me, size_t capacity) \
    { \
        if (capacity <= me->capacity) return; \
        if (me->data == NULL) \
            me->data = (TYPE*)(ALLOCATOR)->malloc((ALLOCATOR)->context, capacity * sizeof(TYPE)); \
        else \
            me->data = (TYPE*)(ALLOCATOR)->realloc((ALLOCATOR)->context, me->data, capacity * sizeof(TYPE)); \
        if (me->data != NULL) \
            me->capacity = capacity; \
    } \
    void PREFIX##NAME##Resize(PREFIX##NAME me, size_t size) \
    { \
        if (size > me->capacity) \
        { \
            size_t newCapacity = me->capacity ? me->capacity : 1; \
            while (newCapacity < size) newCapacity *= NK_VECTOR_GROWTH_FACTOR; \
            PREFIX##NAME##Reserve(me, newCapacity); \
        } \
        if (size > me->size) \
        { \
            for (size_t i = me->size; i < size; i++) \
            { \
                me->data[i] = (TYPE){}; \
                if (me->insertSignal) me->insertSignal(me, &me->data[i]); \
            } \
        } \
        else if (size < me->size) \
        { \
            if (me->removeSignal != NULL) \
                for (size_t i = size; i < me->size; i++) \
                    me->removeSignal(me, &me->data[i]); \
        } \
        me->size = size; \
    } \
    void PREFIX##NAME##ShrinkToFit(PREFIX##NAME me) \
    { \
        if (me->size == me->capacity) return; \
        if (me->size == 0) \
        { \
            (ALLOCATOR)->free((ALLOCATOR)->context, me->data); \
            me->data = NULL; \
            me->capacity = 0; \
            return; \
        } \
        TYPE* newData = (TYPE*)(ALLOCATOR)->realloc((ALLOCATOR)->context, me->data, me->size * sizeof(TYPE)); \
        if (newData != NULL) \
        { \
            me->data = newData; \
            me->capacity = me->size; \
        } \
    } \
    void PREFIX##NAME##Clear(PREFIX##NAME me) \
    { \
        if (me->removeSignal != NULL && me->data != NULL) \
            for (size_t i = 0; i < me->size; i++) \
                me->removeSignal(me, &me->data[i]); \
        me->size = 0; \
    } \
    /* 增删改 */ \
    void PREFIX##NAME##Insert(PREFIX##NAME me, size_t index, const TYPE* element) \
    { \
        PREFIX##NAME##InsertRange(me, index, 1, element); \
    } \
    void PREFIX##NAME##InsertLiteral(PREFIX##NAME me, size_t index, TYPE literal) { PREFIX##NAME##Insert(me, index, &literal); } \
    void PREFIX##NAME##Erase(PREFIX##NAME me, size_t index) \
    { \
        PREFIX##NAME##EraseRange(me, index, 1); \
    } \
    size_t PREFIX##NAME##Push(PREFIX##NAME me, const TYPE* element) \
    { \
        if (me->size + 1 > me->capacity) \
        { \
            size_t newCapacity = me->capacity ? me->capacity * NK_VECTOR_GROWTH_FACTOR : 1; \
            PREFIX##NAME##Reserve(me, newCapacity); \
        } \
        me->data[me->size] = *element; \
        me->size += 1; \
        return me->size - 1; \
    } \
    size_t PREFIX##NAME##PushLiteral(PREFIX##NAME me, TYPE literal) { return PREFIX##NAME##Push(me, &literal); } \
    void PREFIX##NAME##Pop(PREFIX##NAME me) \
    { \
        me->size -= 1; \
        if (me->removeSignal != NULL) \
            me->removeSignal(me, &me->data[me->size]); \
    } \
    void PREFIX##NAME##Set(PREFIX##NAME me, size_t index, const TYPE* element) \
    { \
        if (me->removeSignal != NULL) \
            me->removeSignal(me, &me->data[index]); \
        me->data[index] = *element; \
    } \
    void PREFIX##NAME##SetLiteral(PREFIX##NAME me, size_t index, TYPE literal) { PREFIX##NAME##Set(me, index, &literal); } \
    /* 交换 */ \
    void PREFIX##NAME##Swap(PREFIX##NAME me, PREFIX##NAME other) \
    { \
        TYPE* tempData = me->data; \
        size_t tempSize = me->size; \
        size_t tempCapacity = me->capacity; \
        PREFIX##NAME##Signal tempInsertSignal = me->insertSignal; \
        PREFIX##NAME##Signal tempRemoveSignal = me->removeSignal; \
        me->data = other->data; \
        me->size = other->size; \
        me->capacity = other->capacity; \
        me->insertSignal = other->insertSignal; \
        me->removeSignal = other->removeSignal; \
        other->data = tempData; \
        other->size = tempSize; \
        other->capacity = tempCapacity; \
        other->insertSignal = tempInsertSignal; \
        other->removeSignal = tempRemoveSignal; \
    }
#pragma endregion
#pragma region Sugar
#define NK_VECTOR_FOREACH(TYPE, CONTAINER, ELEM_PTR_NAME) \
    for ( \
        TYPE* ELEM_PTR_NAME = (CONTAINER)->data; \
        ELEM_PTR_NAME != NULL && (size_t)(ELEM_PTR_NAME - (CONTAINER)->data) < (CONTAINER)->size; \
        ELEM_PTR_NAME++ \
    )
#define NK_VECTOR_RFOREACH(TYPE, CONTAINER, ELEM_PTR_NAME) \
    for ( \
        TYPE* ELEM_PTR_NAME = ((CONTAINER)->size > 0 ? &((CONTAINER)->data[(CONTAINER)->size - 1]) : NULL); \
        ELEM_PTR_NAME != NULL; \
        ELEM_PTR_NAME = (ELEM_PTR_NAME == (CONTAINER)->data ? NULL : ELEM_PTR_NAME - 1) \
    )
#pragma endregion

#endif
