#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "enums.h"
#include "global_def.h"
#include "data_structures.h"
#include "dataworks.h"
#include "directives.h"
#include "commands.h"
#include "line_first_pass.h"


int first_pass_read_line(line_info *line,int *IC,int *DC,linked_list *code_image,linked_list *data_image,table **symbol_table)
{
	int i;
	directive d;
	char *symbol;
	line->index=0;
	
	skip_blank(line);
	if(line->content[line->index]=='\0' || line->content[line->index]==';')
	{
		return TRUE; /*recognized legal empty line*/
	}
	/*look for label*/
	symbol=get_label_suspect(line);/*returns a string if label suspect exists or NULL otherwise*/
	/*look for first word of the line, regardless of label existance*/
	i=line->index;
	skip_blank(line);
	if(line->content[line->index]=='\0')
	{
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nMissing a command\n",line->file_name,line->line_number);
		if(symbol!=NULL)
		{
			free(symbol);
		}
		return FALSE;/*line doesn't contain a first word*/
	}
	if(i==line->index && symbol!=NULL)
	{
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nMissing a blank character after label:%s\n",line->file_name,line->line_number,symbol);
		free(symbol);
		return FALSE; /*no space was found between label and first word of line*/
	}
	/*search for directive input*/
	if(line->content[line->index]=='.')
	{
		/*attempting to locate the correct directive*/
		line->index++;
		d=get_directive(line);
		if(symbol!=NULL)
		{
			if(d==DATA_DIRECTIVE || d==STRING_DIRECTIVE)
			{
				if(!valid_label_name(symbol,strlen(symbol)))
				{
					fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\n%s is not a valid label\n",line->file_name,line->line_number,symbol);
					free(symbol);
					return FALSE;
				}
				if(!add_to_table(symbol_table,symbol,*DC,DATA_SYMBOL))
				{
					fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\n%s is already defined as a label\n",line->file_name,line->line_number,symbol);
					free(symbol);
					return FALSE;
				}
			}
			free(symbol);
		}
		return execute_directive(line,DC,data_image,symbol_table,d);
	}
	else/*consider the line as a command line*/
	{
		if(symbol!=NULL)
		{
			if(!valid_label_name(symbol,strlen(symbol)))
			{
				fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\n%s is not a valid label\n",line->file_name,line->line_number,symbol);
				free(symbol);
				return FALSE;
			}
			if(!add_to_table(symbol_table,symbol,*IC,CODE_SYMBOL))
			{
				fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\n%s is already defined as a label\n",line->file_name,line->line_number,symbol);
				free(symbol);
				return FALSE;
			}
			free(symbol);
		}
		return get_commands(line,IC,code_image);
	}
}