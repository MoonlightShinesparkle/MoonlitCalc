cmake_minimum_required(VERSION 3.23)

# Since visual studio code won't detect zsh exported variables...
if (NOT DEFINED ENV{PICO_SDK_PATH})
	set(PICO_SDK_PATH "/Users/mac/Documents/PicoWorkspace/Pico")
endif()

include(pico_sdk_import.cmake)
project(SandboxedProject C CXX ASM)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

pico_sdk_init()

add_executable(${PROJECT_NAME}
	src/Main.cpp
	src/Util/GPIO.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	pico_multicore
	hardware_i2c
)