#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "cos_ab.h" // Include the header to use the function

// Universal PI definition
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define EPSILON 0.000001

int are_close(double a, double b) {
    return fabs(a - b) < EPSILON;
}

int main() {
    printf("Running tests from separate file...\n");

    // Test 1: Simple known value
    assert(are_close(cos_ab(0, 0), 1.0));
    
    // Test 2: Math identity check
    assert(are_close(cos_ab(M_PI/2, 0), 0.0));

    printf("All tests passed!\n");
    return 0;
}
