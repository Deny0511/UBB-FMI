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
    ;Sa se citeasca de la tastatura un numar in baza 10 si un numar in baza 16. 
    ;Sa se afiseze in baza 10 numarul de biti 1 ai sumei celor doua numere citite. Exemplu:
;a = 32 = 0010 0000b
;b = 1Ah = 0001 1010b
;l32 + 1Ah = 0011 1010b
;Se va afisa pe ecran valoarea 4.
    a dd 0
    b dd 0 
    format1 db '%d',0
    format2 db '%X',0
; our code starts here
segment code use32 class=code
    start:
        push dword a 
        push dword format1 
        call [scanf]
        add esp,4*2
        
        push dword b  
        push dword format2 
        call [scanf]
        add esp,4*2
       
        mov eax,[a]
        add eax,[b]
        xor ebx,ebx 
        mov ecx,16
        repeta:
           test eax,1
           jz next 
           inc ebx
           next:           
           shr eax,1
           jnz repeta 
       push ebx
       push dword format1
       call [printf]
       add esp,4*2
       
       
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
