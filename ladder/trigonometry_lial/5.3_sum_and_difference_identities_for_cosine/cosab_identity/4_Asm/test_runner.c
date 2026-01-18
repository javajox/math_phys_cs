#include <stdio.h>
#include <math.h>
#include <assert.h>

// Declare the external assembly function
extern double calc_formula(double a, double b);

// A tolerance for floating point comparisons
#define EPSILON 0.000001

void run_test(double a, double b, char* test_name) {
    // 1. Run Assembly Implementation
    double asm_result = calc_formula(a, b);

    // 2. Run Reference Implementation (C math library)
    // Formula: cos(A)cos(B) - sin(A)sin(B)
    double expected = cos(a)*cos(b) - sin(a)*sin(b);
    
    // Note: The formula is also the identity for cos(A + B)
    // double expected = cos(a + b);

    // 3. Compare
    double diff = fabs(asm_result - expected);
    
    if (diff < EPSILON) {
        printf("[PASS] %s (A=%.2f, B=%.2f) -> Result: %.6f\n", 
               test_name, a, b, asm_result);
    } else {
        printf("[FAIL] %s (A=%.2f, B=%.2f)\n", test_name, a, b);
        printf("       Expected: %.6f\n", expected);
        printf("       Got:      %.6f\n", asm_result);
    }
}

int main() {
    printf("Running Assembly Unit Tests...\n");
    printf("------------------------------\n");

    // Test Case 1: Zeros
    run_test(0.0, 0.0, "Zeros");

    // Test Case 2: Standard Radians
    run_test(1.0, 2.0, "Random Radians");

    // Test Case 3: Pi/2 (90 degrees) - Should be 0
    // cos(90) is 0, so cos(A+B) where A+B=PI/2 should be near 0
    run_test(1.570796, 0.0, "Pi/2 Check");

    // Test Case 4: Negative values
    run_test(-1.0, -1.0, "Negatives");

    return 0;
}
