bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 5
    b db 6
    c db 3
    d dw 8

; our code starts here
segment code use32 class=code
    start:
        ; ...[(d/2)*(c+b)-a*a]/b
       mov ax,[d]   ; AX=d
       mov bl,2     ;BL=2
       div byte bl  ;AX=d/2
       mov bl,[c]   
       add bl,[b]   ;BL=c+b
       mul bl       ; AX=(d/2)*(c+b)
       mov bx,ax    
       mov al,[a]    ; AL=a
       mul al        ;AX=a*a
       sub bx,ax      ; BX=(d/2)*(c+b)-a*a
       mov ax,bx     
       mov bl,[b]     ;BL=b
       div byte bl    ;AX=[(d/2)*(c+d)-a*a]/b
       
       
       
       
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
