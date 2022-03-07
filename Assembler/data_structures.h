/*Header file for data_structures.c*/
/*function prototype*/

/*adding a new item to the structure*/
/*for a linked list*/
/*add_to_list:
input:
list - pointer to a linked_list type data structure.
content - pointer to a machine_word type argument containing the information to be added to the list.
purpose:
add content to the end of list, while keeping the list functional.*/
void add_to_list(linked_list *list,machine_word content);


/*for a table*/
/*add_to_table:
input:
head - pointer to a pointer of a table type data structure.
string - string containing a symbol name.
number - integer containing an address.
type - number corresponding to a symbol_type, as defined in enums.h.
return:
TRUE if the information was added successfully to the last node in the table, FALSE if new node could not be created or conflicting node already exists.
purpose:
adds a new symbol to the table, in addition to the relevant address and the symbol type, if symbol is valid and no conflicting node exists in the table.*/
int add_to_table(table **head, char *string, int number, symbol_type type);


/*for an ex table*/
/*add_to_ex_table:
input:
head - pointer to a pointer of an ex_table type data structure.
string - string containing a symbol name.
number - integer containing an address.
purpose:
adds a new extern symbol to the table, in addition to the relevant address.*/
void add_to_ex_table(ex_table **head, char *string, int number);
/*end of item addition to structures*/

/*data structure deletion*/
/*for a linked list*/
/*free_list:
input:
list - pointer to a linked_list type data structure.
purpose:
free all the dynamically allocated memory for the list.*/
void free_list(linked_list *list);

/*for a table*/
/*free_table:
input:
head - pointer to a pointer of a table type data structure.
purpose:
free all the dynamically allocated memory for the table.*/
void free_table(table **head);

/*for an ex table*/
/*add_to_list:
input:
head - pointer to a pointer of an ex_table type data structure.
purpose:
free all the dynamically allocated memory for the ex_table.*/
void free_ex_table(ex_table **head);
/*end of data structure deletion*/

/*data management*/
/*linked list*/
/*list_update_current:
input:
list - pointer to a linked_list type data structure.
content - pointer to a machine_word type argument containing the information to be updated in the list.
purpose:
update the content of the item currently pointed to by the linked_list list.*/
void list_update_current(linked_list *list,machine_word content);

/*for file printing*/
/*list_return_word:
input:
list - pointer to a linked_list type data structure.
purpose:
return the content of the item currently pointed to by the linked_list list.*/
unsigned int list_return_word(linked_list *list);

/*list_return_ARE:
input:
list - pointer to a linked_list type data structure.
purpose:
return the ARE indication of the item currently pointed to by the linked_list list.*/
char list_return_ARE(linked_list *list);

/*table*/
/*get_table_address:
input:
head - pointer to a pointer of a table type data structure.
string - string containing a symbol name.
value - integer sent to contain the address value of string within the table.
return:
TRUE if the string was found within the table and the address was passed through value, FALSE if string was not found in the table.
purpose:
find a given string in the table and update value to hold the address field of said string.*/
int get_table_address(table **head, char *string, int *value);

/*update_table_address:
input:
head - pointer to a pointer of a table type data structure.
string - string containing a symbol name.
value - integer containing an address.
sort - number corresponding to a symbol_type, as defined in enums.h.
purpose:
update the address value of all the items within the table containing the symbol type mentioned in sort, increasing them  by the given value*/
void update_table_address(table **head, int value, symbol_type sort);

/*update_table_type:
input:
head - pointer to a pointer of a table type data structure.
string - string containing a symbol name.
sort - number corresponding to a symbol_type, as defined in enums.h.
return:
sort if the type of the item within the table containing string was updated correctly, EXTERN_SYMBOL if item was set to external in the file, FALSE if item was not found.
purpose:
look for the given string within the table and update its type to be sort if the operation is valid.*/
int update_table_type(table **head, char *string, symbol_type sort);
/*end of data management*/

/*structure pointer positioning*/
/*linked list*/
/*list_current_to_next:
input:
list - pointer to a linked_list type data structure.
purpose:
move the current pointer to the next item on the list, as long as such item exists.*/
void list_current_to_next(linked_list *list);

/*list_current_to_head:
input:
list - pointer to a linked_list type data structure.
purpose:
move the current pointer to the first item on the list.*/
void list_current_to_head(linked_list *list);

/*table*/
/*point_to_next_table_sort:
input:
head - pointer to a pointer of a table type data structure.
sort - number corresponding to a symbol_type, as defined in enums.h.
purpose:
update the table to point to the next item in line containing sort as its symbol type*/
void point_to_next_table_sort(table **head,symbol_type sort);

/*point_to_next_table:
input:
head - pointer to a pointer of a table type data structure.
purpose:
update the table to point to the next item in line, as long as the head is not empty*/
void point_to_next_table(table **head);

/*ex table*/
/*point_to_next_ex_table:
input:
head - pointer to a pointer of an ex_table type data structure.
purpose:
update the ex_table to point to the next item in line, as long as the head is not empty*/
void point_to_next_ex_table(ex_table **head);

/*end of pinter positioning*/