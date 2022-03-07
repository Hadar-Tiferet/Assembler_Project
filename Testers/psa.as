; file ps.as file without extern and entry labels.

MAIN: add r3, LIST
LOOP: prn #48
lea MAIN, r6
inc r6
mov r3, K
sub r1, r4
bne END
cmp K, #-6
bne %END
dec LIST
jmp %LOOP
add K, K
END: stop
STR: .string "abcd"
LIST: .data 6, -9
.data -100
K: .data 31