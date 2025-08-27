bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 8A9Fh    
    b db 9Bh    

; our code starts here
segment code use32 class=code
    start:
        ;10.Sa se inlocuiasca bitii 0-3 ai octetului B cu bitii 8-11 ai cuvantului A.
        mov bl,[b]
        mov ax,[a]
        and ax, 0000_1111_0000_0000b
        shr ax,8
        and bl,al
        mov al,[b]
        and al,11110000b
        or bl,al
        mov [b],bl
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
