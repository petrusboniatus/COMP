//
// Created by someone on 10/13/17.
//

#include "ErrorLog.h"
#include <stdio.h>
#include <stdlib.h>

void print_error_log(int line, char *error_message, char *string_guilty){
    printf("\x1b[31mERROR-> ");
	printf("%s at line %d: ",error_message, line);
    printf(string_guilty);
    printf("...");
    printf("\x1b[0m \n");
}

void print_fatal_error(int line, char *error_message, char *string_guilty){
	printf("\x1b[31mFATAL ERROR-> ");
	printf("%s at line %d: ",error_message, line);
	printf(string_guilty);
	printf("...");
	printf("\x1b[0m \n");
	exit(1);
}