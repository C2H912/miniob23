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
    BY = 279,                      /* BY  */
    SHOW = 280,                    /* SHOW  */
    SYNC = 281,                    /* SYNC  */
    INSERT = 282,                  /* INSERT  */
    DELETE = 283,                  /* DELETE  */
    UPDATE = 284,                  /* UPDATE  */
    LBRACE = 285,                  /* LBRACE  */
    RBRACE = 286,                  /* RBRACE  */
    COMMA = 287,                   /* COMMA  */
    UNIQUE = 288,                  /* UNIQUE  */
    TRX_BEGIN = 289,               /* TRX_BEGIN  */
    TRX_COMMIT = 290,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 291,            /* TRX_ROLLBACK  */
    INT_T = 292,                   /* INT_T  */
    STRING_T = 293,                /* STRING_T  */
    DATE_T = 294,                  /* DATE_T  */
    FLOAT_T = 295,                 /* FLOAT_T  */
    TEXT = 296,                    /* TEXT  */
    HELP = 297,                    /* HELP  */
    EXIT = 298,                    /* EXIT  */
    DOT = 299,                     /* DOT  */
    INTO = 300,                    /* INTO  */
    VALUES = 301,                  /* VALUES  */
    FROM = 302,                    /* FROM  */
    WHERE = 303,                   /* WHERE  */
    NULL_T = 304,                  /* NULL_T  */
    INNER = 305,                   /* INNER  */
    JOIN = 306,                    /* JOIN  */
    AND = 307,                     /* AND  */
    NOT = 308,                     /* NOT  */
    LIKE = 309,                    /* LIKE  */
    MAX = 310,                     /* MAX  */
    MIN = 311,                     /* MIN  */
    SUM = 312,                     /* SUM  */
    AVG = 313,                     /* AVG  */
    COUNT = 314,                   /* COUNT  */
    SET = 315,                     /* SET  */
    ON = 316,                      /* ON  */
    LOAD = 317,                    /* LOAD  */
    DATA = 318,                    /* DATA  */
    INFILE = 319,                  /* INFILE  */
    EXPLAIN = 320,                 /* EXPLAIN  */
    EQ = 321,                      /* EQ  */
    LT = 322,                      /* LT  */
    GT = 323,                      /* GT  */
    LE = 324,                      /* LE  */
    GE = 325,                      /* GE  */
    NE = 326,                      /* NE  */
    EXISTS = 327,                  /* EXISTS  */
    NUMBER = 328,                  /* NUMBER  */
    NUMBER_NEGA = 329,             /* NUMBER_NEGA  */
    FLOAT = 330,                   /* FLOAT  */
    FLOAT_NEGA = 331,              /* FLOAT_NEGA  */
    ID = 332,                      /* ID  */
    SSS = 333,                     /* SSS  */
    DATESSS = 334,                 /* DATESSS  */
    UNARY_MINUS = 335              /* UNARY_MINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 153 "yacc_sql.y"

  ParsedSqlNode *                   sql_node;
  SelectSqlNode *                   sub_sql_node;
  ConditionSqlNode *                condition;
  std::vector<InnerJoinSqlNode> *   join_lists;
  Value *                           value;
  std::vector<Value> *              record;
  enum CompOp                       comp;
  enum AggrOp                       aggr;
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

#line 174 "yacc_sql.hpp"

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
