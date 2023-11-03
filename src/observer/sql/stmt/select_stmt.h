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
#include <unordered_map>

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
  static RC create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt,std::unordered_map<std::string,Table* > parents);

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
  const std::vector<std::pair<bool,std::string>> &aggr_alias() const
  {
    return aggr_alias_;
  }
  FilterStmt *filter_stmt() const
  {
    return filter_stmt_;
  }
  int conjunction_flag() const
  {
    return conjunction_flag_;
  }

  const std::vector<Field> &group_fields() const
  {
    return group_by_fields_;
  }

  OrderByStmt *order_by_stmt()
  {
    return order_by_stmt_;
  }

  std::vector<std::unique_ptr<Expression>> &expressions()
  {
    return expressions_;
  }

  bool expr_flag()
  {
    return is_expr_;
  }

  bool groupby_flag()
  {
    return groupby_flag_;
  }

private:
  std::vector<Field> query_fields_;
  std::vector<AggrOp> aggr_fields_;
  std::vector<std::string> aggr_specs_;
  std::vector<Table *> tables_;
  std::vector<std::pair<bool,std::string>> aggr_alias_;
  int conjunction_flag_;    //0: AND, 1: OR
  FilterStmt *filter_stmt_ = nullptr;
  std::vector<Field> group_by_fields_;
  bool groupby_flag_ = false;
  OrderByStmt *order_by_stmt_ = nullptr;
  bool is_expr_ = false;
  std::vector<std::unique_ptr<Expression>> expressions_;
};
