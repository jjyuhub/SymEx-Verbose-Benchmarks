#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef KLEE
#include <klee/klee.h>
#endif

// A helper function that computes the absolute difference.
int foo(int a, int b) {
    if (a > b) {
        return a - b;
    } else {
        return b - a;
    }
}

int main() {
    int x, y;
    int z[10];
    double d;

#ifdef KLEE
    // Make variables symbolic for SMT analysis.
    klee_make_symbolic(&x, sizeof(x), "x");
    klee_make_symbolic(&y, sizeof(y), "y");
    klee_make_symbolic(z, sizeof(z), "z");
    klee_make_symbolic(&d, sizeof(d), "d");
#else
    // Fallback values for non-KLEE runs.
    x = rand();
    y = rand();
    for (int i = 0; i < 10; i++) {
        z[i] = rand();
    }
    d = (double)rand() / RAND_MAX;
#endif

    // Branching based on integer values.
    if (x > 100) {
        if (y < 50) {
            if (x % 2 == 0) {
                printf("Case 1: Even x, x = %d, y = %d\n", x, y);
            } else {
                printf("Case 1: Odd x, x = %d, y = %d\n", x, y);
            }
        } else {
            if (foo(x, y) > 10) {
                printf("Case 2: foo(x,y) > 10\n");
            } else {
                printf("Case 2: foo(x,y) <= 10\n");
            }
        }
    } else {
        if (x + y > 200) {
            printf("Case 3: Sum > 200\n");
        } else {
            // Non-linear constraint: multiplication of symbolic variables.
            if (x * y == 0) {
                printf("Case 4: x * y == 0\n");
            } else {
                // Array constraint.
                if (z[0] + z[1] > 100) {
                    printf("Case 5: Array sum > 100\n");
                } else {
                    printf("Case 5: Array sum <= 100\n");
                }
            }
        }
    }

    // Bit-level operations.
    int a = x & 0xF;
    int b = y | 0xF0;
    if (a == b) {
        printf("Bit-level equality: a == b\n");
    } else {
        printf("Bit-level inequality: a != b\n");
    }

    // Floating point constraint.
    if (d > 0.0 && d < 1.0) {
        printf("Double between 0 and 1\n");
    } else {
        printf("Double not between 0 and 1\n");
    }

    // Non-linear arithmetic: check if x^2 equals y^2.
    if (x * x - y * y == 0) {
        printf("x^2 equals y^2\n");
    } else {
        printf("x^2 does not equal y^2\n");
    }

    // Division constraint with a check to avoid divide-by-zero.
    if (y != 0) {
        if ((x / y) > 3) {
            printf("Division constraint satisfied: x/y > 3\n");
        } else {
            printf("Division constraint not satisfied: x/y <= 3\n");
        }
    } else {
        printf("y is zero, skipping division.\n");
    }

    return 0;
}
