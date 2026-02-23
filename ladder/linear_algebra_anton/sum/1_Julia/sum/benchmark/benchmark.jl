using MyMatrixProject
using BenchmarkTools

# 1. Setup data for different scales
small_A = rand(10, 10)
small_B = rand(10, 10)

large_A = rand(1000, 1000)
large_B = rand(1000, 1000)

println("--- Small Matrix (10x10) ---")
# Use @btime to get the minimum time and memory allocation
@btime sum_matrices($small_A, $small_B)

println("\n--- Large Matrix (1000x1000) ---")
@btime sum_matrices($large_A, $large_B)
