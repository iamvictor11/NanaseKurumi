#include <stdio.h>
#include "project_name/platform/console.h"
#include "project_name/utils/random_gen.h"

PNX_DEC_ALLOCATOR(static inline, test, Test)
PNX_DEF_ALLOCATOR(static inline, test, Test)
PNX_IMPL_ALLOCATOR(static inline, test, Test)

TestAllocator allocator;

PNX_DEC_RANDOM_GEN(static inline, test, Test, RandomGen, uint64_t)
PNX_DEF_RANDOM_GEN(static inline, test, Test, RandomGen, uint64_t)
PNX_IMPL_RANDOM_GEN(static inline, test, Test, RandomGen, uint64_t, &allocator)

static inline uint64_t testRandomGenGenerator_LCG(uint64_t state)
{
    state = state * 1103515245 + 12345;
    return state;
}
static inline void testRandomGenClampor_MOD(uint64_t* value, uint64_t min, uint64_t max) {
    uint64_t range = max - min + 1;
    *value = min + (*value % range);
}

int main()
{
    pnxSetConsoleOutputCP_UTF8();

    allocator = testDefaultAllocator();

    TestRandomGenDef def = testNullRandomGenDef();
    def.seed = 11;
    def.generator = testRandomGenGenerator_LCG;
    def.clampor = testRandomGenClampor_MOD;
    TestRandomGen randomGen = testRandomGenCreate(&def);
    uint64_t random = testRandomGenNext(randomGen);
    printf("random: %zu\n", random);
    uint64_t randoms[10];
    testRandomGenNextRangetBulk(randomGen, 1, 10, 10, randoms);
    printf("randoms:\n");
    for (size_t i = 0; i < 10; i++)
        printf("%zu\n", randoms[i]);
    testRandomGenDestroy(randomGen);

    pnxGetChar();
    return EXIT_SUCCESS;
}
