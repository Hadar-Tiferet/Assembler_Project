/*table_instructions header file:
contains a table of the allowed instructions and their unique access in the code.*/

struct instruction_lookup {
	char *name;
	instruction_type type;
	opcode opcode;
	funct funct;
	addressing_mode destination_addressing[4];
	addressing_mode source_addressing[4];
};

/*each table entry contains:
name - string containing the name of the instruction.
type - enum defined in enums.h containing the type of the instruction. (controlling how many arguments the instruction requires)
opcode - enum defined in enums.h containing the designated opcode of the instruction.
funct - enum defined in enums.h containing the designated funct of the instruction.
addressing_addressing - array containing the allowed destination addressing modes for the instruction.
source_addressing - array containing the allowed source addressing modes for the instruction.*/
static struct instruction_lookup instruction_table[]= {
	{"mov", FIRST_TYPE, MOV_OPCODE, NONE_FUNCT, {DIRECT_ADDRESS, REGISTER_ADDRESS, NONE_ADDRESS}, {IMMEDIATE_ADDRESS, DIRECT_ADDRESS, REGISTER_ADDRESS, NONE_ADDRESS}},
	{"cmp", FIRST_TYPE, CMP_OPCODE, NONE_FUNCT, {IMMEDIATE_ADDRESS, DIRECT_ADDRESS, REGISTER_ADDRESS, NONE_ADDRESS}, {IMMEDIATE_ADDRESS, DIRECT_ADDRESS, REGISTER_ADDRESS, NONE_ADDRESS}},
	{"add", FIRST_TYPE, ADD_OPCODE, ADD_FUNCT, {DIRECT_ADDRESS, REGISTER_ADDRESS, NONE_ADDRESS}, {IMMEDIATE_ADDRESS, DIRECT_ADDRESS, REGISTER_ADDRESS, NONE_ADDRESS}},
	{"sub", FIRST_TYPE, SUB_OPCODE, SUB_FUNCT, {DIRECT_ADDRESS, REGISTER_ADDRESS, NONE_ADDRESS}, {IMMEDIATE_ADDRESS, DIRECT_ADDRESS, REGISTER_ADDRESS, NONE_ADDRESS}},
	{"lea", FIRST_TYPE, LEA_OPCODE, NONE_FUNCT, {DIRECT_ADDRESS, REGISTER_ADDRESS, NONE_ADDRESS}, {DIRECT_ADDRESS, NONE_ADDRESS}},
	{"clr", SECOND_TYPE, CLR_OPCODE, CLR_FUNCT, {DIRECT_ADDRESS, REGISTER_ADDRESS, NONE_ADDRESS}, {NONE_ADDRESS}},
	{"not", SECOND_TYPE, NOT_OPCODE, NOT_FUNCT, {DIRECT_ADDRESS, REGISTER_ADDRESS, NONE_ADDRESS}, {NONE_ADDRESS}},
	{"inc", SECOND_TYPE, INC_OPCODE, INC_FUNCT, {DIRECT_ADDRESS, REGISTER_ADDRESS, NONE_ADDRESS}, {NONE_ADDRESS}},
	{"dec", SECOND_TYPE, DEC_OPCODE, DEC_FUNCT, {DIRECT_ADDRESS, REGISTER_ADDRESS, NONE_ADDRESS}, {NONE_ADDRESS}},
	{"jmp", SECOND_TYPE, JMP_OPCODE, JMP_FUNCT, {DIRECT_ADDRESS, RELATIVE_ADDRESS, NONE_ADDRESS}, {NONE_ADDRESS}},
	{"bne", SECOND_TYPE, BNE_OPCODE, BNE_FUNCT, {DIRECT_ADDRESS, RELATIVE_ADDRESS, NONE_ADDRESS}, {NONE_ADDRESS}},
	{"jsr", SECOND_TYPE, JSR_OPCODE, JSR_FUNCT, {DIRECT_ADDRESS, RELATIVE_ADDRESS, NONE_ADDRESS}, {NONE_ADDRESS}},
	{"red", SECOND_TYPE, RED_OPCODE, NONE_FUNCT, {DIRECT_ADDRESS, REGISTER_ADDRESS, NONE_ADDRESS}, {NONE_ADDRESS}},
	{"prn", SECOND_TYPE, PRN_OPCODE, NONE_FUNCT, {IMMEDIATE_ADDRESS, DIRECT_ADDRESS, REGISTER_ADDRESS, NONE_ADDRESS}, {NONE_ADDRESS}},
	{"rts", THIRD_TYPE, RTS_OPCODE, NONE_FUNCT, {NONE_ADDRESS}, {NONE_ADDRESS}},
	{"stop", THIRD_TYPE, STOP_OPCODE, NONE_FUNCT, {NONE_ADDRESS}, {NONE_ADDRESS}},
	{'\0', NONE_TYPE, NONE_OPCODE, NONE_FUNCT, {NONE_ADDRESS}, {NONE_ADDRESS}}
};