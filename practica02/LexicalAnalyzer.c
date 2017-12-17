//
// Created by someone on 18/10/17.
//


#include <stdio.h>
#include <stdlib.h>
#include "LexicalAnalyzer.h"
#include "ErrorLog.h"
#include "lex.yy.h"


/*static external variables of the flex generated lexer*/
extern char *yytext;    //Pointer to the recognized text
extern FILE *yyin;      //File that is been read
extern int yylineno;    //Line of the recognized text
extern int yyleng;      //Size of the recognized element

/*
 * Data necesary to perform the lexical analysis, including:
 * - symbols_table: map where put the ids encountered
 * - go_lex: contains all the automatons that recognize the go Lexical components
 */
typedef struct LexicalAnalyzerData {
	HashMap symbols_table;
} LexicalAnalyzerData;


/*
 * @param self - LexicalAnalyzer object
 * @param error - error code obtained from the automata
 *
 * It go to the end of the line and display an error message indicating what goes
 * worn and in witch part of code
 */
void handle_lexical_error(LexicalComponentId error) {
	switch (error) {
		case LEXICAL_COMPONENT_IS_TO_BIG:
			print_error_log(yylineno, "This lexical component is too big", yytext);
			break;
		case MALFORMED_NUMBER:
			print_error_log(yylineno, "Malformed number", yytext);
			break;
		case UNFINISHED_STRING:
			print_error_log(yylineno, "Unfinished string", yytext);
			break;
		case UNFINISHED_COMMENT:
			print_error_log(yylineno, "Unfinished comment", yytext);
			break;
		case NEVER_A_COMPONENT: //generic
			print_error_log(yylineno, "Unrecognized element", yytext);
			break;
		default:
			break;
	}
}

/*
 * @param filename - name of the file that it will be read
 * @param symbol_table - initialized symbol table
 *
 * @returns new Initialized Lexical analyzer to the file
 */
LexicalAnalyzer new_LexicalAnalyzer(char *filename, HashMap symbol_table) {
	yyin = fopen(filename, "r");
	LexicalAnalyzer new = (LexicalAnalyzer) malloc(sizeof(LexicalAnalyzerData));
	new->symbols_table = symbol_table;
	return new;
}


/*
 * @param self - Lexical analyzer object
 *
 * @returns the next lexical component
 *
 * 1. Skip and show the message of the possible errors of the lexer
 * 2. Reserve memory and insert in the symbol table if necessary
 */
Token get_next_lexical_component(LexicalAnalyzer self) {
	/*Skip possible errors*/
	LexicalComponentId lexical_component_id = (LexicalComponentId) yylex();
	while (IS_LEXICAL_ERROR(lexical_component_id)) {
		handle_lexical_error(lexical_component_id);
		lexical_component_id = (LexicalComponentId) yylex();
	}

	/*create the token, insert the lexeme in memory and in the symbol table if necesary*/
	Token new_token = (Token) malloc(sizeof(TokenData));
	new_token->id = lexical_component_id;
	new_token->lexeme = 0;

	if (CONTENT_CAN_BE_DIFFERENT(new_token->id)) {
		new_token->lexeme = (char *) malloc(sizeof(char) * yyleng + 1);
		strcpy(new_token->lexeme, yytext);
		if (new_token->id == IDENTIFIER && !contains(self->symbols_table, new_token->lexeme)) {
			put(self->symbols_table, new_token->lexeme, new_token);
		}
	}

	return new_token;
}


/*
 * @param Lexical analyzer object
 *
 * Liberate the memory of the object
 */
void close_lexical_analyzer(LexicalAnalyzer self) {
	free(self);
}


