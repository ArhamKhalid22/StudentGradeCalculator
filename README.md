# Student Grade Calculator v1.0

This application calculates final grades for students based on homework results and an exam grade. It provides performance benchmarks for different C++ containers and student separation strategies.

## Releases

- **v0.1**: Initial version with basic student data structures and manual input.
- **v0.2**: Refactored code into classes and header files. Added data generation (10k to 10M records) and separation into "passed" and "failed" files.
- **v0.25**: Integrated `std::list` and `std::deque` containers and performed initial speed analysis.
- **v1.0 (Final Release)**: 
    - Implemented and compared three separation strategies.
    - Optimized implementation using the `<algorithm>` library (`std::stable_partition`, `std::copy`, `std::remove_if`, etc.).
    - Comprehensive performance analysis across `vector`, `list`, and `deque`.

## Performance Analysis & Comments

Based on testing with up to 1,000,000 records:

1. **Strategy 1 (Copying)**: Easy to implement, fast, but uses double the memory as it creates two new containers.
2. **Strategy 2 (Moving & Erasing)**: 
    - **Vector/Deque**: Extremely slow (O(N^2)) due to frequent `erase()` calls shifting elements.
    - **List**: Very efficient, as `list::erase()` is O(1).
3. **Strategy 3 (Algorithm Partitioning)**: 
    - **Vector/Deque**: The fastest and most memory-efficient strategy. Uses `std::stable_partition` to group students in-place in O(N) time.
    - **Overall Winner**: `std::vector` using Strategy 3 (Stable Partition).

| Container | Strategy | Split Time (1M records) |
|-----------|----------|-------------------------|
| Vector    | 1        | ~0.10s                  |
| Vector    | 2        | >100s (Very slow)       |
| Vector    | 3        | ~0.06s                  |
| List      | 2        | ~0.01s                  |

## Usage Guide

### Prerequisites
- A C++ compiler (GCC or Clang) supporting C++17.
- `make` (for Unix) or `CMake`.

### Using Makefile (Unix)
1. Open terminal in the project directory.
2. Run `make` to compile:
   ```bash
   make
   ```
3. Run the application:
   ```bash
   ./StudentGradeCalculator
   ```
4. Follow the menu instructions to select a strategy and view benchmarks.
5. To clean up:
   ```bash
   make clean
   ```

### Using CMake (Any OS)
1. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
2. Configure and build:
   ```bash
   cmake ..
   make
   ```
3. Run:
   ```bash
   ./StudentGradeCalculator
   ```

## Repository Structure
- `src/`: Source files (`main.cpp`, `Student.cpp`, `Utils.cpp`).
- `Include/`: Header files (`Student.h`, `Utils.h`).
- `Makefile`: Build script for Unix systems.
- `CMakeLists.txt`: Cross-platform build configuration.
- `README.md`: This file.
