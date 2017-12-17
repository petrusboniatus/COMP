
#include <stdlib.h>
#include <string.h>
#include "goDefinitions.h"

#define NUMBER_OF_CHAR_SYMBOLS (sizeof(char)*256)
#define BITS_OF_CHAR (sizeof(char)*8)

#define IS_NUMBER(char) ((char)>47 && (char)<58)
#define IS_LETTER(char) ((char)>64 && (char)<91 || (char)>96 && (char)<123)
#define IS_ALPHA(char) (IS_NUMBER(char) || IS_LETTER(char))
#define IS_HEX(char) ((char)>64 && (char)<71 || (char)>96 && (char)<103 || IS_NUMBER(char))
#define IS_OCTAL(char) ((char)>47 && (char)<57)

/*
 * The automata contained in the .c are defined, with the exception of the first, using
 * switch(case) structure. This decision was made to enhance efficiency, because gcc compile
 * the switch case structure as a table, meaning that the cost of a switch with N cases is
 * O(1)
 */


const LexicalComponentId symbols_with_1_character[] = {
		SUM_HASH, DIFFERENCE, PRODUCT, QUOTIENT, REMAINDER, BITWISE_AND, BITWISE_OR,
		BITWISE_XOR, NOT, LESS, GREATER, ASSIGNMENT, OPEN_PARENTHESIS, CLOSE_PARENTHESIS,
		OPEN_BRACKETS, CLOSE_BRACKETS, OPEN_CURLY_BRACKETS, CLOSE_CURLY_BRACKETS, COMMA,
		SEMICOLON, POINT, COLON, (LexicalComponentId) 0 // do not forget Null terminator in c
};

const LexicalComponentId symbols_with_2_characters[] = {
		LEFT_SHIFT, RIGHT_SHIFT, BIT_CLEAR, SHORT_ASSIGNMENT, PLUS_ASSIGNMENT, SUBTRACT_ASSIGNMENT,
		MULTIPLICATION_ASSIGNMENT, DIVISION_ASSIGNMENT, MODULUS_ASSIGNMENT, BITWISE_AND_ASSIGNMENT,
		BITWISE_OR_ASSIGNMENT, BITWISE_XOR_ASSIGNMENT, CHANEL, EQUAL, LESS_OR_EQUAL,
		GREATER_OR_EQUAL, NOT_EQUAL, CONDITIONAL_AND, CONDITIONAL_OR, SELF_INC, SELF_DEC,
		(LexicalComponentId) 0  // do not forget Null terminator in c
};

const LexicalComponentId symbols_with_3_characters[] = {
		LEFT_SHIFT_ASSIGNMENT, RIGHT_SHIFT_ASSIGNMENT, BIT_CLEAR_ASSIGNMENT, MULTIPLE_ARGUMENTS,
		(LexicalComponentId) 0 // do not forget Null terminator in c
};


/*
 * Because this types lexical components are shorter than four characters and his id
 * contains it's string made number, one can just compare if the number that form the
 * character received exist in the list of id's.
 *
 * We define 3 states depending on the number of chars received, and we store the
 * value of the previous char in the *current_state
 *
 */
LexicalComponentId operator_and_punctuation(state *current_state, char automata_input) {

	if (*current_state == INITIAL_STATE) {    // No characters received
		for (int i = 0; symbols_with_1_character[i] != 0; i++) {
			if (symbols_with_1_character[i] == automata_input) {
				*current_state = (symbols_with_1_character[i] << BITS_OF_CHAR);
				return symbols_with_1_character[i];
			}
		}
	} else if (*current_state >= NUMBER_OF_CHAR_SYMBOLS) {  // one character received symbol
		for (int i = 0; symbols_with_2_characters[i] != 0; i++) {
			if (symbols_with_2_characters[i] == *current_state + automata_input) {
				*current_state = (*current_state << BITS_OF_CHAR) + symbols_with_2_characters[i];
				return symbols_with_2_characters[i];
			}
		}
	} else if (*current_state != NEVER_ACCEPT_STATE) {    // tow character received
		for (int i = 0; symbols_with_3_characters[i] != 0; i++) {
			if (symbols_with_3_characters[i] == *current_state + automata_input) {
				*current_state = NEVER_ACCEPT_STATE;
				return symbols_with_3_characters[i];
			}
		}
	}

	*current_state = NEVER_ACCEPT_STATE;
	return NEVER_A_COMPONENT;

};


LexicalComponentId identifier(state *current_state, char automata_input) {
	switch (*current_state) {
		case INITIAL_STATE:
			if (IS_LETTER(automata_input) || automata_input == '_') *current_state = 1;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 1:    // We have received an string that start in a letter and contains alphanumeric chars
			if (IS_ALPHA(automata_input) || automata_input == '_') *current_state = 1;
			else *current_state = NEVER_ACCEPT_STATE;
		default:
			break;
	}
	if (*current_state == NEVER_ACCEPT_STATE) return NEVER_A_COMPONENT;
	else return IDENTIFIER;
};


LexicalComponentId number(state *current_state, char automata_input) {
	switch (*current_state) {
		case INITIAL_STATE:
			if (automata_input == '0') *current_state = 7;
			else if (IS_NUMBER(automata_input)) *current_state = 1;
			else if (automata_input == '.') *current_state = 2;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 1: // We have received only numbers
			if (automata_input == 'E' || automata_input == 'e') *current_state = 3;
			else if (automata_input == '.') *current_state = 2;
			else if (automata_input == 'i') *current_state = 5;
			else if (!IS_NUMBER(automata_input)) *current_state = NEVER_ACCEPT_STATE;
			break;
		case 2: // We have received a point
			if (automata_input == 'E' || automata_input == 'e') *current_state = 3;
			else if (automata_input == 'i') *current_state = 5;
			else if (!IS_NUMBER(automata_input)) *current_state = NEVER_ACCEPT_STATE;
			break;
		case 3: // We have received the 'e' of exponent
			if (automata_input == '+' || automata_input == '-') *current_state = 6;
			else if (IS_NUMBER(automata_input)) *current_state = 4;
			else *current_state = 11;
			break;
		case 4: // The exponent is correct
			if (automata_input == 'i') *current_state = 5;
			else if (!IS_NUMBER(automata_input)) *current_state = NEVER_ACCEPT_STATE;
			break;
		case 5: // We have received the 'i' of imaginary
			*current_state = NEVER_ACCEPT_STATE;
			break;
		case 6: // We have received the sing of the exponent
			if (!IS_NUMBER(automata_input)) *current_state = NEVER_ACCEPT_STATE;
			else *current_state = 4;
			break;
		case 7: // We have received a 0
			if (automata_input == 'x') *current_state = 8;
			else if (IS_OCTAL(automata_input)) *current_state = 10;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 8: // We have received 0x
			if (IS_HEX(automata_input)) *current_state = 9;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 9: // We are receiving hexadecimal number
			if (!IS_HEX(automata_input)) *current_state = NEVER_ACCEPT_STATE;
			break;
		case 10: // We have received an octal number
			if (!IS_OCTAL(automata_input)) *current_state = NEVER_ACCEPT_STATE;
			break;
		case 11: //We have received an error
			*current_state = NEVER_ACCEPT_STATE;
			break;
		default:
			break;
	};

	if (*current_state == NEVER_ACCEPT_STATE) return NEVER_A_COMPONENT;
	else if (*current_state == 1) return INTEGER;
	else if (*current_state == 2) return FLOAT;
	else if (*current_state == 4) return FLOAT;
	else if (*current_state == 5) return IMAGINARY;
	else if (*current_state == 7) return INTEGER;
	else if (*current_state == 9) return INTEGER;
	else if (*current_state == 10)return INTEGER;
	else if (*current_state == 11)return MALFORMED_NUMBER;
	else return PART_OF_A_COMPONENT;

};

LexicalComponentId key_word(state *current_state, char automata_input) {

	switch (*current_state) {
		case INITIAL_STATE:
			if (automata_input == 'i') *current_state = 10; //reading include
			else if (automata_input == 'p') *current_state = 20; //reading package
			else if (automata_input == 'v') *current_state = 30; //reading var
			else if (automata_input == 'g') *current_state = 40; //reading go
			else if (automata_input == 'f') *current_state = 50; //reading for or func
			else if (automata_input == 'r') *current_state = 60;
			else *current_state = NEVER_ACCEPT_STATE;
			break;

		case 10: // the fist letter of include was read
			if (automata_input == 'm') *current_state = 11;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 11:
			if (automata_input == 'p') *current_state = 12;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 12:
			if (automata_input == 'o') *current_state = 13;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 13:
			if (automata_input == 'r') *current_state = 14;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 14:
			if (automata_input == 't') *current_state = 15;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 15:    // Word include recognized
			*current_state = NEVER_ACCEPT_STATE;
			break;

		case 20: // the fist letter of package was read
			if (automata_input == 'a') *current_state = 21;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 21:
			if (automata_input == 'c') *current_state = 22;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 22:
			if (automata_input == 'k') *current_state = 23;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 23:
			if (automata_input == 'a') *current_state = 24;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 24:
			if (automata_input == 'g') *current_state = 25;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 25:
			if (automata_input == 'e') *current_state = 26;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 26:    // Word package recognized
			*current_state = NEVER_ACCEPT_STATE;
			break;

		case 30: // The first letter of var was read
			if (automata_input == 'a') *current_state = 31;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 31:
			if (automata_input == 'r') *current_state = 32;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 32:    // Word var recognized
			*current_state = NEVER_ACCEPT_STATE;
			break;

		case 40: // The first letter of go was read
			if (automata_input == 'o') *current_state = 41;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 41: // word recognized
			*current_state = NEVER_ACCEPT_STATE;
			break;

		case 50: // The first letter of for or func was read
			if (automata_input == 'o') *current_state = 51;
			else if (automata_input == 'u') *current_state = 53;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 51: // read fo of for
			if (automata_input == 'r') *current_state = 52;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 52:    // Word for recognized
			*current_state = NEVER_ACCEPT_STATE;
			break;

		case 53: // read fu of func
			if (automata_input == 'n') *current_state = 54;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 54:
			if (automata_input == 'c') *current_state = 55;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 55:
			*current_state = NEVER_ACCEPT_STATE;
			break;

		case 60: //entered the r of range
			if (automata_input == 'a') *current_state = 61;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 61:
			if (automata_input == 'n') *current_state = 62;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 62:
			if (automata_input == 'g') *current_state = 63;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 63:
			if (automata_input == 'e') *current_state = 64;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 64: //acceptation of word range
			*current_state = NEVER_ACCEPT_STATE;
			break;

		default:
			break;
	}

	if (*current_state == 15 ||
		*current_state == 26 ||
		*current_state == 32 ||
		*current_state == 41 ||
		*current_state == 52 ||
		*current_state == 55 ||
		*current_state == 64) {
		return KEY_WORD;
	} else if (*current_state != NEVER_ACCEPT_STATE) {
		return PART_OF_A_COMPONENT;
	} else {
		return NEVER_A_COMPONENT;
	}
}

LexicalComponentId is_end_of_file(state *current_state, char automata_input) {

	switch (*current_state) {
		case INITIAL_STATE:
			if (automata_input == -1) *current_state = 1;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 1:
			*current_state = NEVER_ACCEPT_STATE;
			break;
		default:
			break;
	}

	if (*current_state == 1)
		return END_OF_FILE;
	else return NEVER_A_COMPONENT;
};

LexicalComponentId string_literal(state *current_state, char automata_input) {
	switch (*current_state) {
		case INITIAL_STATE:
			if (automata_input == '"') *current_state = 1;
			break;
		case 1:
			if (automata_input == '"') *current_state = 2;
			else if (automata_input == -1) *current_state = 4;
			else if (automata_input == '\\') *current_state = 3;
			break;
		case 2: // received closed String
			*current_state = NEVER_ACCEPT_STATE;
			break;
		case 3: // received a character jump
			*current_state = 1;
			break;
		case 4: // We have received an string without closing
			*current_state = NEVER_ACCEPT_STATE;
			break;
		default:
			break;
	}
	if (*current_state == 2) return STRING;
	else if (*current_state == 1 || *current_state == 3) return PART_OF_A_COMPONENT;
	else if (*current_state == 4) {
		return UNFINISHED_STRING;
	}
	else return NEVER_A_COMPONENT;
};

NotLexicalComponentId not_lexical_elements_recognizer(state *current_state, char automata_input) {
	switch (*current_state) {
		case INITIAL_STATE:
			if (automata_input == SPACE || automata_input == TAB || automata_input == CARRIAGE_RETURN) {
				*current_state = INITIAL_STATE;
			} else if (automata_input == '/') {
				*current_state = 1;
			} else {
				*current_state = NEVER_ACCEPT_STATE;
			}
			break;
		case 1: // A bar has entered
			if (automata_input == '/') *current_state = 2;
			else if (automata_input == '*') *current_state = 3;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 2: // double bar has entered
			if (automata_input == '\n') *current_state = 5;
			break;
		case 3: // multilayer comment entered
			if (automata_input == '*') *current_state = 4;
			break;
		case 4: // multilayer comment possible end
			if (automata_input == '/') *current_state = INITIAL_STATE;
			else *current_state = 3;
			break;
		case 5: // comment was finalized
			*current_state = NEVER_ACCEPT_STATE;
		default:
			break;
	}
	if (*current_state == INITIAL_STATE) return (NotLexicalComponentId) automata_input;
	else if (*current_state == 5) return COMMENT;
	else if (*current_state > INITIAL_STATE) return PART_OF_A_NON_LEXICAL_COMPONENT;
	else return NOT_IGNORABLE_ELEMENT;

}

LexicalComponentId new_lines_recognizer(state *current_state, char automata_input) {
	switch (*current_state) {
		case INITIAL_STATE:
			if (automata_input == '\n') *current_state = 1;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		case 1:
			if (automata_input == '\n') *current_state = 1;
			else *current_state = NEVER_ACCEPT_STATE;
			break;
		default:
			break;
	}
	if (*current_state == 1) return NEW_LINE;
	else return NEVER_A_COMPONENT;
}



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
RecognitionAutomata new_recognition_automata() {
	RecognitionAutomata new = (RecognitionAutomata) malloc(sizeof(struct RecognitionAutomataData));

	new->not_lexical_elements_recognizer = &not_lexical_elements_recognizer;
	new->lexical_recognizers[0] = &number;
	new->lexical_recognizers[1] = &operator_and_punctuation;
	new->lexical_recognizers[2] = &string_literal;
	new->lexical_recognizers[3] = &key_word;
	new->lexical_recognizers[4] = &identifier;
	new->lexical_recognizers[5] = &new_lines_recognizer;
	new->lexical_recognizers[6] = &is_end_of_file;
	new->lexical_recognizers[7] = 0;

	return new;
}

void delete_recognition_automata(RecognitionAutomata self) {
	free(self);
}

/*
 * @param e - the token that will be liberated
 *
 * liberates only the memory of the struct content
 */
void free_token(Token e){
	if(e->lexeme!=0) free(e->lexeme);
	free(e);
}

/*
 * @param e - token to liberate
 * @param key - it does not matter, it is here so the liberation function can be placed as
 * the free function in a map.
 *
 * Liberates the token and it's contained data
 */
void free_token_entry(char *key, Token e) {
	Token token_to_free = (Token) e;
	free(key); // Key and lexeme are the same pointer
	free(token_to_free);
}

/*
 * Compare weather or @param e1 equals @param e2.
 *
 * @return 1 if they are equals, 0 if not
 */
int token_entry_equals(Token e1, Token e2) {
	Token foo = (Token) e1;
	Token var = (Token) e2;
	return strcmp(foo->lexeme, var->lexeme) == 0;
}

