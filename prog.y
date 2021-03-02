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
    

    void insert_symbol(char* id, char* type, char* value){
        if(stackPtr == -1){
            return;
        }
        int indx = symTBIndex[stackPtr];
        strcpy(ST[indx][stackPtr].id, id);
        strcpy(ST[indx][stackPtr].type, type);
        strcpy(ST[indx][stackPtr].value, value);
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
            printf("%s\t%s\t\t%s",ST[i][stackPtr].id, ST[i][stackPtr].type, ST[i][stackPtr].value);
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
    short L_BOOL;
    long L_INT;
    double L_FP;
    char L_STR[1024];
    

    int i_val;
    float f_val;
    char* string;
};


%start				Program


%token  <T_ID>				T_IDENTIFIER

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
%type <L_STR>  Literal
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
        TY_INT      { strcpy($$, "int");}
    |   TY_FP       { strcpy($$, "float32"); }
    |   TY_STR      { strcpy($$, "str");}
    |   TY_BOOL     { strcpy($$, "bool");}
    ;


Literal:
        L_FLOAT     { float_flag = 1; sprintf($$, "%f", $1);}
    |   L_BOOLEAN   { bool_flag = 1; sprintf($$, "%d", $1);}
    |   L_INTEGER   { int_flag = 1; sprintf($$, " %d", $1);}
    |   L_STRING   { str_flag = 1; strcpy($$,$1);}
    ;


Expression:
        '(' Expression ')'          { $$ = ($$);}
    |   Expression '+' Expression   { $$ = $1 + $3;}
    |   Expression '-' Expression   { $$ = $1 - $3;}
    |   Expression '*' Expression   { $$ = $1 * $3;}
    |   Expression '/' Expression   { $$ = $1 / $3;}
    |   Expression '%' Expression   { if(int_flag) {$$ = (int)$1 % (int)$3;};}
    |   RelExpression               { $$ = $1;}
    |   Literal                     { if(int_flag || float_flag || bool_flag){ $$ = atof($1);}}
    |   T_IDENTIFIER                { ;/* search in sym table value of id and set $$ to it */;}
    ;

RelExpression:
        Expression '<' Expression           { $$ = ($1 < $3);}
    |   Expression '>' Expression           { $$ = ($1 > $3);}
    |   Expression OP_LEQ Expression        { $$ = ($1 <= $3);}
    |   Expression OP_GEQ Expression        { $$ = ($1 >= $3);}
    |   Expression OP_EQ Expression         { $$ = ($1 == $3);}
    |   Expression OP_NEQ Expression        { $$ = ($1 != $3);}
    |   RelExpression OP_OR RelExpression   { $$ = $1 || $3;}
    |   RelExpression OP_AND RelExpression  { $$ = $1 && $3;}
    |   '!' Expression                      { if($2 != 0){ $$ = 0;} else { $$ = 1;};}
    ;                    


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
