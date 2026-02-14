set(libname Fifo)
add_library(${libname} STATIC)
target_include_directories(${libname} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/..
)
if(PC_SIMULATOR)
    target_sources(${libname} PRIVATE Fifo_PC.cpp)
    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    set(THREADS_PREFER_PTHREAD_FLAG TRUE)
    find_package(Threads REQUIRED)
    target_link_libraries(${libname} PRIVATE Threads::Threads)
else()
    target_sources(${libname} PRIVATE Fifo.cpp)
    target_link_libraries(${libname} PRIVATE 
        pico_multicore
    )
endif()
