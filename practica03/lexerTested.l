%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymbolTable.h"
#include "syntax.tab.h"
extern SymbolTable shared_st;

%}
%option noyywrap
/* to avoid warning: ‘yyunput’ defined but not used */
%option nounput
/* to avoid warning: ‘input’ defined but not used */
%option noinput


LETTER          [a-zA-Z_]
DECIMAL_DIGIT   [0-9]
INTEGER         {DECIMAL_DIGIT}*
EXPONENT        [Ee][+-]?[0-9]+
FLOATING        {DECIMAL_DIGIT}*"."{DECIMAL_DIGIT}+{EXPONENT}?|{DECIMAL_DIGIT}+"."{EXPONENT}?|{DECIMAL_DIGIT}+{EXPONENT}

%x error
%%
[\n]            { return '\n'; }
<<EOF>>         { static int once = 0; return once++ ? 0 : '\n'; /*Append new line to the output*/}
exit            { return 0; }

"("             { return '('; }
")"             { return ')'; }
"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"="             { return '='; }
","             { return ','; }


{INTEGER}                              { yylval.ival = atoi(yytext);return INT; }
{FLOATING}                             { yylval.fval = strtod(yytext, NULL); return FLOAT;}
{LETTER}({LETTER}|{DECIMAL_DIGIT})*    {
                                         yylval.ptr = st_get_or_create(shared_st,yytext);
                                         return IDENTIFIER;
                                       }
[[:blank:]]                            { /*ignore blanks*/ }

.                                      { BEGIN(error); yymore(); /*Generic error starting*/ }
<error>(\n)                            { yymore(); /*go to the next whitespace */ }
<error>.                               { BEGIN(INITIAL);  LOG_ERROR(UNRECOGNIZED_SYMBOL); }

%%

