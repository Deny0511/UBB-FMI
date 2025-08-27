bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
;9. Se de cuvantul A si octetul B. Sa se obtina dublucuvantul C astfel:
;bitii 0-3 ai lui C coincid cu bitii 6-9 ai lui A
;bitii 4-5 ai lui C au valoarea 1
;bitii 6-7 ai lui C coincid cu bitii 1-2 ai lui B
;bitii 8-23 ai lui C coincid cu bitii lui A
;bitii 24-31 ai lui C coincid cu bitii lui B

     a dw 0111_0010_0111_1111b
     b db 1010_1100b
     c dd 0
; our code starts here
segment code use32 class=code
    start:
        ;bitii 0-3 ai lui C coincid cu bitii 6-9 ai lui A
     mov ebx,0
     mov eax,0
     mov ax,[a]
     and ax, 0000_0011_1100_0000b
     shr ax,6                                                 
     or ebx,eax
     
     ;bitii 4-5 ai lui C au valoarea 1
     or ebx,110000b
     
     ;bitii 6-7 ai lui C coincid cu bitii 1-2 ai lui B
     mov eax,0
     mov al,[b]
     and eax,0000_0110b
     shl eax,5
     or ebx,eax
     
     ;bitii 8-23 ai lui C coincid cu bitii lui A
     mov eax,0
     mov ax,[a]
     shl eax,8
     or ebx,eax
     
     ;bitii 24-31 ai lui C coincid cu bitii lui B
     mov eax,0
     mov al,[b]
     shl eax,24
     or ebx,eax
     
     mov [c],ebx      
     
     
     
     
     
     
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
