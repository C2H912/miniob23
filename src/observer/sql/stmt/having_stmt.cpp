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
#include "sql/stmt/having_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

HavingStmt::~HavingStmt()
{
  for (HavingUnit *unit : having_units_) {
    delete unit;
  }
  having_units_.clear();
}

RC HavingStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode *conditions, int condition_num, HavingStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  HavingStmt *tmp_stmt = new HavingStmt();
  for (int i = 0; i < condition_num; i++) {
    HavingUnit *having_unit = nullptr;
    rc = create_filter_unit(db, default_table, tables, conditions[i], having_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->having_units_.push_back(having_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC having_get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
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

RC having_filter_dfs(Expression* current, Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables)
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
    RC rc = having_get_table_and_field(db, default_table, tables, node, table, field, temp);
    if(rc != RC::SUCCESS){
      return rc;
    }
    fieldnode->set_field(temp);
    return RC::SUCCESS;
  }
  //计算节点
  ALUExpr* arithnode = static_cast<ALUExpr*>(current);
  if(arithnode->left() != nullptr){
    RC rc = having_filter_dfs(arithnode->left(), db, default_table, tables);
    if(rc != RC::SUCCESS){
      return rc;
    }
  }
  if(arithnode->right() != nullptr){
    RC rc = having_filter_dfs(arithnode->right(), db, default_table, tables);
    if(rc != RC::SUCCESS){
      return rc;
    }
  }
  return RC::SUCCESS;
}

RC HavingStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode &condition, HavingUnit *&having_unit)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  having_unit = new HavingUnit;
  
  //left expression
  rc = having_filter_dfs(condition.left_expr, db, default_table, tables);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot find attr or invalid value");
    return rc;
  }
  HavingObj left_having_obj;
  left_having_obj.init_expr(condition.left_expr);
  having_unit->set_left(left_having_obj);

  //right expression
  rc = having_filter_dfs(condition.right_expr, db, default_table, tables);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot find attr");
    return rc;
  }
  HavingObj right_having_obj;
  right_having_obj.init_expr(condition.right_expr);
  having_unit->set_right(right_having_obj);

  having_unit->set_comp(comp);

  return rc;
}