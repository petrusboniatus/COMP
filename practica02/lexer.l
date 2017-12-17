%{
#include <stdio.h>
#include "goDefinitions.h"
%}

%option   yylineno

LETTER          [a-zA-Z_]
DECIMAL_DIGIT   [0-9]
OCTAL_DIGIT     [0-7]
HEX_DIGIT       [0-9A-Fa-f]
EXPONENT        [Ee][+-]?[0-9]+
INTEGER         [1-9]{DECIMAL_DIGIT}*|{OCTAL_DIGIT}+|"0x"{HEX_DIGIT}+
FLOATING        {DECIMAL_DIGIT}*"."{DECIMAL_DIGIT}+{EXPONENT}?|{DECIMAL_DIGIT}+"."{EXPONENT}?|{DECIMAL_DIGIT}+{EXPONENT}
IMAGINARY       {FLOATING}"i"|{INTEGER}"i"

%s stringWaiting
%s commentWaiting
%x error
%%

"("       {return OPEN_PARENTHESIS;}
")"       {return CLOSE_PARENTHESIS;}
"["       {return OPEN_BRACKETS;}
"]"       {return CLOSE_BRACKETS;}
"{"       {return OPEN_CURLY_BRACKETS;}
"}"       {return CLOSE_CURLY_BRACKETS;}
","       {return COMMA;}
";"       {return SEMICOLON;}
"."       {return POINT;}

":"       {return COLON;}

"+"      {return SUM_HASH;}
"-"      {return DIFFERENCE;}
"*"      {return PRODUCT;}
"/"      {return QUOTIENT;}
"%"      {return REMAINDER;}
"&"      {return BITWISE_AND;}
"|"      {return BITWISE_OR;}
"^"      {return BITWISE_XOR;}
"<<"     {return LEFT_SHIFT;}
">>"     {return RIGHT_SHIFT;}
"&^"     {return BIT_CLEAR;}
"="      {return ASSIGNMENT;}
":="     {return SHORT_ASSIGNMENT;}
"+="     {return PLUS_ASSIGNMENT;}
"-="     {return SUBTRACT_ASSIGNMENT;}
"*="     {return MULTIPLICATION_ASSIGNMENT;}
"/="     {return DIVISION_ASSIGNMENT;}
"%="     {return MODULUS_ASSIGNMENT;}
"&="     {return BITWISE_AND_ASSIGNMENT;}
"|="     {return BITWISE_OR_ASSIGNMENT;}
"^="     {return BITWISE_XOR_ASSIGNMENT;}
"<<="    {return LEFT_SHIFT_ASSIGNMENT;}
">>="    {return RIGHT_SHIFT_ASSIGNMENT;}
"&^="    {return BIT_CLEAR_ASSIGNMENT;}
"<-"     {return CHANEL;}
"..."    {return MULTIPLE_ARGUMENTS;}
"++"     {return SELF_INC;}
"--"     {return SELF_DEC;}
"=="     {return EQUAL;}
"<"      {return LESS;}
">_"     {return GREATER;}
"<="     {return LESS_OR_EQUAL;}
">="     {return GREATER_OR_EQUAL;}
"!="     {return NOT_EQUAL;}
"!"      {return NOT;}
"&&"     {return CONDITIONAL_AND;}
"||"     {return CONDITIONAL_OR;}


{INTEGER}                             {return INTEGER;}
{FLOATING}                            {return FLOAT;}
{IMAGINARY}                           {return IMAGINARY;}
{DECIMAL_DIGIT}+[Ee][^+0-9]           {return MALFORMED_NUMBER;}

\"                                              {yymore();/*add a character to the buffer*/BEGIN(stringWaiting);}
<stringWaiting><<EOF>>                          {BEGIN(INITIAL);return STRING;}
<stringWaiting>(\\.|[^\\"])*\"                  {BEGIN(INITIAL);return STRING;}

\/\/[^\n]*\n                                    {/*ignore normal comments*/}

\/\*                                            {BEGIN(commentWaiting);}
<commentWaiting><<EOF>>                         {return UNFINISHED_STRING;}
<commentWaiting>([^*]|(\*+([^*\/])))*\*+\/      {BEGIN(INITIAL);/*Escape multiline comment*/}


break|default|func|interface|select|case|defer|go|map|struct|chan|else|goto|package|switch|const|fallthrough|if|range|type|continue|for|import|return|var  {return KEY_WORD;}


[[:blank:]]                           {/*ignore spaces and tabs*/}

{LETTER}({LETTER}|{DECIMAL_DIGIT})*    {return IDENTIFIER;}

[\n]+                               {return NEW_LINE;}

.                             {BEGIN(error); yymore();/*Generic error starting*/}
<error>([^[:blank:]])         {yymore(); /*go to the next whitespace */}
<error>.                      {BEGIN(INITIAL); return NEVER_A_COMPONENT;}


%%

int yywrap(void){return 1;}
