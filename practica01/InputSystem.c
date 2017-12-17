//
// Created by someone on 10/13/17.
//

#include <stdio.h>
#include <stdlib.h>
#include "InputSystem.h"
#include "ErrorLog.h"

#define BLOCK_SIZE 128
#define BLOCK_LAST_INDEX (BLOCK_SIZE-1)

/*
 * This class exist to provide an efficient buffer to the lexical analyzer, the Input system
 * provides a buffer which the lexical analyzer can get characters one by one and go back if
 * it's necesary.
 *
 * When the Lexical analyzer finish to read the current word it can call pop_word() if the
 * content it's no longer needed or get_and_pop_word() to reserve the memory of the word
 */


/*
 * InputSystemData: Elements of the input system object
 * first_block: pointer to the first block
 * second_block: pointer to the second block
 * initial: pointer to the first element of the word that is being read.
 * last: pointer to the current element of the block being read.
 * current_file: pointer to the file read
 */
typedef struct InputSystemData {
	char *first_block;
	char *second_block;
	char *initial;
	char *last;
	FILE *current_file;
} InputSystemData;

/*
 * @param self - InputSystem object
 *
 * Initialize the tow blocks with the first chars in the file. It introduce the EOF (sentinel)
 * at the last Index of the blocks
 */
void read_first_two_blocks(InputSystem self) {
	int i;
	char current_char = 0;
	for (i = 0; i < BLOCK_LAST_INDEX && current_char != EOF; i++) {
		current_char = (char) fgetc(self->current_file);
		self->first_block[i] = current_char;
	}
	self->first_block[BLOCK_LAST_INDEX] = EOF;

	if (i != BLOCK_LAST_INDEX) return;

	for (i = 0; i < BLOCK_LAST_INDEX && current_char != EOF; i++) {
		current_char = (char) fgetc(self->current_file);
		self->second_block[i] = current_char;
	}
	self->second_block[BLOCK_LAST_INDEX] = EOF;
}
/*
 * @param self - InputSystem object
 *
 * The old second block is now the first, and the new second is filed with the file data
 */
void read_next_block(InputSystem self) {
	int i;

	char *swap_aux = self->first_block;
	self->first_block = self->second_block;
	self->second_block = swap_aux;

	char current_char = 0;
	for (i = 0; i < BLOCK_LAST_INDEX && current_char != EOF; i++) {
		current_char = (char) fgetc(self->current_file);
		self->second_block[i] = current_char;
	}

	self->second_block[i] = EOF;
}

/*
 * @param filename - name of the file to open
 *
 * @returns new_InputSystem - an input system object with memory reserved, parameters initialized
 * and first tow blocks read.
 */
InputSystem new_InputSystem(char *filename) {
	FILE *file_to_read = fopen(filename, "r");
	if (!file_to_read) print_fatal_error("Impossible to open given file", filename);

	InputSystem new_InputSystem = (InputSystem) malloc(sizeof(InputSystemData));
	new_InputSystem->first_block = (char *) malloc(sizeof(char) * BLOCK_SIZE);
	new_InputSystem->second_block = (char *) malloc(sizeof(char) * BLOCK_SIZE);
	new_InputSystem->current_file = file_to_read;
	new_InputSystem->initial = new_InputSystem->first_block;
	new_InputSystem->last = new_InputSystem->first_block;
	read_first_two_blocks(new_InputSystem);

	return new_InputSystem;
}

/*
 * @param self - InputSystem object
 *
 * @returns the next character in the file or MAXIMUM_WORD_SIZE_EXCEED if
 * BLOCK_SIZE is exceeded.
 *
 * Define the policy when an EOF is encountered, it can be:
 * 1. First block end, so self->next should point to the second block
 * 2. Second block end, so the words it's at it maximum and an error should
 *    be returned
 * 3. Real EOF: it will return EOF
 */
char manage_EOF(InputSystem self) {
	if (self->last == self->first_block + BLOCK_LAST_INDEX) {
		self->last = self->second_block;
		return *(self->last);
	} else if (self->last == self->second_block + BLOCK_LAST_INDEX) {
		return MAXIMUM_WORD_SIZE_EXCEED;
	} else {
		self->last--;    //With this statement ensure it will remain returning always EOF
		return EOF;
	}
}

/*
 * @param self - InputSystem object
 *
 * @returns next - next character of the buffer or or MAXIMUM_WORD_SIZE_EXCEED if
 * BLOCK_SIZE is exceeded.
 */
char get_next_character(InputSystem self) {
	char next = *(self->last);

	if (next == EOF) {
		next = manage_EOF(self);
	}
	self->last++;
	return next;
}

/*
 * @param self - InputSystem object
 *
 * Go back one character
 */
void return_one_character(InputSystem self) {
	if (self->last == self->second_block)
		self->last = self->first_block + BLOCK_LAST_INDEX - 1;
	else if (self->last != self->initial)
		self->last--;
}

/*
 * @param self - InputSystem object
 *
 * return completely to the init
 */
void return_to_init(InputSystem self) {
	self->last = self->initial;
}

/*
 * @param self - InputSystem object
 *
 * Advance the initial pointer to the position of the last and create a new block if necesary
 */
void pop_word(InputSystem self) {
	self->initial = self->last;
	if (self->second_block <= self->last && self->last < self->second_block + BLOCK_SIZE)
		read_next_block(self);
}

/*
 * @param self - InputSystem object
 * @param word - malloc reserved char array that contains the word between initial and last
 *
 * Reserve memory and read the string inside the initial and last pointer when the
 * word is contained in different blocks
 */
char *pop_word_from_different_blocks(InputSystem self) {
	unsigned long word_size_first_block = (self->first_block + BLOCK_LAST_INDEX) - self->initial;
	unsigned long word_size_second_block = (self->last - self->second_block);
	unsigned long word_size = word_size_first_block + word_size_second_block;
	char *word = (char *) malloc(sizeof(char) * word_size + 1);

	unsigned long word_index = 0;
	for (unsigned long i = 0; i < word_size_first_block; i++, word_index++)
		word[word_index] = self->initial[i];
	for (unsigned long i = 0; i < word_size_second_block; i++, word_index++)
		word[word_index] = self->second_block[i];

	word[word_index] = 0;

	return word;
}

/*
 * @param self - InputSystem object
 * @param word - malloc reserved char array that contains the word between initial and last
 *
 * Reserve memory and read the string inside the initial and last pointer when the
 * word is contained in the same blocks
 */
char *pop_word_from_same_block(InputSystem self) {
	unsigned long word_size = self->last - self->initial;
	char *word = (char *) malloc(sizeof(char) * word_size);

	unsigned long i;
	for (i = 0; i < word_size; i++)
		word[i] = self->initial[i];

	word[i] = 0;

	return word;
}

/*
 * @param self - InputSystem object
 * @param word - malloc reserved char array that contains the word between initial and last
 *
 * Reserve memory and read the string inside the initial and last pointer when the
 * word is contained in the same blocks. Then pop the word.
 */
char *get_and_pop_word(InputSystem self) {
	char *word;
	if (self->last >= self->second_block && self->last < (self->second_block + BLOCK_SIZE))
		word = pop_word_from_different_blocks(self);
	else
		word = pop_word_from_same_block(self);

	pop_word(self);
	return word;
}

/*
 * @param self - InputSystem object
 *
 * Free all reserved memory to the InputSystem object
 */
void delete_input_system(InputSystem self) {
	fclose(self->current_file);
	free(self->first_block);
	free(self->second_block);
	free(self);
}