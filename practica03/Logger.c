//
// Created by pedro on 12/2/17.
//
#include "Logger.h"
char * get_err_message(CALCULATOR_ERROR error_code){
	switch(error_code){
		//Syntax error
		case TOO_MANY_ARGUMENTS : return "Too many arguments for the function";
		case TOO_FEW_ARGUMENTS : return "Too few arguments for the function";
		case INVALID_ARITHMETIC_OPERATOR : return "This is not a valid algebra";
		case UNCLOSED_PARENTHESES : return "You forgot to close the parentheses";
		case TOO_MANY_CLOSE_PARENTHESIS: return "You forgot to open the parentheses";
		case UNRECOGNIZED_SYNTAX: return "Unrecognized syntax";
		case NOT_A_FUNCTION: return "A variable is not a function";
		case NOT_A_VARIABLE: return "A function is not a variable";
		//Lexical Errors
		case UNRECOGNIZED_SYMBOL : return "This symbol is not contained in this unassuming calculator";

		//Execution Error
		case CANT_MODIFY_CONST: return "You can not modify and universal constant... yet ;)";
		case DIVISION_BY_0: return "Division by 0!";

		default: return "No message for this error, lest pretend it never existed...";
	}
}
