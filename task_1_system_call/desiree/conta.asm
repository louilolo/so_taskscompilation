;nasm -f elf64 conta.o conta.asm
;ld -s -o conta conta.o
;./conta

section .data
    msg1 dq "digite a palavra a ser identificada", 0xA
    len1 equ $ - msg1
    msd2 dq "numero de ocorrencias da palavra solicitada = ", 0xA
    len2 equ $ - msg2
    arquivo dq "arquivo.txt", 0
    contador db 0
    erro db 0

section .bss
    palavra resb 50
    caractere resb 1
    fd resb 4
    ocorrencias resb 8


section .text
global _start

_start:
    ;escreve a mensagem
    mov rax, 4                 ;Metodo de escrita(sys_write)
    mov rbx, 1                 ;Metodo de saida(std_out)
    mov rcx, [msg1]            ;Mensagem
    mov rdx, len1               ;Tamanho
    int 0x80                   ;syscall

    ;le a palavra
    mov rax, 3    ;SYS_READ
    mov rbx, 0    ;STD_IN
    mov rcx, palavra ;Variavel que recebe input
    mov rdx, 50   ;Tamanho maximo do input
    int 0x80      ;syscall

    ;abre arquivo
    mov rax, 5
    mov rbx, arquivo
    mov rbc, 0
    int 0x80
    mov fd, rax

leitura_loop:
    ;le arquivo
    mov rbx, [fd]
    mov rax, 3
    mov rcx, caractere
    mov rdx, 1
    int 0x80
    cmp rax, 0
    je pos_loop
    jmp if

if:
    ;ve se eh o fim da palavra
    cmp caractere, 32 ;ve se eh espaco
    je else
    cmp caractere, 9 ;ve se eh \t
    je else
    cmp caractere, 10 ;ve se eh \n
    je else
    cmp caractere, 0 ;ve se eh \0
    je else

    ;compara caracteres
    mov rsi, palavra      ; Coloca o endereço de 'palavra' em rsi
    add rsi, contador     ; Adiciona o valor de 'contador' ao endereço
    cmp byte [caractere], byte [rsi] 
    jnz nao_iguais
    inc contador
    jmp else

    nao_iguais:
        inc erro

else:
    mov contador, 0
    cmp erro, 0
    jnz nao_achou
    inc ocorrencias

    nao_achou:
    mov erro, 0
    jmp leitura_loop


pos_loop:
    ;fecha arquivo
    mov rax, 6   ;CLOSE_FILE
    mov rbx, [fd]
    int 0x80

    mov rax, 4                 ;Metodo de escrita(sys_write)
    mov rbx, 1                 ;Metodo de saida(std_out)
    mov rcx, [msg2]            ;Mensagem
    mov rdx, len2               ;Tamanho
    int 0x80                   ;syscall

    mov rax, 4                 ;Metodo de escrita(sys_write)
    mov rbx, 1                 ;Metodo de saida(std_out)
    mov rcx, [ocorrencias]            ;Mensagem
    mov rdx, 8               ;Tamanho
    int 0x80                   ;syscall

fim:
    ;return 0
    mov rax, 1
    mov rbx, 0
    int 0x80

