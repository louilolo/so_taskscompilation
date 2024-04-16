nasm -f elf64 -o media.o media.asm
ld -o media media.o

.section .data
msg1:
    .ascii "Digite o primeiro numero: \n"
msg2:
    .ascii "Digite o segundo numero: \n"
msg3:
    .ascii "A media é "
format:
    .ascii "%.2f\n"
buffer:
    .skip 10
media_str:
    .skip 10

.section .text
.globl _start

_start:
    # Escreve a mensagem para o 1º número
    movq $1, %rdi
    leaq msg1(%rip), %rsi
    movq $msg1_len, %rdx
    movq $1, %rax
    syscall

    # Lê o primeiro número
    movq $0, %rdi
    leaq buffer(%rip), %rsi
    movq $10, %rdx
    movq $0, %rax
    syscall

    # Converte o primeiro número para inteiro
    call atoi

    # Armazena o primeiro número em n1
    movl %eax, n1(%rip)

    # Escreve a mensagem para o 2º número
    movq $1, %rdi
    leaq msg2(%rip), %rsi
    movq $msg2_len, %rdx
    movq $1, %rax
    syscall

    # Lê o segundo número
    movq $0, %rdi
    leaq buffer(%rip), %rsi
    movq $10, %rdx
    movq $0, %rax
    syscall

    # Converte o segundo número para inteiro
    call atoi

    # Armazena o segundo número em n2
    movl %eax, n2(%rip)

    # Calcula a média
    cvtsi2sd n1(%rip), %xmm0
    cvtsi2sd n2(%rip), %xmm1
    addsd %xmm1, %xmm0
    divsd $2.0, %xmm0
    movsd %xmm0, media(%rip)

    # Formata a média
    leaq format(%rip), %rdi
    movq $0, %rax
    call printf

    # Escreve a média
    movq $1, %rdi
    leaq media_str(%rip), %rsi
    movq $10, %rdx
    movq $1, %rax
    syscall

    # Termina o programa
    movq $0, %rdi
    movq $60, %rax
    syscall

atoi:
    # Converte a string para inteiro
    xorl %eax, %eax
    movq %rsi, %rdi
    xorl %ebx, %ebx
.loop:
    movb (%rdi), %cl
    testb %cl, %cl
    je .done
    imulq $10, %rax
    subb $'0', %cl
    addq %rcx, %rax
    incq %rdi
    jmp .loop
.done:
    ret

.section .bss
n1:
    .zero 4
n2:
    .zero 4
media:
    .zero 8

.section .note.GNU-stack,"",@progbits

