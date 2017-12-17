#include <stdio.h>
#include "stdlib.h"
typedef enum {
	NO_ERROR = 1,
	//Syntax errors
	TOO_MANY_ARGUMENTS = -1,
	TOO_FEW_ARGUMENTS = -2,
	INVALID_ARITHMETIC_OPERATOR = -3,
	UNCLOSED_PARENTHESES = -4,
	TOO_MANY_CLOSE_PARENTHESIS = -5,
	UNRECOGNIZED_SYNTAX = -6,
	NOT_A_FUNCTION = -7,
	NOT_A_VARIABLE = -8,
	//Lexical errors
	UNRECOGNIZED_SYMBOL = -1000,

	//Execution Error
	CANT_MODIFY_CONST = -2000,
	DIVISION_BY_0 = -2001

} CALCULATOR_ERROR;

#define LOG_RESULT(str, ...) \
	printf(str, __VA_ARGS__);

#define LOG_ERROR(error) \
	printf("\x1b[31mERROR-> "); printf("%s", get_err_message(error)); printf("\x1b[0m \n");

#define LOG_WARNING(warning) \
	printf("\e[33mWARNING-> "); printf(warning); printf("\x1b[0m \n");

char * get_err_message(CALCULATOR_ERROR error_code);

