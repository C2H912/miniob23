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
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/update_physical_operator.h"
#include "sql/stmt/update_stmt.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

using namespace std;

UpdatePhysicalOperator::UpdatePhysicalOperator(Table *table, vector<Value> &&values)
    : table_(table), values_(std::move(values))
{}

RC UpdatePhysicalOperator::open(Trx *trx)
{
  //update单条语句应该和insert一样 一个open解决 但是有点破坏火山模型
  //不对 可能会存在多个需要修改的record
  //所以模仿delete来写
   if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;

  return RC::SUCCESS;


  // Record record;
  // RC rc = table_->make_record(static_cast<int>(values_.size()), values_.data(), record);
  // if (rc != RC::SUCCESS) {
  //   LOG_WARN("failed to make record. rc=%s", strrc(rc));
  //   return rc;
  // }

  // rc = trx->insert_record(table_, record);
  // if (rc != RC::SUCCESS) {
  //   LOG_WARN("failed to Update record by transaction. rc=%s", strrc(rc));
  // }
  // return rc;
}

RC UpdatePhysicalOperator::next()
{
  //return RC::RECORD_EOF;

  RC rc = RC::RECORD_EOF;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  PhysicalOperator *child = children_[0].get();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    //先删除record
    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record &record = row_tuple->record();
    rc = trx_->delete_record(table_, record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to delete record: %s", strrc(rc));
      return rc;
    }

    //格式在stmt中判断过了
    //是否需要回退
    Record new_record;
    RC rc = table_->make_record(static_cast<int>(values_.size()), values_.data(), new_record);
    if (rc != RC::SUCCESS) {
    LOG_WARN("failed to make record. rc=%s", strrc(rc));
    return rc;
    }

    rc = trx_->insert_record(table_, new_record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
       return rc;
    }
   

  }

  return RC::RECORD_EOF;


}

RC UpdatePhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
