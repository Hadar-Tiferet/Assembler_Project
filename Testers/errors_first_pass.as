; This file is a tester of the first pass of the assembler.

; All errors should be detectable in the first pass of the assembler.

Start:  dec P1

;    this line is over the maximum amount of characters for a legal line of code.

; 1. label errors:
1label:  inc r6

label:inc r6

thislabelistoolongandshouldnotpass: dec x

labe l: dec x

la@bel: dec x

Start: .data 3

: dec x


; 2. data directive errors:
L1:	.data

L2:	.data 50,

L3:	.data 50,30,

L4:	.data 50 30

L5:	.data 50 , 30, string

L6:	.data 50 , 30 not EOF

L7:	.DATA 30

L7:	.data -2899

L8:	.Data 10

. data

L9:	data 50 , 30

	.data word50 , 30

        	.data 50word , 30


; 3. string directive errors:
.string 

.string "no closure

.string "string" extra content

.string"no space"

.string "not	a valid \r string"

.string "

.string no quotation marks


; 4. extern directive errors:
A1: .extern thislabelistoolongandshouldnotpass

.externnospace

.extern notalabe!l

L3: .extern label:

p: .extern Start

.extern extra content

.extern


; 5. instruction name errors:
Dec x

DEC x

addto 3 10

super stop

.stop


; 6. invalid operands
        add  #5,#6
	
	add  %5,x
		
stop x
		
 jsr r3
 
cmp #2 #1 #5

not x x
		
P1: cmp #-185 #+3476

cmp #-1nonum85 #-45

cmp -185 #-45

cmp #-185 ^45

; in total this file contains 51 errors that should be recognized in the first pass of the assembler, including this line. 