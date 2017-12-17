//
// Created by someone on 18/10/17.
//


#include <stdio.h>
#include <stdlib.h>
#include "LexicalAnalyzer.h"
#include "ErrorLog.h"

/*
 * Data necesary to perform the lexical analysis, including:
 * - symbols_table: map where put the ids encountered
 * - input_system: data structures that provides the char of the file
 * - go_lex: contains all the automatons that recognize the go Lexical components
 */
typedef struct LexicalAnalyzerData {
	HashMap symbols_table;
	InputSystem input_system;
	RecognitionAutomata go_lex;
} LexicalAnalyzerData;


/*
 * @param self - LexicalAnalyzer object
 *
 * Function used to go to the next line when an error occurred.
 * It gets characters of the input system until it gets '\n'
 * so it pop the word
 */
void jump_to_the_end_of_the_line(LexicalAnalyzer self) {
	char next_char = get_next_character(self->input_system);
	while (next_char != -1 && next_char != '\n') {
		pop_word(self->input_system);
		next_char = get_next_character(self->input_system);
	}
	return_one_character(self->input_system);
}

/*
 * @param self - LexicalAnalyzer object
 * @param error - error code obtained from the automata
 *
 * It go to the end of the line and display an error message indicating what goes
 * worn and in witch part of code
 */
void handle_lexical_error(LexicalAnalyzer self, LexicalComponentId error){

	char *string_that_contains_the_error = get_and_pop_word(self->input_system);
	jump_to_the_end_of_the_line(self);
	switch (error) {
		case LEXICAL_COMPONENT_IS_TO_BIG:
			print_error_log("This lexical component is too big", string_that_contains_the_error);
			break;
		case MALFORMED_NUMBER:
			print_error_log("Malformed number", string_that_contains_the_error);
			break;
		case UNFINISHED_STRING:
			print_error_log("Unfinished string", string_that_contains_the_error);
			break;
		case PART_OF_A_COMPONENT: //generic
			print_error_log("Unrecognized string", string_that_contains_the_error);
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

	LexicalAnalyzer new = (LexicalAnalyzer) malloc(sizeof(LexicalAnalyzer));

	new->input_system = new_InputSystem(filename);
	new->symbols_table = symbol_table;
	new->go_lex = new_recognition_automata();
}


/*
 * @param self - LexicalAnalyzer object
 *
 * It travel the states of the ignorable elements automata until it find an element that it's
 * not ignorable.
 * If the input buffer happens to be to large it just pop the word
 *
 * TODO display an special message to unfinished comments, not just the generic
 */
void skip_NotLexicalComponent(LexicalAnalyzer self) {
	NotLexicalComponentId current_id = NOT_IGNORABLE_ELEMENT;
	NotLexicalComponentId previous_id;
	state automata_state = INITIAL_STATE;
	char next_character;
	do {
		next_character = get_next_character(self->input_system);
		if (next_character == MAXIMUM_WORD_SIZE_EXCEED) {
			return_one_character(self->input_system);
			pop_word(self->input_system);
			continue;
		}

		previous_id = current_id;
		current_id = self->go_lex->not_lexical_elements_recognizer(&automata_state, next_character);

	} while (current_id != NOT_IGNORABLE_ELEMENT);

	if (next_character != EOF) return_one_character(self->input_system);
	if (previous_id == PART_OF_A_COMPONENT) return_one_character(self->input_system);
	if (previous_id != NOT_IGNORABLE_ELEMENT) get_and_pop_word(self->input_system);

}

/*
 * @param self - LexicalAnalyzer object
 * @param transit - transition function of the automata
 *
 * @returns the recognized element by the automata, it could be:
 * 1. Valid lexical component
 * 2. Lexical error
 * 3. PART_OF_A_COMPONENT, when none element was found
 */

LexicalComponentId try_function(LexicalAnalyzer self, transition_function transit) {
	state automata_state = INITIAL_STATE;
	LexicalComponentId current_id = PART_OF_A_COMPONENT;
	LexicalComponentId previous_id;
	char next_char;
	do {
		next_char = get_next_character(self->input_system);
		if (next_char == MAXIMUM_WORD_SIZE_EXCEED){
			previous_id = LEXICAL_COMPONENT_IS_TO_BIG;
			break;
		}

		previous_id = current_id;
		current_id = transit(&automata_state, next_char);
	} while (current_id != NEVER_A_COMPONENT);

	if (next_char == EOF);
		//Do not do nothing, Input systems always returns EOF when it's reached
	else if (previous_id != PART_OF_A_COMPONENT)
		return_one_character(self->input_system);
	else
		return_to_init(self->input_system);

	return previous_id;
}

/*
 * @param self - LexicalAnalyzer object
 * @param current_id - id of the token that will be create.
 *
 * @returns New token with reserved memory or 0 if the id does not match a token
 */
Token create_token_and_insert_if_necesary(LexicalAnalyzer self, LexicalComponentId current_id) {
	if(current_id == PART_OF_A_COMPONENT){
		handle_lexical_error(self,current_id);
		return 0;
	}

	Token token = (Token) malloc(sizeof(Token));
	token->id = current_id;
	token->lexeme = 0;

	if (CONTENT_CAN_BE_DIFFERENT(current_id))
		token->lexeme = get_and_pop_word(self->input_system);
	else
		pop_word(self->input_system);

	if (current_id == IDENTIFIER && !contains(self->symbols_table, token->lexeme))
		put(self->symbols_table, token->lexeme, token);

	return token;
}


/*
 * @param self - Lexical analyzer object
 *
 * @returns the next lexical component
 *
 * 1. Iterate over the ignorable elements
 * 2. Try the automatons until it find a lexical component. It exist an error it try again
 * starting from the beginning
 * 3. Create a token and return it
 */
Token get_next_lexical_component(LexicalAnalyzer self) {

	skip_NotLexicalComponent(self);

	LexicalComponentId current_id = PART_OF_A_COMPONENT;
	for (int i = 0; self->go_lex->lexical_recognizers[i]; i++) {
		current_id = try_function(self, self->go_lex->lexical_recognizers[i]);

		if (IS_LEXICAL_ERROR(current_id)) {
			handle_lexical_error(self, current_id);
			i = 0;
			continue;
		}

		if (current_id != PART_OF_A_COMPONENT) break;
	}

	return create_token_and_insert_if_necesary(self, current_id);
}


/*
 * @param Lexical analyzer object
 *
 * Liberate the memory of the object
 */
void close_lexical_analyzer(LexicalAnalyzer self) {
	delete_input_system(self->input_system);
	delete_recognition_automata(self->go_lex);
	free(self);
}


