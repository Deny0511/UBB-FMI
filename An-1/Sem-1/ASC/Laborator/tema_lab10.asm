bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit ,printf,scanf,modul       ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    
import printf msvcrt.dll
import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Sa se citeasca un sir de numere intregi s1 (reprezentate pe dublucuvinte) in baza 10. Sa se determine si sa se afiseze sirul s2 compus din cifrele aflate pe poziţia sutelor în fiecare numar intreg din sirul s1.
    ;Exemplu:
    ;Sirul s1: 5892, 456, 33, 7, 245
    ;Sirul s2: 8, 4, 0, 0, 2
     
      n dd 0
      format db '%d',0
      format_afisare db '%d ',0
      
      message  db "Scrieti un sir de numere in baza 10:", 0
      s1 times 50 dd 0
      
      
      
     
; our code starts here
segment code use32 class=code
    start:
        push dword message
        call [printf]
        add esp,4
        mov edi,s1
        repeta:
            push dword n
            push dword format
            call [scanf]
            add esp,4*2
            
            mov eax,[n]
            cmp eax,0
            je next
            stosd 
            jmp repeta 
        
        next:
        cld
        mov esi,s1
        
        repeta2:
           lodsd 
           cmp eax,0
           je final
           mov ebx,eax
           
           push ebx
           call modul
          
           push eax 
           push dword format_afisare
           call [printf]
           add esp,4*2
          jmp repeta2
        
        final:
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
