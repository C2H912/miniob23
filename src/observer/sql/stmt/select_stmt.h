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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <vector>
#include <memory>

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;
class OrderByStmt;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt 
{
public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override
  {
    return StmtType::SELECT;
  }

public:
  static RC create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt);

public:
  std::vector<Table *> &tables_without_const()
  {
    return tables_;
  }
  const std::vector<Table *> &tables() const
  {
    return tables_;
  }
  const std::vector<Field> &query_fields() const
  {
    return query_fields_;
  }
  const std::vector<AggrOp> &aggr_fields() const
  {
    return aggr_fields_;
  }
  const std::vector<std::string> &aggr_specs() const
  {
    return aggr_specs_;
  }
  FilterStmt *filter_stmt() const
  {
    return filter_stmt_;
  }

  OrderByStmt *order_by_stmt()
  {
    return order_by_stmt_;
  }

private:
  std::vector<Field> query_fields_;
  std::vector<AggrOp> aggr_fields_;
  std::vector<std::string> aggr_specs_;
  std::vector<Table *> tables_;
  FilterStmt *filter_stmt_ = nullptr;
  OrderByStmt *order_by_stmt_ = nullptr;
};
