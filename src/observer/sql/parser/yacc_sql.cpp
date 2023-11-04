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
  YYSYMBOL_LENGTH = 10,                    /* LENGTH  */
  YYSYMBOL_ROUND = 11,                     /* ROUND  */
  YYSYMBOL_DATE_FORMAT = 12,               /* DATE_FORMAT  */
  YYSYMBOL_CREATE = 13,                    /* CREATE  */
  YYSYMBOL_DROP = 14,                      /* DROP  */
  YYSYMBOL_TABLE = 15,                     /* TABLE  */
  YYSYMBOL_TABLES = 16,                    /* TABLES  */
  YYSYMBOL_INDEX = 17,                     /* INDEX  */
  YYSYMBOL_CALC = 18,                      /* CALC  */
  YYSYMBOL_SELECT = 19,                    /* SELECT  */
  YYSYMBOL_AS = 20,                        /* AS  */
  YYSYMBOL_DESC = 21,                      /* DESC  */
  YYSYMBOL_ASC = 22,                       /* ASC  */
  YYSYMBOL_ORDER = 23,                     /* ORDER  */
  YYSYMBOL_GROUP = 24,                     /* GROUP  */
  YYSYMBOL_BY = 25,                        /* BY  */
  YYSYMBOL_HAVING = 26,                    /* HAVING  */
  YYSYMBOL_SHOW = 27,                      /* SHOW  */
  YYSYMBOL_SYNC = 28,                      /* SYNC  */
  YYSYMBOL_INSERT = 29,                    /* INSERT  */
  YYSYMBOL_DELETE = 30,                    /* DELETE  */
  YYSYMBOL_UPDATE = 31,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 32,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 33,                    /* RBRACE  */
  YYSYMBOL_COMMA = 34,                     /* COMMA  */
  YYSYMBOL_UNIQUE = 35,                    /* UNIQUE  */
  YYSYMBOL_TRX_BEGIN = 36,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 37,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 38,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 39,                     /* INT_T  */
  YYSYMBOL_STRING_T = 40,                  /* STRING_T  */
  YYSYMBOL_DATE_T = 41,                    /* DATE_T  */
  YYSYMBOL_FLOAT_T = 42,                   /* FLOAT_T  */
  YYSYMBOL_TEXT = 43,                      /* TEXT  */
  YYSYMBOL_HELP = 44,                      /* HELP  */
  YYSYMBOL_EXIT = 45,                      /* EXIT  */
  YYSYMBOL_DOT = 46,                       /* DOT  */
  YYSYMBOL_INTO = 47,                      /* INTO  */
  YYSYMBOL_VALUES = 48,                    /* VALUES  */
  YYSYMBOL_FROM = 49,                      /* FROM  */
  YYSYMBOL_WHERE = 50,                     /* WHERE  */
  YYSYMBOL_NULL_T = 51,                    /* NULL_T  */
  YYSYMBOL_INNER = 52,                     /* INNER  */
  YYSYMBOL_JOIN = 53,                      /* JOIN  */
  YYSYMBOL_AND = 54,                       /* AND  */
  YYSYMBOL_NOT = 55,                       /* NOT  */
  YYSYMBOL_LIKE = 56,                      /* LIKE  */
  YYSYMBOL_MAX = 57,                       /* MAX  */
  YYSYMBOL_MIN = 58,                       /* MIN  */
  YYSYMBOL_SUM = 59,                       /* SUM  */
  YYSYMBOL_AVG = 60,                       /* AVG  */
  YYSYMBOL_COUNT = 61,                     /* COUNT  */
  YYSYMBOL_SET = 62,                       /* SET  */
  YYSYMBOL_ON = 63,                        /* ON  */
  YYSYMBOL_LOAD = 64,                      /* LOAD  */
  YYSYMBOL_DATA = 65,                      /* DATA  */
  YYSYMBOL_INFILE = 66,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 67,                   /* EXPLAIN  */
  YYSYMBOL_EQ = 68,                        /* EQ  */
  YYSYMBOL_LT = 69,                        /* LT  */
  YYSYMBOL_GT = 70,                        /* GT  */
  YYSYMBOL_LE = 71,                        /* LE  */
  YYSYMBOL_GE = 72,                        /* GE  */
  YYSYMBOL_NE = 73,                        /* NE  */
  YYSYMBOL_EXISTS = 74,                    /* EXISTS  */
  YYSYMBOL_NUMBER = 75,                    /* NUMBER  */
  YYSYMBOL_NUMBER_NEGA = 76,               /* NUMBER_NEGA  */
  YYSYMBOL_FLOAT = 77,                     /* FLOAT  */
  YYSYMBOL_FLOAT_NEGA = 78,                /* FLOAT_NEGA  */
  YYSYMBOL_ID = 79,                        /* ID  */
  YYSYMBOL_SSS = 80,                       /* SSS  */
  YYSYMBOL_DATESSS = 81,                   /* DATESSS  */
  YYSYMBOL_82_ = 82,                       /* '+'  */
  YYSYMBOL_83_ = 83,                       /* '*'  */
  YYSYMBOL_84_ = 84,                       /* '/'  */
  YYSYMBOL_UNARY_MINUS = 85,               /* UNARY_MINUS  */
  YYSYMBOL_YYACCEPT = 86,                  /* $accept  */
  YYSYMBOL_commands = 87,                  /* commands  */
  YYSYMBOL_command_wrapper = 88,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 89,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 90,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 91,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 92,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 93,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 94,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 95,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 96,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 97,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 98,         /* create_index_stmt  */
  YYSYMBOL_id_list = 99,                   /* id_list  */
  YYSYMBOL_id = 100,                       /* id  */
  YYSYMBOL_drop_index_stmt = 101,          /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 102,        /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 103,            /* attr_def_list  */
  YYSYMBOL_attr_def = 104,                 /* attr_def  */
  YYSYMBOL_number = 105,                   /* number  */
  YYSYMBOL_type = 106,                     /* type  */
  YYSYMBOL_insert_stmt = 107,              /* insert_stmt  */
  YYSYMBOL_record_list = 108,              /* record_list  */
  YYSYMBOL_record = 109,                   /* record  */
  YYSYMBOL_value_list = 110,               /* value_list  */
  YYSYMBOL_value = 111,                    /* value  */
  YYSYMBOL_delete_stmt = 112,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 113,              /* update_stmt  */
  YYSYMBOL_update_options = 114,           /* update_options  */
  YYSYMBOL_update_option = 115,            /* update_option  */
  YYSYMBOL_select_stmt = 116,              /* select_stmt  */
  YYSYMBOL_rel = 117,                      /* rel  */
  YYSYMBOL_opt_group_by = 118,             /* opt_group_by  */
  YYSYMBOL_group_by = 119,                 /* group_by  */
  YYSYMBOL_group_by_list = 120,            /* group_by_list  */
  YYSYMBOL_opt_order_by = 121,             /* opt_order_by  */
  YYSYMBOL_order_by_list = 122,            /* order_by_list  */
  YYSYMBOL_order_by_unit = 123,            /* order_by_unit  */
  YYSYMBOL_sub_select_stmt = 124,          /* sub_select_stmt  */
  YYSYMBOL_calc_stmt = 125,                /* calc_stmt  */
  YYSYMBOL_expression_list = 126,          /* expression_list  */
  YYSYMBOL_expression = 127,               /* expression  */
  YYSYMBOL_add_expr_list = 128,            /* add_expr_list  */
  YYSYMBOL_add_expr = 129,                 /* add_expr  */
  YYSYMBOL_mul_expr = 130,                 /* mul_expr  */
  YYSYMBOL_base_expr = 131,                /* base_expr  */
  YYSYMBOL_value2 = 132,                   /* value2  */
  YYSYMBOL_cal_attr = 133,                 /* cal_attr  */
  YYSYMBOL_aggr_func = 134,                /* aggr_func  */
  YYSYMBOL_rel_list = 135,                 /* rel_list  */
  YYSYMBOL_join_list = 136,                /* join_list  */
  YYSYMBOL_on = 137,                       /* on  */
  YYSYMBOL_having = 138,                   /* having  */
  YYSYMBOL_where = 139,                    /* where  */
  YYSYMBOL_condition_list = 140,           /* condition_list  */
  YYSYMBOL_condition = 141,                /* condition  */
  YYSYMBOL_cal_comp_op = 142,              /* cal_comp_op  */
  YYSYMBOL_logical_comp_op = 143,          /* logical_comp_op  */
  YYSYMBOL_load_data_stmt = 144,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 145,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 146,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 147             /* opt_semicolon  */
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
#define YYFINAL  85
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   432

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  189
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  348

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   337


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
       2,     2,    83,    82,     2,     2,     2,    84,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    85
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   263,   263,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   294,   300,   305,   311,   317,   323,   329,
     336,   342,   350,   371,   396,   399,   410,   419,   429,   447,
     460,   463,   476,   485,   494,   503,   513,   522,   530,   541,
     544,   545,   546,   547,   550,   566,   569,   583,   599,   602,
     613,   617,   621,   625,   629,   635,   640,   649,   661,   700,
     703,   713,   721,   732,   781,   789,   795,   806,   809,   820,
     826,   837,   840,   852,   855,   868,   871,   884,   891,   898,
     906,   913,   921,   930,   954,   964,   969,   980,   983,   986,
     989,   992,   996,   999,  1006,  1011,  1022,  1025,  1028,  1033,
    1036,  1039,  1042,  1047,  1051,  1056,  1067,  1071,  1075,  1081,
    1087,  1093,  1098,  1105,  1113,  1121,  1131,  1141,  1148,  1156,
    1166,  1175,  1186,  1194,  1203,  1214,  1223,  1234,  1242,  1252,
    1263,  1278,  1292,  1307,  1324,  1325,  1326,  1327,  1328,  1332,
    1335,  1348,  1351,  1368,  1371,  1377,  1380,  1386,  1389,  1395,
    1398,  1403,  1409,  1417,  1426,  1435,  1444,  1453,  1466,  1476,
    1485,  1496,  1497,  1498,  1499,  1500,  1501,  1502,  1503,  1504,
    1505,  1506,  1507,  1510,  1511,  1514,  1527,  1535,  1545,  1546
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
  "NULLABLE", "IN", "IS", "MINUS", "NEGATIVE_NUM", "OR", "LENGTH", "ROUND",
  "DATE_FORMAT", "CREATE", "DROP", "TABLE", "TABLES", "INDEX", "CALC",
  "SELECT", "AS", "DESC", "ASC", "ORDER", "GROUP", "BY", "HAVING", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA",
  "UNIQUE", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "DATE_T", "FLOAT_T", "TEXT", "HELP", "EXIT", "DOT", "INTO", "VALUES",
  "FROM", "WHERE", "NULL_T", "INNER", "JOIN", "AND", "NOT", "LIKE", "MAX",
  "MIN", "SUM", "AVG", "COUNT", "SET", "ON", "LOAD", "DATA", "INFILE",
  "EXPLAIN", "EQ", "LT", "GT", "LE", "GE", "NE", "EXISTS", "NUMBER",
  "NUMBER_NEGA", "FLOAT", "FLOAT_NEGA", "ID", "SSS", "DATESSS", "'+'",
  "'*'", "'/'", "UNARY_MINUS", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "id_list", "id",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "number", "type", "insert_stmt", "record_list", "record", "value_list",
  "value", "delete_stmt", "update_stmt", "update_options", "update_option",
  "select_stmt", "rel", "opt_group_by", "group_by", "group_by_list",
  "opt_order_by", "order_by_list", "order_by_unit", "sub_select_stmt",
  "calc_stmt", "expression_list", "expression", "add_expr_list",
  "add_expr", "mul_expr", "base_expr", "value2", "cal_attr", "aggr_func",
  "rel_list", "join_list", "on", "having", "where", "condition_list",
  "condition", "cal_comp_op", "logical_comp_op", "load_data_stmt",
  "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-269)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     341,    19,   150,   185,   165,   -37,    56,  -269,    34,    -1,
      38,  -269,  -269,  -269,  -269,  -269,    41,    69,   341,   147,
     212,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,
    -269,   139,   140,   203,   142,   148,   185,   185,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,  -269,     1,  -269,   240,   197,
     200,   201,   165,  -269,  -269,  -269,  -269,  -269,    87,  -269,
     186,    15,   -52,  -269,  -269,  -269,   206,  -269,  -269,   160,
     168,   191,   199,   188,  -269,  -269,  -269,  -269,    21,   205,
     190,  -269,   207,  -269,    11,   185,   185,   185,   185,   185,
    -269,   229,   229,   229,    22,   204,   -58,  -269,   208,   165,
     165,   165,   240,   240,   -55,   236,   239,   211,   229,   213,
     267,   215,   216,   233,   223,  -269,    25,  -269,    25,  -269,
    -269,   135,  -269,  -269,  -269,  -269,  -269,   259,   149,   269,
    -269,  -269,   -11,  -269,    32,   271,   -52,  -269,   -52,  -269,
    -269,    -6,   275,   280,    80,  -269,   243,   288,  -269,   266,
    -269,   159,   290,   293,   247,  -269,  -269,  -269,   248,   249,
     229,   229,   250,  -269,   251,  -269,   208,   287,    36,   253,
      37,   229,   307,    74,   111,    58,  -269,  -269,  -269,  -269,
    -269,  -269,  -269,  -269,   279,     5,  -269,    17,   310,   256,
     211,   239,   330,  -269,  -269,  -269,  -269,  -269,   -12,   215,
     313,   277,   325,  -269,  -269,   328,   331,  -269,  -269,   271,
     305,   239,   284,  -269,   332,   294,  -269,   333,   280,  -269,
    -269,   315,   165,  -269,  -269,   198,  -269,     8,   198,   342,
      80,    80,   356,  -269,  -269,  -269,   288,  -269,   297,   306,
    -269,   329,   290,  -269,  -269,   348,   277,   304,   308,  -269,
     208,   360,  -269,    39,  -269,   229,   355,   307,  -269,   340,
    -269,    23,  -269,  -269,    23,   263,  -269,  -269,  -269,  -269,
    -269,  -269,   357,  -269,  -269,   277,   358,   348,  -269,  -269,
     334,   367,   368,   314,  -269,   333,  -269,  -269,   208,   333,
      91,   348,  -269,   362,    80,   287,   317,    80,   375,  -269,
    -269,   271,   366,  -269,   349,  -269,  -269,  -269,  -269,   361,
     370,  -269,   376,  -269,   239,  -269,  -269,   323,   317,  -269,
     327,   377,  -269,   370,    16,   378,  -269,  -269,  -269,  -269,
     335,   327,  -269,   174,   378,  -269,  -269,  -269
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     188,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,     0,   120,   116,
     118,   117,   119,   121,   122,    94,    95,   103,     0,     0,
       0,     0,     0,   144,   145,   148,   147,   146,   124,   123,
       0,   104,   106,   109,   114,   115,     0,    31,    30,     0,
       0,     0,     0,     0,   186,     1,   189,     2,     0,     0,
       0,    29,     0,   102,     0,     0,     0,     0,     0,     0,
     112,     0,     0,     0,     0,     0,     0,   135,     0,     0,
       0,     0,     0,     0,     0,     0,   157,     0,     0,     0,
       0,     0,     0,     0,     0,   101,    98,    96,    97,    99,
     100,     0,    64,    60,    62,    65,    66,     0,     0,     0,
     113,   130,   126,   125,    75,   149,   108,   105,   107,   110,
     111,     0,     0,     0,   159,    67,     0,    69,   187,     0,
      39,     0,    40,     0,     0,    37,    61,    63,     0,     0,
       0,     0,     0,   136,     0,    74,     0,   151,   128,     0,
     127,     0,    55,     0,     0,     0,   177,   171,   172,   173,
     174,   175,   176,   181,     0,     0,   158,   160,     0,     0,
       0,   157,     0,    50,    51,    53,    52,    47,    48,     0,
       0,     0,     0,   140,   141,     0,     0,   131,    76,   149,
       0,   157,     0,   138,     0,     0,   137,    58,     0,    54,
     179,     0,     0,   178,   182,     0,   183,     0,   170,     0,
     159,   159,     0,   169,    71,    72,    69,    68,     0,     0,
      46,     0,    40,    38,    36,    34,     0,     0,     0,   150,
       0,    77,   133,   129,   132,     0,     0,    55,   180,     0,
     164,   166,   184,   165,   163,     0,   168,   162,   161,    70,
     185,    49,     0,    45,    41,     0,     0,    34,   142,   143,
     153,     0,   155,     0,   139,    58,    57,    56,     0,    58,
      42,    34,    32,     0,   159,   151,     0,   159,    83,   134,
      59,   149,     0,    44,     0,    35,    33,   154,   152,    79,
      81,   156,     0,    73,   157,   167,    43,     0,     0,    78,
       0,     0,    80,    81,    87,    85,    93,    82,    89,    90,
       0,     0,    84,    88,    85,    91,    92,    86
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -269,  -269,   391,  -269,  -269,  -269,  -269,  -269,  -269,  -269,
    -269,  -269,  -269,  -268,  -240,  -269,  -269,   161,   202,  -269,
    -269,  -269,   151,   187,   -92,  -101,  -269,  -269,   170,   217,
     299,  -171,  -269,    92,    88,  -269,    78,    82,   -54,  -269,
     336,   -32,  -104,    -4,   103,    66,     4,  -269,  -269,  -215,
     119,  -269,  -269,  -198,  -194,  -269,    10,  -269,  -269,  -269,
    -269,  -269
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   286,   255,    31,    32,   210,   162,   282,
     208,    33,   229,   182,   266,   137,    34,    35,   201,   157,
      36,   145,   292,   320,   329,   323,   342,   335,   194,    37,
      55,    56,    70,   195,    72,    73,    74,    75,    76,   177,
     221,   305,   308,   155,   196,   197,   198,   239,    38,    39,
      40,    87
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      71,   138,   139,   247,   259,   219,   147,    57,    95,   172,
     236,   183,   109,   272,    93,    94,   287,   158,    95,   303,
     249,   142,   109,   261,   151,   143,   240,   178,   152,   109,
     109,   112,   113,   315,    41,    96,    42,   338,   339,   250,
     179,   120,    77,   251,   125,   301,   277,   278,    80,   110,
      57,    57,   174,   121,    43,   140,   222,   225,   104,   293,
     237,   186,   340,   126,   233,   128,   129,   130,   173,   215,
     216,   241,    78,   187,   188,   189,   190,   191,   192,   193,
     227,    79,   234,    97,    98,    99,   183,   111,    58,   290,
      59,    60,    61,    97,    98,    99,   324,   111,   244,    57,
      57,    57,    57,    57,   111,   111,    71,   105,    98,    99,
     317,   175,   184,   321,   233,   223,   226,    81,   294,    58,
      82,    59,    60,    61,   100,   230,   331,   311,   269,   231,
     232,    48,   234,   106,    83,   185,   186,    63,    64,    65,
      66,    67,   313,    62,   243,   245,   314,    85,   187,   188,
     189,   190,   191,   192,   193,    49,    50,    51,    52,    68,
      53,    54,    48,    69,   295,    44,   107,    45,    63,    64,
      65,    66,    67,    58,   299,    59,    60,    61,   149,   150,
     104,   270,   169,   170,   273,   276,    49,    50,    51,    52,
      68,    53,    54,    46,    69,   345,   346,    62,   203,   204,
     205,   206,   207,   310,   235,   238,    58,   312,    59,    60,
      61,   166,   146,   167,   148,    86,    48,    47,    88,    89,
      90,    91,    63,    64,    65,    66,    67,    92,    71,   101,
     184,   271,   102,   103,   274,   108,    48,   131,   114,   115,
      49,    50,    51,    52,    68,    53,    54,   116,    69,    48,
      59,    60,    61,   117,   119,    63,    64,    65,    66,    67,
      49,    50,    51,    52,   131,    53,    54,   118,   122,   123,
     124,   131,    62,    49,    50,    51,    52,    68,    53,    54,
     132,    69,   232,   141,   153,   183,     4,   144,   242,   154,
     156,    48,   168,   159,   161,   163,   164,    63,    64,    65,
      66,    67,   165,   171,   133,   176,   134,   132,   180,   135,
     136,   199,   181,   202,   132,    49,    50,    51,    52,    68,
      53,    54,   200,    69,   209,   211,   212,   213,   214,   217,
     218,   133,   224,   134,   185,   186,   135,   136,   133,   220,
     134,   228,   242,   135,   136,   248,   253,   187,   188,   189,
     190,   191,   192,   193,     1,     2,   254,   256,   260,     3,
       4,   257,     5,   262,   258,   263,   268,   265,     6,     7,
       8,     9,    10,   264,   275,   232,   280,    11,    12,    13,
     283,   281,   285,   288,   291,    14,    15,   289,   296,   298,
     300,   302,   306,   309,   307,   316,   319,   304,   322,   325,
     326,   330,   332,    16,   328,    17,   334,   327,    18,    84,
     336,   252,   341,   284,   343,   267,   279,   246,   297,   160,
     333,   337,   347,   344,   318,     0,     0,     0,     0,     0,
       0,     0,   127
};

static const yytype_int16 yycheck[] =
{
       4,   102,   103,   201,   219,   176,   110,     3,     7,    20,
       5,     6,     7,     5,    46,    47,   256,   118,     7,   287,
      32,    79,     7,   221,    79,    83,     9,    33,    83,     7,
       7,    83,    84,   301,    15,    34,    17,    21,    22,    51,
      46,    20,    79,    55,    33,   285,   240,   241,    49,    34,
      46,    47,    20,    32,    35,    33,    20,    20,    62,    20,
      55,    56,    46,    95,    56,    97,    98,    99,    79,   170,
     171,    54,    16,    68,    69,    70,    71,    72,    73,    74,
     181,    47,    74,    82,    83,    84,     6,    82,     8,   260,
      10,    11,    12,    82,    83,    84,   311,    82,   199,    95,
      96,    97,    98,    99,    82,    82,   110,    20,    83,    84,
     304,    79,    32,   307,    56,    79,    79,    79,    79,     8,
      79,    10,    11,    12,    58,    51,   324,   298,   232,    55,
      19,    51,    74,    46,    65,    55,    56,    57,    58,    59,
      60,    61,    51,    32,   198,   199,    55,     0,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    51,    83,   265,    15,    79,    17,    57,    58,
      59,    60,    61,     8,   275,    10,    11,    12,   112,   113,
     184,   235,    33,    34,   238,   239,    75,    76,    77,    78,
      79,    80,    81,     8,    83,    21,    22,    32,    39,    40,
      41,    42,    43,   295,   194,   195,     8,   299,    10,    11,
      12,    76,   109,    78,   111,     3,    51,    32,    79,    79,
      17,    79,    57,    58,    59,    60,    61,    79,   232,    32,
      32,   235,    32,    32,   238,    49,    51,     8,    32,    79,
      75,    76,    77,    78,    79,    80,    81,    79,    83,    51,
      10,    11,    12,    62,    66,    57,    58,    59,    60,    61,
      75,    76,    77,    78,     8,    80,    81,    68,    63,    79,
      63,     8,    32,    75,    76,    77,    78,    79,    80,    81,
      51,    83,    19,    79,    48,     6,    19,    79,    32,    50,
      79,    51,    33,    80,    79,    79,    63,    57,    58,    59,
      60,    61,    79,    34,    75,    34,    77,    51,    33,    80,
      81,    68,    32,    47,    51,    75,    76,    77,    78,    79,
      80,    81,    34,    83,    34,    32,    79,    79,    79,    79,
      79,    75,    79,    77,    55,    56,    80,    81,    75,    52,
      77,    34,    32,    80,    81,    15,    33,    68,    69,    70,
      71,    72,    73,    74,    13,    14,    79,    32,    53,    18,
      19,    33,    21,    79,    33,    33,    51,    34,    27,    28,
      29,    30,    31,    79,    32,    19,    79,    36,    37,    38,
      51,    75,    34,    79,    24,    44,    45,    79,    33,    49,
      33,    33,    25,    79,    26,    33,    79,    63,    23,    33,
      51,    25,    79,    62,    34,    64,    79,    46,    67,    18,
      33,   209,    34,   252,    79,   228,   246,   200,   267,   120,
     328,   333,   344,   341,   305,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    14,    18,    19,    21,    27,    28,    29,    30,
      31,    36,    37,    38,    44,    45,    62,    64,    67,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,   101,   102,   107,   112,   113,   116,   125,   144,   145,
     146,    15,    17,    35,    15,    17,     8,    32,    51,    75,
      76,    77,    78,    80,    81,   126,   127,   132,     8,    10,
      11,    12,    32,    57,    58,    59,    60,    61,    79,    83,
     128,   129,   130,   131,   132,   133,   134,    79,    16,    47,
      49,    79,    79,    65,    88,     0,     3,   147,    79,    79,
      17,    79,    79,   127,   127,     7,    34,    82,    83,    84,
     131,    32,    32,    32,   129,    20,    46,    79,    49,     7,
      34,    82,    83,    84,    32,    79,    79,    62,    68,    66,
      20,    32,    63,    79,    63,    33,   127,   126,   127,   127,
     127,     8,    51,    75,    77,    80,    81,   111,   111,   111,
      33,    79,    79,    83,    79,   117,   130,   128,   130,   131,
     131,    79,    83,    48,    50,   139,    79,   115,   111,    80,
     116,    79,   104,    79,    63,    79,    76,    78,    33,    33,
      34,    34,    20,    79,    20,    79,    34,   135,    33,    46,
      33,    32,   109,     6,    32,    55,    56,    68,    69,    70,
      71,    72,    73,    74,   124,   129,   140,   141,   142,    68,
      34,   114,    47,    39,    40,    41,    42,    43,   106,    34,
     103,    32,    79,    79,    79,   111,   111,    79,    79,   117,
      52,   136,    20,    79,    79,    20,    79,   111,    34,   108,
      51,    55,    19,    56,    74,   142,     5,    55,   142,   143,
       9,    54,    32,   124,   111,   124,   115,   139,    15,    32,
      51,    55,   104,    33,    79,   100,    32,    33,    33,   135,
      53,   139,    79,    33,    79,    34,   110,   109,    51,   128,
     124,   129,     5,   124,   129,    32,   124,   140,   140,   114,
      79,    75,   105,    51,   103,    34,    99,   100,    79,    79,
     117,    24,   118,    20,    79,   111,    33,   108,    49,   111,
      33,   100,    33,    99,    63,   137,    25,    26,   138,    79,
     110,   117,   110,    51,    55,    99,    33,   140,   136,    79,
     119,   140,    23,   121,   135,    33,    51,    46,    34,   120,
      25,   139,    79,   119,    79,   123,    33,   120,    21,    22,
      46,    34,   122,    79,   123,    21,    22,   122
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    98,    99,    99,   100,   101,   102,   102,
     103,   103,   104,   104,   104,   104,   104,   104,   104,   105,
     106,   106,   106,   106,   107,   108,   108,   109,   110,   110,
     111,   111,   111,   111,   111,   111,   111,   112,   113,   114,
     114,   115,   115,   116,   117,   117,   117,   118,   118,   119,
     119,   120,   120,   121,   121,   122,   122,   123,   123,   123,
     123,   123,   123,   124,   125,   126,   126,   127,   127,   127,
     127,   127,   127,   127,   128,   128,   129,   129,   129,   130,
     130,   130,   130,   131,   131,   131,   132,   132,   132,   132,
     132,   132,   132,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   134,   134,   134,   134,   134,   135,
     135,   136,   136,   137,   137,   138,   138,   139,   139,   140,
     140,   140,   140,   141,   141,   141,   141,   141,   141,   141,
     141,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   143,   143,   144,   145,   146,   147,   147
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     9,    10,     0,     3,     1,     5,     7,     5,
       0,     3,     5,     7,     6,     4,     3,     2,     2,     1,
       1,     1,     1,     1,     6,     0,     3,     4,     0,     3,
       1,     2,     1,     2,     1,     1,     1,     4,     6,     0,
       3,     3,     3,    10,     2,     1,     3,     0,     4,     1,
       3,     0,     3,     0,     4,     0,     3,     1,     3,     2,
       2,     4,     4,     8,     2,     1,     3,     3,     3,     3,
       3,     3,     2,     1,     1,     3,     1,     3,     3,     1,
       3,     3,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     4,     4,     6,
       3,     5,     6,     6,     8,     2,     4,     5,     5,     7,
       5,     5,     7,     7,     1,     1,     1,     1,     1,     0,
       3,     0,     5,     0,     2,     0,     2,     0,     2,     0,
       1,     3,     3,     3,     3,     3,     3,     6,     3,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       3,     1,     2,     1,     2,     7,     2,     4,     0,     1
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
#line 264 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1947 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 294 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1956 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 300 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1964 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 305 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1972 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 311 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1980 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 317 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1988 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 323 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1996 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 329 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2006 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 336 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2014 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 342 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2024 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE id id_list RBRACE  */
#line 351 "yacc_sql.y"
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
#line 2049 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE id id_list RBRACE  */
#line 372 "yacc_sql.y"
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
#line 2074 "yacc_sql.cpp"
    break;

  case 34: /* id_list: %empty  */
#line 396 "yacc_sql.y"
    {
      (yyval.index_attr_list) = nullptr;
    }
#line 2082 "yacc_sql.cpp"
    break;

  case 35: /* id_list: COMMA id id_list  */
#line 400 "yacc_sql.y"
    {
      if ((yyvsp[0].index_attr_list) != nullptr) {
        (yyval.index_attr_list) = (yyvsp[0].index_attr_list);
      } else {
        (yyval.index_attr_list) = new std::vector<std::string>;
      }
      (yyval.index_attr_list)->push_back((yyvsp[-1].string));
      delete (yyvsp[-1].string);
    }
#line 2096 "yacc_sql.cpp"
    break;

  case 36: /* id: ID  */
#line 411 "yacc_sql.y"
        {

		(yyval.string) = (yyvsp[0].string);
    //free($1);
	}
#line 2106 "yacc_sql.cpp"
    break;

  case 37: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 420 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2118 "yacc_sql.cpp"
    break;

  case 38: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 430 "yacc_sql.y"
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

      create_table.select_flag = false;
    }
#line 2140 "yacc_sql.cpp"
    break;

  case 39: /* create_table_stmt: CREATE TABLE ID AS select_stmt  */
#line 448 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));

      create_table.select_infos = (yyvsp[0].sql_node);
      create_table.select_flag = true;
    }
#line 2154 "yacc_sql.cpp"
    break;

  case 40: /* attr_def_list: %empty  */
#line 460 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2162 "yacc_sql.cpp"
    break;

  case 41: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 464 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2176 "yacc_sql.cpp"
    break;

  case 42: /* attr_def: ID type LBRACE number RBRACE  */
#line 477 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      //$$->nullable = false;
      free((yyvsp[-4].string));
    }
#line 2189 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type LBRACE number RBRACE NOT NULL_T  */
#line 486 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-5].number);
      (yyval.attr_info)->name = (yyvsp[-6].string);
      (yyval.attr_info)->length = (yyvsp[-3].number);
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-6].string));
    }
#line 2202 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type LBRACE number RBRACE NULL_T  */
#line 495 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-5].string));
    }
#line 2215 "yacc_sql.cpp"
    break;

  case 45: /* attr_def: ID type NOT NULL_T  */
#line 504 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-2].number);
      (yyval.attr_info)->name = (yyvsp[-3].string);
      (yyval.attr_info)->length = 4;
      //$$->nullable = true;
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-3].string));
    }
#line 2229 "yacc_sql.cpp"
    break;

  case 46: /* attr_def: ID type NULL_T  */
#line 514 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-2].string));
    }
#line 2242 "yacc_sql.cpp"
    break;

  case 47: /* attr_def: ID TEXT  */
#line 523 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = CHARS;
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 65535;
      free((yyvsp[-1].string));
    }
#line 2254 "yacc_sql.cpp"
    break;

  case 48: /* attr_def: ID type  */
#line 531 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      //$$->nullable = false;
      free((yyvsp[-1].string));
    }
#line 2267 "yacc_sql.cpp"
    break;

  case 49: /* number: NUMBER  */
#line 541 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2273 "yacc_sql.cpp"
    break;

  case 50: /* type: INT_T  */
#line 544 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2279 "yacc_sql.cpp"
    break;

  case 51: /* type: STRING_T  */
#line 545 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2285 "yacc_sql.cpp"
    break;

  case 52: /* type: FLOAT_T  */
#line 546 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2291 "yacc_sql.cpp"
    break;

  case 53: /* type: DATE_T  */
#line 547 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2297 "yacc_sql.cpp"
    break;

  case 54: /* insert_stmt: INSERT INTO ID VALUES record record_list  */
#line 551 "yacc_sql.y"
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
#line 2313 "yacc_sql.cpp"
    break;

  case 55: /* record_list: %empty  */
#line 566 "yacc_sql.y"
    {
      (yyval.record_list) =  nullptr;
    }
#line 2321 "yacc_sql.cpp"
    break;

  case 56: /* record_list: COMMA record record_list  */
#line 569 "yacc_sql.y"
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
#line 2338 "yacc_sql.cpp"
    break;

  case 57: /* record: LBRACE value value_list RBRACE  */
#line 583 "yacc_sql.y"
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
#line 2356 "yacc_sql.cpp"
    break;

  case 58: /* value_list: %empty  */
#line 599 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2364 "yacc_sql.cpp"
    break;

  case 59: /* value_list: COMMA value value_list  */
#line 602 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2378 "yacc_sql.cpp"
    break;

  case 60: /* value: NUMBER  */
#line 613 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2387 "yacc_sql.cpp"
    break;

  case 61: /* value: NEGATIVE_NUM NUMBER_NEGA  */
#line 617 "yacc_sql.y"
                               {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
#line 2396 "yacc_sql.cpp"
    break;

  case 62: /* value: FLOAT  */
#line 621 "yacc_sql.y"
            {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2405 "yacc_sql.cpp"
    break;

  case 63: /* value: NEGATIVE_NUM FLOAT_NEGA  */
#line 625 "yacc_sql.y"
                              {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
#line 2414 "yacc_sql.cpp"
    break;

  case 64: /* value: NULL_T  */
#line 629 "yacc_sql.y"
            { //要放到SSS的前面
      //char *tmp = common::substr($1,1,strlen($1)-2);
      (yyval.value) = new Value(0);
      (yyval.value)->set_null_value();
      //free(tmp);
    }
#line 2425 "yacc_sql.cpp"
    break;

  case 65: /* value: SSS  */
#line 635 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2435 "yacc_sql.cpp"
    break;

  case 66: /* value: DATESSS  */
#line 640 "yacc_sql.y"
             {
			char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(1, tmp);
      free(tmp);
		}
#line 2445 "yacc_sql.cpp"
    break;

  case 67: /* delete_stmt: DELETE FROM ID where  */
#line 650 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2459 "yacc_sql.cpp"
    break;

  case 68: /* update_stmt: UPDATE ID SET update_option update_options where  */
#line 662 "yacc_sql.y"
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
#line 2499 "yacc_sql.cpp"
    break;

  case 69: /* update_options: %empty  */
#line 700 "yacc_sql.y"
    {
      (yyval.attr_name_a_values) = nullptr;
    }
#line 2507 "yacc_sql.cpp"
    break;

  case 70: /* update_options: COMMA update_option update_options  */
#line 703 "yacc_sql.y"
                                                     {
      if ((yyvsp[0].attr_name_a_values) != nullptr) {
        (yyval.attr_name_a_values) = (yyvsp[0].attr_name_a_values);
      } else {
        (yyval.attr_name_a_values) = new std::vector<SetVariableSqlNode>;
      }
      (yyval.attr_name_a_values)->emplace_back(*(yyvsp[-1].attr_name_value));
       delete (yyvsp[-1].attr_name_value);
		}
#line 2521 "yacc_sql.cpp"
    break;

  case 71: /* update_option: ID EQ value  */
#line 713 "yacc_sql.y"
                            {
    	(yyval.attr_name_value) = new SetVariableSqlNode();
      (yyval.attr_name_value)->value = *(yyvsp[0].value);
      (yyval.attr_name_value)->name = (yyvsp[-2].string);
      (yyval.attr_name_value)->type = 0;
      free((yyvsp[-2].string));
      free((yyvsp[0].value));
		}
#line 2534 "yacc_sql.cpp"
    break;

  case 72: /* update_option: ID EQ sub_select_stmt  */
#line 721 "yacc_sql.y"
                            {
    	(yyval.attr_name_value) = new SetVariableSqlNode();
      (yyval.attr_name_value)->query = (yyvsp[0].sub_sql_node);
      (yyval.attr_name_value)->name = (yyvsp[-2].string);
      (yyval.attr_name_value)->type = 1;
      free((yyvsp[-2].string));
		}
#line 2546 "yacc_sql.cpp"
    break;

  case 73: /* select_stmt: SELECT add_expr_list FROM rel rel_list join_list where opt_group_by having opt_order_by  */
#line 733 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);

      if ((yyvsp[-8].expression_list) != nullptr) {
        std::reverse((yyvsp[-8].expression_list)->begin(), (yyvsp[-8].expression_list)->end());
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-8].expression_list));
        delete (yyvsp[-8].expression_list);
      }

      if ((yyvsp[-5].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-5].relation_list));
        delete (yyvsp[-5].relation_list);
      }
      (yyval.sql_node)->selection.relations.push_back(*(yyvsp[-6].rel_name));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      if ((yyvsp[-4].join_lists) != nullptr) {
        (yyval.sql_node)->selection.joinTables.swap(*(yyvsp[-4].join_lists));
        delete (yyvsp[-4].join_lists);
        std::reverse((yyval.sql_node)->selection.joinTables.begin(), (yyval.sql_node)->selection.joinTables.end());
      }

      if ((yyvsp[-3].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-3].condition_list));
        delete (yyvsp[-3].condition_list);
      }

      if ((yyvsp[-2].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.groupBy.swap(*(yyvsp[-2].rel_attr_list));
        delete (yyvsp[-2].rel_attr_list);
        std::reverse((yyval.sql_node)->selection.groupBy.begin(), (yyval.sql_node)->selection.groupBy.end());
      }

      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.havingcConditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }

      if ((yyvsp[0].order_by) != nullptr) {
        (yyval.sql_node)->selection.orderBy.swap(*(yyvsp[0].order_by));
        delete (yyvsp[0].order_by);
      }

      free((yyvsp[-6].rel_name));
    }
#line 2596 "yacc_sql.cpp"
    break;

  case 74: /* rel: ID ID  */
#line 782 "yacc_sql.y"
  {
    (yyval.rel_name) = new RelName();
    (yyval.rel_name)->relation = (yyvsp[-1].string);
    (yyval.rel_name)->alias = (yyvsp[0].string);
    free((yyvsp[-1].string));
    free((yyvsp[0].string));
  }
#line 2608 "yacc_sql.cpp"
    break;

  case 75: /* rel: ID  */
#line 790 "yacc_sql.y"
  {
    (yyval.rel_name) = new RelName();
    (yyval.rel_name)->relation = (yyvsp[0].string);
    free((yyvsp[0].string));
  }
#line 2618 "yacc_sql.cpp"
    break;

  case 76: /* rel: ID AS ID  */
#line 796 "yacc_sql.y"
  {
    (yyval.rel_name) = new RelName();
    (yyval.rel_name)->relation = (yyvsp[-2].string);
    (yyval.rel_name)->alias = (yyvsp[0].string);
    free((yyvsp[-2].string));
    free((yyvsp[0].string));
  }
#line 2630 "yacc_sql.cpp"
    break;

  case 77: /* opt_group_by: %empty  */
#line 806 "yacc_sql.y"
  {
    (yyval.rel_attr_list) = nullptr;
  }
#line 2638 "yacc_sql.cpp"
    break;

  case 78: /* opt_group_by: GROUP BY group_by group_by_list  */
#line 809 "yacc_sql.y"
                                    {
    if ((yyvsp[0].rel_attr_list) != nullptr) {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
    } else {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
    }
    (yyval.rel_attr_list)->push_back(*(yyvsp[-1].rel_attr));
    free((yyvsp[-1].rel_attr));
  }
#line 2652 "yacc_sql.cpp"
    break;

  case 79: /* group_by: ID  */
#line 821 "yacc_sql.y"
  {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
    free((yyvsp[0].string));
  }
#line 2662 "yacc_sql.cpp"
    break;

  case 80: /* group_by: ID DOT ID  */
#line 827 "yacc_sql.y"
  {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
    (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
    free((yyvsp[-2].string));
    free((yyvsp[0].string));
  }
#line 2674 "yacc_sql.cpp"
    break;

  case 81: /* group_by_list: %empty  */
#line 837 "yacc_sql.y"
  {
    (yyval.rel_attr_list) = nullptr;
  }
#line 2682 "yacc_sql.cpp"
    break;

  case 82: /* group_by_list: COMMA group_by group_by_list  */
#line 840 "yacc_sql.y"
                                 {
    if ((yyvsp[0].rel_attr_list) != nullptr) {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
    } else {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
    }
    (yyval.rel_attr_list)->push_back(*(yyvsp[-1].rel_attr));
    free((yyvsp[-1].rel_attr));
  }
#line 2696 "yacc_sql.cpp"
    break;

  case 83: /* opt_order_by: %empty  */
#line 852 "yacc_sql.y"
    {
      (yyval.order_by) = nullptr;
    }
#line 2704 "yacc_sql.cpp"
    break;

  case 84: /* opt_order_by: ORDER BY order_by_unit order_by_list  */
#line 855 "yacc_sql.y"
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
#line 2720 "yacc_sql.cpp"
    break;

  case 85: /* order_by_list: %empty  */
#line 868 "yacc_sql.y"
    {
      (yyval.order_by) = nullptr;
    }
#line 2728 "yacc_sql.cpp"
    break;

  case 86: /* order_by_list: COMMA order_by_unit order_by_list  */
#line 872 "yacc_sql.y"
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
#line 2743 "yacc_sql.cpp"
    break;

  case 87: /* order_by_unit: ID  */
#line 885 "yacc_sql.y"
        {
      (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[0].string);
      //$$->order_relation = NULL;
	}
#line 2753 "yacc_sql.cpp"
    break;

  case 88: /* order_by_unit: ID DOT ID  */
#line 892 "yacc_sql.y"
        {
		  (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[0].string);
      (yyval.order_by_node)->order_relation = (yyvsp[-2].string);
	}
#line 2763 "yacc_sql.cpp"
    break;

  case 89: /* order_by_unit: ID DESC  */
#line 899 "yacc_sql.y"
        {
      (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[-1].string);
      //$$->order_relation = NULL;
      (yyval.order_by_node)->asc_type = false;
	}
#line 2774 "yacc_sql.cpp"
    break;

  case 90: /* order_by_unit: ID ASC  */
#line 907 "yacc_sql.y"
        {
      (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[-1].string);
      //$$->order_relation = NULL;
	}
#line 2784 "yacc_sql.cpp"
    break;

  case 91: /* order_by_unit: ID DOT ID DESC  */
#line 914 "yacc_sql.y"
        {
      (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[-1].string);
      (yyval.order_by_node)->order_relation = (yyvsp[-3].string);
      (yyval.order_by_node)->asc_type = false;
	}
#line 2795 "yacc_sql.cpp"
    break;

  case 92: /* order_by_unit: ID DOT ID ASC  */
#line 922 "yacc_sql.y"
        {
		  (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[-1].string);
      (yyval.order_by_node)->order_relation = (yyvsp[-3].string);
	}
#line 2805 "yacc_sql.cpp"
    break;

  case 93: /* sub_select_stmt: LBRACE SELECT add_expr_list FROM rel rel_list where RBRACE  */
#line 931 "yacc_sql.y"
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
      (yyval.sub_sql_node)->relations.push_back(*(yyvsp[-3].rel_name));
      std::reverse((yyval.sub_sql_node)->relations.begin(), (yyval.sub_sql_node)->relations.end());

      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sub_sql_node)->conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }
      free((yyvsp[-3].rel_name));
    }
#line 2830 "yacc_sql.cpp"
    break;

  case 94: /* calc_stmt: CALC expression_list  */
#line 955 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2841 "yacc_sql.cpp"
    break;

  case 95: /* expression_list: expression  */
#line 965 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2850 "yacc_sql.cpp"
    break;

  case 96: /* expression_list: expression COMMA expression_list  */
#line 970 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2863 "yacc_sql.cpp"
    break;

  case 97: /* expression: expression '+' expression  */
#line 980 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2871 "yacc_sql.cpp"
    break;

  case 98: /* expression: expression MINUS expression  */
#line 983 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2879 "yacc_sql.cpp"
    break;

  case 99: /* expression: expression '*' expression  */
#line 986 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2887 "yacc_sql.cpp"
    break;

  case 100: /* expression: expression '/' expression  */
#line 989 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2895 "yacc_sql.cpp"
    break;

  case 101: /* expression: LBRACE expression RBRACE  */
#line 992 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2904 "yacc_sql.cpp"
    break;

  case 102: /* expression: NEGATIVE_NUM expression  */
#line 996 "yacc_sql.y"
                                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2912 "yacc_sql.cpp"
    break;

  case 103: /* expression: value2  */
#line 999 "yacc_sql.y"
             {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2922 "yacc_sql.cpp"
    break;

  case 104: /* add_expr_list: add_expr  */
#line 1007 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2931 "yacc_sql.cpp"
    break;

  case 105: /* add_expr_list: add_expr COMMA add_expr_list  */
#line 1012 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2944 "yacc_sql.cpp"
    break;

  case 106: /* add_expr: mul_expr  */
#line 1022 "yacc_sql.y"
            {

    }
#line 2952 "yacc_sql.cpp"
    break;

  case 107: /* add_expr: add_expr '+' mul_expr  */
#line 1025 "yacc_sql.y"
                            {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2960 "yacc_sql.cpp"
    break;

  case 108: /* add_expr: add_expr MINUS mul_expr  */
#line 1028 "yacc_sql.y"
                              {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2968 "yacc_sql.cpp"
    break;

  case 109: /* mul_expr: base_expr  */
#line 1033 "yacc_sql.y"
             {

    }
#line 2976 "yacc_sql.cpp"
    break;

  case 110: /* mul_expr: mul_expr '*' base_expr  */
#line 1036 "yacc_sql.y"
                             {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2984 "yacc_sql.cpp"
    break;

  case 111: /* mul_expr: mul_expr '/' base_expr  */
#line 1039 "yacc_sql.y"
                             {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2992 "yacc_sql.cpp"
    break;

  case 112: /* mul_expr: NEGATIVE_NUM base_expr  */
#line 1042 "yacc_sql.y"
                             {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3000 "yacc_sql.cpp"
    break;

  case 113: /* base_expr: LBRACE add_expr RBRACE  */
#line 1047 "yacc_sql.y"
                           {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3009 "yacc_sql.cpp"
    break;

  case 114: /* base_expr: value2  */
#line 1051 "yacc_sql.y"
             {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 3019 "yacc_sql.cpp"
    break;

  case 115: /* base_expr: cal_attr  */
#line 1056 "yacc_sql.y"
               {
      std::string table = (yyvsp[0].rel_attr)->relation_name;
      std::string attribute = (yyvsp[0].rel_attr)->attribute_name;
      std::string alias = (yyvsp[0].rel_attr)->alias;
      AggrOp aggr = (yyvsp[0].rel_attr)->aggr_func;
      (yyval.expression) = new FieldExpr(table, attribute, aggr,alias);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 3033 "yacc_sql.cpp"
    break;

  case 116: /* value2: NUMBER  */
#line 1067 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 3042 "yacc_sql.cpp"
    break;

  case 117: /* value2: FLOAT  */
#line 1071 "yacc_sql.y"
            {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 3051 "yacc_sql.cpp"
    break;

  case 118: /* value2: NUMBER_NEGA  */
#line 1075 "yacc_sql.y"
                  {
      int temp = (int)(yyvsp[0].number);
      temp *= (-1);
      (yyval.value) = new Value(temp);
      (yyloc) = (yylsp[0]);
    }
#line 3062 "yacc_sql.cpp"
    break;

  case 119: /* value2: FLOAT_NEGA  */
#line 1081 "yacc_sql.y"
                 {
      float temp = (float)(yyvsp[0].floats);
      temp *= (-1.0);
      (yyval.value) = new Value(temp);
      (yyloc) = (yylsp[0]);
    }
#line 3073 "yacc_sql.cpp"
    break;

  case 120: /* value2: NULL_T  */
#line 1087 "yacc_sql.y"
            { //要放到SSS的前面
      //char *tmp = common::substr($1,1,strlen($1)-2);
      (yyval.value) = new Value(0);
      (yyval.value)->set_null_value();
      //free(tmp);
    }
#line 3084 "yacc_sql.cpp"
    break;

  case 121: /* value2: SSS  */
#line 1093 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 3094 "yacc_sql.cpp"
    break;

  case 122: /* value2: DATESSS  */
#line 1098 "yacc_sql.y"
             {
			char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(1, tmp);
      free(tmp);
		}
#line 3104 "yacc_sql.cpp"
    break;

  case 123: /* cal_attr: '*'  */
#line 1105 "yacc_sql.y"
        {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = "";
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->fun_op = UNCHECKED;
      (yyloc) = (yylsp[0]);
    }
#line 3117 "yacc_sql.cpp"
    break;

  case 124: /* cal_attr: ID  */
#line 1113 "yacc_sql.y"
         {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->fun_op = UNCHECKED;
      (yyloc) = (yylsp[0]);
      free((yyvsp[0].string));
    }
#line 3130 "yacc_sql.cpp"
    break;

  case 125: /* cal_attr: ID DOT '*'  */
#line 1121 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->fun_op = UNCHECKED;
      (yyloc) = (yylsp[-2]);
      free((yyvsp[-2].string));
      
    }
#line 3145 "yacc_sql.cpp"
    break;

  case 126: /* cal_attr: ID DOT ID  */
#line 1131 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->fun_op = UNCHECKED;
      (yyloc) = (yylsp[-2]);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3160 "yacc_sql.cpp"
    break;

  case 127: /* cal_attr: aggr_func LBRACE '*' RBRACE  */
#line 1141 "yacc_sql.y"
                                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggr_func = (yyvsp[-3].aggr);
      (yyval.rel_attr)->fun_op = UNCHECKED;
      (yyloc) = (yylsp[-3]);
    }
#line 3172 "yacc_sql.cpp"
    break;

  case 128: /* cal_attr: aggr_func LBRACE ID RBRACE  */
#line 1148 "yacc_sql.y"
                                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-3].aggr);
      (yyval.rel_attr)->fun_op = UNCHECKED;
      (yyloc) = (yylsp[-3]);
      free((yyvsp[-1].string));
    }
#line 3185 "yacc_sql.cpp"
    break;

  case 129: /* cal_attr: aggr_func LBRACE ID DOT ID RBRACE  */
#line 1156 "yacc_sql.y"
                                       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-5].aggr);
      (yyval.rel_attr)->fun_op = UNCHECKED;
      (yyloc) = (yylsp[-5]);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 3200 "yacc_sql.cpp"
    break;

  case 130: /* cal_attr: ID AS ID  */
#line 1166 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->fun_op = UNCHECKED;
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[0].string));
      free((yyvsp[-2].string));
    }
#line 3214 "yacc_sql.cpp"
    break;

  case 131: /* cal_attr: ID DOT ID AS ID  */
#line 1175 "yacc_sql.y"
                      {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-4].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->fun_op = UNCHECKED;
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3230 "yacc_sql.cpp"
    break;

  case 132: /* cal_attr: aggr_func LBRACE '*' RBRACE AS ID  */
#line 1186 "yacc_sql.y"
                                        {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggr_func = (yyvsp[-5].aggr);
      (yyval.rel_attr)->fun_op = UNCHECKED;
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3243 "yacc_sql.cpp"
    break;

  case 133: /* cal_attr: aggr_func LBRACE ID RBRACE AS ID  */
#line 1194 "yacc_sql.y"
                                      {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-3].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-5].aggr);
       (yyval.rel_attr)->alias = (yyvsp[0].string);
       (yyval.rel_attr)->fun_op = UNCHECKED;
       free((yyvsp[0].string));
      free((yyvsp[-3].string));
    }
#line 3257 "yacc_sql.cpp"
    break;

  case 134: /* cal_attr: aggr_func LBRACE ID DOT ID RBRACE AS ID  */
#line 1203 "yacc_sql.y"
                                             {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-5].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-3].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-7].aggr);
      (yyval.rel_attr)->fun_op = UNCHECKED;
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[0].string));
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 3273 "yacc_sql.cpp"
    break;

  case 135: /* cal_attr: ID ID  */
#line 1214 "yacc_sql.y"
             { //不加AS也可以
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->fun_op = UNCHECKED;
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[0].string));
      free((yyvsp[-1].string));
    }
#line 3287 "yacc_sql.cpp"
    break;

  case 136: /* cal_attr: ID DOT ID ID  */
#line 1223 "yacc_sql.y"
                   {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->fun_op = UNCHECKED;
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3303 "yacc_sql.cpp"
    break;

  case 137: /* cal_attr: aggr_func LBRACE '*' RBRACE ID  */
#line 1234 "yacc_sql.y"
                                     {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggr_func = (yyvsp[-4].aggr);
      (yyval.rel_attr)->fun_op = UNCHECKED;
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3316 "yacc_sql.cpp"
    break;

  case 138: /* cal_attr: aggr_func LBRACE ID RBRACE ID  */
#line 1242 "yacc_sql.y"
                                   {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-4].aggr);
       (yyval.rel_attr)->alias = (yyvsp[0].string);
       (yyval.rel_attr)->fun_op = UNCHECKED;
       
       free((yyvsp[0].string));
      free((yyvsp[-2].string));
    }
#line 3331 "yacc_sql.cpp"
    break;

  case 139: /* cal_attr: aggr_func LBRACE ID DOT ID RBRACE ID  */
#line 1252 "yacc_sql.y"
                                          {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-4].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-6].aggr);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
       (yyval.rel_attr)->fun_op = UNCHECKED;
      free((yyvsp[0].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 3347 "yacc_sql.cpp"
    break;

  case 140: /* cal_attr: LENGTH LBRACE value RBRACE ID  */
#line 1264 "yacc_sql.y"
    {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->alias = (yyvsp[0].string);
       (yyval.rel_attr)->fun_op = FUNC_ROUND;
      FuncExpr funcExpr;
      //func_expr.funcOp = LENGTH;
      //funcExpr.value = std::make_pair($3,$3);
      funcExpr.is_func = false;
      (yyval.rel_attr)->func = funcExpr;
      free((yyvsp[-2].value));
      free((yyvsp[0].string));
    }
#line 3365 "yacc_sql.cpp"
    break;

  case 141: /* cal_attr: ROUND LBRACE value RBRACE ID  */
#line 1279 "yacc_sql.y"
    {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      (yyval.rel_attr)->fun_op = FUNC_ROUND;
      FuncExpr funcExpr;
      //funcExpr.value = std::make_pair($3,$3);
      funcExpr.is_func = false;
      (yyval.rel_attr)->func = funcExpr;
      free((yyvsp[-2].value));
      free((yyvsp[0].string));
    }
#line 3382 "yacc_sql.cpp"
    break;

  case 142: /* cal_attr: ROUND LBRACE value COMMA value RBRACE ID  */
#line 1293 "yacc_sql.y"
    {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      (yyval.rel_attr)->fun_op = FUNC_ROUND;
      FuncExpr funcExpr;
      //funcExpr.value = std::make_pair($3,$5);
      funcExpr.is_func = false;
      (yyval.rel_attr)->func = funcExpr;
      free((yyvsp[-4].value));
      free((yyvsp[-2].value));
      free((yyvsp[0].string));
    }
#line 3400 "yacc_sql.cpp"
    break;

  case 143: /* cal_attr: DATE_FORMAT LBRACE value COMMA value RBRACE ID  */
#line 1308 "yacc_sql.y"
    {
       (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      (yyval.rel_attr)->fun_op = FUNC_DATE_FORMAT;
      FuncExpr funcExpr;
      //funcExpr.value = std::make_pair($3,$5);
      funcExpr.is_func = false;
      (yyval.rel_attr)->func = funcExpr;
      free((yyvsp[-4].value));
      free((yyvsp[-2].value));
      free((yyvsp[0].string));
    }
#line 3418 "yacc_sql.cpp"
    break;

  case 144: /* aggr_func: MAX  */
#line 1324 "yacc_sql.y"
        { (yyval.aggr)=MAXF; }
#line 3424 "yacc_sql.cpp"
    break;

  case 145: /* aggr_func: MIN  */
#line 1325 "yacc_sql.y"
                { (yyval.aggr)=MINF; }
#line 3430 "yacc_sql.cpp"
    break;

  case 146: /* aggr_func: COUNT  */
#line 1326 "yacc_sql.y"
                  { (yyval.aggr)=COUNTF; }
#line 3436 "yacc_sql.cpp"
    break;

  case 147: /* aggr_func: AVG  */
#line 1327 "yacc_sql.y"
                { (yyval.aggr)=AVGF; }
#line 3442 "yacc_sql.cpp"
    break;

  case 148: /* aggr_func: SUM  */
#line 1328 "yacc_sql.y"
                { (yyval.aggr)=SUMF; }
#line 3448 "yacc_sql.cpp"
    break;

  case 149: /* rel_list: %empty  */
#line 1332 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 3456 "yacc_sql.cpp"
    break;

  case 150: /* rel_list: COMMA rel rel_list  */
#line 1335 "yacc_sql.y"
                         {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<RelName>;
      }

      (yyval.relation_list)->push_back(*(yyvsp[-1].rel_name));//本来是字符串char* 所以这里要加*
      free((yyvsp[-1].rel_name));
    }
#line 3471 "yacc_sql.cpp"
    break;

  case 151: /* join_list: %empty  */
#line 1348 "yacc_sql.y"
    {
      (yyval.join_lists) = nullptr;
    }
#line 3479 "yacc_sql.cpp"
    break;

  case 152: /* join_list: INNER JOIN rel on join_list  */
#line 1351 "yacc_sql.y"
                                 {
      if ((yyvsp[0].join_lists) != nullptr) {
        (yyval.join_lists) = (yyvsp[0].join_lists);
      } else {
        (yyval.join_lists) = new std::vector<InnerJoinSqlNode>;
      }
      InnerJoinSqlNode current;
      current.join_relations = *(yyvsp[-2].rel_name);
      current.join_conditions.swap(*(yyvsp[-1].condition_list));
      (yyval.join_lists)->push_back(current);

      free((yyvsp[-2].rel_name));
      free((yyvsp[-1].condition_list));
    }
#line 3498 "yacc_sql.cpp"
    break;

  case 153: /* on: %empty  */
#line 1368 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3506 "yacc_sql.cpp"
    break;

  case 154: /* on: ON condition_list  */
#line 1371 "yacc_sql.y"
                        {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3514 "yacc_sql.cpp"
    break;

  case 155: /* having: %empty  */
#line 1377 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3522 "yacc_sql.cpp"
    break;

  case 156: /* having: HAVING condition_list  */
#line 1380 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3530 "yacc_sql.cpp"
    break;

  case 157: /* where: %empty  */
#line 1386 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3538 "yacc_sql.cpp"
    break;

  case 158: /* where: WHERE condition_list  */
#line 1389 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3546 "yacc_sql.cpp"
    break;

  case 159: /* condition_list: %empty  */
#line 1395 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3554 "yacc_sql.cpp"
    break;

  case 160: /* condition_list: condition  */
#line 1398 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3564 "yacc_sql.cpp"
    break;

  case 161: /* condition_list: condition AND condition_list  */
#line 1403 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->conjunction = 0;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3575 "yacc_sql.cpp"
    break;

  case 162: /* condition_list: condition OR condition_list  */
#line 1409 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->conjunction = 1;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3586 "yacc_sql.cpp"
    break;

  case 163: /* condition: add_expr cal_comp_op add_expr  */
#line 1418 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3599 "yacc_sql.cpp"
    break;

  case 164: /* condition: sub_select_stmt cal_comp_op sub_select_stmt  */
#line 1427 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_sql = (yyvsp[-2].sub_sql_node);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_sql = (yyvsp[0].sub_sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3612 "yacc_sql.cpp"
    break;

  case 165: /* condition: add_expr cal_comp_op sub_select_stmt  */
#line 1436 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_sql = (yyvsp[0].sub_sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3625 "yacc_sql.cpp"
    break;

  case 166: /* condition: sub_select_stmt cal_comp_op add_expr  */
#line 1445 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_sql = (yyvsp[-2].sub_sql_node);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3638 "yacc_sql.cpp"
    break;

  case 167: /* condition: add_expr logical_comp_op LBRACE value value_list RBRACE  */
#line 1454 "yacc_sql.y"
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
#line 3655 "yacc_sql.cpp"
    break;

  case 168: /* condition: add_expr logical_comp_op sub_select_stmt  */
#line 1467 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_sql = (yyvsp[0].sub_sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3668 "yacc_sql.cpp"
    break;

  case 169: /* condition: cal_comp_op sub_select_stmt  */
#line 1477 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = -1;
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_sql = (yyvsp[0].sub_sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3680 "yacc_sql.cpp"
    break;

  case 170: /* condition: add_expr cal_comp_op  */
#line 1486 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_expr = (yyvsp[-1].expression);
      (yyval.condition)->right_is_attr = -1;
      (yyval.condition)->comp = (yyvsp[0].comp);
    }
#line 3692 "yacc_sql.cpp"
    break;

  case 171: /* cal_comp_op: EQ  */
#line 1496 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3698 "yacc_sql.cpp"
    break;

  case 172: /* cal_comp_op: LT  */
#line 1497 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3704 "yacc_sql.cpp"
    break;

  case 173: /* cal_comp_op: GT  */
#line 1498 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3710 "yacc_sql.cpp"
    break;

  case 174: /* cal_comp_op: LE  */
#line 1499 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3716 "yacc_sql.cpp"
    break;

  case 175: /* cal_comp_op: GE  */
#line 1500 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3722 "yacc_sql.cpp"
    break;

  case 176: /* cal_comp_op: NE  */
#line 1501 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3728 "yacc_sql.cpp"
    break;

  case 177: /* cal_comp_op: LIKE  */
#line 1502 "yacc_sql.y"
           { (yyval.comp) = REGEX_LIKE; }
#line 3734 "yacc_sql.cpp"
    break;

  case 178: /* cal_comp_op: NOT LIKE  */
#line 1503 "yacc_sql.y"
               { (yyval.comp) = REGEX_NOT_LIKE; }
#line 3740 "yacc_sql.cpp"
    break;

  case 179: /* cal_comp_op: IS NULL_T  */
#line 1504 "yacc_sql.y"
               { (yyval.comp) = IS_NULL; }
#line 3746 "yacc_sql.cpp"
    break;

  case 180: /* cal_comp_op: IS NOT NULL_T  */
#line 1505 "yacc_sql.y"
                   { (yyval.comp) = IS_NOT_NULL; }
#line 3752 "yacc_sql.cpp"
    break;

  case 181: /* cal_comp_op: EXISTS  */
#line 1506 "yacc_sql.y"
             { (yyval.comp) = EXISTS_QUERY; }
#line 3758 "yacc_sql.cpp"
    break;

  case 182: /* cal_comp_op: NOT EXISTS  */
#line 1507 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS_QUERY; }
#line 3764 "yacc_sql.cpp"
    break;

  case 183: /* logical_comp_op: IN  */
#line 1510 "yacc_sql.y"
         { (yyval.comp) = IN_QUERY; }
#line 3770 "yacc_sql.cpp"
    break;

  case 184: /* logical_comp_op: NOT IN  */
#line 1511 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_QUERY; }
#line 3776 "yacc_sql.cpp"
    break;

  case 185: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1515 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3790 "yacc_sql.cpp"
    break;

  case 186: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1528 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3799 "yacc_sql.cpp"
    break;

  case 187: /* set_variable_stmt: SET ID EQ value  */
#line 1536 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3811 "yacc_sql.cpp"
    break;


#line 3815 "yacc_sql.cpp"

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

#line 1548 "yacc_sql.y"

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
