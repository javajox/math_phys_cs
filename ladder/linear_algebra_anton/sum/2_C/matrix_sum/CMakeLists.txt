cmake_minimum_required(VERSION 3.10)
project(MatrixSumProject C)

# Set the C standard (C99 or C11 are standard choices)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Tell CMake where to look for your project's header files (.h)
include_directories(include)

# ---------------------------------------------------------
# 1. CORE FUNCTIONALITY
# ---------------------------------------------------------
# Create a library from your core files. 
add_library(matrix_sum_lib src/matrix_sum.c)

# ---------------------------------------------------------
# 2. TESTING SETUP
# ---------------------------------------------------------
# Create an executable for your tests, compiling your test file AND Unity
add_executable(test_matrix_sum 
    test/test_matrix_sum.c 
    test/vendor/unity/unity.c
)

# Tell the test executable specifically where to find unity.h
target_include_directories(test_matrix_sum PRIVATE test/vendor/unity)

# Link your core matrix_sum library to the test executable
target_link_libraries(test_matrix_sum matrix_sum_lib)

# ---------------------------------------------------------
# 3. CLION TEST INTEGRATION (CTest)
# ---------------------------------------------------------
# This enables CLion's built-in test runner GUI
enable_testing()
add_test(NAME MatrixSumTests COMMAND test_matrix_sum)
