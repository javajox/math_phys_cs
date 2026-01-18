# 1. Assemble the library
yasm -f elf64 -g dwarf2 math_lib.asm -o math_lib.o

# 2. Compile the C test runner
gcc -c test_runner.c -o test_runner.o

# 3. Link them together (with math library -lm)
gcc test_runner.o math_lib.o -o run_tests -lm

# 4. Execute
./run_tests
