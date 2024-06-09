# MATRIX

**This project is a class for convenient work with matrices and performing various operations with them.**

* The code is written according to google style
* Handling of exceptional situations
* The program includes such operations on matrices as:
  + Checks matrices for equality with each other - `bool eq_matrix(const S21Matrix& other)`
  + Adds the second matrix to the current one - `void sum_matrix(const S21Matrix& other)`
  + Subtracts another matrix from the current one - `void sub_matrix(const S21Matrix& other)`
  + Multiplies the current matrix by a number - `void mul_number(const double num)`
  + Multiplies the current matrix by the second matrix - `void mul_matrix(const S21Matrix& other)`
  + Creates a new transposed matrix from the current one and returns it - `S21Matrix transpose()`
  + Calculates the algebraic addition matrix of the current one and returns it - `S21Matrix calc_complements()`
  + Calculates and returns the determinant of the current matrix - `double determinant()`
  + Calculates and returns the inverse matrix - `S21Matrix inverse_matrix()`
* Constructors and destructors such as:
  + A basic constructor that initialises a matrix of some predefined dimension - `S21Matrix()`
  + Parametrized constructor with number of rows and columns - `S21Matrix(int rows, int cols)`
  + Copy constructor - `S21Matrix(const S21Matrix& other)`
  + Move constructor - `S21Matrix(S21Matrix&& other)`
  + Destructor - `~S21Matrix()`
* The program includes such overloaded operators as:
  + Addition of two matrices - '+'
  + Subtraction of one matrix from another - '-'
  + Matrix multiplication and matrix multiplication by a number - '*'
  + Checks for matrices equality - '=='
  + Assignment of values from one matrix to another one - '='
  + Addition assignment - '+='
  + Difference assignment - '-='
  + Multiplication assignment - '*='
  + Indexation by matrix elements (row, column) - '(int i, int j)'

# Project Instructions

## Overview

This project involves building and testing a C++ library (`s21_matrix_oop.a`). The project uses Google Test for unit testing, lcov for generating code coverage reports, and tools like `leaks` (on macOS) and `valgrind` (on Linux) for memory leak detection. The provided `Makefile` automates these tasks.

## Prerequisites

Ensure you have the following tools installed:

- `g++` (GNU Compiler Collection)
- `make`
- `Google Test` (`gtest`)
- `lcov` (for generating coverage reports)
- `clang-format` (for code formatting)
- `valgrind` (for memory leak checking on Linux)
- `leaks` (for memory leak checking on macOS)

## Makefile Targets

The `Makefile` includes several targets to automate the workflow:

### 1. `all`
The default target that cleans the project, builds the library, and runs the tests.
```sh
make all
```

### 2. `build`
Compiles the source files.
```sh
make build
```

### 3. `s21_matrix_oop.a`
Creates the static library `s21_matrix_oop.a`.
```sh
make s21_matrix_oop.a
```

### 4. `test`
Compiles and runs the unit tests.
```sh
make test
```

### 5. `gcov_report`
Generates a code coverage report.
```sh
make gcov_report
```
This will create an HTML report in the `report` directory.

### 6. `clang`
Checks the code formatting according to the Google style.
```sh
make clang
```

### 7. `clean`
Cleans up all generated files.
```sh
make clean
```

### 8. `leak`
Checks for memory leaks using `leaks` (macOS only).
```sh
make leak
```

### 9. `valgrind`
Checks for memory leaks using `valgrind` (Linux only).
```sh
make valgrind
```

***

This project was developed by a student of School 21: jereyji