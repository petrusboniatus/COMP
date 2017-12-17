//
// Created by someone on 11/13/17.
//
#include "goDefinitions.h"
#include <stdlib.h>
#include <string.h>

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
