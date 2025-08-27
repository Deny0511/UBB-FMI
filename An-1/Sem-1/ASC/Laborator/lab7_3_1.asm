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
        mov ecx, len
        jecxz final
        
        cld                 ; DF = 0
        mov esi, s1         ; ESI = offset-ul primului element din sirul s1
        mov edi, s2         ; EDI = offset-ul primului element din sirul s2
        mov ebx, 0          ; index pentru sirul destinatie d
    repeta:
        lodsw               ; AX = <DS:ESI> si ESI = ESI + 2 (pentru ca DF = 0)
        scasw               ; CMP AX, <ES:EDI> si EDI = EDI + 2 (pentru ca DF = 0)
        jle mai_mic
        
        mov [d+ebx], ax     ; d[i] <- s1[i]
        ;add ebx, 2          ; trec la urmatorul cuvant din sirul d
        jmp continua
        
    mai_mic:
        mov ax, [s2+ebx]    ; ax = s2[i]
        mov [d+ebx], ax     ; d[i] <- s2[i]
        ;add ebx, 2          ; trec la urmatorul cuvant din sirul d
    
    continua:
        add ebx, 2          ; trec la urmatorul cuvant din sirul d
    loop repeta
    
    final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
