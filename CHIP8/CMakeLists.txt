cmake_minimum_required(VERSION 3.10)
project(Chip8Emulator)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories for each component
add_subdirectory(chip8_soc)
add_subdirectory(gfx)
add_subdirectory(memory)
add_subdirectory(peripherals)

# Add source files
file(GLOB SOURCES "*.cxx")

# Include headers
include_directories(chip8_soc gfx memory peripherals)

# Target executable
add_executable(Chip8Emulator ${SOURCES})

# Link libraries (if any are needed you can specify them here)
target_link_libraries(Chip8Emulator ${SDL2_LIBRARIES} chip8_soc gfx memory peripherals)