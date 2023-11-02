/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

ALUExpr *create_alu_expression(ALUExpr::Type2 type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ALUExpr *expr = new ALUExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

/*
AggreExpr *create_aggr_expression(AggrOp type,
                                      Expression *child,
                                      const char *sql_string,
                                      YYLTYPE *llocp)
{
  AggreExpr *expr = new AggreExpr(type, child);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}
*/


#line 138 "yacc_sql.cpp"

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

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_NULLABLE = 4,                   /* NULLABLE  */
  YYSYMBOL_IN = 5,                         /* IN  */
  YYSYMBOL_IS = 6,                         /* IS  */
  YYSYMBOL_MINUS = 7,                      /* MINUS  */
  YYSYMBOL_NEGATIVE_NUM = 8,               /* NEGATIVE_NUM  */
  YYSYMBOL_OR = 9,                         /* OR  */
  YYSYMBOL_CREATE = 10,                    /* CREATE  */
  YYSYMBOL_DROP = 11,                      /* DROP  */
  YYSYMBOL_TABLE = 12,                     /* TABLE  */
  YYSYMBOL_TABLES = 13,                    /* TABLES  */
  YYSYMBOL_INDEX = 14,                     /* INDEX  */
  YYSYMBOL_CALC = 15,                      /* CALC  */
  YYSYMBOL_SELECT = 16,                    /* SELECT  */
  YYSYMBOL_DESC = 17,                      /* DESC  */
  YYSYMBOL_ASC = 18,                       /* ASC  */
  YYSYMBOL_ORDER = 19,                     /* ORDER  */
  YYSYMBOL_BY = 20,                        /* BY  */
  YYSYMBOL_SHOW = 21,                      /* SHOW  */
  YYSYMBOL_SYNC = 22,                      /* SYNC  */
  YYSYMBOL_INSERT = 23,                    /* INSERT  */
  YYSYMBOL_DELETE = 24,                    /* DELETE  */
  YYSYMBOL_UPDATE = 25,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 26,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 27,                    /* RBRACE  */
  YYSYMBOL_COMMA = 28,                     /* COMMA  */
  YYSYMBOL_UNIQUE = 29,                    /* UNIQUE  */
  YYSYMBOL_TRX_BEGIN = 30,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 31,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 32,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 33,                     /* INT_T  */
  YYSYMBOL_STRING_T = 34,                  /* STRING_T  */
  YYSYMBOL_DATE_T = 35,                    /* DATE_T  */
  YYSYMBOL_FLOAT_T = 36,                   /* FLOAT_T  */
  YYSYMBOL_TEXT = 37,                      /* TEXT  */
  YYSYMBOL_HELP = 38,                      /* HELP  */
  YYSYMBOL_EXIT = 39,                      /* EXIT  */
  YYSYMBOL_DOT = 40,                       /* DOT  */
  YYSYMBOL_INTO = 41,                      /* INTO  */
  YYSYMBOL_VALUES = 42,                    /* VALUES  */
  YYSYMBOL_FROM = 43,                      /* FROM  */
  YYSYMBOL_WHERE = 44,                     /* WHERE  */
  YYSYMBOL_NULL_T = 45,                    /* NULL_T  */
  YYSYMBOL_INNER = 46,                     /* INNER  */
  YYSYMBOL_JOIN = 47,                      /* JOIN  */
  YYSYMBOL_AND = 48,                       /* AND  */
  YYSYMBOL_NOT = 49,                       /* NOT  */
  YYSYMBOL_LIKE = 50,                      /* LIKE  */
  YYSYMBOL_MAX = 51,                       /* MAX  */
  YYSYMBOL_MIN = 52,                       /* MIN  */
  YYSYMBOL_SUM = 53,                       /* SUM  */
  YYSYMBOL_AVG = 54,                       /* AVG  */
  YYSYMBOL_COUNT = 55,                     /* COUNT  */
  YYSYMBOL_SET = 56,                       /* SET  */
  YYSYMBOL_ON = 57,                        /* ON  */
  YYSYMBOL_LOAD = 58,                      /* LOAD  */
  YYSYMBOL_DATA = 59,                      /* DATA  */
  YYSYMBOL_INFILE = 60,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 61,                   /* EXPLAIN  */
  YYSYMBOL_EQ = 62,                        /* EQ  */
  YYSYMBOL_LT = 63,                        /* LT  */
  YYSYMBOL_GT = 64,                        /* GT  */
  YYSYMBOL_LE = 65,                        /* LE  */
  YYSYMBOL_GE = 66,                        /* GE  */
  YYSYMBOL_NE = 67,                        /* NE  */
  YYSYMBOL_EXISTS = 68,                    /* EXISTS  */
  YYSYMBOL_NUMBER = 69,                    /* NUMBER  */
  YYSYMBOL_NUMBER_NEGA = 70,               /* NUMBER_NEGA  */
  YYSYMBOL_FLOAT = 71,                     /* FLOAT  */
  YYSYMBOL_FLOAT_NEGA = 72,                /* FLOAT_NEGA  */
  YYSYMBOL_ID = 73,                        /* ID  */
  YYSYMBOL_SSS = 74,                       /* SSS  */
  YYSYMBOL_DATESSS = 75,                   /* DATESSS  */
  YYSYMBOL_76_ = 76,                       /* '+'  */
  YYSYMBOL_77_ = 77,                       /* '*'  */
  YYSYMBOL_78_ = 78,                       /* '/'  */
  YYSYMBOL_UNARY_MINUS = 79,               /* UNARY_MINUS  */
  YYSYMBOL_YYACCEPT = 80,                  /* $accept  */
  YYSYMBOL_commands = 81,                  /* commands  */
  YYSYMBOL_command_wrapper = 82,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 83,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 84,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 85,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 86,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 87,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 88,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 89,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 90,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 91,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 92,         /* create_index_stmt  */
  YYSYMBOL_id_list = 93,                   /* id_list  */
  YYSYMBOL_id = 94,                        /* id  */
  YYSYMBOL_drop_index_stmt = 95,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 96,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 97,             /* attr_def_list  */
  YYSYMBOL_attr_def = 98,                  /* attr_def  */
  YYSYMBOL_number = 99,                    /* number  */
  YYSYMBOL_type = 100,                     /* type  */
  YYSYMBOL_insert_stmt = 101,              /* insert_stmt  */
  YYSYMBOL_record_list = 102,              /* record_list  */
  YYSYMBOL_record = 103,                   /* record  */
  YYSYMBOL_value_list = 104,               /* value_list  */
  YYSYMBOL_value = 105,                    /* value  */
  YYSYMBOL_delete_stmt = 106,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 107,              /* update_stmt  */
  YYSYMBOL_update_options = 108,           /* update_options  */
  YYSYMBOL_update_option = 109,            /* update_option  */
  YYSYMBOL_select_stmt = 110,              /* select_stmt  */
  YYSYMBOL_opt_order_by = 111,             /* opt_order_by  */
  YYSYMBOL_order_by_list = 112,            /* order_by_list  */
  YYSYMBOL_order_by_unit = 113,            /* order_by_unit  */
  YYSYMBOL_sub_select_stmt = 114,          /* sub_select_stmt  */
  YYSYMBOL_calc_stmt = 115,                /* calc_stmt  */
  YYSYMBOL_expression_list = 116,          /* expression_list  */
  YYSYMBOL_expression = 117,               /* expression  */
  YYSYMBOL_add_expr_list = 118,            /* add_expr_list  */
  YYSYMBOL_add_expr = 119,                 /* add_expr  */
  YYSYMBOL_mul_expr = 120,                 /* mul_expr  */
  YYSYMBOL_base_expr = 121,                /* base_expr  */
  YYSYMBOL_value2 = 122,                   /* value2  */
  YYSYMBOL_cal_attr = 123,                 /* cal_attr  */
  YYSYMBOL_aggr_func = 124,                /* aggr_func  */
  YYSYMBOL_rel_list = 125,                 /* rel_list  */
  YYSYMBOL_join_list = 126,                /* join_list  */
  YYSYMBOL_on = 127,                       /* on  */
  YYSYMBOL_where = 128,                    /* where  */
  YYSYMBOL_condition_list = 129,           /* condition_list  */
  YYSYMBOL_condition = 130,                /* condition  */
  YYSYMBOL_cal_comp_op = 131,              /* cal_comp_op  */
  YYSYMBOL_logical_comp_op = 132,          /* logical_comp_op  */
  YYSYMBOL_load_data_stmt = 133,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 134,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 135,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 136             /* opt_semicolon  */
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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
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
#define YYFINAL  82
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   390

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  162
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  291

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   331


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    77,    76,     2,     2,     2,    78,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    79
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   251,   251,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   282,   288,   293,   299,   305,   311,   317,
     324,   330,   338,   359,   384,   387,   398,   407,   417,   436,
     439,   452,   461,   470,   479,   489,   498,   506,   517,   520,
     521,   522,   523,   526,   542,   545,   559,   575,   578,   589,
     593,   597,   601,   605,   611,   616,   625,   637,   676,   679,
     689,   697,   708,   746,   749,   762,   765,   778,   785,   792,
     800,   807,   815,   826,   850,   860,   865,   876,   879,   882,
     885,   888,   892,   895,   902,   907,   918,   921,   924,   929,
     932,   935,   938,   943,   947,   952,   962,   966,   970,   976,
     982,   988,   993,  1000,  1007,  1014,  1023,  1029,  1036,  1048,
    1049,  1050,  1051,  1052,  1056,  1059,  1072,  1075,  1092,  1095,
    1101,  1104,  1110,  1113,  1118,  1124,  1132,  1141,  1150,  1159,
    1168,  1181,  1191,  1200,  1211,  1212,  1213,  1214,  1215,  1216,
    1217,  1218,  1219,  1220,  1221,  1222,  1225,  1226,  1229,  1242,
    1250,  1260,  1261
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
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON",
  "NULLABLE", "IN", "IS", "MINUS", "NEGATIVE_NUM", "OR", "CREATE", "DROP",
  "TABLE", "TABLES", "INDEX", "CALC", "SELECT", "DESC", "ASC", "ORDER",
  "BY", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE",
  "COMMA", "UNIQUE", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T",
  "STRING_T", "DATE_T", "FLOAT_T", "TEXT", "HELP", "EXIT", "DOT", "INTO",
  "VALUES", "FROM", "WHERE", "NULL_T", "INNER", "JOIN", "AND", "NOT",
  "LIKE", "MAX", "MIN", "SUM", "AVG", "COUNT", "SET", "ON", "LOAD", "DATA",
  "INFILE", "EXPLAIN", "EQ", "LT", "GT", "LE", "GE", "NE", "EXISTS",
  "NUMBER", "NUMBER_NEGA", "FLOAT", "FLOAT_NEGA", "ID", "SSS", "DATESSS",
  "'+'", "'*'", "'/'", "UNARY_MINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "id_list", "id",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "number", "type", "insert_stmt", "record_list", "record", "value_list",
  "value", "delete_stmt", "update_stmt", "update_options", "update_option",
  "select_stmt", "opt_order_by", "order_by_list", "order_by_unit",
  "sub_select_stmt", "calc_stmt", "expression_list", "expression",
  "add_expr_list", "add_expr", "mul_expr", "base_expr", "value2",
  "cal_attr", "aggr_func", "rel_list", "join_list", "on", "where",
  "condition_list", "condition", "cal_comp_op", "logical_comp_op",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-221)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     299,    48,    16,   213,   163,   -67,    10,  -221,    32,    -6,
     -23,  -221,  -221,  -221,  -221,  -221,    40,   -16,   299,   137,
     136,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,    79,    91,   153,    95,    96,   213,   213,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,     7,  -221,   313,   163,
    -221,  -221,  -221,  -221,  -221,   130,  -221,   129,     3,    73,
    -221,  -221,  -221,   147,  -221,  -221,   103,   105,   123,   118,
     121,  -221,  -221,  -221,  -221,   162,   134,   119,  -221,   138,
    -221,    11,   213,   213,   213,   213,   213,  -221,    14,   120,
     125,   163,   163,   163,   313,   313,    24,   154,   155,   139,
      67,   151,   140,   156,   169,   157,  -221,    78,  -221,    78,
    -221,  -221,  -221,  -221,   183,    73,  -221,    73,  -221,  -221,
      -7,   200,   205,    55,  -221,   179,   214,   -30,  -221,  -221,
    -221,  -221,  -221,  -221,   203,   110,   222,   225,   186,  -221,
     187,   206,  -221,   188,  -221,    67,   234,    86,   132,   -34,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,   240,     2,
    -221,     6,   237,    88,   139,   155,  -221,  -221,   252,  -221,
    -221,  -221,  -221,  -221,   -13,   140,   238,   193,   241,   183,
     221,   155,   242,   250,   205,  -221,  -221,   235,   163,  -221,
    -221,   202,  -221,    66,   202,   244,    55,    55,   265,  -221,
    -221,  -221,   214,  -221,   218,   217,  -221,   247,   222,  -221,
    -221,   266,   193,  -221,   220,   276,  -221,    67,   269,   234,
    -221,   254,  -221,     4,  -221,  -221,     4,   174,  -221,  -221,
    -221,  -221,  -221,  -221,   271,  -221,  -221,   193,   272,   266,
     243,   281,  -221,   250,  -221,  -221,   239,   250,   104,   266,
    -221,   284,    55,   206,   245,  -221,   183,   286,  -221,   274,
    -221,  -221,  -221,  -221,     9,   289,   155,  -221,  -221,  -221,
    -221,   253,   245,  -221,   298,   143,   289,  -221,  -221,  -221,
    -221
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     161,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,     0,   110,   106,
     108,   107,   109,   111,   112,    84,    85,    93,     0,     0,
     119,   120,   123,   122,   121,   114,   113,     0,    94,    96,
      99,   104,   105,     0,    31,    30,     0,     0,     0,     0,
       0,   159,     1,   162,     2,     0,     0,     0,    29,     0,
      92,     0,     0,     0,     0,     0,     0,   102,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   130,     0,
       0,     0,     0,     0,     0,     0,    91,    88,    86,    87,
      89,    90,   103,   115,   124,    98,    95,    97,   100,   101,
       0,     0,     0,   132,    66,     0,    68,     0,    63,    59,
      61,    64,    65,   160,     0,     0,    39,     0,     0,    37,
       0,   126,   117,     0,   116,     0,    54,     0,     0,     0,
     150,   144,   145,   146,   147,   148,   149,   154,     0,     0,
     131,   133,     0,     0,     0,   130,    60,    62,     0,    49,
      50,    52,    51,    46,    47,     0,     0,     0,     0,   124,
       0,   130,     0,    57,     0,    53,   152,     0,     0,   151,
     155,     0,   156,     0,   143,     0,   132,   132,     0,   142,
      70,    71,    68,    67,     0,     0,    45,     0,    39,    38,
      36,    34,     0,   125,     0,    73,   118,     0,     0,    54,
     153,     0,   137,   139,   157,   138,   136,     0,   141,   135,
     134,    69,   158,    48,     0,    44,    40,     0,     0,    34,
     128,     0,    72,    57,    56,    55,     0,    57,    41,    34,
      32,     0,   132,   126,     0,    58,   124,     0,    43,     0,
      35,    33,   129,   127,    77,    75,   130,   140,    42,    79,
      80,     0,     0,    74,     0,    78,    75,    83,    81,    82,
      76
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -221,  -221,   309,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,  -220,  -203,  -221,  -221,   114,   148,  -221,
    -221,  -221,    99,   141,  -142,  -151,  -221,  -221,   122,   166,
    -221,  -221,    50,    59,  -148,  -221,   249,   128,   -99,    -4,
     -29,   -46,    -1,  -221,  -221,  -184,    80,  -221,  -174,  -159,
    -221,    -3,  -221,  -221,  -221,  -221,  -221
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   248,   221,    31,    32,   186,   146,   244,
     184,    33,   195,   156,   228,   143,    34,    35,   175,   136,
      36,   252,   283,   275,   168,    37,    55,    56,    67,   169,
      69,    70,    71,    72,    73,   151,   191,   263,   134,   170,
     171,   172,   205,    38,    39,    40,    84
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      68,   213,    57,   126,   193,   223,    74,   202,   157,   101,
     101,   101,    97,   215,    92,   206,   199,   225,    92,   249,
     152,   101,   210,    75,   209,   211,   279,   280,    44,   261,
      45,   102,   216,   153,   200,    93,   217,    77,   116,   270,
     176,   122,   177,    80,   259,    57,    57,   239,   240,   281,
      78,   203,   160,   232,   207,    98,   235,   238,   128,   129,
      41,   157,    42,    58,   161,   162,   163,   164,   165,   166,
     167,   234,   125,    76,   127,   137,   253,    43,   103,   103,
     103,   158,   276,    94,    95,    96,   257,    94,    95,    96,
     103,    57,    57,    57,    57,    57,   137,   130,    68,   231,
      48,   131,   284,   272,   159,   160,    60,    61,    62,    63,
      64,   265,   138,    79,   208,   267,   199,   161,   162,   163,
     164,   165,   166,   167,    49,    50,    51,    52,    65,    53,
      54,   196,    66,   138,   200,   197,   139,    82,   140,    83,
      58,   141,   142,   179,   180,   181,   182,   183,   198,   268,
     104,   105,    85,   269,    98,    95,    96,   139,    59,   140,
     288,   289,   141,   142,    86,   201,   204,    87,    88,    89,
      99,    58,   100,   106,    90,    91,   107,    48,   108,   109,
     110,   111,   137,    60,    61,    62,    63,    64,   112,    59,
     198,   113,   114,   123,    68,   115,   132,   233,   124,   133,
     236,    49,    50,    51,    52,    65,    53,    54,    48,    66,
      58,   150,   135,   145,    60,    61,    62,    63,    64,   138,
     117,    46,   119,   120,   121,   144,   148,   154,   158,   147,
     149,   155,    49,    50,    51,    52,    65,    53,    54,    47,
      66,   173,   174,   139,   178,   140,   157,    48,   141,   142,
     185,   187,   190,    60,    61,    62,    63,    64,    48,   188,
     189,   192,   194,   208,   214,   219,   220,   222,   224,   226,
     237,    49,    50,    51,    52,    65,    53,    54,   227,    66,
     230,   198,    49,    50,    51,    52,   243,    53,    54,   159,
     160,   242,   245,   250,   247,   251,   254,   256,   258,   260,
     262,   264,   161,   162,   163,   164,   165,   166,   167,     1,
       2,   271,   266,   277,     3,     4,     5,   282,   274,   278,
       6,     7,     8,     9,    10,   287,   285,    81,   255,    11,
      12,    13,   246,   218,   241,   229,   290,    14,    15,    59,
     212,   286,   118,   273,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    16,     0,    17,    48,     0,
      18,     0,     0,     0,    60,    61,    62,    63,    64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    49,    50,    51,    52,    65,    53,    54,     0,
      66
};

static const yytype_int16 yycheck[] =
{
       4,   175,     3,   102,   155,   189,    73,     5,     6,     7,
       7,     7,    58,    26,     7,     9,    50,   191,     7,   222,
      27,     7,   173,    13,   172,   173,    17,    18,    12,   249,
      14,    28,    45,    40,    68,    28,    49,    43,    27,   259,
      70,    27,    72,    59,   247,    46,    47,   206,   207,    40,
      73,    49,    50,   201,    48,    59,   204,   205,   104,   105,
      12,     6,    14,     8,    62,    63,    64,    65,    66,    67,
      68,     5,   101,    41,   103,     8,   227,    29,    76,    76,
      76,    26,   266,    76,    77,    78,   237,    76,    77,    78,
      76,    92,    93,    94,    95,    96,     8,    73,   102,   198,
      45,    77,   276,   262,    49,    50,    51,    52,    53,    54,
      55,   253,    45,    73,    26,   257,    50,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    45,    77,    45,    68,    49,    69,     0,    71,     3,
       8,    74,    75,    33,    34,    35,    36,    37,    16,    45,
      77,    78,    73,    49,   158,    77,    78,    69,    26,    71,
      17,    18,    74,    75,    73,   168,   169,    14,    73,    73,
      40,     8,    43,    26,    46,    47,    73,    45,    73,    56,
      62,    60,     8,    51,    52,    53,    54,    55,    26,    26,
      16,    57,    73,    73,   198,    57,    42,   201,    73,    44,
     204,    69,    70,    71,    72,    73,    74,    75,    45,    77,
       8,    28,    73,    73,    51,    52,    53,    54,    55,    45,
      92,     8,    94,    95,    96,    74,    57,    27,    26,    73,
      73,    26,    69,    70,    71,    72,    73,    74,    75,    26,
      77,    62,    28,    69,    41,    71,     6,    45,    74,    75,
      28,    26,    46,    51,    52,    53,    54,    55,    45,    73,
      73,    73,    28,    26,    12,    27,    73,    26,    47,    27,
      26,    69,    70,    71,    72,    73,    74,    75,    28,    77,
      45,    16,    69,    70,    71,    72,    69,    74,    75,    49,
      50,    73,    45,    73,    28,    19,    27,    43,    27,    27,
      57,    20,    62,    63,    64,    65,    66,    67,    68,    10,
      11,    27,    73,    27,    15,    16,    17,    28,    73,    45,
      21,    22,    23,    24,    25,    27,    73,    18,   229,    30,
      31,    32,   218,   185,   212,   194,   286,    38,    39,    26,
     174,   282,    93,   263,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    58,    45,    -1,
      61,    -1,    -1,    -1,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    70,    71,    72,    73,    74,    75,    -1,
      77
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    11,    15,    16,    17,    21,    22,    23,    24,
      25,    30,    31,    32,    38,    39,    56,    58,    61,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    95,    96,   101,   106,   107,   110,   115,   133,   134,
     135,    12,    14,    29,    12,    14,     8,    26,    45,    69,
      70,    71,    72,    74,    75,   116,   117,   122,     8,    26,
      51,    52,    53,    54,    55,    73,    77,   118,   119,   120,
     121,   122,   123,   124,    73,    13,    41,    43,    73,    73,
      59,    82,     0,     3,   136,    73,    73,    14,    73,    73,
     117,   117,     7,    28,    76,    77,    78,   121,   119,    40,
      43,     7,    28,    76,    77,    78,    26,    73,    73,    56,
      62,    60,    26,    57,    73,    57,    27,   117,   116,   117,
     117,   117,    27,    73,    73,   120,   118,   120,   121,   121,
      73,    77,    42,    44,   128,    73,   109,     8,    45,    69,
      71,    74,    75,   105,    74,    73,    98,    73,    57,    73,
      28,   125,    27,    40,    27,    26,   103,     6,    26,    49,
      50,    62,    63,    64,    65,    66,    67,    68,   114,   119,
     129,   130,   131,    62,    28,   108,    70,    72,    41,    33,
      34,    35,    36,    37,   100,    28,    97,    26,    73,    73,
      46,   126,    73,   105,    28,   102,    45,    49,    16,    50,
      68,   131,     5,    49,   131,   132,     9,    48,    26,   114,
     105,   114,   109,   128,    12,    26,    45,    49,    98,    27,
      73,    94,    26,   125,    47,   128,    27,    28,   104,   103,
      45,   118,   114,   119,     5,   114,   119,    26,   114,   129,
     129,   108,    73,    69,    99,    45,    97,    28,    93,    94,
      73,    19,   111,   105,    27,   102,    43,   105,    27,    94,
      27,    93,    57,   127,    20,   104,    73,   104,    45,    49,
      93,    27,   129,   126,    73,   113,   125,    27,    45,    17,
      18,    40,    28,   112,   128,    73,   113,    27,    17,    18,
     112
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    92,    93,    93,    94,    95,    96,    97,
      97,    98,    98,    98,    98,    98,    98,    98,    99,   100,
     100,   100,   100,   101,   102,   102,   103,   104,   104,   105,
     105,   105,   105,   105,   105,   105,   106,   107,   108,   108,
     109,   109,   110,   111,   111,   112,   112,   113,   113,   113,
     113,   113,   113,   114,   115,   116,   116,   117,   117,   117,
     117,   117,   117,   117,   118,   118,   119,   119,   119,   120,
     120,   120,   120,   121,   121,   121,   122,   122,   122,   122,
     122,   122,   122,   123,   123,   123,   123,   123,   123,   124,
     124,   124,   124,   124,   125,   125,   126,   126,   127,   127,
     128,   128,   129,   129,   129,   129,   130,   130,   130,   130,
     130,   130,   130,   130,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   132,   132,   133,   134,
     135,   136,   136
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     9,    10,     0,     3,     1,     5,     7,     0,
       3,     5,     7,     6,     4,     3,     2,     2,     1,     1,
       1,     1,     1,     6,     0,     3,     4,     0,     3,     1,
       2,     1,     2,     1,     1,     1,     4,     6,     0,     3,
       3,     3,     8,     0,     4,     0,     3,     1,     3,     2,
       2,     4,     4,     8,     2,     1,     3,     3,     3,     3,
       3,     3,     2,     1,     1,     3,     1,     3,     3,     1,
       3,     3,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     4,     4,     6,     1,
       1,     1,     1,     1,     0,     3,     0,     5,     0,     2,
       0,     2,     0,     1,     3,     3,     3,     3,     3,     3,
       6,     3,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     3,     1,     2,     1,     2,     7,     2,
       4,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
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

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
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
  YYLTYPE *yylloc;
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
    YYNOMEM;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc, scanner);
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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 252 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1903 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 282 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1912 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 288 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1920 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 293 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1928 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 299 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1936 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 305 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1944 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 311 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1952 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 317 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1962 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 324 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1970 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 330 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1980 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE id id_list RBRACE  */
#line 339 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      //create_index.attribute_name = $7
      std::vector<std::string> *src_attrs = (yyvsp[-1].index_attr_list);
      if (src_attrs != nullptr) {
        create_index.attribute_name.swap(*src_attrs);
      }
      std::string temp = (yyvsp[-2].string);
      create_index.attribute_name.emplace_back(temp);
      std::reverse(create_index.attribute_name.begin(), create_index.attribute_name.end());
      delete (yyvsp[-2].string);
    
      create_index.unique = false;
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      //free($7);
    }
#line 2005 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE id id_list RBRACE  */
#line 360 "yacc_sql.y"
                {
			(yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      //create_index.attribute_name = $7
      std::vector<std::string> *src_attrs = (yyvsp[-1].index_attr_list);
      if (src_attrs != nullptr) {
      create_index.attribute_name.swap(*src_attrs);
      }
      std::string temp = (yyvsp[-2].string);
      create_index.attribute_name.push_back(temp);
      std::reverse(create_index.attribute_name.begin(), create_index.attribute_name.end());//保持顺序
      delete (yyvsp[-2].string);
      create_index.unique = true;
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      //free($8);
      
		}
#line 2030 "yacc_sql.cpp"
    break;

  case 34: /* id_list: %empty  */
#line 384 "yacc_sql.y"
    {
      (yyval.index_attr_list) = nullptr;
    }
#line 2038 "yacc_sql.cpp"
    break;

  case 35: /* id_list: COMMA id id_list  */
#line 388 "yacc_sql.y"
    {
      if ((yyvsp[0].index_attr_list) != nullptr) {
        (yyval.index_attr_list) = (yyvsp[0].index_attr_list);
      } else {
        (yyval.index_attr_list) = new std::vector<std::string>;
      }
      (yyval.index_attr_list)->push_back((yyvsp[-1].string));
      delete (yyvsp[-1].string);
    }
#line 2052 "yacc_sql.cpp"
    break;

  case 36: /* id: ID  */
#line 399 "yacc_sql.y"
        {

		(yyval.string) = (yyvsp[0].string);
    //free($1);
	}
#line 2062 "yacc_sql.cpp"
    break;

  case 37: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 408 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2074 "yacc_sql.cpp"
    break;

  case 38: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 418 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 2094 "yacc_sql.cpp"
    break;

  case 39: /* attr_def_list: %empty  */
#line 436 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2102 "yacc_sql.cpp"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 440 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2116 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type LBRACE number RBRACE  */
#line 453 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      //$$->nullable = false;
      free((yyvsp[-4].string));
    }
#line 2129 "yacc_sql.cpp"
    break;

  case 42: /* attr_def: ID type LBRACE number RBRACE NOT NULL_T  */
#line 462 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-5].number);
      (yyval.attr_info)->name = (yyvsp[-6].string);
      (yyval.attr_info)->length = (yyvsp[-3].number);
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-6].string));
    }
#line 2142 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type LBRACE number RBRACE NULL_T  */
#line 471 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-5].string));
    }
#line 2155 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type NOT NULL_T  */
#line 480 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-2].number);
      (yyval.attr_info)->name = (yyvsp[-3].string);
      (yyval.attr_info)->length = 4;
      //$$->nullable = true;
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-3].string));
    }
#line 2169 "yacc_sql.cpp"
    break;

  case 45: /* attr_def: ID type NULL_T  */
#line 490 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-2].string));
    }
#line 2182 "yacc_sql.cpp"
    break;

  case 46: /* attr_def: ID TEXT  */
#line 499 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = CHARS;
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 65535;
      free((yyvsp[-1].string));
    }
#line 2194 "yacc_sql.cpp"
    break;

  case 47: /* attr_def: ID type  */
#line 507 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      //$$->nullable = false;
      free((yyvsp[-1].string));
    }
#line 2207 "yacc_sql.cpp"
    break;

  case 48: /* number: NUMBER  */
#line 517 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2213 "yacc_sql.cpp"
    break;

  case 49: /* type: INT_T  */
#line 520 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2219 "yacc_sql.cpp"
    break;

  case 50: /* type: STRING_T  */
#line 521 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2225 "yacc_sql.cpp"
    break;

  case 51: /* type: FLOAT_T  */
#line 522 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2231 "yacc_sql.cpp"
    break;

  case 52: /* type: DATE_T  */
#line 523 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2237 "yacc_sql.cpp"
    break;

  case 53: /* insert_stmt: INSERT INTO ID VALUES record record_list  */
#line 527 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-3].string);
      if ((yyvsp[0].record_list) != nullptr) {
        (yyval.sql_node)->insertion.valuerecords.swap(*(yyvsp[0].record_list));
      }
      (yyval.sql_node)->insertion.valuerecords.emplace_back(*(yyvsp[-1].record));
      std::reverse((yyval.sql_node)->insertion.valuerecords.begin(), (yyval.sql_node)->insertion.valuerecords.end());
      delete (yyvsp[-1].record);
      free((yyvsp[-3].string));
    }
#line 2253 "yacc_sql.cpp"
    break;

  case 54: /* record_list: %empty  */
#line 542 "yacc_sql.y"
    {
      (yyval.record_list) =  nullptr;
    }
#line 2261 "yacc_sql.cpp"
    break;

  case 55: /* record_list: COMMA record record_list  */
#line 545 "yacc_sql.y"
                               {
        if ((yyvsp[0].record_list) != nullptr) {
        (yyval.record_list) = (yyvsp[0].record_list);
      } else {
        (yyval.record_list) = new std::vector<ValueRecord>;
      }
      ValueRecord current;
      current.values.swap(*(yyvsp[-1].record));
      (yyval.record_list)->push_back(current);
      //$$->emplace_back(*$2);
      free((yyvsp[-1].record));
    }
#line 2278 "yacc_sql.cpp"
    break;

  case 56: /* record: LBRACE value value_list RBRACE  */
#line 559 "yacc_sql.y"
                                   {
        if ((yyvsp[-1].value_list) != nullptr) {
          (yyval.record) = (yyvsp[-1].value_list);
        }else {
          (yyval.record) = new std::vector<Value>;
        }
        //Record current;
        //current.values.swap(*$2);
        //$$->push_back(current);
        (yyval.record)->emplace_back(*(yyvsp[-2].value));
        std::reverse((yyval.record)->begin(), (yyval.record)->end());
        delete (yyvsp[-2].value);
    }
#line 2296 "yacc_sql.cpp"
    break;

  case 57: /* value_list: %empty  */
#line 575 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2304 "yacc_sql.cpp"
    break;

  case 58: /* value_list: COMMA value value_list  */
#line 578 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2318 "yacc_sql.cpp"
    break;

  case 59: /* value: NUMBER  */
#line 589 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2327 "yacc_sql.cpp"
    break;

  case 60: /* value: NEGATIVE_NUM NUMBER_NEGA  */
#line 593 "yacc_sql.y"
                               {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
#line 2336 "yacc_sql.cpp"
    break;

  case 61: /* value: FLOAT  */
#line 597 "yacc_sql.y"
            {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2345 "yacc_sql.cpp"
    break;

  case 62: /* value: NEGATIVE_NUM FLOAT_NEGA  */
#line 601 "yacc_sql.y"
                              {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
#line 2354 "yacc_sql.cpp"
    break;

  case 63: /* value: NULL_T  */
#line 605 "yacc_sql.y"
            { //要放到SSS的前面
      //char *tmp = common::substr($1,1,strlen($1)-2);
      (yyval.value) = new Value(0);
      (yyval.value)->set_null_value();
      //free(tmp);
    }
#line 2365 "yacc_sql.cpp"
    break;

  case 64: /* value: SSS  */
#line 611 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2375 "yacc_sql.cpp"
    break;

  case 65: /* value: DATESSS  */
#line 616 "yacc_sql.y"
             {
			char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(1, tmp);
      free(tmp);
		}
#line 2385 "yacc_sql.cpp"
    break;

  case 66: /* delete_stmt: DELETE FROM ID where  */
#line 626 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2399 "yacc_sql.cpp"
    break;

  case 67: /* update_stmt: UPDATE ID SET update_option update_options where  */
#line 638 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-4].string);

      std::vector<SetVariableSqlNode> u_list;
      if((yyvsp[-1].attr_name_a_values)!=nullptr){
          u_list.swap(*(yyvsp[-1].attr_name_a_values));
          delete (yyvsp[-1].attr_name_a_values);
      }
      u_list.push_back(*(yyvsp[-2].attr_name_value));
      for(int i = u_list.size(); i > 0 ;i--)
      {
        (yyval.sql_node)->update.attribute_name.push_back(u_list[i-1].name);
        if(u_list[i-1].type == 0){
          value_list temp;
          temp.type = 0;
          temp.value = u_list[i-1].value;
          (yyval.sql_node)->update.values.push_back(temp);
        }
        else{
          value_list temp;
          temp.type = 1;
          temp.sub_query = u_list[i-1].query;
          (yyval.sql_node)->update.values.push_back(temp);
        }
      }
      //delete u_list;
     
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-4].string));
      free((yyvsp[-2].attr_name_value));
    }
#line 2439 "yacc_sql.cpp"
    break;

  case 68: /* update_options: %empty  */
#line 676 "yacc_sql.y"
    {
      (yyval.attr_name_a_values) = nullptr;
    }
#line 2447 "yacc_sql.cpp"
    break;

  case 69: /* update_options: COMMA update_option update_options  */
#line 679 "yacc_sql.y"
                                                     {
      if ((yyvsp[0].attr_name_a_values) != nullptr) {
        (yyval.attr_name_a_values) = (yyvsp[0].attr_name_a_values);
      } else {
        (yyval.attr_name_a_values) = new std::vector<SetVariableSqlNode>;
      }
      (yyval.attr_name_a_values)->emplace_back(*(yyvsp[-1].attr_name_value));
       delete (yyvsp[-1].attr_name_value);
		}
#line 2461 "yacc_sql.cpp"
    break;

  case 70: /* update_option: ID EQ value  */
#line 689 "yacc_sql.y"
                            {
    	(yyval.attr_name_value) = new SetVariableSqlNode();
      (yyval.attr_name_value)->value = *(yyvsp[0].value);
      (yyval.attr_name_value)->name = (yyvsp[-2].string);
      (yyval.attr_name_value)->type = 0;
      free((yyvsp[-2].string));
      free((yyvsp[0].value));
		}
#line 2474 "yacc_sql.cpp"
    break;

  case 71: /* update_option: ID EQ sub_select_stmt  */
#line 697 "yacc_sql.y"
                            {
    	(yyval.attr_name_value) = new SetVariableSqlNode();
      (yyval.attr_name_value)->query = (yyvsp[0].sub_sql_node);
      (yyval.attr_name_value)->name = (yyvsp[-2].string);
      (yyval.attr_name_value)->type = 1;
      free((yyvsp[-2].string));
		}
#line 2486 "yacc_sql.cpp"
    break;

  case 72: /* select_stmt: SELECT add_expr_list FROM ID rel_list join_list where opt_order_by  */
#line 709 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);

      if ((yyvsp[-6].expression_list) != nullptr) {
        std::reverse((yyvsp[-6].expression_list)->begin(), (yyvsp[-6].expression_list)->end());
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-6].expression_list));
        delete (yyvsp[-6].expression_list);
      }

      if ((yyvsp[-3].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-3].relation_list));
        delete (yyvsp[-3].relation_list);
      }
      (yyval.sql_node)->selection.relations.push_back((yyvsp[-4].string));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      if ((yyvsp[-2].join_lists) != nullptr) {
        (yyval.sql_node)->selection.joinTables.swap(*(yyvsp[-2].join_lists));
        delete (yyvsp[-2].join_lists);
        std::reverse((yyval.sql_node)->selection.joinTables.begin(), (yyval.sql_node)->selection.joinTables.end());
      }

      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }

      if ((yyvsp[0].order_by) != nullptr) {
        (yyval.sql_node)->selection.orderBy.swap(*(yyvsp[0].order_by));
        delete (yyvsp[0].order_by);
      }

      free((yyvsp[-4].string));
    }
#line 2525 "yacc_sql.cpp"
    break;

  case 73: /* opt_order_by: %empty  */
#line 746 "yacc_sql.y"
    {
      (yyval.order_by) = nullptr;
    }
#line 2533 "yacc_sql.cpp"
    break;

  case 74: /* opt_order_by: ORDER BY order_by_unit order_by_list  */
#line 749 "yacc_sql.y"
                                          {
        if((yyvsp[0].order_by)!=nullptr){
          (yyval.order_by) = (yyvsp[0].order_by);
        }
        else{
          (yyval.order_by) = new std::vector<OrderBySqlNode>;
        }
        (yyval.order_by)->emplace_back(*(yyvsp[-1].order_by_node));
        delete (yyvsp[-1].order_by_node);
        std::reverse((yyval.order_by)->begin(),(yyval.order_by)->end());
    }
#line 2549 "yacc_sql.cpp"
    break;

  case 75: /* order_by_list: %empty  */
#line 762 "yacc_sql.y"
    {
      (yyval.order_by) = nullptr;
    }
#line 2557 "yacc_sql.cpp"
    break;

  case 76: /* order_by_list: COMMA order_by_unit order_by_list  */
#line 766 "yacc_sql.y"
    {
        if((yyvsp[0].order_by)!=nullptr){
          (yyval.order_by) = (yyvsp[0].order_by);
        }
        else{
          (yyval.order_by) = new std::vector<OrderBySqlNode>;
        }
        (yyval.order_by)->emplace_back(*(yyvsp[-1].order_by_node));
        delete (yyvsp[-1].order_by_node);
    }
#line 2572 "yacc_sql.cpp"
    break;

  case 77: /* order_by_unit: ID  */
#line 779 "yacc_sql.y"
        {
      (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[0].string);
      //$$->order_relation = NULL;
	}
#line 2582 "yacc_sql.cpp"
    break;

  case 78: /* order_by_unit: ID DOT ID  */
#line 786 "yacc_sql.y"
        {
		  (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[0].string);
      (yyval.order_by_node)->order_relation = (yyvsp[-2].string);
	}
#line 2592 "yacc_sql.cpp"
    break;

  case 79: /* order_by_unit: ID DESC  */
#line 793 "yacc_sql.y"
        {
      (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[-1].string);
      //$$->order_relation = NULL;
      (yyval.order_by_node)->asc_type = false;
	}
#line 2603 "yacc_sql.cpp"
    break;

  case 80: /* order_by_unit: ID ASC  */
#line 801 "yacc_sql.y"
        {
      (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[-1].string);
      //$$->order_relation = NULL;
	}
#line 2613 "yacc_sql.cpp"
    break;

  case 81: /* order_by_unit: ID DOT ID DESC  */
#line 808 "yacc_sql.y"
        {
      (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[-1].string);
      (yyval.order_by_node)->order_relation = (yyvsp[-3].string);
      (yyval.order_by_node)->asc_type = false;
	}
#line 2624 "yacc_sql.cpp"
    break;

  case 82: /* order_by_unit: ID DOT ID ASC  */
#line 816 "yacc_sql.y"
        {
		  (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[-1].string);
      (yyval.order_by_node)->order_relation = (yyvsp[-3].string);
	}
#line 2634 "yacc_sql.cpp"
    break;

  case 83: /* sub_select_stmt: LBRACE SELECT add_expr_list FROM ID rel_list where RBRACE  */
#line 827 "yacc_sql.y"
    {
      (yyval.sub_sql_node) = new SelectSqlNode;
      if ((yyvsp[-5].expression_list) != nullptr) {
        std::reverse((yyvsp[-5].expression_list)->begin(), (yyvsp[-5].expression_list)->end());
        (yyval.sub_sql_node)->expressions.swap(*(yyvsp[-5].expression_list));
        delete (yyvsp[-5].expression_list);
      }
      if ((yyvsp[-2].relation_list) != nullptr) {
        (yyval.sub_sql_node)->relations.swap(*(yyvsp[-2].relation_list));
        delete (yyvsp[-2].relation_list);
      }
      (yyval.sub_sql_node)->relations.push_back((yyvsp[-3].string));
      std::reverse((yyval.sub_sql_node)->relations.begin(), (yyval.sub_sql_node)->relations.end());

      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sub_sql_node)->conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }
      free((yyvsp[-3].string));
    }
#line 2659 "yacc_sql.cpp"
    break;

  case 84: /* calc_stmt: CALC expression_list  */
#line 851 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2670 "yacc_sql.cpp"
    break;

  case 85: /* expression_list: expression  */
#line 861 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2679 "yacc_sql.cpp"
    break;

  case 86: /* expression_list: expression COMMA expression_list  */
#line 866 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2692 "yacc_sql.cpp"
    break;

  case 87: /* expression: expression '+' expression  */
#line 876 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2700 "yacc_sql.cpp"
    break;

  case 88: /* expression: expression MINUS expression  */
#line 879 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2708 "yacc_sql.cpp"
    break;

  case 89: /* expression: expression '*' expression  */
#line 882 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2716 "yacc_sql.cpp"
    break;

  case 90: /* expression: expression '/' expression  */
#line 885 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2724 "yacc_sql.cpp"
    break;

  case 91: /* expression: LBRACE expression RBRACE  */
#line 888 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2733 "yacc_sql.cpp"
    break;

  case 92: /* expression: NEGATIVE_NUM expression  */
#line 892 "yacc_sql.y"
                                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2741 "yacc_sql.cpp"
    break;

  case 93: /* expression: value2  */
#line 895 "yacc_sql.y"
             {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2751 "yacc_sql.cpp"
    break;

  case 94: /* add_expr_list: add_expr  */
#line 903 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2760 "yacc_sql.cpp"
    break;

  case 95: /* add_expr_list: add_expr COMMA add_expr_list  */
#line 908 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2773 "yacc_sql.cpp"
    break;

  case 96: /* add_expr: mul_expr  */
#line 918 "yacc_sql.y"
            {

    }
#line 2781 "yacc_sql.cpp"
    break;

  case 97: /* add_expr: add_expr '+' mul_expr  */
#line 921 "yacc_sql.y"
                            {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2789 "yacc_sql.cpp"
    break;

  case 98: /* add_expr: add_expr MINUS mul_expr  */
#line 924 "yacc_sql.y"
                              {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2797 "yacc_sql.cpp"
    break;

  case 99: /* mul_expr: base_expr  */
#line 929 "yacc_sql.y"
             {

    }
#line 2805 "yacc_sql.cpp"
    break;

  case 100: /* mul_expr: mul_expr '*' base_expr  */
#line 932 "yacc_sql.y"
                             {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2813 "yacc_sql.cpp"
    break;

  case 101: /* mul_expr: mul_expr '/' base_expr  */
#line 935 "yacc_sql.y"
                             {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2821 "yacc_sql.cpp"
    break;

  case 102: /* mul_expr: NEGATIVE_NUM base_expr  */
#line 938 "yacc_sql.y"
                             {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2829 "yacc_sql.cpp"
    break;

  case 103: /* base_expr: LBRACE add_expr RBRACE  */
#line 943 "yacc_sql.y"
                           {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2838 "yacc_sql.cpp"
    break;

  case 104: /* base_expr: value2  */
#line 947 "yacc_sql.y"
             {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2848 "yacc_sql.cpp"
    break;

  case 105: /* base_expr: cal_attr  */
#line 952 "yacc_sql.y"
               {
      std::string table = (yyvsp[0].rel_attr)->relation_name;
      std::string attribute = (yyvsp[0].rel_attr)->attribute_name;
      AggrOp aggr = (yyvsp[0].rel_attr)->aggr_func;
      (yyval.expression) = new FieldExpr(table, attribute, aggr);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2861 "yacc_sql.cpp"
    break;

  case 106: /* value2: NUMBER  */
#line 962 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2870 "yacc_sql.cpp"
    break;

  case 107: /* value2: FLOAT  */
#line 966 "yacc_sql.y"
            {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2879 "yacc_sql.cpp"
    break;

  case 108: /* value2: NUMBER_NEGA  */
#line 970 "yacc_sql.y"
                  {
      int temp = (int)(yyvsp[0].number);
      temp *= (-1);
      (yyval.value) = new Value(temp);
      (yyloc) = (yylsp[0]);
    }
#line 2890 "yacc_sql.cpp"
    break;

  case 109: /* value2: FLOAT_NEGA  */
#line 976 "yacc_sql.y"
                 {
      float temp = (float)(yyvsp[0].floats);
      temp *= (-1.0);
      (yyval.value) = new Value(temp);
      (yyloc) = (yylsp[0]);
    }
#line 2901 "yacc_sql.cpp"
    break;

  case 110: /* value2: NULL_T  */
#line 982 "yacc_sql.y"
            { //要放到SSS的前面
      //char *tmp = common::substr($1,1,strlen($1)-2);
      (yyval.value) = new Value(0);
      (yyval.value)->set_null_value();
      //free(tmp);
    }
#line 2912 "yacc_sql.cpp"
    break;

  case 111: /* value2: SSS  */
#line 988 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2922 "yacc_sql.cpp"
    break;

  case 112: /* value2: DATESSS  */
#line 993 "yacc_sql.y"
             {
			char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(1, tmp);
      free(tmp);
		}
#line 2932 "yacc_sql.cpp"
    break;

  case 113: /* cal_attr: '*'  */
#line 1000 "yacc_sql.y"
        {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = "";
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyloc) = (yylsp[0]);
    }
#line 2944 "yacc_sql.cpp"
    break;

  case 114: /* cal_attr: ID  */
#line 1007 "yacc_sql.y"
         {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyloc) = (yylsp[0]);
      free((yyvsp[0].string));
    }
#line 2956 "yacc_sql.cpp"
    break;

  case 115: /* cal_attr: ID DOT ID  */
#line 1014 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyloc) = (yylsp[-2]);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2970 "yacc_sql.cpp"
    break;

  case 116: /* cal_attr: aggr_func LBRACE '*' RBRACE  */
#line 1023 "yacc_sql.y"
                                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggr_func = (yyvsp[-3].aggr);
      (yyloc) = (yylsp[-3]);
    }
#line 2981 "yacc_sql.cpp"
    break;

  case 117: /* cal_attr: aggr_func LBRACE ID RBRACE  */
#line 1029 "yacc_sql.y"
                                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-3].aggr);
      (yyloc) = (yylsp[-3]);
      free((yyvsp[-1].string));
    }
#line 2993 "yacc_sql.cpp"
    break;

  case 118: /* cal_attr: aggr_func LBRACE ID DOT ID RBRACE  */
#line 1036 "yacc_sql.y"
                                       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-5].aggr);
      (yyloc) = (yylsp[-5]);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 3007 "yacc_sql.cpp"
    break;

  case 119: /* aggr_func: MAX  */
#line 1048 "yacc_sql.y"
        { (yyval.aggr)=MAXF; }
#line 3013 "yacc_sql.cpp"
    break;

  case 120: /* aggr_func: MIN  */
#line 1049 "yacc_sql.y"
                { (yyval.aggr)=MINF; }
#line 3019 "yacc_sql.cpp"
    break;

  case 121: /* aggr_func: COUNT  */
#line 1050 "yacc_sql.y"
                  { (yyval.aggr)=COUNTF; }
#line 3025 "yacc_sql.cpp"
    break;

  case 122: /* aggr_func: AVG  */
#line 1051 "yacc_sql.y"
                { (yyval.aggr)=AVGF; }
#line 3031 "yacc_sql.cpp"
    break;

  case 123: /* aggr_func: SUM  */
#line 1052 "yacc_sql.y"
                { (yyval.aggr)=SUMF; }
#line 3037 "yacc_sql.cpp"
    break;

  case 124: /* rel_list: %empty  */
#line 1056 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 3045 "yacc_sql.cpp"
    break;

  case 125: /* rel_list: COMMA ID rel_list  */
#line 1059 "yacc_sql.y"
                        {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }

      (yyval.relation_list)->push_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 3060 "yacc_sql.cpp"
    break;

  case 126: /* join_list: %empty  */
#line 1072 "yacc_sql.y"
    {
      (yyval.join_lists) = nullptr;
    }
#line 3068 "yacc_sql.cpp"
    break;

  case 127: /* join_list: INNER JOIN ID on join_list  */
#line 1075 "yacc_sql.y"
                                {
      if ((yyvsp[0].join_lists) != nullptr) {
        (yyval.join_lists) = (yyvsp[0].join_lists);
      } else {
        (yyval.join_lists) = new std::vector<InnerJoinSqlNode>;
      }
      InnerJoinSqlNode current;
      current.join_relations = (yyvsp[-2].string);
      current.join_conditions.swap(*(yyvsp[-1].condition_list));
      (yyval.join_lists)->push_back(current);

      free((yyvsp[-2].string));
      free((yyvsp[-1].condition_list));
    }
#line 3087 "yacc_sql.cpp"
    break;

  case 128: /* on: %empty  */
#line 1092 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3095 "yacc_sql.cpp"
    break;

  case 129: /* on: ON condition_list  */
#line 1095 "yacc_sql.y"
                        {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3103 "yacc_sql.cpp"
    break;

  case 130: /* where: %empty  */
#line 1101 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3111 "yacc_sql.cpp"
    break;

  case 131: /* where: WHERE condition_list  */
#line 1104 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3119 "yacc_sql.cpp"
    break;

  case 132: /* condition_list: %empty  */
#line 1110 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3127 "yacc_sql.cpp"
    break;

  case 133: /* condition_list: condition  */
#line 1113 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3137 "yacc_sql.cpp"
    break;

  case 134: /* condition_list: condition AND condition_list  */
#line 1118 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->conjunction = 0;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3148 "yacc_sql.cpp"
    break;

  case 135: /* condition_list: condition OR condition_list  */
#line 1124 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->conjunction = 1;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3159 "yacc_sql.cpp"
    break;

  case 136: /* condition: add_expr cal_comp_op add_expr  */
#line 1133 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3172 "yacc_sql.cpp"
    break;

  case 137: /* condition: sub_select_stmt cal_comp_op sub_select_stmt  */
#line 1142 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_sql = (yyvsp[-2].sub_sql_node);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_sql = (yyvsp[0].sub_sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3185 "yacc_sql.cpp"
    break;

  case 138: /* condition: add_expr cal_comp_op sub_select_stmt  */
#line 1151 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_sql = (yyvsp[0].sub_sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3198 "yacc_sql.cpp"
    break;

  case 139: /* condition: sub_select_stmt cal_comp_op add_expr  */
#line 1160 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_sql = (yyvsp[-2].sub_sql_node);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3211 "yacc_sql.cpp"
    break;

  case 140: /* condition: add_expr logical_comp_op LBRACE value value_list RBRACE  */
#line 1169 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_expr = (yyvsp[-5].expression);
      (yyval.condition)->right_is_attr = 2;
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.condition)->right_list.swap(*(yyvsp[-1].value_list));
      }
      (yyval.condition)->right_list.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.condition)->right_list.begin(), (yyval.condition)->right_list.end());
      (yyval.condition)->comp = (yyvsp[-4].comp);
    }
#line 3228 "yacc_sql.cpp"
    break;

  case 141: /* condition: add_expr logical_comp_op sub_select_stmt  */
#line 1182 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_sql = (yyvsp[0].sub_sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3241 "yacc_sql.cpp"
    break;

  case 142: /* condition: cal_comp_op sub_select_stmt  */
#line 1192 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = -1;
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_sql = (yyvsp[0].sub_sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3253 "yacc_sql.cpp"
    break;

  case 143: /* condition: add_expr cal_comp_op  */
#line 1201 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_expr = (yyvsp[-1].expression);
      (yyval.condition)->right_is_attr = -1;
      (yyval.condition)->comp = (yyvsp[0].comp);
    }
#line 3265 "yacc_sql.cpp"
    break;

  case 144: /* cal_comp_op: EQ  */
#line 1211 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3271 "yacc_sql.cpp"
    break;

  case 145: /* cal_comp_op: LT  */
#line 1212 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3277 "yacc_sql.cpp"
    break;

  case 146: /* cal_comp_op: GT  */
#line 1213 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3283 "yacc_sql.cpp"
    break;

  case 147: /* cal_comp_op: LE  */
#line 1214 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3289 "yacc_sql.cpp"
    break;

  case 148: /* cal_comp_op: GE  */
#line 1215 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3295 "yacc_sql.cpp"
    break;

  case 149: /* cal_comp_op: NE  */
#line 1216 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3301 "yacc_sql.cpp"
    break;

  case 150: /* cal_comp_op: LIKE  */
#line 1217 "yacc_sql.y"
           { (yyval.comp) = REGEX_LIKE; }
#line 3307 "yacc_sql.cpp"
    break;

  case 151: /* cal_comp_op: NOT LIKE  */
#line 1218 "yacc_sql.y"
               { (yyval.comp) = REGEX_NOT_LIKE; }
#line 3313 "yacc_sql.cpp"
    break;

  case 152: /* cal_comp_op: IS NULL_T  */
#line 1219 "yacc_sql.y"
               { (yyval.comp) = IS_NULL; }
#line 3319 "yacc_sql.cpp"
    break;

  case 153: /* cal_comp_op: IS NOT NULL_T  */
#line 1220 "yacc_sql.y"
                   { (yyval.comp) = IS_NOT_NULL; }
#line 3325 "yacc_sql.cpp"
    break;

  case 154: /* cal_comp_op: EXISTS  */
#line 1221 "yacc_sql.y"
             { (yyval.comp) = EXISTS_QUERY; }
#line 3331 "yacc_sql.cpp"
    break;

  case 155: /* cal_comp_op: NOT EXISTS  */
#line 1222 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS_QUERY; }
#line 3337 "yacc_sql.cpp"
    break;

  case 156: /* logical_comp_op: IN  */
#line 1225 "yacc_sql.y"
         { (yyval.comp) = IN_QUERY; }
#line 3343 "yacc_sql.cpp"
    break;

  case 157: /* logical_comp_op: NOT IN  */
#line 1226 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_QUERY; }
#line 3349 "yacc_sql.cpp"
    break;

  case 158: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1230 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3363 "yacc_sql.cpp"
    break;

  case 159: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1243 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3372 "yacc_sql.cpp"
    break;

  case 160: /* set_variable_stmt: SET ID EQ value  */
#line 1251 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3384 "yacc_sql.cpp"
    break;


#line 3388 "yacc_sql.cpp"

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
  *++yylsp = yyloc;

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
          = {yyssp, yytoken, &yylloc};
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
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
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
  ++yynerrs;

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
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

#line 1263 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
