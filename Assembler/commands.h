/*Header file for commands.c*/
/*function prototype*/

/*get_commands:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
IC - pointer to an integer containing the current instruction count.
code_image - pointer to a linked_list type data structure containing code lines information.
return:
TRUE if a valid command line was processed, FALSE if an error was encountered.
purpose:
process a line as a command line by taking the next string in line,evaluating it as an instruction and sending the information for further evaluation.*/
int get_commands(line_info *line,int *IC,linked_list *code_image);

/*commands_second_pass:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
IC - pointer to an integer containing the current instruction count.
IC_FINAL - integer containing the final instruction count.
code_image - pointer to a linked_list type data structure containing code lines information.
symbol_table - pointer to a pointer of a table type data structure containing label information.
extern_table - pointer to a pointer of an ex_table type data structure containing information for labels defined as external.
return:
TRUE if the line was processed as an instruction line successfully, FALSE if encountered an error.
purpose:
process an instruction line in second pass, send information for further inspection when required.*/
int commands_second_pass(line_info *line,int *IC,int IC_FINAL,linked_list *code_image,table **symbol_table,ex_table **extern_table);