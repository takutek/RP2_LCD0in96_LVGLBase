set(libname ForegroundTask)
add_library(${libname} STATIC)

target_sources(${libname} PRIVATE
    ForegroundTask.cpp
)

target_include_directories(${libname} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../..
)

target_link_libraries(${libname} PRIVATE
    Fifo
    LvglPort
    Screen
    Timer
)

target_compile_options(${libname} PRIVATE ${COMMON_COMPILE_OPTIONS})
