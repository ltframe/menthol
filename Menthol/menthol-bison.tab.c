/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "../support/flexbison/menthol-bison.y"

#include "StatementList.h"
extern int yylex();
extern int lineno;
extern int yyerrorcount;
extern char* currentyyfile;
int lineaddress=0;
#define YYDEBUG 1
#define YYPARSE_PARAM parm
int linenum=0;
int yyerror(char* str)
{
	/*
	yyerrorcount++;
	printf("\r\n");
	printf("compile error: %s, in %s,at line %d",str,currentyyfile,lineno);
	printf("\r\n");*/
	MError::CreateInstance()->PrintError(str);
	return(1);
}
enum Scope;
struct StackState;


/* Line 371 of yacc.c  */
#line 93 "menthol-bison.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "menthol-bison.tab.h".  */
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

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 209 "menthol-bison.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   691

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  154
/* YYNRULES -- Number of states.  */
#define YYNSTATES  272

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    67,     2,     2,     2,    68,    71,     2,
      62,    63,    55,    54,    59,    53,    66,    56,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    58,    57,
      69,    52,    70,    74,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    64,     2,    65,    72,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,    73,    61,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    16,    18,    23,
      29,    34,    37,    40,    42,    46,    49,    54,    56,    60,
      64,    67,    69,    73,    75,    77,    79,    81,    85,    90,
      95,    97,   102,   108,   114,   121,   125,   132,   138,   143,
     147,   151,   155,   157,   160,   162,   165,   168,   171,   173,
     177,   179,   183,   187,   191,   193,   197,   199,   203,   205,
     209,   211,   215,   217,   221,   225,   229,   233,   235,   239,
     243,   245,   249,   251,   255,   257,   261,   263,   267,   269,
     273,   275,   281,   283,   285,   287,   291,   293,   297,   301,
     304,   308,   310,   314,   318,   321,   323,   327,   330,   335,
     337,   341,   344,   346,   348,   350,   352,   354,   357,   359,
     362,   364,   366,   368,   370,   372,   374,   376,   378,   380,
     382,   384,   386,   388,   390,   392,   394,   396,   398,   400,
     402,   408,   416,   422,   430,   433,   436,   439,   443,   447,
     449,   452,   454,   458,   465,   469,   471,   475,   477,   481,
     487,   492,   494,   497,   499
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      76,     0,    -1,    77,    -1,    76,    77,    -1,   126,    -1,
     129,    -1,    20,   128,    57,    -1,    78,    -1,    43,    58,
      82,    83,    -1,    44,     4,    58,    82,    83,    -1,    44,
       4,    58,    83,    -1,   112,    57,    -1,   105,    57,    -1,
       3,    -1,     3,    36,   104,    -1,    50,     3,    -1,    50,
       3,    36,   104,    -1,    81,    -1,    82,    59,    81,    -1,
      60,    87,    61,    -1,    60,    61,    -1,   104,    -1,    84,
      59,   104,    -1,   109,    -1,   106,    -1,   117,    -1,   103,
      -1,    62,   104,    63,    -1,    49,    62,   104,    63,    -1,
      51,    62,   104,    63,    -1,    85,    -1,    86,    64,   104,
      65,    -1,    86,    64,   104,    47,    65,    -1,    86,    64,
      47,   104,    65,    -1,    86,    64,   104,    47,   104,    65,
      -1,    86,    48,     4,    -1,    86,    66,     4,    62,    84,
      63,    -1,    86,    66,     4,    62,    63,    -1,    86,    62,
      84,    63,    -1,    86,    62,    63,    -1,    86,    66,     5,
      -1,    86,    66,     4,    -1,   113,    -1,    87,   113,    -1,
      86,    -1,    53,    88,    -1,    54,    88,    -1,    67,    88,
      -1,    88,    -1,    89,    25,    88,    -1,    89,    -1,    90,
      55,    89,    -1,    90,    56,    89,    -1,    90,    68,    89,
      -1,    90,    -1,    91,    53,    90,    -1,    91,    -1,    92,
      54,    91,    -1,    92,    -1,    93,    41,    92,    -1,    93,
      -1,    94,    42,    93,    -1,    94,    -1,    95,    69,    94,
      -1,    95,    70,    94,    -1,    95,    30,    94,    -1,    95,
      29,    94,    -1,    95,    -1,    96,    31,    95,    -1,    96,
      26,    95,    -1,    96,    -1,    97,    71,    96,    -1,    97,
      -1,    98,    72,    97,    -1,    98,    -1,    99,    73,    98,
      -1,    99,    -1,   100,    28,    99,    -1,   100,    -1,   101,
      27,   100,    -1,   101,    -1,   101,    74,   105,    58,   102,
      -1,     3,    -1,     5,    -1,   102,    -1,    88,   118,   104,
      -1,   104,    -1,   105,    59,   104,    -1,    64,   105,    65,
      -1,    64,    65,    -1,     4,    48,   104,    -1,   107,    -1,
     108,    59,   107,    -1,    62,   108,    63,    -1,    62,    63,
      -1,   103,    -1,   103,    36,   104,    -1,    50,   103,    -1,
      50,   103,    36,   104,    -1,   110,    -1,   111,    59,   110,
      -1,    45,   111,    -1,    83,    -1,   122,    -1,   115,    -1,
     116,    -1,   114,    -1,   112,    57,    -1,    57,    -1,   105,
      57,    -1,   119,    -1,   125,    -1,   121,    -1,   120,    -1,
       6,    -1,     7,    -1,     8,    -1,     9,    -1,    10,    -1,
      24,    -1,     4,    -1,    36,    -1,    35,    -1,    34,    -1,
      37,    -1,    32,    -1,    33,    -1,    38,    -1,    40,    -1,
      39,    -1,    11,    62,   105,    63,    83,    -1,    11,    62,
     105,    63,    83,    12,    83,    -1,    23,    62,   105,    63,
      83,    -1,    13,    62,   112,    46,   104,    63,    83,    -1,
      21,    57,    -1,    14,    57,    -1,    22,    57,    -1,    22,
     105,    57,    -1,    17,    84,    57,    -1,     3,    -1,    50,
       3,    -1,   123,    -1,   124,    59,   123,    -1,    15,    83,
      16,    58,   124,    83,    -1,    18,   127,    57,    -1,     4,
      -1,   127,    66,     4,    -1,     4,    -1,   128,    59,     4,
      -1,    19,     4,    60,   130,    61,    -1,    19,     4,    60,
      61,    -1,   131,    -1,   130,   131,    -1,    79,    -1,    80,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   106,   106,   107,   111,   112,   113,   114,   119,   131,
     140,   153,   159,   164,   165,   170,   171,   178,   183,   189,
     193,   200,   207,   218,   221,   224,   225,   228,   229,   232,
     239,   240,   246,   252,   258,   265,   272,   279,   287,   293,
     298,   305,   317,   324,   333,   334,   338,   341,   346,   347,
     354,   355,   359,   363,   369,   370,   376,   377,   384,   385,
     392,   393,   399,   400,   404,   408,   412,   418,   419,   423,
     429,   430,   436,   437,   443,   444,   450,   451,   457,   458,
     464,   467,   475,   478,   487,   488,   522,   526,   534,   538,
     544,   550,   555,   564,   565,   571,   576,   581,   586,   594,
     598,   603,   608,   609,   610,   611,   612,   615,   621,   624,
     630,   631,   634,   635,   639,   646,   653,   660,   665,   671,
     676,   685,   686,   687,   688,   689,   690,   691,   692,   693,
     696,   702,   713,   721,   727,   730,   733,   736,   737,   740,
     741,   744,   749,   755,   762,   770,   774,   782,   787,   794,
     800,   807,   814,   823,   824
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VARIDENTIFIER", "IDENTIFIER",
  "GLOBALVARIDENTIFIER", "NUMBER", "STRING", "DOUBLE", "TRUE_KEYWORD",
  "FALSE_KEYWORD", "IF", "ELSE", "FOR", "BREAK", "TRY", "EXCEPT", "THROW",
  "IMPORT", "MODULE", "USE", "CONTINUE", "RETURN", "WHILE", "NULL_KEYWORD",
  "POWER_OP", "NEQ_OP", "OR_OP", "AND_OP", "GE_OP", "LE_OP", "EQ_OP",
  "ADD_ASSIGN", "SUB_ASSIGN", "DIV_ASSIGN", "MUL_ASSIGN", "ASSIGN_ASSIGN",
  "MOD_ASSIGN", "AND_ASSIGN", "OR_ASSIGN", "XOR_ASSIGN", "SHIFT_LEFT_OP",
  "SHIFT_RIGHT_OP", "WMAIN", "DEF", "VAR", "IN", "ARRAYSECTION", "DICT_OP",
  "TYPEOF", "CONST", "MMRT", "'='", "'-'", "'+'", "'*'", "'/'", "';'",
  "':'", "','", "'{'", "'}'", "'('", "')'", "'['", "']'", "'.'", "'!'",
  "'%'", "'<'", "'>'", "'&'", "'^'", "'|'", "'?'", "$accept", "start",
  "run_statement", "wmain_definition", "functiondefinition",
  "global_initialization", "function_parameter_list", "function_parameter",
  "funciton_codeblock_statement", "function_arguments",
  "primary_expression", "list_element", "statement_list",
  "prefix_expression", "power_expression", "multiplicative_expression",
  "subtraction_expression", "additive_expression", "shift_left_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "indentifier_expression",
  "assignment_expression_definition", "expression_definition",
  "array_declare", "dict_expression", "dict_statement", "dict_declare",
  "Initialization_Definition", "initialization_list",
  "initialization_expression", "statement", "expression_statement",
  "selection_statement", "iteration_statement", "built-intype_declare",
  "assignment_operator", "if_statement", "while_statement",
  "for_statement", "jump_statement", "try_parameter_list", "try_parameter",
  "try_statement", "import_expresson", "import_expression_list",
  "use_expression_list", "moduledefine", "modulestatementlist",
  "modulestatement", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,    61,    45,    43,    42,    47,    59,    58,    44,
     123,   125,    40,    41,    91,    93,    46,    33,    37,    60,
      62,    38,    94,   124,    63
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    75,    76,    76,    77,    77,    77,    77,    78,    79,
      79,    80,    80,    81,    81,    81,    81,    82,    82,    83,
      83,    84,    84,    85,    85,    85,    85,    85,    85,    85,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    87,    87,    88,    88,    88,    88,    89,    89,
      90,    90,    90,    90,    91,    91,    92,    92,    93,    93,
      94,    94,    95,    95,    95,    95,    95,    96,    96,    96,
      97,    97,    98,    98,    99,    99,   100,   100,   101,   101,
     102,   102,   103,   103,   104,   104,   105,   105,   106,   106,
     107,   108,   108,   109,   109,   110,   110,   110,   110,   111,
     111,   112,   113,   113,   113,   113,   113,   113,   114,   114,
     115,   115,   116,   116,   117,   117,   117,   117,   117,   117,
     117,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     119,   119,   120,   121,   122,   122,   122,   122,   122,   123,
     123,   124,   124,   125,   126,   127,   127,   128,   128,   129,
     129,   130,   130,   131,   131
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     3,     1,     4,     5,
       4,     2,     2,     1,     3,     2,     4,     1,     3,     3,
       2,     1,     3,     1,     1,     1,     1,     3,     4,     4,
       1,     4,     5,     5,     6,     3,     6,     5,     4,     3,
       3,     3,     1,     2,     1,     2,     2,     2,     1,     3,
       1,     3,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     5,     1,     1,     1,     3,     1,     3,     3,     2,
       3,     1,     3,     3,     2,     1,     3,     2,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     7,     5,     7,     2,     2,     2,     3,     3,     1,
       2,     1,     3,     6,     3,     1,     3,     1,     3,     5,
       4,     1,     2,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     2,     7,     4,     5,
     145,     0,     0,   147,     0,     0,     1,     3,   144,     0,
       0,     6,     0,    13,     0,    17,     0,   146,    82,   120,
      83,   114,   115,   116,   117,   118,   119,     0,     0,     0,
       0,     0,     0,   150,     0,     0,     0,   153,   154,    30,
      44,    48,    50,    54,    56,    58,    60,    62,    67,    70,
      72,    74,    76,    78,    80,    84,    26,    86,     0,    24,
      23,     0,    25,     0,   151,   148,     0,    15,     0,     0,
       8,     0,     0,    95,    99,   101,     0,     0,    45,    46,
     120,    94,     0,    91,     0,    89,     0,    47,     0,     0,
       0,     0,   125,   126,   123,   122,   121,   124,   127,   129,
     128,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    12,     0,    11,   149,   152,    14,     0,    18,
       0,     0,     0,     0,     0,     0,     0,     0,   108,    20,
     102,     0,     0,     0,    42,   106,   104,   105,   110,   113,
     112,   103,   111,     0,    97,     0,     0,     0,     0,     0,
      27,     0,    93,    88,    35,    39,     0,    21,     0,     0,
      41,    40,    85,    49,    48,    51,    52,    53,    55,    57,
      59,    61,    66,    65,    63,    64,    69,    68,    71,    73,
      75,    77,    79,     0,    87,    16,     0,     0,   135,     0,
       0,   134,   136,     0,     0,    19,    43,   109,   107,     0,
      10,     0,    96,   100,    28,    29,    90,     0,    92,     0,
      38,     0,     0,    31,     0,     0,     0,     0,     0,   138,
     137,     0,     9,    98,    22,    33,    32,     0,    37,     0,
      81,     0,     0,     0,     0,    34,    36,   130,     0,   139,
       0,   141,     0,   132,     0,     0,   140,     0,   143,   131,
     133,   142
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,    47,    48,    25,    26,   150,   176,
      49,    50,   151,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    93,    94,    70,    84,    85,    71,   154,   155,
     156,   157,    72,   111,   158,   159,   160,   161,   261,   262,
     162,     8,    11,    14,     9,    73,    74
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -139
static const yytype_int16 yypact[] =
{
      -5,    15,    27,    98,    49,    10,  -139,  -139,  -139,  -139,
    -139,   -40,    25,  -139,    -8,     5,  -139,  -139,  -139,   112,
     286,  -139,   114,    87,   122,  -139,    53,  -139,  -139,  -139,
    -139,  -139,  -139,  -139,  -139,  -139,  -139,   125,     2,    76,
      77,   624,   624,  -139,    57,   373,   624,  -139,  -139,  -139,
     -30,   265,   106,   -33,    83,   107,   121,   123,    18,   -10,
      92,    94,    95,   139,   -16,  -139,  -139,  -139,    21,  -139,
    -139,   113,  -139,   351,  -139,  -139,   624,   133,     5,   197,
    -139,   115,    81,   135,  -139,   116,   624,   624,  -139,  -139,
     126,  -139,   117,  -139,   -39,  -139,   -20,  -139,   172,   438,
     460,   110,  -139,  -139,  -139,  -139,  -139,  -139,  -139,  -139,
    -139,   624,   624,   624,   624,   624,   624,   624,   624,   624,
     624,   624,   624,   624,   624,   624,   624,   624,   624,   624,
     624,   624,  -139,   624,  -139,  -139,  -139,  -139,   624,  -139,
     119,   120,   127,   128,   624,   130,   472,   132,  -139,  -139,
    -139,   262,    40,   138,  -139,  -139,  -139,  -139,  -139,  -139,
    -139,  -139,  -139,    22,   141,   624,     2,   129,   134,   624,
    -139,   175,  -139,  -139,  -139,  -139,    -9,  -139,   624,   -38,
     136,  -139,  -139,  -139,  -139,   106,   106,   106,   -33,    83,
     107,   121,   123,   123,   123,   123,    18,    18,   -10,    92,
      94,    95,   139,    69,  -139,  -139,   624,   140,  -139,   167,
      41,  -139,  -139,    46,   624,  -139,  -139,  -139,  -139,    53,
    -139,   624,  -139,  -139,  -139,  -139,  -139,   126,  -139,   624,
    -139,   131,   537,  -139,   559,   624,    12,   144,   155,  -139,
    -139,    14,  -139,  -139,  -139,  -139,  -139,   150,  -139,    20,
    -139,   128,   624,     9,   128,  -139,  -139,   187,   153,  -139,
     214,  -139,    74,  -139,   128,   128,  -139,     9,  -139,  -139,
    -139,  -139
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -139,  -139,   217,  -139,  -139,  -139,   145,    61,   -26,  -138,
    -139,  -139,  -139,    28,   -73,   111,   109,   137,   118,   -29,
      35,   103,   104,   102,   105,   148,  -139,    -3,   -36,   -43,
     -42,  -139,    62,  -139,  -139,    75,  -139,   -75,    84,  -139,
    -139,  -139,  -139,  -139,  -139,  -139,  -139,  -139,   -27,  -139,
    -139,  -139,  -139,  -139,  -139,  -139,   170
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      80,    92,    83,    96,   153,    28,   210,    30,    23,   232,
      16,   130,   259,     1,     2,     3,   124,    18,    98,    10,
     171,   125,   113,   114,   172,    23,    19,   233,     1,     2,
       3,    12,    99,   137,   100,   115,   101,   152,     4,   133,
     185,   186,   187,   167,   168,   173,   164,   120,   121,    21,
     229,    22,    82,     4,   230,    24,   177,   179,   131,   260,
      28,    90,    30,    31,    32,    33,    34,    35,   182,    88,
      89,   133,    24,   133,    97,   251,   153,   254,   132,   229,
     133,    36,    79,   256,    28,    20,    30,   122,   123,   203,
     204,   192,   193,   194,   195,   205,   249,   217,   239,   133,
     229,   177,    13,   240,   213,   133,    39,    15,    40,   152,
      41,    42,    78,    79,   180,   181,    27,   209,    75,    44,
      91,    45,   222,    76,    46,    77,   226,   235,   133,    81,
      83,   112,   237,   267,    79,   231,   116,   220,    86,    87,
     183,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   196,
     197,   117,   118,   126,   236,   119,   127,   129,   128,   138,
     134,   165,   241,   163,   169,   166,   174,   221,   243,   227,
     170,   206,   207,   238,   208,    38,   244,   211,    79,   247,
     252,   177,   224,   242,   214,   218,   245,   225,   234,   264,
      28,    29,    30,    31,    32,    33,    34,    35,   140,   258,
     141,   142,   143,   253,   144,   255,   265,   266,   145,   146,
     147,    36,    17,   139,   219,   257,   189,   188,   263,   198,
     200,   199,   250,   228,   201,   216,   268,   191,   269,   270,
     271,   223,    38,   136,     0,     0,    39,     0,    40,     0,
      41,    42,     0,     0,   148,   190,     0,    79,   149,    44,
       0,    45,     0,   184,    46,    28,    29,    30,    31,    32,
      33,    34,    35,   140,     0,   141,   142,   143,   202,   144,
       0,     0,     0,   145,   146,   147,    36,     0,     0,    28,
      29,    30,    31,    32,    33,    34,    35,   102,   103,   104,
     105,   106,   107,   108,   109,   110,     0,    38,     0,     0,
      36,    39,     0,    40,     0,    41,    42,     0,     0,   148,
       0,     0,    79,   215,    44,     0,    45,     0,     0,    46,
      37,    38,     0,     0,     0,    39,     0,    40,     0,    41,
      42,     0,     0,     0,     0,     0,     0,    43,    44,     0,
      45,     0,     0,    46,    28,    29,    30,    31,    32,    33,
      34,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    36,    28,    29,    30,    31,
      32,    33,    34,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,    38,    36,     0,     0,
      39,     0,    40,     0,    41,    42,     0,     0,     0,     0,
       0,     0,   135,    44,     0,    45,     0,     0,    46,     0,
       0,     0,    39,     0,    40,     0,    41,    42,     0,     0,
       0,     0,     0,     0,     0,    44,     0,    45,    95,     0,
      46,    28,    29,    30,    31,    32,    33,    34,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,    28,    29,    30,    31,    32,    33,    34,
      35,     0,     0,     0,     0,    28,    29,    30,    31,    32,
      33,    34,    35,     0,    36,     0,     0,    39,     0,    40,
       0,    41,    42,     0,     0,     0,    36,     0,     0,     0,
      44,   175,    45,     0,     0,    46,     0,   178,     0,    39,
       0,    40,     0,    41,    42,     0,     0,     0,     0,     0,
       0,    39,    44,    40,    45,    41,    42,    46,     0,   212,
       0,     0,     0,     0,    44,     0,    45,     0,     0,    46,
      28,    29,    30,    31,    32,    33,    34,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    36,    28,    29,    30,    31,    32,    33,    34,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    36,     0,     0,    39,     0,    40,     0,
      41,    42,     0,     0,     0,     0,     0,     0,     0,    44,
       0,    45,   246,     0,    46,     0,     0,     0,    39,     0,
      40,     0,    41,    42,     0,     0,     0,     0,     0,     0,
       0,    44,   248,    45,     0,     0,    46,    28,    29,    30,
      31,    32,    33,    34,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,     0,    40,     0,    41,    42,     0,
       0,     0,     0,     0,     0,     0,    44,     0,    45,     0,
       0,    46
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-139)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      26,    44,    38,    45,    79,     3,   144,     5,     3,    47,
       0,    27,     3,    18,    19,    20,    26,    57,    48,     4,
      59,    31,    55,    56,    63,     3,    66,    65,    18,    19,
      20,     4,    62,    76,    64,    68,    66,    79,    43,    59,
     113,   114,   115,    86,    87,    65,    82,    29,    30,    57,
      59,    59,    50,    43,    63,    50,    99,   100,    74,    50,
       3,     4,     5,     6,     7,     8,     9,    10,   111,    41,
      42,    59,    50,    59,    46,    63,   151,    63,    57,    59,
      59,    24,    60,    63,     3,    60,     5,    69,    70,   131,
     133,   120,   121,   122,   123,   138,   234,    57,    57,    59,
      59,   144,     4,    57,   146,    59,    49,    58,    51,   151,
      53,    54,    59,    60,     4,     5,     4,   143,     4,    62,
      63,    64,   165,    36,    67,     3,   169,    58,    59,     4,
     166,    25,   207,    59,    60,   178,    53,   163,    62,    62,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   124,
     125,    54,    41,    71,   206,    42,    72,    28,    73,    36,
      57,    36,   214,    58,    48,    59,     4,    36,   221,     4,
      63,    62,    62,    16,    57,    45,   229,    57,    60,   232,
      46,   234,    63,   219,    62,    57,    65,    63,    62,    12,
       3,     4,     5,     6,     7,     8,     9,    10,    11,   252,
      13,    14,    15,    58,    17,    65,    63,     3,    21,    22,
      23,    24,     5,    78,   163,   251,   117,   116,   254,   126,
     128,   127,   235,   171,   129,   151,   262,   119,   264,   265,
     267,   166,    45,    73,    -1,    -1,    49,    -1,    51,    -1,
      53,    54,    -1,    -1,    57,   118,    -1,    60,    61,    62,
      -1,    64,    -1,   235,    67,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    13,    14,    15,   130,    17,
      -1,    -1,    -1,    21,    22,    23,    24,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    -1,    45,    -1,    -1,
      24,    49,    -1,    51,    -1,    53,    54,    -1,    -1,    57,
      -1,    -1,    60,    61,    62,    -1,    64,    -1,    -1,    67,
      44,    45,    -1,    -1,    -1,    49,    -1,    51,    -1,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    -1,
      64,    -1,    -1,    67,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    24,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    24,    -1,    -1,
      49,    -1,    51,    -1,    53,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    62,    -1,    64,    -1,    -1,    67,    -1,
      -1,    -1,    49,    -1,    51,    -1,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    -1,    64,    65,    -1,
      67,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    24,    -1,    -1,    49,    -1,    51,
      -1,    53,    54,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      62,    63,    64,    -1,    -1,    67,    -1,    47,    -1,    49,
      -1,    51,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    62,    51,    64,    53,    54,    67,    -1,    57,
      -1,    -1,    -1,    -1,    62,    -1,    64,    -1,    -1,    67,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    49,    -1,    51,    -1,
      53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    64,    65,    -1,    67,    -1,    -1,    -1,    49,    -1,
      51,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    64,    -1,    -1,    67,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    51,    -1,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,    64,    -1,
      -1,    67
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    19,    20,    43,    76,    77,    78,   126,   129,
       4,   127,     4,     4,   128,    58,     0,    77,    57,    66,
      60,    57,    59,     3,    50,    81,    82,     4,     3,     4,
       5,     6,     7,     8,     9,    10,    24,    44,    45,    49,
      51,    53,    54,    61,    62,    64,    67,    79,    80,    85,
      86,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     109,   112,   117,   130,   131,     4,    36,     3,    59,    60,
      83,     4,    50,   103,   110,   111,    62,    62,    88,    88,
       4,    63,   104,   107,   108,    65,   105,    88,    48,    62,
      64,    66,    32,    33,    34,    35,    36,    37,    38,    39,
      40,   118,    25,    55,    56,    68,    53,    54,    41,    42,
      29,    30,    69,    70,    26,    31,    71,    72,    73,    28,
      27,    74,    57,    59,    57,    61,   131,   104,    36,    81,
      11,    13,    14,    15,    17,    21,    22,    23,    57,    61,
      83,    87,   105,   112,   113,   114,   115,   116,   119,   120,
     121,   122,   125,    58,   103,    36,    59,   104,   104,    48,
      63,    59,    63,    65,     4,    63,    84,   104,    47,   104,
       4,     5,   104,    88,    88,    89,    89,    89,    90,    91,
      92,    93,    94,    94,    94,    94,    95,    95,    96,    97,
      98,    99,   100,   105,   104,   104,    62,    62,    57,    83,
      84,    57,    57,   105,    62,    61,   113,    57,    57,    82,
      83,    36,   104,   110,    63,    63,   104,     4,   107,    59,
      63,   104,    47,    65,    62,    58,   105,   112,    16,    57,
      57,   105,    83,   104,   104,    65,    65,   104,    63,    84,
     102,    63,    46,    58,    63,    65,    63,    83,   104,     3,
      50,   123,   124,    83,    12,    63,     3,    59,    83,    83,
      83,   123
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 8:
/* Line 1792 of yacc.c  */
#line 120 "../support/flexbison/menthol-bison.y"
    {
					StatementList *ls = (StatementList*)parm;
         			FunctionDefinition* fd= new FunctionDefinition("_mmain",MNT_MainFunction);
					fd->AddChilder((yyvsp[(3) - (4)].vStatement));
					fd->AddChilder((yyvsp[(4) - (4)].vStatement));
					ls->AddFunction("_mmain");
					ls->AddMainModuleList(fd);
				}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 132 "../support/flexbison/menthol-bison.y"
    {
						StatementList *ls = (StatementList*)parm;		
						ls->AddStringConstant(string((yyvsp[(2) - (5)].vSTRING)));		
						(yyval.vStatement)= new FunctionDefinition((yyvsp[(2) - (5)].vSTRING),MNT_FunctionDefinition);
						(yyval.vStatement)->AddChilder((yyvsp[(4) - (5)].vStatement));
						(yyval.vStatement)->AddChilder((yyvsp[(5) - (5)].vStatement));
						ls->AddFunction((yyvsp[(2) - (5)].vSTRING));
				  }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 141 "../support/flexbison/menthol-bison.y"
    {
						StatementList *ls = (StatementList*)parm;		
						ls->AddStringConstant(string((yyvsp[(2) - (4)].vSTRING)));		
						(yyval.vStatement)= new FunctionDefinition((yyvsp[(2) - (4)].vSTRING),MNT_FunctionDefinition);
						(yyval.vStatement)->AddChilder(0);
						(yyval.vStatement)->AddChilder((yyvsp[(4) - (4)].vStatement));
						ls->AddFunction((yyvsp[(2) - (4)].vSTRING));
				  }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 154 "../support/flexbison/menthol-bison.y"
    { 
						/*在程序内把变量作用域改为GLOBAL*/
						InitializationList* list = static_cast<InitializationList*>((yyvsp[(1) - (2)].vStatement));
						list->ModfiyMemberScope(GLOBAL);
				     }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 159 "../support/flexbison/menthol-bison.y"
    {
							(yyval.vStatement) = (yyvsp[(1) - (2)].vStatement);
				     }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 164 "../support/flexbison/menthol-bison.y"
    { (yyval.vStatement) = new FunctionParameter((yyvsp[(1) - (1)].vSTRING),false);}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 166 "../support/flexbison/menthol-bison.y"
    {
							(yyval.vStatement) = new FunctionParameter((yyvsp[(1) - (3)].vSTRING),(yyvsp[(3) - (3)].vStatement),false);
					   }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 170 "../support/flexbison/menthol-bison.y"
    { (yyval.vStatement) = new FunctionParameter((yyvsp[(2) - (2)].vSTRING),true);}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 172 "../support/flexbison/menthol-bison.y"
    {
							(yyval.vStatement) = new FunctionParameter((yyvsp[(2) - (4)].vSTRING),(yyvsp[(4) - (4)].vStatement),true);
					   }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 179 "../support/flexbison/menthol-bison.y"
    {
				   		(yyval.vStatement) = new FunctionParameterStatement();
				   		(yyval.vStatement)->AddChilder((yyvsp[(1) - (1)].vStatement));
				   }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 184 "../support/flexbison/menthol-bison.y"
    {
						(yyvsp[(1) - (3)].vStatement)->AddChilder((yyvsp[(3) - (3)].vStatement));
				   }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 189 "../support/flexbison/menthol-bison.y"
    {								
									(yyval.vStatement) = new CodeBlockStatement();
									(yyval.vStatement)->AddChilder((yyvsp[(2) - (3)].vStatement));
								}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 193 "../support/flexbison/menthol-bison.y"
    {
								(yyval.vStatement) = new NopExpression();
							}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 201 "../support/flexbison/menthol-bison.y"
    {
						(yyval.vStatement) =new FunctionArguments();
						if((yyvsp[(1) - (1)].vStatement)!=0){
							(yyval.vStatement)->AddChilder((yyvsp[(1) - (1)].vStatement));
						}
				  }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 208 "../support/flexbison/menthol-bison.y"
    {
						if((yyvsp[(3) - (3)].vStatement)!=0){
							(yyvsp[(1) - (3)].vStatement)->AddChilder((yyvsp[(3) - (3)].vStatement));
						}
				  }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 218 "../support/flexbison/menthol-bison.y"
    {
					(yyval.vStatement) = (yyvsp[(1) - (1)].vStatement);
				   }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 221 "../support/flexbison/menthol-bison.y"
    {
					(yyval.vStatement) = (yyvsp[(1) - (1)].vStatement);
				   }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 224 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) = (yyvsp[(1) - (1)].vStatement);}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 225 "../support/flexbison/menthol-bison.y"
    {
					(yyval.vStatement)=(yyvsp[(1) - (1)].vStatement);
				   }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 228 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) = (yyvsp[(2) - (3)].vStatement);}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 229 "../support/flexbison/menthol-bison.y"
    {
						(yyval.vStatement) = new TypeOfExpression((yyvsp[(3) - (4)].vStatement));
				   }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 232 "../support/flexbison/menthol-bison.y"
    {
						(yyval.vStatement) = new MmrtExpression((yyvsp[(3) - (4)].vStatement));
				   }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 239 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) = (yyvsp[(1) - (1)].vStatement);}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 241 "../support/flexbison/menthol-bison.y"
    {
						ArrayElement* ad = new ArrayElement((yyvsp[(1) - (4)].vStatement),(yyvsp[(3) - (4)].vStatement),0);
						ad->SetOpt(1);
						(yyval.vStatement) = ad;
				}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 247 "../support/flexbison/menthol-bison.y"
    {
						ArrayElement* ad = new ArrayElement((yyvsp[(1) - (5)].vStatement),(yyvsp[(3) - (5)].vStatement),1);
						ad->SetOpt(1);
						(yyval.vStatement) = ad;
				}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 253 "../support/flexbison/menthol-bison.y"
    {
						ArrayElement* ad = new ArrayElement((yyvsp[(1) - (5)].vStatement),(yyvsp[(4) - (5)].vStatement),2);
						ad->SetOpt(1);
						(yyval.vStatement) = ad;
				}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 259 "../support/flexbison/menthol-bison.y"
    {
					ArrayElement* ad = new ArrayElement((yyvsp[(1) - (6)].vStatement),(yyvsp[(3) - (6)].vStatement),(yyvsp[(5) - (6)].vStatement));
					ad->SetOpt(1);
					(yyval.vStatement) = ad;

				}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 266 "../support/flexbison/menthol-bison.y"
    {
					DictElemenet* ad = new DictElemenet((yyvsp[(1) - (3)].vStatement),(yyvsp[(3) - (3)].vSTRING));
					ad->SetOpt(1);
					(yyval.vStatement) = ad;
				}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 273 "../support/flexbison/menthol-bison.y"
    {
				ModuleExpresson* pae =new ModuleExpresson((yyvsp[(1) - (6)].vStatement),(yyvsp[(3) - (6)].vSTRING),(yyvsp[(5) - (6)].vStatement),1);
				StatementList *ls = (StatementList*)parm;		
				ls->AddStringConstant(string((yyvsp[(3) - (6)].vSTRING)));	
				(yyval.vStatement) = pae;
				}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 280 "../support/flexbison/menthol-bison.y"
    {
				ModuleExpresson* pae =new ModuleExpresson((yyvsp[(1) - (5)].vStatement),(yyvsp[(3) - (5)].vSTRING),0,1);
				StatementList *ls = (StatementList*)parm;		
				ls->AddStringConstant(string((yyvsp[(3) - (5)].vSTRING)));	
				pae->SetNType(MNT_ModuleFunCall);
				(yyval.vStatement) = pae;
				}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 288 "../support/flexbison/menthol-bison.y"
    {
					StatementList *ls = (StatementList*)parm;
					(yyval.vStatement) = new FunctionCall((yyvsp[(1) - (4)].vStatement),(yyvsp[(3) - (4)].vStatement));
					(yyval.vStatement)->AddChilder((yyvsp[(3) - (4)].vStatement));
				}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 294 "../support/flexbison/menthol-bison.y"
    {
					StatementList *ls = (StatementList*)parm;
					(yyval.vStatement) = new FunctionCall((yyvsp[(1) - (3)].vStatement),new FunctionArguments());
				}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 299 "../support/flexbison/menthol-bison.y"
    {
					ModuleExpresson* pae =new ModuleExpresson((yyvsp[(1) - (3)].vStatement),(yyvsp[(3) - (3)].vSTRING),0,2);
					StatementList *ls = (StatementList*)parm;		
					ls->AddStringConstant(string((yyvsp[(3) - (3)].vSTRING)));	
					(yyval.vStatement) = pae;
				}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 306 "../support/flexbison/menthol-bison.y"
    {
					ModuleExpresson* pae =new ModuleExpresson((yyvsp[(1) - (3)].vStatement),(yyvsp[(3) - (3)].vSTRING),0,3);
					StatementList *ls = (StatementList*)parm;		
					ls->AddStringConstant(string((yyvsp[(3) - (3)].vSTRING)));	
					pae->SetNType(MNT_ModuleFunctionDefinition);
					(yyval.vStatement) = pae;
				}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 318 "../support/flexbison/menthol-bison.y"
    {
					 (yyval.vStatement) =new ExpressionStatement();
					 if((yyvsp[(1) - (1)].vStatement)!=0){
						(yyval.vStatement)->AddChilder((yyvsp[(1) - (1)].vStatement));
					  }
			   }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 325 "../support/flexbison/menthol-bison.y"
    {
				    if((yyvsp[(2) - (2)].vStatement)!=0){
						(yyval.vStatement)->AddChilder((yyvsp[(2) - (2)].vStatement));
					}
			   }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 333 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) =(yyvsp[(1) - (1)].vStatement);}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 335 "../support/flexbison/menthol-bison.y"
    {
						(yyval.vStatement) = new MinusExpression((yyvsp[(2) - (2)].vStatement));
				  }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 338 "../support/flexbison/menthol-bison.y"
    {
						(yyval.vStatement) = new PlusExpression((yyvsp[(2) - (2)].vStatement));
			      }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 341 "../support/flexbison/menthol-bison.y"
    {
						(yyval.vStatement) = new InverterExpression((yyvsp[(2) - (2)].vStatement));
			      }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 346 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) =(yyvsp[(1) - (1)].vStatement);}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 348 "../support/flexbison/menthol-bison.y"
    {
					(yyval.vStatement) = new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),"**",(yyvsp[(3) - (3)].vStatement));
				}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 354 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) =(yyvsp[(1) - (1)].vStatement);}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 356 "../support/flexbison/menthol-bison.y"
    {
							(yyval.vStatement) = new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),"*",(yyvsp[(3) - (3)].vStatement));
						}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 360 "../support/flexbison/menthol-bison.y"
    {
							(yyval.vStatement) = new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),"/",(yyvsp[(3) - (3)].vStatement));
						}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 364 "../support/flexbison/menthol-bison.y"
    {
							(yyval.vStatement) = new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),"%",(yyvsp[(3) - (3)].vStatement));
						}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 369 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) =(yyvsp[(1) - (1)].vStatement);}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 371 "../support/flexbison/menthol-bison.y"
    {
						(yyval.vStatement) = new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),"-",(yyvsp[(3) - (3)].vStatement));
					  }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 376 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) =(yyvsp[(1) - (1)].vStatement);}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 378 "../support/flexbison/menthol-bison.y"
    {
						(yyval.vStatement) = new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),"+",(yyvsp[(3) - (3)].vStatement));
					}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 384 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) =(yyvsp[(1) - (1)].vStatement);}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 386 "../support/flexbison/menthol-bison.y"
    {
						(yyval.vStatement) = new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),"<<",(yyvsp[(3) - (3)].vStatement));
					 }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 392 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) =(yyvsp[(1) - (1)].vStatement);}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 394 "../support/flexbison/menthol-bison.y"
    {
					(yyval.vStatement) = new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),">>",(yyvsp[(3) - (3)].vStatement));
				}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 399 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) =(yyvsp[(1) - (1)].vStatement);}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 401 "../support/flexbison/menthol-bison.y"
    {
							(yyval.vStatement) = new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),"<",(yyvsp[(3) - (3)].vStatement));
						}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 405 "../support/flexbison/menthol-bison.y"
    {
							(yyval.vStatement) = new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),">",(yyvsp[(3) - (3)].vStatement));
						}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 409 "../support/flexbison/menthol-bison.y"
    {
							(yyval.vStatement) = new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),"<=",(yyvsp[(3) - (3)].vStatement));
						}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 413 "../support/flexbison/menthol-bison.y"
    {
							(yyval.vStatement) = new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),">=",(yyvsp[(3) - (3)].vStatement));
						}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 418 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) =(yyvsp[(1) - (1)].vStatement);}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 420 "../support/flexbison/menthol-bison.y"
    {
						(yyval.vStatement) = new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),"==",(yyvsp[(3) - (3)].vStatement));
					}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 424 "../support/flexbison/menthol-bison.y"
    {
						(yyval.vStatement) = new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),"<>",(yyvsp[(3) - (3)].vStatement));
					}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 429 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) =(yyvsp[(1) - (1)].vStatement);}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 431 "../support/flexbison/menthol-bison.y"
    {
					(yyval.vStatement) =new LogiceEpressionDefintion((yyvsp[(1) - (3)].vStatement),"&",(yyvsp[(3) - (3)].vStatement));
				}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 436 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) =(yyvsp[(1) - (1)].vStatement);}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 438 "../support/flexbison/menthol-bison.y"
    {
							(yyval.vStatement) =new LogiceEpressionDefintion((yyvsp[(1) - (3)].vStatement),"^",(yyvsp[(3) - (3)].vStatement));
						}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 443 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) =(yyvsp[(1) - (1)].vStatement);}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 445 "../support/flexbison/menthol-bison.y"
    {
							(yyval.vStatement) =new LogiceEpressionDefintion((yyvsp[(1) - (3)].vStatement),"|",(yyvsp[(3) - (3)].vStatement));
						}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 450 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) =(yyvsp[(1) - (1)].vStatement);}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 452 "../support/flexbison/menthol-bison.y"
    {
							(yyval.vStatement) =new LogiceEpressionDefintion((yyvsp[(1) - (3)].vStatement),"&&",(yyvsp[(3) - (3)].vStatement));
						}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 457 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) =(yyvsp[(1) - (1)].vStatement);}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 459 "../support/flexbison/menthol-bison.y"
    {
						(yyval.vStatement) =new LogiceEpressionDefintion((yyvsp[(1) - (3)].vStatement),"||",(yyvsp[(3) - (3)].vStatement));
					 }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 464 "../support/flexbison/menthol-bison.y"
    {
						(yyval.vStatement) = (yyvsp[(1) - (1)].vStatement);
					   }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 468 "../support/flexbison/menthol-bison.y"
    {
								(yyval.vStatement) = new TernaryExpression((yyvsp[(1) - (5)].vStatement),(yyvsp[(3) - (5)].vStatement),(yyvsp[(5) - (5)].vStatement));
					   }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 475 "../support/flexbison/menthol-bison.y"
    {
							(yyval.vStatement) =new VarIdentIfier((yyvsp[(1) - (1)].vSTRING));
					  }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 478 "../support/flexbison/menthol-bison.y"
    {
 						StatementList *ls = (StatementList*)parm;
						ls->AddStringConstant(string((yyvsp[(1) - (1)].vSTRING)));
 						(yyval.vStatement) = new VarIdentIfier((char*)(yyvsp[(1) - (1)].vSTRING).c_str());}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 487 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) = (yyvsp[(1) - (1)].vStatement);}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 489 "../support/flexbison/menthol-bison.y"
    {
									if((yyvsp[(2) - (3)].vSTRING)=="+="){
										(yyval.vStatement) = new AssignmentDefinition((yyvsp[(1) - (3)].vStatement),"=",new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),"+",(yyvsp[(3) - (3)].vStatement)));
									}
									if((yyvsp[(2) - (3)].vSTRING)=="-="){
										(yyval.vStatement) = new AssignmentDefinition((yyvsp[(1) - (3)].vStatement),"=",new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),"-",(yyvsp[(3) - (3)].vStatement)));
									}
									if((yyvsp[(2) - (3)].vSTRING)=="/="){
										(yyval.vStatement) = new AssignmentDefinition((yyvsp[(1) - (3)].vStatement),"=",new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),"/",(yyvsp[(3) - (3)].vStatement)));
									}
									if((yyvsp[(2) - (3)].vSTRING)=="*="){
										(yyval.vStatement) = new AssignmentDefinition((yyvsp[(1) - (3)].vStatement),"=",new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),"*",(yyvsp[(3) - (3)].vStatement)));
									}
									if((yyvsp[(2) - (3)].vSTRING)=="%="){
										(yyval.vStatement) = new AssignmentDefinition((yyvsp[(1) - (3)].vStatement),"=",new ArithmeticExpressionDefinition((yyvsp[(1) - (3)].vStatement),"%",(yyvsp[(3) - (3)].vStatement)));
									}
									if((yyvsp[(2) - (3)].vSTRING)=="&="){
										(yyval.vStatement) = new AssignmentDefinition((yyvsp[(1) - (3)].vStatement),"=",new LogiceEpressionDefintion((yyvsp[(1) - (3)].vStatement),"&",(yyvsp[(3) - (3)].vStatement)));
									}
									if((yyvsp[(2) - (3)].vSTRING)=="|="){
										(yyval.vStatement) = new AssignmentDefinition((yyvsp[(1) - (3)].vStatement),"=",new LogiceEpressionDefintion((yyvsp[(1) - (3)].vStatement),"|",(yyvsp[(3) - (3)].vStatement)));
									}
									if((yyvsp[(2) - (3)].vSTRING)=="^="){
										(yyval.vStatement) = new AssignmentDefinition((yyvsp[(1) - (3)].vStatement),"=",new LogiceEpressionDefintion((yyvsp[(1) - (3)].vStatement),"^",(yyvsp[(3) - (3)].vStatement)));
									}
									if((yyvsp[(2) - (3)].vSTRING)=="="){
										AssignmentDefinition* ad = new AssignmentDefinition((yyvsp[(1) - (3)].vStatement),(yyvsp[(2) - (3)].vSTRING),(yyvsp[(3) - (3)].vStatement),true);
										(yyval.vStatement) = ad;
									}								
								}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 522 "../support/flexbison/menthol-bison.y"
    {
							(yyval.vStatement) =new ExpressionList();
							(yyval.vStatement)->AddChilder((yyvsp[(1) - (1)].vStatement));
					   }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 527 "../support/flexbison/menthol-bison.y"
    {
							   (yyvsp[(1) - (3)].vStatement)->AddChilder((yyvsp[(3) - (3)].vStatement));
					   }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 535 "../support/flexbison/menthol-bison.y"
    {
					(yyval.vStatement) = new ArrayDeclare((yyvsp[(2) - (3)].vStatement));
			   }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 539 "../support/flexbison/menthol-bison.y"
    {
					(yyval.vStatement) = new ArrayDeclare(new ExpressionList());
			   }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 545 "../support/flexbison/menthol-bison.y"
    {
					(yyval.vStatement) = new DictExpression((yyvsp[(1) - (3)].vSTRING),(yyvsp[(3) - (3)].vStatement));
				}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 551 "../support/flexbison/menthol-bison.y"
    {
					(yyval.vStatement) = new DictStatement();
					(yyval.vStatement)->AddChilder((yyvsp[(1) - (1)].vStatement));
			   }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 556 "../support/flexbison/menthol-bison.y"
    {
					(yyvsp[(1) - (3)].vStatement)->AddChilder((yyvsp[(3) - (3)].vStatement));
			   }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 564 "../support/flexbison/menthol-bison.y"
    { (yyval.vStatement) = (yyvsp[(2) - (3)].vStatement);}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 565 "../support/flexbison/menthol-bison.y"
    {
					(yyval.vStatement) = new DictStatement();
			}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 571 "../support/flexbison/menthol-bison.y"
    {
								 InitializationDefinition* ad = new InitializationDefinition((yyvsp[(1) - (1)].vStatement),0,false);
								 ad->ModfiyScope(LOCAL);
								 (yyval.vStatement) = ad;
							}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 576 "../support/flexbison/menthol-bison.y"
    {
									InitializationDefinition* ad = new InitializationDefinition((yyvsp[(1) - (3)].vStatement),(yyvsp[(3) - (3)].vStatement),false);
									ad->ModfiyScope(LOCAL);
									(yyval.vStatement) = ad;
							}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 581 "../support/flexbison/menthol-bison.y"
    {
									 InitializationDefinition* ad = new InitializationDefinition((yyvsp[(2) - (2)].vStatement),0,true);
									 ad->ModfiyScope(LOCAL);
									 (yyval.vStatement) = ad;
							}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 586 "../support/flexbison/menthol-bison.y"
    {
									InitializationDefinition* ad = new InitializationDefinition((yyvsp[(2) - (4)].vStatement),(yyvsp[(4) - (4)].vStatement),true);
									ad->ModfiyScope(LOCAL);
									(yyval.vStatement) = ad;
							}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 594 "../support/flexbison/menthol-bison.y"
    {
						(yyval.vStatement) = new InitializationList();
						(yyval.vStatement)->AddChilder((yyvsp[(1) - (1)].vStatement));
					}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 598 "../support/flexbison/menthol-bison.y"
    {
						(yyvsp[(1) - (3)].vStatement)->AddChilder((yyvsp[(3) - (3)].vStatement));
					}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 603 "../support/flexbison/menthol-bison.y"
    {						  
							(yyval.vStatement) = (yyvsp[(2) - (2)].vStatement);						  
						  }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 608 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) = (yyvsp[(1) - (1)].vStatement);}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 609 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) = (yyvsp[(1) - (1)].vStatement);}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 610 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) = (yyvsp[(1) - (1)].vStatement);}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 611 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) = (yyvsp[(1) - (1)].vStatement);}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 612 "../support/flexbison/menthol-bison.y"
    {
			(yyval.vStatement) = (yyvsp[(1) - (1)].vStatement);
		 }
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 615 "../support/flexbison/menthol-bison.y"
    {
			(yyval.vStatement) = (yyvsp[(1) - (2)].vStatement);
		 }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 621 "../support/flexbison/menthol-bison.y"
    {
						(yyval.vStatement) = 0;
					}
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 624 "../support/flexbison/menthol-bison.y"
    {
						(yyval.vStatement) = (yyvsp[(1) - (2)].vStatement);
					}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 630 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) = (yyvsp[(1) - (1)].vStatement);}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 631 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) = (yyvsp[(1) - (1)].vStatement);}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 634 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) = (yyvsp[(1) - (1)].vStatement);}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 635 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) = (yyvsp[(1) - (1)].vStatement);}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 640 "../support/flexbison/menthol-bison.y"
    {   					 
						BuiltinTypeDeclare* btd =new BuiltinTypeDeclare();
						btd->SetNumber((yyvsp[(1) - (1)].vINTEGER));
						(yyval.vStatement)= btd;
					 }
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 647 "../support/flexbison/menthol-bison.y"
    {
						
						BuiltinTypeDeclare* btd =new BuiltinTypeDeclare();
						btd->SetString((yyvsp[(1) - (1)].vSTRING));	
						(yyval.vStatement)= btd;
					 }
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 653 "../support/flexbison/menthol-bison.y"
    {
						 StatementList *ls = (StatementList*)parm;
						BuiltinTypeDeclare* btd =new BuiltinTypeDeclare();
						ls->AddDoubleConstant((yyvsp[(1) - (1)].vDOUBLE));
						btd->SetDouble((yyvsp[(1) - (1)].vDOUBLE));
						(yyval.vStatement)= btd;
					 }
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 660 "../support/flexbison/menthol-bison.y"
    {
						BuiltinTypeDeclare* btd =new BuiltinTypeDeclare();
						btd->SetBool(true);
						(yyval.vStatement)= btd;
					 }
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 666 "../support/flexbison/menthol-bison.y"
    {
						BuiltinTypeDeclare* btd =new BuiltinTypeDeclare();
						btd->SetBool(false);
						(yyval.vStatement)= btd;
					 }
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 671 "../support/flexbison/menthol-bison.y"
    {
						BuiltinTypeDeclare* btd =new BuiltinTypeDeclare();
						btd->SetNull();
						(yyval.vStatement)= btd;				 
					 }
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 676 "../support/flexbison/menthol-bison.y"
    {
						StatementList *ls = (StatementList*)parm;
						ls->AddStringConstant(string((yyvsp[(1) - (1)].vSTRING)));
						BuiltinTypeDeclare* btd =new BuiltinTypeDeclare();
						btd->SetFunctionPointerOrModule((yyvsp[(1) - (1)].vSTRING),1);
						(yyval.vStatement)= btd;
					 }
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 697 "../support/flexbison/menthol-bison.y"
    {
				 (yyval.vStatement) = new IfStatement(0);
				 (yyval.vStatement)->AddChilder((yyvsp[(3) - (5)].vStatement));
				 (yyval.vStatement)->AddChilder((yyvsp[(5) - (5)].vStatement));			 
			  }
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 703 "../support/flexbison/menthol-bison.y"
    {
					 (yyval.vStatement) = new IfStatement(1);
					 (yyval.vStatement)->AddChilder((yyvsp[(3) - (7)].vStatement));
					 (yyval.vStatement)->AddChilder((yyvsp[(5) - (7)].vStatement));
					 (yyval.vStatement)->AddChilder((yyvsp[(7) - (7)].vStatement));	 
			  }
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 714 "../support/flexbison/menthol-bison.y"
    {
					(yyval.vStatement) = new WhileStatement();
					(yyval.vStatement)->AddChilder((yyvsp[(3) - (5)].vStatement));
					(yyval.vStatement)->AddChilder((yyvsp[(5) - (5)].vStatement));
				}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 722 "../support/flexbison/menthol-bison.y"
    {
				  	(yyval.vStatement) = new ForStatement((yyvsp[(3) - (7)].vStatement),(yyvsp[(5) - (7)].vStatement),(yyvsp[(7) - (7)].vStatement));
			  }
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 727 "../support/flexbison/menthol-bison.y"
    {
					(yyval.vStatement) = new ContinueExpression();
			  }
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 730 "../support/flexbison/menthol-bison.y"
    {
					(yyval.vStatement) = new BreakExpression();
			  }
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 733 "../support/flexbison/menthol-bison.y"
    {
					(yyval.vStatement) =new ReturnExpression();
			  }
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 736 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) =new ReturnExpression((yyvsp[(2) - (3)].vStatement));}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 737 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) =new ThrowExpression((yyvsp[(2) - (3)].vStatement));}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 740 "../support/flexbison/menthol-bison.y"
    { (yyval.vStatement) = new TryParameter((yyvsp[(1) - (1)].vSTRING),false);}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 741 "../support/flexbison/menthol-bison.y"
    { (yyval.vStatement) = new TryParameter((yyvsp[(2) - (2)].vSTRING),true);}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 745 "../support/flexbison/menthol-bison.y"
    {
			   		(yyval.vStatement) = new TryParameterStatement();
			   		(yyval.vStatement)->AddChilder((yyvsp[(1) - (1)].vStatement));
			   }
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 750 "../support/flexbison/menthol-bison.y"
    {
					(yyvsp[(1) - (3)].vStatement)->AddChilder((yyvsp[(3) - (3)].vStatement));
			   }
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 756 "../support/flexbison/menthol-bison.y"
    {
				 	(yyval.vStatement) =new TryStatement((yyvsp[(2) - (6)].vStatement),(yyvsp[(5) - (6)].vStatement),(yyvsp[(6) - (6)].vStatement));
			  }
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 763 "../support/flexbison/menthol-bison.y"
    {
						StatementList *ls = (StatementList*)parm;	
						ImportPackagePath* ipp =static_cast<ImportPackagePath*>((yyvsp[(2) - (3)].vStatement));
						ls->SetCompileStructTable(new ImportPackageExpression(ipp->GetPath()));			
				 }
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 771 "../support/flexbison/menthol-bison.y"
    {
							(yyval.vStatement) =new ImportPackagePath((yyvsp[(1) - (1)].vSTRING));
					   }
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 775 "../support/flexbison/menthol-bison.y"
    {
							ImportPackagePath* ipp =static_cast<ImportPackagePath*>((yyvsp[(1) - (3)].vStatement));
							ipp->AddPathString((yyvsp[(3) - (3)].vSTRING));
					   }
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 783 "../support/flexbison/menthol-bison.y"
    {
						StatementList *ls = (StatementList*)parm;	
						ls->AddUseModuleList((yyvsp[(1) - (1)].vSTRING));
				   }
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 788 "../support/flexbison/menthol-bison.y"
    {
						StatementList *ls = (StatementList*)parm;	
						ls->AddUseModuleList((yyvsp[(3) - (3)].vSTRING));				   
				   }
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 795 "../support/flexbison/menthol-bison.y"
    {
					StatementList *ls = (StatementList*)parm;	
											
					ls->SetCompileStructTable(new ModuleDefine(string((yyvsp[(2) - (5)].vSTRING)),(yyvsp[(4) - (5)].vStatement)));		
			  }
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 801 "../support/flexbison/menthol-bison.y"
    {
					StatementList *ls = (StatementList*)parm;	
					ls->SetCompileStructTable(new ModuleDefine(string((yyvsp[(2) - (4)].vSTRING)),new ModuleStatementList()));		
			  }
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 808 "../support/flexbison/menthol-bison.y"
    {
						(yyval.vStatement) =new ModuleStatementList();
						if((yyvsp[(1) - (1)].vStatement)!=0){
							(yyval.vStatement)->AddChilder((yyvsp[(1) - (1)].vStatement));
						}
					}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 815 "../support/flexbison/menthol-bison.y"
    {
						if((yyvsp[(2) - (2)].vStatement)!=0){
							(yyvsp[(1) - (2)].vStatement)->AddChilder((yyvsp[(2) - (2)].vStatement));
						}
					}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 823 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) = (yyvsp[(1) - (1)].vStatement);}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 824 "../support/flexbison/menthol-bison.y"
    {(yyval.vStatement) = (yyvsp[(1) - (1)].vStatement);}
    break;


/* Line 1792 of yacc.c  */
#line 2934 "menthol-bison.tab.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 826 "../support/flexbison/menthol-bison.y"

 