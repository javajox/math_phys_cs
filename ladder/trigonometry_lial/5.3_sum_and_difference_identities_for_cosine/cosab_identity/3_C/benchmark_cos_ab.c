#include <stdio.h>
#include <time.h>      // Required for clock()
#include "cos_ab.h"    // Your function header

#define ITERATIONS 10000000 // 10 Million loops

int main() {
    double a = 1.5;
    double b = 2.5;
    
    // volatile prevents the compiler from skipping the loop
    // because it "thinks" the result is unused.
    volatile double result = 0; 

    printf("Starting benchmark (%d iterations)...\n", ITERATIONS);

    // 1. Start the timer
    clock_t start_time = clock();

    // 2. Run the workload
    for (int i = 0; i < ITERATIONS; i++) {
        result = cos_ab(a, b);
    }

    // 3. Stop the timer
    clock_t end_time = clock();

    // 4. Calculate duration
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Total time: %f seconds\n", time_taken);
    printf("Average time per call: %.9f seconds\n", time_taken / ITERATIONS);
    
    // Print result so the compiler doesn't delete the calculation
    printf("Last result (ignore this): %f\n", result); 

    return 0;
}
