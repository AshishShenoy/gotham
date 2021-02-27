/* A Bison parser, made by GNU Bison 3.7.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PROG_TAB_H_INCLUDED
# define YY_YY_PROG_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_ID = 258,                    /* "identifier"  */
    L_INT = 259,                   /* "integer literal"  */
    L_FLOAT = 260,                 /* "float literal"  */
    L_RUNE = 261,                  /* "rune literal"  */
    L_STRING = 262,                /* "string literal"  */
    K_BREAK = 263,                 /* K_BREAK  */
    K_DEFAULT = 264,               /* K_DEFAULT  */
    K_FUNC = 265,                  /* K_FUNC  */
    K_INTERFACE = 266,             /* K_INTERFACE  */
    K_SELECT = 267,                /* K_SELECT  */
    K_CASE = 268,                  /* K_CASE  */
    K_DEFER = 269,                 /* K_DEFER  */
    K_GO = 270,                    /* K_GO  */
    K_MAP = 271,                   /* K_MAP  */
    K_STRUCT = 272,                /* K_STRUCT  */
    K_CHAN = 273,                  /* K_CHAN  */
    K_ELSE = 274,                  /* K_ELSE  */
    K_GOTO = 275,                  /* K_GOTO  */
    K_PACKAGE = 276,               /* K_PACKAGE  */
    K_SWITCH = 277,                /* K_SWITCH  */
    K_CONST = 278,                 /* K_CONST  */
    K_FALLTHROUGH = 279,           /* K_FALLTHROUGH  */
    K_IF = 280,                    /* K_IF  */
    K_RANGE = 281,                 /* K_RANGE  */
    K_TYPE = 282,                  /* K_TYPE  */
    K_CONTINUE = 283,              /* K_CONTINUE  */
    K_FOR = 284,                   /* K_FOR  */
    K_IMPORT = 285,                /* K_IMPORT  */
    K_RETURN = 286,                /* K_RETURN  */
    K_VAR = 287,                   /* K_VAR  */
    O_ADDEQ = 288,                 /* O_ADDEQ  */
    O_ANDEQ = 289,                 /* O_ANDEQ  */
    O_LAND = 290,                  /* O_LAND  */
    O_EQ = 291,                    /* O_EQ  */
    O_NEQ = 292,                   /* O_NEQ  */
    O_SUBEQ = 293,                 /* O_SUBEQ  */
    O_OREQ = 294,                  /* O_OREQ  */
    O_LOR = 295,                   /* O_LOR  */
    O_LT = 296,                    /* O_LT  */
    O_LEQ = 297,                   /* O_LEQ  */
    O_MULEQ = 298,                 /* O_MULEQ  */
    O_XOREQ = 299,                 /* O_XOREQ  */
    O_CHAN_DIR = 300,              /* O_CHAN_DIR  */
    O_GT = 301,                    /* O_GT  */
    O_GEQ = 302,                   /* O_GEQ  */
    O_LSHIFT = 303,                /* O_LSHIFT  */
    O_DIVEQ = 304,                 /* O_DIVEQ  */
    O_LSHIFTEQ = 305,              /* O_LSHIFTEQ  */
    O_INC = 306,                   /* O_INC  */
    O_ASSGN = 307,                 /* O_ASSGN  */
    O_RSHIFT = 308,                /* O_RSHIFT  */
    O_MODEQ = 309,                 /* O_MODEQ  */
    O_RSHIFTEQ = 310,              /* O_RSHIFTEQ  */
    O_DEC = 311,                   /* O_DEC  */
    O_ELLIPSES = 312,              /* O_ELLIPSES  */
    O_AMPXOR = 313,                /* O_AMPXOR  */
    O_AMPXOREQ = 314,              /* O_AMPXOREQ  */
    P_TYPE = 315,                  /* P_TYPE  */
    P_CONST = 316,                 /* P_CONST  */
    P_NIL = 317,                   /* P_NIL  */
    P_FUNC = 318,                  /* P_FUNC  */
    EMPTY = 319,                   /* EMPTY  */
    NORMAL = 320,                  /* NORMAL  */
    P_UNARY = 321,                 /* P_UNARY  */
    NotPackage = 322,              /* NotPackage  */
    NotParen = 323,                /* NotParen  */
    PreferToRightParen = 324       /* PreferToRightParen  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
  Node * PackageName;                      /* PackageName  */
  Node * Type;                             /* Type  */
  Node * TypeName;                         /* TypeName  */
  Node * QualifiedID;                      /* QualifiedID  */
  Node * VarSpec;                          /* VarSpec  */
  Node * VIdentifierListSuff;              /* VIdentifierListSuff  */
  Node * VIdentifierListTypeSuff;          /* VIdentifierListTypeSuff  */
  Node * IdentifierList;                   /* IdentifierList  */
  Node * ExprList;                         /* ExprList  */
  Node * rel_op;                           /* rel_op  */
  Node * add_op;                           /* add_op  */
  Node * mul_op;                           /* mul_op  */
  Node * unary_op;                         /* unary_op  */
  Node * assign_op;                        /* assign_op  */
  Node * Expr;                             /* Expr  */
  Node * UnaryExpr;                        /* UnaryExpr  */
  Node * PrimaryExpr;                      /* PrimaryExpr  */
  Node * Operand;                          /* Operand  */
  Node * Literal;                          /* Literal  */
  Node * BasicLit;                         /* BasicLit  */
  Node * OperandName;                      /* OperandName  */
  Node * Assignment;                       /* Assignment  */
  char const * T_ID;                       /* "identifier"  */
  char const * L_RUNE;                     /* "rune literal"  */
  char const * L_STRING;                   /* "string literal"  */
  char const * O_ADDEQ;                    /* O_ADDEQ  */
  char const * O_ANDEQ;                    /* O_ANDEQ  */
  char const * O_LAND;                     /* O_LAND  */
  char const * O_EQ;                       /* O_EQ  */
  char const * O_NEQ;                      /* O_NEQ  */
  char const * O_SUBEQ;                    /* O_SUBEQ  */
  char const * O_OREQ;                     /* O_OREQ  */
  char const * O_LOR;                      /* O_LOR  */
  char const * O_LT;                       /* O_LT  */
  char const * O_LEQ;                      /* O_LEQ  */
  char const * O_MULEQ;                    /* O_MULEQ  */
  char const * O_XOREQ;                    /* O_XOREQ  */
  char const * O_CHAN_DIR;                 /* O_CHAN_DIR  */
  char const * O_GT;                       /* O_GT  */
  char const * O_GEQ;                      /* O_GEQ  */
  char const * O_LSHIFT;                   /* O_LSHIFT  */
  char const * O_DIVEQ;                    /* O_DIVEQ  */
  char const * O_LSHIFTEQ;                 /* O_LSHIFTEQ  */
  char const * O_INC;                      /* O_INC  */
  char const * O_ASSGN;                    /* O_ASSGN  */
  char const * O_RSHIFT;                   /* O_RSHIFT  */
  char const * O_MODEQ;                    /* O_MODEQ  */
  char const * O_RSHIFTEQ;                 /* O_RSHIFTEQ  */
  char const * O_DEC;                      /* O_DEC  */
  char const * O_ELLIPSES;                 /* O_ELLIPSES  */
  char const * O_AMPXOR;                   /* O_AMPXOR  */
  char const * O_AMPXOREQ;                 /* O_AMPXOREQ  */
  char const * P_TYPE;                     /* P_TYPE  */
  char const * P_CONST;                    /* P_CONST  */
  char const * P_FUNC;                     /* P_FUNC  */
  double L_FLOAT;                          /* "float literal"  */
  int L_INT;                               /* "integer literal"  */

#line 191 "prog.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PROG_TAB_H_INCLUDED  */
