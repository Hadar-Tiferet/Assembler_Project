#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "global.h"
#include "enums.h"
#include "table_directives.h"
#include "global_def.h"
#include "data_structures.h"
#include "dataworks.h"
#include "directives.h" 
/*static function prototype*/

/*execute_data_directive:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
DC - pointer to an integer containing the current directive count.
data_image - pointer to a linked_list type data structure containing data lines information.
return:
TRUE if current line was a valid data directive line and information was saved correctly, FALSE if an error was found.
purpose:
process data directive line, saving the appropriate data into data image and updating DC accordingly.*/
static int execute_data_directive(line_info *line,int *DC,linked_list *data_image);

/*execute_string_directive:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
DC - pointer to an integer containing the current directive count.
data_image - pointer to a linked_list type data structure containing data lines information.
return:
TRUE if current line was a valid string directive line and information was saved correctly, FALSE if an error was found.
purpose:
process string directive line, saving the appropriate data into data image and updating DC accordingly.*/
/*specific execution for string directives*/
static int execute_string_directive(line_info *line,int *DC,linked_list *data_image);

/*end of static function prototype*/ 


directive get_directive(line_info *line)
{
	int i;
	char *string;
	string=get_string(line);
	for(i=0;directive_table[i].name != NULL;i++)
	{
		if(strcmp(string,directive_table[i].name) == 0)
		{
			free(string);
			return directive_table[i].type;
		}
	}
	if(string[0]=='\0')
	{
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nMissing a directive\n",line->file_name,line->line_number);
	}
	else
	{
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\n%s is not a valid directive\n",line->file_name,line->line_number,string);
	}
	free(string);
	return NONE_DIRECTIVE;
}

/*executes the directive order found in get_directive*/
int execute_directive(line_info *line,int *DC,linked_list *data_image,table **symbol_table,directive d)
{
	char *string;
	skip_blank(line);
	switch (d)
	{
		case DATA_DIRECTIVE:
			return execute_data_directive(line,DC,data_image);
		case STRING_DIRECTIVE:
			return execute_string_directive(line,DC,data_image);
		case ENTRY_DIRECTIVE:
			string=get_string(line);
			if(string[0]!='\0')
			{
				if(!valid_label_name(string,strlen(string)))
				{
					fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\n%s is not a valid label\n",line->file_name,line->line_number,string);
					free(string);
					return FALSE;
				}
				else
				{
					free(string);
					if(check_EOF(line))
					{
						return TRUE;/*line was terminated legally*/
					}
					fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nLine contains invalid input at the end: %s\n",line->file_name,line->line_number,(line->content)+line->index);
					return FALSE;
				}
			}
			fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nMissing an argument after entry directive\n",line->file_name,line->line_number);
			free(string);
			return FALSE;
		case EXTERN_DIRECTIVE:
			string=get_string(line);
			if(string[0]!='\0')
			{
				if(!valid_label_name(string,strlen(string)))
				{
					fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\n%s is not a valid label\n",line->file_name,line->line_number,string);
					free(string);
					return FALSE;
				}
				else
				{
					if(check_EOF(line))
					{
						if(!add_to_table(symbol_table,string,0,EXTERN_SYMBOL))
						{
							fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\n%s is already defined in the file and can not be redefined as external\n",line->file_name,line->line_number,string);
							free(string);
							return FALSE;
						}
						free(string);
						return TRUE;/*line was terminated legally*/
					}
					fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nLine contains invalid input at the end: %s\n",line->file_name,line->line_number,(line->content)+line->index);
					free(string);
					return FALSE;
				}
			}
			fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nMissing a label as an argument after extern directive\n",line->file_name,line->line_number);
			free(string);
			return FALSE;
		case NONE_DIRECTIVE:
			return FALSE;
	}
	return FALSE;
}

/*specific execution for data directives*/
static int execute_data_directive(line_info *line,int *DC,linked_list *data_image)
{
	char *s;
	machine_word w;
	s=get_string(line);
	if(string_to_int(line,s,&w))
	{
		/*a valid integer was found as argument*/
		add_to_list(data_image,w);
		(*DC)++;
		free(s);
		skip_blank(line);
		while(line->content[line->index]==',')
		{
			line->index++;
			if(check_EOF(line))
			{
				fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nExpected an argument after a comma\n",line->file_name,line->line_number);
				return FALSE;
			}
			s=get_string(line);
			if(!string_to_int(line,s,&w))
			{
				/*argument is not an integer*/
				free(s);
				return FALSE;
			}
			add_to_list(data_image,w);
			(*DC)++;
			free(s);
			skip_blank(line);
		}
		if(check_EOF(line))
		{
			/*end of a legal line was reached*/
			return TRUE;
		}
		else
		{
			fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nLine contains invalid input at the end: %s\n",line->file_name,line->line_number,(line->content)+line->index);
			return FALSE;
		}
	}
	/*no legal arguments were found*/
	free(s);
	return FALSE;
}

/*specific execution for string directives*/
static int execute_string_directive(line_info *line,int *DC,linked_list *data_image)
{
	int i;
	int j=0;
	machine_word w;
	w.data.ARE=1;
	if(line->content[line->index]=='"')
	{
		line->index++;
		i=line->index; /*saves current position in line, after opening quotation marks*/
		/*checking if argument is a valid string*/
		while(line->content[line->index]!='\0')
		{
			if(line->content[line->index]=='"')
			{
				/*potential legal end of string recognized*/
				j=line->index;
			}
			line->index++;
		}
		
		if(j==0)
		{
			/*no closing quotation marks*/
			fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nArgument:%s is not a valid string, missing closing quotation marks\n",line->file_name,line->line_number,(line->content)+i-1);
			return FALSE;
		}
		line->index=j+1;
			
		if(!check_EOF(line))
		{
			/*additional input after string*/
			fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nLine contains invalid input at the end: %s \n",line->file_name,line->line_number,(line->content)+line->index);
			return FALSE;
		}
		else
		{
			while(i<j)
			{
				if(!isprint((int)line->content[i]))
				{
					/*character within string is not printable, string is not a legal string*/
					fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nArgument is not a valid string, contains a non printable character:%c\n",line->file_name,line->line_number,line->content[i]);
					return FALSE;
				}
				w.data.content=(int)line->content[i];
				add_to_list(data_image,w);
				(*DC)++;
				i++;
			}
			w.data.content=(int)'\0';
			add_to_list(data_image,w);
			(*DC)++;
			return TRUE; /*every character in the string was saved to the list*/
		}
	}
	else /*argument does not contain the correct syntax to start a string*/
	{
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nArgument:%s is not a valid string\n",line->file_name,line->line_number,(line->content)+line->index);
		return FALSE;
	}
}
/*valid entry: a function for the second pass, sets the type of a symbol in the symbol table to entry, if exists on the table and is not set as extern already*/
int valid_entry(line_info *line,table **symbol_table)
{
	int i;
	char *symbol=get_string(line);
	i=update_table_type(symbol_table,symbol,ENTRY_DIRECTIVE);
	if(i==ENTRY_SYMBOL)
	{
		free(symbol);
		return TRUE;
	}
	else if(i==EXTERN_SYMBOL)
	{
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\n%s is defined as both an entry and an extern label\n",line->file_name,line->line_number,symbol);
		free(symbol);
		return FALSE;
	}
	else
	{
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nSymbol:%s appears only as an argument without being defined as a label in the file\n",line->file_name,line->line_number,symbol);
		free(symbol);
		return FALSE;
	}
}