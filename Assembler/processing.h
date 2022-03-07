/*Header file for processing.c*/
/*function prototype*/

/*assemble:
input:
name - character array containing the name of a requested file.
return:
TRUE if file was processed succesfully and output files were printed, FALSE if an error was encountered with the file.
purpose:
process a given string, attempt to open a file by the name contained by the string and the legal extention,
send the file into first pass, second pass and output files creation - each time only if previous stage finished without errors.*/
int assemble(char *name);