cmake_minimum_required(VERSION 3.22)

# Project
project(TickTackToe LANGUAGES C ASM)

# Helpful for clangd / IDE indexing
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default build type only for single-config generators (Ninja/Unix Makefiles)
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Your ELF target
add_executable(${PROJECT_NAME})

# Target-level language standard
set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS YES
)

# CubeMX generated CMake target(s)
add_subdirectory(cmake/stm32cubemx)

# --- Your sources (keep one authoritative list) -----------------------------
set(APP_SOURCES
    Core/Src/main.c
    Core/Src/adc.c
    Core/Src/display.c
    Core/Src/joystick.c
    Core/Src/game.c
    # All user created source files
)

set(HAL_EXTRA_SOURCES
    Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma2d.c
    Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_ltdc.c
    Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_ltdc_ex.c
    

    Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_adc.c
    Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_adc_ex.c
    # tega ne dati
    # Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
    # Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c

    # add SDRAM HAL
    Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sdram.c
    # often needed with FMC/SDRAM on H7
    Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_fmc.c
)

set(BSP_SOURCES
    Drivers/BSP/STM32H750B-DK/stm32h750b_discovery.c
    Drivers/BSP/STM32H750B-DK/stm32h750b_discovery_lcd.c
    Drivers/BSP/Components/mt48lc4m32b2/mt48lc4m32b2.c
    Drivers/BSP/STM32H750B-DK/stm32h750b_discovery_bus.c
    Drivers/BSP/STM32H750B-DK/stm32h750b_discovery_sdram.c
    Drivers/BSP/STM32H750B-DK/stm32h750b_discovery_ts.c


    # add FT5336 implementation
    Drivers/BSP/Components/ft5336/ft5336.c
    Drivers/BSP/Components/ft5336/ft5336_reg.c
)

set(UTILITIES_SOURCES 
    Utilities/LCD/stm32_lcd.c
    # Utilities source files
)

target_sources(${PROJECT_NAME} PRIVATE
    ${APP_SOURCES}
    ${HAL_EXTRA_SOURCES}
    ${BSP_SOURCES}
    ${UTILITIES_SOURCES}
    # Aditional sources
)

# --- Includes ---------------------------------------------------------------
target_include_directories(${PROJECT_NAME} PRIVATE
    Core/Inc
    Drivers/BSP/STM32H750B-DK
    Drivers/BSP/Components/Common
    Utilities/LCD/Inc
    Utilities/Fonts/Inc
    Drivers/STM32H7xx_HAL_Driver/Inc
    # All include files added into project folder after initial CubeMX init
)

# --- Definitions / warnings -------------------------------------------------
target_compile_definitions(${PROJECT_NAME} PRIVATE
    # e.g. USE_HAL_DRIVER STM32H750xx (often already set by Cube target)
)

# Optional but recommended: common warnings
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wshadow -Wdouble-promotion
    $<$<COMPILE_LANGUAGE:C>:-Wstrict-prototypes>
)

# printf float support
target_link_options(${PROJECT_NAME} PRIVATE
    -Wl,-u,_printf_float
)

# CubeMX target link (keeps startup, linker script, core flags, etc.)
target_link_libraries(${PROJECT_NAME} stm32cubemx)


# If you ever add C++ later, this hack is generally not needed if toolchain is clean.
# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# --- Flash target (configurable tool path) -----------------------------
# Set to location of STM32_Programmer_CLI on your computer
set(STM32_PROGRAMMER_CLI
    "/Applications/STMicroelectronics/STM32Cube/STM32CubeProgrammer/STM32CubeProgrammer.app/Contents/Resources/bin/STM32_Programmer_CLI"
    CACHE FILEPATH "Path to STM32_Programmer_CLI"
)

# Add custom target 'flash', it runs STM32_PROGRAMMER_CLI to load .elf file to stm32 via SWD
add_custom_target(flash
    COMMAND "${STM32_PROGRAMMER_CLI}"
        -c port=SWD mode=UR reset=HWrst
        -w $<TARGET_FILE:${PROJECT_NAME}>
        -rst
    DEPENDS ${PROJECT_NAME}
    USES_TERMINAL
    VERBATIM
)