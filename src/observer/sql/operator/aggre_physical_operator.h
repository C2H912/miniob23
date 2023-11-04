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
  AggrePhysicalOperator(const std::vector<Field> &fields, const std::vector<AggrOp> &aggr_fields,
    const std::vector<std::string> &spec, std::unique_ptr<Expression> expr, bool having_flag);
  AggrePhysicalOperator(const std::vector<Field> &fields, const std::vector<AggrOp> &aggr_fields,
    const std::vector<std::string> &spec, bool having_flag);

  virtual ~AggrePhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::AGGRE;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

  RC do_group_aggre(std::map<Key, std::vector<ValueListTuple>>& groups);
  RC do_aggre_func(std::vector<std::vector<Value>>& all_tuple);
  Value do_int(std::vector<std::vector<Value>>& all_tuple, int index);
  Value do_float(std::vector<std::vector<Value>>& all_tuple, int index);
  Value do_char(std::vector<std::vector<Value>>& all_tuple, int index);
  Value do_date(std::vector<std::vector<Value>>& all_tuple, int index);

  RC next2() override { return RC::SUCCESS; }
  Tuple *current_tuple2() override { return nullptr; }
  std::map<Key, std::vector<ValueListTuple>> current_group() override
  {
    std::map<Key, std::vector<ValueListTuple>> not_used;
    return not_used;
  }

private:
  std::vector<Field> fields_;
  std::vector<AggrOp> aggr_fields_;
  std::vector<std::string> spec_;
  std::vector<AggreListTuple> tuple_;
  std::unique_ptr<Expression> expression_;
  bool having_flag_ = false;
  int scan_index_ = 0;
  bool enter_flag_ = false;
};
