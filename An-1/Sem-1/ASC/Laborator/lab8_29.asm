bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        


extern exit, fopen, fclose, fprintf, printf, scanf
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
segment data use32 class=data
    ; Se citesc de la tastatura trei numere a, m si n (a: word, 0 <= m, n <= 15, m > n).
;    Sa se izoleze bitii de la m-n ai lui a si sa se afiseze numarul intreg reprezentat de acesti bitii in baza 10.
    a dd 0
    m dd 0
    n dd 0
    format db '%d',0
    
; our code starts here
segment code use32 class=code
    start:
        push dword a 
        push dword format 
        call [scanf]
        add esp,4*2
        
        push dword m 
        push dword format 
        call [scanf]
        add esp,4*2
        
        push dword n
        push dword format 
        call [scanf]
        add esp,4*2
        
        mov ecx,[m]
        mov ebx,[n]
        sub ecx,ebx 
        sub ecx,1
        
        mov eax,1
        shl eax,cl
        sub eax,1
        mov ecx,[n]
        shl eax,cl
        
        movzx ebx,word [a]
        and ebx,eax
        
        push ebx 
        push dword format
        call [printf]
        add esp,4*2
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
