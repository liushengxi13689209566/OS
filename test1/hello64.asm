global _start
_start:
    jmp short string

code:
    pop rsi
    mov rax,1
    mov rdi,1
    mov rdx,13
    syscall

    int3

string:
    call code
    db 'Hello world!',0x0a
