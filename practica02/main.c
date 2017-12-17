#include <stdio.h>
#include "IntegrationTest.h"
/*
 * # Responsibilities:
 * 1. For now it only runs the test, so it's easy to compile and make the correction
 */


extern char * yytext;
extern FILE * yyin;
extern int yylineno;

int main(){
	doIntegrationTest();
	return 0;
}


