set(libname Tasks)
add_library(${libname} STATIC)

target_sources(${libname} PRIVATE
    Foreground/ForegroundTask.cpp
    Background/BackgroundTask.cpp
)

target_include_directories(${libname} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../..
)

target_link_libraries(${libname} PRIVATE
    Fifo
    Thread
    Timer
    Adc
    LvglPort
    Switch
    Screen
)
