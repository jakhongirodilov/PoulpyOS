global _start;

[bits 32]
[extern simple]

_start:
    call simple 
    jmp $