add_executable(test "main.c")

target_compile_definitions(test
PRIVATE
    TEST_BUILD_DEBUG=$<IF:$<CONFIG:Debug>,1,0>
    TEST_BUILD_RELEASE=$<IF:$<CONFIG:Release>,1,0>
)
target_include_directories(test
PUBLIC
    "include"
    "src"
)
add_subdirectory("src")
target_link_libraries(test
PUBLIC
    nanaku
)

set_property(TARGET test PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
target_compile_options(test
PRIVATE
    $<$<CONFIG:Debug>:
        -O0
        -g
    >
    $<$<CONFIG:Release>:
        -O3
        -DNDEBUG
        -fomit-frame-pointer
        -fno-semantic-interposition
        -ffunction-sections
        -fdata-sections
    >
)
target_link_options(test
PRIVATE
    -static
    $<$<CONFIG:Release>:
        -s
        -Wl,--gc-sections
    >
)
