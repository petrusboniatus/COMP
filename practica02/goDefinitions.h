//
// Created by someone on 10/14/17.
//
#ifndef UNTITLED_TOKENDEFINITIONS_H
#define UNTITLED_TOKENDEFINITIONS_H

#endif //UNTITLED_TOKENDEFINITIONS_H


typedef enum LexicalComponentId {

	// Error Messages
	UNFINISHED_COMMENT = -4,
	LEXICAL_COMPONENT_IS_TO_BIG = -3,
	MALFORMED_NUMBER = -2,
	UNFINISHED_STRING = -1,
	NEVER_A_COMPONENT = -5, // It is a string that don't correspond to any lexical component

	//Control Messages
	END_OF_FILE = 0,

	//words
	KEY_WORD = 2,
	IDENTIFIER = 3,

	// Literals
	INTEGER = 4,
	FLOAT = 5,
	IMAGINARY = 6,
	STRING= 7,


	//Operators: from here all numbers all calculated ass the byte value of the corresponding
	//string, for further understanding see resources/PerfectHash.c, where is the code that
	//generate this numbers
	SUM_HASH = 43 ,
	DIFFERENCE = 45 ,
	PRODUCT = 42 ,
	QUOTIENT = 47 ,
	REMAINDER = 37 ,
	BITWISE_AND = 38 ,
	BITWISE_OR = 124 ,
	BITWISE_XOR = 94 ,
	LEFT_SHIFT = 15420 ,
	RIGHT_SHIFT = 15934 ,
	BIT_CLEAR = 9822 ,
	ASSIGNMENT = 61 ,
	SHORT_ASSIGNMENT = 14909 ,
	PLUS_ASSIGNMENT = 11069 ,
	SUBTRACT_ASSIGNMENT = 11581 ,
	MULTIPLICATION_ASSIGNMENT = 10813 ,
	DIVISION_ASSIGNMENT = 12093 ,
	MODULUS_ASSIGNMENT = 9533 ,
	BITWISE_AND_ASSIGNMENT = 9789 ,
	BITWISE_OR_ASSIGNMENT = 31805 ,
	BITWISE_XOR_ASSIGNMENT = 24125 ,
	LEFT_SHIFT_ASSIGNMENT = 3947581 ,
	RIGHT_SHIFT_ASSIGNMENT = 4079165 ,
	BIT_CLEAR_ASSIGNMENT = 2514493 ,
	CHANEL = 15405 ,
	MULTIPLE_ARGUMENTS = 3026478 ,
	SELF_INC = 11051 ,
	SELF_DEC = 11565 ,
	EQUAL = 15677 ,
	LESS = 60 ,
	GREATER = 62 ,
	LESS_OR_EQUAL = 15421 ,
	GREATER_OR_EQUAL = 15933 ,
	NOT_EQUAL = 8509 ,
	NOT = 33 ,
	CONDITIONAL_AND = 9766 ,
	CONDITIONAL_OR = 31868 ,

	//separators
	NEW_LINE = 10,


	OPEN_PARENTHESIS = 40 ,
	CLOSE_PARENTHESIS = 41 ,
	OPEN_BRACKETS = 91 ,
	CLOSE_BRACKETS = 93 ,
	OPEN_CURLY_BRACKETS = 123 ,
	CLOSE_CURLY_BRACKETS = 125 ,
	COMMA = 44 ,
	SEMICOLON = 59 ,
	POINT = 46 ,
	COLON = 58 ,
} LexicalComponentId;

//Whether the return is a message error.
#define IS_LEXICAL_ERROR(var) ((var)<0)

//Whether the content can be different so it's necesary to store the lexeme
#define CONTENT_CAN_BE_DIFFERENT(var) ((var)>1 && (var)<8)


/*
 * One token represent a lexical component, it's defined as follow:
 * - id: enum that define the type
 * - lexeme: string that can be null if the component is always the same
 * CONTENT_CAN_BE_DIFFERENT(id) = TRUE
 */

typedef struct TokenData {
    LexicalComponentId id;
    char *lexeme;
} TokenData;

typedef TokenData * Token;

/*
 * @param e - the token that will be liberated
 *
 * liberates only the memory of the struct content
 */
void free_token(Token e);

/*
 * @param e - token to liberate
 * @param key - it does not matter, it is here so the liberation function can be placed as
 * the free function in a map.
 *
 * Liberates the token and it's contained data
 */
void free_token_entry(char *key, Token e);

/*
 * Compare weather or @param e1 equals @param e2.
 *
 * @return 1 if they are equals, 0 if not
 */
int token_entry_equals(Token e1, Token e2);


