add_library(xk INTERFACE)

target_include_directories(xk
INTERFACE
    "include"
)
target_compile_options(xk
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
target_link_options(xk
INTERFACE
    $<$<CONFIG:Release>:
        -s
        -Wl,--gc-sections
    >
)
