//
// Created by someone on 11/10/17.
//

#ifndef UNTITLED_INPUTSYSTEM_H
#define UNTITLED_INPUTSYSTEM_H

#endif //UNTITLED_INPUTSYSTEM_H

#define MAXIMUM_WORD_SIZE_EXCEED (-20)

/*
 * This class exist to provide an efficient buffer to the lexical analyzer, the Input system
 * provides a buffer which the lexical analyzer can get characters one by one and go back if
 * it's necesary.
 *
 * When the Lexical analyzer finish to read the current word it can call pop_word() if the
 * content it's no longer needed or get_and_pop_word() to reserve the memory of the word
 */

typedef struct InputSystemData * InputSystem;

/*
 * @param filename - name of the file to open
 *
 * @returns new_InputSystem - an input system object with memory reserved, parameters initialized
 * and first tow blocks read.
 */
InputSystem new_InputSystem(char *filename);
/*
 * @param self - InputSystem object
 *
 * @returns next - next character of the buffer or or MAXIMUM_WORD_SIZE_EXCEED if
 * BLOCK_SIZE is exceeded.
 */
char get_next_character(InputSystem self);

/*
 * @param self - InputSystem object
 *
 * Go back one character
 */
void return_one_character(InputSystem self);

/*
 * @param self - InputSystem object
 *
 * return completely to the init
 */
void return_to_init(InputSystem self);

/*
 * @param self - InputSystem object
 * @param word - malloc reserved char array that contains the word between initial and last
 *
 * Reserve memory and read the string inside the initial and last pointer when the
 * word is contained in the same blocks. Then pop the word.
 */
void delete_input_system(InputSystem self);

/*
 * @param self - InputSystem object
 * @param word - malloc reserved char array that contains the word between initial and last
 *
 * Reserve memory and read the string inside the initial and last pointer when the
 * word is contained in the same blocks. Then pop the word.
 */
char * get_and_pop_word(InputSystem self);

/*
 * @param self - InputSystem object
 *
 * Advance the initial pointer to the position of the last and create a new block if necesary
 */
void pop_word(InputSystem self);