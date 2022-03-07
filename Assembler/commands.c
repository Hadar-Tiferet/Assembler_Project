#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "global.h"
#include "enums.h"
#include "table_instructions.h"
#include "global_def.h"
#include "data_structures.h"
#include "dataworks.h"
#include "commands.h"
/*static function protoype*/

/*execute_instruction:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
IC - pointer to an integer containing the current instruction count.
code_image - pointer to a linked_list type data structure containing code lines information.
command_name - string containing a suspected instruction word.
type - integer corresponding with the type of group type of instruction present.
return:
TRUE if a valid command line was processed, FALSE if an error was encountered.
purpose:
further process a command line by recognizing the type of instruction preset and sending the info the an appropriate function.*/
static int execute_instruction(line_info *line,int *IC,linked_list *code_image,char *command_name,int type);

/*first_type_instruction:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
IC - pointer to an integer containing the current instruction count.
code_image - pointer to a linked_list type data structure containing code lines information.
command_name - string containing a first type instruction word.
return:
TRUE if a valid first type instruction line was processed and fitting data was saved, FALSE if an error was encountered after printing a relevant message.
purpose:
process, check for errors and save data for a first type instruction line.*/
static int first_type_instruction(line_info *line,int *IC,linked_list *code_image,char *command_name);

/*second_type_instruction:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
IC - pointer to an integer containing the current instruction count.
code_image - pointer to a linked_list type data structure containing code lines information.
command_name - string containing a second type instruction word.
return:
TRUE if a valid second type instruction line was processed and fitting data was saved, FALSE if an error was encountered after printing a relevant message.
purpose:
process, check for errors and save data for a second type instruction line.*/
static int second_type_instruction(line_info *line,int *IC,linked_list *code_image,char *command_name);

/*third_type_instruction:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
IC - pointer to an integer containing the current instruction count.
code_image - pointer to a linked_list type data structure containing code lines information.
command_name - string containing a third type instruction word.
return:
TRUE if a valid third type instruction line was processed and fitting data was saved, FALSE if an error was encountered after printing a relevant message.
purpose:
process, check for errors and save data for a third type instruction line.*/
static int third_type_instruction(line_info *line,int *IC,linked_list *code_image,char *command_name);

/*get_register:
input:
string - string containing an argument suspected as a register.
return:
the number of register mentioned in the string, NON_REG if no valid register was found, as defined in enums.h.
purpose:
return the number of the register mentioned in a given string.*/
static reg get_register(char *string);

/*valid_command:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
command - pointer to a machine_word type argument sent to the function to contain information of the instruction, if the line is valid.
index - integer corresponding to the command name within the instruction table written in table_instructions.h.
destination - integer holding the corresponding number of destination addressing mode in the line.
source - integer holding the corresponding number of source addressing mode in the line.
return:
TRUE if line information is valid for the present command and information of instruction word was updated successfully, FALSE if an error was encountered after printing a relevant message.
purpose:
validate and update first word information for an instruction line.*/
static int valid_command(line_info *line,machine_word *command,int index,int destination,int source);

/*get_instruction_index:
input:
command_name - string containing a suspected instruction word.
return:
an integer corresponding with the correct line withing the instruction table located in table_instructions.h.
purpose:
identify the instruction present in the current line.*/
static int get_instruction_index(char *command_name);

/*get_instruction_type:
input:
command_name - string containing a suspected instruction word.
return:
integer corresponding with the type of group type of instruction present.
purpose:
identify the instruction type present in the current line.*/
static int get_instruction_type(char *command_name);

/*check_instruction_destination_addressing:
input:
index - integer corresponding to the command name within the instruction table written in table_instructions.h.
destination_mode - integer containing the addressing mode used for a destination argument.
return:
TRUE if destination_mode is a valid destination addressing mode for the current instruction, FALSE if invalid.
purpose:
verify the use of destination addressing mode for a given instruction.*/
static int check_instruction_destination_addressing(int index,int destination_mode);

/*check_instruction_source_addressing:
input:
index - integer corresponding to the command name within the instruction table written in table_instructions.h.
source_mode - integer containing the addressing mode used for a source argument.
return:
TRUE if source_mode is a valid source addressing mode for the current instruction, FALSE if invalid.
purpose:
verify the use of source addressing mode for a given instruction.*/
static int check_instruction_source_addressing(int index,int source_mode);

/*get_addressing_mode:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
string - string containing a suspected addressing argument.
word - pointer to a machine_word type argument sent to the function to contain information of the addressing argument, if valid.
return:
addressing_mode type enum corresponding to the addressing mode used in string, as defined in enums.h.
purpose:
update word to contain the addressing argument if valid and return the type of addressing mode used in string.*/
static int get_addressing_mode(line_info *line,char *string,machine_word *word);

/*update_addressing:
input:
line - pointer to a line_info type argument containing the information relevant for processing the current line.
IC - pointer to an integer containing the current instruction count.
IC_FINAL - integer containing the final instruction count.
code_image - pointer to a linked_list type data structure containing code lines information.
symbol_table - pointer to a pointer of a table type data structure containing label information.
extern_table - pointer to a pointer of an ex_table type data structure containing information for labels defined as external.
argument - string containing an addressing argument.
return:
TRUE if the addressing mode used is valid, FALSE if encountered an error.
purpose:
validate the addressing mode used in an argument, update the correct data structures when encountering relative or direct addressing modes.*/
static int update_addressing(line_info *line,int *IC,int IC_FINAL,linked_list *code_image,table **symbol_table,ex_table **extern_table,char *argument);

/*end of static function prototype*/


int get_commands(line_info *line,int *IC,linked_list *code_image)
{
	char *command_name;
	command_name=get_string(line);
	/*first phase - recognising the command*/
	if(execute_instruction(line,IC,code_image,command_name,get_instruction_type(command_name)))
	{
		free(command_name);
		return TRUE;
	}
	else
	{
		free(command_name);
		return FALSE;
	}
}

static int execute_instruction(line_info *line,int *IC,linked_list *code_image,char *command_name,int type)
{
	switch (type)
	{
		case FIRST_TYPE:
			if(check_EOF(line))
			{
				fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nMissing arguments containing source and destination addressing for command:%s\n",line->file_name,line->line_number,command_name);
				return FALSE;
			}
			return first_type_instruction(line,IC,code_image,command_name);
		case SECOND_TYPE:
			if(check_EOF(line))
			{
				fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nMissing an argument containing destination addressing for command:%s\n",line->file_name,line->line_number,command_name);
				return FALSE;
			}
			return second_type_instruction(line,IC,code_image,command_name);
		case THIRD_TYPE:
			return third_type_instruction(line,IC,code_image,command_name);
		case NONE_TYPE:
			fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\n%s is not a valid command\n",line->file_name,line->line_number,command_name);
			return FALSE;
	}
	return FALSE;
}
	
static int first_type_instruction(line_info *line,int *IC,linked_list *code_image,char *command_name)
{
	int destination_mode,source_mode;
	machine_word command,destination,source;
	source_mode = get_addressing_mode(line,get_string(line),&source);
	if(source_mode==NONE_ADDRESS)
	{
		/*non valid argument was found*/
		return FALSE;
	}
	if(check_EOF(line))
	{
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nMissing a second argument containing destination addressing for command:%s\n",line->file_name,line->line_number,command_name);
		return FALSE;
	}
	if(line->content[line->index]!=',')
	{
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nMissing a comma before second argument containing destination addressing for command:%s\n",line->file_name,line->line_number,command_name);
		return FALSE;
	}
	line->index++; /*skip over the comma*/
	if(check_EOF(line))
	{
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nMissing a second argument containing destination addressing for command:%s\n",line->file_name,line->line_number,command_name);
		return FALSE;
	}
	destination_mode = get_addressing_mode(line,get_string(line),&destination);
	if(destination_mode==NONE_ADDRESS)
	{
		/*non valid argument was found*/
		return FALSE;
	}
	if(!check_EOF(line))
	{
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nLine contains invalid input at the end: %s\n",line->file_name,line->line_number,(line->content)+line->index);
		return FALSE;
	}
	if(valid_command(line,&command,get_instruction_index(command_name),destination_mode,source_mode))
	{
		add_to_list(code_image,command);
		(*IC)++;
		add_to_list(code_image,source);
		(*IC)++;
		add_to_list(code_image,destination);
		(*IC)++;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


static int second_type_instruction(line_info *line,int *IC,linked_list *code_image,char *command_name)
{
	int destination_mode;
	machine_word command,destination;
	destination_mode = get_addressing_mode(line,get_string(line),&destination);
	if(destination_mode==NONE_ADDRESS)
	{
		/*non valid argument was found*/
		return FALSE;
	}
	if(!check_EOF(line))
	{
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nLine contains invalid input at the end: %s\n",line->file_name,line->line_number,(line->content)+line->index);
		return FALSE;
	}
	if(valid_command(line,&command,get_instruction_index(command_name),destination_mode,NONE_ADDRESS))
	{
		add_to_list(code_image,command);
		(*IC)++;
		add_to_list(code_image,destination);
		(*IC)++;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

static int third_type_instruction(line_info *line,int *IC,linked_list *code_image,char *command_name)
{
	machine_word command;
	if(!check_EOF(line))
	{
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nLine contains invalid input at the end: %s\n",line->file_name,line->line_number,(line->content)+line->index);
		return FALSE;
	}
	if(valid_command(line,&command,get_instruction_index(command_name),NONE_ADDRESS,NONE_ADDRESS))
	{
		add_to_list(code_image,command);
		(*IC)++;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


static reg get_register(char *string)
{
	if(string[0] == 'r' && isdigit(string[1]) && string[2]== '\0')
	{
		int digit = string[1] - '0';/*converting to an int*/
		if(digit >= R0 && digit < NONE_REG)
		{
			return digit;
		}
	}
	return NONE_REG; /*not a register*/
}

static int valid_command(line_info *line,machine_word *command,int index,int destination,int source)
{
	if(!check_instruction_destination_addressing(index,destination))
	{
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nArgument uses an invalid destination addressing type for command:%s\n",line->file_name,line->line_number,instruction_table[index].name);
		return FALSE;
	}
	if(!check_instruction_source_addressing(index,source))
	{
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nArgument uses an invalid source addressing type for command:%s\n",line->file_name,line->line_number,instruction_table[index].name);
		return FALSE;
	}
	command->code.ARE=1;
	if(destination==NONE_ADDRESS)
	{
		command->code.destination_addressing=0;
	}
	else
	{
		command->code.destination_addressing=destination;
	}
	if(source==NONE_ADDRESS)
	{
		command->code.source_addressing=0;
	}
	else
	{
		command->code.source_addressing=source;
	}
	command->code.funct=instruction_table[index].funct;
	command->code.opcode=instruction_table[index].opcode;
	return TRUE;
}

/*returns the index of the command within the instruction_table*/
static int get_instruction_index(char *command_name)
{
	int i;
	for(i=0;instruction_table[i].name!=NULL;i++)
	{
		if(strcmp(command_name,instruction_table[i].name)==0)
		{
			return i;
		}
	}
	return i;
}



/*returns the group of commands command_name belongs to*/
static int get_instruction_type(char *command_name)
{
	int i;
	for(i=0;instruction_table[i].name!=NULL;i++)
	{
		if(strcmp(command_name,instruction_table[i].name)==0)
		{
			return instruction_table[i].type;
		}
	}
	return instruction_table[i].type;
}

/*returns TRUE if the destination addressing mode given is legal for the specific instruction, FALSE otherwise*/
static int check_instruction_destination_addressing(int index,int destination_mode)
{
	int i;
	for(i=0;instruction_table[index].destination_addressing[i]!=NONE_ADDRESS;i++)
	{
		if(destination_mode==instruction_table[index].destination_addressing[i])
		{
			return TRUE;
		}
	}
	return (destination_mode==NONE_ADDRESS);
}

/*returns TRUE if the source addressing mode given is legal for the specific instruction, FALSE otherwise*/
static int check_instruction_source_addressing(int index,int source_mode)
{
	int i;
	for(i=0;instruction_table[index].source_addressing[i]!=NONE_ADDRESS;i++)
	{
		if(source_mode==instruction_table[index].source_addressing[i])
		{
			return TRUE;
		}
	}
		return (source_mode==NONE_ADDRESS);
}


static int get_addressing_mode(line_info *line,char *string,machine_word *word)
{
	int i;
	if(string[0]=='#')
	{
		/*suspecting immediate addressing*/
		if(string_to_int(line,string+1,word))
		{
			free(string);
			return IMMEDIATE_ADDRESS;
		}
		else
		{
			/*an error was found*/
			free(string);
			return NONE_ADDRESS;
		}
	}
	else if(string[0]=='%')
	{
		/*suspecting relative addressing*/
		if(valid_label_name(string+1,strlen((string+1))))
		{
			word->data.ARE=1;
			word->data.content=0;/*temporary placement for a label address*/
			free(string);
			return RELATIVE_ADDRESS;
		}
		else
		{
			/*error - not a valid string name*/
			if(string[1]=='\0')
			{
				fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nArgument does not contain a valid label\n",line->file_name,line->line_number);
			}
			else
			{
				fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\n%s is not a valid label\n",line->file_name,line->line_number,string+1);
			}
			free(string);
			return NONE_ADDRESS;
		}
	}
	else if((i=get_register(string))!=NONE_REG)
	{
		/*register direct addressing*/
		word->data.ARE=1;
		word->data.content=(1<<i);/*sets the correct register representation*/
		free(string);
		return REGISTER_ADDRESS;
	}
	else
	{
		/*suspecting direct addressing*/
		if(valid_label_name(string,strlen(string)))
		{
			word->data.ARE=(1<<1);
			word->data.content=0;/*temporary placement for a label address*/
			free(string);
			return DIRECT_ADDRESS;
		}
		else
		{
			/*didnt recognize a supported addressing mode*/
			fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nArgument:%s uses an unsupported addressing mode\n",line->file_name,line->line_number,string);
			free(string);
			return NONE_ADDRESS;
		}
	}
}

int commands_second_pass(line_info *line,int *IC,int IC_FINAL,linked_list *code_image,table **symbol_table,ex_table **extern_table)
{
	char *s=get_string(line);
	free(s);
	list_current_to_next(code_image);/*move the current pointer of the list to the next item*/
	(*IC)++;
	if(check_EOF(line))
	{
		return TRUE;/*this is a third type instruction, contains no arguments*/
	}
	if(!update_addressing(line,IC,IC_FINAL,code_image,symbol_table,extern_table,get_string(line)))
	{
		return FALSE;/*encountered an error*/
	}
	if(check_EOF(line))
	{
		return TRUE;/*this is a second type instruction, contains one argument*/
	}
	line->index++;/*skip over the comma*/
	skip_blank(line);
	if(!update_addressing(line,IC,IC_FINAL,code_image,symbol_table,extern_table,get_string(line)))
	{
		return FALSE;/*encountered an error*/
	}
	else
	{
		return TRUE;/*this is a first type instruction, contains two arguments*/
	}
}

static int update_addressing(line_info *line,int *IC,int IC_FINAL,linked_list *code_image,table **symbol_table,ex_table **extern_table,char *argument)
{
	machine_word new;
	int i;
	if(argument[0]=='#')/*immediate addressing, does not require an update*/ 
	{
		list_current_to_next(code_image);
		(*IC)++;
		free(argument);
		return TRUE;
	}
	else if(argument[0]=='%')/*relative addressing, requires an update*/
	{
		if(get_table_address(symbol_table,argument+1,&i))
		{
			/*a matching symbol was found, check if contains a valid code symbol*/
			if(i<IC_FINAL)
			{
				/*the symbol is either external or local code type symbol (not a data symbol)*/
				if(i==0)
				{
					fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nSymbol:%s can not be used as a relative addressing argument while defined as extern\n",line->file_name,line->line_number,argument+1);
					list_current_to_next(code_image);
					(*IC)++;
					free(argument);
					return FALSE;
				}
				new.data.ARE=1;
				if((*IC)>i) /*(destination-current) but in negative*/
				{
					new.data.content=get_twos_complement((*IC)-i);
				}
				else
				{
					new.data.content= i-(*IC);
				}
				list_update_current(code_image,new);
				list_current_to_next(code_image);
				(*IC)++;
				free(argument);
				return TRUE;
			}
			else
			{
				/*this is a data symbol, not valid for relative addressing*/
				fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nSymbol:%s can not be used as a relative addressing argument while defined as data\n",line->file_name,line->line_number,argument+1);
				list_current_to_next(code_image);
				(*IC)++;
				free(argument);
				return FALSE;
			}
		}
		else
		{
			/*the symbol is not set in file*/
			fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nSymbol:%s can not be used as an argument without being defined\n",line->file_name,line->line_number,argument+1);
			list_current_to_next(code_image);
			(*IC)++;
			free(argument);
			return FALSE;
		}
	}
	else if(get_register(argument)!=NONE_REG)/*register addressing, does not require an update*/
	{
		list_current_to_next(code_image);
		(*IC)++;
		free(argument);
		return TRUE;
	}
	else/*direct addressing, requires an update*/
	{
		if(get_table_address(symbol_table,argument,&i))
		{
			/*a matching symbol was found*/
			if(i)
			{
				/*symbol is not extern*/
				new.data.ARE=(1<<1);
			}
			else
			{
				/*symbol is extern*/
				new.data.ARE=(1<<2);
				add_to_ex_table(extern_table,argument,*IC);
			}
			new.data.content=i;
			list_update_current(code_image,new);
			list_current_to_next(code_image);
			(*IC)++;
			free(argument);
			return TRUE;
		}
		else
		{
			/*the symbol is not set in file*/
			fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nSymbol:%s can not be used as an argument without being defined\n",line->file_name,line->line_number,argument);
			list_current_to_next(code_image);
			(*IC)++;
			free(argument);
			return FALSE;
		}
	}
}