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
    ;Sa se citeasca de la tastatura un octet si un cuvant. Sa se afiseze pe ecran daca bitii octetului citit se regasesc consecutiv printre bitii cuvantului. Exemplu:
;a = 10 = 0000 1010b
;b = 256 = 0000 0001 0000 0000b
;Pe ecran se va afisa NU.
;a = 0Ah = 0000 1010b
;b = 6151h = 0110 0001 0101 0001b
;Pe ecran se va afisa DA (bitii se regasesc pe pozitiile 5-12).
    a db 0
    b dw 0 
    format_da db 'DA',0
    format_nu db 'NU',0
    format db '%d',0
    ; our code starts here
segment code use32 class=code
    start:
        push dword a 
        push dword format 
        call [scanf]
        add esp,4*2
        
        push dword b  
        push dword format 
        call [scanf]
        add esp,4*2
        
        mov al,[a]
        mov bx,[b]
        
        mov ecx,9
        
        
        repeta:    
            mov ax,cx
            and ax,0ffh
            cmp al,bl 
            je afisare
            shr bx,1
            loop repeta 
           push dword format_nu
           call [printf]
           add esp,4
        afisare:
           push dword format_da
           call [printf]
           add esp,4
    
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
