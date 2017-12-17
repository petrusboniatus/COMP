#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "Logger.h"
#include "HashMap.h"


typedef double (*math_function)();
typedef struct {
	char *name;
	int argn;
	math_function call;
} CallableFunction;

typedef HashMap SymbolTable;


typedef enum {
	VARIABLE = 3,
	FUNCTION = 4,
} ST_DATA_TYPE;
typedef union {
	double flt;
	CallableFunction fn;
} DataValue;
typedef struct SymbolTableEntryData {
	char *name;
	DataValue value;
	int is_const;
	ST_DATA_TYPE type;
} SymbolTableEntryData;

typedef SymbolTableEntryData *SymbolTableEntry;

SymbolTable st_init();

CALCULATOR_ERROR st_can_i_put(SymbolTable self, char *name);

void st_put_if_not_exist(SymbolTable self, char *name, DataValue value);

SymbolTableEntry st_get(SymbolTable self, char *name);

void st_free(SymbolTable self);

double st_call_func(CallableFunction f, double *argv, int argn);

CALCULATOR_ERROR st_can_i_call(SymbolTable self, SymbolTableEntry f, double *argv, int argn);

SymbolTableEntry st_get_or_create(SymbolTable self, char *name);
