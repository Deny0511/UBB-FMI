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
    ; Sa se citeasca de la tastatura doua numere a si b (in baza 10) si sa se calculeze: (a+b) / (a-b). 
    ;Catul impartirii se va salva in memorie in variabila "rezultat"
    ;(definita in segmentul de date). Valorile se considera cu semn.
    ;Sa se citeasca de la tastatura un numar in baza 10 si sa se afiseze valoarea acelui numar in baza 16.
;    Exemplu: Se citeste: 28; se afiseaza: 1C
    format db '%d',0
    format_afisare db '%s',0
    a dd 0
    s times 5 db '0' 
    b dd 0
; our code starts here
segment code use32 class=code
    start:
        push dword a 
        push dword format 
        call [scanf]
        add esp,4*2
        
        mov eax,[a]
        cdq
        mov ebx,16
        mov edi,s 
        add edi,5
        std
        repeta:
             idiv ebx
             cmp edx,9
             ja next
             add edx,'0'
             xchg eax,edx
             stosb
             xchg eax,edx
             cdq 
             cmp eax,0
             je final 
             jmp repeta 
             next:
             add edx,'A'-10
             xchg eax,edx
             stosb 
             xchg eax,edx
             cdq
             cmp eax,0
             jne repeta
             
             
        final:     
        push dword s
        call [printf]
        add esp,4*1
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
