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

include(FetchContent)

option(PC_SIMULATOR "Build for PC simulator" OFF)

LIST(APPEND COMMON_LIBS
    BoardInit
    Timer
    Adc
    LvglPort
)

if(PC_SIMULATOR)
    project(RP2_LCD0in96_Demo C CXX ASM)
    add_executable(RP2_LCD0in96_Demo RP2_LCD0in96_Demo.cpp )
    target_compile_definitions(RP2_LCD0in96_Demo PRIVATE PC_SIMULATOR)

    FetchContent_Declare(
    lv_port_pc_vscode
    GIT_REPOSITORY https://github.com/lvgl/lv_port_pc_vscode
    GIT_TAG        master
    )
    FetchContent_MakeAvailable(lv_port_pc_vscode)
    set(LV_PORT_PC_VSCODE_DIR ${lv_port_pc_vscode_SOURCE_DIR})

    if(TARGET lv_port_pc_vscode)
        target_compile_options(lv_port_pc_vscode PRIVATE -w)
    endif()
    if(TARGET lvgl)
        target_compile_options(lvgl PRIVATE -w)
    endif()

    find_package(SDL2 REQUIRED)
    
    target_include_directories(RP2_LCD0in96_Demo PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${SDL2_INCLUDE_DIRS}
    )
    target_link_libraries(RP2_LCD0in96_Demo PRIVATE 
            ${COMMON_LIBS}
            -Wl,--start-group
            ${SDL2_LIBRARIES} 
            lvgl
            -Wl,--end-group)
else()

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(RP2_LCD0in96_Demo C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(RP2_LCD0in96_Demo RP2_LCD0in96_Demo.cpp )

pico_set_program_name(RP2_LCD0in96_Demo "RP2_LCD0in96_Demo")
pico_set_program_version(RP2_LCD0in96_Demo "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(RP2_LCD0in96_Demo 1)
pico_enable_stdio_usb(RP2_LCD0in96_Demo 0)

# Add the standard library to the build
target_link_libraries(RP2_LCD0in96_Demo PRIVATE
        ${COMMON_LIBS} Lcd0in96
        lvgl pico_stdlib
        )

# Add the standard include files to the build
target_include_directories(RP2_LCD0in96_Demo PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)
pico_add_extra_outputs(RP2_LCD0in96_Demo)

target_compile_options(RP2_LCD0in96_Demo PRIVATE -Wall -Wextra -Wshadow -Wpedantic -Werror)

FetchContent_Declare(
  lvgl
  GIT_REPOSITORY https://github.com/lvgl/lvgl.git
  GIT_TAG        v9.3.0
)
FetchContent_MakeAvailable(lvgl)
target_compile_options(lvgl PRIVATE -w)

endif()

add_subdirectory(lib)