section .text
global parse_game

parse_game:
    ; Input:
    ;   rdi - pointer to the input string
    ;   rsi, rdx, rcx - upper bounds for red, green, and blue

    ; Initialize counts for red, green, and blue
    xor r8, r8  ; Red count
    xor r9, r9  ; Green count
    xor r10, r10 ; Blue count

parse_loop:
    ; Skip characters until a digit is found
    cmp byte [rdi], 0
    je  end_parse
    cmp byte [rdi], ';'
    je  reset_counts
    cmp byte [rdi], '0'
    jl  next_char
    cmp byte [rdi], '9'
    jg  next_char

    ; Parse the number
    movzx rax, byte [rdi]
    sub rax, '0'
    imul r8, r8, 10
    add r8, rax

    ; Determine the color
    movzx rax, byte [rdi + 2]
    cmp rax, 'r'
    je  red
    cmp rax, 'g'
    je  green
    cmp rax, 'b'
    je  blue
    jmp next_char

red:
    ; Add the parsed number to red count
    add r9, r8
    jmp next_char

green:
    ; Add the parsed number to green count
    add r10, r8
    jmp next_char

blue:
    ; Add the parsed number to blue count
    add r11, r8
    jmp next_char

reset_counts:
    ; Reset counts to zero when encountering ';'
    xor r8, r8
    xor r9, r9
    xor r10, r10
    jmp next_char

next_char:
    ; Move to the next character
    inc rdi
    jmp parse_loop

end_parse:
    ; Check if counts exceed the upper bounds
    cmp r9, rsi
    ja  false_exit
    cmp r10, rdx
    ja  false_exit

    ; Set the result (0 or 1) in rax
    mov rax, 1
    ret

false_exit:
    ; Set the result (0 or 1) in rax
    xor rax, rax
    ret
