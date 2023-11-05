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

FuncExpr *create_func_expression(FuncOp type,
                                             Expression *child,
                                             Expression *constarin,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  FuncExpr *expr = new FuncExpr(type, child, constarin);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

FuncExpr *create_func_expression_alias(FuncOp type,
                                             Expression *child,
                                             Expression *constarin,
                                             std::string alias,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  FuncExpr *expr = new FuncExpr(type, child, constarin, alias);
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


#line 161 "yacc_sql.cpp"

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
  YYSYMBOL_function_attr = 133,            /* function_attr  */
  YYSYMBOL_cal_attr = 134,                 /* cal_attr  */
  YYSYMBOL_aggr_func = 135,                /* aggr_func  */
  YYSYMBOL_rel_list = 136,                 /* rel_list  */
  YYSYMBOL_join_list = 137,                /* join_list  */
  YYSYMBOL_on = 138,                       /* on  */
  YYSYMBOL_having = 139,                   /* having  */
  YYSYMBOL_where = 140,                    /* where  */
  YYSYMBOL_condition_list = 141,           /* condition_list  */
  YYSYMBOL_condition = 142,                /* condition  */
  YYSYMBOL_cal_comp_op = 143,              /* cal_comp_op  */
  YYSYMBOL_logical_comp_op = 144,          /* logical_comp_op  */
  YYSYMBOL_load_data_stmt = 145,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 146,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 147,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 148             /* opt_semicolon  */
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
#define YYFINAL  86
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   499

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  220
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  400

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
       0,   288,   288,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   319,   325,   330,   336,   342,   348,   354,
     361,   367,   375,   396,   421,   424,   435,   444,   454,   472,
     485,   488,   501,   510,   519,   528,   538,   547,   555,   566,
     569,   570,   571,   572,   575,   591,   594,   608,   624,   627,
     638,   642,   646,   650,   654,   660,   665,   674,   686,   725,
     728,   738,   746,   757,   803,   816,   824,   830,   841,   844,
     855,   861,   872,   875,   887,   890,   903,   906,   919,   926,
     933,   941,   948,   956,   965,   989,   999,  1004,  1015,  1018,
    1021,  1024,  1027,  1031,  1034,  1041,  1046,  1057,  1060,  1063,
    1068,  1071,  1074,  1077,  1082,  1086,  1091,  1100,  1105,  1109,
    1113,  1119,  1125,  1131,  1136,  1143,  1150,  1157,  1163,  1169,
    1176,  1184,  1190,  1197,  1205,  1211,  1218,  1226,  1232,  1239,
    1247,  1254,  1261,  1267,  1276,  1285,  1293,  1303,  1313,  1321,
    1328,  1335,  1344,  1354,  1363,  1372,  1381,  1390,  1399,  1406,
    1413,  1422,  1431,  1437,  1444,  1453,  1461,  1471,  1478,  1486,
    1496,  1504,  1514,  1521,  1530,  1543,  1544,  1545,  1546,  1547,
    1551,  1554,  1567,  1570,  1587,  1590,  1596,  1599,  1605,  1608,
    1614,  1617,  1622,  1628,  1636,  1645,  1654,  1663,  1672,  1685,
    1695,  1704,  1715,  1716,  1717,  1718,  1719,  1720,  1721,  1722,
    1723,  1724,  1725,  1726,  1729,  1730,  1733,  1746,  1754,  1764,
    1765
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
  "add_expr", "mul_expr", "base_expr", "value2", "function_attr",
  "cal_attr", "aggr_func", "rel_list", "join_list", "on", "having",
  "where", "condition_list", "condition", "cal_comp_op", "logical_comp_op",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-296)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     407,    44,   163,   168,   222,   -50,   141,  -296,    13,    -7,
      -3,  -296,  -296,  -296,  -296,  -296,    48,   105,   407,   197,
     205,  -296,  -296,  -296,  -296,  -296,  -296,  -296,  -296,  -296,
    -296,  -296,  -296,  -296,  -296,  -296,  -296,  -296,  -296,  -296,
    -296,   131,   144,   214,   156,   162,   168,   168,  -296,  -296,
    -296,  -296,  -296,  -296,  -296,  -296,     1,  -296,   297,   215,
     223,   225,   222,  -296,  -296,  -296,  -296,  -296,   -10,  -296,
     209,     9,   -31,  -296,  -296,  -296,  -296,   227,  -296,  -296,
     198,   199,   230,   216,   229,  -296,  -296,  -296,  -296,    25,
     241,   231,  -296,   248,  -296,     5,   168,   168,   168,   168,
     168,  -296,   104,   185,   255,    11,   233,   -53,  -296,   234,
     222,   222,   222,   297,   297,    88,   266,   267,   240,   318,
     251,   301,   249,   254,   275,   270,  -296,   119,  -296,   119,
    -296,  -296,   111,  -296,  -296,  -296,    -5,  -296,  -296,   313,
      -9,   204,   118,   316,  -296,  -296,    -6,  -296,     2,   319,
     -31,  -296,   -31,  -296,  -296,    29,   327,   320,    60,  -296,
     294,   330,  -296,   321,  -296,   120,   331,   338,   292,  -296,
    -296,  -296,     7,   300,    19,    20,   318,   302,    26,   318,
     318,   303,   318,   305,  -296,   307,  -296,   234,   335,    27,
     311,    35,   318,   357,   117,   210,   -41,  -296,  -296,  -296,
    -296,  -296,  -296,  -296,  -296,   345,   143,  -296,     0,   360,
     286,   240,   267,   379,  -296,  -296,  -296,  -296,  -296,   114,
     249,   363,   323,   365,   324,  -296,   371,   326,  -296,   328,
    -296,   373,   375,   332,  -296,   376,   377,   378,   389,  -296,
    -296,   319,   370,   267,   348,  -296,   391,   350,  -296,   396,
     320,  -296,  -296,   380,   222,  -296,  -296,   264,  -296,     8,
     264,   400,    60,    60,   414,  -296,  -296,  -296,   330,  -296,
     361,   364,  -296,   390,   331,  -296,  -296,   408,   323,  -296,
      43,  -296,  -296,    45,    47,  -296,    74,    75,   318,    77,
    -296,   234,   422,  -296,   103,  -296,   318,   415,   357,  -296,
     398,  -296,    14,  -296,  -296,    14,   308,  -296,  -296,  -296,
    -296,  -296,  -296,   416,  -296,  -296,   323,   417,   408,   374,
    -296,   381,  -296,   382,  -296,   383,  -296,   384,  -296,   421,
     385,  -296,   392,   431,   432,   386,  -296,   396,  -296,  -296,
     234,   396,   154,   408,  -296,   424,  -296,  -296,  -296,  -296,
    -296,   122,  -296,    60,   335,   387,    60,   436,  -296,  -296,
     319,   434,  -296,   419,  -296,  -296,   393,  -296,  -296,  -296,
     427,   441,  -296,   443,  -296,   267,  -296,  -296,  -296,   397,
     387,  -296,   399,   444,  -296,   441,    10,   445,  -296,  -296,
    -296,  -296,   401,   399,  -296,   218,   445,  -296,  -296,  -296
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     219,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,     0,   122,   118,
     120,   119,   121,   123,   124,    95,    96,   104,     0,     0,
       0,     0,     0,   175,   176,   179,   178,   177,   159,   158,
      74,   105,   107,   110,   115,   117,   116,     0,    31,    30,
       0,     0,     0,     0,     0,   217,     1,   220,     2,     0,
       0,     0,    29,     0,   103,     0,     0,     0,     0,     0,
       0,   113,     0,     0,     0,     0,     0,     0,   170,     0,
       0,     0,     0,     0,     0,     0,     0,   188,     0,     0,
       0,     0,     0,     0,     0,     0,   102,    99,    97,    98,
     100,   101,     0,    64,    60,    62,     0,    65,    66,     0,
       0,     0,     0,     0,   114,   165,   161,   160,    76,   180,
     109,   106,   108,   111,   112,     0,     0,     0,   190,    67,
       0,    69,   218,     0,    39,     0,    40,     0,     0,    37,
      61,    63,   128,     0,   127,   137,     0,     0,   142,     0,
       0,     0,     0,     0,   171,     0,    75,     0,   182,   163,
       0,   162,     0,    55,     0,     0,     0,   208,   202,   203,
     204,   205,   206,   207,   212,     0,     0,   189,   191,     0,
       0,     0,   188,     0,    50,    51,    53,    52,    47,    48,
       0,     0,     0,     0,     0,   130,     0,     0,   125,     0,
     138,     0,     0,     0,   140,     0,     0,     0,     0,   166,
      77,   180,     0,   188,     0,   173,     0,     0,   172,    58,
       0,    54,   210,     0,     0,   209,   213,     0,   214,     0,
     201,     0,   190,   190,     0,   200,    71,    72,    69,    68,
       0,     0,    46,     0,    40,    38,    36,    34,     0,   129,
     131,   126,   139,   148,   134,   141,   145,   149,     0,   157,
     181,     0,    78,   168,   164,   167,     0,     0,    55,   211,
       0,   195,   197,   215,   196,   194,     0,   199,   193,   192,
      70,   216,    49,     0,    45,    41,     0,     0,    34,     0,
     133,     0,   146,     0,   135,     0,   143,     0,   153,     0,
       0,   151,   184,     0,   186,     0,   174,    58,    57,    56,
       0,    58,    42,    34,    32,     0,   132,   147,   136,   144,
     154,   150,   152,   190,   182,     0,   190,    84,   169,    59,
     180,     0,    44,     0,    35,    33,     0,   155,   185,   183,
      80,    82,   187,     0,    73,   188,   198,    43,   156,     0,
       0,    79,     0,     0,    81,    82,    88,    86,    94,    83,
      90,    91,     0,     0,    85,    89,    86,    92,    93,    87
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -296,  -296,   463,  -296,  -296,  -296,  -296,  -296,  -296,  -296,
    -296,  -296,  -296,  -295,  -267,  -296,  -296,   208,   263,  -296,
    -296,  -296,   186,   235,  -164,  -102,  -296,  -296,   219,   277,
     368,  -182,  -296,   106,   107,  -296,    94,    98,   -65,  -296,
     402,   128,  -107,    -4,    78,    93,     4,  -296,  -296,  -296,
    -235,   139,  -296,  -296,  -209,  -243,  -296,    46,  -296,  -296,
    -296,  -296,  -296
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   317,   277,    31,    32,   221,   166,   313,
     219,    33,   251,   193,   297,   139,    34,    35,   212,   161,
      36,   149,   334,   371,   381,   374,   394,   387,   205,    37,
      55,    56,    70,   206,    72,    73,    74,    75,    76,    77,
     188,   243,   354,   357,   159,   207,   208,   209,   261,    38,
      39,    40,    88
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      71,   141,   143,   269,   151,   241,   290,    57,    96,   262,
     106,   318,    96,   303,   183,   255,   110,   162,   110,   308,
     309,   110,   185,   345,   175,   176,   146,   224,   172,    78,
     147,   390,   391,   256,   292,    97,   107,   177,   126,   227,
     229,   173,    81,   111,   144,   121,   233,   244,   364,   343,
      57,    57,   113,   114,   263,   247,   392,   122,   105,    41,
      80,    42,   189,   319,   255,   321,   194,   323,    58,   108,
      59,    60,    61,   184,   231,   190,    82,   235,   236,    43,
     238,   186,   256,    98,    99,   100,   225,    98,    99,   100,
     249,   112,   195,   112,   325,   327,   112,   330,   228,   230,
      57,    57,    57,    57,    57,   234,   245,    71,   266,   332,
     368,    48,   132,   372,   248,   196,   197,    63,    64,    65,
      66,    67,   320,   335,   322,   375,   324,    83,   198,   199,
     200,   201,   202,   203,   204,    49,    50,    51,    52,    68,
      53,    54,   366,    69,   265,   267,   271,   300,   258,   194,
     110,   101,   180,   326,   328,   133,   331,    79,   360,   214,
     215,   216,   217,   218,   181,   272,   383,   155,   252,   273,
      84,   156,   253,   359,    94,    95,    46,   361,    44,   134,
      45,   135,   336,   136,   137,   138,   329,   170,   150,   171,
     152,   105,   301,   132,   337,   304,   307,    86,   259,   197,
      47,   367,    99,   100,   341,   362,   153,   154,    87,   363,
      89,   198,   199,   200,   201,   202,   203,   204,    58,    48,
      59,    60,    61,    90,   127,   112,   129,   130,   131,   254,
      58,    91,    59,    60,    61,    92,   133,   178,   179,   397,
     398,    93,    62,    49,    50,    51,    52,   102,    53,    54,
      71,   257,   260,   302,    62,   103,   305,   104,   109,   115,
     134,    48,   135,   132,   140,   137,   138,    63,    64,    65,
      66,    67,    58,    48,    59,    60,    61,   116,   117,    63,
      64,    65,    66,    67,   119,    49,    50,    51,    52,    68,
      53,    54,   118,    69,   132,   120,   195,    49,    50,    51,
      52,    68,    53,    54,   123,    69,   133,    59,    60,    61,
     124,   125,   145,   148,   157,    48,   132,   158,   264,   160,
       4,    63,    64,    65,    66,    67,   132,   254,   165,    62,
     134,   163,   135,   167,   142,   137,   138,   133,   168,    49,
      50,    51,    52,    68,    53,    54,   174,    69,    48,   169,
     182,   194,   192,   187,    63,    64,    65,    66,    67,   133,
     191,   134,   210,   135,   211,   220,   137,   138,   213,   133,
     222,   223,    49,    50,    51,    52,    68,    53,    54,   226,
      69,   232,   237,   134,   239,   135,   240,   242,   137,   138,
     246,   250,   264,   134,   270,   135,   275,   278,   137,   138,
     196,   197,   276,   279,   280,   281,   283,   282,   284,   286,
     287,   285,   288,   198,   199,   200,   201,   202,   203,   204,
       1,     2,   289,   291,   294,     3,     4,   293,     5,   295,
     296,   299,   306,   254,     6,     7,     8,     9,    10,   312,
     311,   314,   316,    11,    12,    13,   333,   340,   338,   342,
     344,    14,    15,   346,   351,   353,   355,   365,   356,   373,
     347,   348,   349,   350,   352,   358,   370,   376,   382,    16,
     377,    17,   378,   379,    18,   380,   384,   388,   386,   393,
     395,    85,   315,   274,   339,   298,   385,   310,   268,   164,
     399,   396,   389,   369,     0,     0,     0,     0,     0,   128
};

static const yytype_int16 yycheck[] =
{
       4,   103,   104,   212,   111,   187,   241,     3,     7,     9,
      20,   278,     7,     5,    20,    56,     7,   119,     7,   262,
     263,     7,    20,   318,    33,    34,    79,    20,    33,    79,
      83,    21,    22,    74,   243,    34,    46,    46,    33,    20,
      20,    46,    49,    34,    33,    20,    20,    20,   343,   316,
      46,    47,    83,    84,    54,    20,    46,    32,    62,    15,
      47,    17,    33,    20,    56,    20,     6,    20,     8,    79,
      10,    11,    12,    79,   176,    46,    79,   179,   180,    35,
     182,    79,    74,    82,    83,    84,    79,    82,    83,    84,
     192,    82,    32,    82,    20,    20,    82,    20,    79,    79,
      96,    97,    98,    99,   100,    79,    79,   111,   210,   291,
     353,    51,     8,   356,    79,    55,    56,    57,    58,    59,
      60,    61,    79,    20,    79,   360,    79,    79,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    20,    83,   209,   210,    32,   254,     5,     6,
       7,    58,    34,    79,    79,    51,    79,    16,   340,    39,
      40,    41,    42,    43,    46,    51,   375,    79,    51,    55,
      65,    83,    55,   337,    46,    47,     8,   341,    15,    75,
      17,    77,    79,    79,    80,    81,   288,    76,   110,    78,
     112,   195,   257,     8,   296,   260,   261,     0,    55,    56,
      32,    79,    83,    84,   306,    51,   113,   114,     3,    55,
      79,    68,    69,    70,    71,    72,    73,    74,     8,    51,
      10,    11,    12,    79,    96,    82,    98,    99,   100,    19,
       8,    17,    10,    11,    12,    79,    51,    33,    34,    21,
      22,    79,    32,    75,    76,    77,    78,    32,    80,    81,
     254,   205,   206,   257,    32,    32,   260,    32,    49,    32,
      75,    51,    77,     8,    79,    80,    81,    57,    58,    59,
      60,    61,     8,    51,    10,    11,    12,    79,    79,    57,
      58,    59,    60,    61,    68,    75,    76,    77,    78,    79,
      80,    81,    62,    83,     8,    66,    32,    75,    76,    77,
      78,    79,    80,    81,    63,    83,    51,    10,    11,    12,
      79,    63,    79,    79,    48,    51,     8,    50,    32,    79,
      19,    57,    58,    59,    60,    61,     8,    19,    79,    32,
      75,    80,    77,    79,    79,    80,    81,    51,    63,    75,
      76,    77,    78,    79,    80,    81,    33,    83,    51,    79,
      34,     6,    32,    34,    57,    58,    59,    60,    61,    51,
      33,    75,    68,    77,    34,    34,    80,    81,    47,    51,
      32,    79,    75,    76,    77,    78,    79,    80,    81,    79,
      83,    79,    79,    75,    79,    77,    79,    52,    80,    81,
      79,    34,    32,    75,    15,    77,    33,    32,    80,    81,
      55,    56,    79,    79,    33,    79,    33,    79,    33,    33,
      33,    79,    34,    68,    69,    70,    71,    72,    73,    74,
      13,    14,    33,    53,    33,    18,    19,    79,    21,    79,
      34,    51,    32,    19,    27,    28,    29,    30,    31,    75,
      79,    51,    34,    36,    37,    38,    24,    49,    33,    33,
      33,    44,    45,    79,    33,    63,    25,    33,    26,    23,
      79,    79,    79,    79,    79,    79,    79,    33,    25,    62,
      51,    64,    79,    46,    67,    34,    79,    33,    79,    34,
      79,    18,   274,   220,   298,   250,   380,   268,   211,   121,
     396,   393,   385,   354,    -1,    -1,    -1,    -1,    -1,    97
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    14,    18,    19,    21,    27,    28,    29,    30,
      31,    36,    37,    38,    44,    45,    62,    64,    67,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,   101,   102,   107,   112,   113,   116,   125,   145,   146,
     147,    15,    17,    35,    15,    17,     8,    32,    51,    75,
      76,    77,    78,    80,    81,   126,   127,   132,     8,    10,
      11,    12,    32,    57,    58,    59,    60,    61,    79,    83,
     128,   129,   130,   131,   132,   133,   134,   135,    79,    16,
      47,    49,    79,    79,    65,    88,     0,     3,   148,    79,
      79,    17,    79,    79,   127,   127,     7,    34,    82,    83,
      84,   131,    32,    32,    32,   129,    20,    46,    79,    49,
       7,    34,    82,    83,    84,    32,    79,    79,    62,    68,
      66,    20,    32,    63,    79,    63,    33,   127,   126,   127,
     127,   127,     8,    51,    75,    77,    79,    80,    81,   111,
      79,   111,    79,   111,    33,    79,    79,    83,    79,   117,
     130,   128,   130,   131,   131,    79,    83,    48,    50,   140,
      79,   115,   111,    80,   116,    79,   104,    79,    63,    79,
      76,    78,    33,    46,    33,    33,    34,    46,    33,    34,
      34,    46,    34,    20,    79,    20,    79,    34,   136,    33,
      46,    33,    32,   109,     6,    32,    55,    56,    68,    69,
      70,    71,    72,    73,    74,   124,   129,   141,   142,   143,
      68,    34,   114,    47,    39,    40,    41,    42,    43,   106,
      34,   103,    32,    79,    20,    79,    79,    20,    79,    20,
      79,   111,    79,    20,    79,   111,   111,    79,   111,    79,
      79,   117,    52,   137,    20,    79,    79,    20,    79,   111,
      34,   108,    51,    55,    19,    56,    74,   143,     5,    55,
     143,   144,     9,    54,    32,   124,   111,   124,   115,   140,
      15,    32,    51,    55,   104,    33,    79,   100,    32,    79,
      33,    79,    79,    33,    33,    79,    33,    33,    34,    33,
     136,    53,   140,    79,    33,    79,    34,   110,   109,    51,
     128,   124,   129,     5,   124,   129,    32,   124,   141,   141,
     114,    79,    75,   105,    51,   103,    34,    99,   100,    20,
      79,    20,    79,    20,    79,    20,    79,    20,    79,   111,
      20,    79,   117,    24,   118,    20,    79,   111,    33,   108,
      49,   111,    33,   100,    33,    99,    79,    79,    79,    79,
      79,    33,    79,    63,   138,    25,    26,   139,    79,   110,
     117,   110,    51,    55,    99,    33,    20,    79,   141,   137,
      79,   119,   141,    23,   121,   136,    33,    51,    79,    46,
      34,   120,    25,   140,    79,   119,    79,   123,    33,   120,
      21,    22,    46,    34,   122,    79,   123,    21,    22,   122
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
     114,   115,   115,   116,   116,   117,   117,   117,   118,   118,
     119,   119,   120,   120,   121,   121,   122,   122,   123,   123,
     123,   123,   123,   123,   124,   125,   126,   126,   127,   127,
     127,   127,   127,   127,   127,   128,   128,   129,   129,   129,
     130,   130,   130,   130,   131,   131,   131,   131,   132,   132,
     132,   132,   132,   132,   132,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   135,   135,   135,   135,   135,
     136,   136,   137,   137,   138,   138,   139,   139,   140,   140,
     141,   141,   141,   141,   142,   142,   142,   142,   142,   142,
     142,   142,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   144,   144,   145,   146,   147,   148,
     148
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
       3,     3,     3,    10,     2,     2,     1,     3,     0,     4,
       1,     3,     0,     3,     0,     4,     0,     3,     1,     3,
       2,     2,     4,     4,     8,     2,     1,     3,     3,     3,
       3,     3,     3,     2,     1,     1,     3,     1,     3,     3,
       1,     3,     3,     2,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     6,     4,     4,     6,
       5,     6,     8,     7,     6,     7,     8,     4,     5,     6,
       5,     6,     4,     7,     8,     6,     7,     8,     6,     6,
       8,     7,     8,     7,     8,     9,    10,     6,     1,     1,
       3,     3,     4,     4,     6,     3,     5,     6,     6,     8,
       2,     4,     5,     5,     7,     1,     1,     1,     1,     1,
       0,     3,     0,     5,     0,     2,     0,     2,     0,     2,
       0,     1,     3,     3,     3,     3,     3,     3,     6,     3,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     3,     1,     2,     1,     2,     7,     2,     4,     0,
       1
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
#line 289 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 2010 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 319 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 2019 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 325 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 2027 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 330 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 2035 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 336 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 2043 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 342 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2051 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 348 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2059 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 354 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2069 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 361 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2077 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 367 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2087 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE id id_list RBRACE  */
#line 376 "yacc_sql.y"
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
#line 2112 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE id id_list RBRACE  */
#line 397 "yacc_sql.y"
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
#line 2137 "yacc_sql.cpp"
    break;

  case 34: /* id_list: %empty  */
#line 421 "yacc_sql.y"
    {
      (yyval.index_attr_list) = nullptr;
    }
#line 2145 "yacc_sql.cpp"
    break;

  case 35: /* id_list: COMMA id id_list  */
#line 425 "yacc_sql.y"
    {
      if ((yyvsp[0].index_attr_list) != nullptr) {
        (yyval.index_attr_list) = (yyvsp[0].index_attr_list);
      } else {
        (yyval.index_attr_list) = new std::vector<std::string>;
      }
      (yyval.index_attr_list)->push_back((yyvsp[-1].string));
      delete (yyvsp[-1].string);
    }
#line 2159 "yacc_sql.cpp"
    break;

  case 36: /* id: ID  */
#line 436 "yacc_sql.y"
        {

		(yyval.string) = (yyvsp[0].string);
    //free($1);
	}
#line 2169 "yacc_sql.cpp"
    break;

  case 37: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 445 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2181 "yacc_sql.cpp"
    break;

  case 38: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 455 "yacc_sql.y"
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
#line 2203 "yacc_sql.cpp"
    break;

  case 39: /* create_table_stmt: CREATE TABLE ID AS select_stmt  */
#line 473 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));

      create_table.select_infos = (yyvsp[0].sql_node);
      create_table.select_flag = true;
    }
#line 2217 "yacc_sql.cpp"
    break;

  case 40: /* attr_def_list: %empty  */
#line 485 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2225 "yacc_sql.cpp"
    break;

  case 41: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 489 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2239 "yacc_sql.cpp"
    break;

  case 42: /* attr_def: ID type LBRACE number RBRACE  */
#line 502 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      //$$->nullable = false;
      free((yyvsp[-4].string));
    }
#line 2252 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type LBRACE number RBRACE NOT NULL_T  */
#line 511 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-5].number);
      (yyval.attr_info)->name = (yyvsp[-6].string);
      (yyval.attr_info)->length = (yyvsp[-3].number);
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-6].string));
    }
#line 2265 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type LBRACE number RBRACE NULL_T  */
#line 520 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-5].string));
    }
#line 2278 "yacc_sql.cpp"
    break;

  case 45: /* attr_def: ID type NOT NULL_T  */
#line 529 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-2].number);
      (yyval.attr_info)->name = (yyvsp[-3].string);
      (yyval.attr_info)->length = 4;
      //$$->nullable = true;
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-3].string));
    }
#line 2292 "yacc_sql.cpp"
    break;

  case 46: /* attr_def: ID type NULL_T  */
#line 539 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-2].string));
    }
#line 2305 "yacc_sql.cpp"
    break;

  case 47: /* attr_def: ID TEXT  */
#line 548 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = CHARS;
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 65535;
      free((yyvsp[-1].string));
    }
#line 2317 "yacc_sql.cpp"
    break;

  case 48: /* attr_def: ID type  */
#line 556 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      //$$->nullable = false;
      free((yyvsp[-1].string));
    }
#line 2330 "yacc_sql.cpp"
    break;

  case 49: /* number: NUMBER  */
#line 566 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2336 "yacc_sql.cpp"
    break;

  case 50: /* type: INT_T  */
#line 569 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2342 "yacc_sql.cpp"
    break;

  case 51: /* type: STRING_T  */
#line 570 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2348 "yacc_sql.cpp"
    break;

  case 52: /* type: FLOAT_T  */
#line 571 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2354 "yacc_sql.cpp"
    break;

  case 53: /* type: DATE_T  */
#line 572 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2360 "yacc_sql.cpp"
    break;

  case 54: /* insert_stmt: INSERT INTO ID VALUES record record_list  */
#line 576 "yacc_sql.y"
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
#line 2376 "yacc_sql.cpp"
    break;

  case 55: /* record_list: %empty  */
#line 591 "yacc_sql.y"
    {
      (yyval.record_list) =  nullptr;
    }
#line 2384 "yacc_sql.cpp"
    break;

  case 56: /* record_list: COMMA record record_list  */
#line 594 "yacc_sql.y"
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
#line 2401 "yacc_sql.cpp"
    break;

  case 57: /* record: LBRACE value value_list RBRACE  */
#line 608 "yacc_sql.y"
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
#line 2419 "yacc_sql.cpp"
    break;

  case 58: /* value_list: %empty  */
#line 624 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2427 "yacc_sql.cpp"
    break;

  case 59: /* value_list: COMMA value value_list  */
#line 627 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2441 "yacc_sql.cpp"
    break;

  case 60: /* value: NUMBER  */
#line 638 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2450 "yacc_sql.cpp"
    break;

  case 61: /* value: NEGATIVE_NUM NUMBER_NEGA  */
#line 642 "yacc_sql.y"
                               {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
#line 2459 "yacc_sql.cpp"
    break;

  case 62: /* value: FLOAT  */
#line 646 "yacc_sql.y"
            {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2468 "yacc_sql.cpp"
    break;

  case 63: /* value: NEGATIVE_NUM FLOAT_NEGA  */
#line 650 "yacc_sql.y"
                              {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
#line 2477 "yacc_sql.cpp"
    break;

  case 64: /* value: NULL_T  */
#line 654 "yacc_sql.y"
            { //要放到SSS的前面
      //char *tmp = common::substr($1,1,strlen($1)-2);
      (yyval.value) = new Value(0);
      (yyval.value)->set_null_value();
      //free(tmp);
    }
#line 2488 "yacc_sql.cpp"
    break;

  case 65: /* value: SSS  */
#line 660 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2498 "yacc_sql.cpp"
    break;

  case 66: /* value: DATESSS  */
#line 665 "yacc_sql.y"
             {
			char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(1, tmp);
      free(tmp);
		}
#line 2508 "yacc_sql.cpp"
    break;

  case 67: /* delete_stmt: DELETE FROM ID where  */
#line 675 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2522 "yacc_sql.cpp"
    break;

  case 68: /* update_stmt: UPDATE ID SET update_option update_options where  */
#line 687 "yacc_sql.y"
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
#line 2562 "yacc_sql.cpp"
    break;

  case 69: /* update_options: %empty  */
#line 725 "yacc_sql.y"
    {
      (yyval.attr_name_a_values) = nullptr;
    }
#line 2570 "yacc_sql.cpp"
    break;

  case 70: /* update_options: COMMA update_option update_options  */
#line 728 "yacc_sql.y"
                                                     {
      if ((yyvsp[0].attr_name_a_values) != nullptr) {
        (yyval.attr_name_a_values) = (yyvsp[0].attr_name_a_values);
      } else {
        (yyval.attr_name_a_values) = new std::vector<SetVariableSqlNode>;
      }
      (yyval.attr_name_a_values)->emplace_back(*(yyvsp[-1].attr_name_value));
       delete (yyvsp[-1].attr_name_value);
		}
#line 2584 "yacc_sql.cpp"
    break;

  case 71: /* update_option: ID EQ value  */
#line 738 "yacc_sql.y"
                            {
    	(yyval.attr_name_value) = new SetVariableSqlNode();
      (yyval.attr_name_value)->value = *(yyvsp[0].value);
      (yyval.attr_name_value)->name = (yyvsp[-2].string);
      (yyval.attr_name_value)->type = 0;
      free((yyvsp[-2].string));
      free((yyvsp[0].value));
		}
#line 2597 "yacc_sql.cpp"
    break;

  case 72: /* update_option: ID EQ sub_select_stmt  */
#line 746 "yacc_sql.y"
                            {
    	(yyval.attr_name_value) = new SetVariableSqlNode();
      (yyval.attr_name_value)->query = (yyvsp[0].sub_sql_node);
      (yyval.attr_name_value)->name = (yyvsp[-2].string);
      (yyval.attr_name_value)->type = 1;
      free((yyvsp[-2].string));
		}
#line 2609 "yacc_sql.cpp"
    break;

  case 73: /* select_stmt: SELECT add_expr_list FROM rel rel_list join_list where opt_group_by having opt_order_by  */
#line 758 "yacc_sql.y"
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
#line 2659 "yacc_sql.cpp"
    break;

  case 74: /* select_stmt: SELECT add_expr_list  */
#line 804 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);

      if ((yyvsp[0].expression_list) != nullptr) {
        std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
#line 2673 "yacc_sql.cpp"
    break;

  case 75: /* rel: ID ID  */
#line 817 "yacc_sql.y"
  {
    (yyval.rel_name) = new RelName();
    (yyval.rel_name)->relation = (yyvsp[-1].string);
    (yyval.rel_name)->alias = (yyvsp[0].string);
    free((yyvsp[-1].string));
    free((yyvsp[0].string));
  }
#line 2685 "yacc_sql.cpp"
    break;

  case 76: /* rel: ID  */
#line 825 "yacc_sql.y"
  {
    (yyval.rel_name) = new RelName();
    (yyval.rel_name)->relation = (yyvsp[0].string);
    free((yyvsp[0].string));
  }
#line 2695 "yacc_sql.cpp"
    break;

  case 77: /* rel: ID AS ID  */
#line 831 "yacc_sql.y"
  {
    (yyval.rel_name) = new RelName();
    (yyval.rel_name)->relation = (yyvsp[-2].string);
    (yyval.rel_name)->alias = (yyvsp[0].string);
    free((yyvsp[-2].string));
    free((yyvsp[0].string));
  }
#line 2707 "yacc_sql.cpp"
    break;

  case 78: /* opt_group_by: %empty  */
#line 841 "yacc_sql.y"
  {
    (yyval.rel_attr_list) = nullptr;
  }
#line 2715 "yacc_sql.cpp"
    break;

  case 79: /* opt_group_by: GROUP BY group_by group_by_list  */
#line 844 "yacc_sql.y"
                                    {
    if ((yyvsp[0].rel_attr_list) != nullptr) {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
    } else {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
    }
    (yyval.rel_attr_list)->push_back(*(yyvsp[-1].rel_attr));
    free((yyvsp[-1].rel_attr));
  }
#line 2729 "yacc_sql.cpp"
    break;

  case 80: /* group_by: ID  */
#line 856 "yacc_sql.y"
  {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
    free((yyvsp[0].string));
  }
#line 2739 "yacc_sql.cpp"
    break;

  case 81: /* group_by: ID DOT ID  */
#line 862 "yacc_sql.y"
  {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
    (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
    free((yyvsp[-2].string));
    free((yyvsp[0].string));
  }
#line 2751 "yacc_sql.cpp"
    break;

  case 82: /* group_by_list: %empty  */
#line 872 "yacc_sql.y"
  {
    (yyval.rel_attr_list) = nullptr;
  }
#line 2759 "yacc_sql.cpp"
    break;

  case 83: /* group_by_list: COMMA group_by group_by_list  */
#line 875 "yacc_sql.y"
                                 {
    if ((yyvsp[0].rel_attr_list) != nullptr) {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
    } else {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
    }
    (yyval.rel_attr_list)->push_back(*(yyvsp[-1].rel_attr));
    free((yyvsp[-1].rel_attr));
  }
#line 2773 "yacc_sql.cpp"
    break;

  case 84: /* opt_order_by: %empty  */
#line 887 "yacc_sql.y"
    {
      (yyval.order_by) = nullptr;
    }
#line 2781 "yacc_sql.cpp"
    break;

  case 85: /* opt_order_by: ORDER BY order_by_unit order_by_list  */
#line 890 "yacc_sql.y"
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
#line 2797 "yacc_sql.cpp"
    break;

  case 86: /* order_by_list: %empty  */
#line 903 "yacc_sql.y"
    {
      (yyval.order_by) = nullptr;
    }
#line 2805 "yacc_sql.cpp"
    break;

  case 87: /* order_by_list: COMMA order_by_unit order_by_list  */
#line 907 "yacc_sql.y"
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
#line 2820 "yacc_sql.cpp"
    break;

  case 88: /* order_by_unit: ID  */
#line 920 "yacc_sql.y"
        {
      (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[0].string);
      //$$->order_relation = NULL;
	}
#line 2830 "yacc_sql.cpp"
    break;

  case 89: /* order_by_unit: ID DOT ID  */
#line 927 "yacc_sql.y"
        {
		  (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[0].string);
      (yyval.order_by_node)->order_relation = (yyvsp[-2].string);
	}
#line 2840 "yacc_sql.cpp"
    break;

  case 90: /* order_by_unit: ID DESC  */
#line 934 "yacc_sql.y"
        {
      (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[-1].string);
      //$$->order_relation = NULL;
      (yyval.order_by_node)->asc_type = false;
	}
#line 2851 "yacc_sql.cpp"
    break;

  case 91: /* order_by_unit: ID ASC  */
#line 942 "yacc_sql.y"
        {
      (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[-1].string);
      //$$->order_relation = NULL;
	}
#line 2861 "yacc_sql.cpp"
    break;

  case 92: /* order_by_unit: ID DOT ID DESC  */
#line 949 "yacc_sql.y"
        {
      (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[-1].string);
      (yyval.order_by_node)->order_relation = (yyvsp[-3].string);
      (yyval.order_by_node)->asc_type = false;
	}
#line 2872 "yacc_sql.cpp"
    break;

  case 93: /* order_by_unit: ID DOT ID ASC  */
#line 957 "yacc_sql.y"
        {
		  (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[-1].string);
      (yyval.order_by_node)->order_relation = (yyvsp[-3].string);
	}
#line 2882 "yacc_sql.cpp"
    break;

  case 94: /* sub_select_stmt: LBRACE SELECT add_expr_list FROM rel rel_list where RBRACE  */
#line 966 "yacc_sql.y"
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
#line 2907 "yacc_sql.cpp"
    break;

  case 95: /* calc_stmt: CALC expression_list  */
#line 990 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2918 "yacc_sql.cpp"
    break;

  case 96: /* expression_list: expression  */
#line 1000 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2927 "yacc_sql.cpp"
    break;

  case 97: /* expression_list: expression COMMA expression_list  */
#line 1005 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2940 "yacc_sql.cpp"
    break;

  case 98: /* expression: expression '+' expression  */
#line 1015 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2948 "yacc_sql.cpp"
    break;

  case 99: /* expression: expression MINUS expression  */
#line 1018 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2956 "yacc_sql.cpp"
    break;

  case 100: /* expression: expression '*' expression  */
#line 1021 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2964 "yacc_sql.cpp"
    break;

  case 101: /* expression: expression '/' expression  */
#line 1024 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2972 "yacc_sql.cpp"
    break;

  case 102: /* expression: LBRACE expression RBRACE  */
#line 1027 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2981 "yacc_sql.cpp"
    break;

  case 103: /* expression: NEGATIVE_NUM expression  */
#line 1031 "yacc_sql.y"
                                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2989 "yacc_sql.cpp"
    break;

  case 104: /* expression: value2  */
#line 1034 "yacc_sql.y"
             {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2999 "yacc_sql.cpp"
    break;

  case 105: /* add_expr_list: add_expr  */
#line 1042 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 3008 "yacc_sql.cpp"
    break;

  case 106: /* add_expr_list: add_expr COMMA add_expr_list  */
#line 1047 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 3021 "yacc_sql.cpp"
    break;

  case 107: /* add_expr: mul_expr  */
#line 1057 "yacc_sql.y"
            {

    }
#line 3029 "yacc_sql.cpp"
    break;

  case 108: /* add_expr: add_expr '+' mul_expr  */
#line 1060 "yacc_sql.y"
                            {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3037 "yacc_sql.cpp"
    break;

  case 109: /* add_expr: add_expr MINUS mul_expr  */
#line 1063 "yacc_sql.y"
                              {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3045 "yacc_sql.cpp"
    break;

  case 110: /* mul_expr: base_expr  */
#line 1068 "yacc_sql.y"
             {

    }
#line 3053 "yacc_sql.cpp"
    break;

  case 111: /* mul_expr: mul_expr '*' base_expr  */
#line 1071 "yacc_sql.y"
                             {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3061 "yacc_sql.cpp"
    break;

  case 112: /* mul_expr: mul_expr '/' base_expr  */
#line 1074 "yacc_sql.y"
                             {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3069 "yacc_sql.cpp"
    break;

  case 113: /* mul_expr: NEGATIVE_NUM base_expr  */
#line 1077 "yacc_sql.y"
                             {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3077 "yacc_sql.cpp"
    break;

  case 114: /* base_expr: LBRACE add_expr RBRACE  */
#line 1082 "yacc_sql.y"
                           {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3086 "yacc_sql.cpp"
    break;

  case 115: /* base_expr: value2  */
#line 1086 "yacc_sql.y"
             {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 3096 "yacc_sql.cpp"
    break;

  case 116: /* base_expr: cal_attr  */
#line 1091 "yacc_sql.y"
               {
      std::string table = (yyvsp[0].rel_attr)->relation_name;
      std::string attribute = (yyvsp[0].rel_attr)->attribute_name;
      std::string alias = (yyvsp[0].rel_attr)->alias;
      AggrOp aggr = (yyvsp[0].rel_attr)->aggr_func;
      (yyval.expression) = new FieldExpr(table, attribute, aggr,alias);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 3110 "yacc_sql.cpp"
    break;

  case 117: /* base_expr: function_attr  */
#line 1100 "yacc_sql.y"
                    {

    }
#line 3118 "yacc_sql.cpp"
    break;

  case 118: /* value2: NUMBER  */
#line 1105 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 3127 "yacc_sql.cpp"
    break;

  case 119: /* value2: FLOAT  */
#line 1109 "yacc_sql.y"
            {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 3136 "yacc_sql.cpp"
    break;

  case 120: /* value2: NUMBER_NEGA  */
#line 1113 "yacc_sql.y"
                  {
      int temp = (int)(yyvsp[0].number);
      temp *= (-1);
      (yyval.value) = new Value(temp);
      (yyloc) = (yylsp[0]);
    }
#line 3147 "yacc_sql.cpp"
    break;

  case 121: /* value2: FLOAT_NEGA  */
#line 1119 "yacc_sql.y"
                 {
      float temp = (float)(yyvsp[0].floats);
      temp *= (-1.0);
      (yyval.value) = new Value(temp);
      (yyloc) = (yylsp[0]);
    }
#line 3158 "yacc_sql.cpp"
    break;

  case 122: /* value2: NULL_T  */
#line 1125 "yacc_sql.y"
            { //要放到SSS的前面
      //char *tmp = common::substr($1,1,strlen($1)-2);
      (yyval.value) = new Value(0);
      (yyval.value)->set_null_value();
      //free(tmp);
    }
#line 3169 "yacc_sql.cpp"
    break;

  case 123: /* value2: SSS  */
#line 1131 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 3179 "yacc_sql.cpp"
    break;

  case 124: /* value2: DATESSS  */
#line 1136 "yacc_sql.y"
             {
			char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(1, tmp);
      free(tmp);
		}
#line 3189 "yacc_sql.cpp"
    break;

  case 125: /* function_attr: LENGTH LBRACE value RBRACE ID  */
#line 1144 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-2].value));
      (yyval.expression) = create_func_expression_alias(LENGTHS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
      free((yyvsp[0].string));
    }
#line 3199 "yacc_sql.cpp"
    break;

  case 126: /* function_attr: LENGTH LBRACE value RBRACE AS ID  */
#line 1151 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-3].value));
      (yyval.expression) = create_func_expression_alias(LENGTHS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
      free((yyvsp[0].string));
    }
#line 3209 "yacc_sql.cpp"
    break;

  case 127: /* function_attr: LENGTH LBRACE value RBRACE  */
#line 1158 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-1].value));
      (yyval.expression) = create_func_expression(LENGTHS, temp, nullptr, sql_string, &(yyloc));
    }
#line 3218 "yacc_sql.cpp"
    break;

  case 128: /* function_attr: LENGTH LBRACE ID RBRACE  */
#line 1164 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-1].string));
      (yyval.expression) = create_func_expression(LENGTHS, temp, nullptr, sql_string, &(yyloc));
    }
#line 3227 "yacc_sql.cpp"
    break;

  case 129: /* function_attr: LENGTH LBRACE ID RBRACE AS ID  */
#line 1170 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-3].string));
      //$$ = create_func_expression(LENGTHS, temp, nullptr, sql_string, &@$);
      (yyval.expression) =create_func_expression_alias(LENGTHS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
    }
#line 3237 "yacc_sql.cpp"
    break;

  case 130: /* function_attr: LENGTH LBRACE ID RBRACE ID  */
#line 1177 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-2].string));
      //$$ = create_func_expression(LENGTHS, temp, nullptr, sql_string, &@$);
      (yyval.expression) =create_func_expression_alias(LENGTHS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
    }
#line 3247 "yacc_sql.cpp"
    break;

  case 131: /* function_attr: LENGTH LBRACE ID DOT ID RBRACE  */
#line 1185 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-3].string),(yyvsp[-1].string));
      (yyval.expression) = create_func_expression(LENGTHS, temp, nullptr, sql_string, &(yyloc));
    }
#line 3256 "yacc_sql.cpp"
    break;

  case 132: /* function_attr: LENGTH LBRACE ID DOT ID RBRACE AS ID  */
#line 1191 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-5].string),(yyvsp[-3].string));
      //$$ = create_func_expression(LENGTHS, temp, nullptr, sql_string, &@$);
      (yyval.expression) =create_func_expression_alias(LENGTHS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
    }
#line 3266 "yacc_sql.cpp"
    break;

  case 133: /* function_attr: LENGTH LBRACE ID DOT ID RBRACE ID  */
#line 1198 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-4].string),(yyvsp[-2].string));
      //$$ = create_func_expression(LENGTHS, temp, nullptr, sql_string, &@$);
      (yyval.expression) =create_func_expression_alias(LENGTHS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
    }
#line 3276 "yacc_sql.cpp"
    break;

  case 134: /* function_attr: ROUND LBRACE ID DOT ID RBRACE  */
#line 1206 "yacc_sql.y"
    {
     FieldExpr *temp = new FieldExpr((yyvsp[-3].string),(yyvsp[-1].string));
      (yyval.expression) = create_func_expression(ROUNDS, temp, nullptr, sql_string, &(yyloc));
    }
#line 3285 "yacc_sql.cpp"
    break;

  case 135: /* function_attr: ROUND LBRACE ID DOT ID RBRACE ID  */
#line 1212 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-4].string),(yyvsp[-2].string));
      //$$ = create_func_expression(ROUNDS, temp, nullptr, sql_string, &@$);
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
    }
#line 3295 "yacc_sql.cpp"
    break;

  case 136: /* function_attr: ROUND LBRACE ID DOT ID RBRACE AS ID  */
#line 1219 "yacc_sql.y"
    {
     FieldExpr *temp = new FieldExpr((yyvsp[-5].string),(yyvsp[-3].string));
      //$$ = create_func_expression(ROUNDS, temp, nullptr, sql_string, &@$);
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
      free((yyvsp[0].string));
    }
#line 3306 "yacc_sql.cpp"
    break;

  case 137: /* function_attr: ROUND LBRACE ID RBRACE  */
#line 1227 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-1].string));
      (yyval.expression) = create_func_expression(ROUNDS, temp, nullptr, sql_string, &(yyloc));
    }
#line 3315 "yacc_sql.cpp"
    break;

  case 138: /* function_attr: ROUND LBRACE ID RBRACE ID  */
#line 1233 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-2].string));
      //$$ = create_func_expression(ROUNDS, temp, nullptr, sql_string, &@$);
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
    }
#line 3325 "yacc_sql.cpp"
    break;

  case 139: /* function_attr: ROUND LBRACE ID RBRACE AS ID  */
#line 1240 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-3].string));
      //$$ = create_func_expression(ROUNDS, temp, nullptr, sql_string, &@$);
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
      free((yyvsp[0].string));
    }
#line 3336 "yacc_sql.cpp"
    break;

  case 140: /* function_attr: ROUND LBRACE value RBRACE ID  */
#line 1248 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-2].value));
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
      free((yyvsp[0].string));
    }
#line 3346 "yacc_sql.cpp"
    break;

  case 141: /* function_attr: ROUND LBRACE value RBRACE AS ID  */
#line 1255 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-3].value));
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
      free((yyvsp[0].string));
    }
#line 3356 "yacc_sql.cpp"
    break;

  case 142: /* function_attr: ROUND LBRACE value RBRACE  */
#line 1262 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-1].value));
      (yyval.expression) = create_func_expression(ROUNDS, temp, nullptr, sql_string, &(yyloc));
    }
#line 3365 "yacc_sql.cpp"
    break;

  case 143: /* function_attr: ROUND LBRACE value COMMA value RBRACE ID  */
#line 1268 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-4].value));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-2].value));
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3377 "yacc_sql.cpp"
    break;

  case 144: /* function_attr: ROUND LBRACE value COMMA value RBRACE AS ID  */
#line 1277 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-5].value));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-3].value));
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3389 "yacc_sql.cpp"
    break;

  case 145: /* function_attr: ROUND LBRACE value COMMA value RBRACE  */
#line 1286 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-3].value));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-1].value));
      (yyval.expression) = create_func_expression(ROUNDS, temp, temp2, sql_string, &(yyloc));
    }
#line 3399 "yacc_sql.cpp"
    break;

  case 146: /* function_attr: ROUND LBRACE ID COMMA value RBRACE ID  */
#line 1294 "yacc_sql.y"
    {
      //ValueExpr *temp = new ValueExpr(*$3);
      FieldExpr *temp = new FieldExpr((yyvsp[-4].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-2].value));
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3412 "yacc_sql.cpp"
    break;

  case 147: /* function_attr: ROUND LBRACE ID COMMA value RBRACE AS ID  */
#line 1304 "yacc_sql.y"
    {
      //ValueExpr *temp = new ValueExpr(*$3);
      FieldExpr *temp = new FieldExpr((yyvsp[-5].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-3].value));
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3425 "yacc_sql.cpp"
    break;

  case 148: /* function_attr: ROUND LBRACE ID COMMA value RBRACE  */
#line 1314 "yacc_sql.y"
    {
      //ValueExpr *temp = new ValueExpr(*$3);
      FieldExpr *temp = new FieldExpr((yyvsp[-3].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-1].value));
      (yyval.expression) = create_func_expression(ROUNDS, temp, temp2, sql_string, &(yyloc));
    }
#line 3436 "yacc_sql.cpp"
    break;

  case 149: /* function_attr: DATE_FORMAT LBRACE ID COMMA value RBRACE  */
#line 1322 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-3].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-1].value));
      (yyval.expression) = create_func_expression(DATE_FORMATS, temp, temp2, sql_string, &(yyloc));
    }
#line 3446 "yacc_sql.cpp"
    break;

  case 150: /* function_attr: DATE_FORMAT LBRACE ID DOT ID COMMA value RBRACE  */
#line 1329 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-5].string),(yyvsp[-3].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-1].value));
      (yyval.expression) = create_func_expression(DATE_FORMATS, temp, temp2, sql_string, &(yyloc));
    }
#line 3456 "yacc_sql.cpp"
    break;

  case 151: /* function_attr: DATE_FORMAT LBRACE value COMMA value RBRACE ID  */
#line 1336 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-4].value));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-2].value));
      (yyval.expression) = create_func_expression_alias(DATE_FORMATS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3468 "yacc_sql.cpp"
    break;

  case 152: /* function_attr: DATE_FORMAT LBRACE value COMMA value RBRACE AS ID  */
#line 1345 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-5].value));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-3].value));
      (yyval.expression) = create_func_expression_alias(DATE_FORMATS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3480 "yacc_sql.cpp"
    break;

  case 153: /* function_attr: DATE_FORMAT LBRACE ID COMMA value RBRACE ID  */
#line 1355 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-4].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-2].value));
      (yyval.expression) = create_func_expression_alias(DATE_FORMATS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3492 "yacc_sql.cpp"
    break;

  case 154: /* function_attr: DATE_FORMAT LBRACE ID COMMA value RBRACE AS ID  */
#line 1364 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-5].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-3].value));
      (yyval.expression) = create_func_expression_alias(DATE_FORMATS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3504 "yacc_sql.cpp"
    break;

  case 155: /* function_attr: DATE_FORMAT LBRACE ID DOT ID COMMA value RBRACE ID  */
#line 1373 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-6].string),(yyvsp[-4].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-2].value));
      (yyval.expression) = create_func_expression_alias(DATE_FORMATS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[-2].value));
    }
#line 3516 "yacc_sql.cpp"
    break;

  case 156: /* function_attr: DATE_FORMAT LBRACE ID DOT ID COMMA value RBRACE AS ID  */
#line 1382 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-7].string),(yyvsp[-5].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-3].value));
      (yyval.expression) = create_func_expression_alias(DATE_FORMATS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3528 "yacc_sql.cpp"
    break;

  case 157: /* function_attr: DATE_FORMAT LBRACE value COMMA value RBRACE  */
#line 1391 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-3].value));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-1].value));
      (yyval.expression) = create_func_expression(DATE_FORMATS, temp, temp2, sql_string, &(yyloc));
    }
#line 3538 "yacc_sql.cpp"
    break;

  case 158: /* cal_attr: '*'  */
#line 1399 "yacc_sql.y"
        {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = "";
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyloc) = (yylsp[0]);
    }
#line 3550 "yacc_sql.cpp"
    break;

  case 159: /* cal_attr: ID  */
#line 1406 "yacc_sql.y"
         {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyloc) = (yylsp[0]);
      free((yyvsp[0].string));
    }
#line 3562 "yacc_sql.cpp"
    break;

  case 160: /* cal_attr: ID DOT '*'  */
#line 1413 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyloc) = (yylsp[-2]);
      free((yyvsp[-2].string));
      
    }
#line 3576 "yacc_sql.cpp"
    break;

  case 161: /* cal_attr: ID DOT ID  */
#line 1422 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyloc) = (yylsp[-2]);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3590 "yacc_sql.cpp"
    break;

  case 162: /* cal_attr: aggr_func LBRACE '*' RBRACE  */
#line 1431 "yacc_sql.y"
                                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggr_func = (yyvsp[-3].aggr);
      (yyloc) = (yylsp[-3]);
    }
#line 3601 "yacc_sql.cpp"
    break;

  case 163: /* cal_attr: aggr_func LBRACE ID RBRACE  */
#line 1437 "yacc_sql.y"
                                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-3].aggr);
      (yyloc) = (yylsp[-3]);
      free((yyvsp[-1].string));
    }
#line 3613 "yacc_sql.cpp"
    break;

  case 164: /* cal_attr: aggr_func LBRACE ID DOT ID RBRACE  */
#line 1444 "yacc_sql.y"
                                       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-5].aggr);
      (yyloc) = (yylsp[-5]);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 3627 "yacc_sql.cpp"
    break;

  case 165: /* cal_attr: ID AS ID  */
#line 1453 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[0].string));
      free((yyvsp[-2].string));
    }
#line 3640 "yacc_sql.cpp"
    break;

  case 166: /* cal_attr: ID DOT ID AS ID  */
#line 1461 "yacc_sql.y"
                      {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-4].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3655 "yacc_sql.cpp"
    break;

  case 167: /* cal_attr: aggr_func LBRACE '*' RBRACE AS ID  */
#line 1471 "yacc_sql.y"
                                        {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggr_func = (yyvsp[-5].aggr);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3667 "yacc_sql.cpp"
    break;

  case 168: /* cal_attr: aggr_func LBRACE ID RBRACE AS ID  */
#line 1478 "yacc_sql.y"
                                      {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-3].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-5].aggr);
       (yyval.rel_attr)->alias = (yyvsp[0].string);
       free((yyvsp[0].string));
      free((yyvsp[-3].string));
    }
#line 3680 "yacc_sql.cpp"
    break;

  case 169: /* cal_attr: aggr_func LBRACE ID DOT ID RBRACE AS ID  */
#line 1486 "yacc_sql.y"
                                             {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-5].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-3].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-7].aggr);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[0].string));
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 3695 "yacc_sql.cpp"
    break;

  case 170: /* cal_attr: ID ID  */
#line 1496 "yacc_sql.y"
             { //不加AS也可以
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[0].string));
      free((yyvsp[-1].string));
    }
#line 3708 "yacc_sql.cpp"
    break;

  case 171: /* cal_attr: ID DOT ID ID  */
#line 1504 "yacc_sql.y"
                   {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3723 "yacc_sql.cpp"
    break;

  case 172: /* cal_attr: aggr_func LBRACE '*' RBRACE ID  */
#line 1514 "yacc_sql.y"
                                     {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggr_func = (yyvsp[-4].aggr);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3735 "yacc_sql.cpp"
    break;

  case 173: /* cal_attr: aggr_func LBRACE ID RBRACE ID  */
#line 1521 "yacc_sql.y"
                                   {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-4].aggr);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
       
       free((yyvsp[0].string));
      free((yyvsp[-2].string));
    }
#line 3749 "yacc_sql.cpp"
    break;

  case 174: /* cal_attr: aggr_func LBRACE ID DOT ID RBRACE ID  */
#line 1530 "yacc_sql.y"
                                          {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-4].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-6].aggr);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[0].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 3764 "yacc_sql.cpp"
    break;

  case 175: /* aggr_func: MAX  */
#line 1543 "yacc_sql.y"
        { (yyval.aggr)=MAXF; }
#line 3770 "yacc_sql.cpp"
    break;

  case 176: /* aggr_func: MIN  */
#line 1544 "yacc_sql.y"
                { (yyval.aggr)=MINF; }
#line 3776 "yacc_sql.cpp"
    break;

  case 177: /* aggr_func: COUNT  */
#line 1545 "yacc_sql.y"
                  { (yyval.aggr)=COUNTF; }
#line 3782 "yacc_sql.cpp"
    break;

  case 178: /* aggr_func: AVG  */
#line 1546 "yacc_sql.y"
                { (yyval.aggr)=AVGF; }
#line 3788 "yacc_sql.cpp"
    break;

  case 179: /* aggr_func: SUM  */
#line 1547 "yacc_sql.y"
                { (yyval.aggr)=SUMF; }
#line 3794 "yacc_sql.cpp"
    break;

  case 180: /* rel_list: %empty  */
#line 1551 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 3802 "yacc_sql.cpp"
    break;

  case 181: /* rel_list: COMMA rel rel_list  */
#line 1554 "yacc_sql.y"
                         {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<RelName>;
      }

      (yyval.relation_list)->push_back(*(yyvsp[-1].rel_name));//本来是字符串char* 所以这里要加*
      free((yyvsp[-1].rel_name));
    }
#line 3817 "yacc_sql.cpp"
    break;

  case 182: /* join_list: %empty  */
#line 1567 "yacc_sql.y"
    {
      (yyval.join_lists) = nullptr;
    }
#line 3825 "yacc_sql.cpp"
    break;

  case 183: /* join_list: INNER JOIN rel on join_list  */
#line 1570 "yacc_sql.y"
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
#line 3844 "yacc_sql.cpp"
    break;

  case 184: /* on: %empty  */
#line 1587 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3852 "yacc_sql.cpp"
    break;

  case 185: /* on: ON condition_list  */
#line 1590 "yacc_sql.y"
                        {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3860 "yacc_sql.cpp"
    break;

  case 186: /* having: %empty  */
#line 1596 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3868 "yacc_sql.cpp"
    break;

  case 187: /* having: HAVING condition_list  */
#line 1599 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3876 "yacc_sql.cpp"
    break;

  case 188: /* where: %empty  */
#line 1605 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3884 "yacc_sql.cpp"
    break;

  case 189: /* where: WHERE condition_list  */
#line 1608 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3892 "yacc_sql.cpp"
    break;

  case 190: /* condition_list: %empty  */
#line 1614 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3900 "yacc_sql.cpp"
    break;

  case 191: /* condition_list: condition  */
#line 1617 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3910 "yacc_sql.cpp"
    break;

  case 192: /* condition_list: condition AND condition_list  */
#line 1622 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->conjunction = 0;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3921 "yacc_sql.cpp"
    break;

  case 193: /* condition_list: condition OR condition_list  */
#line 1628 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->conjunction = 1;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3932 "yacc_sql.cpp"
    break;

  case 194: /* condition: add_expr cal_comp_op add_expr  */
#line 1637 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3945 "yacc_sql.cpp"
    break;

  case 195: /* condition: sub_select_stmt cal_comp_op sub_select_stmt  */
#line 1646 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_sql = (yyvsp[-2].sub_sql_node);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_sql = (yyvsp[0].sub_sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3958 "yacc_sql.cpp"
    break;

  case 196: /* condition: add_expr cal_comp_op sub_select_stmt  */
#line 1655 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_sql = (yyvsp[0].sub_sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3971 "yacc_sql.cpp"
    break;

  case 197: /* condition: sub_select_stmt cal_comp_op add_expr  */
#line 1664 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_sql = (yyvsp[-2].sub_sql_node);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3984 "yacc_sql.cpp"
    break;

  case 198: /* condition: add_expr logical_comp_op LBRACE value value_list RBRACE  */
#line 1673 "yacc_sql.y"
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
#line 4001 "yacc_sql.cpp"
    break;

  case 199: /* condition: add_expr logical_comp_op sub_select_stmt  */
#line 1686 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_sql = (yyvsp[0].sub_sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 4014 "yacc_sql.cpp"
    break;

  case 200: /* condition: cal_comp_op sub_select_stmt  */
#line 1696 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = -1;
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_sql = (yyvsp[0].sub_sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 4026 "yacc_sql.cpp"
    break;

  case 201: /* condition: add_expr cal_comp_op  */
#line 1705 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_expr = (yyvsp[-1].expression);
      (yyval.condition)->right_is_attr = -1;
      (yyval.condition)->comp = (yyvsp[0].comp);
    }
#line 4038 "yacc_sql.cpp"
    break;

  case 202: /* cal_comp_op: EQ  */
#line 1715 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 4044 "yacc_sql.cpp"
    break;

  case 203: /* cal_comp_op: LT  */
#line 1716 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 4050 "yacc_sql.cpp"
    break;

  case 204: /* cal_comp_op: GT  */
#line 1717 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 4056 "yacc_sql.cpp"
    break;

  case 205: /* cal_comp_op: LE  */
#line 1718 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 4062 "yacc_sql.cpp"
    break;

  case 206: /* cal_comp_op: GE  */
#line 1719 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 4068 "yacc_sql.cpp"
    break;

  case 207: /* cal_comp_op: NE  */
#line 1720 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 4074 "yacc_sql.cpp"
    break;

  case 208: /* cal_comp_op: LIKE  */
#line 1721 "yacc_sql.y"
           { (yyval.comp) = REGEX_LIKE; }
#line 4080 "yacc_sql.cpp"
    break;

  case 209: /* cal_comp_op: NOT LIKE  */
#line 1722 "yacc_sql.y"
               { (yyval.comp) = REGEX_NOT_LIKE; }
#line 4086 "yacc_sql.cpp"
    break;

  case 210: /* cal_comp_op: IS NULL_T  */
#line 1723 "yacc_sql.y"
               { (yyval.comp) = IS_NULL; }
#line 4092 "yacc_sql.cpp"
    break;

  case 211: /* cal_comp_op: IS NOT NULL_T  */
#line 1724 "yacc_sql.y"
                   { (yyval.comp) = IS_NOT_NULL; }
#line 4098 "yacc_sql.cpp"
    break;

  case 212: /* cal_comp_op: EXISTS  */
#line 1725 "yacc_sql.y"
             { (yyval.comp) = EXISTS_QUERY; }
#line 4104 "yacc_sql.cpp"
    break;

  case 213: /* cal_comp_op: NOT EXISTS  */
#line 1726 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS_QUERY; }
#line 4110 "yacc_sql.cpp"
    break;

  case 214: /* logical_comp_op: IN  */
#line 1729 "yacc_sql.y"
         { (yyval.comp) = IN_QUERY; }
#line 4116 "yacc_sql.cpp"
    break;

  case 215: /* logical_comp_op: NOT IN  */
#line 1730 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_QUERY; }
#line 4122 "yacc_sql.cpp"
    break;

  case 216: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1734 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 4136 "yacc_sql.cpp"
    break;

  case 217: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1747 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 4145 "yacc_sql.cpp"
    break;

  case 218: /* set_variable_stmt: SET ID EQ value  */
#line 1755 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 4157 "yacc_sql.cpp"
    break;


#line 4161 "yacc_sql.cpp"

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

#line 1767 "yacc_sql.y"

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
