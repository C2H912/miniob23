/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/6/6.
//
// #define DEFER_WHEN_NOT_NULL(ptr) \
//   DEFER([ptr]() {                \
//     if (nullptr != (ptr)) {      \
//       delete (ptr);              \
//     }                            \
//   });


#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/stmt/order_by_stmt.h"



SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num()- table_meta.extra_filed_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

#if 0
RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt,std::unordered_map<std::string,Table* > parents)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

// ---------- collect tables in `from` statement ----------
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  //位于from里的所有表
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }
  //位于join里的所有表
  for(int i = 0; i < (int)select_sql.joinTables.size(); i++){
    InnerJoinSqlNode temp_node = select_sql.joinTables[i];
    const char *table_name = temp_node.join_relations.c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }

// ---------- collect query fields in `select` statement ----------
  std::vector<Field> query_fields;
  std::vector<AggrOp> aggr_fields;
  std::vector<std::string> aggr_specs;

  const RelAttrSqlNode &relation_attr = select_sql.attributes[static_cast<int>(select_sql.attributes.size()) - 1];
  AggrOp aggr_flag = relation_attr.aggr_func;   //是否带有聚合

  for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
    const RelAttrSqlNode &relation_attr = select_sql.attributes[i];
    
  //1. 检查聚合的语法

    //要么全部都是聚合或者全部都不是聚合
    if(aggr_flag == UNKNOWN){
      if(relation_attr.aggr_func != UNKNOWN){
        LOG_WARN("ID, AGGR(ID) is not allowed.");
        return RC::INVALID_ARGUMENT;
      }
    }
    else{
      if(relation_attr.aggr_func == UNKNOWN){
        LOG_WARN("ID, AGGR(ID) is not allowed.");
        return RC::INVALID_ARGUMENT;
      }
      //检查是否会出现max(*)这种错误语法
      if(relation_attr.aggr_func != COUNTF && (relation_attr.attribute_name == "*")){
        LOG_WARN("MAX(*)/MIN(*)/AVG(*)/SUM(*) is not allowed.");
        return RC::INVALID_ARGUMENT;
      }
    }

  //2. 创建stmt

    if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
      for (Table *table : tables) {
        if(relation_attr.aggr_func != UNKNOWN){
          query_fields.push_back(Field(table, table->table_meta().field(0)));
        }
        else{
          wildcard_fields(table, query_fields);
        }
      }
      aggr_specs.push_back("*");

    } else if (!common::is_blank(relation_attr.relation_name.c_str())) {
      const char *table_name = relation_attr.relation_name.c_str();
      const char *field_name = relation_attr.attribute_name.c_str();

      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        for (Table *table : tables) {
          if(relation_attr.aggr_func != UNKNOWN){
            query_fields.push_back(Field(table, table->table_meta().field(0)));
          }
          else{
            wildcard_fields(table, query_fields);
          }
        }
        aggr_specs.push_back("*");
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          if(relation_attr.aggr_func != UNKNOWN){
            query_fields.push_back(Field(table, table->table_meta().field(0)));
          }
          else{
            wildcard_fields(table, query_fields);
          }
          aggr_specs.push_back("*");
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          query_fields.push_back(Field(table, field_meta));
          aggr_specs.push_back(relation_attr.attribute_name);
        }
      }
    } else {
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table *table = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      query_fields.push_back(Field(table, field_meta));
      aggr_specs.push_back(relation_attr.attribute_name);
    }
    aggr_fields.push_back(relation_attr.aggr_func);
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

// ---------- create filter statement in `where` statement ----------
  FilterStmt *filter_stmt = nullptr;
  std::vector<ConditionSqlNode> all_filters;
  int conjunction_flag = -1;
  //conjunction flag
  if((int)select_sql.conditions.size() > 1){
    conjunction_flag = select_sql.conditions[1].conjunction;
  }
  //一般的where条件
  for(size_t i = 0; i < select_sql.conditions.size(); i++){
    all_filters.push_back(select_sql.conditions[i]);
  }
  //join里面的on条件
  for(size_t i = 0; i < select_sql.joinTables.size(); i++){
    for(size_t j = 0; j < select_sql.joinTables[i].join_conditions.size(); j++){
      all_filters.push_back(select_sql.joinTables[i].join_conditions[j]);
    }
  }
  //检查复杂子查询中是否有此父表
  std::unordered_map<std::string, Table *> all_parents = table_map;
  for(std::pair<std::string, Table *> it : parents){
    all_parents.insert(it);
  }
  RC rc = FilterStmt::create(db,
      default_table,
      &all_parents,
      all_filters.data(),
      static_cast<int>(all_filters.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  OrderByStmt *orderby_stmt = nullptr;
  //DEFER_WHEN_NOT_NULL(orderby_stmt);//在离开作用域时，检查orderby_stmt,如果不为空 delete
  if (0 != select_sql.orderBy.size()) {
    rc = OrderByStmt::create(db, default_table, &table_map, select_sql.orderBy, select_sql.orderBy.size(), orderby_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct order by stmt");
      return rc;
    }
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->aggr_fields_.swap(aggr_fields);
  select_stmt->aggr_specs_.swap(aggr_specs);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->conjunction_flag_ = conjunction_flag;
  select_stmt->order_by_stmt_ = orderby_stmt;
  stmt = select_stmt;
  return RC::SUCCESS;
}
#endif

void dfs(Expression* current, std::vector<RelAttrSqlNode>& attr, std::vector<AggrOp>& aggre, 
         std::vector<Expression*>& aggr_node, std::string default_table_name)
{
  //终止节点
  if(current->type() == ExprType::VALUE){
    return;
  }
  else if(current->type() == ExprType::FIELD){
    FieldExpr* fieldnode = static_cast<FieldExpr*>(current);
    RelAttrSqlNode node;
    if(fieldnode->str_table_name().empty()){
      node.relation_name = default_table_name;
      fieldnode->set_table_name(default_table_name);
    }
    else{
      node.relation_name = fieldnode->str_table_name();
    }
    node.attribute_name = fieldnode->str_attribute_name();
    node.aggr_func = fieldnode->aggr_name();
    attr.push_back(node);
    return;
  }
  //聚合节点
  if(current->type() == ExprType::AGGRE){
    AggreExpr* aggrenode = static_cast<AggreExpr*>(current);
    if(aggrenode->child() != nullptr){
      aggre.push_back(aggrenode->aggre_type());
      aggr_node.push_back(current);
      dfs(aggrenode->child(), attr, aggre, aggr_node, default_table_name);
      return;
    }
  }
  //计算节点
  ALUExpr* arithnode = static_cast<ALUExpr*>(current);
  if(arithnode->left() != nullptr){
    dfs(arithnode->left(), attr, aggre, aggr_node, default_table_name);
  }
  if(arithnode->right() != nullptr){
    dfs(arithnode->right(), attr, aggre, aggr_node, default_table_name);
  }
}

//计算节点时必须根据field拿到这个属性的Attrtype，所以要遍历一遍赋值上field
void dfs_for_field(Expression* current, int &index, std::vector<Field> &fields)
{
  //终止节点
  if(current->type() == ExprType::VALUE){
    return;
  }
  else if(current->type() == ExprType::FIELD){
    FieldExpr* fieldnode = static_cast<FieldExpr*>(current);
    fieldnode->set_field(fields[index]);
    index++;
    return;
  }
  //聚合节点
  if(current->type() == ExprType::AGGRE){
    AggreExpr* aggrenode = static_cast<AggreExpr*>(current);
    if(aggrenode->child() != nullptr){
      dfs_for_field(aggrenode->child(), index, fields);
      return;
    }
  }
  //计算节点
  ALUExpr* arithnode = static_cast<ALUExpr*>(current);
  if(arithnode->left() != nullptr){
    dfs_for_field(arithnode->left(), index, fields);
  }
  if(arithnode->right() != nullptr){
    dfs_for_field(arithnode->right(), index, fields);
  }
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt,std::unordered_map<std::string,Table* > parents)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

// ---------- collect tables in `from` statement ----------
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  //位于from里的所有表
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }
  //位于join里的所有表
  for(int i = 0; i < (int)select_sql.joinTables.size(); i++){
    InnerJoinSqlNode temp_node = select_sql.joinTables[i];
    const char *table_name = temp_node.join_relations.c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }

// ---------- 首先通过深度优先搜索把expression树中的内容解析出来,并且为Field节点附上表名 ----------
  std::vector<RelAttrSqlNode> all_relAttrNodes;
  std::vector<Expression*> aggr_nodes;
  std::vector<AggrOp> all_aggres;
  for(size_t i = 0; i < select_sql.expressions.size(); i++){
    dfs(select_sql.expressions[i], all_relAttrNodes, all_aggres, aggr_nodes, tables[0]->name());
  }
  //特殊情况: 整个表达式只有一个*，即select * from a;
  bool is_star = false;
  if(0 == strcmp(all_relAttrNodes[0].attribute_name.c_str(), "*")){
    is_star = true;
  }
  //把expression树里的内容填入到select_sql，这里为了兼容以前写的
  /* 首先把聚合函数填入到RelAttrSqlNode，这里做出如下三个假设：
   *    1.聚合不会嵌套，即不会出现min(avg(id))
   *    2.每个聚合函数下面只有一个属性，即不会出现min(id+col)
   *    3.不会出现聚合与不聚合同时出现的情况，即不会出现select min(id),id from a;
   * 所以这里认为，all_relAttrNodes中的节点与all_aggres一一对应，直接把它们关联在一起，这样原本的聚合算子就不用
   * 改写了，当然如果要改写的话可以使用aggr_nodes，聚合算子的接口已经写好。
   * 
   * 目前只支持min(id)+max(col)这种，不支持min(id+1),max(col+id)这种
   */
  if((int)all_aggres.size() != 0){
    if((int)all_aggres.size() != (int)all_relAttrNodes.size()){
      LOG_WARN("ID, AGGR(ID) is not allowed.");
      return RC::INVALID_ARGUMENT;
    }
  }
  else{
    all_aggres.push_back(UNKNOWN);
  }
  select_sql.attributes = all_relAttrNodes;

// ---------- collect query fields in `select` statement ----------
  std::vector<Field> query_fields;
  std::vector<AggrOp> aggr_fields;
  std::vector<std::string> aggr_specs;

  //const RelAttrSqlNode &relation_attr = select_sql.attributes[0];
  //AggrOp aggr_flag = relation_attr.aggr_func;   //是否带有聚合

  for (int i = 0; i < (int)select_sql.attributes.size(); i++) {
    const RelAttrSqlNode &relation_attr = select_sql.attributes[i];
    
  //1. 检查聚合的语法
#if 0
    //要么全部都是聚合或者全部都不是聚合
    if(aggr_flag == UNKNOWN){
      if(relation_attr.aggr_func != UNKNOWN){
        LOG_WARN("ID, AGGR(ID) is not allowed.");
        return RC::INVALID_ARGUMENT;
      }
    }
    else{
      if(relation_attr.aggr_func == UNKNOWN){
        LOG_WARN("ID, AGGR(ID) is not allowed.");
        return RC::INVALID_ARGUMENT;
      }
      //检查是否会出现max(*)这种错误语法
      if(relation_attr.aggr_func != COUNTF && (relation_attr.attribute_name == "*")){
        LOG_WARN("MAX(*)/MIN(*)/AVG(*)/SUM(*) is not allowed.");
        return RC::INVALID_ARGUMENT;
      }
    }
#endif
  //2. 创建stmt

    if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
      for (Table *table : tables) {
        if(relation_attr.aggr_func != UNKNOWN){
          query_fields.push_back(Field(table, table->table_meta().field(0)));
        }
        else{
          wildcard_fields(table, query_fields);
        }
      }
      aggr_specs.push_back("*");

    } else if (!common::is_blank(relation_attr.relation_name.c_str())) {
      const char *table_name = relation_attr.relation_name.c_str();
      const char *field_name = relation_attr.attribute_name.c_str();

      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        for (Table *table : tables) {
          if(relation_attr.aggr_func != UNKNOWN){
            query_fields.push_back(Field(table, table->table_meta().field(0)));
          }
          else{
            wildcard_fields(table, query_fields);
          }
        }
        aggr_specs.push_back("*");
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          if(relation_attr.aggr_func != UNKNOWN){
            query_fields.push_back(Field(table, table->table_meta().field(0)));
          }
          else{
            wildcard_fields(table, query_fields);
          }
          aggr_specs.push_back("*");
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          query_fields.push_back(Field(table, field_meta));
          aggr_specs.push_back(relation_attr.attribute_name);
        }
      }
    } else {
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table *table = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      query_fields.push_back(Field(table, field_meta));
      aggr_specs.push_back(relation_attr.attribute_name);
    }
    aggr_fields.push_back(relation_attr.aggr_func);
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

// ---------- create filter statement in `where` statement ----------
  FilterStmt *filter_stmt = nullptr;
  std::vector<ConditionSqlNode> all_filters;
  int conjunction_flag = -1;
  //conjunction flag
  if((int)select_sql.conditions.size() > 1){
    conjunction_flag = select_sql.conditions[1].conjunction;
  }
  //一般的where条件
  for(size_t i = 0; i < select_sql.conditions.size(); i++){
    all_filters.push_back(select_sql.conditions[i]);
  }
  //join里面的on条件
  for(size_t i = 0; i < select_sql.joinTables.size(); i++){
    for(size_t j = 0; j < select_sql.joinTables[i].join_conditions.size(); j++){
      all_filters.push_back(select_sql.joinTables[i].join_conditions[j]);
    }
  }
  //检查复杂子查询中是否有此父表
  std::unordered_map<std::string, Table *> all_parents = table_map;
  for(std::pair<std::string, Table *> it : parents){
    all_parents.insert(it);
  }
  RC rc = FilterStmt::create(db,
      default_table,
      &all_parents,
      all_filters.data(),
      static_cast<int>(all_filters.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

// ---------- create filter statement in `order by` statement ----------
  OrderByStmt *orderby_stmt = nullptr;
  //DEFER_WHEN_NOT_NULL(orderby_stmt);//在离开作用域时，检查orderby_stmt,如果不为空 delete
  if (0 != select_sql.orderBy.size()) {
    rc = OrderByStmt::create(db, default_table, &table_map, select_sql.orderBy, select_sql.orderBy.size(), orderby_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct order by stmt");
      return rc;
    }
  }

// ---------------- everything alright ------------------

  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  //这里还得进行一次深度优先遍历，用于把query_fields中解析出来的属性对应的类型写入到expr树对应的Field中
  //否则运算时不知道类型
  int expr_index = 0;
  for(size_t i = 0; i < select_sql.expressions.size(); i++){
    dfs_for_field(select_sql.expressions[i], expr_index, select_stmt->query_fields_);
  }
  //
  select_stmt->aggr_fields_.swap(all_aggres);
  select_stmt->aggr_specs_.swap(aggr_specs);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->conjunction_flag_ = conjunction_flag;
  select_stmt->order_by_stmt_ = orderby_stmt;
  //放入聚合表达式
  //for (Expression * const expr : aggr_nodes) {
  //  select_stmt->aggr_expr_node_.emplace_back(expr);
  //}
  //放入表达式
  //特殊情况，如果一开始expresion是*，那么就要把expression替换为所有列的expression，
  //count(*)的情况不用担心，因为count(*)跟列没有任何关系，可以直接得到结果
  if(is_star == true){
    for(size_t i = 0; i < select_stmt->query_fields_.size(); i++){
      std::string tablename = select_stmt->query_fields_[i].table_name();
      std::string fieldname = select_stmt->query_fields_[i].field_name();
      FieldExpr *expr = new FieldExpr(tablename, fieldname, UNKNOWN);
      if(select_stmt->tables_.size() > 1){
        std::string s = tablename + "." + fieldname;
        expr->set_name(s);
      }
      else{
        expr->set_name(fieldname);
      }
      select_stmt->expressions_.emplace_back(expr);
    }
  }
  else{
    for (Expression * const expr : select_sql.expressions) {
      select_stmt->expressions_.emplace_back(expr);
    }
  }

  stmt = select_stmt;
  return RC::SUCCESS;
}