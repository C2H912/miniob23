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
#include <unordered_map>
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/expr/expression.h"

class Db;
class Table;
class FieldMeta;

struct HavingObj 
{
  Expression *expr;

  void init_expr(Expression *expr)
  {
    this->expr = expr;
  }
};

class HavingUnit 
{
public:
  HavingUnit() = default;
  ~HavingUnit()
  {}

  void set_comp(CompOp comp)
  {
    comp_ = comp;
  }

  CompOp comp() const
  {
    return comp_;
  }

  void set_left(const HavingObj &obj)
  {
    left_ = obj;
  }
  void set_right(const HavingObj &obj)
  {
    right_ = obj;
  }

  const HavingObj &left() const
  {
    return left_;
  }
  const HavingObj &right() const
  {
    return right_;
  }

private:
  CompOp comp_ = NO_OP;
  HavingObj left_;
  HavingObj right_;
};

/**
 * @brief Having/谓词/过滤语句
 * @ingroup Statement
 */
class HavingStmt 
{
public:
  HavingStmt() = default;
  virtual ~HavingStmt();

public:
  const std::vector<HavingUnit *> &having_units() const
  {
    return having_units_;
  }

public:
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const ConditionSqlNode *conditions, int condition_num, HavingStmt *&stmt);

  static RC create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const ConditionSqlNode &condition, HavingUnit *&filter_unit);

private:
  std::vector<HavingUnit *> having_units_;  // 默认当前都是AND关系
};