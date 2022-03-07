#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "enums.h"
#include "global_def.h"
#include "type_recognition.h"
#include "data_structures.h"


/*adding a new item to the structure*/
/*for a linked list*/
void add_to_list(linked_list *list,machine_word content)
{
	tnode *new;
	new=(tnode*)malloc_or_exit(sizeof(tnode));
	new->word=content;
	new->next=NULL;
	if(list->head==NULL)/*if the list is empty*/
	{
		list->head=new;
		list->current=new;
	}
	else
	{
		list->current->next=new;
		list->current=new;
	}
}

/*for a table*/
int add_to_table(table **head, char *string, int number, symbol_type type)
{
	int i;
	table *new;
	table *previous;
	table *temp= *head;
	if(*head==NULL)
	{
		new=(table*)malloc_or_exit(sizeof(table));
		new->name=(char *)malloc_or_exit(sizeof(char)*(strlen(string)+1));
		new->address=number;
		new->type=type;
		for(i=0;string[i]!='\0';i++)
		{
			new->name[i]=string[i];
		}
		new->name[i]='\0';
		new->next=NULL;
		*head=new;
		return TRUE;
	}
	
	while(temp!=NULL) /*get to the last entry + check if string already exists*/
	{
		if(strcmp(temp->name,string)==0)
		{
			if(temp->type==EXTERN_SYMBOL && type==EXTERN_SYMBOL)
			{
				return TRUE;/*this is a redefining of an extern label, which is allowed*/
			}
			return FALSE;/*error: string already exists in the table*/
		}
		previous=temp;
		temp=temp->next;
	}
	/*temp is now pointing at NULL, previous pointing at the last item in the table*/
	new=(table*)malloc_or_exit(sizeof(table));
	new->name=(char *)malloc_or_exit(sizeof(char)*(strlen(string)+1));
	new->address=number;
	new->type=type;
	for(i=0;string[i]!='\0';i++)
	{
		new->name[i]=string[i];
	}
	new->name[i]='\0';
	new->next=NULL;
	previous->next=new;
	return TRUE;
}

/*for an ex table*/
/*add new item to the extern table*/
void add_to_ex_table(ex_table **head, char *string, int number)
{
	int i;
	ex_table *new=(ex_table*)malloc_or_exit(sizeof(ex_table));
	ex_table *temp= *head;
	new->name=(char *)malloc_or_exit(sizeof(char)*(strlen(string)+1));
	new->address=number;
	for(i=0;string[i]!='\0';i++)
	{
		new->name[i]=string[i];
	}
	new->name[i]='\0';
	new->next=NULL;
	if(*head==NULL)
	{
		*head=new;
		return;
	}
	
	while(temp->next!=NULL) /*get to the last entry*/
	{
		temp=temp->next;
	}
	temp->next=new;
}
/*end of item addition to structures*/

/*data structure deletion*/
/*for a linked list*/
void free_list(linked_list *list)
{
	while(list->head!=NULL)
	{
		list->current=list->head->next;
		free(list->head);
		list->head=list->current;
	}
}

/*for a table*/
void free_table(table **head)
{
	table *current=*head;
	table *temp;
	while(current!=NULL)
	{
		temp=current->next;
		free(current->name);
		free(current);
		current=temp;
	}
	*head=NULL;
}

/*for an ex table*/
void free_ex_table(ex_table **head)
{
	ex_table *current=*head;
	ex_table *temp;
	while(current!=NULL)
	{
		temp=current->next;
		free(current->name);
		free(current);
		current=temp;
	}
	*head=NULL;
}
/*end of data structure deletion*/

/*data management*/
/*linked list*/
void list_update_current(linked_list *list,machine_word content)
{
	list->current->word=content;
}

/*for file printing*/
unsigned int list_return_word(linked_list *list)
{
	return list->current->word.data.content;
}

/*for file printing*/
char list_return_ARE(linked_list *list)
{
	if(list->current->word.data.ARE==1)
	{
		return 'A';
	}
	else if(list->current->word.data.ARE==(1<<1))
	{
		return 'R';
	}
	else if(list->current->word.data.ARE==(1<<2))
	{
		return 'E';
	}
	else
	{
		return 'F';/*for error checking*/
	}
}

/*table*/
int get_table_address(table **head, char *string, int *value)
{
	table *temp=*head;
	while(temp!=NULL)
	{
		if(strcmp(temp->name,string)==0)
		{
			(*value)=temp->address;
			return TRUE; /*a matching table entry was found*/
		}
		temp=temp->next;
	}
	return FALSE;/*no matching table entry*/
}

void update_table_address(table **head, int value, symbol_type sort)
{
	table *temp=*head;
	while(temp!=NULL)
	{
		if(temp->type==sort)
		{
			temp->address += value;
		}
		temp=temp->next;
	}
}

int update_table_type(table **head, char *string, symbol_type sort)
{
	table *temp=*head;
	while(temp!=NULL)
	{
		if(strcmp(temp->name,string)==0)
		{
			if(temp->type==EXTERN_SYMBOL)
			{
				return EXTERN_SYMBOL;
			}
			temp->type=sort;
			return sort;
		}
		temp=temp->next;
	}
	return FALSE;
}
/*end of data management*/

/*structure pointer positioning*/
/*linked list*/
void list_current_to_next(linked_list *list)
{
	if(list->current!=NULL)
	{
		list->current=list->current->next;
	}
}

void list_current_to_head(linked_list *list)
{
	list->current=list->head;
}

/*table*/
/*will override the given table, only useful for locating the next symbol to print into entry file*/
void point_to_next_table_sort(table **head,symbol_type sort)
{
	while((*head)!=NULL)
	{
		if((*head)->type==sort)
		{
			return;
		}
		(*head)=(*head)->next;
	}
}

/*will override the given table,useful for creating entry file, will move the pointer to the next in line*/
void point_to_next_table(table **head)
{
	if((*head)!=NULL)
	{
		(*head)=(*head)->next;
	}
}

/*ex table*/
/*will override the given ex table, only useful for locating the next symbol to print into extern file*/
void point_to_next_ex_table(ex_table **head)
{
	if((*head)!=NULL)
	{
		(*head)=(*head)->next;
	}
}
/*end of pinter positioning*/