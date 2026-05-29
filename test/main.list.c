#include <stdio.h>
#include "project_name/platform/console.h"
#include "project_name/container/list.h"
#include <stdlib.h>

pn_Allocator allocator = PN_DEFAULT_ALLOCATOR;

PN_DEC_LIST(test, List, TestItem)
PN_DEF_LIST(test, List, TestItem)
typedef struct TestItem
{
    int value;
    testListNode node;
} TestItem;
PN_IMPL_LIST(test, List, TestItem, node, &allocator)

int main()
{
    pn_SetConsoleOutputCP_UTF8();

    testList list = testListCreate(NULL);
    TestItem items[] = {{0}, {1}, {2}};
    testListPushBack(list, &items[0]);
    testListPushBack(list, &items[1]);
    testListPushBack(list, &items[2]);
    PN_LIST_RFOREACH(TestItem, node, list, it)
        printf("%d ", it->value);
    printf("\n");
    testListErase(list, &items[1]);
    PN_LIST_FOREACH(TestItem, node, list, it)
        printf("%d ", it->value);
    printf("\n");
    testListClear(list);
    testListDestroy(list);

    pn_GetChar();
    return EXIT_SUCCESS;
}
