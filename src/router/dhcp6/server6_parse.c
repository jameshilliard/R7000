/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse sfyyparse
#define yylex   sfyylex
#define yyerror sfyyerror
#define yylval  sfyylval
#define yychar  sfyychar
#define yydebug sfyydebug
#define yynerrs sfyynerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTERFACE = 258,
     IFNAME = 259,
     PREFIX = 260,
     LINK = 261,
     RELAY = 262,
     STRING = 263,
     NUMBER = 264,
     SIGNEDNUMBER = 265,
     DECIMAL = 266,
     BOOLEAN = 267,
     IPV6ADDR = 268,
     INFINITY = 269,
     HOST = 270,
     POOL = 271,
     RANGE = 272,
     GROUP = 273,
     LINKLOCAL = 274,
     OPTION = 275,
     ALLOW = 276,
     SEND = 277,
     PREFERENCE = 278,
     RENEWTIME = 279,
     REBINDTIME = 280,
     RAPIDCOMMIT = 281,
     ADDRESS = 282,
     VALIDLIFETIME = 283,
     PREFERLIFETIME = 284,
     UNICAST = 285,
     TEMPIPV6ADDR = 286,
     DNS_SERVERS = 287,
     SIP_SERVERS = 288,
     NTP_SERVERS = 289,
     DUID = 290,
     DUID_ID = 291,
     IAID = 292,
     IAIDINFO = 293,
     INFO_ONLY = 294,
     TO = 295,
     BAD_TOKEN = 296
   };
#endif
/* Tokens.  */
#define INTERFACE 258
#define IFNAME 259
#define PREFIX 260
#define LINK 261
#define RELAY 262
#define STRING 263
#define NUMBER 264
#define SIGNEDNUMBER 265
#define DECIMAL 266
#define BOOLEAN 267
#define IPV6ADDR 268
#define INFINITY 269
#define HOST 270
#define POOL 271
#define RANGE 272
#define GROUP 273
#define LINKLOCAL 274
#define OPTION 275
#define ALLOW 276
#define SEND 277
#define PREFERENCE 278
#define RENEWTIME 279
#define REBINDTIME 280
#define RAPIDCOMMIT 281
#define ADDRESS 282
#define VALIDLIFETIME 283
#define PREFERLIFETIME 284
#define UNICAST 285
#define TEMPIPV6ADDR 286
#define DNS_SERVERS 287
#define SIP_SERVERS 288
#define NTP_SERVERS 289
#define DUID 290
#define DUID_ID 291
#define IAID 292
#define IAIDINFO 293
#define INFO_ONLY 294
#define TO 295
#define BAD_TOKEN 296




/* Copy the first part of user declarations.  */
#line 34 "server6_parse.y"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <syslog.h>
#include <errno.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include "queue.h"
#include "dhcp6.h"
#include "config.h"
#include "common.h"
#include "server6_conf.h"
#include "hash.h"
#include "lease.h"

extern int num_lines;
extern char *sfyytext;
extern int sock;
static struct interface *ifnetworklist = NULL;
static struct link_decl *linklist = NULL;
static struct host_decl *hostlist = NULL;
static struct pool_decl *poollist = NULL;

static struct interface *ifnetwork = NULL;
static struct link_decl *link = NULL;
static struct host_decl *host = NULL;
static struct pool_decl *pool = NULL;
static struct scopelist *currentscope = NULL;
static struct scopelist *currentgroup = NULL;
static int allow = 0;

static void cleanup(void);
void sfyyerror(char *msg);

#define ABORT	do { cleanup(); YYABORT; } while (0)

extern int sfyylex __P((void));


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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 116 "server6_parse.y"
{
	unsigned int	num;
	int 	snum;
	char	*str;
	int 	dec;
	int	bool;
	struct in6_addr	addr;
	struct dhcp6_addr *dhcp6addr;
}
/* Line 187 of yacc.c.  */
#line 238 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 251 "y.tab.c"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   212

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNRULES -- Number of states.  */
#define YYNSTATES  187

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    45,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    44,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,    43,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    11,    13,    15,    21,
      24,    25,    28,    30,    32,    34,    36,    42,    45,    46,
      49,    51,    53,    55,    57,    59,    61,    63,    66,    68,
      74,    80,    82,    83,    86,    88,    90,    92,    94,    96,
     102,   110,   116,   117,   120,   122,   124,   126,   128,   130,
     132,   134,   136,   142,   145,   148,   150,   154,   156,   158,
     164,   169,   174,   176,   180,   183,   185,   187,   189,   191,
     197,   203,   208,   213,   215,   220,   223,   225,   227,   229,
     232,   235,   238,   241,   245,   249,   253,   256,   258,   260,
     263,   265,   267,   270,   272,   274,   276,   278,   280,   284,
     288,   292,   296,   300,   302,   304
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    -1,    47,    48,    -1,    49,    -1,    65,
      -1,    91,    -1,    53,    -1,    50,    42,    51,    43,    44,
      -1,     3,     4,    -1,    -1,    51,    52,    -1,    53,    -1,
      69,    -1,    65,    -1,    91,    -1,    54,    42,    55,    43,
      44,    -1,     6,    94,    -1,    -1,    55,    56,    -1,    59,
      -1,    64,    -1,    63,    -1,    69,    -1,    65,    -1,    91,
      -1,    57,    -1,    57,    58,    -1,    58,    -1,     7,    13,
      45,     9,    44,    -1,    60,    42,    61,    43,    44,    -1,
      16,    -1,    -1,    61,    62,    -1,    69,    -1,    65,    -1,
      64,    -1,    63,    -1,    91,    -1,     5,    13,    45,     9,
      44,    -1,    17,    13,    40,    13,    45,     9,    44,    -1,
      68,    42,    66,    43,    44,    -1,    -1,    66,    67,    -1,
      69,    -1,    59,    -1,    53,    -1,    64,    -1,    63,    -1,
      49,    -1,    91,    -1,    18,    -1,    70,    42,    71,    43,
      44,    -1,    15,    94,    -1,    71,    72,    -1,    72,    -1,
      35,    36,    44,    -1,    73,    -1,    76,    -1,    38,    42,
      74,    43,    44,    -1,    74,    24,    93,    44,    -1,    74,
      25,    93,    44,    -1,    75,    -1,    37,     9,    44,    -1,
      76,    77,    -1,    77,    -1,    78,    -1,    79,    -1,    82,
      -1,    27,    42,    80,    43,    44,    -1,     5,    42,    80,
      43,    44,    -1,    80,    28,    93,    44,    -1,    80,    29,
      93,    44,    -1,    81,    -1,    13,    45,     9,    44,    -1,
      83,    84,    -1,    22,    -1,    21,    -1,    20,    -1,    26,
      44,    -1,    31,    44,    -1,    30,    44,    -1,    39,    44,
      -1,    32,    85,    44,    -1,    33,    87,    44,    -1,    34,
      89,    44,    -1,    85,    86,    -1,    86,    -1,    13,    -1,
      87,    88,    -1,    88,    -1,    13,    -1,    89,    90,    -1,
      90,    -1,    13,    -1,     8,    -1,    92,    -1,    82,    -1,
      24,    93,    44,    -1,    25,    93,    44,    -1,    28,    93,
      44,    -1,    29,    93,    44,    -1,    23,     9,    44,    -1,
       9,    -1,    14,    -1,     8,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   126,   126,   128,   132,   133,   134,   135,   139,   165,
     206,   208,   212,   213,   214,   215,   219,   237,   274,   276,
     280,   281,   282,   283,   284,   285,   286,   290,   291,   295,
     317,   330,   355,   357,   361,   362,   363,   364,   365,   369,
     412,   507,   517,   519,   523,   524,   525,   526,   527,   528,
     529,   533,   558,   582,   614,   615,   619,   627,   628,   632,
     638,   642,   646,   650,   661,   662,   666,   680,   688,   692,
     700,   708,   712,   716,   723,   743,   747,   755,   764,   775,
     782,   789,   796,   803,   806,   809,   815,   816,   820,   827,
     828,   832,   839,   840,   844,   850,   881,   882,   886,   895,
     904,   920,   936,   950,   954,   961
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTERFACE", "IFNAME", "PREFIX", "LINK",
  "RELAY", "STRING", "NUMBER", "SIGNEDNUMBER", "DECIMAL", "BOOLEAN",
  "IPV6ADDR", "INFINITY", "HOST", "POOL", "RANGE", "GROUP", "LINKLOCAL",
  "OPTION", "ALLOW", "SEND", "PREFERENCE", "RENEWTIME", "REBINDTIME",
  "RAPIDCOMMIT", "ADDRESS", "VALIDLIFETIME", "PREFERLIFETIME", "UNICAST",
  "TEMPIPV6ADDR", "DNS_SERVERS", "SIP_SERVERS", "NTP_SERVERS", "DUID",
  "DUID_ID", "IAID", "IAIDINFO", "INFO_ONLY", "TO", "BAD_TOKEN", "'{'",
  "'}'", "';'", "'/'", "$accept", "statements", "networkdef", "ifdef",
  "ifhead", "ifbody", "ifparams", "linkdef", "linkhead", "linkbody",
  "linkparams", "relaylist", "relaypara", "pooldef", "poolhead",
  "poolbody", "poolparas", "prefixdef", "rangedef", "groupdef",
  "groupbody", "groupparas", "grouphead", "hostdef", "hosthead",
  "hostbody", "hostdecl", "iaiddef", "iaidbody", "iaidpara", "hostparas",
  "hostpara", "hostaddr6", "hostprefix6", "addr6para", "v6address",
  "optiondecl", "optionhead", "optionpara", "dns_paras", "dns_para",
  "sip_paras", "sip_para", "ntp_paras", "ntp_para", "confdecl", "paradecl",
  "number_or_infinity", "name", 0
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
     295,   296,   123,   125,    59,    47
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    47,    48,    48,    48,    48,    49,    50,
      51,    51,    52,    52,    52,    52,    53,    54,    55,    55,
      56,    56,    56,    56,    56,    56,    56,    57,    57,    58,
      59,    60,    61,    61,    62,    62,    62,    62,    62,    63,
      64,    65,    66,    66,    67,    67,    67,    67,    67,    67,
      67,    68,    69,    70,    71,    71,    72,    72,    72,    73,
      74,    74,    74,    75,    76,    76,    77,    77,    77,    78,
      79,    80,    80,    80,    81,    82,    83,    83,    83,    84,
      84,    84,    84,    84,    84,    84,    85,    85,    86,    87,
      87,    88,    89,    89,    90,    90,    91,    91,    92,    92,
      92,    92,    92,    93,    93,    94
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     5,     2,
       0,     2,     1,     1,     1,     1,     5,     2,     0,     2,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     5,
       5,     1,     0,     2,     1,     1,     1,     1,     1,     5,
       7,     5,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     2,     2,     1,     3,     1,     1,     5,
       4,     4,     1,     3,     2,     1,     1,     1,     1,     5,
       5,     4,     4,     1,     4,     2,     1,     1,     1,     2,
       2,     2,     2,     3,     3,     3,     2,     1,     1,     2,
       1,     1,     2,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    51,    78,    77,    76,     0,
       0,     0,     0,     0,     3,     4,     0,     7,     0,     5,
       0,    97,     0,     6,    96,     9,   105,    17,     0,   103,
     104,     0,     0,     0,     0,    10,    18,    42,     0,     0,
       0,     0,     0,     0,     0,    75,   102,    98,    99,   100,
     101,     0,     0,     0,    79,    81,    80,    88,     0,    87,
      91,     0,    90,    95,    94,     0,    93,    82,     0,     0,
      11,    12,    14,    13,     0,    15,     0,     0,    31,     0,
       0,    19,    26,    28,    20,     0,    22,    21,    24,    23,
      25,     0,    49,    46,    45,    48,    47,    43,    44,    50,
      83,    86,    84,    89,    85,    92,    53,     8,     0,     0,
       0,     0,    16,    27,    32,    41,     0,     0,     0,     0,
       0,    55,    57,    58,    65,    66,    67,    68,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    54,    64,     0,
       0,     0,     0,    33,    37,    36,    35,    34,    38,     0,
       0,    73,     0,    56,     0,     0,    62,    52,    39,    29,
       0,    30,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    70,    69,    63,     0,     0,
      59,    40,    74,    71,    72,    60,    61
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    14,    15,    16,    51,    70,    17,    18,    52,
      81,    82,    83,    84,    85,   131,   143,    86,    87,    19,
      53,    97,    20,    73,    74,   120,   121,   122,   155,   156,
     123,   124,   125,   126,   150,   151,    21,    22,    45,    58,
      59,    61,    62,    65,    66,    23,    24,    31,    27
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -49
static const yytype_int16 yypact[] =
{
     -49,   144,   -49,    15,    14,   -49,   -49,   -49,   -49,    31,
      32,    32,    32,    32,   -49,   -49,   -19,   -49,     2,   -49,
      23,   -49,   145,   -49,   -49,   -49,   -49,   -49,    27,   -49,
     -49,    34,    40,    50,    57,   -49,   -49,   -49,    58,    61,
      65,    55,    63,    56,    67,   -49,   -49,   -49,   -49,   -49,
     -49,   113,    38,     9,   -49,   -49,   -49,   -49,     3,   -49,
     -49,     4,   -49,   -49,   -49,     5,   -49,   -49,    14,    68,
     -49,   -49,   -49,   -49,    72,   -49,   102,   103,   -49,   104,
      76,   -49,    44,   -49,   -49,    80,   -49,   -49,   -49,   -49,
     -49,    79,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,
     -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   105,    85,
      94,   106,   -49,   -49,   -49,   -49,   107,   109,   112,   117,
      86,   -49,   -49,    52,   -49,   -49,   -49,   -49,   136,   146,
     141,    75,   147,   147,   119,   124,   126,   -49,   -49,   130,
     137,   135,   138,   -49,   -49,   -49,   -49,   -49,   -49,   140,
      -1,   -49,     7,   -49,   174,    -4,   -49,   -49,   -49,   -49,
     177,   -49,   178,    32,    32,   148,   149,   150,    32,    32,
     151,   152,   153,   154,   155,   -49,   -49,   -49,   156,   157,
     -49,   -49,   -49,   -49,   -49,   -49,   -49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -49,   -49,   -49,   158,   -49,   -49,   -49,    24,   -49,   -49,
     -49,   -49,   108,   159,   -49,   -49,   -49,   -43,   -42,   -45,
     -49,   -49,   -49,   -44,   -49,   -49,    69,   -49,   -49,   -49,
     -49,    81,   -49,   -49,    70,   -49,   -38,   -49,   -49,   -49,
     133,   -49,   127,   -49,   142,   -48,   -49,   -11,   134
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      32,    33,    34,    75,    90,    99,    72,    88,    89,    98,
      95,    96,     3,    63,    76,     4,    57,    60,    64,    25,
     168,   169,    26,    35,    68,    78,    79,   163,   164,     6,
       7,     8,     9,    10,    11,   163,   164,    12,    13,   170,
      28,    29,   165,    76,    36,    77,    30,   100,   102,   104,
     166,    77,    91,    68,    78,    79,     5,   116,     6,     7,
       8,     9,    10,    11,    63,    37,    12,    13,    57,    64,
     127,    46,     6,     7,     8,    71,    60,    93,    47,   117,
      76,    80,   127,   148,    48,   127,   146,   147,   144,   145,
      68,   116,    79,     5,    49,     6,     7,     8,     9,    10,
      11,    50,    54,    12,    13,    55,     6,     7,     8,    56,
     116,    67,   107,   117,   108,   109,   110,   111,   142,     4,
     112,   118,   114,   115,   119,     6,     7,     8,    68,   136,
     128,     5,   117,     6,     7,     8,     9,    10,    11,   129,
     118,    12,    13,   119,     2,   139,   130,     3,   134,   132,
       4,   133,   173,   174,   141,   140,    69,   178,   179,   135,
     149,   154,     5,   153,     6,     7,     8,     9,    10,    11,
     157,    38,    12,    13,   158,    39,    40,    41,    42,    43,
     160,   159,   161,   167,    44,   162,   171,   172,   103,   137,
     113,   101,   175,   176,   177,   180,   181,   182,   183,   184,
     185,   186,   106,   152,   138,     0,     0,   105,     0,     0,
       0,    92,    94
};

static const yytype_int16 yycheck[] =
{
      11,    12,    13,    51,    52,    53,    51,    52,    52,    53,
      53,    53,     3,     8,     5,     6,    13,    13,    13,     4,
      24,    25,     8,    42,    15,    16,    17,    28,    29,    20,
      21,    22,    23,    24,    25,    28,    29,    28,    29,    43,
       9,     9,    43,     5,    42,     7,    14,    44,    44,    44,
      43,     7,    43,    15,    16,    17,    18,     5,    20,    21,
      22,    23,    24,    25,     8,    42,    28,    29,    13,    13,
     108,    44,    20,    21,    22,    51,    13,    53,    44,    27,
       5,    43,   120,   131,    44,   123,   131,   131,   131,   131,
      15,     5,    17,    18,    44,    20,    21,    22,    23,    24,
      25,    44,    44,    28,    29,    44,    20,    21,    22,    44,
       5,    44,    44,    27,    42,    13,    13,    13,    43,     6,
      44,    35,    42,    44,    38,    20,    21,    22,    15,    43,
      45,    18,    27,    20,    21,    22,    23,    24,    25,    45,
      35,    28,    29,    38,     0,     9,    40,     3,    36,    42,
       6,    42,   163,   164,    13,     9,    43,   168,   169,    42,
      13,    37,    18,    44,    20,    21,    22,    23,    24,    25,
      44,    26,    28,    29,    44,    30,    31,    32,    33,    34,
      45,    44,    44,     9,    39,    45,     9,     9,    61,   120,
      82,    58,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    68,   133,   123,    -1,    -1,    65,    -1,    -1,
      -1,    53,    53
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    47,     0,     3,     6,    18,    20,    21,    22,    23,
      24,    25,    28,    29,    48,    49,    50,    53,    54,    65,
      68,    82,    83,    91,    92,     4,     8,    94,     9,     9,
      14,    93,    93,    93,    93,    42,    42,    42,    26,    30,
      31,    32,    33,    34,    39,    84,    44,    44,    44,    44,
      44,    51,    55,    66,    44,    44,    44,    13,    85,    86,
      13,    87,    88,     8,    13,    89,    90,    44,    15,    43,
      52,    53,    65,    69,    70,    91,     5,     7,    16,    17,
      43,    56,    57,    58,    59,    60,    63,    64,    65,    69,
      91,    43,    49,    53,    59,    63,    64,    67,    69,    91,
      44,    86,    44,    88,    44,    90,    94,    44,    42,    13,
      13,    13,    44,    58,    42,    44,     5,    27,    35,    38,
      71,    72,    73,    76,    77,    78,    79,    82,    45,    45,
      40,    61,    42,    42,    36,    42,    43,    72,    77,     9,
       9,    13,    43,    62,    63,    64,    65,    69,    91,    13,
      80,    81,    80,    44,    37,    74,    75,    44,    44,    44,
      45,    44,    45,    28,    29,    43,    43,     9,    24,    25,
      43,     9,     9,    93,    93,    44,    44,    44,    93,    93,
      44,    44,    44,    44,    44,    44,    44
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
        case 8:
#line 140 "server6_parse.y"
    {
		if (linklist) {
			ifnetwork->linklist = linklist;
			linklist = NULL;
		}
		if (hostlist) {
			ifnetwork->hostlist = hostlist;
			hostlist = NULL;
		}
		if (currentgroup) 
			ifnetwork->group = currentgroup->scope;

		dprintf(LOG_DEBUG, "interface definition for %s is ok", ifnetwork->name);
		ifnetwork->next = ifnetworklist;
		ifnetworklist = ifnetwork;
		ifnetwork = NULL;

		globalgroup->iflist = ifnetworklist;

		/* leave interface scope we know the current scope is not point to NULL*/
		currentscope = pop_double_list(currentscope);
	}
    break;

  case 9:
#line 166 "server6_parse.y"
    {
		struct interface *temp_if = ifnetworklist;
		while (temp_if)
		{
			if (!strcmp(temp_if->name, (yyvsp[(2) - (2)].str)))
			{
				dprintf(LOG_ERR, "duplicate interface definition for %s",
					temp_if->name);
				ABORT;
			}
			temp_if = temp_if->next;
		}
		ifnetwork = (struct interface *)malloc(sizeof(*ifnetwork));
		if (ifnetwork == NULL) {
			dprintf(LOG_ERR, "failed to allocate memory");
			ABORT;
		}
		memset(ifnetwork, 0, sizeof(*ifnetwork));
		TAILQ_INIT(&ifnetwork->ifscope.dnslist.addrlist);
		TAILQ_INIT(&ifnetwork->ifscope.siplist);
		TAILQ_INIT(&ifnetwork->ifscope.ntplist);
		strncpy(ifnetwork->name, (yyvsp[(2) - (2)].str), strlen((yyvsp[(2) - (2)].str))); 
		if (get_linklocal(ifnetwork->name, &ifnetwork->linklocal) < 0) {
			dprintf(LOG_ERR, "get device %s linklocal failed", ifnetwork->name);
		}
		
		/* check device, if the device is not available,
		 * it is OK, it might be added later
		 * so keep this in the configuration file.
		 */
		if (if_nametoindex(ifnetwork->name) == 0) {
			dprintf(LOG_ERR, "this device %s doesn't exist.", (yyvsp[(2) - (2)].str));
		}
		/* set up hw_addr, link local, primary ipv6addr */
		/* enter interface scope */
		currentscope = push_double_list(currentscope, &ifnetwork->ifscope);
		if (currentscope == NULL)
			ABORT;
	}
    break;

  case 16:
#line 220 "server6_parse.y"
    {
		if (poollist) {
			link->poollist = poollist;
			poollist = NULL;
		}
		if (currentgroup) 
			link->group = currentgroup->scope;

		link->next = linklist;
		linklist = link;
		link = NULL;
		/* leave iink scope we know the current scope is not point to NULL*/
		currentscope = pop_double_list(currentscope);
	}
    break;

  case 17:
#line 238 "server6_parse.y"
    {
		struct link_decl *temp_sub = linklist;
		/* memory allocation for link */
		link = (struct link_decl *)malloc(sizeof(*link));
		if (link == NULL) {
			dprintf(LOG_ERR, "failed to allocate memory");
			ABORT;
		}
		memset(link, 0, sizeof(*link));
		TAILQ_INIT(&link->linkscope.dnslist.addrlist);
		TAILQ_INIT(&link->linkscope.siplist);
		TAILQ_INIT(&link->linkscope.ntplist);
		while (temp_sub) {
			if (!strcmp(temp_sub->name, (yyvsp[(2) - (2)].str)))
			{
				dprintf(LOG_ERR, "duplicate link definition for %s", (yyvsp[(2) - (2)].str));
				ABORT;
			}
			temp_sub = temp_sub->next;
		}			
		/* link set */
		strncpy(link->name, (yyvsp[(2) - (2)].str), strlen((yyvsp[(2) - (2)].str)));
		if (ifnetwork)
			link->network = ifnetwork;
		else {
			/* create a ifnetwork for this interface */
		}
		link->relaylist = NULL;
		link->seglist = NULL;
		/* enter link scope */
		currentscope = push_double_list(currentscope, &link->linkscope);
		if (currentscope == NULL)
			ABORT;
	}
    break;

  case 29:
#line 296 "server6_parse.y"
    {
		struct v6addrlist *temprelay;
		if (!link) {
			dprintf(LOG_ERR, "relay must be defined under link");
			ABORT;
		}
		temprelay = (struct v6addrlist *)malloc(sizeof(*temprelay));
		if (temprelay == NULL) {
			dprintf(LOG_ERR, "failed to allocate memory");
			ABORT;
		}
		memset(temprelay, 0, sizeof(*temprelay));
		memcpy(&temprelay->v6addr.addr, &(yyvsp[(2) - (5)].addr), sizeof(temprelay->v6addr.addr));
		temprelay->v6addr.plen = (yyvsp[(4) - (5)].num);
		temprelay->next = link->relaylist;
		link->relaylist = temprelay;
		temprelay = NULL;
	}
    break;

  case 30:
#line 318 "server6_parse.y"
    {
		if (currentgroup) 
			pool->group = currentgroup->scope;
		pool->next = poollist;
		poollist = pool;
		pool = NULL;
		/* leave pool scope we know the current scope is not point to NULL*/
		currentscope = pop_double_list(currentscope);
	}
    break;

  case 31:
#line 331 "server6_parse.y"
    {
		if (!link) {
			dprintf(LOG_ERR, "pooldef must be defined under link");
			ABORT;
		}
		pool = (struct pool_decl *)malloc(sizeof(*pool));
		if (pool == NULL) {
			dprintf(LOG_ERR, "fail to allocate memory");
			ABORT;
		}
		memset(pool, 0, sizeof(*pool));
		TAILQ_INIT(&pool->poolscope.dnslist.addrlist);
		TAILQ_INIT(&pool->poolscope.siplist);
		TAILQ_INIT(&pool->poolscope.ntplist);
		if (link)
			pool->link = link;
			
		/* enter pool scope */
		currentscope = push_double_list(currentscope, &pool->poolscope);
		if (currentscope == NULL)
			ABORT;
	}
    break;

  case 39:
#line 370 "server6_parse.y"
    {
		struct v6prefix *v6prefix, *v6prefix0;
		struct v6addr *prefix;
		if (!link) {
			dprintf(LOG_ERR, "prefix must be defined under link");
			ABORT;
		}
		v6prefix = (struct v6prefix *)malloc(sizeof(*v6prefix));
		if (v6prefix == NULL) {
			dprintf(LOG_ERR, "failed to allocate memory");
			ABORT;
		}
		memset(v6prefix, 0, sizeof(*v6prefix));
		v6prefix->link = link;
		if (pool)
			v6prefix->pool = pool;
		/* make sure the range ipv6 address within the prefixaddr */
		if ((yyvsp[(4) - (5)].num) > 128 || (yyvsp[(4) - (5)].num) < 0) {
			dprintf(LOG_ERR, "invalid prefix length in line %d", num_lines);
			ABORT;
		}
		prefix = getprefix(&(yyvsp[(2) - (5)].addr), (yyvsp[(4) - (5)].num));
		for (v6prefix0 = link->prefixlist; v6prefix0; v6prefix0 = v6prefix0->next) {
			if (IN6_ARE_ADDR_EQUAL(prefix, &v6prefix0->prefix.addr) && 
					(yyvsp[(4) - (5)].num) == v6prefix0->prefix.plen)  {
				dprintf(LOG_ERR, "duplicated prefix defined within same link");
				ABORT;
			}
		}
		/* check the assigned prefix is not reserved pv6 addresses */
		if (IN6_IS_ADDR_RESERVED(prefix)) {
			dprintf(LOG_ERR, "config reserved prefix");
			ABORT;
		}
		memcpy(&v6prefix->prefix, prefix, sizeof(v6prefix->prefix));
		v6prefix->next = link->prefixlist;
		link->prefixlist = v6prefix;
		free(prefix);
	}
    break;

  case 40:
#line 413 "server6_parse.y"
    {
		struct v6addrseg *seg, *temp_seg;
		struct v6addr *prefix1, *prefix2;
		if (!link) {
			dprintf(LOG_ERR, "range must be defined under link");
			ABORT;
		}
		seg = (struct v6addrseg *)malloc(sizeof(*seg));
		if (seg == NULL) {
			dprintf(LOG_ERR, "failed to allocate memory");
			ABORT;
		}
		memset(seg, 0, sizeof(*seg));
		temp_seg = link->seglist;
		seg->link = link;
		if (pool)
			seg->pool = pool;
		/* make sure the range ipv6 address within the prefixaddr */
		if ((yyvsp[(6) - (7)].num) > 128 || (yyvsp[(6) - (7)].num) < 0) {
			dprintf(LOG_ERR, "invalid prefix length in line %d", num_lines);
			ABORT;
		}
		prefix1 = getprefix(&(yyvsp[(2) - (7)].addr), (yyvsp[(6) - (7)].num));
		prefix2 = getprefix(&(yyvsp[(4) - (7)].addr), (yyvsp[(6) - (7)].num));
		if (!prefix1 || !prefix2) {
			dprintf(LOG_ERR, "address range defined error");
			ABORT;
		}
		if (ipv6addrcmp(&prefix1->addr, &prefix2->addr)) {
			dprintf(LOG_ERR, 
				"address range defined doesn't in the same prefix range");
			ABORT;
		}
		if (ipv6addrcmp(&(yyvsp[(2) - (7)].addr), &(yyvsp[(4) - (7)].addr)) < 0) {
			memcpy(&seg->min, &(yyvsp[(2) - (7)].addr), sizeof(seg->min));
			memcpy(&seg->max, &(yyvsp[(4) - (7)].addr), sizeof(seg->max));
		} else {
			memcpy(&seg->max, &(yyvsp[(2) - (7)].addr), sizeof(seg->max));
			memcpy(&seg->min, &(yyvsp[(4) - (7)].addr), sizeof(seg->min));
		}
		/* check the assigned addresses are not reserved ipv6 addresses */
		if (IN6_IS_ADDR_RESERVED(&seg->max) || IN6_IS_ADDR_RESERVED(&seg->max)) {
			dprintf(LOG_ERR, "config reserved ipv6address");
			ABORT;
		}

		memcpy(&seg->prefix, prefix1, sizeof(seg->prefix));
		memcpy(&seg->free, &seg->min, sizeof(seg->free));
		if (pool)
			seg->pool = pool;
		/* make sure there is no overlap in the rangelist */
		/* the segaddr is sorted by prefix len, thus most specific
		   ipv6 address is going to be assigned.
		 */
		if (!temp_seg) {
			seg->next = NULL;
			seg->prev = NULL;
			link->seglist = seg;
		} else {
			for (; temp_seg; temp_seg = temp_seg->next) { 
				if ( prefix1->plen < temp_seg->prefix.plen) {
					if (temp_seg->next == NULL) {
						temp_seg->next = seg;
						seg->prev = temp_seg;
						seg->next = NULL;
						break;
					}
					continue;
				}
				if (prefix1->plen == temp_seg->prefix.plen) {
	     				if (!(ipv6addrcmp(&seg->min, &temp_seg->max) > 0
					    || ipv6addrcmp(&seg->max, &temp_seg->min) < 0)) {
		   				dprintf(LOG_ERR, "overlap range addr defined");
		   				ABORT;
					}
				}
				if (temp_seg->prev == NULL) { 
					link->seglist = seg;
					seg->prev = NULL;
				} else {
					temp_seg->prev->next = seg;
					seg->prev = temp_seg->prev;
				}
				temp_seg->prev = seg;
				seg->next = temp_seg;
				break;
			}
		}
		free(prefix1);
		free(prefix2);
	}
    break;

  case 41:
#line 508 "server6_parse.y"
    {
		/* return to prev group scope if any */
		currentgroup = pop_double_list(currentgroup);

		/* leave current group scope */
		currentscope = pop_double_list(currentscope);
	}
    break;

  case 51:
#line 534 "server6_parse.y"
    {
		struct scope *groupscope;
		groupscope = (struct scope *)malloc(sizeof(*groupscope));
		if (groupscope == NULL) {
			dprintf(LOG_ERR, "group memory allocation failed");
			ABORT;
		}
		memset(groupscope, 0, sizeof(*groupscope));
		TAILQ_INIT(&groupscope->dnslist.addrlist);
		TAILQ_INIT(&groupscope->siplist);
		TAILQ_INIT(&groupscope->ntplist);
		/* set up current group */
		currentgroup = push_double_list(currentgroup, groupscope);
		if (currentgroup == NULL)
			ABORT;

		/* enter group scope  */
		currentscope = push_double_list(currentscope, groupscope);
		if (currentscope == NULL)
			ABORT;
	}
    break;

  case 52:
#line 559 "server6_parse.y"
    {
		struct host_decl *temp_host = hostlist;
		while (temp_host)
		{
			if (temp_host->iaidinfo.iaid == host->iaidinfo.iaid) {
				dprintf(LOG_ERR, "duplicated host %d redefined", 
					host->iaidinfo.iaid);
				ABORT;
			}
			temp_host = temp_host->next;
		}
		if (currentgroup) 
			host->group = currentgroup->scope;
		host->next = hostlist;
		hostlist = host;
		host = NULL;
		/* leave host scope we know the current scope is not point to NULL*/
		currentscope = pop_double_list(currentscope);
	}
    break;

  case 53:
#line 583 "server6_parse.y"
    {
		struct host_decl *temp_host = hostlist;
		while (temp_host)
		{
			if (!strcmp(temp_host->name, (yyvsp[(2) - (2)].str))) {
				dprintf(LOG_ERR, "duplicated host %s redefined", (yyvsp[(2) - (2)].str));
				ABORT;
			}
			temp_host = temp_host->next;
		}
		host = (struct host_decl *)malloc(sizeof(*host));
		if (host == NULL) {
			dprintf(LOG_ERR, "fail to allocate memory");
			ABORT;
		}
		memset(host, 0, sizeof(*host));
		TAILQ_INIT(&host->addrlist);
		TAILQ_INIT(&host->prefixlist);
		TAILQ_INIT(&host->hostscope.dnslist.addrlist);
		TAILQ_INIT(&host->hostscope.siplist);
		TAILQ_INIT(&host->hostscope.ntplist);
		host->network = ifnetwork;
		strncpy(host->name, (yyvsp[(2) - (2)].str), strlen((yyvsp[(2) - (2)].str)));
		/* enter host scope */
		currentscope = push_double_list(currentscope, &host->hostscope);
		if (currentscope == NULL)
			ABORT;
	}
    break;

  case 56:
#line 620 "server6_parse.y"
    {
		if (host == NULL) {
			dprintf(LOG_DEBUG, "duid should be defined under host decl");
			ABORT;
		}
		configure_duid((yyvsp[(2) - (3)].str), &host->cid);
	}
    break;

  case 59:
#line 633 "server6_parse.y"
    {
	}
    break;

  case 60:
#line 639 "server6_parse.y"
    {
		host->iaidinfo.renewtime = (yyvsp[(3) - (4)].num);
	}
    break;

  case 61:
#line 643 "server6_parse.y"
    {
		host->iaidinfo.rebindtime = (yyvsp[(3) - (4)].num);
	}
    break;

  case 63:
#line 651 "server6_parse.y"
    {
		if (host == NULL) {
			dprintf(LOG_DEBUG, "iaid should be defined under host decl");
			ABORT;
		}
		host->iaidinfo.iaid = (yyvsp[(2) - (3)].num);
	}
    break;

  case 66:
#line 667 "server6_parse.y"
    {
		if (host == NULL) {
			dprintf(LOG_DEBUG, "address should be defined under host decl");
			ABORT;
		}
		dhcp6_add_listval(&host->addrlist, (yyvsp[(1) - (1)].dhcp6addr), DHCP6_LISTVAL_DHCP6ADDR);
		if (hash_add(host_addr_hash_table, &((yyvsp[(1) - (1)].dhcp6addr)->addr), (yyvsp[(1) - (1)].dhcp6addr)) != 0) {
			dprintf(LOG_ERR, "%s" "hash add lease failed for %s",
				FNAME, in6addr2str(&((yyvsp[(1) - (1)].dhcp6addr)->addr), 0));
			free((yyvsp[(1) - (1)].dhcp6addr));
			return (-1);
		}
	}
    break;

  case 67:
#line 681 "server6_parse.y"
    {
		if (host == NULL) {
			dprintf(LOG_DEBUG, "prefix should be defined under host decl");
			ABORT;
		}
		dhcp6_add_listval(&host->prefixlist, (yyvsp[(1) - (1)].dhcp6addr), DHCP6_LISTVAL_DHCP6ADDR);
	}
    break;

  case 69:
#line 693 "server6_parse.y"
    {
		(yyvsp[(3) - (5)].dhcp6addr)->type = IANA;
		(yyval.dhcp6addr) = (yyvsp[(3) - (5)].dhcp6addr);
	}
    break;

  case 70:
#line 701 "server6_parse.y"
    {
		(yyvsp[(3) - (5)].dhcp6addr)->type = IAPD;
		(yyval.dhcp6addr) = (yyvsp[(3) - (5)].dhcp6addr);
	}
    break;

  case 71:
#line 709 "server6_parse.y"
    {
		(yyvsp[(1) - (4)].dhcp6addr)->validlifetime = (yyvsp[(3) - (4)].num);
	}
    break;

  case 72:
#line 713 "server6_parse.y"
    {
		(yyvsp[(1) - (4)].dhcp6addr)->preferlifetime = (yyvsp[(3) - (4)].num);
	}
    break;

  case 73:
#line 717 "server6_parse.y"
    {
		(yyval.dhcp6addr) = (yyvsp[(1) - (1)].dhcp6addr);
	}
    break;

  case 74:
#line 724 "server6_parse.y"
    {
		struct dhcp6_addr *temp;
		temp = (struct dhcp6_addr *)malloc(sizeof(*temp));
		if (temp == NULL) {
			dprintf(LOG_ERR, "v6addr memory allocation failed");
			ABORT;
		}
		memset(temp, 0, sizeof(*temp));
		memcpy(&temp->addr, &(yyvsp[(1) - (4)].addr), sizeof(temp->addr));
		if ((yyvsp[(3) - (4)].num) > 128 || (yyvsp[(3) - (4)].num) < 0) {
			dprintf(LOG_ERR, "invalid prefix length in line %d", num_lines);
			ABORT;
		}
		temp->plen = (yyvsp[(3) - (4)].num);
		(yyval.dhcp6addr) = temp;
	}
    break;

  case 76:
#line 748 "server6_parse.y"
    {		
		if (!currentscope) { 
			currentscope = push_double_list(currentscope, &globalgroup->scope);
			if (currentscope == NULL)
				ABORT;
		}
	}
    break;

  case 77:
#line 756 "server6_parse.y"
    {		
		if (!currentscope) {
			currentscope = push_double_list(currentscope, &globalgroup->scope);
			if (currentscope == NULL)
				ABORT;
		}
		allow = 1;
	}
    break;

  case 78:
#line 765 "server6_parse.y"
    {		
		if (!currentscope) {
			currentscope = push_double_list(currentscope, &globalgroup->scope);
			if (currentscope == NULL)
				ABORT;
		}
	}
    break;

  case 79:
#line 776 "server6_parse.y"
    {
		if (allow) 
			currentscope->scope->allow_flags |= DHCIFF_RAPID_COMMIT;
		else 
			currentscope->scope->send_flags |= DHCIFF_RAPID_COMMIT;
	}
    break;

  case 80:
#line 783 "server6_parse.y"
    {
		if (allow) 
			currentscope->scope->allow_flags |= DHCIFF_TEMP_ADDRS;
		else 
			currentscope->scope->send_flags |= DHCIFF_TEMP_ADDRS;
	}
    break;

  case 81:
#line 790 "server6_parse.y"
    {
		if (allow) 
			currentscope->scope->allow_flags |= DHCIFF_UNICAST;
		else 
			currentscope->scope->send_flags |= DHCIFF_UNICAST;
	}
    break;

  case 82:
#line 797 "server6_parse.y"
    {
		if (allow) 
			currentscope->scope->allow_flags |= DHCIFF_INFO_ONLY;
		else
			currentscope->scope->send_flags |= DHCIFF_INFO_ONLY;
	}
    break;

  case 83:
#line 804 "server6_parse.y"
    {
	}
    break;

  case 84:
#line 807 "server6_parse.y"
    {
	}
    break;

  case 85:
#line 810 "server6_parse.y"
    {
	}
    break;

  case 88:
#line 821 "server6_parse.y"
    {
		dhcp6_add_listval(&currentscope->scope->dnslist.addrlist, &(yyvsp[(1) - (1)].addr),
			DHCP6_LISTVAL_ADDR6);
	}
    break;

  case 91:
#line 833 "server6_parse.y"
    {
		dhcp6_add_listval(&currentscope->scope->siplist, &(yyvsp[(1) - (1)].addr),
			DHCP6_LISTVAL_ADDR6);
	}
    break;

  case 94:
#line 845 "server6_parse.y"
    {
		dhcp6_add_listval(&currentscope->scope->ntplist, &(yyvsp[(1) - (1)].addr),
			DHCP6_LISTVAL_ADDR6);
	}
    break;

  case 95:
#line 851 "server6_parse.y"
    {
		struct domain_list *domainname, *temp;
		int len = 0;
		domainname = (struct domain_list *)malloc(sizeof(*domainname));
		if (domainname == NULL)
			ABORT;
		len = strlen((yyvsp[(1) - (1)].str));
		if (len > MAXDNAME) 
			ABORT;
		strncpy(domainname->name, (yyvsp[(1) - (1)].str), len);
		domainname->name[len] = '\0';
		domainname->next = NULL;
		if (currentscope->scope->dnslist.domainlist == NULL) {
			currentscope->scope->dnslist.domainlist = domainname;
			dprintf(LOG_DEBUG, "add domain name %s", domainname->name);
		} else {
			for (temp = currentscope->scope->dnslist.domainlist; temp;
			     temp = temp->next) {
				if (temp->next == NULL) {
					dprintf(LOG_DEBUG, "add domain name %s", 
						domainname->name);
					temp->next = domainname;
					break;
				}
			}
		}
	}
    break;

  case 98:
#line 887 "server6_parse.y"
    {
		if (!currentscope) {
			currentscope = push_double_list(currentscope, &globalgroup->scope);
			if (currentscope == NULL)
				ABORT;
		}
		currentscope->scope->renew_time = (yyvsp[(2) - (3)].num);
	}
    break;

  case 99:
#line 896 "server6_parse.y"
    {	
		if (!currentscope) {
			currentscope = push_double_list(currentscope, &globalgroup->scope);
			if (currentscope == NULL)
				ABORT;
		}
		currentscope->scope->rebind_time = (yyvsp[(2) - (3)].num);
	}
    break;

  case 100:
#line 905 "server6_parse.y"
    {
		if (!currentscope) {
			currentscope = push_double_list(currentscope, &globalgroup->scope);
			if (currentscope == NULL)
				ABORT;
		}
		currentscope->scope->valid_life_time = (yyvsp[(2) - (3)].num);
		if (currentscope->scope->prefer_life_time != 0 && 
		    currentscope->scope->valid_life_time <
		    currentscope->scope->prefer_life_time) {
			dprintf(LOG_ERR, "%s" 
				"validlifetime is less than preferlifetime", FNAME);
			ABORT;
		}
	}
    break;

  case 101:
#line 921 "server6_parse.y"
    {
		if (!currentscope) {
			currentscope = push_double_list(currentscope, &globalgroup->scope);
			if (currentscope == NULL)
				ABORT;
		}
		currentscope->scope->prefer_life_time = (yyvsp[(2) - (3)].num);
		if (currentscope->scope->valid_life_time != 0 &&
		    currentscope->scope->valid_life_time <
		    currentscope->scope->prefer_life_time) {
			dprintf(LOG_ERR, "%s" 
				"validlifetime is less than preferlifetime", FNAME);
			ABORT;
		}
	}
    break;

  case 102:
#line 937 "server6_parse.y"
    {
		if (!currentscope) {
			currentscope = push_double_list(currentscope, &globalgroup->scope);
			if (currentscope == NULL)
				ABORT;
		}
		if ((yyvsp[(2) - (3)].num) < 0 || (yyvsp[(2) - (3)].num) > 255)
			dprintf(LOG_ERR, "%s" "bad server preference number", FNAME);
		currentscope->scope->server_pref = (yyvsp[(2) - (3)].num);
	}
    break;

  case 103:
#line 951 "server6_parse.y"
    {
		(yyval.num) = (yyvsp[(1) - (1)].num); 
	}
    break;

  case 104:
#line 955 "server6_parse.y"
    {
		(yyval.num) = DHCP6_DURATITION_INFINITE;
	}
    break;

  case 105:
#line 962 "server6_parse.y"
    {
		(yyval.str) = (yyvsp[(1) - (1)].str);
	}
    break;


/* Line 1267 of yacc.c.  */
#line 2413 "y.tab.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 967 "server6_parse.y"



static
void cleanup(void)
{
	/* it is not necessary to free all the pre malloc(), if it fails, 
	 * exit will free them automatically.
	 */
}

void
sfyyerror(char *msg)
{
	cleanup();
	dprintf(LOG_ERR, "%s in line %d: %s ", msg, num_lines, sfyytext);
}

