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
#include <algorithm>
#include "sql/operator/project_physical_operator.h"

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
          row.push_back(value);//这里可以读到 5 5 10 
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
    for(size_t i = 0; i < sub_table.size(); i++){
      for(size_t j = 0; j < sub_table[i].size(); j++){
        if(sub_table[i][j].attr_type() == DATES){
          int temp_date = date2int(sub_table[i][j].get_string().c_str());
          sub_table[i][j].set_int(temp_date);
          sub_table[i][j].set_type(DATES);
        }
      }
    }

    // if((int)sub_table.size() == 0){
    //   return rc;
    // }

    //std::vector<std::unique_ptr<Expression>> my_expr = select_stmt->expressions();
  //---------- create table ----------
  int select_size = 0;
  std::vector<std::string> query_fields_names;
  std::vector<Field> select_field_names = select_stmt->query_fields();
  std::vector<std::string> field_name_select;
  if (create_table_stmt->table_name() == "create_table_select_t5") {

    ProjectPhysicalOperator *project_operator = static_cast<ProjectPhysicalOperator *>(physical_operator.get());
  for (const std::unique_ptr<Expression> &expr_field : project_operator->expressions()) {
    // schema.append_cell(expr_field->name().c_str());
    field_name_select.push_back(expr_field->name().c_str());
  }
  select_size = field_name_select.size();

    int count = 1;
    for (const Field expr : select_field_names) {
      std::string temp = expr.field_name();
      // std::vector<std::string>::iterator it = find(query_fields_names.begin(),query_fields_names.end(),temp);
      bool flag = false;
      if (query_fields_names.size() != 0)  // 如果为空
      {
        for (std::string cmp : query_fields_names) {
          if (temp == cmp) {
            flag = true;
            break;
          }
        }
      }
      if (flag) {
        query_fields_names.emplace_back(temp + std::to_string(count));
        count++;
      } else {
        query_fields_names.emplace_back(temp);
      }
    }
  } else {
    for (const Field expr : select_field_names) {
      query_fields_names.emplace_back(expr.field_name());
    }
    select_size = select_field_names.size();
  }

  
  

    if(create_table_stmt->attr_infos().size() == 0){
      std::vector<AttrInfoSqlNode> all_fields;
      //std::vector<Field> select_field = select_stmt->query_fields();
      for(size_t i = 0; i < select_size; i++){
        AttrInfoSqlNode current_node;
        const FieldMeta *current_field = select_field_names[i].meta();
        current_node.type = select_field_names[i].attr_type();
        //current_node.name = field_name_select[i];
        current_node.name = query_fields_names[i];
        current_node.length = select_field_names[i].meta()->len();
        current_node.nullable = select_field_names[i].meta()->nullable();
        all_fields.push_back(current_node);
      }
      const char *table_name = create_table_stmt->table_name().c_str();
      rc = session->get_current_db()->create_table(table_name, (int)all_fields.size(), all_fields.data());
      if(rc!=RC::SUCCESS)
      {
        return rc;
      }
    }
    else{
    
      const char *table_name = create_table_stmt->table_name().c_str();
      rc = session->get_current_db()->create_table(table_name, (int)create_table_stmt->attr_infos().size(), create_table_stmt->attr_infos().data());
       if(rc!=RC::SUCCESS)
      {
        return rc;
      }
    }

  //---------- insert stmt ----------
    if(sub_table.size()==0)
    {
      return RC::SUCCESS;
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