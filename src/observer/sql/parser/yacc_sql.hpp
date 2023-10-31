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
    OR = 262,                      /* OR  */
    CREATE = 263,                  /* CREATE  */
    DROP = 264,                    /* DROP  */
    TABLE = 265,                   /* TABLE  */
    TABLES = 266,                  /* TABLES  */
    INDEX = 267,                   /* INDEX  */
    CALC = 268,                    /* CALC  */
    SELECT = 269,                  /* SELECT  */
    DESC = 270,                    /* DESC  */
    ASC = 271,                     /* ASC  */
    ORDER = 272,                   /* ORDER  */
    BY = 273,                      /* BY  */
    SHOW = 274,                    /* SHOW  */
    SYNC = 275,                    /* SYNC  */
    INSERT = 276,                  /* INSERT  */
    DELETE = 277,                  /* DELETE  */
    UPDATE = 278,                  /* UPDATE  */
    LBRACE = 279,                  /* LBRACE  */
    RBRACE = 280,                  /* RBRACE  */
    COMMA = 281,                   /* COMMA  */
    UNIQUE = 282,                  /* UNIQUE  */
    TRX_BEGIN = 283,               /* TRX_BEGIN  */
    TRX_COMMIT = 284,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 285,            /* TRX_ROLLBACK  */
    INT_T = 286,                   /* INT_T  */
    STRING_T = 287,                /* STRING_T  */
    DATE_T = 288,                  /* DATE_T  */
    FLOAT_T = 289,                 /* FLOAT_T  */
    TEXT = 290,                    /* TEXT  */
    HELP = 291,                    /* HELP  */
    EXIT = 292,                    /* EXIT  */
    DOT = 293,                     /* DOT  */
    INTO = 294,                    /* INTO  */
    VALUES = 295,                  /* VALUES  */
    FROM = 296,                    /* FROM  */
    WHERE = 297,                   /* WHERE  */
    NULL_T = 298,                  /* NULL_T  */
    INNER = 299,                   /* INNER  */
    JOIN = 300,                    /* JOIN  */
    AND = 301,                     /* AND  */
    NOT = 302,                     /* NOT  */
    LIKE = 303,                    /* LIKE  */
    MAX = 304,                     /* MAX  */
    MIN = 305,                     /* MIN  */
    SUM = 306,                     /* SUM  */
    AVG = 307,                     /* AVG  */
    COUNT = 308,                   /* COUNT  */
    SET = 309,                     /* SET  */
    ON = 310,                      /* ON  */
    LOAD = 311,                    /* LOAD  */
    DATA = 312,                    /* DATA  */
    INFILE = 313,                  /* INFILE  */
    EXPLAIN = 314,                 /* EXPLAIN  */
    EQ = 315,                      /* EQ  */
    LT = 316,                      /* LT  */
    GT = 317,                      /* GT  */
    LE = 318,                      /* LE  */
    GE = 319,                      /* GE  */
    NE = 320,                      /* NE  */
    EXISTS = 321,                  /* EXISTS  */
    NUMBER = 322,                  /* NUMBER  */
    FLOAT = 323,                   /* FLOAT  */
    ID = 324,                      /* ID  */
    SSS = 325,                     /* SSS  */
    DATESSS = 326,                 /* DATESSS  */
    UNARY_MINUS = 327              /* UNARY_MINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 147 "yacc_sql.y"

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
  std::vector<std::string> *        relation_list;
  std::vector<std::string> *        index_attr_list;
  std::vector<OrderBySqlNode> *     order_by;
  OrderBySqlNode *                  order_by_node;
  char *                            string;
  int                               number;
  float                             floats;

#line 165 "yacc_sql.hpp"

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
