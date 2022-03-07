/*Header file for line_second_pass.c*/
/*function prototype*/

/*second_pass_read_line:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
IC - pointer to an integer containing the current instruction count.
IC_FINAL - integer containing the final instruction count.
code_image - pointer to a linked_list type data structure containing code lines information.
symbol_table - pointer to a pointer of a table type data structure containing label information.
extern_table - pointer to a pointer of an ex_table type data structure containing information for labels defined as external.
return:
TRUE if the line was processed successfully, FALSE if encountered an error.
purpose:
go through a line in second pass, save and update relvant information to the correct data structures and return success status.*/
int second_pass_read_line(line_info *line,int *IC,int IC_FINAL,linked_list *code_image,table **symbol_table,ex_table **extern_table);