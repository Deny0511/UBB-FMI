bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;Se da un sir de caractere format din litere mici.
    ;Sa se transforme acest sir in sirul literelor mari corespunzator.
    sir db 'a','b','c' ; ='abcde' ;sirul de caractere
    len equ $-sir
   ; sir2 db 'XYZ
   ; len equ $-sir2             ; numarul de octeti 
    
; our code starts here
segment code use32 class=code
    start:
        mov ecx,len ; pt ca loop sa functioneze in ecx trebuie sa fie o valoare >0
        ;sau mov ecx,5
      ;  jecxz sfarsit   ; nu trebuie depasit 127 biti, asta e short
        cmp ecx,0
        je sfarsit       ; asta e near
        mov ebx,0   ; ca si i=0; se poate folosi ESI
        repeta:
            mov al,[sir+ebx]
            sub al, 'a'-'A';transform in litera mare
            mov [sir+ebx],al 
            inc ebx
            loop repeta
        sfarsit:
    
    
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
