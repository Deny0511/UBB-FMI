bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; (a+c-d)+d-(b+b-c)
    a db 7
    b db 5
    c db 2
    d db 3

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ah, [a]  ;AH=a
        add ah, [c]  ;AH=a+c
        sub ah, [d]  ; AH= a+c-d
        add ah, [d]  ; AH=a+c-d+d
        mov al, [b]  ; AL=b
        add al, [b]  ; AL=b+b
        sub al, [c]  ; AL=b+b-c
        sub ah,al    ; AH=AH-AL
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
