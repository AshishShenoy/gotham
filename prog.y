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
%token              KW_PRINT

%token				OP_AND 
%token				OP_OR 
%token				OP_EQ 
%token				OP_NEQ 
%token				OP_GEQ 
%token				OP_LEQ 
%token              OP_L
%token              OP_G
%token				OP_ARRAY_DECL 


%%

Program:    Program stat | ;

        
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

stat: PackageDecl ImportDeclList
      | declaration stat
      | expression stat
      | relation stat
      | printstat stat
      | assignstat stat
      | funcstat stat
      | returnStmt stat
      | ifstat stat
      | forStmt stat
      | {};

declaration: KW_VAR T_IDENTIFIER type '=' expression|
             KW_VAR T_IDENTIFIER type;

type:   TY_INT|
        TY_FP|
        TY_STR|
        TY_BOOL;

const: L_FLOAT
       | L_BOOLEAN
       | L_INTEGER
       | L_STRING;


expression: '(' expression ')' 
            | expression '+' expression
            | expression '-' expression
            | expression '*' expression
            | expression '/' expression
            | expression '%' expression
            | const
            | T_IDENTIFIER;
/* extend support for or and and */
relation: expression OP_L expression
          | expression OP_G expression
          | expression OP_LEQ expression
          | expression OP_GEQ expression
          | expression OP_EQ expression
          | expression OP_NEQ expression;

printstat: KW_PRINT '(' L_STRING ')'
           | KW_PRINT '(' expression ')';


assignstat: T_IDENTIFIER '=' expression;

block: '{' stat '}' | {};

funcstat: KW_FUNC T_IDENTIFIER '(' params ')' type block;

params: paramList | {};

paramList: paramList ',' param | param ;

param: paramId type;

paramId: paramId ',' T_IDENTIFIER | T_IDENTIFIER;

returnStmt: KW_RETURN expression | KW_RETURN;

ifstat: KW_IF '(' relation ')' block OptionalElse;

OptionalElse: KW_ELSE block | KW_ELSE ifstat | {};

forStmt: KW_FOR stat ';' relation ';' stat block;


%%


void yyerror(char const* error) {
    fprintf(stderr, "%s: token %d on line %d\n", error, yychar, yylineno);
}

int main() {
    yyparse();

    return 0;
}
