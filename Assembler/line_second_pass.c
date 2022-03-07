#include "global.h"
#include "enums.h"
#include "global_def.h"
#include "data_structures.h"
#include "dataworks.h"
#include "directives.h"
#include "commands.h"
#include "line_second_pass.h"


int second_pass_read_line(line_info *line,int *IC,int IC_FINAL,linked_list *code_image,table **symbol_table,ex_table **extern_table)
{
	line->index=0;
	
	skip_blank(line);
	if(line->content[line->index]=='\0' || line->content[line->index]==';')
	{
		return TRUE; /*recognized legal empty line*/
	}
	/*look for label and skip over it if found*/
	skip_label(line);
	/*look for first word of the line, regardless of label existance*/
	skip_blank(line);
	/*search for directive input*/
	if(line->content[line->index]=='.')
	{
		/*attempting to locate the correct directive*/
		line->index++;
		if(get_directive(line)==ENTRY_DIRECTIVE)
		{
			skip_blank(line);
			return valid_entry(line,symbol_table);
		}
		else
		{
			/*this is a data, string or extern directive*/
			return TRUE;
		}
	}
	else/*this is a command line*/
	{
		return commands_second_pass(line,IC,IC_FINAL,code_image,symbol_table,extern_table);
	}
}