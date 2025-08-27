bits 32

global modul       

 
segment code use32 class=code
    modul:
       mov edx,0
       mov eax,[esp+4]
       mov ecx,100
       div ecx 
       mov edx,0
       mov ecx,10
       div ecx 
       mov eax,edx 
       
       ret 4
              
           
           