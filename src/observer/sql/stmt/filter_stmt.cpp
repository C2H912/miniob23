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
// Created by Wangyunlai on 2022/5/22.
//

#include "common/rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc = create_filter_unit(db, default_table, tables, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,std::unordered_map<std::string, Table *> *alias_tables,
    const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc = create_filter_unit(db, default_table, tables, alias_tables,conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC filter_get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field, Field &output_field)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) { //这里用到了 在表中找匹配的表
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  output_field.set_field(field);
  output_field.set_table(table);

  return RC::SUCCESS;
}


RC filter_get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,std::unordered_map<std::string, Table *> *alias_tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field, Field &output_field)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) { //这里用到了 在表中找匹配的表
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  output_field.set_field(field);
  output_field.set_table(table);

  return RC::SUCCESS;
}


RC filter_dfs(Expression* current, Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables)
{
  //终止节点
  if(current->type() == ExprType::VALUE){
    if(current->value_type() == UNDEFINED){
      LOG_WARN("attr_type invalid");
      return RC::INVALID_ARGUMENT;
    }
    return RC::SUCCESS;
  }
  else if(current->type() == ExprType::FIELD){
    FieldExpr* fieldnode = static_cast<FieldExpr*>(current);
    RelAttrSqlNode node;
    if(fieldnode->str_table_name().empty()){
      node.relation_name = default_table->name();
      fieldnode->set_table_name(default_table->name());
    }
    else{
      node.relation_name = fieldnode->str_table_name();
    }
    node.attribute_name = fieldnode->str_attribute_name();
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    Field temp;
    RC rc = filter_get_table_and_field(db, default_table, tables, node, table, field, temp);
    if(rc != RC::SUCCESS){
      return rc;
    }
    fieldnode->set_field(temp);
    return RC::SUCCESS;
  }
  //计算节点
  ALUExpr* arithnode = static_cast<ALUExpr*>(current);
  if(arithnode->left() != nullptr){
    RC rc = filter_dfs(arithnode->left(), db, default_table, tables);
    if(rc != RC::SUCCESS){
      return rc;
    }
  }
  if(arithnode->right() != nullptr){
    RC rc = filter_dfs(arithnode->right(), db, default_table, tables);
    if(rc != RC::SUCCESS){
      return rc;
    }
  }
  return RC::SUCCESS;
}



RC filter_dfs(Expression* current, Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables ,std::unordered_map<std::string, Table *> *alias_tables)
{
  //终止节点
  if(current->type() == ExprType::VALUE){
    if(current->value_type() == UNDEFINED){
      LOG_WARN("attr_type invalid");
      return RC::INVALID_ARGUMENT;
    }
    return RC::SUCCESS;
  }
  else if(current->type() == ExprType::FIELD){
    FieldExpr* fieldnode = static_cast<FieldExpr*>(current);
    RelAttrSqlNode node;
    if(fieldnode->str_table_name().empty()){
      node.relation_name = default_table->name();
      fieldnode->set_table_name(default_table->name());
    }
    else{
      node.relation_name = fieldnode->str_table_name();
    }
    node.attribute_name = fieldnode->str_attribute_name();
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    Field temp;
    RC rc = filter_get_table_and_field(db, default_table, tables,alias_tables, node, table, field, temp);
    if(rc != RC::SUCCESS){
      return rc;
    }
    fieldnode->set_field(temp);
    return RC::SUCCESS;
  }
  //计算节点
  ALUExpr* arithnode = static_cast<ALUExpr*>(current);
  if(arithnode->left() != nullptr){
    RC rc = filter_dfs(arithnode->left(), db, default_table, tables);
    if(rc != RC::SUCCESS){
      return rc;
    }
  }
  if(arithnode->right() != nullptr){
    RC rc = filter_dfs(arithnode->right(), db, default_table, tables);
    if(rc != RC::SUCCESS){
      return rc;
    }
  }
  return RC::SUCCESS;
}


RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,std::unordered_map<std::string, Table *> *alias_tables,
    const ConditionSqlNode &condition, FilterUnit *&filter_unit)
{  //这里才是现在走的函数
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) { //操作符无效
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  filter_unit = new FilterUnit;
  // std::unordered_map<std::string,Table*> sons;
 
  //   for(std::pair<std::string, Table *> it : *tables){
  //   sons.insert(it);
  // }
  // for(std::pair<std::string, Table *> it : *alias_tables){
  //   sons.insert(it);
  // }
  
  //expression
  if (condition.left_is_attr == 0) {
    rc = filter_dfs(condition.left_expr, db, default_table, tables);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr or invalid value");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_expr(condition.left_expr);
    filter_unit->set_left(filter_obj);
  //sub_query
  } else if (condition.left_is_attr == 1) {
    //递归地调用create生成子查询
    Stmt *sub_stmt;
    SelectStmt *caller;   //无实质内容，只为了调用一个select的create方法，把create的结果存到sub_stmt中
    rc = caller->create(db, *condition.left_sql, sub_stmt, *tables);
    if(rc != RC::SUCCESS){
      LOG_WARN("sub create stmt fail");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_stmt(static_cast<SelectStmt*>(sub_stmt));
    filter_unit->set_left(filter_obj);
  }
  //exists的左边,无
  else{
    FilterObj filter_obj;
    filter_obj.set_nothing_here();
    filter_unit->set_left(filter_obj);
  }

  //expression
  if (condition.right_is_attr == 0) {
    rc = filter_dfs(condition.right_expr, db, default_table, tables);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_expr(condition.right_expr);
    filter_unit->set_right(filter_obj);
  } 
  //sub_query
  else if (condition.right_is_attr == 1) {
    //递归地调用create生成子查询
    Stmt *sub_stmt;
    SelectStmt *caller;   //无实质内容，只为了调用一个select的create方法，把create的结果存到sub_stmt中
    rc = caller->create(db, *condition.right_sql, sub_stmt, *tables);
    if(rc != RC::SUCCESS){
      LOG_WARN("sub create stmt fail");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_stmt(static_cast<SelectStmt*>(sub_stmt));
    filter_unit->set_right(filter_obj);
  }
  //valueList
  else if (condition.right_is_attr == 2) {
    FilterObj filter_obj;
    filter_obj.init_value_list(condition.right_list);
    filter_unit->set_right(filter_obj);
  }
  //is null的右边
  else {
    FilterObj filter_obj;
    filter_obj.set_nothing_here();
    filter_unit->set_right(filter_obj);
  }

  filter_unit->set_comp(comp);

  // 检查两个类型是否能够比较
  return rc;
}


RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) { //操作符无效
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  filter_unit = new FilterUnit;
  
  //expression
  if (condition.left_is_attr == 0) {
    rc = filter_dfs(condition.left_expr, db, default_table, tables);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr or invalid value");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_expr(condition.left_expr);
    filter_unit->set_left(filter_obj);
  //sub_query
  } else if (condition.left_is_attr == 1) {
    //递归地调用create生成子查询
    Stmt *sub_stmt;
    SelectStmt *caller;   //无实质内容，只为了调用一个select的create方法，把create的结果存到sub_stmt中
    rc = caller->create(db, *condition.left_sql, sub_stmt, *tables);
    if(rc != RC::SUCCESS){
      LOG_WARN("sub create stmt fail");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_stmt(static_cast<SelectStmt*>(sub_stmt));
    filter_unit->set_left(filter_obj);
  }
  //exists的左边,无
  else{
    FilterObj filter_obj;
    filter_obj.set_nothing_here();
    filter_unit->set_left(filter_obj);
  }

  //expression
  if (condition.right_is_attr == 0) {
    rc = filter_dfs(condition.right_expr, db, default_table, tables);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_expr(condition.right_expr);
    filter_unit->set_right(filter_obj);
  } 
  //sub_query
  else if (condition.right_is_attr == 1) {
    //递归地调用create生成子查询
    Stmt *sub_stmt;
    SelectStmt *caller;   //无实质内容，只为了调用一个select的create方法，把create的结果存到sub_stmt中
    rc = caller->create(db, *condition.right_sql, sub_stmt, *tables);
    if(rc != RC::SUCCESS){
      LOG_WARN("sub create stmt fail");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_stmt(static_cast<SelectStmt*>(sub_stmt));
    filter_unit->set_right(filter_obj);
  }
  //valueList
  else if (condition.right_is_attr == 2) {
    FilterObj filter_obj;
    filter_obj.init_value_list(condition.right_list);
    filter_unit->set_right(filter_obj);
  }
  //is null的右边
  else {
    FilterObj filter_obj;
    filter_obj.set_nothing_here();
    filter_unit->set_right(filter_obj);
  }

  filter_unit->set_comp(comp);

  // 检查两个类型是否能够比较
  return rc;
}

// RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,std::unordered_map<std::string, Table *> *alias_tables,
//     const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field)
// {
//   if (common::is_blank(attr.relation_name.c_str())) {
//     table = default_table;
//   } else if (nullptr != tables) { //这里用到了 在表中找匹配的表
//     auto iter = tables->find(attr.relation_name);
//     if (iter != tables->end()) {
//       table = iter->second;
//     }else if(nullptr != alias_tables){
//       auto iter2 = alias_tables->find(attr.relation_name);//在别名中找对比
//       if (iter2 != alias_tables->end()) {
//       table = iter2->second;
//     }
//     }
   
//   } else {
//     table = db->find_table(attr.relation_name.c_str());
//   }
//   if (nullptr == table) {
//     LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
//     return RC::SCHEMA_TABLE_NOT_EXIST;
//   }

//   field = table->table_meta().field(attr.attribute_name.c_str());
//   if (nullptr == field) {
//     LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
//     table = nullptr;
//     return RC::SCHEMA_FIELD_NOT_EXIST;
//   }

//   return RC::SUCCESS;
// }







// RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,std::unordered_map<std::string, Table *> *alias_tables,
//     const ConditionSqlNode &condition, FilterUnit *&filter_unit)
// {
//   RC rc = RC::SUCCESS;

//   CompOp comp = condition.comp;
//   if (comp < EQUAL_TO || comp >= NO_OP) { //操作符无效
//     LOG_WARN("invalid compare operator : %d", comp);
//     return RC::INVALID_ARGUMENT;
//   }

//   filter_unit = new FilterUnit;
  
//   if (condition.left_is_attr == 1) {
//     Table *table = nullptr;
//     const FieldMeta *field = nullptr;
//     rc = get_table_and_field(db, default_table, tables,alias_tables, condition.left_attr, table, field);
//     if (rc != RC::SUCCESS) {
//       LOG_WARN("cannot find attr");
//       return rc;
//     }
//     FilterObj filter_obj;
//     filter_obj.init_attr(Field(table, field));
//     filter_unit->set_left(filter_obj);
//   } else if (condition.left_is_attr == 0) {
//     if(condition.left_value.attr_type() == UNDEFINED){
//       LOG_WARN("attr_type invalid");
//       return RC::INVALID_ARGUMENT;
//     }
//     FilterObj filter_obj;
//     filter_obj.init_value(condition.left_value);
//     filter_unit->set_left(filter_obj);
//   }
//   else if (condition.left_is_attr == -1){
//     //递归地调用create生成子查询
//     Stmt *sub_stmt;
//     SelectStmt *caller;   //无实质内容，只为了调用一个select的create方法，把create的结果存到sub_stmt中
//     std::unordered_map<std::string,Table*> sons;
//     //std::unordered_map<std::string, Table *> all_parents = table_map;
//     for(std::pair<std::string, Table *> it : *tables){
//     sons.insert(it);
//   }
//   for(std::pair<std::string, Table *> it : *alias_tables){
//     sons.insert(it);
//   }
//     rc = caller->create(db, *condition.left_sql, sub_stmt, *tables);//
//     if(rc != RC::SUCCESS){
//       LOG_WARN("sub create stmt fail");
//       return rc;
//     }
//     FilterObj filter_obj;
//     filter_obj.init_stmt(static_cast<SelectStmt*>(sub_stmt));
//     filter_unit->set_left(filter_obj);
//   }
//   else{
//     //exists的左边,无
//   }

//   if (condition.right_is_attr == 1) {
//     Table *table = nullptr;
//     const FieldMeta *field = nullptr;
//     rc = get_table_and_field(db, default_table, tables,alias_tables, condition.right_attr, table, field);
//     if (rc != RC::SUCCESS) {
//       LOG_WARN("cannot find attr");
//       return rc;
//     }
//     FilterObj filter_obj;
//     filter_obj.init_attr(Field(table, field));
//     filter_unit->set_right(filter_obj);
//   } 
//   else if (condition.right_is_attr == 0) {
//     if(condition.right_value.attr_type() == UNDEFINED){
//       LOG_WARN("attr_type invalid");
//       return RC::INVALID_ARGUMENT;
//     }
//     FilterObj filter_obj;
//     filter_obj.init_value(condition.right_value);
//     filter_unit->set_right(filter_obj);
//   }
//   else if (condition.right_is_attr == -1) {
//     //递归地调用create生成子查询
//     Stmt *sub_stmt;
//     SelectStmt *caller;   //无实质内容，只为了调用一个select的create方法，把create的结果存到sub_stmt中
//     std::unordered_map<std::string,Table*> sons;
//     //std::unordered_map<std::string, Table *> all_parents = table_map;
//     for(std::pair<std::string, Table *> it : *tables){
//     sons.insert(it);
//   }
//   for(std::pair<std::string, Table *> it : *alias_tables){
//     sons.insert(it);
//   }
//     rc = caller->create(db, *condition.right_sql, sub_stmt, *tables);
//     if(rc != RC::SUCCESS){
//       LOG_WARN("sub create stmt fail");
//       return rc;
//     }
//     FilterObj filter_obj;
//     filter_obj.init_stmt(static_cast<SelectStmt*>(sub_stmt));
//     filter_unit->set_right(filter_obj);
//   }
//   else if (condition.right_is_attr == 3) {
//     FilterObj filter_obj;
//     filter_obj.init_value_list(condition.right_list);
//     filter_unit->set_right(filter_obj);
//   }
//   else {
//     //无
//   }

//   filter_unit->set_comp(comp);

//   // 检查两个类型是否能够比较
//   return rc;
// }