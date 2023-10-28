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

#pragma once

#include <vector>
#include <string>
#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"


class Table;
class FilterStmt;
class SelectStmt;

typedef struct update_list{
  int type;
  Value value;
  SelectStmt* sub_query;
};

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt 
{
public:
  UpdateStmt() = default;
  UpdateStmt(Table *table, std::vector<update_list> &values, int value_amount, FilterStmt *filter_stmt,std::vector<std::string> &value_name_);

public:
  static RC create(Db *db, UpdateSqlNode &update_sql, Stmt *&stmt);

  
public:
  Table *table() const
  {
    return table_;
  }
  std::vector<update_list> valueList() const
  {
    return update_list_;
  }
  int value_amount() const
  {
    return value_amount_;
  }
   FilterStmt *filter_stmt() const
  {
    return filter_stmt_;
  }
   StmtType type() const override
  {
    return StmtType::UPDATE;
  }
   const std::vector<std::string> &names() const 
  { 
    return value_name_; 
  }

private:
  Table *table_ = nullptr;
  //Value *values_ = nullptr;
  std::vector<update_list> update_list_;
  std::vector<std::string> value_name_; 
  int value_amount_ = 0;
  FilterStmt *filter_stmt_ = nullptr;
};
