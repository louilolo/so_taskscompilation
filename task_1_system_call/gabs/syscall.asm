section .data
    arquivo db 'exemplo.txt', 0
    format_string db 'O arquivo possui %d palavras.', 10, 0

section .text
    global _start

_start:
    ; Abrir o arquivo
    mov rdi, arquivo       ; Nome do arquivo
    mov rsi, O_RDONLY      ; tipo de abertura
    call open
    mov r12, rax           ; ele salva o descritor de arquivo em r12

leitura_loop:
    ; Ler do arquivo para o buffer
    mov rdi, r12           ; descritor de arquivo
    lea rsi, [buffer]      ; buffer
    mov rdx, BUFFER_SIZE   ; tamanho do buffer
    call read
    test rax, rax
    jle fim_programa      ; se read retornar 0 ou menos, termina

    ; Contar palavras
    mov rcx, rax          ; tamanho dos bytes lidos
    mov rsi, buffer
contagem_loop:
    cmp byte [rsi], 0
    je proximo_byte
    cmp byte [rsi], ' '
    je eh_espaco
    cmp byte [rsi], '\n'
    je eh_espaco
    cmp byte [rsi], '\t'
    je eh_espaco
    jmp proximo_byte

eh_espaco:
    cmp byte [prev_char], ' '
    je proximo_byte
    inc qword [word_count]

proximo_byte:
    mov byte [prev_char], byte [rsi]
    inc rsi
    loop contagem_loop

    jmp leitura_loop

fim_programa:
    ; a gente ver o número de palavras
    mov rdi, format_string
    mov rsi, [word_count]
    call printf

    ; fechar o arquivo
    mov rdi, [r12]
    call close

    ; sair
    mov rdi, 0
    call exit
