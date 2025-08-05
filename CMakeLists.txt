cmake_minimum_required(VERSION 3.15)
project(MazeGenerator LANGUAGES CXX)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Set source files
set(SOURCES
    src/main.cpp
    src/game.cpp
    src/grid.cpp
    src/cell.cpp
    src/randomManager.cpp
    src/drawText.cpp
)

# Include directories (BOTH relative and absolute paths)
include_directories(
    ${CMAKE_SOURCE_DIR}/Header
    ${CMAKE_SOURCE_DIR}
)

# Add executable
add_executable(maze_generator ${SOURCES})

# Link libraries
target_link_libraries(maze_generator PRIVATE sfml-graphics sfml-window sfml-system)

# C++17 standard
target_compile_features(maze_generator PRIVATE cxx_std_17)

# Copy assets
file(COPY ${CMAKE_SOURCE_DIR}/Images DESTINATION ${CMAKE_BINARY_DIR})