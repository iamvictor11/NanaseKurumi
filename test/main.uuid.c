#include <stdio.h>
#include "CTemplateKit/platform/console.h"
#include "CTemplateKit/utils/random_gen.h"
#include "CTemplateKit/type/uuid.h"

C_TEMPLATE_DECL_ALLOCATOR(static inline, test, Test)
C_TEMPLATE_DEFN_ALLOCATOR(static inline, test, Test)
C_TEMPLATE_IMPL_ALLOCATOR(static inline, test, Test)

TestAllocator allocator;

C_TEMPLATE_DECL_UUID(static inline, test, Test, UUID)
C_TEMPLATE_DEFN_UUID(static inline, test, Test, UUID)
C_TEMPLATE_IMPL_UUID(static inline, test, Test, UUID, allocator)

C_TEMPLATE_DECL_RANDOM_GEN(static inline, test, Test, RandomGen, TestUUID)
C_TEMPLATE_DEFN_RANDOM_GEN(static inline, test, Test, RandomGen, TestUUID)
C_TEMPLATE_IMPL_RANDOM_GEN(static inline, test, Test, RandomGen, TestUUID, &allocator)

int main()
{
    osSetConsoleOutputCP_UTF8();

    allocator = testDefaultAllocator();

    TestRandomGenDef def = testNullRandomGenDef();
    def.seed = (TestUUID){1, 1};
    def.generator = testUUIDGenerator;
    def.clampor = testUUIDClampor;
    TestRandomGen randomGen = testRandomGenCreate(&def);
    TestUUID uuidrd = testRandomGenNext(randomGen);
    printf("uuidrd: %s = {%zu, %zu}\n", testUUIDToCstr(uuidrd), uuidrd.high, uuidrd.low);
    TestUUID uuidmk = testUUIDFromCstr("47e4ce4b-896c-dd1d-835a-5c5cc01df086");
    printf("uuidmk: %s = {%zu, %zu}\n", testUUIDToCstr(uuidmk), uuidmk.high, uuidmk.low);
    testRandomGenDestroy(randomGen);

    osGetChar();
    return EXIT_SUCCESS;
}
