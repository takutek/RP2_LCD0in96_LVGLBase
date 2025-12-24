set(libname Gpio)
add_library(${libname} STATIC)
if(PC_SIMULATOR)
    target_sources(${libname} PRIVATE ${libname}_PC.cpp)
    target_link_libraries(${libname} PRIVATE 
            ${SDL2_LIBRARIES})
else()
    target_sources(${libname} PRIVATE ${libname}.cpp)
    target_link_libraries(${libname} PRIVATE 
            hardware_gpio)
endif()
target_include_directories(${libname} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../..
)
