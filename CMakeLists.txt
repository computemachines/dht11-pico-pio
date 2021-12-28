cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)
project(temperature-pico C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(temperature)

pico_generate_pio_header(temperature ${CMAKE_CURRENT_LIST_DIR}/src/dht11.pio)
pico_generate_pio_header(temperature ${CMAKE_CURRENT_LIST_DIR}/src/simple_read.pio)

target_sources(temperature PRIVATE src/main.c)

target_link_libraries(temperature PRIVATE pico_stdlib hardware_pio hardware_gpio hardware_irq)

pico_add_extra_outputs(temperature)
pico_enable_stdio_usb(temperature 0)
pico_enable_stdio_uart(temperature 1)