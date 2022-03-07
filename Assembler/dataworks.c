#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "global.h"
#include "enums.h"
#include "global_def.h"
#include "type_recognition.h"
#include "dataworks.h"

/*definitions*/
/*maximum character size of a valid label*/
#define MAX_LABEL_LENGTH 31
/*maximum size of a positive signed integer within a 12 bit word*/
#define MAX_POSITIVE_INT 2047
/*end of defines*/

/*returns the next string in line, while advancing the line index accordingly, requires freeing the memory afterwards*/
char *get_string(line_info *line)
{
	/*a string can be as big as the max length minus the part of the line that is already covered plus one for termination sign*/
	char *s=(char *)malloc_or_exit(sizeof(char)*(MAX_LINE_LENGTH+1-(line->index))); 
	int i;
	for(i=0;line->content[line->index]!=' ' && line->content[line->index]!='\t' && line->content[line->index]!=',' && line->content[line->index]!='\0';i++,line->index++)
	{
		s[i]=line->content[line->index];
	}
	s[i]='\0';
	return s;
}

void skip_blank(line_info *line)
{
	while (line->content[line->index]==' ' || line->content[line->index]=='\t')
	{
		line->index++;
	}
}

/*returns current End Of File status for a given line*/
int check_EOF(line_info *line)
{
	skip_blank(line);
	if(line->content[line->index]=='\0')
	{
		return TRUE;
	}
	return FALSE;
}

/*checks the next word in line as a label, returns a pointer to it if valid syntax for a label was found or NULL if no attempt to declare a label has been made*/
char *get_label_suspect(line_info *line)
{
	int i=line->index;/*before attempting to locate a label*/
	int j=0;
	char *label=(char *)malloc_or_exit(sizeof(char)*(MAX_LINE_LENGTH+1-(line->index)));
	while (line->content[line->index]!=':' && line->content[line->index]!='\0' && line->content[line->index]!=' ' && line->content[line->index]!='\t')
	{
		label[j]=line->content[line->index];
		line->index++;
		j++;
	}
	label[j]='\0';/*end of string*/

	/*if the was an attempt to define a label*/
	if(line->content[line->index] == ':')
	{
		line->index++;/*move index to the next character after ':'*/
		return label;
	}
	else
	{
		/*no label decleration was found*/
		line->index=i;/*returns to starting index of line*/
		free(label);
		return NULL;
	}
}

int valid_label_name(char *string,int i)
{
	return (i<=(MAX_LABEL_LENGTH + 1) && isalpha(string[0]) && is_alphanumeric_string(string,i) && !is_reserved_word(string));
}

unsigned int get_twos_complement(unsigned int x)
{
	return (~x)+1;
}

int string_to_int(line_info *line,char *string,machine_word *word) /*line is passed to the function only for errors*/
{
	unsigned int x;
	int i=0;
	if(!is_int(string))
	{
		if(string[0]=='\0')
		{
			fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nMissing an integer argument\n",line->file_name,line->line_number);
		}
		else
		{
			fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\n%s is not a valid integer\n",line->file_name,line->line_number,string);
		}
		return FALSE;
	}
	if(string[i] == '-')
	{
		i++;
		x=(unsigned int)atoi(string+i);
		if(x<=MAX_POSITIVE_INT+1)
		{
			word->data.ARE=1;
			word->data.content=get_twos_complement(x);
			return TRUE;
		}
		else
		{
			fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nNumber -%u is too big to be represented as a signed integer in a 12 bit word\n",line->file_name,line->line_number,x);
			return FALSE;
		}
	}
	if(string[i] == '+')
	{
		i++;
	}
	x=(unsigned int)atoi(string+i);
	if(x<=MAX_POSITIVE_INT)
	{
		word->data.ARE=1;
		word->data.content=x;
		return TRUE;
	}
	else
	{
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nNumber %u is too big to be represented as a signed integer in a 12 bit word\n",line->file_name,line->line_number,x);
		return FALSE;
	}
}

/*skip_label: a function for second pass, will set the line index to the next character after a label if exists*/
void skip_label(line_info *line)
{
	int i=line->index;
	while (line->content[i]!=':' && line->content[i]!='\0' && line->content[i]!=' ' && line->content[i]!='\t')
	{
		i++;
	}
	if(line->content[i]==':')
	{
		line->index=i+1;/*if a label was found - skip to the character after it*/
	}
}