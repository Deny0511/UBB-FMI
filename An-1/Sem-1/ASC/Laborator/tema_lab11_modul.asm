bits 32

global _cifra_sutelor
extern _printf

segment data use32 class=data
    format_afisare db '%d ',0

segment code use32 class=code
    
_cifra_sutelor:
    push ebp
    mov ebp,esp
    
       mov eax,[ebp+8]
       mov ecx,100
       div ecx 
       mov edx,0
       mov ecx,10
       div ecx 
       mov eax,edx 
       
       push eax 
       push dword format_afisare
       call _printf
       add esp,4*2
       
    mov esp,ebp
    pop ebp 
    ret 