# Search for all source files in the current directory
# and save the names to the DIR_Config_SRCS variable
aux_source_directory(. DIR_Config_SRCS) 

# Generate link library
add_library(Config STATIC ${DIR_Config_SRCS})
target_link_libraries(Config PUBLIC hardware_spi hardware_pwm hardware_dma hardware_timer)
target_include_directories(Config PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_compile_options(Config PRIVATE -w)