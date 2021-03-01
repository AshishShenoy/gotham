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


%token                          T_NEWLINE
%token                          T_SEMICOLON

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


%left                           '+' '-'
%left                           '*' '/'


%%

Program:
        PackageDecl ImportDeclList GlobalStmtList;
        

PackageDecl:
        KW_PACKAGE T_IDENTIFIER StatementTermList;


StatementTermList:
        StatementTermList StatementTerminator
    |   StatementTerminator;


StatementTerminator:
        T_SEMICOLON
    |   T_NEWLINE;


ImportDeclList:
        ImportDeclList ImportDecl
    |	%empty;


ImportDecl:
        KW_IMPORT L_STRING StatementTermList;


GlobalStmtList:
        GlobalStmtList Statement StatementTermList
    |   %empty;


Statement:
        VarDecl
    |   Expression
    |   PrintStmt
    |   FunctionDecl
    |   ReturnStmt
    |   IfStmt
    |   ForStmt;


VarDecl:
        KW_VAR T_IDENTIFIER Type '=' Expression
    |   KW_VAR T_IDENTIFIER Type;


Type:
        TY_INT
    |   TY_FP
    |   TY_STR
    |   TY_BOOL;


Expression:
        '(' Expression ')'
    |   AssignmentExpression
    |   SimpleExpression;


AssignmentExpression:
        T_IDENTIFIER '=' Expression;


SimpleExpression:
        SimpleExpression OP_OR AndExpression
    |   AndExpression;


AndExpression:
        AndExpression OP_AND UnaryRelExpression
    |   UnaryRelExpression;


UnaryRelExpression:
        '!' UnaryRelExpression
    |   RelExpression;


RelExpression:
        SumExpression OP_EQ SumExpression
    |   SumExpression OP_NEQ SumExpression
    |   SumExpression '<' SumExpression
    |   SumExpression OP_LEQ SumExpression
    |   SumExpression '>' SumExpression
    |   SumExpression OP_GEQ SumExpression
    |   SumExpression;


SumExpression:
        SumExpression '+' MulExpression
    |   SumExpression '-' MulExpression
    |   MulExpression;


MulExpression:
        MulExpression '*' UnaryExpression
    |   MulExpression '/' UnaryExpression
    |   MulExpression '%' UnaryExpression
    |   UnaryExpression;


UnaryExpression:
        '+' UnaryExpression
    |   '-' UnaryExpression
    |   Factor;


Factor:
        T_IDENTIFIER
    |   FunctionCallStmt
    |   Literal


FunctionCallStmt:
        T_IDENTIFIER '(' ArgumentList ')';


ArgumentList:
        ArgumentList ',' Expression
    |   Expression
    |   %empty;


Literal:
        L_FLOAT
    |   L_BOOLEAN
    |   L_INTEGER
    |   L_STRING;


FunctionDecl:
        KW_FUNC T_IDENTIFIER '(' ParameterList ')' Type OptionalNewlines BlockStmt;


OptionalNewlines:
        OptionalNewlines T_NEWLINE
    |   %empty;


ParameterList:
        ParameterList ',' Parameter
    |   Parameter
    |   %empty;


Parameter:
        T_IDENTIFIER Type;


PrintStmt:
        KW_PRINT '(' Expression ')';


BlockStmt:
        '{' OptionalStmtTermList BlockStmtList OptionalStmtTermList '}';


OptionalStmtTermList:
        OptionalStmtTermList StatementTerminator
    |   %empty;


BlockStmtList:
        BlockStmtList Statement StatementTermList
    |   %empty;


ReturnStmt:
        KW_RETURN Expression
    |   KW_RETURN;


IfStmt:
        KW_IF '(' Expression ')' OptionalNewlines BlockStmt OptionalElse;


OptionalElse:
        KW_ELSE OptionalNewlines BlockStmt
    |   KW_ELSE IfStmt
    |   %empty;


ForStmt:
        KW_FOR VarDecl T_SEMICOLON Expression T_SEMICOLON Expression OptionalNewlines BlockStmt;


%%


void yyerror(char const* error) {
    fprintf(stderr, "%s: token %s on line %d\n", error, yytext, yylineno);
}

int main() {
    yyparse();

    return 0;
}
