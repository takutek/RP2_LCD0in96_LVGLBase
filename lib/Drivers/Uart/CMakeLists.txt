set(libname Uart)
add_library(${libname} STATIC)
if(PC_SIMULATOR)
    target_sources(${libname} PRIVATE Dummy${libname}.cpp)
else()
    target_sources(${libname} PRIVATE ${libname}.cpp)
    target_link_libraries(${libname} PRIVATE
        hardware_uart
    )
endif()
target_include_directories(${libname} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../..
)
