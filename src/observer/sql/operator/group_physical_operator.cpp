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

#include "common/log/log.h"
#include "sql/operator/group_physical_operator.h"
#include "storage/record/record.h"
#include "storage/field/field.h"

GroupPhysicalOperator::GroupPhysicalOperator(const std::vector<Field> &fields, const std::vector<Field> &group_fields)
:all_fields_(fields), group_fields_(group_fields)
{}

RC GroupPhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->open(trx);
}

RC GroupPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  PhysicalOperator *oper = children_.front().get();

  //先把所有值存起来
  std::vector<std::vector<Value>> all_tuple;
  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }
    //读取一行数据, 并生成ValueListTuple
    std::vector<Value> one_tuple;
    for(int i = 0; i < (int)all_fields_.size(); i++){
      Value value;
      FieldExpr field_exp(all_fields_[i]);
      rc = field_exp.get_value(*tuple, value);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      one_tuple.push_back(value);
    }
    ValueListTuple one_tuple_list;
    one_tuple_list.set_cells(one_tuple);
    one_tuple_list.set_specs(all_fields_);
    //生成键值ValueListTuple
    std::vector<Value> one_key;
    for(int i = 0; i < (int)group_fields_.size(); i++){
      Value value;
      FieldExpr field_exp(group_fields_[i]);
      rc = field_exp.get_value(*tuple, value);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      one_key.push_back(value);
    }
    ValueListTuple one_key_list;
    one_key_list.set_cells(one_key);
    one_key_list.set_specs(group_fields_);
    Key current_key;
    current_key.set_valueList(one_key_list);
    //放入hash中
    groups_[current_key].push_back(one_tuple_list);
  }
  if (rc == RC::RECORD_EOF) {
    return RC::SUCCESS;
  }
  
  return rc;
}

RC GroupPhysicalOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *GroupPhysicalOperator::current_tuple()
{
  return nullptr;
}

std::map<Key, std::vector<ValueListTuple>> GroupPhysicalOperator::current_group()
{
  return groups_;
}
