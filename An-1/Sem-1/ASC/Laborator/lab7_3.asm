bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s1 dw 1234h, 67ABh, 89CDh
    l equ ($-s1)/2
    s2 dw 2345h, 5678h, 4567h
    d times l dw 0 
    
; Se dau doua siruri de cuvinte s1 si s2.
; Se cere sirul de cuvinte d obtinut in interpretarea cu semn, astfel:
; - d[i] = s1[i], daca s1[i] > s2[i]
; - d[i] = s2[i], altfel.

; our code starts here
segment code use32 class=code
    start:
        mov ecx,l
        jecxz final
        
        cld ; DF=0
        mov esi, s1 ; offset-ul primul element din sirul sursa s1
        mov edi, d ; offset-ul primul element din sirul destinatie d
        rep movsw ; copiez in sirul d sirul s1
        
        mov ecx, ls
        cld ; DF=0
        mov esi, s2 ; offset-ul primul element din sirul sursa s2
        mov edi, d ; offset-ul primul element din sirul destinatie d
        
        repeta:
            lodsw ; ax=<ds:esi> si esi=esi+2
            
            scasw ; cmp ax, <es:edi> si edi=edi+2
            
            jle next ; daca ax <= <es:edi> sar la urmatorul pas
            
            sub edi, 2 ; revin la pozitia la care a fost facuta comparatia
            stosw ; <es:edi>=ax si edi=edi+2
            
            next:
            
        loop repeta 
       
        final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
