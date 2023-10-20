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
// Created by WangYunlai on 2022/6/27.
//

#pragma once

#include <memory>
#include "sql/operator/physical_operator.h"
#include "sql/expr/expression.h"

class FilterStmt;

/**
 * @brief 过滤/谓词物理算子
 * @ingroup PhysicalOperator
 */
class AggrePhysicalOperator : public PhysicalOperator
{
public:
  AggrePhysicalOperator(const std::vector<Field> &fields, const std::vector<AggrOp> &aggr_fields);

  virtual ~AggrePhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::PREDICATE;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;
  RC do_aggre_func(std::vector<std::vector<Value>>& all_tuple);
  Value do_int(std::vector<std::vector<Value>>& all_tuple, int index);
  Value do_float(std::vector<std::vector<Value>>& all_tuple, int index);
  Value do_char(std::vector<std::vector<Value>>& all_tuple, int index);

private:
  std::vector<Field> fields_;
  std::vector<AggrOp> aggr_fields_;
  ValueListTuple tuple_;
  bool enter_flag_ = false;
};
