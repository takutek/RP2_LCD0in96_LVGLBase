set(libname BoardConfig)
add_library(${libname} INTERFACE)

if(PC_SIMULATOR)
    find_package(SDL2 REQUIRED)
    target_link_libraries(${libname} INTERFACE ${SDL2_LIBRARIES})
    target_include_directories(${libname} INTERFACE ${SDL2_INCLUDE_DIRS})
endif()

target_include_directories(${libname} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
