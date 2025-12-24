set(libname BoardInit)
add_library(${libname} STATIC)

target_link_libraries(${libname} PRIVATE BoardConfig)

if(PC_SIMULATOR)
    target_sources(${libname} PRIVATE DummyBoardInit.cpp)
else()
    target_sources(${libname} PRIVATE BoardInit.cpp)
    target_link_libraries(${libname} PRIVATE
        hardware_clocks hardware_pll pico_stdlib
    )
endif()

target_include_directories(${libname} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
