# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================




cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico CACHE STRING "Board type")

include(pico_sdk_import.cmake)
project(Tarefa_Final C CXX ASM)
pico_sdk_init()
add_executable(Tarefa_Final Tarefa_Final.c lib/ssd1306.c)
pico_set_program_name(Tarefa_Final "Tarefa_Final")
pico_set_program_version(Tarefa_Final "0.1")
pico_enable_stdio_uart(Tarefa_Final 0)
pico_enable_stdio_usb(Tarefa_Final 1)
target_link_libraries(Tarefa_Final pico_stdlib hardware_i2c hardware_adc)
target_include_directories(Tarefa_Final PRIVATE ${CMAKE_CURRENT_LIST_DIR})
pico_add_extra_outputs(Tarefa_Final)

