
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "final.y"

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int yylex();
int yyerror(char const * s);
extern FILE* yyin;

//Symbol Table
struct symbol{
    char* name;
    double value;
    int type;
    struct ast *func;
    struct symlist *syms;
};


#define NHASH 9997
struct symbol symtab[NHASH];

struct symbol *lookup(char *);
struct symbol *install(char *,int type);

//Lista de símbolos
struct symlist{
    struct symbol *sym;
    struct symlist *next;
};

struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);


//Aqui se guardan vari
enum bifs{
    print
};

//Nodos del arbol sintactico
struct node{
    int nodetype;
    struct node *l;
    struct node *r;
};

//Nodos de las funciones por default Eg. Print, Read
struct fncall{
    int nodetype;
    struct node *l;
    enum bifs functype;
};

//Nodos de las funciones creadas por el usuario
struct ufncall{
    int nodetype;
    struct node *l;
    struct symbol *s;
};

//Nodos para el manejo de flujo condicionado. If Else While
struct flow{
    int nodetype;
    struct node *cond;
    struct node *tl;
    struct node *el;
};

//Nodos para almacenar los números
struct numval{
    int nodetype;
    double number;
};

//Nodos para hacer referencia a los símbolos
struct symref{
    int nodetype;
    struct symbol *s;
};

//Nodos para hacer asignaciones
struct symasgn{
    int nodetype;
    struct symbol *s;
    struct node *v;
};

//Funciones del arbol sintáctico
struct node * readasgn(struct symbol *s);
struct node *newnode(int nodetype, struct node *l, struct node *r);
struct node *newcmp(int cmptype, struct node *l, struct node *r);
struct node *newfunc(int functype,struct node *l);
struct node *newcall(struct symbol *s, struct node *l);
struct node *newref(struct symbol *s);
struct node *newasgn(struct symbol *s, struct node *v);
struct node *newnum(double d);
struct node *newflow(int nodetype, struct node *cond, struct node *tl, struct node *tr);

//Funcion para crear funciones de usuario
void dodef(struct symbol *name, struct symlist *syms, struct node *stmts);
static double callbuiltin(struct fncall *f);
static double calluser(struct ufncall *);

//Función principal, recorre el arbol
double eval(struct node *);

void treefree(struct node *);

void Display();



/* Line 189 of yacc.c  */
#line 189 "final.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     NUM = 259,
     NAME = 260,
     PRINT = 261,
     EOL = 262,
     INT = 263,
     FLOAT = 264,
     IF = 265,
     IFELSE = 266,
     WHILE = 267,
     DO = 268,
     LET = 269,
     START = 270,
     END = 271,
     VAR = 272,
     FUN = 273,
     READ = 274,
     RETURN = 275,
     CMP = 276
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 117 "final.y"

    struct node *a;
    double d;
    struct symbol *s;
    struct symlist *sl;
    char *c;
    int ty;
    int fn;



/* Line 214 of yacc.c  */
#line 258 "final.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 270 "final.tab.c"

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
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   83

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  46
/* YYNRULES -- Number of states.  */
#define YYNSTATES  96

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   276

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      29,    30,    25,    23,    31,    24,     2,    26,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    28,    27,
      32,    22,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     9,    11,    12,    16,    18,    23,    25,
      26,    30,    32,    44,    46,    47,    51,    53,    57,    59,
      61,    63,    64,    68,    70,    74,    80,    87,    93,    96,
      99,   103,   107,   111,   113,   117,   121,   123,   125,   127,
     129,   134,   138,   140,   141,   145,   147
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      34,     0,    -1,    35,    38,    15,    45,    16,    -1,    36,
      -1,    -1,    37,    27,    36,    -1,    37,    -1,    17,     5,
      28,    44,    -1,    39,    -1,    -1,    40,    27,    39,    -1,
      40,    -1,    18,     5,    29,    41,    30,    28,    44,    35,
      15,    45,    16,    -1,    42,    -1,    -1,    43,    31,    42,
      -1,    43,    -1,     5,    28,    44,    -1,     8,    -1,     9,
      -1,    46,    -1,    -1,    47,    27,    46,    -1,    47,    -1,
       5,    32,    48,    -1,    10,    29,    53,    30,    47,    -1,
      11,    29,    53,    30,    47,    47,    -1,    12,    29,    53,
      30,    47,    -1,     6,    48,    -1,    19,     5,    -1,    15,
      45,    16,    -1,    48,    23,    49,    -1,    48,    24,    49,
      -1,    49,    -1,    49,    25,    50,    -1,    49,    26,    50,
      -1,    50,    -1,     5,    -1,     4,    -1,     3,    -1,     5,
      29,    51,    30,    -1,    29,    48,    30,    -1,    52,    -1,
      -1,    48,    31,    52,    -1,    48,    -1,    48,    21,    48,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   146,   146,   149,   150,   153,   154,   157,   160,   161,
     164,   165,   168,   171,   172,   175,   176,   179,   182,   183,
     186,   187,   190,   191,   194,   195,   196,   197,   198,   199,
     200,   203,   204,   205,   208,   209,   210,   213,   214,   215,
     216,   217,   220,   221,   224,   225,   229
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "NUM", "NAME", "PRINT", "EOL",
  "INT", "FLOAT", "IF", "IFELSE", "WHILE", "DO", "LET", "START", "END",
  "VAR", "FUN", "READ", "RETURN", "CMP", "'='", "'+'", "'-'", "'*'", "'/'",
  "';'", "':'", "'('", "')'", "','", "'<'", "$accept", "prog", "opt_decls",
  "decls", "dec", "opt_fun_decls", "fun_decls", "fun_dec", "opt_params",
  "params_lst", "param", "tipo", "opt_stmts", "stmt_list", "stmt", "expr",
  "term", "factor", "opt_args", "arg_lst", "expression", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,    61,    43,    45,    42,    47,    59,    58,    40,
      41,    44,    60
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    36,    37,    38,    38,
      39,    39,    40,    41,    41,    42,    42,    43,    44,    44,
      45,    45,    46,    46,    47,    47,    47,    47,    47,    47,
      47,    48,    48,    48,    49,    49,    49,    50,    50,    50,
      50,    50,    51,    51,    52,    52,    53
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     1,     0,     3,     1,     4,     1,     0,
       3,     1,    11,     1,     0,     3,     1,     3,     1,     1,
       1,     0,     3,     1,     3,     5,     6,     5,     2,     2,
       3,     3,     3,     1,     3,     3,     1,     1,     1,     1,
       4,     3,     1,     0,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     9,     3,     6,     0,     1,     0,     0,
       8,    11,     0,     0,     0,    21,     0,     5,    18,    19,
       7,    14,     0,     0,     0,     0,     0,    21,     0,     0,
      20,    23,    10,     0,     0,    13,    16,     0,    39,    38,
      37,     0,    28,    33,    36,     0,     0,     0,     0,    29,
       2,     0,     0,     0,     0,    24,    43,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    30,    22,    17,     0,
      15,    45,     0,    42,    41,    31,    32,    34,    35,     0,
       0,     0,     0,     4,     0,    40,    46,    25,     0,    27,
       0,    44,    26,    21,     0,    12
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,     5,     9,    10,    11,    34,    35,
      36,    20,    29,    30,    31,    62,    43,    44,    72,    73,
      63
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -58
static const yytype_int8 yypact[] =
{
      -9,     9,    18,    23,   -58,    -6,     8,   -58,    27,    29,
     -58,    20,    -9,    21,    24,     1,    23,   -58,   -58,   -58,
     -58,    47,    22,    -1,    26,    30,    31,     1,    51,    42,
     -58,    34,   -58,    35,    37,   -58,    33,    -1,   -58,   -58,
      36,    -1,    16,    17,   -58,    -1,    -1,    -1,    52,   -58,
     -58,     1,    21,    41,    47,    16,    -1,     3,    -1,    -1,
      -1,    -1,    14,    40,    43,    44,   -58,   -58,   -58,    21,
     -58,   -14,    45,   -58,   -58,    17,    17,   -58,   -58,    -1,
       1,     1,     1,    -9,    -1,   -58,    16,   -58,     1,   -58,
      56,   -58,   -58,     1,    60,   -58
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -58,   -58,   -11,    65,   -58,   -58,    62,   -58,   -58,    25,
     -58,   -47,   -27,    32,   -57,   -22,   -13,   -12,   -58,    -4,
       4
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      48,    42,    38,    39,    40,    68,    22,    23,     1,    58,
      59,    24,    25,    26,     6,    55,    27,    84,     7,    57,
      28,    12,    83,    87,    88,    89,    58,    59,    41,    18,
      19,    92,    14,    74,    71,    79,    13,    58,    59,    58,
      59,     8,    60,    61,    15,    75,    76,    16,    77,    78,
      64,    65,    33,    21,    37,    45,    49,    86,    50,    46,
      47,    51,    71,    52,    54,    56,    94,    53,    66,    69,
      80,    93,    90,    81,    82,    85,    95,    17,    32,    70,
      91,     0,     0,    67
};

static const yytype_int8 yycheck[] =
{
      27,    23,     3,     4,     5,    52,     5,     6,    17,    23,
      24,    10,    11,    12,     5,    37,    15,    31,     0,    41,
      19,    27,    69,    80,    81,    82,    23,    24,    29,     8,
       9,    88,     5,    30,    56,    21,    28,    23,    24,    23,
      24,    18,    25,    26,    15,    58,    59,    27,    60,    61,
      46,    47,     5,    29,    32,    29,     5,    79,    16,    29,
      29,    27,    84,    28,    31,    29,    93,    30,    16,    28,
      30,    15,    83,    30,    30,    30,    16,    12,    16,    54,
      84,    -1,    -1,    51
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    17,    34,    35,    36,    37,     5,     0,    18,    38,
      39,    40,    27,    28,     5,    15,    27,    36,     8,     9,
      44,    29,     5,     6,    10,    11,    12,    15,    19,    45,
      46,    47,    39,     5,    41,    42,    43,    32,     3,     4,
       5,    29,    48,    49,    50,    29,    29,    29,    45,     5,
      16,    27,    28,    30,    31,    48,    29,    48,    23,    24,
      25,    26,    48,    53,    53,    53,    16,    46,    44,    28,
      42,    48,    51,    52,    30,    49,    49,    50,    50,    21,
      30,    30,    30,    44,    31,    30,    48,    47,    47,    47,
      35,    52,    47,    15,    45,    16
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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

/* Prevent warnings from -Wmissing-prototypes.  */
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
        case 2:

/* Line 1455 of yacc.c  */
#line 146 "final.y"
    {eval((yyvsp[(4) - (5)].a)); treefree((yyvsp[(4) - (5)].a)); exit(0);;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 149 "final.y"
    {;;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 150 "final.y"
    {;;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 153 "final.y"
    {;;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 154 "final.y"
    {;;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 157 "final.y"
    {(yyval.sl) = newsymlist(install((yyvsp[(2) - (4)].s),(yyvsp[(4) - (4)].ty)),NULL);;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 160 "final.y"
    {;;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 161 "final.y"
    {;;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 164 "final.y"
    {;;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 165 "final.y"
    {;;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 168 "final.y"
    {dodef(install((yyvsp[(2) - (11)].s),(yyvsp[(7) - (11)].ty)),(yyvsp[(4) - (11)].sl),(yyvsp[(10) - (11)].a));;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 171 "final.y"
    {;;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 172 "final.y"
    {;;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 175 "final.y"
    {(yyval.sl) = newsymlist((yyvsp[(1) - (3)].sl),(yyvsp[(3) - (3)].sl));;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 176 "final.y"
    {;;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 179 "final.y"
    {(yyval.sl) = newsymlist(install((yyvsp[(1) - (3)].s),(yyvsp[(3) - (3)].ty)),NULL);;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 182 "final.y"
    {;;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 183 "final.y"
    {;;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 186 "final.y"
    {;;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 187 "final.y"
    {;;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 190 "final.y"
    {(yyval.a) = newnode('L',(yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a));;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 191 "final.y"
    {(yyval.a) = (yyvsp[(1) - (1)].a);;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 194 "final.y"
    {(yyval.a) = newasgn(lookup((yyvsp[(1) - (3)].s)),(yyvsp[(3) - (3)].a));;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 195 "final.y"
    {(yyval.a) = newflow('I',(yyvsp[(3) - (5)].a),(yyvsp[(5) - (5)].a),NULL);;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 196 "final.y"
    {(yyval.a) = newflow('I',(yyvsp[(3) - (6)].a),(yyvsp[(5) - (6)].a),(yyvsp[(6) - (6)].a));;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 197 "final.y"
    {(yyval.a) = newflow('W',(yyvsp[(3) - (5)].a),(yyvsp[(5) - (5)].a),NULL);;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 198 "final.y"
    {(yyval.a) = newfunc((yyvsp[(1) - (2)].fn),(yyvsp[(2) - (2)].a));;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 199 "final.y"
    {(yyval.a) = readasgn(lookup((yyvsp[(2) - (2)].s)));}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 200 "final.y"
    {(yyval.a) = newnode('L',(yyvsp[(2) - (3)].a),NULL);;;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 203 "final.y"
    {(yyval.a) = newnode('+',(yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a));;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 204 "final.y"
    {(yyval.a) = newnode('-',(yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a));;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 208 "final.y"
    {(yyval.a) = newnode('*',(yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a));;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 209 "final.y"
    {(yyval.a) = newnode('/',(yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a));;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 213 "final.y"
    {(yyval.a) = newref(lookup((yyvsp[(1) - (1)].s)));;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 214 "final.y"
    {(yyval.a) = newnum((yyvsp[(1) - (1)].d));;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 215 "final.y"
    {(yyval.a) = newnum((yyvsp[(1) - (1)].d));;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 216 "final.y"
    {(yyval.a) = newcall(lookup((yyvsp[(1) - (4)].s)),(yyvsp[(3) - (4)].a));;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 217 "final.y"
    {(yyval.a) = (yyvsp[(2) - (3)].a);;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 220 "final.y"
    {;;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 221 "final.y"
    {;;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 224 "final.y"
    { (yyval.a) = newnode('L',(yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a));;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 225 "final.y"
    {;;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 229 "final.y"
    {(yyval.a) = newcmp((yyvsp[(2) - (3)].fn),(yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a));;}
    break;



/* Line 1455 of yacc.c  */
#line 1836 "final.tab.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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



/* Line 1675 of yacc.c  */
#line 233 "final.y"


//Funcion que guarda en la lista las funciones
void dodef(struct symbol *name, struct symlist *syms, struct node *func){
    
    if(name -> syms) symlistfree(name->syms);
    if(name -> func) treefree(name->func);
    name->syms = syms;
    name->func = func;
    
}

struct symlist * newsymlist(struct symbol *sym, struct symlist *next){
    struct symlist *sl = malloc(sizeof(struct symlist));
    if(!sl){
        yyerror("outofspace");
        exit(0);
    }
    sl->sym = sym;
    sl->next = next;
    return sl;
}

void symlistfree(struct symlist *sl){
    struct symlist *nsl;

    while(sl){
        nsl = sl->next;
        free(sl);
        sl = nsl;
    }
}


double eval(struct node *a){
    double v;
    double b;
    
    if(!a) {
        yyerror("internal error, null eval");
        return 0.0;
    }
    switch(a->nodetype){
        case 'K' : v = ((struct numval *) a)->number; break;

        case 'N' : v = ((struct symref *) a)->s->value;break;

        case '+' : v = eval(a->l) + eval(a->r); break;

        case '-' : v = eval(a->l) - eval(a->r); break;

        case '*' : v = eval(a->l) * eval(a->r); break;

        case '/' : v = eval(a->l) / eval(a->r); break;

        case '=' : 
            switch(((struct symasgn *) a)->s->type){
                case 1:
                    v = ((struct symasgn *) a)->s->value = (int)eval(((struct symasgn *)a)->v);break;
                    break;
                case 2:
                    v = ((struct symasgn *) a)->s->value = eval(((struct symasgn *)a)->v);break;
                    break;
            }
            break;

        case 'F' : v = callbuiltin((struct fncall *)a); break;

        case 'L' : eval(a->l); v= eval(a->r); break;

        case '1': v = (eval(a->l) > eval(a->r))? 1 : 0; break;

        case '2': v = (eval(a->l) < eval(a->r))? 1 : 0; break;

        case '3': v = (eval(a->l) == eval(a->r))? 1 : 0; break;

        case '4': v = (eval(a->l) >= eval(a->r))? 1 : 0; break;

        case '5': v = (eval(a->l) <= eval(a->r))? 1 : 0; break;

        case 'R' : scanf("%lf",&b); v = ((struct symasgn *) a)->s->value = b;break;

        case 'I':
            if( eval( ((struct flow *)a)->cond) != 0) { 
                if( ((struct flow *)a)->tl) { 
                    v = eval( ((struct flow *)a)->tl);
                } 
                else
                    v = 0.0; 
            } 
            else {
                if( ((struct flow *)a)->el) {
                    v = eval(((struct flow *)a)->el);
                } 
                else
                v = 0.0; 
            }
            break;

        case 'W':
            v = 0.0;
            if( ((struct flow *)a)->tl) {
                while( eval(((struct flow *)a)->cond) != 0) 
                    v = eval(((struct flow *)a)->tl);
            }
            break;

        case 'C' : v = calluser((struct ufncall *)a); break;

    }
    return v;
}

struct node * newfunc(int functype, struct node *l){
    struct fncall *a = malloc(sizeof(struct fncall));

    if(!a){
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'F';
    a->l = l;
    a->functype = functype;
    return (struct node *)a;
}

struct node * newcall(struct symbol *s, struct node *l){
    struct ufncall *a = malloc(sizeof(struct ufncall));

    if(!a){
        yyerror("Out of space");
        exit(0);
    }

    a->nodetype = 'C';
    a->l = l;
    a->s = s;
    return (struct node *)a;

}


static double callbuiltin(struct fncall *f){
    enum bifs functype = f->functype;
    double v = eval(f->l);

    switch(functype){
        case print:
            printf("= %4.4g\n", v);
            return v;

    }

}

static double calluser(struct ufncall *f){
    struct symbol *fn = f->s;
    struct symlist *sl;
    struct node *args = f->l;
    double *oldval, *newval;
    double v;
    int nargs;
    int i;

    if(!fn->func){
        yyerror("call to undefined function");
        return 0;
    }

    sl = fn->syms;
    for(nargs = 0;sl;sl = sl->next){
        nargs++;
    }

    oldval = (double *)malloc(nargs * sizeof(double));
    newval = (double *)malloc(nargs * sizeof(double));
    if(!oldval || !newval){
        yyerror("Out of space");
        return 0.0;
    }

    for(i=0; i<nargs; i++){
        if(!args){
            yyerror("too few arguments in call to ");
            free(oldval); free(newval);
            return 0.0;
        }
        if(args->nodetype == 'L'){
            newval[i] = eval(args->l);
            args = args->r;
        }else{
            newval[i] = eval(args);
            args = NULL;
        }
    }

    sl = fn->syms;
    for(i = 0; i<nargs;i++){
        struct symbol *s = sl->sym;

        oldval[i] = s->value;
        s->value = newval[i];
        sl = sl-> next;
    }

    free(newval);

    v = eval(fn->func);

    sl = fn->syms;
    for(i=0; i<nargs; i++){
        struct symbol *s = sl->sym;

        s->value = oldval[i];
        sl = sl->next;
    }

    free(oldval);
    return v;

}

void treefree(struct node *a){
    switch(a->nodetype){
        case '+':
        case '-':
        case '*':
        case '/':
        case '1': case '2': case '3': case '4': case '5': case '6':
        case 'L':
            treefree(a->r);

        case 'M': case 'C': case 'F':
            treefree(a->l);


        case 'K' : case 'N':
            break;
        case '=' :
            free( ((struct symasgn *)a)->v);
            break;

        case 'I': case 'W':
            free( ((struct flow *)a)->cond);
            if( ((struct flow *)a)->tl) treefree( ((struct flow *)a)->tl);
            if( ((struct flow *)a)->el) treefree( ((struct flow *)a)->el);
        break;

    }
    free(a);
}

static unsigned symhash(char *sym){
    unsigned int hash = 0;
    unsigned c;

    while(c=*sym++){
        hash = hash*9 ^ c;
    }
    return hash;
}

struct symbol * install(char *sym, int type){
    struct symbol *sp = &symtab[symhash(sym)%NHASH];
    int scount = NHASH;
    while(--scount >= 0){
        if(sp->name && !strcmp(sp->name,sym)){
            yyerror("La variable ya ha sido declarada");
        }
        if(!sp->name){
            switch(type){
                case 1 :
                    sp->type = 1;
                    break;
                case 2:
                    sp->type = 2;
                    break;
            }

            sp->name = strdup(sym);
            sp->value = 0;
            sp->func = NULL;
            sp->syms = NULL;
            return sp;
        }
        if(++sp >= symtab+NHASH)
            sp = symtab;
    }
    yyerror("symbol table overflow\n");
    abort(); /* tried them all, table is full */

}

struct symbol * lookup(char* sym){
    struct symbol *sp = &symtab[symhash(sym)%NHASH];
    int scount = NHASH;

    while(--scount >= 0){
        if(sp->name && !strcmp(sp->name,sym)){
            return sp;
        }
        if(!sp->name){
            printf("%s",sp->name);
            yyerror(sp->name);
            
            exit(0);
        }
        if(++sp >= symtab+NHASH)
            sp = symtab;
    }
    yyerror("symbol table overflow\n");
    abort(); /* tried them all, table is full */
}

struct node *newnode(int nodetype, struct node *l, struct node *r){
    struct node *a = malloc(sizeof(struct node));

    if(!a){
        yyerror("Out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

struct node *newnum(double d){
    struct numval *a = malloc(sizeof(struct numval));

    if(!a){
        yyerror("Out of space");
        exit(0);
    }
    a->nodetype = 'K';
    a->number = d;
    return (struct node *)a;
}

struct node *newcmp(int cmptype, struct node *l, struct node *r){
    struct node *a = malloc(sizeof(struct node));

    if(!a){
        yyerror("Out of space");
        exit(0);
    }
    a->nodetype = '0' + cmptype;
    a->l = l;
    a->r = r;
    return a;

}

struct node *newref(struct symbol *s){
    struct symref *a = malloc(sizeof(struct symref));
    if(!a) {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'N';
    a->s = s;
    return (struct node *)a;

}

struct node * readasgn(struct symbol *s){
    struct symasgn *a = malloc(sizeof(struct symasgn));
    if(!a) {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'R';
    a->s = s;
    return (struct node *)a;
}

struct node * newasgn(struct symbol *s, struct node *v){
    struct symasgn *a = malloc(sizeof(struct symasgn));
    if(!a) {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = '=';
    a->s = s;
    a->v = v;
    return (struct node *)a;


}

struct node * newflow(int nodetype, struct node *cond, struct node *tl, struct node *el){
    struct flow *a = malloc(sizeof(struct flow));

    if(!a){
        yyerror("out of space");
        exit(0);
    }
    a->nodetype=nodetype;
    a->cond = cond;
    a->tl = tl;
    a->el = el;
    return (struct node *)a;
}

int yyerror(char const * s) {
    extern int yylineno;
    fprintf(stderr,"Error %s | Line: %d\n",s,yylineno);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    yyin= fopen(argv[1],"r");
    yyparse(yyin);

}

