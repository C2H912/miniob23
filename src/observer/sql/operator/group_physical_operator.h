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


/**
 * @brief 分组物理算子
 * @ingroup PhysicalOperator
 */
class GroupPhysicalOperator : public PhysicalOperator
{
public:
  GroupPhysicalOperator(const std::vector<Field> &fields, const std::vector<Field> &group_fields);

  virtual ~GroupPhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::GROUP;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

  RC next2() override { return RC::SUCCESS; }
  Tuple *current_tuple2() override { return nullptr; }
  std::map<Key, std::vector<ValueListTuple>> current_group() override;

private:
  std::vector<Field> all_fields_;
  std::vector<Field> group_fields_;
  std::map<Key, std::vector<ValueListTuple>> groups_;
};
