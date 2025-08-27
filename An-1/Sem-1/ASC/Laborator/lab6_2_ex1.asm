bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s db 'abcdef'
    l equ $-s
    d times l db 0
; Se da un sir de caractere s.
; Se cere sirul de caractere d obtinut prin copierea sirului s.

; our code starts here
segment code use32 class=code
    start:
       mov ecx,l
       jecxz final
       cld         ;DF=0
       mov esi,s   ; adresa sir sursa
       mov edi,d    ; adresa sir dest
       
       repeta:
           ;sau: movsb
           lodsb       ; al=s[i]+ inc esi 
           ;
           ; 
           stosb       ; al=s[i]+inc esi 
           ;
           ;
           loop repeta 
        
       
       final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
