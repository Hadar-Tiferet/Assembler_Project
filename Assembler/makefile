assembler: type_recognition.o dataworks.o data_structures.o file_access.o directives.o commands.o line_second_pass.o line_first_pass.o processing.o assembler.o
	gcc -g -ansi -Wall -pedantic type_recognition.o dataworks.o data_structures.o file_access.o directives.o commands.o line_second_pass.o line_first_pass.o processing.o assembler.o -o assembler
	
type_recognition.o: type_recognition.c global.h enums.h table_instructions.h table_directives.h type_recognition.h
	gcc -c -ansi -Wall -pedantic type_recognition.c -o type_recognition.o
	
dataworks.o: dataworks.c global.h enums.h global_def.h type_recognition.h dataworks.h
	gcc -c -ansi -Wall -pedantic dataworks.c -o dataworks.o
	
data_structures.o: data_structures.c global.h enums.h global_def.h type_recognition.h data_structures.h
	gcc -c -ansi -Wall -pedantic data_structures.c -o data_structures.o
	
file_access.o: file_access.c global.h enums.h global_def.h type_recognition.h data_structures.h file_access.h
	gcc -c -ansi -Wall -pedantic file_access.c -o file_access.o
	
directives.o: directives.c global.h enums.h table_directives.h global_def.h data_structures.h dataworks.h directives.h
	gcc -c -ansi -Wall -pedantic directives.c -o directives.o
	
commands.o: commands.c global.h enums.h table_instructions.h global_def.h data_structures.h dataworks.h commands.h
	gcc -c -ansi -Wall -pedantic commands.c -o commands.o

line_second_pass.o: line_second_pass.c global.h enums.h global_def.h data_structures.h dataworks.h directives.h commands.h line_second_pass.h
	gcc -c -ansi -Wall -pedantic line_second_pass.c -o line_second_pass.o
	
line_first_pass.o: line_first_pass.c global.h enums.h global_def.h data_structures.h dataworks.h directives.h commands.h line_first_pass.h
	gcc -c -ansi -Wall -pedantic line_first_pass.c -o line_first_pass.o
	
processing.o: processing.c global.h enums.h global_def.h data_structures.h file_access.h line_first_pass.h line_second_pass.h processing.h
	gcc -c -ansi -Wall -pedantic processing.c -o processing.o
	
assembler.o: assembler.c global.h enums.h global_def.h processing.h
	gcc -c -ansi -Wall -pedantic assembler.c -o assembler.o