%{
    #include <stdio.h>
    #include <errno.h>
    #include <stdlib.h>
    #include <string.h>

    #include "y.tab.h"
%}

%option yylineno
/*No support yet for ++, -- += etc */
/* Characters */
alpha                           [a-zA-Z_]
digit                           [0-9]
statement_terminator            {newline}|{semicolon}
newline                         \n
semicolon                       ;
whitespace                      [ \t]
char                            .

/* Comments */
comment_valid                   {comment_single_line}|{comment_block}
comment_single_line             "//".*
comment_block                   "/*"[^*]*"*"+([^*/][^*]*"*"+)*"/"
comment_invalid                 "/*"[^("*/")]*

/* Keywords */
keyword_package                 package
keyword_import                  import
keyword_var                     var
keyword_func                    func
keyword_return                  return
keyword_if                      if
keyword_else                    else
keyword_for                     for
keyword_print                   "fmt.Print"|"fmt.Println"

/* Operators */
operator_logical_and            "&&"
operator_logical_or             "||"
operator_equality               "=="
operator_neg_equality           "!="
operator_leq                    "<="
operator_geq                    ">="
operator_array_decl             "[]"
operator_char                   {operator_numeric}|{operator_bracket}|{operator_other}
operator_numeric                "+"|"-"|"*"|"/"|"%"|"!"|"<"|">"
operator_bracket                "["|"]"|"{"|"}"|"("|")"
operator_other                  "."|","|"="

/* Types */
type_int                        int
type_float32                    float32
type_string                     string
type_bool                       bool

/* Identifier */
identifier                      {alpha}({alpha}|{digit}){0,31}
identifier_lengthy              {alpha}({alpha}|{digit}){32,}

/* Literals */
bool_literal                    (true)|(false)
int_literal                     {digit}+
float32_literal                 {digit}+"."{digit}+
string_literal                  {string_single_quotes}|{string_double_quotes}
string_single_quotes            \'[^']*\'
string_double_quotes            \"[^"]*\"
string_invalid                  {string_invalid_single}|{string_invalid_double}
string_invalid_single           \'[^']*
string_invalid_double           \"[^"]*


%%


{whitespace}                    ;

{comment_valid}                 ;
{comment_invalid}               {
                                    printf("Preprocesser Error: Unterminated Comment\n");
                                    exit(EXIT_FAILURE);
                                }

{statement_terminator}          return T_STMT_TERMINATOR;
                                

{operator_char}                 return yytext[0];
{operator_logical_and}          return OP_AND;
{operator_logical_or}           return OP_OR;
{operator_equality}             return OP_EQ;
{operator_neg_equality}         return OP_NEQ;
{operator_leq}                  return OP_LEQ;
{operator_geq}                  return OP_GEQ;
{operator_array_decl}           return OP_ARRAY_DECL;

{keyword_package}               return KW_PACKAGE;
{keyword_import}                return KW_IMPORT;
{keyword_var}                   return KW_VAR;
{keyword_func}                  return KW_FUNC;
{keyword_return}                return KW_RETURN;
{keyword_if}                    return KW_IF;
{keyword_else}                  return KW_ELSE;
{keyword_for}                   return KW_FOR;
{keyword_print}                 return KW_PRINT;

{type_int}                      return TY_INT;
{type_bool}                     return TY_BOOL;
{type_float32}                  return TY_FP;
{type_string}                   return TY_STR;

{bool_literal}                  {
                                    yylval.L_BOOL = (strcmp(yytext, "true") == 0) ? 1 : 0;
                                    return L_BOOLEAN;
                                }
{int_literal}                   {
                                    yylval.L_INT = atoi(yytext);
                                    return L_INTEGER;
                                }
{float32_literal}               {
                                    yylval.L_FP = atof(yytext);
                                    return L_FLOAT;
                                }
{string_literal}                {
                                    strcpy(yylval.T_ID, yytext);
                                    return L_STRING; 
                                }
{string_invalid}                {
                                    printf("Lexer Error: unterminated string on line %d\n", yylineno);
                                    exit(EXIT_FAILURE);
                                }

{identifier}                    {
                                    strcpy(yylval.T_ID, yytext);
                                    return T_IDENTIFIER;
                                }
{identifier_lengthy}            {
                                    printf("Lexer Error: identifier on line %d exceeds length limit 31\n", yylineno);
                                    exit(EXIT_FAILURE);
                                }

.                               {
                                    printf("Lexer Error: Unable to tokenise '%s' on line %d\n", yytext, yylineno);
                                    exit(EXIT_FAILURE);
                                }


%%

