set(libname BoardInit)
add_library(${libname} STATIC
    ${libname}.cpp
)
target_include_directories(${libname} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(${libname} PRIVATE
    hardware_clocks hardware_pll
)
