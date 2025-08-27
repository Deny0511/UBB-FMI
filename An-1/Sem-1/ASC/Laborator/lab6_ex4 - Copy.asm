bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s1 db 7, 3, 9, 1, 5
    l1 equ $-s1
    s2 db 2, 4, 6, 8, 10
    l2 db $-s2 
    
; Se dau 2 siruri de numere intregi s1 si s2 de lungimi egale.
; Se cere sirul de numere intregi d obtinut astfel:
; - d[i] = s1[i] - s2[i], daca s1[i] > s2[i]
; - d[i] = s2[i] - s1[i], altfel.

; our code starts here
segment code use32 class=code
    start:
    mov ecx,l1
    cmp ecx,0
    je final
    
    mov edx,l2 
    cmp edx,0
    je final 
    
    repeta:
    
    
    
    
    
      loop repeta 
    
    
    
    
    
    
    final:
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
