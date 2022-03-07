/*Header file for line_first_pass.c*/
/*function prototype*/

/*first_pass_read_line:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
IC - pointer to an integer containing the current instruction count.
DC - pointer to an integer containing the current directive count.
code_image - pointer to a linked_list type data structure containing code lines information.
data_image - pointer to a linked_list type data structure containing data lines information.
symbol_table - pointer to a pointer of a table type data structure containing label information.
return:
TRUE if the line was processed successfully, FALSE if encountered an error.
purpose:
go through a line in first pass, save relvant information to the correct data structures and return success status.*/
int first_pass_read_line(line_info *line,int *IC,int *DC,linked_list *code_image,linked_list *data_image,table **symbol_table);