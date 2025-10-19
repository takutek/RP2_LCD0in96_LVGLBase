# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(RP2_LCD0in96_Demo C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(RP2_LCD0in96_Demo RP2_LCD0in96_Demo.c )

pico_set_program_name(RP2_LCD0in96_Demo "RP2_LCD0in96_Demo")
pico_set_program_version(RP2_LCD0in96_Demo "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(RP2_LCD0in96_Demo 1)
pico_enable_stdio_usb(RP2_LCD0in96_Demo 0)

# Add the standard library to the build
target_link_libraries(RP2_LCD0in96_Demo PRIVATE
        lvgl Config lvglport
        hardware_timer
        hardware_adc
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(RP2_LCD0in96_Demo PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
pico_add_extra_outputs(RP2_LCD0in96_Demo)

target_compile_options(RP2_LCD0in96_Demo PRIVATE -Wall -Wextra -Wshadow -Werror)

include(FetchContent)
FetchContent_Declare(
  lvgl
  GIT_REPOSITORY https://github.com/lvgl/lvgl.git
  GIT_TAG        v9.3.0
)
FetchContent_MakeAvailable(lvgl)
target_compile_options(lvgl PRIVATE -w)

add_subdirectory(external)
add_subdirectory(lib)