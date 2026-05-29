#include <stdio.h>
#include "project_name/platform/console.h"
#include "project_name/container/list.h"
#include <stdlib.h>

pnxAllocator allocator = PNX_DEFAULT_ALLOCATOR;

PNX_DEC_LIST(test, List, TestItem)
PNX_DEF_LIST(test, List, TestItem)
typedef struct TestItem
{
    int value;
    testListNode node;
} TestItem;
PNX_IMPL_LIST(test, List, TestItem, node, &allocator)

int main()
{
    pnxSetConsoleOutputCP_UTF8();

    testList list = testListCreate(NULL);
    TestItem items[] = {{0}, {1}, {2}};
    testListPushBack(list, &items[0]);
    testListPushBack(list, &items[1]);
    testListPushBack(list, &items[2]);
    PNX_LIST_RFOREACH(TestItem, node, list, it)
        printf("%d ", it->value);
    printf("\n");
    testListErase(list, &items[1]);
    PNX_LIST_FOREACH(TestItem, node, list, it)
        printf("%d ", it->value);
    printf("\n");
    testListClear(list);
    testListDestroy(list);

    pnxGetChar();
    return EXIT_SUCCESS;
}
