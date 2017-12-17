//
// Created by someone on 10/14/17.
//
#ifndef UNTITLED_TOKENDEFINITIONS_H
#define UNTITLED_TOKENDEFINITIONS_H

#endif //UNTITLED_TOKENDEFINITIONS_H


/*
 * This goDefinitions.c/.h provides all the GO language definitions, including:
 *
 * 	1. Types of lexical components: contained in the enum LexicalComponentId
 * 	2. Types of accepted non lexical components: contained in the enum NotLexicalComponent
 * 	3. Types of lexical component detections errors: contained also in LexicalComponentId
 * 	4. Regular expressions of that lexical components: For practices restrictions they are present
 * 	in the form of functions that emulate the finite state automata that recognize that expressions.
 * 	5. The definition of a token
 */


typedef enum NotLexicalComponentId{
	//Ignorable elements
	NOT_IGNORABLE_ELEMENT = 0,
	PART_OF_A_NON_LEXICAL_COMPONENT = 1,
	COMMENT = 2,
	SPACE = 32,
	CARRIAGE_RETURN = 15,
	TAB = 11
} NotLexicalComponentId;


typedef enum LexicalComponentId {

	// Error Messages
	LEXICAL_COMPONENT_IS_TO_BIG = -3,
	MALFORMED_NUMBER = -2,
	UNFINISHED_STRING = -1,


	//Control Messages
	NEVER_A_COMPONENT = 0, // It is a string that don't correspond to any lexical component
	PART_OF_A_COMPONENT = 1, // It is a string that could be a part of a lexical component

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
	END_OF_FILE = 9,

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

//Wheather the content can be different so it's necesary to store the lexeme
#define CONTENT_CAN_BE_DIFFERENT(var) ((var)>1 && (var)<8)


// The automata state are defined by an integer
typedef int state;
#define INITIAL_STATE 0			// When starting to recognize an string state must be that
#define NEVER_ACCEPT_STATE (-1)	// This is the hole state, it will never reach an acceptation state


/*
 * @param current_state: pointer to the current state of the automata, it will be update with
 * the new state
 * @param automata_input: char input of the automata
 *
 * @returns A lexical component id if the chain correspond for now with the lexical components
 * that the automata recognize. Otherwise it can return:
 *
 * PART_OF_A_COMPONENT - if a recognition of the particular lexical component could be reached
 * NEVER_A_COMPONENT - if the recognition could not be reached anyway(hole state)
 * error message - it recognized a concrete lexical error
 */
typedef LexicalComponentId (*transition_function)(state *  current_state, char automata_input);

/*
 * @param current_state: pointer to the current state of the automata, it will be update with
 * the new state
 * @param automata_input: char input of the automata
 *
 * @return The not lexical valid component recognized
 */
typedef NotLexicalComponentId (*not_lex_transition_function)(state * current_state, char automata_input);


/*
 * All the recognition functions are contained in RecognitionAutomata.
 * The memory of the object is reserved with new_recognition_automata() and liberated
 * with delete_recognition_automata()
 *
 * It contains the following attributes:
 *
 * - lexical_recognizer: automata that recognize the lexical elements. This elements are ordered
 * with the following criteria: if an automata A is before B it means that in the set of
 * strings recognized by both A and B; A recognize longest continuation possible of all that chains.
 *
 * - not_lexical_recognizer: automata that recognize not lexical elements
 */
#define NUMBER_OF_AUTOMATA 7
typedef struct RecognitionAutomataData{
	transition_function lexical_recognizers[NUMBER_OF_AUTOMATA+1]; //Remember the null terminator
	not_lex_transition_function not_lexical_elements_recognizer;
}RecognitionAutomataData;

typedef struct RecognitionAutomataData * RecognitionAutomata;
RecognitionAutomata new_recognition_automata();
void delete_recognition_automata(RecognitionAutomata self);




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


