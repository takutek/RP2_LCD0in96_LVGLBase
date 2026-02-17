set(libname Fifo)
add_library(${libname} STATIC)
target_include_directories(${libname} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/..
)
if(PC_SIMULATOR)
    target_sources(${libname} PRIVATE Fifo_PC.cpp)
else()
    target_sources(${libname} PRIVATE Fifo.cpp)
    target_link_libraries(${libname} PRIVATE 
        pico_multicore
    )
endif()
