/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

#ifndef YY_YY_MENTHOL_BISON_TAB_H_INCLUDED
# define YY_YY_MENTHOL_BISON_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     VARIDENTIFIER = 258,
     IDENTIFIER = 259,
     GLOBALVARIDENTIFIER = 260,
     NUMBER = 261,
     STRING = 262,
     DOUBLE = 263,
     TRUE_KEYWORD = 264,
     FALSE_KEYWORD = 265,
     IF = 266,
     ELSE = 267,
     FOR = 268,
     BREAK = 269,
     TRY = 270,
     EXCEPT = 271,
     THROW = 272,
     IMPORT = 273,
     MODULE = 274,
     USE = 275,
     CONTINUE = 276,
     RETURN = 277,
     WHILE = 278,
     NULL_KEYWORD = 279,
     POWER_OP = 280,
     NEQ_OP = 281,
     OR_OP = 282,
     AND_OP = 283,
     GE_OP = 284,
     LE_OP = 285,
     EQ_OP = 286,
     ADD_ASSIGN = 287,
     SUB_ASSIGN = 288,
     DIV_ASSIGN = 289,
     MUL_ASSIGN = 290,
     ASSIGN_ASSIGN = 291,
     MOD_ASSIGN = 292,
     AND_ASSIGN = 293,
     OR_ASSIGN = 294,
     XOR_ASSIGN = 295,
     SHIFT_LEFT_OP = 296,
     SHIFT_RIGHT_OP = 297,
     WMAIN = 298,
     DEF = 299,
     VAR = 300,
     IN = 301,
     ARRAYSECTION = 302,
     DICT_OP = 303,
     TYPEOF = 304,
     CONST = 305,
     MMRT = 306
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_MENTHOL_BISON_TAB_H_INCLUDED  */
