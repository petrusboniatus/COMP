//
// Created by someone on 10/21/17.
//
#include <stdio.h>
#include "LexicalAnalyzer.h"



#ifndef UNTITLED_INTEGRATIONTEST_H_H
#define UNTITLED_INTEGRATIONTEST_H_H

#endif //UNTITLED_INTEGRATIONTEST_H_H


/*
 * This test is meant to serve the correcting of the practice. Because in the system
 * lexemes are not always store it needs adHoc print lexical id and free token.
 */

void print_string_from_lexical_id(LexicalComponentId id){
	char * characters_in_id = (char*)&id;

	int i;
	for(i = 0; i<4 && characters_in_id[i]!=0; i++);
	i--;
	for(; 0<=i; i--)
		printf("%c",characters_in_id[i]);

	printf("\n");
}

void free_token_if_necesary(Token e, HashMap h){
	if(e == 0) return;
	else if(e->id != IDENTIFIER)
		free_token(e);
	else if(get(h,e->lexeme)!=e)
		free_token(e);
}


void doIntegrationTest() {

	HashMap symbol_table = create_map((free_entry_function) &free_token_entry,
									  (equals_function) &token_entry_equals);
	LexicalAnalyzer analyzer = new_LexicalAnalyzer("../resources/concurrentSum.go", symbol_table);

	Token t = 0;
	do{
		free_token_if_necesary(t, symbol_table);
		t = get_next_lexical_component(analyzer);

		printf("id: %d --- ",t->id);

		if(t->id == END_OF_FILE) printf("END_OF_FILE\n");
		else if(t->id == NEW_LINE) printf("NEW_LINE\n");
		else if(t->lexeme == 0) print_string_from_lexical_id(t->id);
		else printf("%s\n",t->lexeme);

	}while(t->id != END_OF_FILE);
	free_token_if_necesary(t, symbol_table);
	print_map(symbol_table);
	close_lexical_analyzer(analyzer);
	delete_map(symbol_table);

}
