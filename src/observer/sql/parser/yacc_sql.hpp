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
    CREATE = 262,                  /* CREATE  */
    DROP = 263,                    /* DROP  */
    TABLE = 264,                   /* TABLE  */
    TABLES = 265,                  /* TABLES  */
    INDEX = 266,                   /* INDEX  */
    CALC = 267,                    /* CALC  */
    SELECT = 268,                  /* SELECT  */
    DESC = 269,                    /* DESC  */
    SHOW = 270,                    /* SHOW  */
    SYNC = 271,                    /* SYNC  */
    INSERT = 272,                  /* INSERT  */
    DELETE = 273,                  /* DELETE  */
    UPDATE = 274,                  /* UPDATE  */
    LBRACE = 275,                  /* LBRACE  */
    RBRACE = 276,                  /* RBRACE  */
    COMMA = 277,                   /* COMMA  */
    UNIQUE = 278,                  /* UNIQUE  */
    TRX_BEGIN = 279,               /* TRX_BEGIN  */
    TRX_COMMIT = 280,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 281,            /* TRX_ROLLBACK  */
    INT_T = 282,                   /* INT_T  */
    STRING_T = 283,                /* STRING_T  */
    DATE_T = 284,                  /* DATE_T  */
    FLOAT_T = 285,                 /* FLOAT_T  */
    HELP = 286,                    /* HELP  */
    EXIT = 287,                    /* EXIT  */
    DOT = 288,                     /* DOT  */
    INTO = 289,                    /* INTO  */
    VALUES = 290,                  /* VALUES  */
    FROM = 291,                    /* FROM  */
    WHERE = 292,                   /* WHERE  */
    NULL_T = 293,                  /* NULL_T  */
    INNER = 294,                   /* INNER  */
    JOIN = 295,                    /* JOIN  */
    AND = 296,                     /* AND  */
    NOT = 297,                     /* NOT  */
    LIKE = 298,                    /* LIKE  */
    MAX = 299,                     /* MAX  */
    MIN = 300,                     /* MIN  */
    SUM = 301,                     /* SUM  */
    AVG = 302,                     /* AVG  */
    COUNT = 303,                   /* COUNT  */
    SET = 304,                     /* SET  */
    ON = 305,                      /* ON  */
    LOAD = 306,                    /* LOAD  */
    DATA = 307,                    /* DATA  */
    INFILE = 308,                  /* INFILE  */
    EXPLAIN = 309,                 /* EXPLAIN  */
    EQ = 310,                      /* EQ  */
    LT = 311,                      /* LT  */
    GT = 312,                      /* GT  */
    LE = 313,                      /* LE  */
    GE = 314,                      /* GE  */
    NE = 315,                      /* NE  */
    EXISTS = 316,                  /* EXISTS  */
    NUMBER = 317,                  /* NUMBER  */
    FLOAT = 318,                   /* FLOAT  */
    ID = 319,                      /* ID  */
    SSS = 320,                     /* SSS  */
    DATESSS = 321,                 /* DATESSS  */
    UMINUS = 322                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 119 "yacc_sql.y"

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
  char *                            string;
  int                               number;
  float                             floats;

#line 158 "yacc_sql.hpp"

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
