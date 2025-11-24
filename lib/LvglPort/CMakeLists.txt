set(libname LvglPort)
add_library(${libname} STATIC)
if(PC_SIMULATOR)
    set(MAIN_SOURCES ${LV_PORT_PC_VSCODE_DIR}/src/mouse_cursor_icon.c ${LV_PORT_PC_VSCODE_DIR}/src/hal/hal.c)
    target_sources(${libname} PRIVATE ${libname}_PC.cpp ${MAIN_SOURCES})
    target_include_directories(${libname} PRIVATE ${SDL2_INCLUDE_DIRS})
    target_include_directories(${libname} PRIVATE ${LV_PORT_PC_VSCODE_DIR}/src/)
    target_include_directories(${libname} PRIVATE ${LV_PORT_PC_VSCODE_DIR}/)
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
