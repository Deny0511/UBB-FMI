bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s dd 11234456h, 22345567h, 33456678h
    l equ ($-s)/4
    d times l dd 0
; Se da un sir de dublucuvinte s.
; Se cere sirul d ale carui elemente sunt cuvinte obtinute in interpretarea cu semn, astfel:
; - octetul inferior din d[i] este suma octetilor inferiori ai cuvintelor din fiecare dublucuvant al sirului s
; - octetul superior din d[i] este suma octetilor superiori ai cuvintelor din fiecare dublucuvant al sirului s

; our code starts here
segment code use32 class=code
    start:
        mov ecx,l
        jecxz final
         
        cld                 ; DF = 0
        mov esi, s          ; ESI = offset-ul primului element din sirul s
        mov edi, d          ; EDI = offset-ul primului element din sirul d
    repeta:
        ; incarc cuvantul inferior
        lodsw               ; AX = <DS:ESI> si ESI = ESI+2 (pentru ca DF = 0)
        
        mov bl, al          ; mut octetul inferior in BL
        mov bh, ah          ; mut octetul superior in BH
        
        ; incarc cuvantul superior
        lodsw               ; AX = <DS:ESI> si ESI = ESI+2 (pentru ca DF = 0)
        
        ; calculez suma in AX
        add al, bl          ; calculez suma octetilor inferiori in AL
        add ah, bh          ; calculez suma octetilor superiori in AH
        
        ; stochez rezultatul in sirul d
        stosw               ; <ES:EDI> <- suma in AX si EDI = EDI+2
        
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
