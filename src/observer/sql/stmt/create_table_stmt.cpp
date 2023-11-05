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

#include "sql/stmt/create_table_stmt.h"
#include "event/sql_debug.h"

RC CreateTableStmt::create(Db *db, const CreateTableSqlNode &create_table, Stmt *&stmt)
{
  CreateTableStmt *create_stmt;
  if(create_table.select_flag == true){
    Stmt *sub_stmt;
    SelectStmt *caller;   //无实质内容，只为了调用一个select的create方法，把create的结果存到sub_stmt中
    std::unordered_map<std::string,Table* > parents;
    RC rc = caller->create(db, create_table.select_infos->selection, sub_stmt, parents);
    if(rc != RC::SUCCESS){
      LOG_WARN("sub create stmt fail");
      return rc;
    }
    if(create_table.attr_infos.size() == 0){
      create_stmt = new CreateTableStmt(create_table.relation_name, static_cast<SelectStmt*>(sub_stmt));
    }
    else{
      create_stmt = new CreateTableStmt(create_table.relation_name, create_table.attr_infos, static_cast<SelectStmt*>(sub_stmt));
    }
  }
  else{
    create_stmt = new CreateTableStmt(create_table.relation_name, create_table.attr_infos);
  }
  stmt = create_stmt;
  sql_debug("create table statement: table name %s", create_table.relation_name.c_str());
  return RC::SUCCESS;
}
