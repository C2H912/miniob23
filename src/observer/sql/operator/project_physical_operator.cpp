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

#include "common/log/log.h"
#include "sql/operator/project_physical_operator.h"
#include "storage/record/record.h"
#include "storage/table/table.h"

RC ProjectPhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

#if 1
RC ProjectPhysicalOperator::next2()
{
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }
  return children_[0]->next();
}

Tuple *ProjectPhysicalOperator::current_tuple2()
{
  tuple_.set_tuple(children_[0]->current_tuple());
  return &tuple_;
}

#endif

RC ProjectPhysicalOperator::next()
{
  if (children_.empty()) {
    //处理不经过表的function
    if(function_enter_ == false){
      std::vector<Value> temp_result;
      int cell_num = expr_tuple_.cell_num();
      for (int i = 0; i < cell_num; i++) {
        Value value;
        ValueListTuple not_used;
        RC rcc = expr_tuple_.get_expr_value(not_used, value, i);
        if (OB_FAIL(rcc)) {
          return rcc;
        }
        temp_result.push_back(value);
      }
      result_.set_cells(temp_result);
      if(!temp_result.empty()){
        function_enter_ = true;
        return RC::SUCCESS;
      }
      else{
        function_enter_ = false;
        return RC::RECORD_EOF;
      }
    }
    else{
      function_enter_ = false;
      return RC::RECORD_EOF;
    }
  }

  RC rc = RC::SUCCESS;
  PhysicalOperator *oper = children_.front().get();
  rc = oper->next();
  if(rc == RC::RECORD_EOF){
    return rc;
  }
  else if(rc != RC::SUCCESS){
    return rc;
  }

  Tuple *tuple = oper->current_tuple();
  if (nullptr == tuple) {
    rc = RC::INTERNAL;
    LOG_WARN("failed to get tuple from operator");
  }

  std::vector<Value> temp_result;
  int cell_num = expr_tuple_.cell_num();
  for (int i = 0; i < cell_num; i++) {
    Value value;
    rc = expr_tuple_.get_expr_value(*tuple, value, i);
    if (OB_FAIL(rc)) {
      return rc;
    }
    temp_result.push_back(value);
  }
  result_.set_cells(temp_result);
   
  return rc;
}

RC ProjectPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}

Tuple *ProjectPhysicalOperator::current_tuple()
{
  return static_cast<Tuple*>(&result_);
}

void ProjectPhysicalOperator::add_projection(const Table *table, const FieldMeta *field_meta)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  TupleCellSpec *spec = new TupleCellSpec(table->name(), field_meta->name(), field_meta->name());
  tuple_.add_cell_spec(spec);
}

void ProjectPhysicalOperator::add_projection(std::string s, AggrOp aggr)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  TupleCellSpec *spec = new TupleCellSpec(s, aggr);
  tuple_.add_cell_spec(spec);
}

void ProjectPhysicalOperator::add_projection(const Table *table, const FieldMeta *field_meta,const char* alias)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  if(alias==nullptr)
  {
    TupleCellSpec *spec = new TupleCellSpec(table->name(), field_meta->name(), field_meta->name());
    tuple_.add_cell_spec(spec);
  }
  else{
    TupleCellSpec *spec = new TupleCellSpec(table->name(), field_meta->name(),alias);
    tuple_.add_cell_spec(spec);
  }
 
}

void ProjectPhysicalOperator::add_projection(const char* alias)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  TupleCellSpec *spec = new TupleCellSpec(alias);
  tuple_.add_cell_spec(spec);
}

