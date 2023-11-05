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
#define YYLAST   498

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  221
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  404

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
     491,   504,   507,   520,   529,   538,   547,   557,   566,   574,
     585,   588,   589,   590,   591,   594,   610,   613,   627,   643,
     646,   657,   661,   665,   669,   673,   679,   684,   693,   705,
     744,   747,   757,   765,   776,   786,   836,   844,   850,   861,
     864,   875,   881,   892,   895,   907,   910,   923,   926,   939,
     946,   953,   961,   968,   976,   985,  1009,  1019,  1024,  1035,
    1038,  1041,  1044,  1047,  1051,  1054,  1061,  1066,  1077,  1080,
    1083,  1088,  1091,  1094,  1097,  1102,  1106,  1111,  1120,  1125,
    1129,  1133,  1139,  1145,  1151,  1156,  1163,  1170,  1177,  1183,
    1189,  1195,  1202,  1210,  1217,  1225,  1232,  1240,  1246,  1252,
    1259,  1267,  1274,  1281,  1287,  1296,  1305,  1313,  1323,  1331,
    1342,  1349,  1356,  1365,  1375,  1384,  1393,  1402,  1411,  1419,
    1426,  1433,  1442,  1451,  1457,  1464,  1473,  1481,  1491,  1498,
    1506,  1516,  1524,  1534,  1541,  1550,  1563,  1564,  1565,  1566,
    1567,  1571,  1574,  1587,  1590,  1607,  1610,  1616,  1619,  1625,
    1628,  1634,  1637,  1642,  1648,  1656,  1665,  1674,  1683,  1692,
    1705,  1715,  1724,  1735,  1736,  1737,  1738,  1739,  1740,  1741,
    1742,  1743,  1744,  1745,  1746,  1749,  1750,  1753,  1766,  1774,
    1784,  1785
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

#define YYPACT_NINF (-309)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     423,    14,   165,    45,   238,   -41,    31,  -309,    64,    79,
      54,  -309,  -309,  -309,  -309,  -309,    72,   141,   423,   172,
     176,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,   109,   140,   225,   164,   168,    45,    45,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,    10,  -309,   313,   212,
     220,   221,   238,  -309,  -309,  -309,  -309,  -309,   -10,  -309,
      27,    25,   -29,  -309,  -309,  -309,  -309,   223,  -309,  -309,
     177,   180,   198,   193,   196,  -309,  -309,  -309,  -309,     8,
     201,   187,  -309,   208,  -309,    35,    45,    45,    45,    45,
      45,  -309,    55,   188,   271,    17,   195,   -46,  -309,  -309,
     197,   238,   238,   238,   313,   313,    61,   224,   228,   202,
     334,   200,   254,   203,   214,   231,   229,  -309,   110,  -309,
     110,  -309,  -309,    74,  -309,  -309,  -309,    15,  -309,  -309,
     242,   113,   167,   103,   266,  -309,  -309,    -6,  -309,    -5,
     277,   -29,  -309,   -29,  -309,  -309,   122,   287,   294,   152,
    -309,   259,   295,  -309,   281,  -309,   135,   296,   301,   256,
    -309,  -309,  -309,    36,   257,    62,    63,   334,   265,    75,
     334,   334,   268,   334,   270,  -309,   275,  -309,   197,   310,
      77,   286,    92,   334,   332,   102,   226,   -40,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,   361,    16,  -309,     3,
     344,   302,   202,   228,   363,  -309,  -309,  -309,  -309,  -309,
       9,   203,   347,   305,   349,   307,  -309,   354,   316,  -309,
     318,  -309,   365,   367,   323,  -309,   370,   373,   374,   377,
    -309,  -309,   277,   359,   228,   328,  -309,   380,   340,  -309,
     389,   294,  -309,  -309,   375,   238,  -309,  -309,   280,  -309,
       6,   280,   392,   152,   152,   406,  -309,  -309,  -309,   295,
    -309,   348,   353,  -309,   387,   296,    23,  -309,   405,   305,
    -309,    94,  -309,  -309,   104,   107,  -309,   111,   118,   334,
     119,  -309,   197,   416,  -309,   123,  -309,   334,   410,   332,
    -309,   396,  -309,    18,  -309,  -309,    18,   324,  -309,  -309,
    -309,  -309,  -309,  -309,   413,  -309,  -309,  -309,   254,   305,
     414,   405,   369,  -309,   376,  -309,   378,  -309,   379,  -309,
     383,  -309,   430,   385,  -309,   386,   431,   439,   390,  -309,
     389,  -309,  -309,   197,   389,   114,  -309,   405,  -309,   433,
    -309,  -309,  -309,  -309,  -309,   125,  -309,   152,   310,   391,
     152,   448,  -309,  -309,   277,   440,  -309,   421,  -309,  -309,
     395,  -309,  -309,  -309,   429,   442,  -309,   452,  -309,   228,
    -309,  -309,  -309,   399,   391,  -309,   400,   447,  -309,   442,
      24,   449,  -309,  -309,  -309,  -309,   402,   400,  -309,   194,
     449,  -309,  -309,  -309
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     220,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,     0,   123,   119,
     121,   120,   122,   124,   125,    96,    97,   105,     0,     0,
       0,     0,     0,   176,   177,   180,   179,   178,   160,   159,
       0,   106,   108,   111,   116,   118,   117,     0,    31,    30,
       0,     0,     0,     0,     0,   218,     1,   221,     2,     0,
       0,     0,    29,     0,   104,     0,     0,     0,     0,     0,
       0,   114,     0,     0,     0,     0,     0,     0,   171,    74,
       0,     0,     0,     0,     0,     0,     0,     0,   189,     0,
       0,     0,     0,     0,     0,     0,     0,   103,   100,    98,
      99,   101,   102,     0,    65,    61,    63,     0,    66,    67,
       0,     0,     0,     0,     0,   115,   166,   162,   161,    77,
     181,   110,   107,   109,   112,   113,     0,     0,     0,   191,
      68,     0,    70,   219,     0,    40,     0,    41,     0,     0,
      37,    62,    64,   129,     0,   128,   137,     0,     0,   143,
       0,     0,     0,     0,     0,   172,     0,    76,     0,   183,
     164,     0,   163,     0,    56,     0,     0,     0,   209,   203,
     204,   205,   206,   207,   208,   213,     0,     0,   190,   192,
       0,     0,     0,   189,     0,    51,    52,    54,    53,    48,
      49,     0,     0,     0,     0,     0,   132,     0,     0,   126,
       0,   139,     0,     0,     0,   141,     0,     0,     0,     0,
     167,    78,   181,     0,   189,     0,   174,     0,     0,   173,
      59,     0,    55,   211,     0,     0,   210,   214,     0,   215,
       0,   202,     0,   191,   191,     0,   201,    72,    73,    70,
      69,     0,     0,    47,     0,    41,     0,    36,    34,     0,
     131,   130,   127,   140,   148,   138,   142,   146,   150,     0,
     158,   182,     0,    79,   169,   165,   168,     0,     0,    56,
     212,     0,   196,   198,   216,   197,   195,     0,   200,   194,
     193,    71,   217,    50,     0,    46,    42,    38,     0,     0,
       0,    34,     0,   134,     0,   147,     0,   135,     0,   144,
       0,   154,     0,     0,   152,   185,     0,   187,     0,   175,
      59,    58,    57,     0,    59,    43,    39,    34,    32,     0,
     133,   149,   136,   145,   155,   151,   153,   191,   183,     0,
     191,    85,   170,    60,   181,     0,    45,     0,    35,    33,
       0,   156,   186,   184,    81,    83,   188,     0,    75,   189,
     199,    44,   157,     0,     0,    80,     0,     0,    82,    83,
      89,    87,    95,    84,    91,    92,     0,     0,    86,    90,
      87,    93,    94,    88
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -309,  -309,   464,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -308,  -252,  -309,  -309,   209,   267,  -309,
    -309,  -309,   190,   235,  -159,  -102,  -309,  -309,   222,   282,
    -119,  -182,  -309,   108,   106,  -309,    93,    99,   -44,  -309,
     401,   322,  -107,    -4,    78,   -49,     5,  -309,  -309,  -309,
    -235,   139,  -309,  -309,  -209,  -244,  -309,    34,  -309,  -309,
    -309,  -309,  -309
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   320,   278,    31,    32,   222,   167,   314,
     220,    33,   252,   194,   298,   140,    34,    35,   213,   162,
      36,   150,   337,   375,   385,   378,   398,   391,   206,    37,
      55,    56,    70,   207,    72,    73,    74,    75,    76,    77,
     189,   244,   358,   361,   160,   208,   209,   210,   262,    38,
      39,    40,    88
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      71,   142,   144,   165,   270,   152,   242,   291,    57,   101,
     106,   304,   263,   349,   184,   186,   256,    96,   163,   309,
     310,   259,   195,   111,   111,   111,   317,   321,   122,    41,
     109,    42,   111,   147,   257,   293,   107,   148,    78,   368,
     123,   272,    96,   318,    97,   394,   395,    79,   173,    43,
     145,    57,    57,    46,   114,   115,   225,   264,   105,   112,
     273,   174,   256,   133,   274,   154,   155,   347,   127,   108,
     396,   260,   198,   185,   187,   232,   110,    47,   236,   237,
     257,   239,   228,   230,   199,   200,   201,   202,   203,   204,
     205,   250,    98,    99,   100,   234,    48,   245,   113,   113,
     113,    57,    57,    57,    57,    57,   134,   113,    71,   267,
     335,    80,   248,   372,   322,   226,   376,    98,    99,   100,
      49,    50,    51,    52,   324,    53,    54,   326,    81,   379,
     135,   328,   136,    82,   137,   138,   139,   181,   330,   333,
     156,   229,   231,   338,   157,   370,   176,   177,   301,   182,
     171,    83,   172,   253,   235,   190,   246,   254,   195,   178,
      58,   364,    59,    60,    61,   366,   266,   268,   191,   367,
     387,   249,    86,   323,   215,   216,   217,   218,   219,    87,
      44,   363,    45,   325,   196,   365,   327,   332,    89,   151,
     329,   153,   105,    99,   100,   340,   133,   331,   334,   346,
     179,   180,   339,    48,   371,   344,    84,   197,   198,    63,
      64,    65,    66,    67,   302,   401,   402,   305,   308,    90,
     199,   200,   201,   202,   203,   204,   205,    49,    50,    51,
      52,    68,    53,    54,    58,    69,    59,    60,    61,   134,
     258,   261,    91,    92,   102,   255,    58,    93,    59,    60,
      61,    71,   103,   104,   303,   116,   117,   306,    62,   118,
     119,   120,   121,   135,   124,   136,   125,   141,   138,   139,
      62,   126,   158,     4,   146,   175,   149,    48,   159,   133,
     164,   161,   166,    63,    64,    65,    66,    67,    58,    48,
      59,    60,    61,   168,   169,    63,    64,    65,    66,    67,
     183,    49,    50,    51,    52,    68,    53,    54,   170,    69,
     133,   188,   196,    49,    50,    51,    52,    68,    53,    54,
     192,    69,   134,    59,    60,    61,   193,   211,   214,   212,
     221,    48,   133,   223,   265,   224,   227,    63,    64,    65,
      66,    67,   133,   255,   233,    62,   135,   238,   136,   240,
     143,   138,   139,   134,   241,    49,    50,    51,    52,    68,
      53,    54,   243,    69,    48,   247,   251,   195,    94,    95,
      63,    64,    65,    66,    67,   134,   265,   135,   271,   136,
     276,   279,   138,   139,   277,   134,   280,   281,    49,    50,
      51,    52,    68,    53,    54,   282,    69,   283,   284,   135,
     285,   136,   286,   287,   138,   139,   288,   294,   289,   135,
     290,   136,   292,   295,   138,   139,   197,   198,   128,   296,
     130,   131,   132,   297,   307,   255,   300,   312,   313,   199,
     200,   201,   202,   203,   204,   205,     1,     2,   315,   319,
     336,     3,     4,   341,     5,   343,   345,   348,   350,   357,
       6,     7,     8,     9,    10,   351,   359,   352,   353,    11,
      12,    13,   354,   355,   356,   360,   369,    14,    15,   362,
     374,   377,   381,   380,   382,   383,   384,   386,   388,   390,
     392,   399,    85,   397,   316,    16,   299,    17,   275,   342,
      18,   311,   389,   403,   269,   393,   400,   373,   129
};

static const yytype_int16 yycheck[] =
{
       4,   103,   104,   122,   213,   112,   188,   242,     3,    58,
      20,     5,     9,   321,    20,    20,    56,     7,   120,   263,
     264,     5,     6,     7,     7,     7,     3,   279,    20,    15,
       3,    17,     7,    79,    74,   244,    46,    83,    79,   347,
      32,    32,     7,    20,    34,    21,    22,    16,    33,    35,
      33,    46,    47,     8,    83,    84,    20,    54,    62,    34,
      51,    46,    56,     8,    55,   114,   115,   319,    33,    79,
      46,    55,    56,    79,    79,   177,    49,    32,   180,   181,
      74,   183,    20,    20,    68,    69,    70,    71,    72,    73,
      74,   193,    82,    83,    84,    20,    51,    20,    82,    82,
      82,    96,    97,    98,    99,   100,    51,    82,   112,   211,
     292,    47,    20,   357,    20,    79,   360,    82,    83,    84,
      75,    76,    77,    78,    20,    80,    81,    20,    49,   364,
      75,    20,    77,    79,    79,    80,    81,    34,    20,    20,
      79,    79,    79,    20,    83,    20,    33,    34,   255,    46,
      76,    79,    78,    51,    79,    33,    79,    55,     6,    46,
       8,   343,    10,    11,    12,    51,   210,   211,    46,    55,
     379,    79,     0,    79,    39,    40,    41,    42,    43,     3,
      15,   340,    17,    79,    32,   344,    79,   289,    79,   111,
      79,   113,   196,    83,    84,   297,     8,    79,    79,   318,
      33,    34,    79,    51,    79,   307,    65,    55,    56,    57,
      58,    59,    60,    61,   258,    21,    22,   261,   262,    79,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,     8,    83,    10,    11,    12,    51,
     206,   207,    17,    79,    32,    19,     8,    79,    10,    11,
      12,   255,    32,    32,   258,    32,    79,   261,    32,    79,
      62,    68,    66,    75,    63,    77,    79,    79,    80,    81,
      32,    63,    48,    19,    79,    33,    79,    51,    50,     8,
      80,    79,    79,    57,    58,    59,    60,    61,     8,    51,
      10,    11,    12,    79,    63,    57,    58,    59,    60,    61,
      34,    75,    76,    77,    78,    79,    80,    81,    79,    83,
       8,    34,    32,    75,    76,    77,    78,    79,    80,    81,
      33,    83,    51,    10,    11,    12,    32,    68,    47,    34,
      34,    51,     8,    32,    32,    79,    79,    57,    58,    59,
      60,    61,     8,    19,    79,    32,    75,    79,    77,    79,
      79,    80,    81,    51,    79,    75,    76,    77,    78,    79,
      80,    81,    52,    83,    51,    79,    34,     6,    46,    47,
      57,    58,    59,    60,    61,    51,    32,    75,    15,    77,
      33,    32,    80,    81,    79,    51,    79,    33,    75,    76,
      77,    78,    79,    80,    81,    79,    83,    79,    33,    75,
      33,    77,    79,    33,    80,    81,    33,    79,    34,    75,
      33,    77,    53,    33,    80,    81,    55,    56,    96,    79,
      98,    99,   100,    34,    32,    19,    51,    79,    75,    68,
      69,    70,    71,    72,    73,    74,    13,    14,    51,    34,
      24,    18,    19,    33,    21,    49,    33,    33,    79,    63,
      27,    28,    29,    30,    31,    79,    25,    79,    79,    36,
      37,    38,    79,    33,    79,    26,    33,    44,    45,    79,
      79,    23,    51,    33,    79,    46,    34,    25,    79,    79,
      33,    79,    18,    34,   275,    62,   251,    64,   221,   299,
      67,   269,   384,   400,   212,   389,   397,   358,    97
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
      84,   131,    32,    32,    32,   129,    20,    46,    79,     3,
      49,     7,    34,    82,    83,    84,    32,    79,    79,    62,
      68,    66,    20,    32,    63,    79,    63,    33,   127,   126,
     127,   127,   127,     8,    51,    75,    77,    79,    80,    81,
     111,    79,   111,    79,   111,    33,    79,    79,    83,    79,
     117,   130,   128,   130,   131,   131,    79,    83,    48,    50,
     140,    79,   115,   111,    80,   116,    79,   104,    79,    63,
      79,    76,    78,    33,    46,    33,    33,    34,    46,    33,
      34,    34,    46,    34,    20,    79,    20,    79,    34,   136,
      33,    46,    33,    32,   109,     6,    32,    55,    56,    68,
      69,    70,    71,    72,    73,    74,   124,   129,   141,   142,
     143,    68,    34,   114,    47,    39,    40,    41,    42,    43,
     106,    34,   103,    32,    79,    20,    79,    79,    20,    79,
      20,    79,   111,    79,    20,    79,   111,   111,    79,   111,
      79,    79,   117,    52,   137,    20,    79,    79,    20,    79,
     111,    34,   108,    51,    55,    19,    56,    74,   143,     5,
      55,   143,   144,     9,    54,    32,   124,   111,   124,   115,
     140,    15,    32,    51,    55,   104,    33,    79,   100,    32,
      79,    33,    79,    79,    33,    33,    79,    33,    33,    34,
      33,   136,    53,   140,    79,    33,    79,    34,   110,   109,
      51,   128,   124,   129,     5,   124,   129,    32,   124,   141,
     141,   114,    79,    75,   105,    51,   103,     3,    20,    34,
      99,   100,    20,    79,    20,    79,    20,    79,    20,    79,
      20,    79,   111,    20,    79,   117,    24,   118,    20,    79,
     111,    33,   108,    49,   111,    33,   116,   100,    33,    99,
      79,    79,    79,    79,    79,    33,    79,    63,   138,    25,
      26,   139,    79,   110,   117,   110,    51,    55,    99,    33,
      20,    79,   141,   137,    79,   119,   141,    23,   121,   136,
      33,    51,    79,    46,    34,   120,    25,   140,    79,   119,
      79,   123,    33,   120,    21,    22,    46,    34,   122,    79,
     123,    21,    22,   122
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    98,    99,    99,   100,   101,   102,   102,
     102,   103,   103,   104,   104,   104,   104,   104,   104,   104,
     105,   106,   106,   106,   106,   107,   108,   108,   109,   110,
     110,   111,   111,   111,   111,   111,   111,   111,   112,   113,
     114,   114,   115,   115,   116,   116,   117,   117,   117,   118,
     118,   119,   119,   120,   120,   121,   121,   122,   122,   123,
     123,   123,   123,   123,   123,   124,   125,   126,   126,   127,
     127,   127,   127,   127,   127,   127,   128,   128,   129,   129,
     129,   130,   130,   130,   130,   131,   131,   131,   131,   132,
     132,   132,   132,   132,   132,   132,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   135,   135,   135,   135,
     135,   136,   136,   137,   137,   138,   138,   139,   139,   140,
     140,   141,   141,   141,   141,   142,   142,   142,   142,   142,
     142,   142,   142,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   144,   144,   145,   146,   147,
     148,   148
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     9,    10,     0,     3,     1,     5,     8,     9,
       5,     0,     3,     5,     7,     6,     4,     3,     2,     2,
       1,     1,     1,     1,     1,     6,     0,     3,     4,     0,
       3,     1,     2,     1,     2,     1,     1,     1,     4,     6,
       0,     3,     3,     3,     3,    10,     2,     1,     3,     0,
       4,     1,     3,     0,     3,     0,     4,     0,     3,     1,
       3,     2,     2,     4,     4,     8,     2,     1,     3,     3,
       3,     3,     3,     3,     2,     1,     1,     3,     1,     3,
       3,     1,     3,     3,     2,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     6,     4,     4,
       6,     6,     5,     8,     7,     7,     8,     4,     6,     5,
       6,     5,     6,     4,     7,     8,     6,     7,     6,     8,
       6,     8,     7,     8,     7,     8,     9,    10,     6,     1,
       1,     3,     3,     4,     4,     6,     3,     5,     6,     6,
       8,     2,     4,     5,     5,     7,     1,     1,     1,     1,
       1,     0,     3,     0,     5,     0,     2,     0,     2,     0,
       2,     0,     1,     3,     3,     3,     3,     3,     3,     6,
       3,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     3,     1,     2,     1,     2,     7,     2,     4,
       0,     1
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
#line 2013 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 319 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 2022 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 325 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 2030 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 330 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 2038 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 336 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 2046 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 342 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2054 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 348 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2062 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 354 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2072 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 361 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2080 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 367 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2090 "yacc_sql.cpp"
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
#line 2115 "yacc_sql.cpp"
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
#line 2140 "yacc_sql.cpp"
    break;

  case 34: /* id_list: %empty  */
#line 421 "yacc_sql.y"
    {
      (yyval.index_attr_list) = nullptr;
    }
#line 2148 "yacc_sql.cpp"
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
#line 2162 "yacc_sql.cpp"
    break;

  case 36: /* id: ID  */
#line 436 "yacc_sql.y"
        {

		(yyval.string) = (yyvsp[0].string);
    //free($1);
	}
#line 2172 "yacc_sql.cpp"
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
#line 2184 "yacc_sql.cpp"
    break;

  case 38: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 455 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-3].attr_info);

      create_table.select_flag = false;
    }
#line 2206 "yacc_sql.cpp"
    break;

  case 39: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE AS select_stmt  */
#line 473 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-6].string);
      free((yyvsp[-6].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-3].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-4].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());

      create_table.select_infos = (yyvsp[0].sql_node);
      create_table.select_flag = true;
      delete (yyvsp[-4].attr_info);
    }
#line 2229 "yacc_sql.cpp"
    break;

  case 40: /* create_table_stmt: CREATE TABLE ID AS select_stmt  */
#line 492 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));

      create_table.select_infos = (yyvsp[0].sql_node);
      create_table.select_flag = true;
    }
#line 2243 "yacc_sql.cpp"
    break;

  case 41: /* attr_def_list: %empty  */
#line 504 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2251 "yacc_sql.cpp"
    break;

  case 42: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 508 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2265 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type LBRACE number RBRACE  */
#line 521 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      //$$->nullable = false;
      free((yyvsp[-4].string));
    }
#line 2278 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type LBRACE number RBRACE NOT NULL_T  */
#line 530 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-5].number);
      (yyval.attr_info)->name = (yyvsp[-6].string);
      (yyval.attr_info)->length = (yyvsp[-3].number);
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-6].string));
    }
#line 2291 "yacc_sql.cpp"
    break;

  case 45: /* attr_def: ID type LBRACE number RBRACE NULL_T  */
#line 539 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-5].string));
    }
#line 2304 "yacc_sql.cpp"
    break;

  case 46: /* attr_def: ID type NOT NULL_T  */
#line 548 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-2].number);
      (yyval.attr_info)->name = (yyvsp[-3].string);
      (yyval.attr_info)->length = 4;
      //$$->nullable = true;
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-3].string));
    }
#line 2318 "yacc_sql.cpp"
    break;

  case 47: /* attr_def: ID type NULL_T  */
#line 558 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-2].string));
    }
#line 2331 "yacc_sql.cpp"
    break;

  case 48: /* attr_def: ID TEXT  */
#line 567 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = CHARS;
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 65535;
      free((yyvsp[-1].string));
    }
#line 2343 "yacc_sql.cpp"
    break;

  case 49: /* attr_def: ID type  */
#line 575 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      //$$->nullable = false;
      free((yyvsp[-1].string));
    }
#line 2356 "yacc_sql.cpp"
    break;

  case 50: /* number: NUMBER  */
#line 585 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2362 "yacc_sql.cpp"
    break;

  case 51: /* type: INT_T  */
#line 588 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2368 "yacc_sql.cpp"
    break;

  case 52: /* type: STRING_T  */
#line 589 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2374 "yacc_sql.cpp"
    break;

  case 53: /* type: FLOAT_T  */
#line 590 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2380 "yacc_sql.cpp"
    break;

  case 54: /* type: DATE_T  */
#line 591 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2386 "yacc_sql.cpp"
    break;

  case 55: /* insert_stmt: INSERT INTO ID VALUES record record_list  */
#line 595 "yacc_sql.y"
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
#line 2402 "yacc_sql.cpp"
    break;

  case 56: /* record_list: %empty  */
#line 610 "yacc_sql.y"
    {
      (yyval.record_list) =  nullptr;
    }
#line 2410 "yacc_sql.cpp"
    break;

  case 57: /* record_list: COMMA record record_list  */
#line 613 "yacc_sql.y"
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
#line 2427 "yacc_sql.cpp"
    break;

  case 58: /* record: LBRACE value value_list RBRACE  */
#line 627 "yacc_sql.y"
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
#line 2445 "yacc_sql.cpp"
    break;

  case 59: /* value_list: %empty  */
#line 643 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2453 "yacc_sql.cpp"
    break;

  case 60: /* value_list: COMMA value value_list  */
#line 646 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2467 "yacc_sql.cpp"
    break;

  case 61: /* value: NUMBER  */
#line 657 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2476 "yacc_sql.cpp"
    break;

  case 62: /* value: NEGATIVE_NUM NUMBER_NEGA  */
#line 661 "yacc_sql.y"
                               {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
#line 2485 "yacc_sql.cpp"
    break;

  case 63: /* value: FLOAT  */
#line 665 "yacc_sql.y"
            {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2494 "yacc_sql.cpp"
    break;

  case 64: /* value: NEGATIVE_NUM FLOAT_NEGA  */
#line 669 "yacc_sql.y"
                              {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
#line 2503 "yacc_sql.cpp"
    break;

  case 65: /* value: NULL_T  */
#line 673 "yacc_sql.y"
            { //要放到SSS的前面
      //char *tmp = common::substr($1,1,strlen($1)-2);
      (yyval.value) = new Value(0);
      (yyval.value)->set_null_value();
      //free(tmp);
    }
#line 2514 "yacc_sql.cpp"
    break;

  case 66: /* value: SSS  */
#line 679 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2524 "yacc_sql.cpp"
    break;

  case 67: /* value: DATESSS  */
#line 684 "yacc_sql.y"
             {
			char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(1, tmp);
      free(tmp);
		}
#line 2534 "yacc_sql.cpp"
    break;

  case 68: /* delete_stmt: DELETE FROM ID where  */
#line 694 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2548 "yacc_sql.cpp"
    break;

  case 69: /* update_stmt: UPDATE ID SET update_option update_options where  */
#line 706 "yacc_sql.y"
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
#line 2588 "yacc_sql.cpp"
    break;

  case 70: /* update_options: %empty  */
#line 744 "yacc_sql.y"
    {
      (yyval.attr_name_a_values) = nullptr;
    }
#line 2596 "yacc_sql.cpp"
    break;

  case 71: /* update_options: COMMA update_option update_options  */
#line 747 "yacc_sql.y"
                                                     {
      if ((yyvsp[0].attr_name_a_values) != nullptr) {
        (yyval.attr_name_a_values) = (yyvsp[0].attr_name_a_values);
      } else {
        (yyval.attr_name_a_values) = new std::vector<SetVariableSqlNode>;
      }
      (yyval.attr_name_a_values)->emplace_back(*(yyvsp[-1].attr_name_value));
       delete (yyvsp[-1].attr_name_value);
		}
#line 2610 "yacc_sql.cpp"
    break;

  case 72: /* update_option: ID EQ value  */
#line 757 "yacc_sql.y"
                            {
    	(yyval.attr_name_value) = new SetVariableSqlNode();
      (yyval.attr_name_value)->value = *(yyvsp[0].value);
      (yyval.attr_name_value)->name = (yyvsp[-2].string);
      (yyval.attr_name_value)->type = 0;
      free((yyvsp[-2].string));
      free((yyvsp[0].value));
		}
#line 2623 "yacc_sql.cpp"
    break;

  case 73: /* update_option: ID EQ sub_select_stmt  */
#line 765 "yacc_sql.y"
                            {
    	(yyval.attr_name_value) = new SetVariableSqlNode();
      (yyval.attr_name_value)->query = (yyvsp[0].sub_sql_node);
      (yyval.attr_name_value)->name = (yyvsp[-2].string);
      (yyval.attr_name_value)->type = 1;
      free((yyvsp[-2].string));
		}
#line 2635 "yacc_sql.cpp"
    break;

  case 74: /* select_stmt: SELECT add_expr_list SEMICOLON  */
#line 777 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);

      if ((yyvsp[-1].expression_list) != nullptr) {
        std::reverse((yyvsp[-1].expression_list)->begin(), (yyvsp[-1].expression_list)->end());
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-1].expression_list));
        delete (yyvsp[-1].expression_list);
      }
    }
#line 2649 "yacc_sql.cpp"
    break;

  case 75: /* select_stmt: SELECT add_expr_list FROM rel rel_list join_list where opt_group_by having opt_order_by  */
#line 787 "yacc_sql.y"
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
#line 2699 "yacc_sql.cpp"
    break;

  case 76: /* rel: ID ID  */
#line 837 "yacc_sql.y"
  {
    (yyval.rel_name) = new RelName();
    (yyval.rel_name)->relation = (yyvsp[-1].string);
    (yyval.rel_name)->alias = (yyvsp[0].string);
    free((yyvsp[-1].string));
    free((yyvsp[0].string));
  }
#line 2711 "yacc_sql.cpp"
    break;

  case 77: /* rel: ID  */
#line 845 "yacc_sql.y"
  {
    (yyval.rel_name) = new RelName();
    (yyval.rel_name)->relation = (yyvsp[0].string);
    free((yyvsp[0].string));
  }
#line 2721 "yacc_sql.cpp"
    break;

  case 78: /* rel: ID AS ID  */
#line 851 "yacc_sql.y"
  {
    (yyval.rel_name) = new RelName();
    (yyval.rel_name)->relation = (yyvsp[-2].string);
    (yyval.rel_name)->alias = (yyvsp[0].string);
    free((yyvsp[-2].string));
    free((yyvsp[0].string));
  }
#line 2733 "yacc_sql.cpp"
    break;

  case 79: /* opt_group_by: %empty  */
#line 861 "yacc_sql.y"
  {
    (yyval.rel_attr_list) = nullptr;
  }
#line 2741 "yacc_sql.cpp"
    break;

  case 80: /* opt_group_by: GROUP BY group_by group_by_list  */
#line 864 "yacc_sql.y"
                                    {
    if ((yyvsp[0].rel_attr_list) != nullptr) {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
    } else {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
    }
    (yyval.rel_attr_list)->push_back(*(yyvsp[-1].rel_attr));
    free((yyvsp[-1].rel_attr));
  }
#line 2755 "yacc_sql.cpp"
    break;

  case 81: /* group_by: ID  */
#line 876 "yacc_sql.y"
  {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
    free((yyvsp[0].string));
  }
#line 2765 "yacc_sql.cpp"
    break;

  case 82: /* group_by: ID DOT ID  */
#line 882 "yacc_sql.y"
  {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
    (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
    free((yyvsp[-2].string));
    free((yyvsp[0].string));
  }
#line 2777 "yacc_sql.cpp"
    break;

  case 83: /* group_by_list: %empty  */
#line 892 "yacc_sql.y"
  {
    (yyval.rel_attr_list) = nullptr;
  }
#line 2785 "yacc_sql.cpp"
    break;

  case 84: /* group_by_list: COMMA group_by group_by_list  */
#line 895 "yacc_sql.y"
                                 {
    if ((yyvsp[0].rel_attr_list) != nullptr) {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
    } else {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
    }
    (yyval.rel_attr_list)->push_back(*(yyvsp[-1].rel_attr));
    free((yyvsp[-1].rel_attr));
  }
#line 2799 "yacc_sql.cpp"
    break;

  case 85: /* opt_order_by: %empty  */
#line 907 "yacc_sql.y"
    {
      (yyval.order_by) = nullptr;
    }
#line 2807 "yacc_sql.cpp"
    break;

  case 86: /* opt_order_by: ORDER BY order_by_unit order_by_list  */
#line 910 "yacc_sql.y"
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
#line 2823 "yacc_sql.cpp"
    break;

  case 87: /* order_by_list: %empty  */
#line 923 "yacc_sql.y"
    {
      (yyval.order_by) = nullptr;
    }
#line 2831 "yacc_sql.cpp"
    break;

  case 88: /* order_by_list: COMMA order_by_unit order_by_list  */
#line 927 "yacc_sql.y"
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
#line 2846 "yacc_sql.cpp"
    break;

  case 89: /* order_by_unit: ID  */
#line 940 "yacc_sql.y"
        {
      (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[0].string);
      //$$->order_relation = NULL;
	}
#line 2856 "yacc_sql.cpp"
    break;

  case 90: /* order_by_unit: ID DOT ID  */
#line 947 "yacc_sql.y"
        {
		  (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[0].string);
      (yyval.order_by_node)->order_relation = (yyvsp[-2].string);
	}
#line 2866 "yacc_sql.cpp"
    break;

  case 91: /* order_by_unit: ID DESC  */
#line 954 "yacc_sql.y"
        {
      (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[-1].string);
      //$$->order_relation = NULL;
      (yyval.order_by_node)->asc_type = false;
	}
#line 2877 "yacc_sql.cpp"
    break;

  case 92: /* order_by_unit: ID ASC  */
#line 962 "yacc_sql.y"
        {
      (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[-1].string);
      //$$->order_relation = NULL;
	}
#line 2887 "yacc_sql.cpp"
    break;

  case 93: /* order_by_unit: ID DOT ID DESC  */
#line 969 "yacc_sql.y"
        {
      (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[-1].string);
      (yyval.order_by_node)->order_relation = (yyvsp[-3].string);
      (yyval.order_by_node)->asc_type = false;
	}
#line 2898 "yacc_sql.cpp"
    break;

  case 94: /* order_by_unit: ID DOT ID ASC  */
#line 977 "yacc_sql.y"
        {
		  (yyval.order_by_node) = new OrderBySqlNode();
      (yyval.order_by_node)->field = (yyvsp[-1].string);
      (yyval.order_by_node)->order_relation = (yyvsp[-3].string);
	}
#line 2908 "yacc_sql.cpp"
    break;

  case 95: /* sub_select_stmt: LBRACE SELECT add_expr_list FROM rel rel_list where RBRACE  */
#line 986 "yacc_sql.y"
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
#line 2933 "yacc_sql.cpp"
    break;

  case 96: /* calc_stmt: CALC expression_list  */
#line 1010 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2944 "yacc_sql.cpp"
    break;

  case 97: /* expression_list: expression  */
#line 1020 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2953 "yacc_sql.cpp"
    break;

  case 98: /* expression_list: expression COMMA expression_list  */
#line 1025 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2966 "yacc_sql.cpp"
    break;

  case 99: /* expression: expression '+' expression  */
#line 1035 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2974 "yacc_sql.cpp"
    break;

  case 100: /* expression: expression MINUS expression  */
#line 1038 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2982 "yacc_sql.cpp"
    break;

  case 101: /* expression: expression '*' expression  */
#line 1041 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2990 "yacc_sql.cpp"
    break;

  case 102: /* expression: expression '/' expression  */
#line 1044 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2998 "yacc_sql.cpp"
    break;

  case 103: /* expression: LBRACE expression RBRACE  */
#line 1047 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3007 "yacc_sql.cpp"
    break;

  case 104: /* expression: NEGATIVE_NUM expression  */
#line 1051 "yacc_sql.y"
                                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3015 "yacc_sql.cpp"
    break;

  case 105: /* expression: value2  */
#line 1054 "yacc_sql.y"
             {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 3025 "yacc_sql.cpp"
    break;

  case 106: /* add_expr_list: add_expr  */
#line 1062 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 3034 "yacc_sql.cpp"
    break;

  case 107: /* add_expr_list: add_expr COMMA add_expr_list  */
#line 1067 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 3047 "yacc_sql.cpp"
    break;

  case 108: /* add_expr: mul_expr  */
#line 1077 "yacc_sql.y"
            {

    }
#line 3055 "yacc_sql.cpp"
    break;

  case 109: /* add_expr: add_expr '+' mul_expr  */
#line 1080 "yacc_sql.y"
                            {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3063 "yacc_sql.cpp"
    break;

  case 110: /* add_expr: add_expr MINUS mul_expr  */
#line 1083 "yacc_sql.y"
                              {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3071 "yacc_sql.cpp"
    break;

  case 111: /* mul_expr: base_expr  */
#line 1088 "yacc_sql.y"
             {

    }
#line 3079 "yacc_sql.cpp"
    break;

  case 112: /* mul_expr: mul_expr '*' base_expr  */
#line 1091 "yacc_sql.y"
                             {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3087 "yacc_sql.cpp"
    break;

  case 113: /* mul_expr: mul_expr '/' base_expr  */
#line 1094 "yacc_sql.y"
                             {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3095 "yacc_sql.cpp"
    break;

  case 114: /* mul_expr: NEGATIVE_NUM base_expr  */
#line 1097 "yacc_sql.y"
                             {
      (yyval.expression) = create_alu_expression(ALUExpr::Type2::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3103 "yacc_sql.cpp"
    break;

  case 115: /* base_expr: LBRACE add_expr RBRACE  */
#line 1102 "yacc_sql.y"
                           {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3112 "yacc_sql.cpp"
    break;

  case 116: /* base_expr: value2  */
#line 1106 "yacc_sql.y"
             {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 3122 "yacc_sql.cpp"
    break;

  case 117: /* base_expr: cal_attr  */
#line 1111 "yacc_sql.y"
               {
      std::string table = (yyvsp[0].rel_attr)->relation_name;
      std::string attribute = (yyvsp[0].rel_attr)->attribute_name;
      std::string alias = (yyvsp[0].rel_attr)->alias;
      AggrOp aggr = (yyvsp[0].rel_attr)->aggr_func;
      (yyval.expression) = new FieldExpr(table, attribute, aggr,alias);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 3136 "yacc_sql.cpp"
    break;

  case 118: /* base_expr: function_attr  */
#line 1120 "yacc_sql.y"
                    {

    }
#line 3144 "yacc_sql.cpp"
    break;

  case 119: /* value2: NUMBER  */
#line 1125 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 3153 "yacc_sql.cpp"
    break;

  case 120: /* value2: FLOAT  */
#line 1129 "yacc_sql.y"
            {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 3162 "yacc_sql.cpp"
    break;

  case 121: /* value2: NUMBER_NEGA  */
#line 1133 "yacc_sql.y"
                  {
      int temp = (int)(yyvsp[0].number);
      temp *= (-1);
      (yyval.value) = new Value(temp);
      (yyloc) = (yylsp[0]);
    }
#line 3173 "yacc_sql.cpp"
    break;

  case 122: /* value2: FLOAT_NEGA  */
#line 1139 "yacc_sql.y"
                 {
      float temp = (float)(yyvsp[0].floats);
      temp *= (-1.0);
      (yyval.value) = new Value(temp);
      (yyloc) = (yylsp[0]);
    }
#line 3184 "yacc_sql.cpp"
    break;

  case 123: /* value2: NULL_T  */
#line 1145 "yacc_sql.y"
            { //要放到SSS的前面
      //char *tmp = common::substr($1,1,strlen($1)-2);
      (yyval.value) = new Value(0);
      (yyval.value)->set_null_value();
      //free(tmp);
    }
#line 3195 "yacc_sql.cpp"
    break;

  case 124: /* value2: SSS  */
#line 1151 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 3205 "yacc_sql.cpp"
    break;

  case 125: /* value2: DATESSS  */
#line 1156 "yacc_sql.y"
             {
			char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(1, tmp);
      free(tmp);
    }
#line 3215 "yacc_sql.cpp"
    break;

  case 126: /* function_attr: LENGTH LBRACE value RBRACE ID  */
#line 1164 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-2].value));
      (yyval.expression) = create_func_expression_alias(LENGTHS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
      free((yyvsp[0].string));
    }
#line 3225 "yacc_sql.cpp"
    break;

  case 127: /* function_attr: LENGTH LBRACE value RBRACE AS ID  */
#line 1171 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-3].value));
      (yyval.expression) = create_func_expression_alias(LENGTHS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
      free((yyvsp[0].string));
    }
#line 3235 "yacc_sql.cpp"
    break;

  case 128: /* function_attr: LENGTH LBRACE value RBRACE  */
#line 1178 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-1].value));
      (yyval.expression) = create_func_expression(LENGTHS, temp, nullptr, sql_string, &(yyloc));
    }
#line 3244 "yacc_sql.cpp"
    break;

  case 129: /* function_attr: LENGTH LBRACE ID RBRACE  */
#line 1184 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-1].string));
      (yyval.expression) = create_func_expression(LENGTHS, temp, nullptr, sql_string, &(yyloc));
    }
#line 3253 "yacc_sql.cpp"
    break;

  case 130: /* function_attr: LENGTH LBRACE ID DOT ID RBRACE  */
#line 1190 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-3].string), (yyvsp[-1].string));
      (yyval.expression) = create_func_expression(LENGTHS, temp, nullptr, sql_string, &(yyloc));
    }
#line 3262 "yacc_sql.cpp"
    break;

  case 131: /* function_attr: LENGTH LBRACE ID RBRACE AS ID  */
#line 1196 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-3].string));
      //$$ = create_func_expression(LENGTHS, temp, nullptr, sql_string, &@$);
      (yyval.expression) =create_func_expression_alias(LENGTHS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
    }
#line 3272 "yacc_sql.cpp"
    break;

  case 132: /* function_attr: LENGTH LBRACE ID RBRACE ID  */
#line 1203 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-2].string));
      //$$ = create_func_expression(LENGTHS, temp, nullptr, sql_string, &@$);
      (yyval.expression) =create_func_expression_alias(LENGTHS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
    }
#line 3282 "yacc_sql.cpp"
    break;

  case 133: /* function_attr: LENGTH LBRACE ID DOT ID RBRACE AS ID  */
#line 1211 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-5].string),(yyvsp[-3].string));
      //$$ = create_func_expression(LENGTHS, temp, nullptr, sql_string, &@$);
      (yyval.expression) =create_func_expression_alias(LENGTHS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
    }
#line 3292 "yacc_sql.cpp"
    break;

  case 134: /* function_attr: LENGTH LBRACE ID DOT ID RBRACE ID  */
#line 1218 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-4].string),(yyvsp[-2].string));
      //$$ = create_func_expression(LENGTHS, temp, nullptr, sql_string, &@$);
      (yyval.expression) =create_func_expression_alias(LENGTHS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
    }
#line 3302 "yacc_sql.cpp"
    break;

  case 135: /* function_attr: ROUND LBRACE ID DOT ID RBRACE ID  */
#line 1226 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-4].string),(yyvsp[-2].string));
      //$$ = create_func_expression(ROUNDS, temp, nullptr, sql_string, &@$);
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
    }
#line 3312 "yacc_sql.cpp"
    break;

  case 136: /* function_attr: ROUND LBRACE ID DOT ID RBRACE AS ID  */
#line 1233 "yacc_sql.y"
    {
     FieldExpr *temp = new FieldExpr((yyvsp[-5].string),(yyvsp[-3].string));
      //$$ = create_func_expression(ROUNDS, temp, nullptr, sql_string, &@$);
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
      free((yyvsp[0].string));
    }
#line 3323 "yacc_sql.cpp"
    break;

  case 137: /* function_attr: ROUND LBRACE ID RBRACE  */
#line 1241 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-1].string));
      (yyval.expression) = create_func_expression(ROUNDS, temp, nullptr, sql_string, &(yyloc));
    }
#line 3332 "yacc_sql.cpp"
    break;

  case 138: /* function_attr: ROUND LBRACE ID DOT ID RBRACE  */
#line 1247 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-3].string), (yyvsp[-1].string));
      (yyval.expression) = create_func_expression(ROUNDS, temp, nullptr, sql_string, &(yyloc));
    }
#line 3341 "yacc_sql.cpp"
    break;

  case 139: /* function_attr: ROUND LBRACE ID RBRACE ID  */
#line 1253 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-2].string));
      //$$ = create_func_expression(ROUNDS, temp, nullptr, sql_string, &@$);
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
    }
#line 3351 "yacc_sql.cpp"
    break;

  case 140: /* function_attr: ROUND LBRACE ID RBRACE AS ID  */
#line 1260 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-3].string));
      //$$ = create_func_expression(ROUNDS, temp, nullptr, sql_string, &@$);
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
      free((yyvsp[0].string));
    }
#line 3362 "yacc_sql.cpp"
    break;

  case 141: /* function_attr: ROUND LBRACE value RBRACE ID  */
#line 1268 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-2].value));
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
      free((yyvsp[0].string));
    }
#line 3372 "yacc_sql.cpp"
    break;

  case 142: /* function_attr: ROUND LBRACE value RBRACE AS ID  */
#line 1275 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-3].value));
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, nullptr, (yyvsp[0].string), sql_string, &(yyloc));
      free((yyvsp[0].string));
    }
#line 3382 "yacc_sql.cpp"
    break;

  case 143: /* function_attr: ROUND LBRACE value RBRACE  */
#line 1282 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-1].value));
      (yyval.expression) = create_func_expression(ROUNDS, temp, nullptr, sql_string, &(yyloc));
    }
#line 3391 "yacc_sql.cpp"
    break;

  case 144: /* function_attr: ROUND LBRACE value COMMA value RBRACE ID  */
#line 1288 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-4].value));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-2].value));
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3403 "yacc_sql.cpp"
    break;

  case 145: /* function_attr: ROUND LBRACE value COMMA value RBRACE AS ID  */
#line 1297 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-5].value));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-3].value));
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3415 "yacc_sql.cpp"
    break;

  case 146: /* function_attr: ROUND LBRACE value COMMA value RBRACE  */
#line 1306 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-3].value));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-1].value));
      (yyval.expression) = create_func_expression(ROUNDS, temp, temp2, sql_string, &(yyloc));
    }
#line 3425 "yacc_sql.cpp"
    break;

  case 147: /* function_attr: ROUND LBRACE ID COMMA value RBRACE ID  */
#line 1314 "yacc_sql.y"
    {
      //ValueExpr *temp = new ValueExpr(*$3);
      FieldExpr *temp = new FieldExpr((yyvsp[-4].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-2].value));
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3438 "yacc_sql.cpp"
    break;

  case 148: /* function_attr: ROUND LBRACE ID COMMA value RBRACE  */
#line 1324 "yacc_sql.y"
    {
      //ValueExpr *temp = new ValueExpr(*$3);
      FieldExpr *temp = new FieldExpr((yyvsp[-3].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-1].value));
      (yyval.expression) = create_func_expression(ROUNDS, temp, temp2, sql_string, &(yyloc));
    }
#line 3449 "yacc_sql.cpp"
    break;

  case 149: /* function_attr: ROUND LBRACE ID COMMA value RBRACE AS ID  */
#line 1332 "yacc_sql.y"
    {
      //ValueExpr *temp = new ValueExpr(*$3);
      FieldExpr *temp = new FieldExpr((yyvsp[-5].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-3].value));
      (yyval.expression) = create_func_expression_alias(ROUNDS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3462 "yacc_sql.cpp"
    break;

  case 150: /* function_attr: DATE_FORMAT LBRACE ID COMMA value RBRACE  */
#line 1343 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-3].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-1].value));
      (yyval.expression) = create_func_expression(DATE_FORMATS, temp, temp2, sql_string, &(yyloc));
    }
#line 3472 "yacc_sql.cpp"
    break;

  case 151: /* function_attr: DATE_FORMAT LBRACE ID DOT ID COMMA value RBRACE  */
#line 1350 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-5].string), (yyvsp[-3].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-1].value));
      (yyval.expression) = create_func_expression(DATE_FORMATS, temp, temp2, sql_string, &(yyloc));
    }
#line 3482 "yacc_sql.cpp"
    break;

  case 152: /* function_attr: DATE_FORMAT LBRACE value COMMA value RBRACE ID  */
#line 1357 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-4].value));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-2].value));
      (yyval.expression) = create_func_expression_alias(DATE_FORMATS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3494 "yacc_sql.cpp"
    break;

  case 153: /* function_attr: DATE_FORMAT LBRACE value COMMA value RBRACE AS ID  */
#line 1366 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-5].value));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-3].value));
      (yyval.expression) = create_func_expression_alias(DATE_FORMATS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3506 "yacc_sql.cpp"
    break;

  case 154: /* function_attr: DATE_FORMAT LBRACE ID COMMA value RBRACE ID  */
#line 1376 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-4].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-2].value));
      (yyval.expression) = create_func_expression_alias(DATE_FORMATS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3518 "yacc_sql.cpp"
    break;

  case 155: /* function_attr: DATE_FORMAT LBRACE ID COMMA value RBRACE AS ID  */
#line 1385 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-5].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-3].value));
      (yyval.expression) = create_func_expression_alias(DATE_FORMATS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3530 "yacc_sql.cpp"
    break;

  case 156: /* function_attr: DATE_FORMAT LBRACE ID DOT ID COMMA value RBRACE ID  */
#line 1394 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-6].string),(yyvsp[-4].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-2].value));
      (yyval.expression) = create_func_expression_alias(DATE_FORMATS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[-2].value));
    }
#line 3542 "yacc_sql.cpp"
    break;

  case 157: /* function_attr: DATE_FORMAT LBRACE ID DOT ID COMMA value RBRACE AS ID  */
#line 1403 "yacc_sql.y"
    {
      FieldExpr *temp = new FieldExpr((yyvsp[-7].string),(yyvsp[-5].string));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-3].value));
      (yyval.expression) = create_func_expression_alias(DATE_FORMATS, temp, temp2, (yyvsp[0].string), sql_string, &(yyloc));

      free((yyvsp[0].string));
    }
#line 3554 "yacc_sql.cpp"
    break;

  case 158: /* function_attr: DATE_FORMAT LBRACE value COMMA value RBRACE  */
#line 1412 "yacc_sql.y"
    {
      ValueExpr *temp = new ValueExpr(*(yyvsp[-3].value));
      ValueExpr *temp2 = new ValueExpr(*(yyvsp[-1].value));
      (yyval.expression) = create_func_expression(DATE_FORMATS, temp, temp2, sql_string, &(yyloc));
    }
#line 3564 "yacc_sql.cpp"
    break;

  case 159: /* cal_attr: '*'  */
#line 1419 "yacc_sql.y"
        {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = "";
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyloc) = (yylsp[0]);
    }
#line 3576 "yacc_sql.cpp"
    break;

  case 160: /* cal_attr: ID  */
#line 1426 "yacc_sql.y"
         {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyloc) = (yylsp[0]);
      free((yyvsp[0].string));
    }
#line 3588 "yacc_sql.cpp"
    break;

  case 161: /* cal_attr: ID DOT '*'  */
#line 1433 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyloc) = (yylsp[-2]);
      free((yyvsp[-2].string));
      
    }
#line 3602 "yacc_sql.cpp"
    break;

  case 162: /* cal_attr: ID DOT ID  */
#line 1442 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyloc) = (yylsp[-2]);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3616 "yacc_sql.cpp"
    break;

  case 163: /* cal_attr: aggr_func LBRACE '*' RBRACE  */
#line 1451 "yacc_sql.y"
                                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggr_func = (yyvsp[-3].aggr);
      (yyloc) = (yylsp[-3]);
    }
#line 3627 "yacc_sql.cpp"
    break;

  case 164: /* cal_attr: aggr_func LBRACE ID RBRACE  */
#line 1457 "yacc_sql.y"
                                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-3].aggr);
      (yyloc) = (yylsp[-3]);
      free((yyvsp[-1].string));
    }
#line 3639 "yacc_sql.cpp"
    break;

  case 165: /* cal_attr: aggr_func LBRACE ID DOT ID RBRACE  */
#line 1464 "yacc_sql.y"
                                       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-5].aggr);
      (yyloc) = (yylsp[-5]);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 3653 "yacc_sql.cpp"
    break;

  case 166: /* cal_attr: ID AS ID  */
#line 1473 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[0].string));
      free((yyvsp[-2].string));
    }
#line 3666 "yacc_sql.cpp"
    break;

  case 167: /* cal_attr: ID DOT ID AS ID  */
#line 1481 "yacc_sql.y"
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
#line 3681 "yacc_sql.cpp"
    break;

  case 168: /* cal_attr: aggr_func LBRACE '*' RBRACE AS ID  */
#line 1491 "yacc_sql.y"
                                        {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggr_func = (yyvsp[-5].aggr);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3693 "yacc_sql.cpp"
    break;

  case 169: /* cal_attr: aggr_func LBRACE ID RBRACE AS ID  */
#line 1498 "yacc_sql.y"
                                      {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-3].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-5].aggr);
       (yyval.rel_attr)->alias = (yyvsp[0].string);
       free((yyvsp[0].string));
      free((yyvsp[-3].string));
    }
#line 3706 "yacc_sql.cpp"
    break;

  case 170: /* cal_attr: aggr_func LBRACE ID DOT ID RBRACE AS ID  */
#line 1506 "yacc_sql.y"
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
#line 3721 "yacc_sql.cpp"
    break;

  case 171: /* cal_attr: ID ID  */
#line 1516 "yacc_sql.y"
             { //不加AS也可以
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->aggr_func = UNKNOWN;
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[0].string));
      free((yyvsp[-1].string));
    }
#line 3734 "yacc_sql.cpp"
    break;

  case 172: /* cal_attr: ID DOT ID ID  */
#line 1524 "yacc_sql.y"
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
#line 3749 "yacc_sql.cpp"
    break;

  case 173: /* cal_attr: aggr_func LBRACE '*' RBRACE ID  */
#line 1534 "yacc_sql.y"
                                     {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = "*";
      (yyval.rel_attr)->aggr_func = (yyvsp[-4].aggr);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3761 "yacc_sql.cpp"
    break;

  case 174: /* cal_attr: aggr_func LBRACE ID RBRACE ID  */
#line 1541 "yacc_sql.y"
                                   {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->aggr_func = (yyvsp[-4].aggr);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
       
       free((yyvsp[0].string));
      free((yyvsp[-2].string));
    }
#line 3775 "yacc_sql.cpp"
    break;

  case 175: /* cal_attr: aggr_func LBRACE ID DOT ID RBRACE ID  */
#line 1550 "yacc_sql.y"
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
#line 3790 "yacc_sql.cpp"
    break;

  case 176: /* aggr_func: MAX  */
#line 1563 "yacc_sql.y"
        { (yyval.aggr)=MAXF; }
#line 3796 "yacc_sql.cpp"
    break;

  case 177: /* aggr_func: MIN  */
#line 1564 "yacc_sql.y"
                { (yyval.aggr)=MINF; }
#line 3802 "yacc_sql.cpp"
    break;

  case 178: /* aggr_func: COUNT  */
#line 1565 "yacc_sql.y"
                  { (yyval.aggr)=COUNTF; }
#line 3808 "yacc_sql.cpp"
    break;

  case 179: /* aggr_func: AVG  */
#line 1566 "yacc_sql.y"
                { (yyval.aggr)=AVGF; }
#line 3814 "yacc_sql.cpp"
    break;

  case 180: /* aggr_func: SUM  */
#line 1567 "yacc_sql.y"
                { (yyval.aggr)=SUMF; }
#line 3820 "yacc_sql.cpp"
    break;

  case 181: /* rel_list: %empty  */
#line 1571 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 3828 "yacc_sql.cpp"
    break;

  case 182: /* rel_list: COMMA rel rel_list  */
#line 1574 "yacc_sql.y"
                         {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<RelName>;
      }

      (yyval.relation_list)->push_back(*(yyvsp[-1].rel_name));//本来是字符串char* 所以这里要加*
      free((yyvsp[-1].rel_name));
    }
#line 3843 "yacc_sql.cpp"
    break;

  case 183: /* join_list: %empty  */
#line 1587 "yacc_sql.y"
    {
      (yyval.join_lists) = nullptr;
    }
#line 3851 "yacc_sql.cpp"
    break;

  case 184: /* join_list: INNER JOIN rel on join_list  */
#line 1590 "yacc_sql.y"
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
#line 3870 "yacc_sql.cpp"
    break;

  case 185: /* on: %empty  */
#line 1607 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3878 "yacc_sql.cpp"
    break;

  case 186: /* on: ON condition_list  */
#line 1610 "yacc_sql.y"
                        {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3886 "yacc_sql.cpp"
    break;

  case 187: /* having: %empty  */
#line 1616 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3894 "yacc_sql.cpp"
    break;

  case 188: /* having: HAVING condition_list  */
#line 1619 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3902 "yacc_sql.cpp"
    break;

  case 189: /* where: %empty  */
#line 1625 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3910 "yacc_sql.cpp"
    break;

  case 190: /* where: WHERE condition_list  */
#line 1628 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3918 "yacc_sql.cpp"
    break;

  case 191: /* condition_list: %empty  */
#line 1634 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3926 "yacc_sql.cpp"
    break;

  case 192: /* condition_list: condition  */
#line 1637 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3936 "yacc_sql.cpp"
    break;

  case 193: /* condition_list: condition AND condition_list  */
#line 1642 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->conjunction = 0;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3947 "yacc_sql.cpp"
    break;

  case 194: /* condition_list: condition OR condition_list  */
#line 1648 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->conjunction = 1;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3958 "yacc_sql.cpp"
    break;

  case 195: /* condition: add_expr cal_comp_op add_expr  */
#line 1657 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3971 "yacc_sql.cpp"
    break;

  case 196: /* condition: sub_select_stmt cal_comp_op sub_select_stmt  */
#line 1666 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_sql = (yyvsp[-2].sub_sql_node);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_sql = (yyvsp[0].sub_sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3984 "yacc_sql.cpp"
    break;

  case 197: /* condition: add_expr cal_comp_op sub_select_stmt  */
#line 1675 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_sql = (yyvsp[0].sub_sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3997 "yacc_sql.cpp"
    break;

  case 198: /* condition: sub_select_stmt cal_comp_op add_expr  */
#line 1684 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_sql = (yyvsp[-2].sub_sql_node);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 4010 "yacc_sql.cpp"
    break;

  case 199: /* condition: add_expr logical_comp_op LBRACE value value_list RBRACE  */
#line 1693 "yacc_sql.y"
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
#line 4027 "yacc_sql.cpp"
    break;

  case 200: /* condition: add_expr logical_comp_op sub_select_stmt  */
#line 1706 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_sql = (yyvsp[0].sub_sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 4040 "yacc_sql.cpp"
    break;

  case 201: /* condition: cal_comp_op sub_select_stmt  */
#line 1716 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = -1;
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_sql = (yyvsp[0].sub_sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 4052 "yacc_sql.cpp"
    break;

  case 202: /* condition: add_expr cal_comp_op  */
#line 1725 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_expr = (yyvsp[-1].expression);
      (yyval.condition)->right_is_attr = -1;
      (yyval.condition)->comp = (yyvsp[0].comp);
    }
#line 4064 "yacc_sql.cpp"
    break;

  case 203: /* cal_comp_op: EQ  */
#line 1735 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 4070 "yacc_sql.cpp"
    break;

  case 204: /* cal_comp_op: LT  */
#line 1736 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 4076 "yacc_sql.cpp"
    break;

  case 205: /* cal_comp_op: GT  */
#line 1737 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 4082 "yacc_sql.cpp"
    break;

  case 206: /* cal_comp_op: LE  */
#line 1738 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 4088 "yacc_sql.cpp"
    break;

  case 207: /* cal_comp_op: GE  */
#line 1739 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 4094 "yacc_sql.cpp"
    break;

  case 208: /* cal_comp_op: NE  */
#line 1740 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 4100 "yacc_sql.cpp"
    break;

  case 209: /* cal_comp_op: LIKE  */
#line 1741 "yacc_sql.y"
           { (yyval.comp) = REGEX_LIKE; }
#line 4106 "yacc_sql.cpp"
    break;

  case 210: /* cal_comp_op: NOT LIKE  */
#line 1742 "yacc_sql.y"
               { (yyval.comp) = REGEX_NOT_LIKE; }
#line 4112 "yacc_sql.cpp"
    break;

  case 211: /* cal_comp_op: IS NULL_T  */
#line 1743 "yacc_sql.y"
               { (yyval.comp) = IS_NULL; }
#line 4118 "yacc_sql.cpp"
    break;

  case 212: /* cal_comp_op: IS NOT NULL_T  */
#line 1744 "yacc_sql.y"
                   { (yyval.comp) = IS_NOT_NULL; }
#line 4124 "yacc_sql.cpp"
    break;

  case 213: /* cal_comp_op: EXISTS  */
#line 1745 "yacc_sql.y"
             { (yyval.comp) = EXISTS_QUERY; }
#line 4130 "yacc_sql.cpp"
    break;

  case 214: /* cal_comp_op: NOT EXISTS  */
#line 1746 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS_QUERY; }
#line 4136 "yacc_sql.cpp"
    break;

  case 215: /* logical_comp_op: IN  */
#line 1749 "yacc_sql.y"
         { (yyval.comp) = IN_QUERY; }
#line 4142 "yacc_sql.cpp"
    break;

  case 216: /* logical_comp_op: NOT IN  */
#line 1750 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_QUERY; }
#line 4148 "yacc_sql.cpp"
    break;

  case 217: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1754 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 4162 "yacc_sql.cpp"
    break;

  case 218: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1767 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 4171 "yacc_sql.cpp"
    break;

  case 219: /* set_variable_stmt: SET ID EQ value  */
#line 1775 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 4183 "yacc_sql.cpp"
    break;


#line 4187 "yacc_sql.cpp"

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

#line 1787 "yacc_sql.y"

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
