#include "SymbolTable.h"
#include <stdio.h>


double st_sqrt(double a) {
	if (a < 0) {
		LOG_WARNING("Negative sqrt: It seem like someone is trying to go to some banned plain...");
	}
	return sqrt(a);
}

const CallableFunction shared_functions[] =
		{
				{"atan", 1, atan},
				{"cos",  1, cos},
				{"exp",  1, exp},
				{"ln",   1, log},
				{"sin",  1, sin},
				{"sqrt", 1, st_sqrt},
				{"pow",  2, pow},
				{"log",  1, log},
				{0,      0, 0},
		};

typedef struct {
	char *const_name;
	double const_val;
} UniversalConst;

const UniversalConst consts[] =
		{
				{"pi",         3.14159265359},
				{"e",          2.71828182846},
				{"tau",        6.2831853071},
				{"LightSpeed", 1e9},
				{0,            0}
		};


void free_token_entry(char *key, SymbolTableEntry e) {
	if (!e->is_const) free(key);
	free(e);
}

int token_entry_equals(SymbolTableEntry e1, SymbolTableEntry e2) {
	return strcmp(e1->name, e2->name) == 0;
}

SymbolTable st_init() {
	SymbolTable new_st = create_map((free_entry_function) &free_token_entry,
									(equals_function) &token_entry_equals);

	for (int i = 0; shared_functions[i].name != 0; i++) {
		SymbolTableEntry function_entry = (SymbolTableEntry) malloc(sizeof(SymbolTableEntryData));
		function_entry->name = (char *) malloc(sizeof(char) * strlen(shared_functions[i].name));
		function_entry->is_const = 1;
		strcpy(function_entry->name, shared_functions[i].name);
		function_entry->value.fn = shared_functions[i];
		function_entry->type = FUNCTION;
		put(new_st, function_entry->name, function_entry);
	}

	for (int i = 0; consts[i].const_name; i++) {
		SymbolTableEntry function_entry = (SymbolTableEntry) malloc(sizeof(SymbolTableEntryData));
		function_entry->name = consts[i].const_name;
		function_entry->is_const = 1;
		function_entry->value.flt = consts[i].const_val;
		function_entry->type = VARIABLE;
		put(new_st, function_entry->name, function_entry);
	}

	return new_st;
}

void st_put_if_not_exist(SymbolTable self, char *name, DataValue value) {

	if (contains(self, name)) return;

	SymbolTableEntry new_entry = (SymbolTableEntry) malloc(sizeof(SymbolTableEntryData));
	new_entry->name = (char *) malloc(sizeof(char) * strlen(name));

	strcpy(new_entry->name, name);
	new_entry->value = value;
	new_entry->is_const = 0;
	new_entry->type = VARIABLE;
	put(self, new_entry->name, new_entry);
}

SymbolTableEntry st_get_or_create(SymbolTable self, char *name) {
	DataValue b;
	b.flt = 0;
	st_put_if_not_exist(self, name, b);
	SymbolTableEntry e = st_get(self, name);
	return e;
}


double st_call_func(CallableFunction f, double *argv, int argn) {

	switch (argn) { //May work with assembly for the N case?
		case 0:
			return f.call();
		case 1:
			return f.call(argv[0]);
		case 2:
			return f.call(argv[0], argv[1]);
		case 3:
			return f.call(argv[0], argv[1], argv[2]);
		case 4:
			return f.call(argv[0], argv[1], argv[2], argv[3]);
		case 5:
			return f.call(argv[0], argv[1], argv[2], argv[3], argv[4]);
		case 6:
			return f.call(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
		case 7:
			return f.call(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
		case 9:
			return f.call(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
		default:
		LOG_WARNING("Too many arguments for a function definition, returning 0");
			return 0;
	}
}

CALCULATOR_ERROR st_can_i_call(SymbolTable self, SymbolTableEntry f, double *argv, int argn) {
	if (f->type != FUNCTION)
		return NOT_A_FUNCTION;
	if (f->value.fn.argn < argn)
		return TOO_MANY_ARGUMENTS;
	if (f->value.fn.argn > argn)
		return TOO_FEW_ARGUMENTS;
	return NO_ERROR;
}

CALCULATOR_ERROR st_can_i_put(SymbolTable self, char *name) {
	SymbolTableEntry entry = st_get(self, name);
	if (entry->type != VARIABLE)
		return NOT_A_VARIABLE;
	if (entry->is_const)
		return CANT_MODIFY_CONST;
	else
		return NO_ERROR;
}

SymbolTableEntry st_get(SymbolTable self, char *name) {
	SymbolTableEntry getted = get(self, name);
	return getted;
}

void st_free(SymbolTable self) {
	delete_map(self);
}
