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


    #define MAX_SYMBOLS 100
    #define STACK_SIZE 10
    #define STACK_EMPTY_PTR -1
 

    // Each entry in the symbol table.
    struct SymbolTableEntry {
        int lineno;
        char identifier[32];
        char type[10];
        char storage[10];
    };

    // The set of all scopes in the program and their associated symbol tables.
    // The scopes are ordered as a stack.
    struct ProgramTable {
        struct SymbolTableEntry table[STACK_SIZE][MAX_SYMBOLS];
        int scope_stack[STACK_SIZE];
        int stack_ptr;
        char scope_names[STACK_SIZE][32];
    };

    struct ProgramTable PT;
    
    // Stores the value of the last matched function name.
    char function_name[32];


    // Returns true if the symbol is found on the current scope.
    int lookup_symbol_table(char* identifier) {
        int index = PT.scope_stack[PT.stack_ptr];

        for (int i = 0; i < index; i++) {
            if (strcmp(identifier, PT.table[PT.stack_ptr][i].identifier) == 0) {
                return true;
            }
        }
        return false;
    }

    // Inserts a symbol into the symbol table of the current scope if 
    // it is not redeclared.
    void insert_symbol(char* identifier, char* type, int lineno) {
        if (PT.stack_ptr == STACK_EMPTY_PTR) {
            fprintf(stderr, "\033[0;31m");
            fprintf(stderr, "Identifier %s on line %d is in invalid scope\n", identifier, lineno);
            fprintf(stderr, "\033[0m");
            exit(EXIT_FAILURE);
            return;
        }

        if (lookup_symbol_table(identifier)) {
            fprintf(stderr, "\033[0;31m");
            fprintf(stderr, "Identifier %s on line %d already declared in scope %s\n", identifier, lineno, PT.scope_names[PT.stack_ptr]);
            fprintf(stderr, "\033[0m");
            return;
        }

        char storage[10] = "0";
        if (strcmp(type, "int") == 0) {
            strcpy(storage, "4");
        } else if (strcmp(type, "float32") == 0) {
            strcpy(storage, "4");
        } else if (strcmp(type, "bool") == 0) {
            strcpy(storage, "1");
        } else if (strcmp(type, "string") == 0) {
            // Cannot determine size of string at compile time.
            strcpy(storage, "NA");
        }

        int index = PT.scope_stack[PT.stack_ptr];

        PT.table[PT.stack_ptr][index].lineno = lineno;
        strcpy(PT.table[PT.stack_ptr][index].identifier, identifier);
        strcpy(PT.table[PT.stack_ptr][index].type, type);
        strcpy(PT.table[PT.stack_ptr][index].storage, storage);

        PT.scope_stack[PT.stack_ptr] = index + 1;
    }

    
    // Print all the symbols of the current scope.
    void display_symbol_table() {
        if (PT.stack_ptr == STACK_EMPTY_PTR) {
            return;
        }

        int index = PT.scope_stack[PT.stack_ptr];
        
        if (index == 0) {
            return;
        }
        
        fprintf(yyout, "SYMBOL TABLE FOR SCOPE <%s>\n", PT.scope_names[PT.stack_ptr]);
        fprintf(yyout, "%s\t%s\t%s\t\t%s\n", "Line No.", "Name", "Type", "Storage");
        
        for (int i = 0; i < index; i++) {
            fprintf(yyout, "%d\t\t%s\t%s\t\t%s\n",
                PT.table[PT.stack_ptr][i].lineno,
                PT.table[PT.stack_ptr][i].identifier, 
                PT.table[PT.stack_ptr][i].type,
                PT.table[PT.stack_ptr][i].storage
            );
        }
        fprintf(yyout, "\n\n");
    }

    // Adds a symbol table to the stack.
    void push_block() {
        PT.stack_ptr++;

        if (strcmp(function_name, "") == 0) {
            strcpy(PT.scope_names[PT.stack_ptr], "unnamed_block");
        } else {
            strcpy(PT.scope_names[PT.stack_ptr], function_name);
            strcpy(function_name, "");
        }

        if (PT.stack_ptr == STACK_SIZE){
            PT.stack_ptr = STACK_SIZE - 1;
            fprintf(stderr, "\033[0;31m");
            fprintf(stderr, "Scope Stack Overflow\n");
            fprintf(stderr, "\033[0m");
            exit(EXIT_FAILURE);
        }
    }

    // Removes a symbol table from the stack, and displays it.
    void pop_block() {
        if (PT.stack_ptr != STACK_EMPTY_PTR) {
            display_symbol_table();
            PT.scope_stack[PT.stack_ptr] = 0;
            (PT.stack_ptr)--;
        }
        else {
            fprintf(stderr, "\033[0;31m");
            fprintf(stderr, "Scope Stack Underflow\n");
            fprintf(stderr, "\033[0m");
            exit(EXIT_FAILURE);
        }
    }

    int float_flag = 0;
    int int_flag = 0;
    int bool_flag = 0;
    int str_flag = 0;


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

%token                  TY_BOOL
%token                  TY_INT
%token                  TY_FP
%token                  TY_STR

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


%type <TYPE>            Type
%type <L_BOOL>          RelExpression
%type <L_FP>            Expression
%type <L_FP>            SumExpression
%type <L_FP>            MulExpression
%type <L_STR>           UnaryExpression
%type <L_FP>            AssignmentExpression
%type <L_FP>            SimpleExpression
%type <L_BOOL>          AndExpression
%type <L_BOOL>          UnaryRelExpression
%type <L_STR>           Literal
%type <L_STR>           Factor


%left                   '+' '-'
%left                   '*' '/'



%%

Program:
        PackageDecl ImportDeclList GlobalStmtList       { pop_block(); };
        

PackageDecl:
        OptionalStmtTermList KW_PACKAGE T_IDENTIFIER StatementTermList;


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
        KW_VAR T_IDENTIFIER Type { insert_symbol($2, $3, yylineno); } '=' Expression
    |   KW_VAR T_IDENTIFIER Type { insert_symbol($2, $3, yylineno - 1); }
    ;


Type:
        TY_INT                      { strcpy($$, "int"); }
    |   TY_FP                       { strcpy($$, "float32"); }
    |   TY_STR                      { strcpy($$, "string"); }
    |   TY_BOOL                     { strcpy($$, "bool"); }
    ;


Expression:
        '(' Expression ')'          { strcpy($$, ($$)); }
    |   AssignmentExpression        { strcpy($$, $1); }
    |   SimpleExpression            { strcpy($$, $1); }
    ;


AssignmentExpression:
        T_IDENTIFIER '=' Expression                     { strcpy($$, $3); }
    ;


SimpleExpression:
        SimpleExpression OP_OR AndExpression
    |   AndExpression                                   { strcpy($$, $1);}
    ;


AndExpression:
        AndExpression OP_AND UnaryRelExpression         { sprintf($$, "%f", atof($1) && atof($3)); }
    |   UnaryRelExpression                              { strcpy($$, $1); }
    ;


UnaryRelExpression:
        '!' UnaryRelExpression                      { sprintf($$, "%f", !atof($2)); }
    |   RelExpression                               { strcpy($$, $1); }
    ;


RelExpression:
        SumExpression OP_EQ SumExpression           { strcpy($$, strcmp($1,$3) == 0? "1" : "0" ); }
    |   SumExpression OP_NEQ SumExpression          { strcpy($$, strcmp($1,$3) == 0? "0" : "1" ); }
    |   SumExpression '<' SumExpression             { strcpy($$, atof($1) < atof($3) ? "1" : "0" ); }
    |   SumExpression OP_LEQ SumExpression          { strcpy($$, atof($1) <= atof($3) ? "1" : "0" ); }
    |   SumExpression '>' SumExpression             { strcpy($$, atof($1) > atof($3) ? "1" : "0" ); }
    |   SumExpression OP_GEQ SumExpression          { strcpy($$, atof($1) >= atof($3) ? "1" : "0" ); }
    |   SumExpression                               { strcpy($$, $1); }
    ;



SumExpression:
        SumExpression '+' MulExpression             { sprintf($$, "%f", atof($1) + atof($3)); }
    |   SumExpression '-' MulExpression             { sprintf($$, "%f", atof($1) - atof($3)); }
    |   MulExpression;


MulExpression:
        MulExpression '*' UnaryExpression           {
                                                        if (float_flag) {
                                                            sprintf($$, "%f", (atof($1) * atof($3)));
                                                        } else if(int_flag) {
                                                            sprintf($$, "%d", (atoi($1) * atoi($3)));
                                                        }
                                                    }

    |   MulExpression '/' UnaryExpression           {
                                                        if ((float_flag || int_flag) && $3 != 0) {
                                                            sprintf($$, "%f", atof($1) / atof($3));
                                                        } else {
                                                            yyerror("Invaild division");
                                                        }
                                                    }
    |   MulExpression '%' UnaryExpression           {
                                                        if (int_flag && $3 > 0) {
                                                            sprintf($$, "%d", atoi($1) % atoi($3));
                                                        }
                                                    }
    |   UnaryExpression                             { strcpy($$, $1); }
    ;


UnaryExpression:
        '+' UnaryExpression                         { strcpy($$, $2); }
    |   '-' UnaryExpression                         { sprintf($$, "%f",- atof($2)); }
    |   Factor                                      { strcpy($$,$1); }
    ;


Factor:
        T_IDENTIFIER                                { /*search sym tbl */; }
    |   FunctionCallStmt                            { /* I have no clue */; }
    |   Literal                                     { strcpy($$,$1); }
    ;


FunctionCallStmt:
        T_IDENTIFIER '(' ArgumentList ')';


ArgumentList:
        ArgumentList ',' Expression
    |   Expression
    |   %empty;


Literal:
        L_FLOAT                 {
                                    float_flag = 1; 
                                    int_flag = 0; bool_flag = 0; str_flag = 0;
                                    sprintf($$, "%f", $1);
                                }
    |   L_BOOLEAN               {
                                    bool_flag = 1; 
                                    int_flag =0; float_flag = 0; str_flag = 0;
                                    sprintf($$, "%d", $1);
                                }
    |   L_INTEGER               {
                                    int_flag = 1; 
                                    bool_flag = 0; float_flag = 0; str_flag = 0;
                                    sprintf($$, " %d", $1);
                                }
    |   L_STRING                {
                                    str_flag = 1;
                                    int_flag = 0; float_flag = 0; bool_flag = 0;
                                    strcpy($$,$1);
                                }
    ;
    

FunctionDecl:
        KW_FUNC T_IDENTIFIER 
            {
                strcpy(function_name, $2);
                push_block();
            }
        '(' ParameterList ')' Type OptionalNewlines BlockStmt { pop_block(); };


OptionalNewlines:
        OptionalNewlines T_NEWLINE
    |   %empty;


ParameterList:
        ParameterList ',' Parameter
    |   Parameter
    |   %empty;


Parameter:
        T_IDENTIFIER Type             { insert_symbol($1, $2, yylineno); };


PrintStmt:
        KW_PRINT '(' Expression ')';


BlockStmt:
        '{' OptionalStmtTermList BlockStmtList OptionalStmtTermList  '}' ;


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
        KW_IF '(' Expression ')' OptionalNewlines { push_block(); } BlockStmt { pop_block(); } OptionalElse;


OptionalElse:
        KW_ELSE OptionalNewlines { push_block(); } BlockStmt { pop_block(); }
    |   KW_ELSE IfStmt
    |   %empty;


ForStmt:
        KW_FOR VarDecl T_SEMICOLON Expression T_SEMICOLON Expression OptionalNewlines { push_block(); } BlockStmt { pop_block(); };


%%


void yyerror(char const* error) {
    fprintf(stderr, "%s: token %s on line %d\n", error, yytext, yylineno);
}

int main() {
    PT.stack_ptr = 0;
    strcpy(PT.scope_names[PT.stack_ptr], "global");

    yyout = fopen("symbol_table.txt", "w");

    yyparse();

    return 0;
}
