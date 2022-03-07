/*Header file for dataworks.c*/
/*function prototype*/

/*get_string:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
return:
pointer to a dynamically allocated memory containing the next valid string in line.
purpose:
return the next string in line and update the line index to point to the next character after the string.*/
char *get_string(line_info *line);

/*skip_blank:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
purpose:
update the line index to point to the next non blank character in line.*/
void skip_blank(line_info *line);

/*check_EOF:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
return:
TRUE if the next character in line is EOF, FALSE otherwise.
purpose:
return the current end of file status for the line.*/
int check_EOF(line_info *line);

/*get_label_suspect:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
return:
pointer to a dynamically allocated memory containing a suspected label string, NULL if no attempt to declare a label has been made.
purpose:
return a suspected label string for a given line and update the line index to point to the next character after the label.*/
char *get_label_suspect(line_info *line);

/*valid_label_name:
input:
string - a string containing a suspected label name.
i - index of the last character of string.
return:
TRUE if string is a valid label name by syntax, FALSE if string can not be a label name.
purpose:
determine whether string can be a valid label.*/
int valid_label_name(char *string,int i);

/*get_twos_complement:
input:
x - unsigned integer.
return:
unsigned integer containing the twos complement value of x.
purpose:
return the twos complement value of a given integer (made to make sure negative numbers are set using the twos complement method).*/
unsigned int get_twos_complement(unsigned int x);

/*string_to_int:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
string - a string containing a suspected integer.
word - pointer to a machine_word type argument for containing the integer held by string.
return:
TRUE if string was successfully transfered into an integer, FALSE if no valid integer was found.
purpose:
convert a valid string into an integer ready to insert in the correct data structure.*/
int string_to_int(line_info *line,char *string,machine_word *word);

/*skip_label:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
purpose:
update the line index to point after a label declaration, if present.*/
void skip_label(line_info *line);