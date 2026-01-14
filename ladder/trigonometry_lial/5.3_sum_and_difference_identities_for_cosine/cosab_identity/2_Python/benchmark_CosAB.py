#!/usr/bin/env python3

import timeit
import math
from CosAB import cos_ab

# 1. Define the input values
angle_a = math.pi / 3
angle_b = math.pi / 4

# 2. Define the tasks to measure using lambdas (anonymous functions)
#    We use lambdas so we can pass arguments easily.
task_custom = lambda: cos_ab(angle_a, angle_b)
task_native = lambda: math.cos(angle_a + angle_b)

# 3. Run the benchmark
#    number=1000000 means "run this code 1 million times"
print("Benchmarking... please wait.")

time_custom = timeit.timeit(task_custom, number=1000000)
time_native = timeit.timeit(task_native, number=1000000)

# 4. Print results
print(f"Custom cos_ab time:  {time_custom:.4f} seconds")
print(f"Native math.cos time: {time_native:.4f} seconds")

# 5. Calculate speed difference
print(f"Native is {time_custom / time_native:.2f}x faster")
