%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <errno.h>
	#include <string.h>

	extern int yylex();
	extern void yyerror();
%}


%union {
	char *T_ID;
	char T_OP;
	long L_INT;
	double L_FP;
	char *L_STR;
};


%start							program


%token							T_IDENTIFIER

%token							L_INTEGER
%token							L_FLOAT
%token							L_STRING

%token							KW_PACKAGE
%token							KW_IMPORT
%token							KW_VAR
%token							KW_FUNC
%token							KW_RETURN
%token							KW_IF
%token							KW_ELSE
%token							KW_FOR

%token							OP_AND 
%token							OP_OR 
%token							OP_EQ 
%token							OP_NEQ 
%token							OP_GEQ 
%token							OP_LEQ 
%token							OP_ARRAY_DECL 


%%

program: ;

%%


void yyerror(char const* error) {
	fprintf(stderr, "%s\n", error);
}

int main() {
	yyparse();

	return 0;
}
