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

    struct ST{
        char id[32];
        char type[10];
        char value[20];
        //int index;
    };
    typedef struct ST symTB;

    #define MAX_SYMBOL_NUM 100
    #define STACK_SIZE 10
    symTB ST[MAX_SYMBOL_NUM][STACK_SIZE];
    int stackPtr = 0;


    int symTBIndex[STACK_SIZE];
    

    void insert_symbol(char* id, char* type){
        if(stackPtr == -1){
            return;
        }
        int indx = symTBIndex[stackPtr];
        strcpy(ST[indx][stackPtr].id, id);
        strcpy(ST[indx][stackPtr].type, type);
        //strcpy(ST[indx][stackPtr].value, value);
        symTBIndex[stackPtr] = indx + 1;
        return;
    }

    
    void disp_symtbl(){
        if(stackPtr == -1){
            return;
        }
        int indx = symTBIndex[stackPtr];
        printf("%s\t%s\t\t%s\n","Name", "Type", "Value");
        for(int i = 0; i < indx; i++){
            printf("%s\t%s\t\t\n",ST[i][stackPtr].id, ST[i][stackPtr].type);
        }
        printf("\n\n");
        return;
    }

    void push_block(){
        stackPtr++;
        if(stackPtr == STACK_SIZE){
            stackPtr = STACK_SIZE - 1;
            printf("STACK FULL");
        }
        return;
    }

    // pop stack and display sym tbl
    void pop_block(){
        if(stackPtr != -1){
            disp_symtbl();
            symTBIndex[stackPtr] = 0;
            stackPtr--;
            return;
        }
        printf("STACK EMPTY");
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


%start				Program



%token  <T_ID>				T_IDENTIFIER
%token                          T_NEWLINE
%token                          T_SEMICOLON


%token	<L_BOOL>			L_BOOLEAN
%token	<L_INT>			L_INTEGER
%token	<L_FP>			L_FLOAT
%token	<L_STR>			L_STRING

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


%type <TYPE>  Type
%type <L_BOOL> RelExpression
%type <L_FP>   Expression
%type <L_FP>   SumExpression
%type <L_FP>   MulExpression
%type <L_STR>   UnaryExpression
%type <L_FP>   AssignmentExpression
%type <L_FP>   SimpleExpression
%type <L_BOOL> AndExpression
%type <L_BOOL> UnaryRelExpression
%type <L_STR>  Literal
%type <L_STR>   Factor


%left                           '+' '-'
%left                           '*' '/'



%%

Program:
        PackageDecl ImportDeclList GlobalStmtList       {pop_block();};
        

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
        KW_VAR T_IDENTIFIER Type '=' Expression       { insert_symbol($2, $3);}
    |   KW_VAR T_IDENTIFIER Type                     { insert_symbol($2, $3);}
    ;


Type:
        TY_INT      { strcpy($$, "int");}
    |   TY_FP       { strcpy($$, "float32"); }
    |   TY_STR      { strcpy($$, "str");}
    |   TY_BOOL     { strcpy($$, "bool");}
    ;


Expression:
        '(' Expression ')'      { strcpy($$, ($$));}
    |   AssignmentExpression    { strcpy($$, $1);}
    |   SimpleExpression        { strcpy($$, $1);}
    ;


AssignmentExpression:
        T_IDENTIFIER '=' Expression    {strcpy($$, $3);}
    ;


SimpleExpression:
        SimpleExpression OP_OR AndExpression        { ;}
    |   AndExpression                               { strcpy($$, $1);}
    ;


AndExpression:
        AndExpression OP_AND UnaryRelExpression     { sprintf($$, "%f", atof($1) && atof($3));}
    |   UnaryRelExpression                          { strcpy($$, $1);}
    ;


UnaryRelExpression:
        '!' UnaryRelExpression                      { sprintf($$, "%f", !atof($2));}
    |   RelExpression                               { strcpy($$, $1);}
    ;


RelExpression:
        SumExpression OP_EQ SumExpression           { strcpy($$, strcmp($1,$3) == 0? "1" : "0" );}
    |   SumExpression OP_NEQ SumExpression          { strcpy($$, strcmp($1,$3) == 0? "0" : "1" );}
    |   SumExpression '<' SumExpression             { strcpy($$, atof($1) < atof($3) ? "1" : "0" );}
    |   SumExpression OP_LEQ SumExpression          { strcpy($$, atof($1) <= atof($3) ? "1" : "0" );}
    |   SumExpression '>' SumExpression             { strcpy($$, atof($1) > atof($3) ? "1" : "0" );}
    |   SumExpression OP_GEQ SumExpression          { strcpy($$, atof($1) >= atof($3) ? "1" : "0" );}
    |   SumExpression                               { strcpy($$, $1);}
    ;



SumExpression:
        SumExpression '+' MulExpression        { sprintf($$, "%f", atof($1) + atof($3));}
    |   SumExpression '-' MulExpression        { sprintf($$, "%f", atof($1) - atof($3));}
    |   MulExpression;


MulExpression:
        MulExpression '*' UnaryExpression      { if (float_flag){
                                                    sprintf($$, "%f", (atof($1) * atof($3)));
                                                } else if(int_flag){
                                                    sprintf($$, "%d", (atoi($1) * atoi($3)));
                                                }

        }
    |   MulExpression '/' UnaryExpression      { if((float_flag || int_flag) && $3 != 0) {sprintf($$, "%f", atof($1) / atof($3));} else {yyerror("Invaild division");}}
    |   MulExpression '%' UnaryExpression      { if(int_flag && $3 > 0) { sprintf($$, "%d", atoi($1) % atoi($3));};}
    |   UnaryExpression                        { strcpy($$, $1);}
    ;


UnaryExpression:
        '+' UnaryExpression                    { strcpy($$, $2);}
    |   '-' UnaryExpression                    { sprintf($$, "%f",- atof($2));}
    |   Factor                                 { strcpy($$,$1);}
    ;


Factor:
        T_IDENTIFIER                           {/*search sym tbl */;}
    |   FunctionCallStmt                       { /* I have no clue */;}
    |   Literal                                { strcpy($$,$1);}


FunctionCallStmt:
        T_IDENTIFIER '(' ArgumentList ')';


ArgumentList:
        ArgumentList ',' Expression
    |   Expression
    |   %empty;


Literal:
        L_FLOAT     {   float_flag = 1; 
                        int_flag = 0; bool_flag = 0; str_flag = 0;
                        sprintf($$, "%f", $1);}
    |   L_BOOLEAN   {   bool_flag = 1; 
                        int_flag =0; float_flag = 0; str_flag = 0;
                        sprintf($$, "%d", $1);}
    |   L_INTEGER   {   int_flag = 1; 
                        bool_flag = 0; float_flag = 0; str_flag = 0;
                        sprintf($$, " %d", $1);}
    |   L_STRING   {    str_flag = 1;
                        int_flag = 0; float_flag = 0; bool_flag = 0;
                        strcpy($$,$1);}
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
        '{' { push_block(); }OptionalStmtTermList BlockStmtList OptionalStmtTermList '}' {pop_block();};


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
