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

    int if_stack_pointer = 1;
    int if_max_depth = 1;

    int for_stack_pointer = 1;
    int for_max_depth = 1;

    int inst_ctr = 1;
    int temp_ctr = 1;
    int branch_ctr = 1;
    int if_end_ctr = 1;
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
        KW_VAR T_IDENTIFIER Type '=' Expression     { fprintf(fp, "[%04d] ASSIGN\t%s\t\t%s\n", inst_ctr++, $5, $2); }
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
        T_IDENTIFIER '=' Expression                 { fprintf(fp, "[%04d] ASSIGN\t%s\t\t%s\n", inst_ctr++, $3, $1); }
    ;


SimpleExpression:
        SimpleExpression OP_OR AndExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "[%04d] OR\t%s\t%s\tt%d\n", inst_ctr++, $1, $3, temp_ctr++);
        }
    |   AndExpression                               { strcpy($$, $1); }
    ;


AndExpression:
        AndExpression OP_AND UnaryRelExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "[%04d] AND\t%s\t%s\tt%d\n", inst_ctr++, $1, $3, temp_ctr++);
        }
    |   UnaryRelExpression                          { strcpy($$, $1); }
    ;


UnaryRelExpression:
        '!' UnaryRelExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "[%04d] NOT\t%s\t\tt%d\n", inst_ctr++, $2, temp_ctr++);
        }
    |   RelExpression                               { strcpy($$, $1); }
    ;


RelExpression:
        SumExpression OP_EQ SumExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "[%04d] EQ\t%s\t%s\tt%d\n", inst_ctr++, $1, $3, temp_ctr++);
        }
    |   SumExpression OP_NEQ SumExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "[%04d] NEQ\t%s\t%s\tt%d\n", inst_ctr++, $1, $3, temp_ctr++);
        }
    |   SumExpression '<' SumExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "[%04d] LT\t%s\t%s\tt%d\n", inst_ctr++, $1, $3, temp_ctr++);
        }
    |   SumExpression OP_LEQ SumExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "[%04d] LEQ\t%s\t%s\tt%d\n", inst_ctr++, $1, $3, temp_ctr++);
        }
    |   SumExpression '>' SumExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "[%04d] GT\t%s\t%s\tt%d\n", inst_ctr++, $1, $3, temp_ctr++);
        }
    |   SumExpression OP_GEQ SumExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "[%04d] GEQ\t%s\t%s\tt%d\n", inst_ctr++, $1, $3, temp_ctr++);
        }
    |   SumExpression                               { strcpy($$, $1); }
    ;



SumExpression:
        SumExpression '+' MulExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "[%04d] ADD\t%s\t%s\tt%d\n", inst_ctr++, $1, $3, temp_ctr++);
        }
    |   SumExpression '-' MulExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "[%04d] SUB\t%s\t%s\tt%d\n", inst_ctr++, $1, $3, temp_ctr++);
        }
    |   MulExpression                               { strcpy($$, $1); }
    ;


MulExpression:
        MulExpression '*' UnaryExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "[%04d] MUL\t%s\t%s\tt%d\n", inst_ctr++, $1, $3, temp_ctr++);
        }
    |   MulExpression '/' UnaryExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "[%04d] DIV\t%s\t%s\tt%d\n", inst_ctr++, $1, $3, temp_ctr++);
        }
    |   MulExpression '%' UnaryExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "[%04d] MOD\t%s\t%s\tt%d\n", inst_ctr++, $1, $3, temp_ctr++);
        }
    |   UnaryExpression                             { strcpy($$, $1); }
    ;


UnaryExpression:
        '+' UnaryExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "[%04d] ASSIGN\t%s\t\tt%d\n", inst_ctr++, $2, temp_ctr++);
        }
    |   '-' UnaryExpression {
            sprintf($$, "t%d", temp_ctr);
            fprintf(fp, "[%04d] ASSIGN\t-%s\t\tt%d\n", inst_ctr++, $2, temp_ctr++);
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
        KW_PRINT '(' Expression ')' {
            fprintf(fp, "[%04d] PARAMS\t\t\t%s\n", inst_ctr++, $3);
            fprintf(fp, "[%04d] CALL\t\t\tPRINT\n", inst_ctr++);
        }
    ;


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
            fprintf(fp, "[%04d] BEQ\t%s\t0\tB%d\n", inst_ctr++, $3, branch_ctr++);
            if_stack_pointer++;
            if_max_depth++;
        } BlockStmt {
            if_stack_pointer--;
            fprintf(fp, "[%04d] GOTO\t\t\tENDIF%d\n", inst_ctr++,  if_end_ctr);
            fprintf(fp, "B%d:\n", branch_ctr + (if_stack_pointer - if_max_depth));
        } OptionalElse {
            if (is_end_of_if_stmt) {
                fprintf(fp, "ENDIF%d:\n", if_end_ctr++);
                if (if_stack_pointer == 1) {
                    if_max_depth = 1;
                }
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
            fprintf(fp, "[%04d] BEQ\t%s\t0\tENDFOR%d\n", inst_ctr++, $5, loop_ctr);
            fprintf(fp, "[%04d] GOTO\t\t\tBLOCK%d\n", inst_ctr++,  loop_ctr);
            fprintf(fp, "INC%d:\n", loop_ctr);
        } T_SEMICOLON Expression { 
            fprintf(fp, "[%04d] GOTO\t\t\tCOND%d\n", inst_ctr++,  loop_ctr);
        } OptionalNewlines {
            fprintf(fp, "BLOCK%d:\n", loop_ctr++);
            for_stack_pointer++;
            for_max_depth++;
        } BlockStmt {
            for_stack_pointer--;
            fprintf(fp, "[%04d] GOTO\t\t\tINC%d\n", inst_ctr++,  loop_ctr + (for_stack_pointer - for_max_depth));
            fprintf(fp, "ENDFOR%d:\n", loop_ctr + (for_stack_pointer - for_max_depth));

            if (for_stack_pointer == 1) {
                for_max_depth = 1;
            }
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
