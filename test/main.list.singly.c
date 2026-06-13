#include <stdio.h>
#include "c_template/platform/console.h"
#include "c_template/container/list.singly.h"

C_TEMPLATE_DECL_ALLOCATOR(static inline, test, Test)
C_TEMPLATE_DEFN_ALLOCATOR(static inline, test, Test,)
C_TEMPLATE_IMPL_ALLOCATOR(static inline, test, Test)

TestAllocator allocator;

typedef struct TestItem TestItem;
C_TEMPLATE_DECL_SLIST(static inline, test, Test, List, TestItem)
C_TEMPLATE_DEFN_SLIST(static inline, test, Test, List, TestItem)
typedef struct TestItem
{
    int value;
    TestListNode node;
} TestItem;
C_TEMPLATE_IMPL_SLIST(static inline, test, Test, List, TestItem, node, &allocator)

int main()
{
    osSetConsoleOutputCP_UTF8();

    allocator = testDefaultAllocator();

    TestList list = testListCreate(NULL);
    TestItem items[] = {{0}, {1}, {2}};
    testListPushBack(list, &items[0]);
    testListPushBack(list, &items[1]);
    testListPushBack(list, &items[2]);
    C_TEMPLATE_SLIST_FOREACH(TestItem, it, node, list)
        printf("%d ", it->value);
    printf("\n");
    testListErase(list, &items[1]);
    C_TEMPLATE_SLIST_FOREACH(TestItem, it, node, list)
        printf("%d ", it->value);
    printf("\n");
    testListClear(list);
    testListDestroy(list);

    osGetChar();
    return EXIT_SUCCESS;
}
