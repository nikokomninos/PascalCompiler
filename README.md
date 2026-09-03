# CSC 645 - Pascal Compiler

This repo contains the source code for my CSC645 Compiler Construction
project. This compiler lexes, parses, and compiles a subset of Pascal.

## Building

### Prerequisites

- A C++ compiler that supports C++20 (such as `g++` or `clang++`)
- GNU Make or a compatible `make` command

# Build Steps

1. From the repository root, build the compiler with:

```sh
make
```

This creates the `pascalc` executable in the repository root.

## Running

Pass a source file as the program's only argument:

```sh
./pascalc example.txt
```
