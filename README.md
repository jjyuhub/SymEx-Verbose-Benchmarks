# SymEx-Verbose-Benchmarks

This repository contains a toy C application (`toy.c`) designed to trigger a wide range of SMT (Satisfiability Modulo Theories) problems for symbolic execution engines. The goal is to evaluate maximum verbosity and detailed SMT profiling across different engines such as KLEE, angr, S2E, and Triton.

## Overview

The toy application includes diverse SMT challenges:
- **Symbolic Integer Constraints:** Branching with comparisons, modulus, division, and non-linear arithmetic.
- **Array Constraints:** Uses a symbolic array with conditional checks.
- **Bit-level Operations:** Forces bit-level reasoning.
- **Floating-point Constraints:** Tests handling of floating-point symbolic values.
- **Function Call Constraints:** Includes a helper function to introduce additional branches.
- **Division Checks:** Incorporates division with safety checks.

## Getting Started

### Prerequisites

To run symbolic execution on this application, you may need:
- **KLEE** (for LLVM bitcode symbolic execution).
- **angr** (for binary analysis).
- **S2E** (for system-level symbolic execution).
- **Triton** (for dynamic symbolic execution).
- **Clang/LLVM** to compile `toy.c` to LLVM bitcode (for KLEE).

### Compiling for KLEE

Compile `toy.c` to LLVM bitcode:
```bash
clang -I/usr/include/klee -emit-llvm -c toy.c -o toy.bc
