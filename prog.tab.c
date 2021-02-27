/* A Bison parser, made by GNU Bison 3.7.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "prog.y"

#include "header.h"
#include <stdio.h>
#include <stdlib.h>
int TABLE_SIZE = 10009;
union NodeVal value;

int base = 1000;

typedef struct symbol_table {
    char name[31];
    char dtype[10];
    char type;
    char value[20];
    char scope[10];
    int hcode;
  }ST;
  
 ST hashTable[10009];

struct Stack {
   char s[25][25];
   int top;
};

typedef struct Stack stack;

stack stack_i = {.top = -1};
stack stack_v = {.top = -1};
stack stack_t = {.top = -1};
stack stack_scope = {.top = -1};


char result[20];
char Tflag[20];

int stfull(stack st,int size) {
	if (st.top >= size - 1)
		return 1;
	else
		return 0;
}

void push(stack *p_st,char *item) {
	p_st->top++;
	strcpy(p_st->s[p_st->top], item);
}

int stempty(stack st) {
	if (st.top == -1)
		return 1;
	else
		return 0;
}

char * pop(stack *p_st) {
	char *item;
	item = p_st->s[p_st->top];
	p_st->top--;
	return (item);
}

int hash1(char *token) {
				
	int hash = 0;
	for (int i = 0; token[i] != '\0'; i++) { 
		hash = ( 256 * hash + token[i] ) % 1000000009; 
	}
	hash = hash % TABLE_SIZE;
	return hash;

}

int check(char *token) {
				
	int index1 = hash1(token); 
	int i = 0;
	while ( i < TABLE_SIZE && strcmp(hashTable[( index1 + i ) % TABLE_SIZE].name, token) != 0 )
		i++;

	if ( i == TABLE_SIZE )
		return 1;
	else
		return index1 + i;

}


void insert(char type, char *token, char *dtype, char *value, char *scope) {

	if (check(token) != 1) {
		yyerror("variable is redeclared");
    	/*printf("Error: %s is redeclared..!\n", token);
    	exit(0);*/
    	return;
  	}
  	int index = hash1(token);

  	if (hashTable[index].hcode != -1) {

	    int i = 1;
		while (1) {
			int newIndex = (index + i) % TABLE_SIZE;

			if (hashTable[newIndex].hcode == -1) {

				strcpy(hashTable[newIndex].name, token);
				strcpy(hashTable[newIndex].dtype, dtype);
				strcpy(hashTable[newIndex].value, value);
				strcpy(hashTable[newIndex].scope, scope);
				hashTable[newIndex].type = type;
				hashTable[newIndex].hcode = 1;
				break;
			}
			i++;
		}
	}

	else {
		strcpy(hashTable[index].name, token);
		strcpy(hashTable[index].dtype, dtype);
		strcpy(hashTable[index].value, value);
		strcpy(hashTable[index].scope, scope);
		hashTable[index].type = type;
		hashTable[index].hcode = 1;
	}
}
char * search(char *token) {

	int index1 = hash1(token); 
	int i = 0;
	while ( i < TABLE_SIZE && strcmp(hashTable[( index1 + i ) % TABLE_SIZE].name, token)!=0)
		i++;
	if ( i == TABLE_SIZE ) {
		printf("Error: %s is not defined\n", token);
		exit(0);
	}
	else
		return hashTable[index1 + i].dtype;
}


void update(char *token, char *dtype, char *value) {
	int index = check(token);
	if ( index == 1 ) {
		printf("Error: %s is not defined\n", token);
		exit(0);
		return;
	}
	
	if (hashTable[index].type == 'c') {
		printf("Error: cannot assign to %s (declared const)", token);
		exit(0);
		return;
	}
	else {
		if (strcmp(hashTable[index].value, "NULL") != 0)
			strcpy(hashTable[index].value, value);
		if (strcmp(hashTable[index].dtype, "NULL") != 0)
			strcpy(hashTable[index].dtype, dtype);
	}
}

void disp_symtbl() {

	int base = 1000;
	printf("%s\t%s\t\t%s\t\t%s\t\t%s\n","Name", "Type","Data Type", "Value", "Scope");

	for(int i=0; i<TABLE_SIZE; i++) {
		if(hashTable[i].hcode != -1 )
			printf("%s\t%c\t\t%s\t\t\t%s\t\t%s\n",hashTable[i].name, hashTable[i].type, hashTable[i].dtype, hashTable[i].value, hashTable[i].scope);
		}

}





#line 251 "prog.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "prog.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_ID = 3,                       /* "identifier"  */
  YYSYMBOL_L_INT = 4,                      /* "integer literal"  */
  YYSYMBOL_L_FLOAT = 5,                    /* "float literal"  */
  YYSYMBOL_L_RUNE = 6,                     /* "rune literal"  */
  YYSYMBOL_L_STRING = 7,                   /* "string literal"  */
  YYSYMBOL_K_BREAK = 8,                    /* K_BREAK  */
  YYSYMBOL_K_DEFAULT = 9,                  /* K_DEFAULT  */
  YYSYMBOL_K_FUNC = 10,                    /* K_FUNC  */
  YYSYMBOL_K_INTERFACE = 11,               /* K_INTERFACE  */
  YYSYMBOL_K_SELECT = 12,                  /* K_SELECT  */
  YYSYMBOL_K_CASE = 13,                    /* K_CASE  */
  YYSYMBOL_K_DEFER = 14,                   /* K_DEFER  */
  YYSYMBOL_K_GO = 15,                      /* K_GO  */
  YYSYMBOL_K_MAP = 16,                     /* K_MAP  */
  YYSYMBOL_K_STRUCT = 17,                  /* K_STRUCT  */
  YYSYMBOL_K_CHAN = 18,                    /* K_CHAN  */
  YYSYMBOL_K_ELSE = 19,                    /* K_ELSE  */
  YYSYMBOL_K_GOTO = 20,                    /* K_GOTO  */
  YYSYMBOL_K_PACKAGE = 21,                 /* K_PACKAGE  */
  YYSYMBOL_K_SWITCH = 22,                  /* K_SWITCH  */
  YYSYMBOL_K_CONST = 23,                   /* K_CONST  */
  YYSYMBOL_K_FALLTHROUGH = 24,             /* K_FALLTHROUGH  */
  YYSYMBOL_K_IF = 25,                      /* K_IF  */
  YYSYMBOL_K_RANGE = 26,                   /* K_RANGE  */
  YYSYMBOL_K_TYPE = 27,                    /* K_TYPE  */
  YYSYMBOL_K_CONTINUE = 28,                /* K_CONTINUE  */
  YYSYMBOL_K_FOR = 29,                     /* K_FOR  */
  YYSYMBOL_K_IMPORT = 30,                  /* K_IMPORT  */
  YYSYMBOL_K_RETURN = 31,                  /* K_RETURN  */
  YYSYMBOL_K_VAR = 32,                     /* K_VAR  */
  YYSYMBOL_O_ADDEQ = 33,                   /* O_ADDEQ  */
  YYSYMBOL_O_ANDEQ = 34,                   /* O_ANDEQ  */
  YYSYMBOL_O_LAND = 35,                    /* O_LAND  */
  YYSYMBOL_O_EQ = 36,                      /* O_EQ  */
  YYSYMBOL_O_NEQ = 37,                     /* O_NEQ  */
  YYSYMBOL_O_SUBEQ = 38,                   /* O_SUBEQ  */
  YYSYMBOL_O_OREQ = 39,                    /* O_OREQ  */
  YYSYMBOL_O_LOR = 40,                     /* O_LOR  */
  YYSYMBOL_O_LT = 41,                      /* O_LT  */
  YYSYMBOL_O_LEQ = 42,                     /* O_LEQ  */
  YYSYMBOL_O_MULEQ = 43,                   /* O_MULEQ  */
  YYSYMBOL_O_XOREQ = 44,                   /* O_XOREQ  */
  YYSYMBOL_O_CHAN_DIR = 45,                /* O_CHAN_DIR  */
  YYSYMBOL_O_GT = 46,                      /* O_GT  */
  YYSYMBOL_O_GEQ = 47,                     /* O_GEQ  */
  YYSYMBOL_O_LSHIFT = 48,                  /* O_LSHIFT  */
  YYSYMBOL_O_DIVEQ = 49,                   /* O_DIVEQ  */
  YYSYMBOL_O_LSHIFTEQ = 50,                /* O_LSHIFTEQ  */
  YYSYMBOL_O_INC = 51,                     /* O_INC  */
  YYSYMBOL_O_ASSGN = 52,                   /* O_ASSGN  */
  YYSYMBOL_O_RSHIFT = 53,                  /* O_RSHIFT  */
  YYSYMBOL_O_MODEQ = 54,                   /* O_MODEQ  */
  YYSYMBOL_O_RSHIFTEQ = 55,                /* O_RSHIFTEQ  */
  YYSYMBOL_O_DEC = 56,                     /* O_DEC  */
  YYSYMBOL_O_ELLIPSES = 57,                /* O_ELLIPSES  */
  YYSYMBOL_O_AMPXOR = 58,                  /* O_AMPXOR  */
  YYSYMBOL_O_AMPXOREQ = 59,                /* O_AMPXOREQ  */
  YYSYMBOL_P_TYPE = 60,                    /* P_TYPE  */
  YYSYMBOL_P_CONST = 61,                   /* P_CONST  */
  YYSYMBOL_P_NIL = 62,                     /* P_NIL  */
  YYSYMBOL_P_FUNC = 63,                    /* P_FUNC  */
  YYSYMBOL_EMPTY = 64,                     /* EMPTY  */
  YYSYMBOL_NORMAL = 65,                    /* NORMAL  */
  YYSYMBOL_66_ = 66,                       /* '+'  */
  YYSYMBOL_67_ = 67,                       /* '-'  */
  YYSYMBOL_68_ = 68,                       /* '|'  */
  YYSYMBOL_69_ = 69,                       /* '^'  */
  YYSYMBOL_70_ = 70,                       /* '*'  */
  YYSYMBOL_71_ = 71,                       /* '/'  */
  YYSYMBOL_72_ = 72,                       /* '%'  */
  YYSYMBOL_73_ = 73,                       /* '&'  */
  YYSYMBOL_P_UNARY = 74,                   /* P_UNARY  */
  YYSYMBOL_NotPackage = 75,                /* NotPackage  */
  YYSYMBOL_NotParen = 76,                  /* NotParen  */
  YYSYMBOL_77_ = 77,                       /* '('  */
  YYSYMBOL_78_ = 78,                       /* ')'  */
  YYSYMBOL_PreferToRightParen = 79,        /* PreferToRightParen  */
  YYSYMBOL_80_ = 80,                       /* '.'  */
  YYSYMBOL_81_ = 81,                       /* ','  */
  YYSYMBOL_82_ = 82,                       /* '='  */
  YYSYMBOL_83_ = 83,                       /* '!'  */
  YYSYMBOL_84_ = 84,                       /* '['  */
  YYSYMBOL_85_ = 85,                       /* ']'  */
  YYSYMBOL_86_ = 86,                       /* '{'  */
  YYSYMBOL_87_ = 87,                       /* '}'  */
  YYSYMBOL_88_ = 88,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 89,                  /* $accept  */
  YYSYMBOL_SourceFile = 90,                /* SourceFile  */
  YYSYMBOL_PackageClause = 91,             /* PackageClause  */
  YYSYMBOL_PackageName = 92,               /* PackageName  */
  YYSYMBOL_ImportDecls = 93,               /* ImportDecls  */
  YYSYMBOL_ImportDecl = 94,                /* ImportDecl  */
  YYSYMBOL_ImportSpecList = 95,            /* ImportSpecList  */
  YYSYMBOL_ImportSpecList2 = 96,           /* ImportSpecList2  */
  YYSYMBOL_ImportSpec = 97,                /* ImportSpec  */
  YYSYMBOL_Type = 98,                      /* Type  */
  YYSYMBOL_TypeName = 99,                  /* TypeName  */
  YYSYMBOL_QualifiedID = 100,              /* QualifiedID  */
  YYSYMBOL_Signature = 101,                /* Signature  */
  YYSYMBOL_SignatureSuff = 102,            /* SignatureSuff  */
  YYSYMBOL_Result = 103,                   /* Result  */
  YYSYMBOL_Parameters = 104,               /* Parameters  */
  YYSYMBOL_ParameterList = 105,            /* ParameterList  */
  YYSYMBOL_ParameterList2 = 106,           /* ParameterList2  */
  YYSYMBOL_ParameterDecl = 107,            /* ParameterDecl  */
  YYSYMBOL_ParameterDeclPre = 108,         /* ParameterDeclPre  */
  YYSYMBOL_PIdentifierListSuff = 109,      /* PIdentifierListSuff  */
  YYSYMBOL_MethodName = 110,               /* MethodName  */
  YYSYMBOL_TopLevelDecls = 111,            /* TopLevelDecls  */
  YYSYMBOL_TopLevelDecl = 112,             /* TopLevelDecl  */
  YYSYMBOL_Declaration = 113,              /* Declaration  */
  YYSYMBOL_FunctionDecl = 114,             /* FunctionDecl  */
  YYSYMBOL_FunctionName = 115,             /* FunctionName  */
  YYSYMBOL_FunctionBody = 116,             /* FunctionBody  */
  YYSYMBOL_MethodDecl = 117,               /* MethodDecl  */
  YYSYMBOL_Receiver = 118,                 /* Receiver  */
  YYSYMBOL_ConstDecl = 119,                /* ConstDecl  */
  YYSYMBOL_ConstSpecs = 120,               /* ConstSpecs  */
  YYSYMBOL_ConstSpec = 121,                /* ConstSpec  */
  YYSYMBOL_CIdentifierListSuff = 122,      /* CIdentifierListSuff  */
  YYSYMBOL_CIdentifierListSuffPre = 123,   /* CIdentifierListSuffPre  */
  YYSYMBOL_TypeDecl = 124,                 /* TypeDecl  */
  YYSYMBOL_TypeSpecs = 125,                /* TypeSpecs  */
  YYSYMBOL_TypeSpecList = 126,             /* TypeSpecList  */
  YYSYMBOL_TypeSpec = 127,                 /* TypeSpec  */
  YYSYMBOL_AliasDecl = 128,                /* AliasDecl  */
  YYSYMBOL_TypeDef = 129,                  /* TypeDef  */
  YYSYMBOL_VarDecl = 130,                  /* VarDecl  */
  YYSYMBOL_VarSpecs = 131,                 /* VarSpecs  */
  YYSYMBOL_VarSpec = 132,                  /* VarSpec  */
  YYSYMBOL_VIdentifierListSuff = 133,      /* VIdentifierListSuff  */
  YYSYMBOL_VIdentifierListTypeSuff = 134,  /* VIdentifierListTypeSuff  */
  YYSYMBOL_IdentifierList = 135,           /* IdentifierList  */
  YYSYMBOL_ExprList = 136,                 /* ExprList  */
  YYSYMBOL_rel_op = 137,                   /* rel_op  */
  YYSYMBOL_add_op = 138,                   /* add_op  */
  YYSYMBOL_mul_op = 139,                   /* mul_op  */
  YYSYMBOL_unary_op = 140,                 /* unary_op  */
  YYSYMBOL_assign_op = 141,                /* assign_op  */
  YYSYMBOL_Expr = 142,                     /* Expr  */
  YYSYMBOL_UnaryExpr = 143,                /* UnaryExpr  */
  YYSYMBOL_PrimaryExpr = 144,              /* PrimaryExpr  */
  YYSYMBOL_Index = 145,                    /* Index  */
  YYSYMBOL_Arguments = 146,                /* Arguments  */
  YYSYMBOL_Args2 = 147,                    /* Args2  */
  YYSYMBOL_ArgsOp1 = 148,                  /* ArgsOp1  */
  YYSYMBOL_ArgsOp2 = 149,                  /* ArgsOp2  */
  YYSYMBOL_Operand = 150,                  /* Operand  */
  YYSYMBOL_Literal = 151,                  /* Literal  */
  YYSYMBOL_BasicLit = 152,                 /* BasicLit  */
  YYSYMBOL_FunctionLit = 153,              /* FunctionLit  */
  YYSYMBOL_OperandName = 154,              /* OperandName  */
  YYSYMBOL_Block = 155,                    /* Block  */
  YYSYMBOL_156_1 = 156,                    /* $@1  */
  YYSYMBOL_157_2 = 157,                    /* $@2  */
  YYSYMBOL_StatementList = 158,            /* StatementList  */
  YYSYMBOL_Statement = 159,                /* Statement  */
  YYSYMBOL_SimpleStmt = 160,               /* SimpleStmt  */
  YYSYMBOL_ExprStmt = 161,                 /* ExprStmt  */
  YYSYMBOL_IncDecStmt = 162,               /* IncDecStmt  */
  YYSYMBOL_Assignment = 163,               /* Assignment  */
  YYSYMBOL_ShortVarDecl = 164,             /* ShortVarDecl  */
  YYSYMBOL_ForStmt = 165,                  /* ForStmt  */
  YYSYMBOL_OptionalForClause = 166,        /* OptionalForClause  */
  YYSYMBOL_Condition = 167,                /* Condition  */
  YYSYMBOL_ForClause = 168,                /* ForClause  */
  YYSYMBOL_OptionalForClauseInit = 169,    /* OptionalForClauseInit  */
  YYSYMBOL_OptionalForClauseCondition = 170, /* OptionalForClauseCondition  */
  YYSYMBOL_OptionalForClausePost = 171,    /* OptionalForClausePost  */
  YYSYMBOL_InitStmt = 172,                 /* InitStmt  */
  YYSYMBOL_PostStmt = 173,                 /* PostStmt  */
  YYSYMBOL_RangeClause = 174,              /* RangeClause  */
  YYSYMBOL_OptionalForRangePre = 175,      /* OptionalForRangePre  */
  YYSYMBOL_IfStmt = 176,                   /* IfStmt  */
  YYSYMBOL_OptionalElse = 177,             /* OptionalElse  */
  YYSYMBOL_ReturnStmt = 178                /* ReturnStmt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   689

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  89
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  90
/* YYNRULES -- Number of rules.  */
#define YYNRULES  195
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  271

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    83,     2,     2,     2,    72,    73,     2,
      77,    78,    70,    66,    81,    67,    80,    71,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    88,
       2,    82,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    84,     2,    85,    69,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    86,    68,    87,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    74,    75,    76,    79
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   279,   279,   287,   291,   300,   301,   305,   306,   310,
     314,   315,   319,   320,   321,   326,   327,   331,   336,   352,
     400,   403,   404,   407,   407,   410,   413,   414,   417,   418,
     421,   424,   425,   426,   429,   430,   448,   457,   458,   461,
     462,   463,   466,   467,   468,   472,   475,   478,   479,   483,
     486,   490,   512,   536,   537,   540,   543,   546,   547,   551,
     554,   555,   558,   559,   562,   563,   566,   569,   573,   595,
     618,   619,   622,   636,   641,   648,   653,   661,   670,   681,
     701,   733,   735,   737,   739,   741,   743,   747,   749,   751,
     753,   757,   759,   761,   763,   765,   767,   769,   773,   775,
     777,   779,   781,   783,   788,   790,   792,   794,   796,   798,
     800,   802,   804,   806,   808,   813,   815,   817,   819,   821,
     823,   827,   829,   831,   835,   838,   841,   847,   856,   859,
     860,   861,   862,   865,   866,   869,   870,   874,   876,   878,
     880,   882,   886,   889,   892,   894,   897,   899,   903,   906,
     908,   910,   916,   917,   916,   920,   921,   926,   927,   928,
     929,   930,   933,   935,   936,   937,   946,   955,   956,   960,
     988,   995,  1021,  1026,  1027,  1028,  1029,  1031,  1034,  1037,
    1038,  1041,  1044,  1045,  1048,  1051,  1054,  1057,  1058,  1059,
    1063,  1070,  1071,  1072,  1076,  1077
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"identifier\"",
  "\"integer literal\"", "\"float literal\"", "\"rune literal\"",
  "\"string literal\"", "K_BREAK", "K_DEFAULT", "K_FUNC", "K_INTERFACE",
  "K_SELECT", "K_CASE", "K_DEFER", "K_GO", "K_MAP", "K_STRUCT", "K_CHAN",
  "K_ELSE", "K_GOTO", "K_PACKAGE", "K_SWITCH", "K_CONST", "K_FALLTHROUGH",
  "K_IF", "K_RANGE", "K_TYPE", "K_CONTINUE", "K_FOR", "K_IMPORT",
  "K_RETURN", "K_VAR", "O_ADDEQ", "O_ANDEQ", "O_LAND", "O_EQ", "O_NEQ",
  "O_SUBEQ", "O_OREQ", "O_LOR", "O_LT", "O_LEQ", "O_MULEQ", "O_XOREQ",
  "O_CHAN_DIR", "O_GT", "O_GEQ", "O_LSHIFT", "O_DIVEQ", "O_LSHIFTEQ",
  "O_INC", "O_ASSGN", "O_RSHIFT", "O_MODEQ", "O_RSHIFTEQ", "O_DEC",
  "O_ELLIPSES", "O_AMPXOR", "O_AMPXOREQ", "P_TYPE", "P_CONST", "P_NIL",
  "P_FUNC", "EMPTY", "NORMAL", "'+'", "'-'", "'|'", "'^'", "'*'", "'/'",
  "'%'", "'&'", "P_UNARY", "NotPackage", "NotParen", "'('", "')'",
  "PreferToRightParen", "'.'", "','", "'='", "'!'", "'['", "']'", "'{'",
  "'}'", "';'", "$accept", "SourceFile", "PackageClause", "PackageName",
  "ImportDecls", "ImportDecl", "ImportSpecList", "ImportSpecList2",
  "ImportSpec", "Type", "TypeName", "QualifiedID", "Signature",
  "SignatureSuff", "Result", "Parameters", "ParameterList",
  "ParameterList2", "ParameterDecl", "ParameterDeclPre",
  "PIdentifierListSuff", "MethodName", "TopLevelDecls", "TopLevelDecl",
  "Declaration", "FunctionDecl", "FunctionName", "FunctionBody",
  "MethodDecl", "Receiver", "ConstDecl", "ConstSpecs", "ConstSpec",
  "CIdentifierListSuff", "CIdentifierListSuffPre", "TypeDecl", "TypeSpecs",
  "TypeSpecList", "TypeSpec", "AliasDecl", "TypeDef", "VarDecl",
  "VarSpecs", "VarSpec", "VIdentifierListSuff", "VIdentifierListTypeSuff",
  "IdentifierList", "ExprList", "rel_op", "add_op", "mul_op", "unary_op",
  "assign_op", "Expr", "UnaryExpr", "PrimaryExpr", "Index", "Arguments",
  "Args2", "ArgsOp1", "ArgsOp2", "Operand", "Literal", "BasicLit",
  "FunctionLit", "OperandName", "Block", "$@1", "$@2", "StatementList",
  "Statement", "SimpleStmt", "ExprStmt", "IncDecStmt", "Assignment",
  "ShortVarDecl", "ForStmt", "OptionalForClause", "Condition", "ForClause",
  "OptionalForClauseInit", "OptionalForClauseCondition",
  "OptionalForClausePost", "InitStmt", "PostStmt", "RangeClause",
  "OptionalForRangePre", "IfStmt", "OptionalElse", "ReturnStmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,    43,    45,   124,    94,
      42,    47,    37,    38,   321,   322,   323,    40,    41,   324,
      46,    44,    61,    33,    91,    93,   123,   125,    59
};
#endif

#define YYPACT_NINF (-189)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-190)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -14,    31,    45,   100,  -189,  -189,  -189,    25,   147,   100,
    -189,    30,    48,    91,  -189,     0,    23,    62,    64,  -189,
     147,  -189,  -189,  -189,  -189,  -189,  -189,  -189,    54,    30,
    -189,  -189,  -189,    18,  -189,    60,   137,  -189,   144,  -189,
       9,    -1,   155,  -189,  -189,  -189,  -189,   144,  -189,     1,
    -189,  -189,  -189,    30,  -189,    82,  -189,    37,   -34,    87,
      51,  -189,    60,     6,  -189,  -189,    37,   165,    96,  -189,
    -189,  -189,  -189,   101,    37,  -189,   109,   155,    14,  -189,
     209,   107,  -189,  -189,  -189,   111,  -189,  -189,  -189,  -189,
    -189,  -189,    65,  -189,  -189,  -189,  -189,    87,  -189,  -189,
     123,  -189,   199,   209,  -189,  -189,  -189,  -189,  -189,   125,
    -189,  -189,  -189,  -189,    60,   209,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,   209,  -189,  -189,   126,   209,   513,
    -189,   -64,  -189,  -189,  -189,  -189,  -189,   209,  -189,    32,
    -189,   125,  -189,  -189,  -189,   126,    87,  -189,   474,   209,
    -189,   209,  -189,  -189,   209,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
     209,   209,   209,   190,   209,  -189,  -189,   126,  -189,   159,
    -189,  -189,   513,   590,   552,   616,   270,   270,   190,   127,
      99,   126,   149,   378,    68,   209,    46,   209,  -189,    43,
      22,   431,   122,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,   209,  -189,   129,  -189,   266,    74,   117,   335,
    -189,    87,  -189,  -189,   130,  -189,  -189,   185,   126,   209,
     209,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,   209,  -189,   126,  -189,   139,   204,
     209,   209,  -189,   209,   209,   126,   126,   513,  -189,    13,
    -189,   513,  -189,   136,   513,  -189,  -189,   284,  -189,  -189,
    -189
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     6,     4,     3,     1,     0,    38,     6,
      12,     0,     0,     0,     7,     0,     0,     0,     0,     2,
      38,    39,    40,    41,    42,    43,    44,     5,     0,    11,
      13,    14,    46,    33,    50,     0,     0,    77,     0,    51,
      58,     0,    63,    59,    60,    64,    65,     0,    68,     0,
      37,     8,     9,    11,    32,     0,    29,     0,    35,    48,
      22,    36,     0,     0,    53,    17,     0,     0,     0,    57,
      15,    18,    55,     0,     0,    67,     0,    63,     0,    70,
       0,    76,    72,    10,    25,    26,    30,    34,    31,   152,
      45,    47,    27,    24,    20,    21,    23,    48,    52,    54,
       0,    78,     0,     0,    66,    61,    62,    69,    71,   149,
     144,   145,   146,   147,     0,     0,   141,   140,   150,    98,
      99,   101,   102,   103,     0,   100,   151,    74,     0,    79,
     120,   123,   124,   137,   142,   143,   138,     0,    73,    33,
     156,    77,    49,    16,    19,    56,    48,   121,     0,     0,
     122,     0,    81,    82,     0,    83,    84,    85,    86,    94,
      95,    97,    87,    88,    89,    90,    91,    92,    93,    96,
       0,     0,     0,   132,     0,   125,   126,    75,    28,   153,
     148,   139,    80,   116,   115,   117,   118,   119,     0,   130,
     151,   129,   134,     0,   149,     0,   176,   194,   158,     0,
       0,   166,     0,   155,   157,   162,   163,   164,   165,   159,
     160,   161,     0,   133,   136,   127,     0,     0,     0,    79,
     184,     0,   173,   174,     0,   179,   175,     0,   195,     0,
       0,   104,   111,   105,   106,   108,   107,   109,   112,   167,
     110,   113,   168,   114,     0,   154,   131,   135,     0,   193,
     188,   187,   172,     0,     0,   171,   169,   170,   128,     0,
     190,   177,   181,     0,   186,   192,   191,   183,   185,   178,
     182
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -189,  -189,  -189,   174,   221,  -189,  -189,   178,   124,   -30,
    -189,   -35,   -44,  -189,  -189,    33,  -189,  -189,    94,  -189,
    -189,  -189,   214,  -189,    58,  -189,  -189,   -61,  -189,  -189,
    -189,  -189,    89,  -189,  -189,  -189,  -189,   161,   222,  -189,
    -189,  -189,  -189,    -5,  -189,  -189,   -18,   -79,  -189,  -189,
    -189,  -189,  -189,  -108,    39,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,  -115,  -189,  -189,  -189,
    -189,  -188,  -189,  -189,  -189,  -189,  -189,  -189,   -13,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,   -16,  -189,  -189
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    68,     8,     9,    28,    52,    53,   100,
      70,   126,    59,    94,    95,    60,    55,    85,    56,    57,
      88,    62,    19,    20,    21,    22,    35,    90,    23,    36,
      24,    63,    39,    72,    73,    25,    43,    76,    77,    45,
      46,    26,    78,    48,    82,   138,    40,   200,   170,   171,
     172,   128,   244,   129,   130,   131,   175,   176,   192,   214,
     248,   132,   133,   134,   135,   136,    91,   140,   202,   179,
     203,   204,   205,   206,   207,   208,   209,   221,   222,   223,
     224,   263,   269,   225,   270,   226,   227,   210,   260,   211
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,   127,     4,    32,     4,    71,    71,     1,   220,    37,
      69,    75,     4,   173,    71,    58,   148,    37,    97,    81,
     174,    37,    71,    87,   145,    71,    37,    86,     4,    49,
      93,    71,    10,     4,     4,    37,   142,    10,   195,    71,
       4,   182,    79,   183,   104,     6,   184,    67,    34,   194,
     110,   111,   112,   113,     4,    30,   114,    71,   177,    65,
      49,    65,   185,   186,   187,    41,   193,    37,   141,    65,
     146,   201,  -189,   108,    58,    54,    66,    33,    66,   268,
     148,    74,    67,    80,    98,   180,    66,   216,   219,    54,
      67,   115,   107,    96,   191,   229,   -27,    65,    31,    89,
      38,   249,    11,   149,   230,    12,   252,   116,   117,   118,
      12,    65,   119,   120,    66,   121,   122,   218,   228,   123,
     -77,    58,    54,   124,    67,    65,   250,    64,    92,   125,
       7,    14,    51,   246,  -180,    29,   257,    33,   190,    42,
      61,    47,    66,   189,   265,   261,   264,    37,    -4,   -77,
     255,   256,    99,   190,   147,    67,   -18,    15,    41,   201,
      84,   199,   194,   110,   111,   112,   113,   150,   101,   114,
      16,   255,   256,    89,    17,     5,   102,   -18,   217,    18,
     -18,    13,    16,   103,   195,    13,    17,   105,   196,   137,
     197,    18,   139,   109,   110,   111,   112,   113,   149,   251,
     114,   143,   144,    13,   115,    -4,   213,   149,   212,   245,
     247,   254,   109,   110,   111,   112,   113,   258,   253,   114,
     116,   117,   118,   259,   267,   119,   120,    13,   121,   122,
      27,    83,   123,   178,    50,   115,   124,   198,   106,    44,
     262,     0,   125,   266,     0,     0,     0,     0,     0,   199,
      65,   116,   117,   118,   115,     0,   119,   120,     0,   121,
     122,     0,     0,   123,     0,     0,     0,   188,     0,     0,
     116,   117,   118,   125,     0,   119,   120,     0,   121,   122,
       0,     0,   123,     0,     0,     0,   124,   194,   110,   111,
     112,   113,   125,     0,   114,     0,     0,     0,     0,     0,
       0,   151,   152,   153,     0,     0,   154,   155,   156,     0,
       0,     0,   157,   158,   159,     0,     0,     0,   159,   160,
       0,     0,     0,   160,   161,     0,     0,     0,   161,   115,
       0,     0,   162,   163,   164,   165,   166,   167,   168,   169,
     166,   167,   168,   169,     0,   116,   117,   118,     0,     0,
     119,   120,    89,   121,   122,     0,     0,   123,     0,     0,
       0,   124,     0,     0,     0,     0,     0,   125,   231,   232,
     151,   152,   153,   233,   234,   154,   155,   156,   235,   236,
       0,   157,   158,   159,   237,   238,   239,     0,   160,   240,
     241,   242,     0,   161,   243,     0,     0,     0,     0,     0,
       0,   162,   163,   164,   165,   166,   167,   168,   169,     0,
       0,     0,     0,   151,   152,   153,     0,     0,   154,   155,
     156,  -177,     0,  -166,   157,   158,   159,     0,     0,     0,
       0,   160,     0,     0,     0,     0,   161,     0,     0,     0,
       0,     0,     0,     0,   162,   163,   164,   165,   166,   167,
     168,   169,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   215,   231,   232,   151,   152,   153,   233,
     234,   154,   155,   156,   235,   236,     0,   157,   158,   159,
     237,   238,   239,     0,   160,   240,   241,   242,     0,   161,
     243,     0,     0,     0,     0,     0,     0,   162,   163,   164,
     165,   166,   167,   168,   169,     0,     0,     0,     0,   151,
     152,   153,   -79,   -79,   154,   155,   156,     0,     0,     0,
     157,   158,   159,     0,     0,     0,     0,   160,     0,     0,
       0,     0,   161,     0,     0,     0,     0,     0,     0,     0,
     162,   163,   164,   165,   166,   167,   168,   169,   151,   152,
     153,     0,   181,   154,   155,   156,     0,     0,     0,   157,
     158,   159,     0,     0,     0,     0,   160,     0,     0,     0,
       0,   161,     0,     0,     0,     0,     0,     0,     0,   162,
     163,   164,   165,   166,   167,   168,   169,   151,   152,   153,
       0,     0,     0,   155,   156,     0,     0,     0,   157,   158,
     159,     0,     0,     0,     0,   160,     0,     0,     0,     0,
     161,     0,     0,     0,     0,     0,     0,     0,   162,   163,
     164,   165,   166,   167,   168,   169,   152,   153,     0,     0,
       0,   155,   156,     0,     0,     0,   157,   158,   159,     0,
       0,     0,     0,   160,     0,     0,     0,     0,   161,     0,
       0,     0,     0,     0,     0,     0,   162,   163,   164,   165,
     166,   167,   168,   169,   159,     0,     0,     0,     0,   160,
       0,     0,     0,     0,   161,     0,     0,     0,     0,     0,
       0,     0,   162,   163,   164,   165,   166,   167,   168,   169
};

static const yytype_int16 yycheck[] =
{
      18,    80,     3,     3,     3,    40,    41,    21,   196,     3,
      40,    41,     3,    77,    49,    33,   124,     3,    62,    49,
      84,     3,    57,    57,   103,    60,     3,    57,     3,    47,
      60,    66,     7,     3,     3,     3,    97,     7,    25,    74,
       3,   149,    47,   151,    74,     0,   154,    81,    15,     3,
       4,     5,     6,     7,     3,     7,    10,    92,   137,    60,
      78,    60,   170,   171,   172,     3,   174,     3,     3,    60,
     114,   179,    26,    78,    92,    57,    77,    77,    77,   267,
     188,    82,    81,    82,    78,   146,    77,   195,   196,    57,
      81,    45,    78,    60,   173,    52,    78,    60,     7,    86,
      77,   216,    77,    81,    82,    80,   221,    61,    62,    63,
      80,    60,    66,    67,    77,    69,    70,   196,   197,    73,
      52,   139,    57,    77,    81,    60,    52,    38,    77,    83,
      30,     7,    78,   212,    88,    11,   244,    77,   173,    77,
       3,    77,    77,   173,   259,   253,   254,     3,    80,    81,
     229,   230,    63,   188,   115,    81,    57,    10,     3,   267,
      78,   179,     3,     4,     5,     6,     7,   128,     3,    10,
      23,   250,   251,    86,    27,     1,    80,    78,   196,    32,
      81,     7,    23,    82,    25,    11,    27,    78,    29,    82,
      31,    32,    81,     3,     4,     5,     6,     7,    81,    82,
      10,    78,     3,    29,    45,    80,    57,    81,    81,    87,
      81,    26,     3,     4,     5,     6,     7,    78,    88,    10,
      61,    62,    63,    19,    88,    66,    67,    53,    69,    70,
       9,    53,    73,   139,    20,    45,    77,   179,    77,    17,
     253,    -1,    83,   259,    -1,    -1,    -1,    -1,    -1,   267,
      60,    61,    62,    63,    45,    -1,    66,    67,    -1,    69,
      70,    -1,    -1,    73,    -1,    -1,    -1,    77,    -1,    -1,
      61,    62,    63,    83,    -1,    66,    67,    -1,    69,    70,
      -1,    -1,    73,    -1,    -1,    -1,    77,     3,     4,     5,
       6,     7,    83,    -1,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    -1,    -1,    40,    41,    42,    -1,
      -1,    -1,    46,    47,    48,    -1,    -1,    -1,    48,    53,
      -1,    -1,    -1,    53,    58,    -1,    -1,    -1,    58,    45,
      -1,    -1,    66,    67,    68,    69,    70,    71,    72,    73,
      70,    71,    72,    73,    -1,    61,    62,    63,    -1,    -1,
      66,    67,    86,    69,    70,    -1,    -1,    73,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    -1,    -1,    83,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    46,    47,    48,    49,    50,    51,    -1,    53,    54,
      55,    56,    -1,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    35,    36,    37,    -1,    -1,    40,    41,
      42,    86,    -1,    88,    46,    47,    48,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,    46,    47,    48,
      49,    50,    51,    -1,    53,    54,    55,    56,    -1,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    35,
      36,    37,    81,    82,    40,    41,    42,    -1,    -1,    -1,
      46,    47,    48,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    35,    36,
      37,    -1,    78,    40,    41,    42,    -1,    -1,    -1,    46,
      47,    48,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    70,    71,    72,    73,    35,    36,    37,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    46,    47,
      48,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,
      68,    69,    70,    71,    72,    73,    36,    37,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    46,    47,    48,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      70,    71,    72,    73,    48,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    70,    71,    72,    73
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    21,    90,    91,     3,    92,     0,    30,    93,    94,
       7,    77,    80,    92,    97,    10,    23,    27,    32,   111,
     112,   113,   114,   117,   119,   124,   130,    93,    95,    97,
       7,     7,     3,    77,   104,   115,   118,     3,    77,   121,
     135,     3,    77,   125,   127,   128,   129,    77,   132,   135,
     111,    78,    96,    97,    57,   105,   107,   108,   135,   101,
     104,     3,   110,   120,   121,    60,    77,    81,    92,    98,
      99,   100,   122,   123,    82,    98,   126,   127,   131,   132,
      82,    98,   133,    96,    78,   106,    98,    57,   109,    86,
     116,   155,    77,    98,   102,   103,   104,   101,    78,   121,
      98,     3,    80,    82,    98,    78,   126,    78,   132,     3,
       4,     5,     6,     7,    10,    45,    61,    62,    63,    66,
      67,    69,    70,    73,    77,    83,   100,   136,   140,   142,
     143,   144,   150,   151,   152,   153,   154,    82,   134,    81,
     156,     3,   116,    78,     3,   136,   101,   143,   142,    81,
     143,    35,    36,    37,    40,    41,    42,    46,    47,    48,
      53,    58,    66,    67,    68,    69,    70,    71,    72,    73,
     137,   138,   139,    77,    84,   145,   146,   136,   107,   158,
     116,    78,   142,   142,   142,   142,   142,   142,    77,    98,
     100,   136,   147,   142,     3,    25,    29,    31,   113,   135,
     136,   142,   157,   159,   160,   161,   162,   163,   164,   165,
     176,   178,    81,    57,   148,    85,   142,   135,   136,   142,
     160,   166,   167,   168,   169,   172,   174,   175,   136,    52,
      82,    33,    34,    38,    39,    43,    44,    49,    50,    51,
      54,    55,    56,    59,   141,    87,   136,    81,   149,   155,
      52,    82,   155,    88,    26,   136,   136,   142,    78,    19,
     177,   142,   167,   170,   142,   155,   176,    88,   160,   171,
     173
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    89,    90,    91,    92,    93,    93,    94,    94,    95,
      96,    96,    97,    97,    97,    98,    98,    99,    99,   100,
     101,   102,   102,   103,   103,   104,   105,   105,   106,   106,
     107,   108,   108,   108,   109,   109,   110,   111,   111,   112,
     112,   112,   113,   113,   113,   114,   115,   116,   116,   117,
     118,   119,   119,   120,   120,   121,   122,   123,   123,   124,
     125,   125,   126,   126,   127,   127,   128,   129,   130,   130,
     131,   131,   132,   133,   133,   134,   134,   135,   135,   136,
     136,   137,   137,   137,   137,   137,   137,   138,   138,   138,
     138,   139,   139,   139,   139,   139,   139,   139,   140,   140,
     140,   140,   140,   140,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   142,   142,   142,   142,   142,
     142,   143,   143,   143,   144,   144,   144,   145,   146,   147,
     147,   147,   147,   148,   148,   149,   149,   150,   150,   150,
     150,   150,   151,   151,   152,   152,   152,   152,   153,   154,
     154,   154,   156,   157,   155,   158,   158,   159,   159,   159,
     159,   159,   160,   160,   160,   160,   161,   162,   162,   163,
     163,   164,   165,   166,   166,   166,   166,   167,   168,   169,
     169,   170,   171,   171,   172,   173,   174,   175,   175,   175,
     176,   177,   177,   177,   178,   178
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     1,     2,     0,     2,     4,     2,
       2,     0,     1,     2,     2,     1,     3,     1,     1,     3,
       2,     1,     0,     1,     1,     3,     2,     0,     3,     0,
       2,     2,     1,     0,     1,     0,     1,     2,     0,     1,
       1,     1,     1,     1,     1,     4,     1,     1,     0,     5,
       1,     2,     4,     1,     2,     2,     3,     1,     0,     2,
       1,     3,     2,     0,     1,     1,     3,     2,     2,     4,
       1,     2,     2,     2,     2,     2,     0,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       1,     2,     2,     1,     1,     2,     2,     3,     5,     1,
       1,     3,     0,     1,     0,     1,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     0,     0,     5,     2,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     3,
       3,     3,     3,     1,     1,     1,     0,     1,     5,     1,
       0,     1,     1,     0,     1,     1,     3,     2,     2,     0,
       4,     2,     2,     0,     1,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* SourceFile: PackageClause ImportDecls TopLevelDecls  */
#line 280 "prog.y"
                                         {if (yychar != YYEOF) {printf("Invalid - reached start symbol before EOF\n")
; YYERROR;} printf("Valid\n"); YYACCEPT;}
#line 2005 "prog.tab.c"
    break;

  case 4: /* PackageName: "identifier"  */
#line 292 "prog.y"
                                                {	
							strcpy(value.name, (yyvsp[0].T_ID)); 
							(yyval.PackageName) = makeNode(T_ID, value, NULL, NULL);
						}
#line 2014 "prog.tab.c"
    break;

  case 15: /* Type: TypeName  */
#line 326 "prog.y"
                          { (yyval.Type) = (yyvsp[0].TypeName); }
#line 2020 "prog.tab.c"
    break;

  case 16: /* Type: '(' Type ')'  */
#line 327 "prog.y"
                                { (yyval.Type) = (yyvsp[-1].Type); }
#line 2026 "prog.tab.c"
    break;

  case 17: /* TypeName: P_TYPE  */
#line 332 "prog.y"
                                { 
				 	strcpy(value.name, (yyvsp[0].P_TYPE));
				 	(yyval.TypeName) = makeNode(T_ID, value, NULL, NULL);
				}
#line 2035 "prog.tab.c"
    break;

  case 18: /* TypeName: QualifiedID  */
#line 337 "prog.y"
                                 {(yyval.TypeName) = (yyvsp[0].QualifiedID);}
#line 2041 "prog.tab.c"
    break;

  case 19: /* QualifiedID: PackageName '.' "identifier"  */
#line 353 "prog.y"
                                                {	
							value.name[0] = 0; 
							strcat(value.name, (yyvsp[-2].PackageName)->value.name); 
							strcat(value.name, "."); 
							strcat(value.name, (yyvsp[0].T_ID)); 
							(yyval.QualifiedID) = makeNode(T_ID, value, NULL, NULL);
						}
#line 2053 "prog.tab.c"
    break;

  case 51: /* ConstDecl: K_CONST ConstSpec  */
#line 490 "prog.y"
                                                                {
											if(stack_v.top != stack_i.top && stack_v.top != -1) {
												yyerror("Imbalanced assignment");
												YYERROR;
											}
											else {
												if (stack_v.top == -1){
													while(!stempty(stack_i)) {

														insert('c', pop(&stack_i), pop(&stack_t), "NULL", stack_scope.s[stack_scope.top]);

													}
												}
												else {
													while(!stempty(stack_i)) {

														insert('c', pop(&stack_i), pop(&stack_t), pop(&stack_v), stack_scope.s[stack_scope.top]);

													}
												}
											} 
										}
#line 2080 "prog.tab.c"
    break;

  case 52: /* ConstDecl: K_CONST '(' ConstSpecs ')'  */
#line 513 "prog.y"
                                                                                {
											if(stack_v.top != stack_i.top && stack_v.top != -1) {
												yyerror("Imbalanced assignment");
												YYERROR;
											}
											else {
												if (stack_v.top == -1){
													while(!stempty(stack_i)) {

														insert('c', pop(&stack_i), pop(&stack_t), "NULL", stack_scope.s[stack_scope.top]);

													}
												}
												else {
													while(!stempty(stack_i)) {

														insert('c', pop(&stack_i), pop(&stack_t), pop(&stack_v), stack_scope.s[stack_scope.top]);

													}
												}
											}  
										}
#line 2107 "prog.tab.c"
    break;

  case 68: /* VarDecl: K_VAR VarSpec  */
#line 573 "prog.y"
                                                        { 
										if(stack_v.top != stack_i.top && stack_v.top != -1) {
												yyerror("Imbalanced assignment");
												YYERROR;
											}
											else {
												if (stack_v.top == -1){
													while(!stempty(stack_i)) {

														insert('v', pop(&stack_i), Tflag, "NULL", stack_scope.s[stack_scope.top]);

													}
												}
												else {
													while(!stempty(stack_i)) {

														insert('v', pop(&stack_i), pop(&stack_t), pop(&stack_v), stack_scope.s[stack_scope.top]);

													}
												}
											} 
									}
#line 2134 "prog.tab.c"
    break;

  case 69: /* VarDecl: K_VAR '(' VarSpecs ')'  */
#line 595 "prog.y"
                                                         { 
											if(stack_v.top != stack_i.top && stack_v.top != -1) {
												yyerror("Imbalanced assignment");
												YYERROR;
											}
											else {
												if (stack_v.top == -1){
													while(!stempty(stack_i)) {

														insert('v', pop(&stack_i), Tflag, "NULL", stack_scope.s[stack_scope.top]);

													}
												}
												else {
													while(!stempty(stack_i)) {

														insert('v', pop(&stack_i), pop(&stack_t), pop(&stack_v), stack_scope.s[stack_scope.top]);

													}
												}
											} 
										}
#line 2161 "prog.tab.c"
    break;

  case 72: /* VarSpec: IdentifierList VIdentifierListSuff  */
#line 623 "prog.y"
                                { 
					if((yyvsp[0].VIdentifierListSuff)) {
						printf("Assigning to variables\nIds: %d Exprs: %d\n", seqLen((yyvsp[-1].IdentifierList)), seqLen((yyvsp[0].VIdentifierListSuff)->value.n)); 
						value.op[0] = '='; value.op[1] = 0; 
						(yyval.VarSpec) = makeNode(OP, value, (yyvsp[-1].IdentifierList), (yyvsp[0].VIdentifierListSuff));
					} 
					else {
						printf("Not assigning\n");
						(yyval.VarSpec) = NULL;
					}
				}
#line 2177 "prog.tab.c"
    break;

  case 73: /* VIdentifierListSuff: Type VIdentifierListTypeSuff  */
#line 637 "prog.y"
                                                                         {	
									 	(yyval.VIdentifierListSuff) = (yyvsp[0].VIdentifierListTypeSuff);
									 	strcpy(Tflag, (yyvsp[-1].Type)->value.name);
									 }
#line 2186 "prog.tab.c"
    break;

  case 74: /* VIdentifierListSuff: '=' ExprList  */
#line 642 "prog.y"
                                                                         {	
									 	value.n = (yyvsp[0].ExprList); 
									 	(yyval.VIdentifierListSuff) = makeNode(OP, value, NULL, NULL);
									 }
#line 2195 "prog.tab.c"
    break;

  case 75: /* VIdentifierListTypeSuff: '=' ExprList  */
#line 649 "prog.y"
                                                                                         {	
											 	value.n = (yyvsp[0].ExprList); 
											 	(yyval.VIdentifierListTypeSuff) = makeNode(OP, value, NULL, NULL);
											 }
#line 2204 "prog.tab.c"
    break;

  case 76: /* VIdentifierListTypeSuff: %empty  */
#line 654 "prog.y"
                                                                                                {
											  		(yyval.VIdentifierListTypeSuff) = NULL; 

												}
#line 2213 "prog.tab.c"
    break;

  case 77: /* IdentifierList: "identifier"  */
#line 662 "prog.y"
                                                        {	
							 	strcpy(value.name, (yyvsp[0].T_ID)); 
							 	(yyval.IdentifierList) = makeNode(T_ID, value, NULL, NULL); 
							 	/*printf("Type: %d Value: %s\n", $$->type, $$->value.name);*/
								
								push(&stack_i, value.name);
								
							}
#line 2226 "prog.tab.c"
    break;

  case 78: /* IdentifierList: IdentifierList ',' "identifier"  */
#line 671 "prog.y"
                                                        {	
							 	strcpy(value.name, (yyvsp[0].T_ID)); 
							 	(yyval.IdentifierList) = makeNode(SEQ, value, makeNode(T_ID, value, NULL, NULL), (yyvsp[-2].IdentifierList));

							 	push(&stack_i, value.name);
							}
#line 2237 "prog.tab.c"
    break;

  case 79: /* ExprList: Expr  */
#line 682 "prog.y"
                                {	
				 	(yyval.ExprList) = (yyvsp[0].Expr);
				 			
    				if ((yyvsp[0].Expr)->type == INT) {
    					sprintf(result, "%d", (yyvsp[0].Expr)->value.i);
    					push(&stack_t, "int");
    				}
    				if ((yyvsp[0].Expr)->type == FLOAT) {
    					sprintf(result, "%f", (yyvsp[0].Expr)->value.f);
    					push(&stack_t, "float");
    				}
    				if ((yyvsp[0].Expr)->type == STRING) {
    					strcpy(result, (yyvsp[0].Expr)->value.str);
    					push(&stack_t, "string");
    				}
    							
    				push(&stack_v, result);
    				
				 }
#line 2261 "prog.tab.c"
    break;

  case 80: /* ExprList: ExprList ',' Expr  */
#line 702 "prog.y"
                                 { 
				 	(yyval.ExprList) = makeNode(SEQ, value, (yyvsp[0].Expr), (yyvsp[-2].ExprList));

				 	
    				if ((yyvsp[0].Expr)->type == INT) {
    					sprintf(result, "%d", (yyvsp[0].Expr)->value.i);
    					push(&stack_t, "int");
    				}
    				if ((yyvsp[0].Expr)->type == FLOAT) {
    					sprintf(result, "%f", (yyvsp[0].Expr)->value.f);
    					push(&stack_t, "float");
    				}
    				if ((yyvsp[0].Expr)->type == STRING) {
    					strcpy(result, (yyvsp[0].Expr)->value.str);
    					push(&stack_t, "string");
    				}
    						
    				push(&stack_v, result);
    			
				 }
#line 2286 "prog.tab.c"
    break;

  case 81: /* rel_op: O_EQ  */
#line 734 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_EQ)); (yyval.rel_op) = makeNode(OP, value, NULL, NULL); }
#line 2292 "prog.tab.c"
    break;

  case 82: /* rel_op: O_NEQ  */
#line 736 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_NEQ)); (yyval.rel_op) = makeNode(OP, value, NULL, NULL);}
#line 2298 "prog.tab.c"
    break;

  case 83: /* rel_op: O_LT  */
#line 738 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_LT)); (yyval.rel_op) = makeNode(OP, value, NULL, NULL);}
#line 2304 "prog.tab.c"
    break;

  case 84: /* rel_op: O_LEQ  */
#line 740 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_LEQ)); (yyval.rel_op) = makeNode(OP, value, NULL, NULL);}
#line 2310 "prog.tab.c"
    break;

  case 85: /* rel_op: O_GT  */
#line 742 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_GT)); (yyval.rel_op) = makeNode(OP, value, NULL, NULL);}
#line 2316 "prog.tab.c"
    break;

  case 86: /* rel_op: O_GEQ  */
#line 744 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_GEQ)); (yyval.rel_op) = makeNode(OP, value, NULL, NULL);}
#line 2322 "prog.tab.c"
    break;

  case 87: /* add_op: '+'  */
#line 748 "prog.y"
                                         {value.op[0] = *((int*)&yylval); value.op[1] = 0; (yyval.add_op) = makeNode(OP, value, NULL, NULL);}
#line 2328 "prog.tab.c"
    break;

  case 88: /* add_op: '-'  */
#line 750 "prog.y"
                                         {value.op[0] = *((int*)&yylval); value.op[1] = 0; (yyval.add_op) = makeNode(OP, value, NULL, NULL);}
#line 2334 "prog.tab.c"
    break;

  case 89: /* add_op: '|'  */
#line 752 "prog.y"
                                         {value.op[0] = *((int*)&yylval); value.op[1] = 0; (yyval.add_op) = makeNode(OP, value, NULL, NULL);}
#line 2340 "prog.tab.c"
    break;

  case 90: /* add_op: '^'  */
#line 754 "prog.y"
                                         {value.op[0] = *((int*)&yylval); value.op[1] = 0; (yyval.add_op) = makeNode(OP, value, NULL, NULL);}
#line 2346 "prog.tab.c"
    break;

  case 91: /* mul_op: '*'  */
#line 758 "prog.y"
                                         {value.op[0] = *((int*)&yylval); value.op[1] = 0; (yyval.mul_op) = makeNode(OP, value, NULL, NULL);}
#line 2352 "prog.tab.c"
    break;

  case 92: /* mul_op: '/'  */
#line 760 "prog.y"
                                         {value.op[0] = *((int*)&yylval); value.op[1] = 0; (yyval.mul_op) = makeNode(OP, value, NULL, NULL);}
#line 2358 "prog.tab.c"
    break;

  case 93: /* mul_op: '%'  */
#line 762 "prog.y"
                                         {value.op[0] = *((int*)&yylval); value.op[1] = 0; (yyval.mul_op) = makeNode(OP, value, NULL, NULL);}
#line 2364 "prog.tab.c"
    break;

  case 94: /* mul_op: O_LSHIFT  */
#line 764 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_LSHIFT)); (yyval.mul_op) = makeNode(OP, value, NULL, NULL);}
#line 2370 "prog.tab.c"
    break;

  case 95: /* mul_op: O_RSHIFT  */
#line 766 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_RSHIFT)); (yyval.mul_op) = makeNode(OP, value, NULL, NULL);}
#line 2376 "prog.tab.c"
    break;

  case 96: /* mul_op: '&'  */
#line 768 "prog.y"
                                         {value.op[0] = *((int*)&yylval); value.op[1] = 0; (yyval.mul_op) = makeNode(OP, value, NULL, NULL);}
#line 2382 "prog.tab.c"
    break;

  case 97: /* mul_op: O_AMPXOR  */
#line 770 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_AMPXOR)); (yyval.mul_op) = makeNode(OP, value, NULL, NULL);}
#line 2388 "prog.tab.c"
    break;

  case 98: /* unary_op: '+'  */
#line 774 "prog.y"
                                         {value.op[0] = *((int*)&yylval); value.op[1] = 0; (yyval.unary_op) = makeNode(OP, value, NULL, NULL);}
#line 2394 "prog.tab.c"
    break;

  case 99: /* unary_op: '-'  */
#line 776 "prog.y"
                                         {value.op[0] = *((int*)&yylval); value.op[1] = 0; (yyval.unary_op) = makeNode(OP, value, NULL, NULL);}
#line 2400 "prog.tab.c"
    break;

  case 100: /* unary_op: '!'  */
#line 778 "prog.y"
                                         {value.op[0] = *((int*)&yylval); value.op[1] = 0; (yyval.unary_op) = makeNode(OP, value, NULL, NULL);}
#line 2406 "prog.tab.c"
    break;

  case 101: /* unary_op: '^'  */
#line 780 "prog.y"
                                         {value.op[0] = *((int*)&yylval); value.op[1] = 0; (yyval.unary_op) = makeNode(OP, value, NULL, NULL);}
#line 2412 "prog.tab.c"
    break;

  case 102: /* unary_op: '*'  */
#line 782 "prog.y"
                                         {value.op[0] = *((int*)&yylval); value.op[1] = 0; (yyval.unary_op) = makeNode(OP, value, NULL, NULL);}
#line 2418 "prog.tab.c"
    break;

  case 103: /* unary_op: '&'  */
#line 784 "prog.y"
                                         {value.op[0] = *((int*)&yylval); value.op[1] = 0; (yyval.unary_op) = makeNode(OP, value, NULL, NULL);}
#line 2424 "prog.tab.c"
    break;

  case 104: /* assign_op: O_ADDEQ  */
#line 789 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_ADDEQ)); (yyval.assign_op) = makeNode(OP, value, NULL, NULL);}
#line 2430 "prog.tab.c"
    break;

  case 105: /* assign_op: O_SUBEQ  */
#line 791 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_SUBEQ)); (yyval.assign_op) = makeNode(OP, value, NULL, NULL);}
#line 2436 "prog.tab.c"
    break;

  case 106: /* assign_op: O_OREQ  */
#line 793 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_OREQ)); (yyval.assign_op) = makeNode(OP, value, NULL, NULL);}
#line 2442 "prog.tab.c"
    break;

  case 107: /* assign_op: O_XOREQ  */
#line 795 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_XOREQ)); (yyval.assign_op) = makeNode(OP, value, NULL, NULL);}
#line 2448 "prog.tab.c"
    break;

  case 108: /* assign_op: O_MULEQ  */
#line 797 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_MULEQ)); (yyval.assign_op) = makeNode(OP, value, NULL, NULL);}
#line 2454 "prog.tab.c"
    break;

  case 109: /* assign_op: O_DIVEQ  */
#line 799 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_DIVEQ)); (yyval.assign_op) = makeNode(OP, value, NULL, NULL);}
#line 2460 "prog.tab.c"
    break;

  case 110: /* assign_op: O_MODEQ  */
#line 801 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_MODEQ)); (yyval.assign_op) = makeNode(OP, value, NULL, NULL);}
#line 2466 "prog.tab.c"
    break;

  case 111: /* assign_op: O_ANDEQ  */
#line 803 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_ANDEQ)); (yyval.assign_op) = makeNode(OP, value, NULL, NULL);}
#line 2472 "prog.tab.c"
    break;

  case 112: /* assign_op: O_LSHIFTEQ  */
#line 805 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_LSHIFTEQ)); (yyval.assign_op) = makeNode(OP, value, NULL, NULL);}
#line 2478 "prog.tab.c"
    break;

  case 113: /* assign_op: O_RSHIFTEQ  */
#line 807 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_RSHIFTEQ)); (yyval.assign_op) = makeNode(OP, value, NULL, NULL);}
#line 2484 "prog.tab.c"
    break;

  case 114: /* assign_op: O_AMPXOREQ  */
#line 809 "prog.y"
                                         {strcpy(value.op, (yyvsp[0].O_AMPXOREQ)); (yyval.assign_op) = makeNode(OP, value, NULL, NULL);}
#line 2490 "prog.tab.c"
    break;

  case 115: /* Expr: Expr O_LOR Expr  */
#line 814 "prog.y"
                 {strcpy(value.op, (yyvsp[-1].O_LOR)); (yyval.Expr) = makeNode(OP, value, (yyvsp[-2].Expr), (yyvsp[0].Expr));}
#line 2496 "prog.tab.c"
    break;

  case 116: /* Expr: Expr O_LAND Expr  */
#line 816 "prog.y"
                 {strcpy(value.op, (yyvsp[-1].O_LAND)); (yyval.Expr) = makeNode(OP, value, (yyvsp[-2].Expr), (yyvsp[0].Expr));}
#line 2502 "prog.tab.c"
    break;

  case 117: /* Expr: Expr rel_op Expr  */
#line 818 "prog.y"
                 {strcpy(value.op, (yyvsp[-1].rel_op)->value.op); (yyval.Expr) = makeNode(OP, value, (yyvsp[-2].Expr), (yyvsp[0].Expr));}
#line 2508 "prog.tab.c"
    break;

  case 118: /* Expr: Expr add_op Expr  */
#line 820 "prog.y"
                 {strcpy(value.op, (yyvsp[-1].add_op)->value.op); (yyval.Expr) = makeNode(OP, value, (yyvsp[-2].Expr), (yyvsp[0].Expr));}
#line 2514 "prog.tab.c"
    break;

  case 119: /* Expr: Expr mul_op Expr  */
#line 822 "prog.y"
                 {strcpy(value.op, (yyvsp[-1].mul_op)->value.op); (yyval.Expr) = makeNode(OP, value, (yyvsp[-2].Expr), (yyvsp[0].Expr));}
#line 2520 "prog.tab.c"
    break;

  case 120: /* Expr: UnaryExpr  */
#line 824 "prog.y"
                 {(yyval.Expr) = (yyvsp[0].UnaryExpr);}
#line 2526 "prog.tab.c"
    break;

  case 121: /* UnaryExpr: O_CHAN_DIR UnaryExpr  */
#line 828 "prog.y"
                                        {strcpy(value.op, (yyvsp[-1].O_CHAN_DIR)); (yyval.UnaryExpr) = makeNode(OP, value, (yyvsp[0].UnaryExpr), NULL);}
#line 2532 "prog.tab.c"
    break;

  case 122: /* UnaryExpr: unary_op UnaryExpr  */
#line 830 "prog.y"
                                        {strcpy(value.op, (yyvsp[-1].unary_op)->value.op); (yyval.UnaryExpr) = makeNode(OP, value, (yyvsp[0].UnaryExpr), NULL);}
#line 2538 "prog.tab.c"
    break;

  case 123: /* UnaryExpr: PrimaryExpr  */
#line 832 "prog.y"
                                        {(yyval.UnaryExpr) = (yyvsp[0].PrimaryExpr);}
#line 2544 "prog.tab.c"
    break;

  case 124: /* PrimaryExpr: Operand  */
#line 836 "prog.y"
                                                {(yyval.PrimaryExpr) = (yyvsp[0].Operand);}
#line 2550 "prog.tab.c"
    break;

  case 137: /* Operand: Literal  */
#line 875 "prog.y"
                                                {(yyval.Operand) = (yyvsp[0].Literal);}
#line 2556 "prog.tab.c"
    break;

  case 138: /* Operand: OperandName  */
#line 877 "prog.y"
                                                {(yyval.Operand) = (yyvsp[0].OperandName);}
#line 2562 "prog.tab.c"
    break;

  case 139: /* Operand: '(' Expr ')'  */
#line 879 "prog.y"
                                                {(yyval.Operand) = (yyvsp[-1].Expr);}
#line 2568 "prog.tab.c"
    break;

  case 140: /* Operand: P_NIL  */
#line 881 "prog.y"
                                                {value.n = NULL; (yyval.Operand) = makeNode(INT, value, NULL, NULL);}
#line 2574 "prog.tab.c"
    break;

  case 141: /* Operand: P_CONST  */
#line 883 "prog.y"
                                                {value.b = strcmp((yyvsp[0].P_CONST), "true")==0 ? 1 : 0; (yyval.Operand) = makeNode(BOOL, value, NULL, NULL);}
#line 2580 "prog.tab.c"
    break;

  case 142: /* Literal: BasicLit  */
#line 887 "prog.y"
                                                {(yyval.Literal) = (yyvsp[0].BasicLit);}
#line 2586 "prog.tab.c"
    break;

  case 144: /* BasicLit: "integer literal"  */
#line 893 "prog.y"
                                                {value.i = (yyvsp[0].L_INT); (yyval.BasicLit) = makeNode(INT, value, NULL, NULL);}
#line 2592 "prog.tab.c"
    break;

  case 145: /* BasicLit: "float literal"  */
#line 895 "prog.y"
                                                {value.f = (yyvsp[0].L_FLOAT); (yyval.BasicLit) = makeNode(FLOAT, value, NULL, NULL);}
#line 2598 "prog.tab.c"
    break;

  case 146: /* BasicLit: "rune literal"  */
#line 898 "prog.y"
                                                {strcpy(value.str, (yyvsp[0].L_RUNE)); (yyval.BasicLit) = makeNode(RUNE, value, NULL, NULL);}
#line 2604 "prog.tab.c"
    break;

  case 147: /* BasicLit: "string literal"  */
#line 900 "prog.y"
                                                {strcpy(value.str, (yyvsp[0].L_STRING)); (yyval.BasicLit) = makeNode(STRING, value, NULL, NULL);}
#line 2610 "prog.tab.c"
    break;

  case 149: /* OperandName: "identifier"  */
#line 907 "prog.y"
                                                {strcpy(value.name, (yyvsp[0].T_ID)); (yyval.OperandName) = makeNode(T_ID, value, NULL, NULL);}
#line 2616 "prog.tab.c"
    break;

  case 150: /* OperandName: P_FUNC  */
#line 909 "prog.y"
                                                {strcpy(value.name, (yyvsp[0].P_FUNC)); (yyval.OperandName) = makeNode(FUNC, value, NULL, NULL);}
#line 2622 "prog.tab.c"
    break;

  case 151: /* OperandName: QualifiedID  */
#line 911 "prog.y"
                                                {(yyval.OperandName) = (yyvsp[0].QualifiedID);}
#line 2628 "prog.tab.c"
    break;

  case 152: /* $@1: %empty  */
#line 916 "prog.y"
                            {	sprintf(result, "%d", base++);
					push(&stack_scope, result);}
#line 2635 "prog.tab.c"
    break;

  case 153: /* $@2: %empty  */
#line 917 "prog.y"
                                                                                   { pop(&stack_scope); }
#line 2641 "prog.tab.c"
    break;

  case 169: /* Assignment: ExprList '=' ExprList  */
#line 961 "prog.y"
                                         {	
					 	printf("started\n"); 
					 	value.op[0] = '='; 
					 	value.op[1] = 0; 
					 	printf("Operator: %s\n", value.op); 
					 	(yyval.Assignment) = makeNode(OP, value, (yyvsp[-2].ExprList), (yyvsp[0].ExprList));
						strcpy(result, search((yyvsp[-2].ExprList)->value.name));

						if(strcmp(result, "int") == 0 && (yyvsp[0].ExprList)->type == INT) {
							sprintf(result, "%d", (yyvsp[0].ExprList)->value.i);
					 		update((yyvsp[-2].ExprList)->value.name, "int", result);
						}

					 	else if(strcmp(result, "float") == 0 && (yyvsp[0].ExprList)->type == FLOAT) {
					 		sprintf(result, "%f", (yyvsp[0].ExprList)->value.f);
					 		update((yyvsp[-2].ExprList)->value.name, "int", result);
					 	}	

					 	else if(strcmp(result, "string") == 0 && (yyvsp[0].ExprList)->type == STRING)
					 		update((yyvsp[-2].ExprList)->value.name, "int", (yyvsp[0].ExprList)->value.str);

					 	else {
					 		yyerror("Error: type mismatched assignment");
					 		YYERROR;
					 	}

					 }
#line 2673 "prog.tab.c"
    break;

  case 170: /* Assignment: Expr assign_op Expr  */
#line 989 "prog.y"
                                         {	
					 	strcpy(value.op, (yyvsp[-1].assign_op)->value.op); 
					 	(yyval.Assignment) = makeNode(OP, value, (yyvsp[-2].Expr), (yyvsp[0].Expr));
					 }
#line 2682 "prog.tab.c"
    break;

  case 171: /* ShortVarDecl: IdentifierList O_ASSGN ExprList  */
#line 996 "prog.y"
                                        {
						if(stack_v.top != stack_i.top && stack_v.top != -1) {
							yyerror("Imbalanced assignment");
							YYERROR;
						}
						else {
							if (stack_v.top == -1){
								while(!stempty(stack_i)) {

									insert('v', pop(&stack_i), pop(&stack_t), "NULL", stack_scope.s[stack_scope.top]);

								}
							}
							else {
								while(!stempty(stack_i)) {

									insert('v', pop(&stack_i), pop(&stack_t), pop(&stack_v), stack_scope.s[stack_scope.top]);

								}
							}
							 
						}
					}
#line 2710 "prog.tab.c"
    break;


#line 2714 "prog.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1080 "prog.y"

extern int yylineno;

void yyerror(char const* error) {
	fprintf(stderr, "%d: %s\n", yylineno, error);
}

int main()
{
	for(int i=0; i<TABLE_SIZE; i++)
		hashTable[i].hcode = -1;

	sprintf(result, "%d", base);
	base++;
	push(&stack_scope, result);

	
	if ( yyparse() != 0){
		printf("BUILD FAILED...!!\n\n");
		exit(1);
	}

	printf("\n\n\n");
	printf("---------------------------------Symbol Table---------------------------------\n\n");
	disp_symtbl();

	return 0;
}
