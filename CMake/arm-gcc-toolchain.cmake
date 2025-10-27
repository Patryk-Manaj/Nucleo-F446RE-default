# ===============================================================
# CMake Toolchain file for STM32F4 / Cortex-M4 using GNU Arm GCC
# ===============================================================

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Path to your GNU Arm Embedded Toolchain
set(TOOLCHAIN_PATH "/usr/local/gcc-arm-none-eabi-10.3-2021.10/bin")

# Define compiler executables
set(CMAKE_C_COMPILER   ${TOOLCHAIN_PATH}/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-gcc)
set(CMAKE_OBJCOPY      ${TOOLCHAIN_PATH}/arm-none-eabi-objcopy)
set(CMAKE_SIZE         ${TOOLCHAIN_PATH}/arm-none-eabi-size)

# MCU and optimization flags — use list form so CMake passes them correctly
set(MCU_FLAGS
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)

# Add compile options
add_compile_options(
    ${MCU_FLAGS}
    -ffunction-sections
    -fdata-sections
    -Wall
    -g
)

# Linker flags (can stay as a string)
set(CMAKE_EXE_LINKER_FLAGS
    "-Wl,--gc-sections"
    CACHE STRING "" FORCE
)

# Prevent CMake from trying to run binaries on host
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
