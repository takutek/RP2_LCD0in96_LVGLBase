if(NOT PC_SIMULATOR)
    target_compile_options(lvgl PRIVATE -w)
    target_compile_options(hardware_spi INTERFACE -w)
    target_compile_options(hardware_irq INTERFACE -w)
endif()

add_subdirectory(Board)
add_subdirectory(Drivers)
add_subdirectory(LvglPort)
