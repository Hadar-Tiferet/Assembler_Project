; tester file ps4.as.

Start:    add r1,Label1
Data1: .data     	1,2,3   ,  	4, -5  ,-99	     
Data2: .data 2047 , -2048


;this is a comment
;cmp r2, Data1 another comment

Label1: mov Data2,r2
;label2 not in use,a label before extern or entry decleration is ignored.
               Label2: .extern exLabel
lea exLabel ,     r3
L00P: bne %Start

jmp L00P

cmp r2 ,r3

;  this line contains the maximum amount of characters for a legal line of code.

L2: .entry Label1
label2: .string "this is a string"
; empty strings are allowed
.string ""
  prn #42
 
.entry label3
sub exLabel , exLabel
clr r4
rts
red r5
prn label2
not Data1
label3: 		.string "!string % *contains'symbols' $ & {}\n \r\w"  abcdefg"
.string "a"
sub #8 ,r2
add Data1, L00P
bne %END
END: stop