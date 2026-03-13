cmake_minimum_required(VERSION 3.15)
project(MazeGenerator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake to find SFML via config mode
find_package(SFML 2.5 CONFIG REQUIRED COMPONENTS graphics window system)

set(SOURCES
    src/main.cpp
    src/game.cpp
    src/grid.cpp
    src/cell.cpp
    src/randomManager.cpp
    src/drawText.cpp
)

add_executable(maze_generator ${SOURCES})

target_include_directories(maze_generator PRIVATE
    ${CMAKE_SOURCE_DIR}/Header
    ${CMAKE_SOURCE_DIR}
)

# Link imported SFML targets (correct for MSVC)
target_link_libraries(maze_generator PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

# Copy assets - use add_custom_command to copy during build
add_custom_command(TARGET maze_generator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Images
    $<TARGET_FILE_DIR:maze_generator>/Images
    COMMENT "Copying Images to build directory"
)
