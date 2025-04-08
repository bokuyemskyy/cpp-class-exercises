# Programming Languages 2 – Class & Homework

This repository contains my classwork and homework tasks for the *Programming Languages 2* course.

## Build Instructions

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