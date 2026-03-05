cmake_minimum_required(VERSION 3.20)
project(vectorops C)

# Note: C23 is the newest standard. Ensure your compiler (GCC 14+ or Clang 18+) supports it!
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 1. The Library
add_library(vectorops STATIC vectorops.c)

# Use '.' or CMAKE_CURRENT_SOURCE_DIR to tell users of this lib where headers are
target_include_directories(vectorops PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 2. Find and link math to the LIBRARY, not just the test
find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    # We use PUBLIC so that anything linking to vectorops also links to the math lib
    target_link_libraries(vectorops PUBLIC ${MATH_LIBRARY})
endif()

# 3. The Test Executable
add_executable(test_vectorops test_vectorops.c unity.c)

# Now test_vectorops gets 'vectorops' AND 'm' automatically!
target_link_libraries(test_vectorops PRIVATE vectorops)
target_compile_definitions(test_vectorops PRIVATE UNITY_INCLUDE_DOUBLE)

# 4. Testing setup
include(CTest) # This automatically calls enable_testing()
add_test(NAME vectorops_tests COMMAND test_vectorops)