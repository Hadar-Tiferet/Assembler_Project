/*
Assembler program.
Made by: Hadar Tiferet, ID: 205492507
For Mmn14 (project), Course: 20465, Semester: 2021A, OpenU.
*/
/*note:
comments and explanations for functions are located above the function prototype.
for static function - at the top of the .c file and for the rest within the header file.*/
#include <stdio.h>
#include "global.h"
#include "enums.h"
#include "global_def.h"
#include "processing.h"


int main(int argc, char *argv[])
{
	int i;
	int j=0;
	if(argc==1) /*meaning the user have not passed a file name*/
	{
		fprintf(ERROR_OUTPUT_FILE,"The assembler requires at least one file name to be passed as an argument.\n");
		return FALSE;
	}
	for (i=1;i<argc;i++)
	{
		if(assemble(argv[i]))
		{
			j++;
		}
	}
	i--;
	/*run feedback*/
	fprintf(ERROR_OUTPUT_FILE,"\nAssembler operation report:\n%d files passed as argument.\n%d files successfully converted.\n%d files contain errors.\n",i,j,i-j);
	return TRUE;
}
