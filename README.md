# Maze-Generator

A C++ implementation of four different maze-generation algorithms with real-time visualization using SFML.

---

## Features
- Implements four maze-generation algorithms:

  - Recursive Backtracker (DFS)

  - Randomized Prim's Algorithm

  - Wilson's Algorithm (Loop-erased random walk)
  
  - Aldous-Broder Algorithm (BFS)

- Real-time visualization of maze generation

- Performance metrics tracking (steps and time)

- Interactive controls to switch between algorithms

- Customizable grid size through configuration

---

## Requirements
- C++17 compatible compiler (GCC, Clang, MSVC)

- SFML 2.5+ library

- CMake 3.15+ (recommended)

---
## Installation

### Prerequisites
- C++17 compatible compiler (GCC, Clang, or MSVC)
- CMake 3.15 or higher
- SFML 2.5 or higher

### Platform-Specific Setup

#### Linux (Ubuntu/Debian)
```bash
# Install dependencies
sudo apt update
sudo apt install libsfml-dev cmake g++

# Clone or download the repository
cd Maze-Generator

# Build the project
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)

# Run
./maze_generator
```

#### Linux (Fedora/RHEL)
```bash
# Install dependencies
sudo dnf install SFML-devel cmake gcc-c++

# Build the project
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)

# Run
./maze_generator
```

#### macOS
```bash
# Install dependencies via Homebrew
brew install sfml cmake

# Clone or download the repository
cd Maze-Generator

# Build the project
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(sysctl -n hw.ncpu)

# Run
./maze_generator
```

#### Windows (Visual Studio)
1. Install [SFML](https://www.sfml-dev.org/download/sfml/2.6.2/) or use vcpkg:
   ```bash
   vcpkg install sfml:x64-windows
   ```

2. Install [CMake](https://cmake.org/download/) and [Visual Studio](https://visualstudio.microsoft.com/)

3. Clone or download the repository

4. Build using VS Code or command line:
   ```bash
   mkdir build && cd build
   cmake -G "Visual Studio 17 2022" ..
   cmake --build . --config Release
   ```

5. Run from the build directory:
   ```bash
   .\Release\maze_generator.exe
   ```

### Building with CMake Tools Extension (VS Code)

1. Install the [CMake Tools extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) in VS Code
2. Open the project folder in VS Code
3. Select the appropriate build configuration:
   - Windows: `Windows-x64-Release`
   - Linux: `Linux-Release`
   - macOS: `macOS-Release`
4. Click "Build" in the CMake Tools sidebar

### Controls
- **1-4 Keys**: Switch between algorithms
- **Window Close Button**: Exit the application

### Real-time Metrics
The display shows:
- **Steps**: Number of generation steps completed
- **Time**: Live elapsed time in milliseconds while generating (updates each frame)
- **Algorithm Name**: Currently running algorithm

---

# Algorithms Overview
1. *Recursive Backtracker (DFS)*

    - Depth-first search approach

    - Creates mazes with long corridors

    - Fast but produces biased results

2. *Randomized Prim's Algorithm*

    - Grows maze from random frontier cells

    - More natural branching patterns

    - Balanced performance and randomness

3. *Wilson's Algorithm*

    - Uses loop-erased random walks

    - Produces uniform spanning trees

    - Slower but unbiased results

4. *Aldous-Broder Algorithm (BFS)*

    - Simple random walk approach

    - Uniform but very slow

    - Good for theoretical understanding
