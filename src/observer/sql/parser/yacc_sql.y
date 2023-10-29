
%{

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

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        NULLABLE
        IN
        IS
        OR
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        CALC
        SELECT
        AS
        DESC
        ASC
        ORDER
        BY
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        UNIQUE
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        DATE_T
        FLOAT_T
        TEXT
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        NULL_T
        INNER
        JOIN
        AND
        NOT
        LIKE
        MAX
        MIN
        SUM
        AVG
        COUNT
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        EQ
        LT
        GT
        LE
        GE
        NE
        EXISTS


/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
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
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
%token <string> DATESSS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <condition>           condition
%type <value>               value
%type <record>              record
%type <number>              number
%type <comp>                comp_op
%type <aggr>                aggr_func;
%type <rel_attr>            rel_attr
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <record_list>         record_list
%type <condition_list>      where
%type <condition_list>      condition_list
%type <condition_list>      on
%type <join_lists>          join_list
%type <rel_attr_list>       select_attr
%type <relation_list>       rel_list
%type <rel_name>            rel
%type <index_attr_list>     id_list
%type <string>              id
%type <order_by>            order_by_list
%type <order_by>            opt_order_by
%type <order_by_node>       order_by_unit
%type <attr_name_a_values>  update_options
%type <attr_name_value>     update_option
%type <rel_attr_list>       attr_list
%type <expression>          expression
%type <expression_list>     expression_list
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sub_sql_node>        sub_select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands

%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE id id_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;
      //create_index.attribute_name = $7
      std::vector<std::string> *src_attrs = $8;
      if (src_attrs != nullptr) {
        create_index.attribute_name.swap(*src_attrs);
      }
      std::string temp = $7;
      create_index.attribute_name.emplace_back(temp);
      std::reverse(create_index.attribute_name.begin(), create_index.attribute_name.end());
      delete $7;
    
      create_index.unique = false;
      free($3);
      free($5);
      //free($7);
    }
    | CREATE UNIQUE INDEX ID ON ID LBRACE id id_list RBRACE 
		{
			$$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $4;
      create_index.relation_name = $6;
      //create_index.attribute_name = $7
      std::vector<std::string> *src_attrs = $9;
      if (src_attrs != nullptr) {
      create_index.attribute_name.swap(*src_attrs);
      }
      std::string temp = $8;
      create_index.attribute_name.push_back(temp);
      std::reverse(create_index.attribute_name.begin(), create_index.attribute_name.end());//保持顺序
      delete $8;
      create_index.unique = true;
      free($4);
      free($6);
      //free($8);
      
		}
    ;

id_list:
		 /* empty */
    {
      $$ = nullptr;
    }
    | COMMA id id_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::string>;
      }
      $$->push_back($2);
      delete $2;
    }
id:
	ID 
	{

		$$ = $1;
    //free($1);
	}
	;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE 
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      //$$->nullable = false;
      free($1);
    }
    | ID type LBRACE number RBRACE NOT NULL_T
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->nullable = false;
      free($1);
    }
    | ID type LBRACE number RBRACE NULL_T
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->nullable = true;
      free($1);
    }
    | ID type NOT NULL_T
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      //$$->nullable = true;
      $$->nullable = false;
      free($1);
    }
    | ID type NULL_T
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->nullable = true;
      free($1);
    }
    | ID TEXT
    {
      $$ = new AttrInfoSqlNode;
      $$->type = CHARS;
      $$->name = $1;
      $$->length = 65535;
      free($1);
    }
    | ID type
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      //$$->nullable = false;
      free($1);
    }
    ;
number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$=INTS; }
    | STRING_T { $$=CHARS; }
    | FLOAT_T  { $$=FLOATS; }
    | DATE_T   { $$=DATES; }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES record record_list 
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($6 != nullptr) {
        $$->insertion.valuerecords.swap(*$6);
      }
      $$->insertion.valuerecords.emplace_back(*$5);
      std::reverse($$->insertion.valuerecords.begin(), $$->insertion.valuerecords.end());
      delete $5;
      free($3);
    }
    ;

record_list:
    /* empty */
    {
      $$ =  nullptr;
    }
    | COMMA record record_list {
        if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<ValueRecord>;
      }
      ValueRecord current;
      current.values.swap(*$2);
      $$->push_back(current);
      //$$->emplace_back(*$2);
      free($2);
    }

record:
    LBRACE value value_list RBRACE {
        if ($3 != nullptr) {
          $$ = $3;
        }else {
          $$ = new std::vector<Value>;
        }
        //Record current;
        //current.values.swap(*$2);
        //$$->push_back(current);
        $$->emplace_back(*$2);
        std::reverse($$->begin(), $$->end());
        delete $2;
    }

value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA value value_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    | NULL_T{ //要放到SSS的前面
      //char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(0);
      $$->set_null_value();
      //free(tmp);
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
    }
    |DATESSS {
			char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(1, tmp);
      free(tmp);
		}
   
    ;
    
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions.swap(*$4);
        delete $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET update_option update_options where 
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;

      std::vector<SetVariableSqlNode> u_list;
      if($5!=nullptr){
          u_list.swap(*$5);
          delete $5;
      }
      u_list.push_back(*$4);
      for(int i = u_list.size(); i > 0 ;i--)
      {
        $$->update.attribute_name.push_back(u_list[i-1].name);
        if(u_list[i-1].type == 0){
          value_list temp;
          temp.type = 0;
          temp.value = u_list[i-1].value;
          $$->update.values.push_back(temp);
        }
        else{
          value_list temp;
          temp.type = 1;
          temp.sub_query = u_list[i-1].query;
          $$->update.values.push_back(temp);
        }
      }
      //delete u_list;
     
      if ($6 != nullptr) {
        $$->update.conditions.swap(*$6);
        delete $6;
      }
      free($2);
      free($4);
    }
    ;
update_options:
		/* EMPTY */
    {
      $$ = nullptr;
    }
		| COMMA update_option update_options {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<SetVariableSqlNode>;
      }
      $$->emplace_back(*$2);
       delete $2;
		};
update_option:
		ID EQ value {
    	$$ = new SetVariableSqlNode();
      $$->value = *$3;
      $$->name = $1;
      $$->type = 0;
      free($1);
      free($3);
		}
    | ID EQ sub_select_stmt {
    	$$ = new SetVariableSqlNode();
      $$->query = $3;
      $$->name = $1;
      $$->type = 1;
      free($1);
		}
    ;


select_stmt:        /*  select 语句的语法解析树*/
    SELECT select_attr FROM rel rel_list join_list where opt_order_by
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.attributes.swap(*$2);
        delete $2;
      }
      if ($5 != nullptr) {
        $$->selection.relations.swap(*$5);
        delete $5;
      }
      $$->selection.relations.push_back(*$4);
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());
      if ($6 != nullptr) {
        $$->selection.joinTables.swap(*$6);
        delete $6;
        std::reverse($$->selection.joinTables.begin(), $$->selection.joinTables.end());
      }
      if ($8 != nullptr) {
        $$->selection.orderBy.swap(*$8);
        delete $8;
      }

      if ($7 != nullptr) {
        $$->selection.conditions.swap(*$7);
        delete $7;
      }
      free($4);
    }
    ;

rel://这个是返回表名结构体的语法
  ID ID 
  {
    $$ = new RelName();
    $$->relation = $1;
    $$->alias = $2;
    free($1);
    free($2);
  }
  | ID
  {
    $$ = new RelName();
    $$->relation = $1;
    free($1);
  }
  | ID AS ID 
  {
    $$ = new RelName();
    $$->relation = $1;
    $$->alias = $3;
    free($1);
    free($3);
  }
  ;

opt_order_by:
    {
      $$ = nullptr;
    }
    | ORDER BY order_by_unit order_by_list{
        if($4!=nullptr){
          $$ = $4;
        }
        else{
          $$ = new std::vector<OrderBySqlNode>;
        }
        $$->emplace_back(*$3);
        delete $3;
        std::reverse($$->begin(),$$->end());
    };

order_by_list:
    {
      $$ = nullptr;
    }
    | COMMA order_by_unit order_by_list
    {
        if($3!=nullptr){
          $$ = $3;
        }
        else{
          $$ = new std::vector<OrderBySqlNode>;
        }
        $$->emplace_back(*$2);
        delete $2;
    };

order_by_unit:
  ID
	{
      $$ = new OrderBySqlNode();
      $$->field = $1;
      //$$->order_relation = NULL;
	}
	|
	ID DOT ID
	{
		  $$ = new OrderBySqlNode();
      $$->field = $3;
      $$->order_relation = $1;
	}
	|
	ID DESC
	{
      $$ = new OrderBySqlNode();
      $$->field = $1;
      //$$->order_relation = NULL;
      $$->asc_type = false;
	}
	|
	ID ASC
	{
      $$ = new OrderBySqlNode();
      $$->field = $1;
      //$$->order_relation = NULL;
	}
	|
	ID DOT ID DESC
	{
      $$ = new OrderBySqlNode();
      $$->field = $3;
      $$->order_relation = $1;
      $$->asc_type = false;
	}
	|
	ID DOT ID ASC
	{
		  $$ = new OrderBySqlNode();
      $$->field = $3;
      $$->order_relation = $1;
	}
	;



sub_select_stmt:        /*  select 语句的语法解析树*/
    LBRACE SELECT select_attr FROM rel rel_list where RBRACE
    {
      $$ = new SelectSqlNode;
      if ($3 != nullptr) {
        $$->attributes.swap(*$3);
        delete $3;
      }
      if ($6 != nullptr) {
        $$->relations.swap(*$6);
        delete $6;
      }
      $$->relations.push_back(*$5);
      std::reverse($$->relations.begin(), $$->relations.end());

      if ($7 != nullptr) {
        $$->conditions.swap(*$7);
        delete $7;
      }
      free($5);
    }
    ;
calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      std::reverse($2->begin(), $2->end());
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression
    {
      $$ = new std::vector<Expression*>;
      $$->emplace_back($1);
    }
    | expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Expression *>;
      }
      $$->emplace_back($1);
    }
    ;
expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    ;

select_attr:
    '*' {
      $$ = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      attr.aggr_func = UNKNOWN;
      $$->emplace_back(attr);
    }
    | rel_attr attr_list {
      if ($2 != nullptr) {
        $$ = $2;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
aggr_func:
    MAX { $$=MAXF; }
	  | MIN { $$=MINF; }
	  | COUNT { $$=COUNTF; }
	  | AVG { $$=AVGF; }
	  | SUM { $$=SUMF; }
    ;
rel_attr:
    ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      $$->aggr_func = UNKNOWN;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      $$->aggr_func = UNKNOWN;
      free($1);
      free($3);
    }
    | aggr_func LBRACE '*' RBRACE {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = "*";
      $$->aggr_func = $1;
    }
    | aggr_func LBRACE ID RBRACE {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $3;
      $$->aggr_func = $1;
      free($3);
    }
    | aggr_func LBRACE ID DOT ID RBRACE {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $3;
      $$->attribute_name = $5;
      $$->aggr_func = $1;
      free($3);
      free($5);
    }//这后面是带别名的
     | ID AS ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      $$->aggr_func = UNKNOWN;
      $$->alias = $3;
      free($3);
      free($1);
    }
    | ID DOT ID AS ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      $$->aggr_func = UNKNOWN;
      $$->alias = $5;
      free($1);
      free($3);
      free($5);
    }
    | aggr_func LBRACE '*' RBRACE AS ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = "*";
      $$->aggr_func = $1;
      $$->alias = $6;
      free($6);
    }
    | aggr_func LBRACE ID RBRACE AS ID{
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $3;
      $$->aggr_func = $1;
       $$->alias = $6;
       free($6);
      free($3);
    }
    | aggr_func LBRACE ID DOT ID RBRACE AS ID{
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $3;
      $$->attribute_name = $5;
      $$->aggr_func = $1;
      $$->alias = $8;
      free($8);
      free($3);
      free($5);
    }
    ;

attr_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA rel_attr attr_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }

      $$->emplace_back(*$2);
      delete $2;
    }
    ;

rel_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA rel rel_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<RelName>;
      }

      $$->push_back(*$2);//本来是字符串char* 所以这里要加*
      free($2);
    }
    ;
join_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | INNER JOIN rel on join_list{
      if ($5 != nullptr) {
        $$ = $5;
      } else {
        $$ = new std::vector<InnerJoinSqlNode>;
      }
      InnerJoinSqlNode current;
      current.join_relations = *$3;
      current.join_conditions.swap(*$4);
      $$->push_back(current);

      free($3);
      free($4);
    }
    ;
on:
    /* empty */
    {
      $$ = nullptr;
    }
    | ON condition_list {
      $$ = $2;  
    }
    ;
where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;  
    }
    ;
condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $1->conjunction = 0;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition OR condition_list {
      $$ = $3;
      $1->conjunction = 1;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
condition:
    rel_attr comp_op value
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op value 
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | rel_attr comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
  
    | sub_select_stmt comp_op sub_select_stmt
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = -1;
      $$->left_sql = $1;
      $$->right_is_attr = -1;
      $$->right_sql = $3;
      $$->comp = $2;

    }
    | rel_attr comp_op sub_select_stmt
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = -1;
      $$->right_sql = $3;
      $$->comp = $2;

      delete $1;
    }
    | sub_select_stmt comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = -1;
      $$->left_sql = $1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $3;
    }
    | value comp_op sub_select_stmt
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = -1;
      $$->right_sql = $3;
      $$->comp = $2;

      delete $1;
    }
    | sub_select_stmt comp_op value
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = -1;
      $$->left_sql = $1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $3;
    }
    | rel_attr comp_op LBRACE value value_list RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 3;
      if ($5 != nullptr) {
        $$->right_list.swap(*$5);
      }
      $$->right_list.emplace_back(*$4);
      std::reverse($$->right_list.begin(), $$->right_list.end());
      $$->comp = $2;

      delete $1;
    }
    | comp_op sub_select_stmt
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 2;
      $$->right_is_attr = -1;
      $$->right_sql = $2;
      $$->comp = $1;
    }
    | rel_attr comp_op
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 2;
      $$->comp = $2;
    }
    | value comp_op
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 2;
      $$->comp = $2;
    }
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE { $$ = REGEX_LIKE; }
    | NOT LIKE { $$ = REGEX_NOT_LIKE; }
    | IN { $$ = IN_QUERY; }
    | IS NULL_T{ $$ = IS_NULL; }
    | IS NOT NULL_T{ $$ = IS_NOT_NULL; }
    | NOT IN { $$ = NOT_IN_QUERY; }
    | EXISTS { $$ = EXISTS_QUERY; }
    | NOT EXISTS { $$ = NOT_EXISTS_QUERY; }
    ;

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
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
