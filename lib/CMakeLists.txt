set(libname lvglport)
add_library(${libname} STATIC
    src/LvglPort.c
)
target_include_directories(${libname} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)
target_link_libraries(${libname} PUBLIC
    lvgl PRIVATE LCD hardware_spi hardware_dma
)
target_compile_options(${libname} PRIVATE -Wall -Wextra -Wshadow -Wpedantic -Werror)

target_compile_options(lvgl PRIVATE -w)
target_compile_options(hardware_spi INTERFACE -w)