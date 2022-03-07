/*Global type definitions:
structures that will make the program more convenient and easier to read.*/

/*note:
the use of unsigned integer instead of signed integer is done in order to make sure to manually enforce the use of twos compelemt method when representing negative numbers.*/

/*code_word:
ARE - 3 bits wide field containing the ARE status of a code word.
destination_addressing - 2 bits wide field containing the destination addressing mode of a code word.
source_addressing - 2 bits wide field containing the source addressing mode of a code word.
funct - 4 bits wide field containing the funct description of a code word.
opcode - 4 bits wide field containing the opcode description of a code word.
description:
representation of a code word (first word in an instruction line) alongside ARE status indicator, using bit fields*/
typedef struct code_word {
	unsigned int ARE: 3;
	unsigned int destination_addressing: 2;
	unsigned int source_addressing: 2;
	unsigned int funct: 4;
	unsigned int opcode: 4;
} code_word;

/*data_word:
ARE - 3 bits wide field containing the ARE status of a code word.
content - 12 bits wide field containing the content of a word containing data in a 12 bit system.
description:
representation of a data_word alongside ARE status indicator, using bit fields.*/
typedef struct data_word {
	unsigned int ARE: 3;
	unsigned int content: 12;
} data_word;

/*machine_word:
code - code_word type argument containing information of a code word in a 12 bit system.
data - data_word type argument containing information of a data word in a 12 bit system.
description:
representation of a machine word under a 12 bit system, which is either a code word or a data word, using union.*/
typedef union machine_word{
	code_word code;
	data_word data;
} machine_word;

/*line_info:
file_name - string containing the name of the file currently reviewed.
line_number - integer containing the number of the line being currently reviewed within file_name.
content - array containing the line being currently reviewed.
index - integer representing the next character to be read in content.
description:
a structure made for convenience, holding the required information to process a line and give detailed information about potential errors.*/
typedef struct line_info {
	/*name of the file*/
	char *file_name;
	/*line number in file*/
	int line_number;
	/*the content of the line*/
	char content[MAX_LINE_LENGTH+1];
	int index;
} line_info;

/*tnode:
word - machine_word type argument containing a word representation in a 12 bit system.
next - pointer to the next node in the structure.
description:
a data type to be used for each individual node within the linked_list data structure. each node contains the content of current node and a pointer to the next node in the structure.*/ 
typedef struct node {
	machine_word word;
	struct node *next;
} tnode;

/*linked_list:
head - ponter to a tnode type argument containing the head of the linked list.
current - pointer to a tnode type argument containing the current (or last to be viewed) node in the linked list.
description:
a data type containing two nodes from the linked list, the head of the list and the currently viewed node, for easier access.*/
typedef struct linked_list {
	tnode *head;
	tnode *current;
} linked_list;

/*table:
address - integer containing the address (IC or DC) of the symbol of the current entry in the table.
name - string containing the name of the current entry in the table.
type - value corresponding to the symbol type of the current entry, as defined in enums.h.
next - pointer to the next entry in the table.
description:
a data structure containing the relevant information of each label in the file.*/ 
typedef struct entry {
	int address;
	char *name;
	symbol_type type;
	struct entry *next;
} table;

/*ex_table:
address - integer containing the address (IC after addresses were updated) of the argument calling the current entry in the table.
name - string containing the name of the current entry (extern symbol) in the table.
next - pointer to the next entry in the ex_table.
description:
a data structure, based on the table structure, containing the relevant information of each external label in the file.*/ 
typedef struct external_table {
	int address;
	char *name;
	struct external_table *next;
} ex_table;
