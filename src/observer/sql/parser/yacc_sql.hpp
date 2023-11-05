/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    NULLABLE = 259,                /* NULLABLE  */
    IN = 260,                      /* IN  */
    IS = 261,                      /* IS  */
    MINUS = 262,                   /* MINUS  */
    NEGATIVE_NUM = 263,            /* NEGATIVE_NUM  */
    OR = 264,                      /* OR  */
    LENGTH = 265,                  /* LENGTH  */
    ROUND = 266,                   /* ROUND  */
    DATE_FORMAT = 267,             /* DATE_FORMAT  */
    CREATE = 268,                  /* CREATE  */
    DROP = 269,                    /* DROP  */
    TABLE = 270,                   /* TABLE  */
    TABLES = 271,                  /* TABLES  */
    INDEX = 272,                   /* INDEX  */
    CALC = 273,                    /* CALC  */
    SELECT = 274,                  /* SELECT  */
    AS = 275,                      /* AS  */
    DESC = 276,                    /* DESC  */
    ASC = 277,                     /* ASC  */
    ORDER = 278,                   /* ORDER  */
    GROUP = 279,                   /* GROUP  */
    BY = 280,                      /* BY  */
    HAVING = 281,                  /* HAVING  */
    SHOW = 282,                    /* SHOW  */
    SYNC = 283,                    /* SYNC  */
    INSERT = 284,                  /* INSERT  */
    DELETE = 285,                  /* DELETE  */
    UPDATE = 286,                  /* UPDATE  */
    LBRACE = 287,                  /* LBRACE  */
    RBRACE = 288,                  /* RBRACE  */
    COMMA = 289,                   /* COMMA  */
    UNIQUE = 290,                  /* UNIQUE  */
    TRX_BEGIN = 291,               /* TRX_BEGIN  */
    TRX_COMMIT = 292,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 293,            /* TRX_ROLLBACK  */
    INT_T = 294,                   /* INT_T  */
    STRING_T = 295,                /* STRING_T  */
    DATE_T = 296,                  /* DATE_T  */
    FLOAT_T = 297,                 /* FLOAT_T  */
    TEXT = 298,                    /* TEXT  */
    HELP = 299,                    /* HELP  */
    EXIT = 300,                    /* EXIT  */
    DOT = 301,                     /* DOT  */
    INTO = 302,                    /* INTO  */
    VALUES = 303,                  /* VALUES  */
    FROM = 304,                    /* FROM  */
    WHERE = 305,                   /* WHERE  */
    NULL_T = 306,                  /* NULL_T  */
    INNER = 307,                   /* INNER  */
    JOIN = 308,                    /* JOIN  */
    AND = 309,                     /* AND  */
    NOT = 310,                     /* NOT  */
    LIKE = 311,                    /* LIKE  */
    MAX = 312,                     /* MAX  */
    MIN = 313,                     /* MIN  */
    SUM = 314,                     /* SUM  */
    AVG = 315,                     /* AVG  */
    COUNT = 316,                   /* COUNT  */
    SET = 317,                     /* SET  */
    ON = 318,                      /* ON  */
    LOAD = 319,                    /* LOAD  */
    DATA = 320,                    /* DATA  */
    INFILE = 321,                  /* INFILE  */
    EXPLAIN = 322,                 /* EXPLAIN  */
    EQ = 323,                      /* EQ  */
    LT = 324,                      /* LT  */
    GT = 325,                      /* GT  */
    LE = 326,                      /* LE  */
    GE = 327,                      /* GE  */
    NE = 328,                      /* NE  */
    EXISTS = 329,                  /* EXISTS  */
    NUMBER = 330,                  /* NUMBER  */
    NUMBER_NEGA = 331,             /* NUMBER_NEGA  */
    FLOAT = 332,                   /* FLOAT  */
    FLOAT_NEGA = 333,              /* FLOAT_NEGA  */
    ID = 334,                      /* ID  */
    SSS = 335,                     /* SSS  */
    DATESSS = 336,                 /* DATESSS  */
    UNARY_MINUS = 337              /* UNARY_MINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 172 "yacc_sql.y"

  ParsedSqlNode *                   sql_node;
  SelectSqlNode *                   sub_sql_node;
  ConditionSqlNode *                condition;
  std::vector<InnerJoinSqlNode> *   join_lists;
  Value *                           value;
  std::vector<Value> *              record;
  enum CompOp                       comp;
  enum AggrOp                       aggr;
  enum FuncOp                       func;
  RelAttrSqlNode *                  rel_attr;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  Expression *                      expression;
  std::vector<Expression *> *       expression_list;
  std::vector<Value> *              value_list;
  std::vector<SetVariableSqlNode> * attr_name_a_values;
  SetVariableSqlNode *              attr_name_value;
  std::vector<ValueRecord> *        record_list;
  std::vector<ConditionSqlNode> *   condition_list;
  std::vector<RelAttrSqlNode> *     rel_attr_list;
  std::vector<RelName> *            relation_list;
  RelName *                         rel_name;
  std::vector<std::string> *        index_attr_list;
  std::vector<OrderBySqlNode> *     order_by;
  OrderBySqlNode *                  order_by_node;
  char *                            string;
  int                               number;
  float                             floats;

#line 177 "yacc_sql.hpp"

};
typedef union YYSTYPE YYSTYPE;
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




int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);


#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */
