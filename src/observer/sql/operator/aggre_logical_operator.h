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
// Created by Wangyunlai on 2022/12/07.
//

#pragma once

#include "sql/operator/logical_operator.h"
#include "sql/expr/expression.h"

/**
 * @brief 谓词/过滤逻辑算子
 * @ingroup LogicalOperator
 */
class AggreLogicalOperator : public LogicalOperator 
{
public:
  AggreLogicalOperator(const std::vector<Field> &fields, const std::vector<AggrOp> &aggr_fields,
          const std::vector<std::string> &spec, std::unique_ptr<Expression> expression, bool having, int having_num);
  AggreLogicalOperator(const std::vector<Field> &fields, const std::vector<AggrOp> &aggr_fields,
          const std::vector<std::string> &spec, bool having, int having_num);
  virtual ~AggreLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::AGGRE;
  }

  const std::vector<Field> &fields() const
  {
    return fields_;
  }
  const std::vector<AggrOp> &aggr_fields() const
  {
    return aggr_fields_;
  }
  const std::vector<std::string> &spec() const
  {
    return spec_;
  }
  const bool having_flag() const
  {
    return having_;
  } 
  
  const int having_num() const
  {
    return having_num_;
  } 
  
private:
  std::vector<Field> fields_;
  std::vector<AggrOp> aggr_fields_;
  std::vector<std::string> spec_;
  bool having_ = false;
  int having_num_ = 0;
};
