set(libname LvglPort)
add_library(${libname} STATIC)
if(PC_SIMULATOR)
    target_sources(${libname} PRIVATE ${libname}_PC.cpp mouse_cursor_icon.cpp)
    target_include_directories(${libname} PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(${libname} PRIVATE lvgl Timer)
else()
    target_sources(${libname} PRIVATE ${libname}.cpp)
    target_link_libraries(${libname} PRIVATE
    lvgl Dma Lcd0in96
    )
endif()
target_include_directories(${libname} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../..
)
