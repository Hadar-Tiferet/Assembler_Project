/*table_directives header file:
contains a table of the allowed directives and their unique access in the code.*/

struct directive_lookup {
	char *name;
	directive type;
};

/*each table entry contains:
name - string containing the name of the directive.
type - enum defined in enums.h containing the type of the directive.*/
static struct directive_lookup directive_table[]= {
	{"data", DATA_DIRECTIVE},
	{"string", STRING_DIRECTIVE},
	{"entry", ENTRY_DIRECTIVE},
	{"extern", EXTERN_DIRECTIVE},
	{'\0', NONE_DIRECTIVE}
};
