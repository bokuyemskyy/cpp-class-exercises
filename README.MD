# Programming Languages 2 – Class & Homework

This repository contains my classwork and homework tasks for the *Programming Languages 2* course.

## Build Instructions

To automatically build all tasks into executables:

```bash
cmake -Bbuild
cmake --build build
```

To automatically remove all built executables:

```bash
cmake -Bbuild
cmake --build build --target clear_bins
```