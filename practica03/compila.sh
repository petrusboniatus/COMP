#!/usr/bin/env bash
flex lexerTested.l
bison syntax.y -d
gcc -Wall -lm HashMap.c HashMap.h SymbolTable.c Logger.h Logger.c SymbolTable.h lex.yy.c syntax.tab.c -o interprete
