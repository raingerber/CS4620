/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 6 "parser.y" /* yacc.c:339  */


#include "scanner.h" // for yylex
#include "parser.h"
#include "errors.h"

void yyerror(const char *msg); // standard error-handling routine

#line 75 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_Void = 258,
    T_Bool = 259,
    T_Int = 260,
    T_Double = 261,
    T_String = 262,
    T_Class = 263,
    T_LessEqual = 264,
    T_GreaterEqual = 265,
    T_Equal = 266,
    T_NotEqual = 267,
    T_Dims = 268,
    T_And = 269,
    T_Or = 270,
    T_Null = 271,
    T_Extends = 272,
    T_This = 273,
    T_Interface = 274,
    T_Implements = 275,
    T_While = 276,
    T_For = 277,
    T_If = 278,
    T_Else = 279,
    T_Return = 280,
    T_Break = 281,
    T_New = 282,
    T_NewArray = 283,
    T_Print = 284,
    T_ReadInteger = 285,
    T_ReadLine = 286,
    T_Identifier = 287,
    T_StringConstant = 288,
    T_IntConstant = 289,
    T_DoubleConstant = 290,
    T_BoolConstant = 291,
    T_Increm = 292,
    T_Decrem = 293,
    T_Switch = 294,
    T_Case = 295,
    T_Default = 296,
    T_UnaryMinus = 297,
    T_Lower_Than_Else = 298
  };
#endif
/* Tokens.  */
#define T_Void 258
#define T_Bool 259
#define T_Int 260
#define T_Double 261
#define T_String 262
#define T_Class 263
#define T_LessEqual 264
#define T_GreaterEqual 265
#define T_Equal 266
#define T_NotEqual 267
#define T_Dims 268
#define T_And 269
#define T_Or 270
#define T_Null 271
#define T_Extends 272
#define T_This 273
#define T_Interface 274
#define T_Implements 275
#define T_While 276
#define T_For 277
#define T_If 278
#define T_Else 279
#define T_Return 280
#define T_Break 281
#define T_New 282
#define T_NewArray 283
#define T_Print 284
#define T_ReadInteger 285
#define T_ReadLine 286
#define T_Identifier 287
#define T_StringConstant 288
#define T_IntConstant 289
#define T_DoubleConstant 290
#define T_BoolConstant 291
#define T_Increm 292
#define T_Decrem 293
#define T_Switch 294
#define T_Case 295
#define T_Default 296
#define T_UnaryMinus 297
#define T_Lower_Than_Else 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 18 "parser.y" /* yacc.c:355  */

    int integerConstant;
    bool boolConstant;
    char *stringConstant;
    double doubleConstant;
    char identifier[MaxIdentLen+1]; // +1 for terminating null
    Decl *decl;
    List<Decl*> *declList;
    Type *type;
    NamedType *cType;
    List<NamedType*> *cTypeList;
    FnDecl *fDecl;
    VarDecl *var;
    List<VarDecl*> *varList;
    Expr *expr;
    List<Expr*> *exprList;
    Stmt *stmt;
    List<Stmt*> *stmtList;
    LValue *lvalue;
    /*
    Case *aCase;
    List<Case*> *caseList;
    */

#line 226 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 255 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   596

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  183

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,     2,     2,    49,     2,     2,
      59,    60,    47,    45,    58,    46,    52,    48,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    55,
      43,    42,    44,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    53,     2,    61,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    56,     2,    57,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    50,    54
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   106,   106,   119,   120,   123,   124,   125,   126,   129,
     132,   135,   136,   137,   138,   139,   140,   143,   147,   149,
     152,   156,   158,   161,   163,   166,   168,   171,   172,   175,
     176,   180,   182,   186,   187,   190,   192,   195,   198,   202,
     203,   206,   207,   210,   211,   212,   214,   216,   218,   220,
     222,   224,   228,   229,   230,   233,   235,   239,   240,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   258,   260,   261,   262,   263,   265,   266,
     268,   269,   271,   273,   278,   279,   280,   281,   282,   285,
     286,   289,   290,   293,   294
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_Void", "T_Bool", "T_Int", "T_Double",
  "T_String", "T_Class", "T_LessEqual", "T_GreaterEqual", "T_Equal",
  "T_NotEqual", "T_Dims", "T_And", "T_Or", "T_Null", "T_Extends", "T_This",
  "T_Interface", "T_Implements", "T_While", "T_For", "T_If", "T_Else",
  "T_Return", "T_Break", "T_New", "T_NewArray", "T_Print", "T_ReadInteger",
  "T_ReadLine", "T_Identifier", "T_StringConstant", "T_IntConstant",
  "T_DoubleConstant", "T_BoolConstant", "T_Increm", "T_Decrem", "T_Switch",
  "T_Case", "T_Default", "'='", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "'%'", "T_UnaryMinus", "'!'", "'.'", "'['", "T_Lower_Than_Else", "';'",
  "'{'", "'}'", "','", "'('", "')'", "']'", "$accept", "Program",
  "DeclList", "Decl", "VarDecl", "Variable", "Type", "IntfDecl",
  "IntfList", "ClassDecl", "OptExt", "OptImpl", "ImpList", "FieldList",
  "Field", "FnHeader", "Formals", "FormalList", "FnDecl", "StmtBlock",
  "VarDecls", "StmtList", "Stmt", "LValue", "Call", "OptExpr", "Expr",
  "Constant", "Actuals", "ExprList", "OptElse", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,    61,    60,    62,    43,    45,    42,    47,    37,
     297,    33,    46,    91,   298,    59,   123,   125,    44,    40,
      41,    93
};
# endif

#define YYPACT_NINF -83

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-83)))

#define YYTABLE_NINF -59

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-59)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      77,   -26,   -83,   -83,   -83,   -83,   -21,     2,   -83,    36,
      77,   -83,   -83,   -17,    -4,   -83,   -83,   -16,   -83,   -18,
      22,   -10,   -83,   -83,   -83,   -83,    -7,   -83,   -83,   153,
      17,    48,   -83,   153,    72,   -83,    -1,    11,    15,   -83,
      42,    30,    13,    27,   -83,   -83,    32,    52,    53,   503,
      58,    56,    57,    60,    62,    63,    -5,   -83,   -83,   -83,
     -83,   537,   537,   537,   -83,   -83,    67,   427,    83,   -83,
      71,   322,   -83,   -83,   -83,   153,   -83,    78,   -83,   -83,
      16,    74,   -83,   537,   537,   537,    80,   -83,   262,   -83,
      98,   537,   537,    81,    82,   537,   -20,   -20,   134,   -83,
     -83,   537,   -83,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   537,   537,   108,   537,   -83,   115,
      18,    -7,   -83,   181,    99,   199,   -83,    93,   246,   322,
     -53,   -83,   -83,   102,   107,   -83,   322,   154,   154,   378,
     378,   389,   333,   154,   154,   103,   103,   -20,   -20,   -20,
     114,   123,   -83,   -83,   -83,   -83,   -83,   469,   537,   469,
     -83,   153,   537,   119,   -83,   537,   -83,   -83,   309,   164,
      -9,   322,   -83,   129,   537,   469,   -83,   -83,   -83,   144,
     -83,   469,   -83
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    12,    11,    14,    13,     0,     0,    15,     0,
       2,     4,     7,     0,     0,     8,     5,     0,     6,     0,
      22,     0,     1,     3,     9,    16,    10,    40,    37,    34,
       0,    24,    19,    34,    42,    36,     0,     0,    33,    21,
       0,     0,     0,     0,    88,    83,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,    87,    84,    86,
      85,     0,     0,     0,    39,    44,     0,    42,    59,    60,
       0,    57,    61,    10,    32,     0,    26,    23,    28,    17,
       0,     0,    31,     0,    58,     0,    52,    49,     0,    51,
       0,     0,     0,     0,     0,    90,    77,    78,     0,    38,
      41,     0,    43,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    35,     0,
       0,     0,    18,     0,     0,     0,    48,     0,     0,    92,
       0,    79,    80,     0,    89,    76,    62,    72,    73,    68,
      69,    74,    75,    70,    71,    63,    64,    66,    65,    67,
      53,     0,    25,    20,    29,    27,    30,    58,     0,    58,
      81,     0,     0,     0,    55,    90,    54,    46,     0,    94,
       0,    91,    50,     0,    58,    58,    45,    82,    56,     0,
      93,    58,    47
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -83,   -83,   -83,   195,   -31,    -3,     0,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   170,   182,   -83,    96,   200,
     -83,   151,   105,   -83,   -83,   -82,   -48,   -83,    54,   128,
     -83
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    11,    12,    13,    36,    15,    42,    16,
      31,    41,    77,   120,   155,    17,    37,    38,    18,    65,
      34,    66,    67,    68,    69,    70,    71,    72,   133,   134,
     176
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      14,    88,   124,    64,    25,   162,    19,   163,   -15,    25,
      14,    20,    25,    96,    97,    98,     1,     2,     3,     4,
       5,     1,     2,     3,     4,     5,    35,   -15,    26,    25,
      35,    73,   116,   117,    21,   123,    22,   125,    24,    30,
      27,    29,    80,   128,   129,     8,    32,   129,   121,    39,
       8,   177,    33,   136,    95,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,    40,   151,
      79,    74,   118,    75,    76,   153,     2,     3,     4,     5,
       1,     2,     3,     4,     5,     6,    78,    82,    44,   154,
      45,    83,   179,    46,    47,    48,     7,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,     8,
     168,    84,    85,    89,   171,    90,    91,   129,    61,    92,
      14,    93,    94,    62,    99,   101,   102,   -58,    27,   122,
     127,    63,   103,   104,   105,   106,   119,   107,   108,    95,
     150,   131,   132,   103,   104,   105,   106,   152,   107,   108,
     113,   114,   115,   160,   158,   116,   117,     2,     3,     4,
       5,   170,   164,   -59,   -59,   162,   109,   110,   111,   112,
     113,   114,   115,   165,   172,   116,   117,   109,   110,   111,
     112,   113,   114,   115,   166,     8,   116,   117,   175,   178,
     103,   104,   105,   106,   135,   107,   108,   -59,   -59,   111,
     112,   113,   114,   115,   181,    23,   116,   117,   103,   104,
     105,   106,    81,   107,   108,    43,   156,    28,   100,   173,
     130,     0,     0,     0,   109,   110,   111,   112,   113,   114,
     115,     0,     0,   116,   117,     0,     0,     0,     0,     0,
       0,   157,   109,   110,   111,   112,   113,   114,   115,     0,
       0,   116,   117,     0,     0,   103,   104,   105,   106,   159,
     107,   108,   167,     0,   169,     0,     0,     0,     0,     0,
       0,   103,   104,   105,   106,     0,   107,   108,     0,     0,
     180,     0,     0,     0,     0,     0,   182,     0,     0,   109,
     110,   111,   112,   113,   114,   115,     0,     0,   116,   117,
       0,     0,     0,     0,   161,   109,   110,   111,   112,   113,
     114,   115,     0,     0,   116,   117,     0,   126,   103,   104,
     105,   106,     0,   107,   108,     0,     0,     0,     0,     0,
       0,   103,   104,   105,   106,     0,   107,   108,     0,     0,
       0,     0,   103,   104,   105,   106,     0,   107,     0,     0,
       0,     0,   109,   110,   111,   112,   113,   114,   115,     0,
       0,   116,   117,     0,   174,   109,   110,   111,   112,   113,
     114,   115,     0,     0,   116,   117,   109,   110,   111,   112,
     113,   114,   115,     0,     0,   116,   117,   103,   104,   -59,
     -59,     0,     0,     0,     0,     0,     0,     0,   103,   104,
     105,   106,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   109,   110,   111,   112,   113,   114,   115,     0,     0,
     116,   117,   109,   110,   111,   112,   113,   114,   115,     0,
       0,   116,   117,    44,     0,    45,     0,     0,    46,    47,
      48,     0,    49,    50,    51,    52,    53,    54,    55,    86,
      57,    58,    59,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    61,     0,     0,     0,     0,    62,     0,
       0,     0,   -58,    27,     0,    44,    63,    45,     0,     0,
      46,    47,    48,     0,    49,    50,    51,    52,    53,    54,
      55,    86,    57,    58,    59,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,     0,     0,     0,    44,
      62,    45,     0,     0,     0,    27,     0,     0,    63,     0,
      51,    52,     0,    54,    55,    86,    57,    58,    59,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61,
       0,     0,     0,    44,    62,    45,     0,     0,    87,     0,
       0,     0,    63,     0,    51,    52,     0,    54,    55,    86,
      57,    58,    59,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    61,     0,     0,     0,     0,    62,     0,
       0,     0,     0,     0,     0,     0,    63
};

static const yytype_int16 yycheck[] =
{
       0,    49,    84,    34,    13,    58,    32,    60,    13,    13,
      10,    32,    13,    61,    62,    63,     3,     4,     5,     6,
       7,     3,     4,     5,     6,     7,    29,    32,    32,    13,
      33,    32,    52,    53,    32,    83,     0,    85,    55,    17,
      56,    59,    42,    91,    92,    32,    56,    95,    32,    32,
      32,    60,    59,   101,    59,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,    20,   117,
      57,    60,    75,    58,    32,    57,     4,     5,     6,     7,
       3,     4,     5,     6,     7,     8,    56,    60,    16,   120,
      18,    59,   174,    21,    22,    23,    19,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    32,
     158,    59,    59,    55,   162,    59,    59,   165,    46,    59,
     120,    59,    59,    51,    57,    42,    55,    55,    56,    55,
      32,    59,     9,    10,    11,    12,    58,    14,    15,    59,
      32,    60,    60,     9,    10,    11,    12,    32,    14,    15,
      47,    48,    49,    60,    55,    52,    53,     4,     5,     6,
       7,   161,    60,     9,    10,    58,    43,    44,    45,    46,
      47,    48,    49,    59,    55,    52,    53,    43,    44,    45,
      46,    47,    48,    49,    61,    32,    52,    53,    24,    60,
       9,    10,    11,    12,    60,    14,    15,    43,    44,    45,
      46,    47,    48,    49,    60,    10,    52,    53,     9,    10,
      11,    12,    42,    14,    15,    33,   120,    17,    67,   165,
      92,    -1,    -1,    -1,    43,    44,    45,    46,    47,    48,
      49,    -1,    -1,    52,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    43,    44,    45,    46,    47,    48,    49,    -1,
      -1,    52,    53,    -1,    -1,     9,    10,    11,    12,    60,
      14,    15,   157,    -1,   159,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    10,    11,    12,    -1,    14,    15,    -1,    -1,
     175,    -1,    -1,    -1,    -1,    -1,   181,    -1,    -1,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,    52,    53,
      -1,    -1,    -1,    -1,    58,    43,    44,    45,    46,    47,
      48,    49,    -1,    -1,    52,    53,    -1,    55,     9,    10,
      11,    12,    -1,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    10,    11,    12,    -1,    14,    15,    -1,    -1,
      -1,    -1,     9,    10,    11,    12,    -1,    14,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    47,    48,    49,    -1,
      -1,    52,    53,    -1,    55,    43,    44,    45,    46,    47,
      48,    49,    -1,    -1,    52,    53,    43,    44,    45,    46,
      47,    48,    49,    -1,    -1,    52,    53,     9,    10,    11,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    46,    47,    48,    49,    -1,    -1,
      52,    53,    43,    44,    45,    46,    47,    48,    49,    -1,
      -1,    52,    53,    16,    -1,    18,    -1,    -1,    21,    22,
      23,    -1,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    55,    56,    -1,    16,    59,    18,    -1,    -1,
      21,    22,    23,    -1,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    16,
      51,    18,    -1,    -1,    -1,    56,    -1,    -1,    59,    -1,
      27,    28,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    -1,    16,    51,    18,    -1,    -1,    55,    -1,
      -1,    -1,    59,    -1,    27,    28,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    19,    32,    63,
      64,    65,    66,    67,    68,    69,    71,    77,    80,    32,
      32,    32,     0,    65,    55,    13,    32,    56,    81,    59,
      17,    72,    56,    59,    82,    67,    68,    78,    79,    32,
      20,    73,    70,    78,    16,    18,    21,    22,    23,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    46,    51,    59,    66,    81,    83,    84,    85,    86,
      87,    88,    89,    32,    60,    58,    32,    74,    56,    57,
      68,    77,    60,    59,    59,    59,    32,    55,    88,    55,
      59,    59,    59,    59,    59,    59,    88,    88,    88,    57,
      83,    42,    55,     9,    10,    11,    12,    14,    15,    43,
      44,    45,    46,    47,    48,    49,    52,    53,    67,    58,
      75,    32,    55,    88,    87,    88,    55,    32,    88,    88,
      91,    60,    60,    90,    91,    60,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      32,    88,    32,    57,    66,    76,    80,    60,    55,    60,
      60,    58,    58,    60,    60,    59,    61,    84,    88,    84,
      68,    88,    55,    90,    55,    24,    92,    60,    60,    87,
      84,    60,    84
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    64,    64,    65,    65,    65,    65,    66,
      67,    68,    68,    68,    68,    68,    68,    69,    70,    70,
      71,    72,    72,    73,    73,    74,    74,    75,    75,    76,
      76,    77,    77,    78,    78,    79,    79,    80,    81,    82,
      82,    83,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    85,    85,    85,    86,    86,    87,    87,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    89,    89,    89,    89,    89,    90,
      90,    91,    91,    92,    92
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     1,     1,     2,     5,     3,     0,
       7,     2,     0,     2,     0,     3,     1,     2,     0,     1,
       1,     5,     5,     1,     0,     3,     1,     2,     4,     2,
       0,     2,     0,     2,     1,     6,     5,     9,     3,     2,
       5,     2,     1,     3,     4,     4,     6,     1,     0,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     3,
       3,     4,     6,     1,     1,     1,     1,     1,     1,     1,
       0,     3,     1,     2,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex ();
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
  *++yylsp = yylloc;
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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 106 "parser.y" /* yacc.c:1646  */
    { 
                                      (yylsp[0]); 
                                      Program *program = new Program((yyvsp[0].declList));
                                      // if no errors, advance to next phase
                                      if (ReportError::NumErrors() == 0) {
                                        program->CreateTables();
                                        program->Check();
                                        //program->Check(0, tracker);
                                      }
                                    }
#line 1652 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 119 "parser.y" /* yacc.c:1646  */
    { ((yyval.declList)=(yyvsp[-1].declList))->Append((yyvsp[0].decl)); }
#line 1658 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 120 "parser.y" /* yacc.c:1646  */
    { ((yyval.declList) = new List<Decl*>)->Append((yyvsp[0].decl)); }
#line 1664 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 124 "parser.y" /* yacc.c:1646  */
    { (yyval.decl)=(yyvsp[0].fDecl); }
#line 1670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 125 "parser.y" /* yacc.c:1646  */
    { (yyval.decl)=(yyvsp[0].var); }
#line 1676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 132 "parser.y" /* yacc.c:1646  */
    { (yyval.var) = new VarDecl(new Identifier((yylsp[0]), (yyvsp[0].identifier)), (yyvsp[-1].type)); }
#line 1682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 135 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = Type::intType; }
#line 1688 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 136 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = Type::boolType; }
#line 1694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 137 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = Type::stringType; }
#line 1700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 138 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = Type::doubleType; }
#line 1706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 139 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new NamedType(new Identifier((yylsp[0]),(yyvsp[0].identifier))); }
#line 1712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 140 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new ArrayType(Join((yylsp[-1]), (yylsp[0])), (yyvsp[-1].type)); }
#line 1718 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 144 "parser.y" /* yacc.c:1646  */
    { (yyval.decl) = new InterfaceDecl(new Identifier((yylsp[-3]), (yyvsp[-3].identifier)), (yyvsp[-1].declList)); }
#line 1724 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 148 "parser.y" /* yacc.c:1646  */
    { ((yyval.declList)=(yyvsp[-2].declList))->Append((yyvsp[-1].fDecl)); }
#line 1730 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 149 "parser.y" /* yacc.c:1646  */
    { (yyval.declList) = new List<Decl*>(); }
#line 1736 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 153 "parser.y" /* yacc.c:1646  */
    { (yyval.decl) = new ClassDecl(new Identifier((yylsp[-5]), (yyvsp[-5].identifier)), (yyvsp[-4].cType), (yyvsp[-3].cTypeList), (yyvsp[-1].declList)); }
#line 1742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 157 "parser.y" /* yacc.c:1646  */
    { (yyval.cType) = new NamedType(new Identifier((yylsp[0]), (yyvsp[0].identifier))); }
#line 1748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 158 "parser.y" /* yacc.c:1646  */
    { (yyval.cType) = NULL; }
#line 1754 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 162 "parser.y" /* yacc.c:1646  */
    { (yyval.cTypeList) = (yyvsp[0].cTypeList); }
#line 1760 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 163 "parser.y" /* yacc.c:1646  */
    { (yyval.cTypeList) = new List<NamedType*>; }
#line 1766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 167 "parser.y" /* yacc.c:1646  */
    { ((yyval.cTypeList)=(yyvsp[-2].cTypeList))->Append(new NamedType(new Identifier((yylsp[0]), (yyvsp[0].identifier)))); }
#line 1772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 168 "parser.y" /* yacc.c:1646  */
    { ((yyval.cTypeList)=new List<NamedType*>)->Append(new NamedType(new Identifier((yylsp[0]), (yyvsp[0].identifier)))); }
#line 1778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 171 "parser.y" /* yacc.c:1646  */
    { ((yyval.declList)=(yyvsp[-1].declList))->Append((yyvsp[0].decl)); }
#line 1784 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 172 "parser.y" /* yacc.c:1646  */
    { (yyval.declList) = new List<Decl*>(); }
#line 1790 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 175 "parser.y" /* yacc.c:1646  */
    { (yyval.decl) = (yyvsp[0].var); }
#line 1796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 176 "parser.y" /* yacc.c:1646  */
    { (yyval.decl) = (yyvsp[0].fDecl); }
#line 1802 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 181 "parser.y" /* yacc.c:1646  */
    { (yyval.fDecl) = new FnDecl(new Identifier((yylsp[-3]), (yyvsp[-3].identifier)), (yyvsp[-4].type), (yyvsp[-1].varList)); }
#line 1808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 183 "parser.y" /* yacc.c:1646  */
    { (yyval.fDecl) = new FnDecl(new Identifier((yylsp[-3]), (yyvsp[-3].identifier)), Type::voidType, (yyvsp[-1].varList)); }
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 186 "parser.y" /* yacc.c:1646  */
    { (yyval.varList) = (yyvsp[0].varList); }
#line 1820 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 187 "parser.y" /* yacc.c:1646  */
    { (yyval.varList) = new List<VarDecl*>; }
#line 1826 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 191 "parser.y" /* yacc.c:1646  */
    { ((yyval.varList)=(yyvsp[-2].varList))->Append((yyvsp[0].var)); }
#line 1832 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 192 "parser.y" /* yacc.c:1646  */
    { ((yyval.varList) = new List<VarDecl*>)->Append((yyvsp[0].var)); }
#line 1838 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 195 "parser.y" /* yacc.c:1646  */
    { ((yyval.fDecl)=(yyvsp[-1].fDecl))->SetFunctionBody((yyvsp[0].stmt)); }
#line 1844 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 199 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new StmtBlock((yyvsp[-2].varList), (yyvsp[-1].stmtList)); }
#line 1850 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 202 "parser.y" /* yacc.c:1646  */
    { ((yyval.varList)=(yyvsp[-1].varList))->Append((yyvsp[0].var)); }
#line 1856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 203 "parser.y" /* yacc.c:1646  */
    { (yyval.varList) = new List<VarDecl*>; }
#line 1862 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 206 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtList) = (yyvsp[0].stmtList); (yyval.stmtList)->InsertAt((yyvsp[-1].stmt), 0); }
#line 1868 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 207 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtList) = new List<Stmt*>; }
#line 1874 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 210 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[-1].expr); }
#line 1880 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 213 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new IfStmt((yyvsp[-3].expr), (yyvsp[-1].stmt), (yyvsp[0].stmt)); }
#line 1886 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 215 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new WhileStmt((yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 1892 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 217 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new ForStmt((yyvsp[-6].expr), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 1898 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 219 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new ReturnStmt((yylsp[-1]), (yyvsp[-1].expr)); }
#line 1904 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 221 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new ReturnStmt((yylsp[-1]), new EmptyExpr()); }
#line 1910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 223 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new PrintStmt((yyvsp[-2].exprList)); }
#line 1916 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 224 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new BreakStmt((yylsp[-1])); }
#line 1922 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 228 "parser.y" /* yacc.c:1646  */
    { (yyval.lvalue) = new FieldAccess(NULL, new Identifier((yylsp[0]), (yyvsp[0].identifier))); }
#line 1928 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 229 "parser.y" /* yacc.c:1646  */
    { (yyval.lvalue) = new FieldAccess((yyvsp[-2].expr), new Identifier((yylsp[0]), (yyvsp[0].identifier))); }
#line 1934 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 230 "parser.y" /* yacc.c:1646  */
    { (yyval.lvalue) = new ArrayAccess(Join((yylsp[-3]), (yylsp[0])), (yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 1940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 234 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new Call(Join((yylsp[-3]),(yylsp[0])), NULL, new Identifier((yylsp[-3]),(yyvsp[-3].identifier)), (yyvsp[-1].exprList)); }
#line 1946 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 236 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new Call(Join((yylsp[-5]),(yylsp[0])), (yyvsp[-5].expr), new Identifier((yylsp[-3]),(yyvsp[-3].identifier)), (yyvsp[-1].exprList)); }
#line 1952 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 239 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1958 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 240 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new EmptyExpr(); }
#line 1964 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 243 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].lvalue); }
#line 1970 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 246 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new AssignExpr((yyvsp[-2].lvalue), new Operator((yylsp[-1]),"="), (yyvsp[0].expr)); }
#line 1976 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 247 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ArithmeticExpr((yyvsp[-2].expr), new Operator((yylsp[-1]), "+"), (yyvsp[0].expr)); }
#line 1982 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 248 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ArithmeticExpr((yyvsp[-2].expr), new Operator((yylsp[-1]), "-"), (yyvsp[0].expr)); }
#line 1988 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 249 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ArithmeticExpr((yyvsp[-2].expr), new Operator((yylsp[-1]),"/"), (yyvsp[0].expr)); }
#line 1994 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 250 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ArithmeticExpr((yyvsp[-2].expr), new Operator((yylsp[-1]),"*"), (yyvsp[0].expr)); }
#line 2000 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 251 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ArithmeticExpr((yyvsp[-2].expr), new Operator((yylsp[-1]),"%"), (yyvsp[0].expr)); }
#line 2006 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 252 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new EqualityExpr((yyvsp[-2].expr), new Operator((yylsp[-1]),"=="), (yyvsp[0].expr)); }
#line 2012 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 253 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new EqualityExpr((yyvsp[-2].expr), new Operator((yylsp[-1]),"!="), (yyvsp[0].expr)); }
#line 2018 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 254 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new RelationalExpr((yyvsp[-2].expr), new Operator((yylsp[-1]),"<"), (yyvsp[0].expr)); }
#line 2024 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 255 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new RelationalExpr((yyvsp[-2].expr), new Operator((yylsp[-1]),">"), (yyvsp[0].expr)); }
#line 2030 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 257 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new RelationalExpr((yyvsp[-2].expr), new Operator((yylsp[-1]),"<="), (yyvsp[0].expr)); }
#line 2036 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 259 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new RelationalExpr((yyvsp[-2].expr), new Operator((yylsp[-1]),">="), (yyvsp[0].expr)); }
#line 2042 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 260 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new LogicalExpr((yyvsp[-2].expr), new Operator((yylsp[-1]),"&&"), (yyvsp[0].expr)); }
#line 2048 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 261 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new LogicalExpr((yyvsp[-2].expr), new Operator((yylsp[-1]),"||"), (yyvsp[0].expr)); }
#line 2054 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 262 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2060 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 264 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ArithmeticExpr(new Operator((yylsp[-1]),"-"), (yyvsp[0].expr)); }
#line 2066 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 265 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new LogicalExpr(new Operator((yylsp[-1]),"!"), (yyvsp[0].expr)); }
#line 2072 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 267 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ReadIntegerExpr(Join((yylsp[-2]),(yylsp[0]))); }
#line 2078 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 268 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ReadLineExpr(Join((yylsp[-2]),(yylsp[0]))); }
#line 2084 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 270 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new NewExpr(Join((yylsp[-3]),(yylsp[0])),new NamedType(new Identifier((yylsp[-1]),(yyvsp[-1].identifier)))); }
#line 2090 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 272 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new NewArrayExpr(Join((yylsp[-5]),(yylsp[0])),(yyvsp[-3].expr), (yyvsp[-1].type)); }
#line 2096 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 273 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new This((yylsp[0])); }
#line 2102 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 278 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new IntConstant((yylsp[0]),(yyvsp[0].integerConstant)); }
#line 2108 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 279 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BoolConstant((yylsp[0]),(yyvsp[0].boolConstant)); }
#line 2114 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 280 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new DoubleConstant((yylsp[0]),(yyvsp[0].doubleConstant)); }
#line 2120 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 281 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new StringConstant((yylsp[0]),(yyvsp[0].stringConstant)); }
#line 2126 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 282 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new NullConstant((yylsp[0])); }
#line 2132 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 285 "parser.y" /* yacc.c:1646  */
    { (yyval.exprList) = (yyvsp[0].exprList); }
#line 2138 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 286 "parser.y" /* yacc.c:1646  */
    { (yyval.exprList) = new List<Expr*>; }
#line 2144 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 289 "parser.y" /* yacc.c:1646  */
    { ((yyval.exprList)=(yyvsp[-2].exprList))->Append((yyvsp[0].expr)); }
#line 2150 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 290 "parser.y" /* yacc.c:1646  */
    { ((yyval.exprList) = new List<Expr*>)->Append((yyvsp[0].expr)); }
#line 2156 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 293 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2162 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 295 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = NULL; }
#line 2168 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2172 "y.tab.c" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
  return yyresult;
}
#line 316 "parser.y" /* yacc.c:1906  */



/* Function: InitParser
 * --------------------
 * This function will be called before any calls to yyparse().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the parser (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yydebug that controls whether yacc prints debugging information about
 * parser actions (shift/reduce) and contents of state stack during parser.
 * If set to false, no information is printed. Setting it to true will give
 * you a running trail that might be helpful when debugging your parser.
 * Please be sure the variable is set to false when submitting your final
 * version.
 */
void InitParser()
{
   PrintDebug("parser", "Initializing parser");
   yydebug = false;
}



