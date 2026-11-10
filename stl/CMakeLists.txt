add_library(stl INTERFACE)

target_include_directories(stl
INTERFACE
    "include"
)
target_compile_options(stl
INTERFACE
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
target_link_options(stl
INTERFACE
    $<$<CONFIG:Release>:
        -s
        -Wl,--gc-sections
    >
)
