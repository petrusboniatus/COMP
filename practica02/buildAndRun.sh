#!/bin/bash

rm -rf compiled
mkdir compiled 
flex --header-file=lex.yy.h lexer.l
cd compiled
gcc ../*.c -o compilador
./compilador


