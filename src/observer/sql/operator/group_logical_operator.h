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
class GroupLogicalOperator : public LogicalOperator 
{
public:
  GroupLogicalOperator(const std::vector<Field> &all_fields, const std::vector<Field> &group_fields);
  virtual ~GroupLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::GROUP;
  }

  const std::vector<Field> &all_fields() const
  {
    return all_fields_;
  }

  const std::vector<Field> &group_fields() const
  {
    return group_fields_;
  }
  
private:
  std::vector<Field> all_fields_;
  std::vector<Field> group_fields_;
};
