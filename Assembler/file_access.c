#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "enums.h"
#include "global_def.h"
#include "type_recognition.h"
#include "data_structures.h"
#include "file_access.h"
/*static function prototype*/

/*create_object_file:
input:
file - string containing a file name with the required extention.
IC - integer containing the instruction count.
DC - integer containing the directive count.
code_image - pointer to a linked_list type data structure containing code lines information.
data_image - pointer to a linked_list type data structure containing data lines information.
purpose:
create the object output file for the currently reviewed file, from the content of code_image followed by the content of data_image.*/
static void create_object_file(char *file,int IC,int DC,linked_list *code_image,linked_list *data_image);

/*create_files:
input:
file - string containing a file name with the required extention.
entry_table - pointer to a pointer of a table type data structure containing entry type label information.
purpose:
create the entry output file for the currently reviewed file, if at least one entry type symbol was found in the file.*/
static void create_entry_file(char *file,table **entry_table);

/*create_files:
input:
file - string containing a file name with the required extention.
extern_table - pointer to a pointer of an ex_table type data structure containing extern type label information.
purpose:
create the extern output file for the currently reviewed file, by listing each extern label alongside the address they were called by, if at least one extern type symbol was found in the file.*/
static void create_extern_file(char *file,ex_table **extern_table);

/*end of static function prototype*/


/*returns the requested file name with the given extention*/
char *add_file_extention(char *string,char *extention)
{
	int i=strlen(string);
	int j;
	char *name;
	if(i>MAX_FILE_NAME_LENGTH)
	{
		return NULL;
	}
	name=(char *)malloc_or_exit(sizeof(char)*(i+5));
	for(i=0;string[i]!='\0';i++)
	{
		name[i]=string[i];
	}
	for(j=0;extention[j]!='\0';j++,i++)
	{
		name[i]=extention[j];
	}
	name[i]='\0';
	return name;
}

/*copies the next line in file, returns the next character within the file*/
char get_line(FILE *in,line_info *line)
{
	char c;
	int i=0;
	
	c=fgetc(in);
	while (c!= '\n' && c!= EOF && i<MAX_LINE_LENGTH)
	{
		line->content[i]= c;
		c=fgetc(in);
		i++;
	}
	if(line->content[i-1]=='\r' && c== '\n')
	{
		/*for CRLF new line character code*/
		i--;
	}
	line->content[i]= '\0';
	return c;
}

/*file creation*/

void create_files(char *name,int IC,int DC,linked_list *code_image,linked_list *data_image,table **symbol_table,ex_table **extern_table)
{
	table *entry_table=*symbol_table;
	point_to_next_table_sort(&entry_table,ENTRY_SYMBOL);
	create_object_file(add_file_extention(name,".ob"),IC,DC,code_image,data_image);
	if(entry_table!=NULL)
	{
		create_entry_file(add_file_extention(name,".ent"),&entry_table);
	}
	if((*extern_table)!=NULL)
	{
		create_extern_file(add_file_extention(name,".ext"),extern_table);
	}
}


static void create_object_file(char *file,int IC,int DC,linked_list *code_image,linked_list *data_image)
{
	FILE *p;
	int i=IC_INITIAL;
	p=fopen(file,"w");
	fprintf(p,"\t%d %d\n",IC,DC);
	list_current_to_head(code_image);/*resets the position of current item to the head*/
	list_current_to_head(data_image);/*resets the position of current item to the head*/
	while(code_image->current!=NULL)
	{
		fprintf(p,"%04d %03X %c\n",i,list_return_word(code_image),list_return_ARE(code_image));
		list_current_to_next(code_image);
		i++;
	}
	while(data_image->current!=NULL)
	{
		fprintf(p,"%04d %03X %c\n",i,list_return_word(data_image),list_return_ARE(data_image));
		list_current_to_next(data_image);
		i++;
	}
	fclose(p);
	free(file);
}


static void create_entry_file(char *file,table **entry_table)
{
	FILE *p;
	p=fopen(file,"w");
	do
	{
		fprintf(p,"%s %04d\n",(*entry_table)->name,(*entry_table)->address);
		point_to_next_table(entry_table);
		point_to_next_table_sort(entry_table,ENTRY_SYMBOL);
	}while(*entry_table!=NULL);
	fclose(p);
	free(file);
}

static void create_extern_file(char *file,ex_table **extern_table)
{
	FILE *p;
	ex_table *temp=*extern_table;
	p=fopen(file,"w");
	do
	{
		fprintf(p,"%s %04d\n",temp->name,temp->address);
		point_to_next_ex_table(&temp);
	}while(temp!=NULL);
	fclose(p);
	free(file);
}