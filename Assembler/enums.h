/*enums header file:
contains enumerations for ease of use and clearity of the code*/

/*
Editing note:
for registers -
when adding/deleting registers, please update the definition of reg below and make sure to keep the registers consecutive and NONE_REG at the bottom of the list, undefined (to make sure it keeps the last value in the list)
for instructions -
please update the relevant definitions below, in addition to the table in table_instructions.h
for directives -
please update the relevant definitions below, in addition to the table in table_directives.h
*/

/*instruction type*/
typedef enum instruction_types {
	/*first group*/
	FIRST_TYPE = 0,
	/*second group*/
	SECOND_TYPE = 1,
	/*third group*/
	THIRD_TYPE = 2,
	/*non valid type*/
	NONE_TYPE = -1
} instruction_type;

/*operand addressing mode*/
typedef enum addressing_modes {
	/*immediate addressing (0)*/
	IMMEDIATE_ADDRESS = 0,
	/*direct addressing (1)*/
	DIRECT_ADDRESS = 1,
	/*relative addressing (2)*/
	RELATIVE_ADDRESS = 2,
	/*register direct addressing (3)*/
	REGISTER_ADDRESS = 3,
	/*non valid addressing mode (-1)*/
	NONE_ADDRESS = -1
} addressing_mode;

/*instruction opcodes*/
typedef enum opcodes {
	/*first group*/
	MOV_OPCODE = 0,
	CMP_OPCODE = 1,
	
	ADD_OPCODE = 2,
	SUB_OPCODE = 2,
	
	LEA_OPCODE = 4,
	/*second group*/
	CLR_OPCODE = 5,
	NOT_OPCODE = 5,
	INC_OPCODE = 5,
	DEC_OPCODE = 5,
	
	JMP_OPCODE = 9,
	BNE_OPCODE = 9,
	JSR_OPCODE = 9,
	
	RED_OPCODE = 12,
	PRN_OPCODE = 13,
	/*third group*/
	RTS_OPCODE = 14,
	STOP_OPCODE = 15,
	/*non valid opcode*/
	NONE_OPCODE = -1
} opcode;

/*instruction funct*/
typedef enum functs {
	/*default*/
	NONE_FUNCT = 0,
	/*opcode 2*/
	ADD_FUNCT = 10,
	SUB_FUNCT = 11,
	/*opcode 5*/
	CLR_FUNCT = 10,
	NOT_FUNCT = 11,
	INC_FUNCT = 12,
	DEC_FUNCT = 13,
	/*opcode 9*/
	JMP_FUNCT = 10,
	BNE_FUNCT = 11,
	JSR_FUNCT = 12
} funct;
/*end of typedef*/

/*registers*/
typedef enum registers {
	R0 = 0,
	R1 = 1,
	R2 = 2,
	R3 = 3,
	R4 = 4,
	R5 = 5,
	R6 = 6,
	R7 = 7,
	NONE_REG
} reg;

/*directive type*/
typedef enum directives {
	/*.data directive*/
	DATA_DIRECTIVE,
	/*.string directive*/
	STRING_DIRECTIVE,
	/*.entry directive*/
	ENTRY_DIRECTIVE,
	/*.extern directive*/
	EXTERN_DIRECTIVE,
	/*non valid directive*/
	NONE_DIRECTIVE
} directive;

/*symbol types*/
typedef enum symbol_types {
	CODE_SYMBOL,
	DATA_SYMBOL,
	ENTRY_SYMBOL,
	EXTERN_SYMBOL
} symbol_type;