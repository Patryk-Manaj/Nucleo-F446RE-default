cmake_minimum_required(VERSION 3.22)
project(default_project C ASM)

# -----------------------------------------------------------------------------
# Toolchain and MCU configuration
# -----------------------------------------------------------------------------
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/arm-gcc-toolchain.cmake")

# -----------------------------------------------------------------------------
# Target
# -----------------------------------------------------------------------------
set(TARGET default_project)
add_executable(${TARGET})

# -----------------------------------------------------------------------------
# MCU flags
# -----------------------------------------------------------------------------
set(MCU_FLAGS
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)


target_compile_options(${TARGET} PRIVATE
    ${MCU_FLAGS}
    -Wall -Og -ffunction-sections -fdata-sections -g
)

target_compile_definitions(${TARGET} PRIVATE
    USE_HAL_DRIVER
    STM32F446xx
)

# -----------------------------------------------------------------------------
# Source files
# -----------------------------------------------------------------------------
file(GLOB_RECURSE SOURCES
    "Core/Src/*.c"
    "Drivers/STM32F4xx_HAL_Driver/Src/*.c"
    "startup_stm32f446xx.s"
)
target_sources(${TARGET} PRIVATE ${SOURCES})

# -----------------------------------------------------------------------------
# Include directories
# -----------------------------------------------------------------------------
target_include_directories(${TARGET} PRIVATE
    Core/Inc
    Drivers/STM32F4xx_HAL_Driver/Inc
    Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
    Drivers/CMSIS/Device/ST/STM32F4xx/Include
    Drivers/CMSIS/Include
)

# -----------------------------------------------------------------------------
# Linker options
# -----------------------------------------------------------------------------
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/STM32F446RETx_FLASH.ld")

target_link_options(${TARGET} PRIVATE
    ${MCU_FLAGS}
    -T${LINKER_SCRIPT}
    -specs=nano.specs
    -Wl,--gc-sections
    -Wl,-Map=${TARGET}.map,--cref
)

# -----------------------------------------------------------------------------
# Post-build commands (.hex, .bin, size)
# -----------------------------------------------------------------------------
add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${TARGET} ${TARGET}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary ${TARGET} ${TARGET}.bin
    COMMAND ${CMAKE_SIZE} ${TARGET}
)

# -----------------------------------------------------------------------------
# Flash target (ST-Link)
# -----------------------------------------------------------------------------
add_custom_target(flash
    COMMAND st-flash --reset write ${CMAKE_BINARY_DIR}/${TARGET}.bin 0x08000000
    DEPENDS ${TARGET}
)
