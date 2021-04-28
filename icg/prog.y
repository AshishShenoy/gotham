%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <string.h>
    #include <stdbool.h>

    extern int yylex();
    extern void yyerror();

    extern int yylineno;
    extern char* yytext;
    extern int yychar;
    extern FILE* yyout;

    FILE *fp;

    int temp_ctr = 1;
    int branch_ctr = 1;
    int end_ctr = 1;
    int loop_ctr = 1;

    bool is_end_of_if_stmt = true;
%}


%union {
    
    char T_ID[32];
    char TYPE[10];
    char T_OP;
    char L_BOOL[1];
    char L_INT[32];
    char L_FP[64];
    char L_STR[1024];
};


%start                  Program



%token <T_ID>           T_IDENTIFIER
%token                  T_NEWLINE
%token                  T_SEMICOLON


%token <L_BOOL>         L_BOOLEAN
%token <L_INT>          L_INTEGER
%token <L_FP>           L_FLOAT
%token <L_STR>          L_STRING

%token <L_STR>          TY_BOOL
%token <L_STR>          TY_INT
%token <L_STR>          TY_FP
%token <L_STR>          TY_STR

%token                  KW_PACKAGE
%token                  KW_IMPORT
%token                  KW_VAR
%token                  KW_FUNC
%token                  KW_RETURN
%token                  KW_IF
%token                  KW_ELSE
%token                  KW_FOR
%token                  KW_PRINT

%token                  OP_AND 
%token                  OP_OR 
%token                  OP_EQ 
%token                  OP_NEQ 
%token                  OP_GEQ 
%token                  OP_LEQ 
%token                  OP_ARRAY_DECL 


%type <L_STR>           VarDecl
%type <L_STR>           Statement
%type <L_STR>           BlockStmt
%type <L_STR>           BlockStmtList
%type <L_STR>           Expression
%type <L_STR>           SumExpression
%type <L_STR>           MulExpression
%type <L_STR>           SimpleExpression
%type <L_STR>           AndExpression
%type <L_STR>           UnaryExpression
%type <L_STR>           UnaryRelExpression
%type <L_STR>           RelExpression
%type <L_STR>           Factor
%type <L_STR>           Literal



%left                   '+' '-'
%left                   '*' '/'



%%

Program:
        PackageDecl ImportDeclList GlobalStmtList;
        

PackageDecl:
        OptionalStmtTermList KW_PACKAGE T_IDENTIFIER StatementTermList
    |   %empty;


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
        VarDecl                                     { strcpy($$, $1); }
    |   Expression                                  { strcpy($$, $1); }
    |   PrintStmt
    |   FunctionDecl
    |   ReturnStmt
    |   IfStmt
    |   ForStmt;


VarDecl:
        KW_VAR T_IDENTIFIER Type '=' Expression     { fprintf(fp, "%s = %s\n", $2, $5); }
    |   KW_VAR T_IDENTIFIER Type
    ;


Type:
        TY_INT
    |   TY_FP
    |   TY_STR
    |   TY_BOOL
    ;


Expression:
        '(' Expression ')'
    |   AssignmentExpression
    |   SimpleExpression                            { strcpy($$, $1); }
    ;


AssignmentExpression:
        T_IDENTIFIER '=' Expression                 { fprintf(fp, "%s = %s\n", $1, $3); }
    ;


SimpleExpression:
        SimpleExpression OP_OR AndExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "t%d = %s || %s\n", temp_ctr++, $1, $3);
        }
    |   AndExpression                               { strcpy($$, $1); }
    ;


AndExpression:
        AndExpression OP_AND UnaryRelExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "t%d = %s && %s\n", temp_ctr++, $1, $3);
        }
    |   UnaryRelExpression                          { strcpy($$, $1); }
    ;


UnaryRelExpression:
        '!' UnaryRelExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "t%d = ! %s\n", temp_ctr++, $2);
        }
    |   RelExpression                               { strcpy($$, $1); }
    ;


RelExpression:
        SumExpression OP_EQ SumExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "t%d = %s == %s\n", temp_ctr++, $1, $3);
        }
    |   SumExpression OP_NEQ SumExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "t%d = %s != %s\n", temp_ctr++, $1, $3);
        }
    |   SumExpression '<' SumExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "t%d = %s < %s\n", temp_ctr++, $1, $3);
        }
    |   SumExpression OP_LEQ SumExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "t%d = %s <= %s\n", temp_ctr++, $1, $3);
        }
    |   SumExpression '>' SumExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "t%d = %s > %s\n", temp_ctr++, $1, $3);
        }
    |   SumExpression OP_GEQ SumExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "t%d = %s >= %s\n", temp_ctr++, $1, $3);
        }
    |   SumExpression                               { strcpy($$, $1); }
    ;



SumExpression:
        SumExpression '+' MulExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "t%d = %s + %s\n", temp_ctr++, $1, $3);
        }
    |   SumExpression '-' MulExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "t%d = %s - %s\n", temp_ctr++, $1, $3);
        }
    |   MulExpression                               { strcpy($$, $1); }
    ;


MulExpression:
        MulExpression '*' UnaryExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "t%d = %s * %s\n", temp_ctr++, $1, $3);
        }
    |   MulExpression '/' UnaryExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "t%d = %s / %s\n", temp_ctr++, $1, $3);
        }
    |   MulExpression '%' UnaryExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "t%d = %s %% %s\n", temp_ctr++, $1, $3);
        }
    |   UnaryExpression                             { strcpy($$, $1); }
    ;


UnaryExpression:
        '+' UnaryExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "t%d = + %s\n", temp_ctr++, $2);
        }
    |   '-' UnaryExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "t%d = - %s\n", temp_ctr++, $2);
        }
    |   Factor                                      { strcpy($$, $1); }
    ;


Factor:
        T_IDENTIFIER
    |   FunctionCallStmt
    |   Literal                                     { strcpy($$, $1); }
    ;


FunctionCallStmt:
        T_IDENTIFIER '(' ArgumentList ')';


ArgumentList:
        ArgumentList ',' Expression
    |   Expression
    |   %empty;


Literal:
        L_FLOAT                                     { strcpy($$, $1); }
    |   L_BOOLEAN                                   { strcpy($$, $1); }
    |   L_INTEGER                                   { strcpy($$, $1); }
    |   L_STRING                                    { strcpy($$, $1); }
    ;
    

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
        '{' OptionalStmtTermList BlockStmtList OptionalStmtTermList '}' { strcpy($$, $3); }
    ;


OptionalStmtTermList:
        OptionalStmtTermList StatementTerminator
    |   %empty;


BlockStmtList:
        BlockStmtList Statement StatementTermList   { strcpy($$, $2); }
    |   %empty;


ReturnStmt:
        KW_RETURN Expression
    |   KW_RETURN;


IfStmt:
        KW_IF '(' Expression ')' OptionalNewlines {
            fprintf(fp, "IF FALSE %s GOTO B%d\n", $3, branch_ctr);
        } BlockStmt {
            fprintf(fp, "GOTO END%d\n", end_ctr);
            fprintf(fp, "B%d:\n", branch_ctr++);
        } OptionalElse {
            if (is_end_of_if_stmt) {
                fprintf(fp, "END%d:\n", end_ctr++);
            }
        };
    ;


OptionalElse:
        KW_ELSE OptionalNewlines BlockStmt
    |   KW_ELSE {
            is_end_of_if_stmt = false;
        } IfStmt {
            is_end_of_if_stmt = true;
        }
    |   %empty
    ;

ForStmt:
        KW_FOR VarDecl T_SEMICOLON {
            fprintf(fp, "COND%d:\n", loop_ctr);
        } Expression {
            fprintf(fp, "IF FALSE %s GOTO END%d\n", $5, end_ctr);
            fprintf(fp, "GOTO BLOCK%d\n", loop_ctr);
            fprintf(fp, "INC%d:\n", loop_ctr);
        } T_SEMICOLON Expression { 
            fprintf(fp, "GOTO COND%d\n", loop_ctr);
        } OptionalNewlines { fprintf(fp, "BLOCK%d:\n", loop_ctr); } BlockStmt {
            fprintf(fp, "GOTO INC%d\n", loop_ctr);            
            fprintf(fp, "END%d\n", end_ctr++);
            loop_ctr++;
        };


%%


void yyerror(char const* error) {
    fprintf(stderr, "%s: token %s on line %d\n", error, yytext, yylineno);
}

int main() {
    fp = fopen("icg.txt", "w");

    yyparse();

    return 0;
}
