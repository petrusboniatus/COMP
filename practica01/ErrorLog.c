//
// Created by someone on 10/13/17.
//

#include "ErrorLog.h"
#include <stdio.h>
#include <stdlib.h>

void print_error_log(char *error_message, char *string_guilty){
    printf("\x1b[31mERROR-> ");
    printf(error_message);
	printf(": ");
    printf(string_guilty);
    printf("...");
    printf("\x1b[0m \n");
}

void print_fatal_error(char *error_message, char *string_guilty){
	printf("\x1b[31mFATAL ERROR-> ");
	printf(error_message);
	printf(": ");
	printf(string_guilty);
	printf("...");
	printf("\x1b[0m \n");
	exit(1);
}