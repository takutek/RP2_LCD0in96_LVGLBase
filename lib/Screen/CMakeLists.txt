set(libname Screen)
add_library(${libname} STATIC
    Scale.cpp
)
target_include_directories(${libname} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../..
)
target_link_libraries(${libname} PRIVATE
    lvgl
)
