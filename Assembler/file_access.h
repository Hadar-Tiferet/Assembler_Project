/*Header file for file_access.c*/
/*function prototype*/

/*add_file_extention:
input:
string - string containing a file name without the required extention.
extention - string containing the required file extention.
return:
pointer to dynamically allocated memory containing string followed by extention, NULL if encountered an error.
purpose:
combine the given name with the given extention to create a legal file name*/
char *add_file_extention(char *string,char *extention);

/*get_line:
input:
in - FILE pointer containing the character stream of the current file.
line - pointer to a line_info type argument containing the information relevant for processing a line.
return:
the latest character to be read from the file.
purpose:
copy the next line in the current file into line, allow for further checking and indication of EOF.*/
char get_line(FILE *in,line_info *line);

/*file creation*/
/*create_files:
input:
name - string containing a file name without the required extention.
IC - integer containing the instruction count.
DC - integer containing the directive count.
code_image - pointer to a linked_list type data structure containing code lines information.
data_image - pointer to a linked_list type data structure containing data lines information.
symbol_table - pointer to a pointer of a table type data structure containing label information.
extern_table - pointer to a pointer of an ex_table type data structure containing information for labels defined as external.
purpose:
prepare the necesary information and send info further to the currect functions for the process of creating output files.*/
void create_files(char *name,int IC,int DC,linked_list *code_image,linked_list *data_image,table **symbol_table,ex_table **extern_table);
