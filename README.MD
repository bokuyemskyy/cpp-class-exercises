## Programming Languages 2 course

This repository is my classwork for the *Programming Languages 2* course

### Requirements

* **C++ Standard:** C++23 (Compiler must support C++23 features)
* **CMake Version:** 3.25 or newer

### Build Instructions

1) To automatically build all tasks into executables:

```bash
cmake -Bbuild
cmake --build build
```

Each binary will appear in a correspondent task's directory.

2) To automatically remove all built executables:

```bash
cmake -Bbuild
cmake --build build --target clear_bins
```

