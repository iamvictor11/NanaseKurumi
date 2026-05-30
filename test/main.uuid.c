#include <stdio.h>
#include "project_name/platform/console.h"
#include "project_name/utils/random_gen.h"
#include "project_name/type/uuid.h"

PNX_DEC_ALLOCATOR(static inline, test, Test)
PNX_DEF_ALLOCATOR(static inline, test, Test)
PNX_IMPL_ALLOCATOR(static inline, test, Test)

TestAllocator allocator;

PNX_DEC_UUID(static inline, test, Test, UUID)
PNX_DEF_UUID(static inline, test, Test, UUID)
PNX_IMPL_UUID(static inline, test, Test, UUID, allocator)

PNX_DEC_RANDOM_GEN(static inline, test, Test, RandomGen, TestUUID)
PNX_DEF_RANDOM_GEN(static inline, test, Test, RandomGen, TestUUID)
PNX_IMPL_RANDOM_GEN(static inline, test, Test, RandomGen, TestUUID, &allocator)

int main()
{
    pnxSetConsoleOutputCP_UTF8();

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

    pnxGetChar();
    return EXIT_SUCCESS;
}
