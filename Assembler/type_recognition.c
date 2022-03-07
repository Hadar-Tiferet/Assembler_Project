#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "global.h"
#include "enums.h"
#include "table_instructions.h"
#include "table_directives.h"
#include "type_recognition.h"
/*static function prototype*/

/*is_directive:
input:
string - string containing an argument suspected as a directive.
return:
TRUE if string describes a valid directive, FALSE if string is not a directive, as defined in table_directives.h.
purpose:
check if a given string describes a directive.*/
static int is_directive(char *string);

/*is_instruction:
input:
string - string containing an argument suspected as an instruction.
return:
TRUE if string describes a valid instruction, FALSE if string is not an instruction, as defined in table_instructions.h.
purpose:
check if a given string describes an instruction.*/
static int is_instruction(char *string);

/*is_register:
input:
string - string containing an argument suspected as a register.
return:
TRUE if string describes a valid register, FALSE if string is not a register, as defined in enums.h.
purpose:
check if a given string describes a register.*/
static int is_register(char *string);

/*end of static function prototype*/


/*memory allocation*/
void *malloc_or_exit(long size)
{
	void *p = malloc(size);
	if(p == NULL)
	{
		fprintf(ERROR_OUTPUT_FILE,"Error: Memory allocation failed."); /*could not allocate new memory*/
		exit(1);
	}
	return p;
}


int is_alphanumeric_string(char *string,int i)
{
	int j;
	for (j=0;j<i;j++)
	{
		if(!isalpha(string[j]) && !isdigit(string[j]))
		{
			return FALSE;
		}
	}
	return TRUE;
}

int is_reserved_word(char *string)
{
	if(is_instruction(string) || is_register(string) || is_directive(string))
	{
		return TRUE; /*the string is a reserved word*/
	}
	else
	{
		return FALSE;
	}
}



int is_int(char *string)
{
	int i=0;
	if(string[i] == '+' || string[i] == '-')
	{
		string++;
	}
	while (string[i] != '\0' && string[i] != ',')
	{
		if(!isdigit(string[i]))
		{
			return FALSE;
		}
		i++;
	}
	return i > 0;/*i==0 means empty string*/
}

static int is_directive(char *string)
{
	int i;
	for(i=0;directive_table[i].name != NULL;i++)
	{
		if(strcmp(string,directive_table[i].name) == 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}

static int is_instruction(char *string)
{
	int i;
	for(i=0;instruction_table[i].name!=NULL;i++)
	{
		if(strcmp(string,instruction_table[i].name)==0)
		{
			return TRUE;
		}
	}
	return FALSE;
}

static int is_register(char *string)
{
	if(string[0] == 'r' && isdigit(string[1]) && string[2]== '\0')
	{
		int digit = string[1] - '0';/*converting to an int*/
		if(digit >= R0 && digit < NONE_REG)
		{
			return TRUE;
		}
	}
	return FALSE; /*not a register*/
}