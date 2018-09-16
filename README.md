# QSolver

A simple library for solving quadratic equations and a cli for this library.

## Requirements

To build QSolver you will need CMake version 3.12.1 or newer and a C++ compiler.

If you want to build documentation, you will also need:
  - Doxygen version 1.8.13 or newer
  - Tools listed [here](https://www.stack.nl/~dimitri/doxygen/manual/formulas.html) to render formulas

## Build

Just run cmake to create a project for your ide and then build the `all` target as usual.

You can also set the following cmake options:
  - `BUILD_TESTS` if this option is on, cmake will generate a `test` target which will run tests.
  - `BUILD_DOC` if this option is on, cmake will use doxygen to generate the documentation for the project and put it to the `doc` directory in the output folder.
    Make sure you have the tools required to build the documentation before setting this option.


## Run

After building the `all` target a directory named `bin` will appear in the output folder. This directory contains `qsolver` binary which is the command line interface for the QSolver library.


```
qsolver [-h] [-p] A B C

Solve a quadratic equation in form A * x^2 + B * x + C = 0
Print newline-separated roots of the equation.

positional arguments:
 A, B, C     coefficients of the equation

optional arguments:
 -h, --help  show this help message and exit
 -p, --precision set real numbers compare precision
```
