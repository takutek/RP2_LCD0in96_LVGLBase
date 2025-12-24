set(libname Switch)
add_library(${libname} STATIC
    ${libname}.cpp
)
target_include_directories(${libname} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../..
)
target_link_libraries(${libname} PRIVATE
    Gpio
)
