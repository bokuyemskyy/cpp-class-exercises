## Programming Languages 2 course

This repository is my classwork for the *Programming Languages 2* course

### Requirements

* **C++ Standard:** C++20 (Compiler must support C++20 features)
* **CMake Version:** 3.25 or newer

### Build Instructions

1) To build all the tasks:

```bash
git clone https://github.com/bokuyemskyy/cpp-class-exercises
cd cpp-class-exercises
cmake -Bbuild
cmake --build build
```
Each binary will appear in a correspondent task's directory.

2) To run the main "hub" binary:

```bash
./hub/main
```

3) To automatically remove all the built executables:

```bash
cmake --build build --target clear_bins
```

