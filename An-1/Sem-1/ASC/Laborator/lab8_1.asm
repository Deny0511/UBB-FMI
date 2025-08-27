bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
      n db -120 
      format_a db "n = %d",0
      c db 'H'
      format_c db "n = %c",0
      
      n1 dd 111
      n2 dd 222
      n3 dd 333
      format_n dd ("%d %d %d,n1,n2,n3 "),13,10,0
      
      s1  db "Ana are mere"
      format_s dd ("%d %d %d,n1,n2,n3 ")
; our code starts here
segment code use32 class=code
    start:
    ; afisez un intreg
    ;printf("%d",n )
        xor eax,eax 
        mov al, [n]
        cbw
        cwde
        push eax 
        push format_a
        
        call [printf] ;apelul functiei
        add esp, 2*4 ;eliberarea argumentelor
        
        ;afisez mai multi intregi
        ;printf("%d %d %d,n1,n2,n3 ")
        mov eax,[n3]
        push eax
        mov eax,[n2]
        push eax
        mov eax,[n1]
        push eax
        push format_n    
        call [printf]
        add esp,2*4
        
        ;afisez un sir
        ;printf("%s,s1")
        push dword s1
        push dword format_s
        call [printf]
        add esp,2*4
        
        ;afisez un caracter 
        ;print("%c",c)
        
        xor eax,eax
        mov al,[c]
        push eax
        push format_c
        call [printf]
        add esp,2*4
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
