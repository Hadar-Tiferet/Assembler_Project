/*Header file for directives.c*/
/*function prototype*/

/*get_directive:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
return:
the number of directive described as the next string in line, NONE_DIRECTIVE if no directive was found, as defined in enums.h.
purpose:
locate the type of directive present in line and progress the line beyond it.*/
directive get_directive(line_info *line);

/*execute_directive:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
DC - pointer to an integer containing the current directive count.
data_image - pointer to a linked_list type data structure containing data lines information.
symbol_table - pointer to a pointer of a table type data structure containing label information.
d - number corresponding to the directive present in line, as defined in enums.h.
return:
TRUE if directive line was processed correctly, FALSE if an error was found.
purpose:
process a directive line by passing along information to the correct function if needed and return read status.*/
int execute_directive(line_info *line,int *DC,linked_list *data_image,table **symbol_table,directive d);

/*valid_entry:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
symbol_table - pointer to a pointer of a table type data structure containing label information.
return:
TRUE if an argument was updated as an entry symbol in symbol_table correctly, FALSE if argument is already set as extern or does not appear as a label in the file.
purpose:
during the second pass, update the type of an entry symbol as such in the symbol table, print a relevant message in case of an error.*/
int valid_entry(line_info *line,table **symbol_table);