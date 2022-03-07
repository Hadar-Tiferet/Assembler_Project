/*Header file for type_recognition.c*/
/*function prototype*/

/*memory allocation*/
/*malloc_or_exit:
input:
size - long integer containing the amount of memory requested for allocation.
return:
pointer to the dynamically allocated memory, or an exit from the program if allocation could not be possible.
purpose:
allocate a requested amount of memory for use or exit the program if allocation could not be done.*/
void *malloc_or_exit(long size);
/*end of memory allocation*/

/*is_alphanumeric_string:
input:
string - string containing an argument suspected as containing only digits and letters.
i - index of the last character of string.
return:
TRUE if string is alphanumeric, FALSE if string is not alphanumeric.
purpose:
check if a given string is alphanumeric.*/
int is_alphanumeric_string(char *string,int i);

/*is_reserved_word:
input:
string - string containing an argument suspected as a reserved word.
return:
TRUE if string is one of the reserved words, FALSE if string is not one of the reserved words, as defined in enums.h, table_directives.h and table_instructions.h.
purpose:
check if a given string is a reserved word.*/
int is_reserved_word(char *string);

/*is_int:
input:
string - string containing an argument suspected as an int.
return:
TRUE if string describes a valid integer, FALSE if string is not an integer or an empty string.
purpose:
check if a given string describes an integer.*/
int is_int(char *string);