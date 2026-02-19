;; yasm -f elf64 -g dwarf2 matrix_sum.asm -o matrix.o
;; ld matrix.o -o matrix
;; gdb -q ./matrix

section .data
    matrix_A dd 1, 2, 3, 4
    matrix_B dd 5, 6, 7, 8

    total_elements equ 4

section .bss
    matrix_C resd total_elements

section .text
    global _start

_start:
    mov rcx, total_elements
    xor rsi, rsi

.add_loop:
    mov eax, dword [matrix_A + rsi*4]
    add eax, dword [matrix_B + rsi*4]
    mov dword [matrix_C + rsi*4], eax
    inc rsi
    loop .add_loop

_done:

    mov rax, 60
    xor rdi, rdi
    syscall

