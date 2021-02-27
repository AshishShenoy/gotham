%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <string.h>

    extern int yylex();
    extern void yyerror();

    extern int yylineno;
    extern char* yytext;
    extern int yychar;
%}


%union {
    char T_ID[32];
    char T_OP;
    short L_BOOL;
    long L_INT;
    double L_FP;
    char L_STR[1024];
};


%start				Program


%token				T_IDENTIFIER

%token				L_BOOLEAN
%token				L_INTEGER
%token				L_FLOAT
%token				L_STRING

%token				TY_BOOL
%token				TY_INT
%token				TY_FP
%token				TY_STR

%token				KW_PACKAGE
%token				KW_IMPORT
%token				KW_VAR
%token				KW_FUNC
%token				KW_RETURN
%token				KW_IF
%token				KW_ELSE
%token				KW_FOR

%token				OP_AND 
%token				OP_OR 
%token				OP_EQ 
%token				OP_NEQ 
%token				OP_GEQ 
%token				OP_LEQ 
%token				OP_ARRAY_DECL 


%%

Program:
                    PackageDecl ImportDeclList;

        
PackageDecl:
                    KW_PACKAGE EntryPoint;


EntryPoint:
                    T_IDENTIFIER;
                    

ImportDeclList:
                    ImportDecl ImportDeclList
                |	ImportDecl;


ImportDecl:
                    KW_IMPORT ModuleName;


ModuleName:
                    L_STRING;



%%


void yyerror(char const* error) {
    fprintf(stderr, "%s: token %d on line %d\n", error, yychar, yylineno);
}

int main() {
    yyparse();

    return 0;
}
