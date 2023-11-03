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
// Created by WangYunlai on 2022/07/01.
//

#pragma once

#include "sql/operator/physical_operator.h"

/**
 * @brief 选择/投影物理算子
 * @ingroup PhysicalOperator
 */
class ProjectPhysicalOperator : public PhysicalOperator
{
public:
  ProjectPhysicalOperator(std::vector<std::unique_ptr<Expression>> &&expressions)
    : expressions_(std::move(expressions)), expr_tuple_(expressions_)
  {}

  virtual ~ProjectPhysicalOperator() = default;

  void add_expressions(std::vector<std::unique_ptr<Expression>> &&expressions)
  {
    expressions_.swap(expressions);
  }
  void add_projection(const Table *table, const FieldMeta *field);

  void add_projection(std::string s, AggrOp aggr);

  void add_projection(const Table *table, const FieldMeta *field_meta,const char* alias);//重载 使用别名

  void add_projection(const char* alias);

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::PROJECT;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  int cell_num() const
  {
    return tuple_.cell_num();
  }

  Tuple *current_tuple() override;
  
  RC next2() override;
  Tuple *current_tuple2() override;
  std::map<Key, std::vector<ValueListTuple>> current_group() override
  {
    std::map<Key, std::vector<ValueListTuple>> not_used;
    return not_used;
  }

  const std::vector<std::unique_ptr<Expression>> &expressions() const
  {
    return expressions_;
  }

private:
  ProjectTuple tuple_;
  std::vector<std::unique_ptr<Expression>> expressions_;
  ExpressionTuple expr_tuple_;
  ValueListTuple result_;
};
