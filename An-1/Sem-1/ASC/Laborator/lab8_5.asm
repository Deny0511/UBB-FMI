bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

extern exit, fopen, fclose, fprintf, printf, fscanf
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import printf msvcrt.dll
import fscanf msvcrt.dll
segment data use32 class=data
    ;Se dau doua numere naturale a si b (a, b: word, definite in segmentul de date). Sa se calculeze a/b si sa se afiseze catul si restul impartirii in urmatorul format: "Cat = <cat>, rest = <rest>"
;Exemplu: pentru a=23 si b=10 se va afisa: "Cat = 2, rest = 3"
;Valorile vor fi afisate in format decimal (baza 10) cu semn.
    format db 'Cat = <%d>,rest = <%d>',0
    a dw 23
    b dw -10 
    
    
; our code starts here
segment code use32 class=code
    start:
        xor eax,eax
        xor edx,edx 
        mov ax, [a]
        cwd
        mov bx,[b]
        idiv bx 
        push edx 
        push eax 
        push format
        call [printf]
        add esp,4*4
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
