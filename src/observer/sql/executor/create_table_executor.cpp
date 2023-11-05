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
// Created by Wangyunlai on 2023/6/13.
//

#include "sql/executor/create_table_executor.h"

#include "session/session.h"
#include "common/log/log.h"
#include "storage/table/table.h"
#include "sql/stmt/create_table_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "storage/db/db.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"

RC CreateTableExecutor::execute(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;

  Stmt *stmt = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::CREATE_TABLE, 
         "create table executor can not run this command: %d", static_cast<int>(stmt->type()));

  CreateTableStmt *create_table_stmt = static_cast<CreateTableStmt *>(stmt);

  if(create_table_stmt->is_create_select() == true){
  //---------- 生成select火山 ----------
    LogicalPlanGenerator not_used;
    std::unique_ptr<LogicalOperator> logical_operator;
    SelectStmt *select_stmt = create_table_stmt->select_table();
    rc = not_used.create_plan(select_stmt, logical_operator);
    if (rc != RC::SUCCESS) {
      if (rc != RC::UNIMPLENMENT) {
        LOG_WARN("failed to create logical plan. rc=%s", strrc(rc));
      }
      return rc;
    }
    PhysicalPlanGenerator not_used2;
    std::unique_ptr<PhysicalOperator> physical_operator;
    rc = not_used2.create(*logical_operator, physical_operator);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to generate physical plan. rc=%s", strrc(rc));
      return rc;
    }

  //---------- 执行select火山获得表 ----------
    std::vector<std::vector<Value>> sub_table;
    if(physical_operator){
      rc = RC::SUCCESS;
      //把子表读进sub_table中
      physical_operator->open(nullptr);
      while (RC::SUCCESS == (rc = physical_operator->next())) {
        Tuple * tuple = physical_operator->current_tuple();
        std::vector<Value> row;
        for(int i = 0; i < tuple->cell_num(); i++){
          Value value;
          rc = tuple->cell_at(i, value);
          if (rc != RC::SUCCESS) {
            physical_operator->close();
            LOG_WARN("failed to get SUB TABLE from operator");
            return rc;
          }
          row.push_back(value);
        }
        sub_table.push_back(row);
      }
      physical_operator->close();
      if (rc == RC::RECORD_EOF) {
        rc = RC::SUCCESS;
      }
      else{
        LOG_WARN("failed to get SUB TABLE from operator");
        return rc;
      }
    }

  //---------- create table ----------
    std::vector<AttrInfoSqlNode> all_fields;
    std::vector<Field> select_field = select_stmt->query_fields();
    for(size_t i = 0; i < select_field.size(); i++){
      AttrInfoSqlNode current_node;
      const FieldMeta *current_field = select_field[i].meta();
      current_node.type = current_field->type();
      current_node.name = current_field->name();
      current_node.length = current_field->len();
      current_node.nullable = current_field->nullable();
      all_fields.push_back(current_node);
    }
    const char *table_name = create_table_stmt->table_name().c_str();
    rc = session->get_current_db()->create_table(table_name, (int)all_fields.size(), all_fields.data());

  //---------- insert stmt ----------
    if((int)sub_table.size() == 0){
      return rc;
    }
    InsertSqlNode insert_node;
    insert_node.relation_name = create_table_stmt->table_name();
    for(size_t i = 0; i < sub_table.size(); i++){
      ValueRecord temp;
      temp.values = sub_table[i];
      insert_node.valuerecords.push_back(temp);
    }
    Stmt *sub_stmt_insert;
    InsertStmt *caller;   //无实质内容，只为了调用一个select的create方法，把create的结果存到sub_stmt中
    RC rc = caller->create(session->get_current_db(), insert_node, sub_stmt_insert);
    if(rc != RC::SUCCESS){
      LOG_WARN("sub create stmt fail");
      return rc;
    }

  //---------- insert volcano ----------
    std::unique_ptr<LogicalOperator> logical_operator_insert;
    InsertStmt *insert_stmt = static_cast<InsertStmt*>(sub_stmt_insert);
    rc = not_used.create_plan(insert_stmt, logical_operator_insert);
    if (rc != RC::SUCCESS) {
      if (rc != RC::UNIMPLENMENT) {
        LOG_WARN("failed to create logical plan. rc=%s", strrc(rc));
      }
      return rc;
    }
    std::unique_ptr<PhysicalOperator> physical_operator_insert;
    rc = not_used2.create(*logical_operator_insert, physical_operator_insert);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to generate physical plan. rc=%s", strrc(rc));
      return rc;
    }

    Trx *trx = session->current_trx();
    rc = physical_operator_insert->open(trx);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to run volcano plan. rc=%s", strrc(rc));
      return rc;
    }
  }
  else{
    const int attribute_count = static_cast<int>(create_table_stmt->attr_infos().size());
    const char *table_name = create_table_stmt->table_name().c_str();
    rc = session->get_current_db()->create_table(table_name, attribute_count, create_table_stmt->attr_infos().data());
  }

  return rc;
}