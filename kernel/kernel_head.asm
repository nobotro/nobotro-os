[bits 32]
global krand
global ksleep
[extern main]

 

loadkernel:
call main

jmp $


 


krand:
 
push ebp
mov  ebp, esp
RDTSC;reads the processor's time-stamp counter into EDX:EAX.xor,we use only eax
mov ebx,dword [ebp+8];start
mov ecx,dword [ebp+12];end
xor edx,edx
sub ecx,ebx
div ecx;div eax to ecx;quotient => EAX = 11 ;remainder => EDX = 3
add edx,ebx
mov eax,edx
mov esp, ebp
pop ebp
ret



ksleep:
push ebp
mov  ebp, esp
mov ecx,dword [ebp+8];start
;1000 microwami=1 miliwami
imul ecx,1000
lp:
out 0x80,al; need 1 milisecond
 
loop lp

mov esp, ebp
pop ebp
ret


