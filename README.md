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
### Linux (Ubuntu/Debian)
```bash
sudo apt install libsfml-dev cmake g++
```

### Windows
Install SFML through vcpkg or download from [SFML's official site](https://www.sfml-dev.org/)

### Building
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

### Run the compiled executable:
```bash
./maze_generator
```

### Controls
- Keys 1-4: Switch between algorithms

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
