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
%token                          KW_PRINT

%token				OP_AND 
%token				OP_OR 
%token				OP_EQ 
%token				OP_NEQ 
%token				OP_GEQ 
%token				OP_LEQ 
%token				OP_ARRAY_DECL 


%%

Program:
        PackageDecl ImportDeclList GlobalStmtList;
        

PackageDecl:
        KW_PACKAGE EntryPoint;


EntryPoint:
        T_IDENTIFIER;


ImportDeclList:
        ImportDeclList ImportDecl
    |	%empty;


ImportDecl:
        KW_IMPORT ModuleName;


ModuleName:
        L_STRING;


GlobalStmtList:
        GlobalStmtList  Statement
    |   %empty;


Statement:
        VarDecl
    |   Expression
    |   RelExpression
    |   PrintStmt
    |   AssignmentStmt
    |   FunctionDecl
    |   ReturnStmt
    |   IfStmt
    |   ForStmt
    |   FunctionCallStmt;


VarDecl:
        KW_VAR T_IDENTIFIER Type '=' Expression
    |   KW_VAR T_IDENTIFIER Type;


Type:
        TY_INT
    |   TY_FP
    |   TY_STR
    |   TY_BOOL;


Literal:
        L_FLOAT
    |   L_BOOLEAN
    |   L_INTEGER
    |   L_STRING;


Expression:
        '(' Expression ')' 
    |   Expression '+' Expression
    |   Expression '-' Expression
    |   Expression '*' Expression
    |   Expression '/' Expression
    |   Expression '%' Expression
    |   RelExpression
    |   Literal
    |   T_IDENTIFIER;


RelExpression:
        Expression '<' Expression
    |   Expression '>' Expression
    |   Expression OP_LEQ Expression
    |   Expression OP_GEQ Expression
    |   Expression OP_EQ Expression
    |   Expression OP_NEQ Expression
    |   RelExpression OP_OR RelExpression
    |   RelExpression OP_AND RelExpression
    |   '!' Expression;


PrintStmt:
        KW_PRINT '(' L_STRING ')'
    |   KW_PRINT '(' Expression ')';


AssignmentStmt:
        T_IDENTIFIER '=' Expression;


BlockStmt:
        '{' BlockStmtList '}'
    |   '{' '}';


BlockStmtList:
        BlockStmtList Statement
    |   Statement;


FunctionDecl:
        KW_FUNC T_IDENTIFIER '(' Parameters ')' Type BlockStmt;


Parameters:
        ParameterList
    |   Parameter;


ParameterList:
        ParameterList ',' Parameter
    |   %empty;


Parameter:
        ParamIdList Type;


ParamIdList:
        ParamIdList ',' T_IDENTIFIER
    |   T_IDENTIFIER;


ReturnStmt:
        KW_RETURN Expression
    |   KW_RETURN;


IfStmt:
        KW_IF '(' RelExpression ')' BlockStmt OptionalElse;


OptionalElse:
        KW_ELSE BlockStmt
    |   KW_ELSE IfStmt
    |   %empty;


ForStmt:
        KW_FOR VarDecl ';' RelExpression ';' Statement BlockStmt;


FunctionCallStmt:
        T_IDENTIFIER '(' Arguments ')';


Arguments:
        ArgumentList
    |   Argument;


ArgumentList:
        ArgumentList ',' Expression
    |   %empty;


Argument:
        Expression;

%%


void yyerror(char const* error) {
    fprintf(stderr, "%s: token %d on line %d\n", error, yychar, yylineno);
}

int main() {
    yyparse();

    return 0;
}
