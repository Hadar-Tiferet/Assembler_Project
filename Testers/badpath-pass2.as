; This file is intended to check the bad-path of the assembler.

; Each line (except a few) contains an error in the assembly language code.
; A comment preceding each line explains the error.

; All errors should be detectable in the second pass of the assembler.

; Run the assembler on this file, and verify that it catches all the errors.
; Your assembler messages need not be identical to the comments in this file.

; Disclaimer: this list of errors is not necessarily exhaustive; 
;             you are encouraged to identify additional errors.

; 1. this line is ok (label X is ignored, warning may be issued in 1st pass)
X:     .extern DATA1

; 2. this line is ok (label Y is ignored, warning may be issued in 1st pass)
Y:     .entry START

; 3. this line is ok
       .entry END
	   
; 4. this line is ok
Z:	   .string "abc"

; 5. this line is ok (DATA1 is an external label)
START:  add  DATA1,r1

; 6. undefined label as first operand
        add  Q,r2

; 7. undefined label as second operand
        add  r3,Q

; 8. undefined label as first operand (declaration of label X was ignored)
        add  X,r4

; 9. undefined label as second operand (declaration of label Y was ignored)
        add  r5,Y

; 10. this line is ok (it is ok to designate the same entry more than once)
       .entry END

; 11. this line is ok
END:   stop

; 12. undefined label 
       .entry Q

; 13. undefined label (declaration of label X was ignored) 
       .entry X

; 14. undefined label (declaration of label Y was ignored)  
       .entry Y
	   
; 15. invalid entry label (label set as extern can not be also set to entry)  
       .entry DATA1
	   
; 16. invalid relative mode label (relative label can not be of type data)  
       bne %Z
	   
; 17. this line is ok  
       bne %START