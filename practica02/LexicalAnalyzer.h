//
// Created by someone on 11/10/17.
//

#ifndef UNTITLED_LEXICALANALIZER_H
#define UNTITLED_LEXICALANALIZER_H

#endif //UNTITLED_LEXICALANALIZER_H

#include "goDefinitions.h"
#include "HashMap.h"

/*
 * Opaque type that represent the object
 */
typedef struct LexicalAnalyzerData * LexicalAnalyzer;

/*
 * @param filename - name of the file that it will be read
 * @param symbol_table - initialized symbol table
 *
 * @returns new Initialized Lexical analyzer to the file
 */
LexicalAnalyzer new_LexicalAnalyzer(char * filename, HashMap symbol_table);

/*
 * @param self - Lexical analyzer object
 *
 * @returns the next lexical component
 */
Token get_next_lexical_component(LexicalAnalyzer self);

/*
 * @param Lexical analyzer object
 *
 * Liberate the memory of the object
 */
void close_lexical_analyzer(LexicalAnalyzer self);
