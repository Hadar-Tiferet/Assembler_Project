; file ps3.as
.data -100
.entry LIST
.extern W
STR: .string "abcd"
MAIN: add r3, LIST
LOOP: prn #48
lea W, r6
inc r6
mov r3, K
sub r1, r4
bne END
LIST: .data 6, -9
cmp K, #-6
bne %END
dec W
.entry MAIN
K: .data 31
jmp %LOOP
add L3, L3
END: stop
.extern L3