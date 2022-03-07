#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "enums.h"
#include "global_def.h"
#include "data_structures.h"
#include "file_access.h"
#include "line_first_pass.h"
#include "line_second_pass.h"
#include "processing.h"
/*static function prototype*/

/*first_pass:
input:
file - FILE pointer containing the character stream of the current file.
line - line_info type argument containing the information relevant for processing a line.
err - pointer to an integer counting the number of errors encountered in the file so far.
IC - pointer to an integer containing the current instruction count.
DC - pointer to an integer containing the current directive count.
code_image - pointer to a linked_list type data structure containing code lines information.
data_image - pointer to a linked_list type data structure containing data lines information.
symbol_table - pointer to a pointer of a table type data structure containing label information.
purpose:
run through the file one line at a time until EOF is encountered, update err each time a line contains an error.*/
static void first_pass(FILE *file,line_info line,int *err,int *IC,int *DC,linked_list *code_image,linked_list *data_image,table **symbol_table);

/*second_pass:
input:
file - FILE pointer containing the character stream of the current file.
line - line_info type argument containing the information relevant for processing a line.
err - pointer to an integer counting the number of errors encountered in the file so far.
IC_FINAL - integer containing the final instruction count.
code_image - pointer to a linked_list type data structure containing code lines information.
symbol_table - pointer to a pointer of a table type data structure containing label information.
extern_table - pointer to a pointer of an ex_table type data structure containing information for labels defined as external.
purpose:
run through the file one line at a time until EOF is encountered, update err each time a line contains an error.*/
static void second_pass(FILE *file,line_info line,int *err,int IC_FINAL,linked_list *code_image,table **symbol_table,ex_table **extern_table);

/*end of static function prototype*/


int assemble(char *name)
{
	FILE *as;
	line_info line;/*currently reviewed line*/
	/*set data structures*/
	linked_list code_image;
	linked_list data_image;
	table *symbol_table;
	ex_table *extern_table;
	int ic=IC_INITIAL;/*instruction count*/
	int dc=0;/*directive count*/
	int err=0;/*error count*/
	/*initialize data structures*/
	code_image.head=NULL;
	data_image.head=NULL;
	symbol_table=NULL;
	extern_table=NULL;
	line.line_number=0;/*counting the line number in the source code*/
	line.file_name=add_file_extention(name,".as");
	if(line.file_name==NULL)
	{
		/*the name given is longer than the allowed limit*/
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s Error:\nFile name can not be longer than the allowed value:%d characters.\n\n",name,MAX_FILE_NAME_LENGTH);
		return FALSE;
	}
	as=fopen(line.file_name,"r");
	if(as==NULL)
	{
		/*file was not found in current directory*/
		fprintf(ERROR_OUTPUT_FILE,"FILE:%s Error:\nFile was not found.\nNote: when passing files from another directory, please make sure to include the full path of the file\n\n",line.file_name);
		free(line.file_name);
		return FALSE;
	}
	first_pass(as,line,&err,&ic,&dc,&code_image,&data_image,&symbol_table);
	if (err)
	{
		/*encountered an error during first pass, will not continue to second pass*/
		fprintf(ERROR_OUTPUT_FILE,"\n\tFile:%s contains %d errors.\n\n",line.file_name,err);
		fclose(as);
		free_list(&code_image);
		free_list(&data_image);
		free_table(&symbol_table);
		free(line.file_name);
		return FALSE;
	}
	rewind(as);/*point back to the start of the file*/
	list_current_to_head(&code_image);/*resets the current pointer in code_image to point at the head for the second pass*/
	update_table_address(&symbol_table,ic,DATA_SYMBOL);/*update the symbols belonging to the data part of the code to their correct position*/
	second_pass(as,line,&err,ic,&code_image,&symbol_table,&extern_table);
	if (err)
	{
		/*encountered an error during second pass, will not continue to output phase*/
		fprintf(ERROR_OUTPUT_FILE,"\n\tFile:%s contains %d errors.\n\n",line.file_name,err);
		fclose(as);
		free_list(&code_image);
		free_list(&data_image);
		free_table(&symbol_table);
		free_ex_table(&extern_table);
		free(line.file_name);
		return FALSE;
	}
	fclose(as);
	/*did not encounter errors in source file, create appropriate output files*/
	ic-=IC_INITIAL;
	create_files(name,ic,dc,&code_image,&data_image,&symbol_table,&extern_table);
	/*free allocated memory*/
	free_list(&code_image);
	free_list(&data_image);
	free_table(&symbol_table);
	free_ex_table(&extern_table);
	free(line.file_name);
	return TRUE;
}

static void first_pass(FILE *file,line_info line,int *err,int *IC,int *DC,linked_list *code_image,linked_list *data_image,table **symbol_table)
{
	char lastC; /*used for various line checks, including EOF for the file*/
	do
	{
		line.line_number++;
		lastC=get_line(file,&line);
		if (lastC!='\n' && lastC!=EOF)/*line was too long*/
		{
			(*err)++;
			fprintf(ERROR_OUTPUT_FILE,"FILE:%s LINE:%d ERROR:\nLine was too long, a valid line can contain up to %d characters\n",line.file_name,line.line_number,MAX_LINE_LENGTH);
			while (lastC!='\n' && lastC!=EOF)
			{
				lastC=fgetc(file);/*move the file pointer to the start of the next line*/
			}
		}
		else
		{
			if(!first_pass_read_line(&line,IC,DC,code_image,data_image,symbol_table))
			{
				(*err)++;
			}
		}
	}while(lastC!=EOF);
}

static void second_pass(FILE *file,line_info line,int *err,int IC_FINAL,linked_list *code_image,table **symbol_table,ex_table **extern_table)
{
	/*no need to check for errors in input, since the file passed the first pass*/
	char lastC; /*used to indicate EOF status in currently reviewed line*/
	int IC=IC_INITIAL;/*internal instruction count for the second pass*/
	do
	{
		line.line_number++;
		lastC=get_line(file,&line);
		if(!second_pass_read_line(&line,&IC,IC_FINAL,code_image,symbol_table,extern_table))
		{
			(*err)++;
		}
	}while(lastC!=EOF);
}