/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_COMPILA_TAB_H_INCLUDED
# define YY_YY_COMPILA_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMt = 258,
    ID = 259,
    ADDt = 260,
    SUBt = 261,
    MULt = 262,
    DIVt = 263,
    ASGN = 264,
    OPEN = 265,
    CLOSE = 266,
    RETt = 267,
    EOL = 268,
    RECOt = 269,
    MOVEt = 270,
    ATAQt = 271,
    DEPOt = 272,
    ATRt = 273,
    ANGt = 274,
    EQt = 275,
    NEt = 276,
    LTt = 277,
    LEt = 278,
    GTt = 279,
    GEt = 280,
    ABRE = 281,
    FECHA = 282,
    SEP = 283,
    IF = 284,
    ELSE = 285,
    WHILE = 286,
    FUNC = 287,
    PRINT = 288,
    NEG = 289,
    PWR = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 25 "compila.y" /* yacc.c:1909  */

  double val;
  /* symrec *cod; */
  char cod[30];

#line 96 "compila.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_COMPILA_TAB_H_INCLUDED  */
