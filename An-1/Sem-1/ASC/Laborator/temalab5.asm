bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
   ;Se dau doua siruri de caractere S1 si S2. Sa se construiasca sirul D ce contine toate elementele din S1 care nu apar in S2
   ; S1: '+', '4', '2', 'a', '8', '4', 'X', '5'
   ; S2: 'a', '4', '5'
   ; D: '+', '2', '8', 'X'
   s1 db '+', '4', '2', 'a', '8', '4', 'X', '5'
   l1 equ $-s1
   s2 db 'a', '4', '5'
   l2 equ $-s2
   d times l1 db 0


; our code starts here
segment code use32 class=code
    start:
    
    mov ebx,0
    mov edi,d
    mov ecx,l1    ;punem lungimea in ECX pentru a putea realiza bucla loop de ecx ori
    cmp ecx,0
    je sfarsit
    
    repeta:
        mov al,[s1+ebx]   
        cmp al,0          
        je sfarsit        
        
        mov esi,0
        mov edx,l2
        mov ah,0
        
    bucla: 
        cmp esi,edx
        je next1
          
        cmp al,[s2+esi]
        je found 
          
        inc esi         ;incrementam ESI 
        jmp bucla
       
    found:
        mov ah,1
          
    next1:
        cmp ah,0
        jne next2  
        mov [edi],al
        
        inc edi    ; incrementam EDI
        
    next2:
        inc ebx     ;incrementam EBX
          
        loop repeta 
   sfarsit:   
         
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
