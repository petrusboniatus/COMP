%{
#include <stdio.h>
#include "SymbolTable.h"
SymbolTable shared_st;
extern char * get_err_message(CALCULATOR_ERROR error_code);

//Bison + flex includes
extern int yylex();
extern int yyparse();
extern FILE *yyin;
void yyerror(const char *s);

// Functions to put multiple arguments and custom errors
void init_list();
void add_arg( double arg);
double argv [127]; //Maximum arguments in C
int argn;
CALCULATOR_ERROR custom_error = NO_ERROR;
%}

%union {
	int ival;
	double fval;
	SymbolTableEntry ptr;
}

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> INT
%token <fval> FLOAT
%token <ptr> IDENTIFIER

%type  <fval>  exp

%left '-' '+'
%left '*' '/'
%precedence NEG

%% 
input:
  %empty
| input line
;


line:
'\n'
| exp '\n'                            {
                                        if(custom_error == NO_ERROR) { LOG_RESULT("%g\n", $1); }
                                        else { yyerror(""); yyerrok;}
                                      }
| asig '\n'                           { /*Logged in asig command*/ }
| error '\n'                          { yyerrok;}
;

asig:
  IDENTIFIER '=' exp                {
                                     if(custom_error == NO_ERROR)
                                         custom_error = st_can_i_put(shared_st, $1->name);

                                     if(custom_error == NO_ERROR) {
                                         $1->value.flt = $3;
                                         LOG_RESULT("%s = %g\n", $1->name, $3);
                                     } else {
                                         LOG_ERROR(custom_error);
                                         custom_error = NO_ERROR;
                                     }
                                    }
;

exp:
INT                               { $$ = $1; }
| FLOAT                           { $$ = $1; }
| IDENTIFIER '(' bodyfunc ')'     {
                                      custom_error = st_can_i_call(shared_st, $1, argv, argn);
                                      if(custom_error == NO_ERROR){
                                          $$ = st_call_func($1->value.fn, argv, argn);
                                      }
                                  }
| IDENTIFIER                      { $$ = $1->value.flt; }
| exp '+' exp                     { $$ = $1 + $3; }
| exp '-' exp                     { $$ = $1 - $3; }
| exp '*' exp                     { $$ = $1 * $3; }
| exp '/' exp                     {
                                      if($3 == 0) {
                                          custom_error = DIVISION_BY_0;
                                      } else {
                                          $$ = $1 / $3;
                                      }
                                  }
| '-' exp  %prec NEG              { $$ = -$2; }
| '(' exp ')'                     { $$ = $2; }

;

bodyfunc:
  %empty
| exp                             { init_list(); add_arg($1); }
| bodyfunc ',' exp                { add_arg($3); }
;

%%

void init_list() {
	argn=0;
}
void add_arg( double arg) {
	argv[argn] = arg;
	argn++;
}


int main(int argc, char** argv) {
	// open a file handle to a particular file:
	if(argc > 2){
		printf("./interprete [ruta_al_archivo]\n");
		return -1;
	}

    if (argc == 2){
        FILE *myfile = fopen(argv[1], "r");
        if (!myfile) {
            printf("I can't open %s\n", argv[1]);
            return -1;
        }
        yyin = myfile;
    }

	shared_st = st_init();
	yyparse();

	st_free(shared_st);
	return 0;
}

void yyerror(const char *s) {
	if (custom_error == NO_ERROR)
		custom_error = UNRECOGNIZED_SYNTAX;
	LOG_ERROR(custom_error);
	custom_error = NO_ERROR;
}
