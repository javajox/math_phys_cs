default rel
global calc_formula    ; Export the symbol so C can see it

section .text

; -----------------------------------------------------------------------------
; Subroutine: calc_formula
; C Signature: double calc_formula(double A, double B);
; -----------------------------------------------------------------------------
calc_formula:
    sub     rsp, 24             ; Align stack & reserve space

    ; --- 1. Compute for A ---
    movsd   qword [rsp], xmm0   ; Move A to stack
    fld     qword [rsp]         ; Load A to FPU
    fsincos                     ; st0=cosA, st1=sinA

    ; --- 2. Compute for B ---
    movsd   qword [rsp+8], xmm1 ; Move B to stack
    fld     qword [rsp+8]       ; Load B to FPU
    fsincos                     ; st0=cosB, st1=sinB, st2=cosA, st3=sinA

    ; --- 3. Math Logic ---
    fmul    st0, st2            ; st0 = cosB * cosA
    fxch    st1                 ; Swap to get sinB at top
    fmul    st0, st3            ; st0 = sinB * sinA
    
    fsubp   st1, st0            ; st1 = cosTerm - sinTerm (result in st1, pop st0)
    
    ; --- 4. Cleanup & Return ---
    fstp    qword [rsp]         ; Pop result to memory
    fstp    st0                 ; Clean garbage
    fstp    st0                 ; Clean garbage

    movsd   xmm0, qword [rsp]   ; Return result in xmm0
    add     rsp, 24
    ret
