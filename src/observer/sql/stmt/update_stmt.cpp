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

#include "sql/stmt/update_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/parser/typecast.h"

UpdateStmt::UpdateStmt(Table *table, std::vector<Value> &values, int value_amount, FilterStmt *filter_stmt,
    std::vector<std::string> &value_name)
    : table_(table), values_(values), value_amount_(value_amount), filter_stmt_(filter_stmt), value_name_(value_name)
{}

RC UpdateStmt::create(Db *db, UpdateSqlNode &update, Stmt *&stmt)
{
  const char *table_name = update.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || update.value.size() == 0) {
    // LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d",
    //     db, table_name, static_cast<int>(update.values.size()));
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the fields number
  // Value *values = (Value *)&update.value;//将const转化成非const
  const int        value_num  = update.attribute_name.size();  // update多字段需要修改
  const TableMeta &table_meta = table->table_meta();

  // check fields type
  // const int sys_field_num = table_meta.sys_field_num();

  // 首先判断有无该字段
  // 将const转化成非const
  std::vector<Value> values;
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field_meta = table_meta.field(update.attribute_name[i].c_str());
    values.emplace_back(update.value[i]);
    if (field_meta == nullptr) {
      return RC::SCHEMA_FIELD_MISSING;
    }
    // 这里要对表中对应字段进行判断才行
    const AttrType field_type             = field_meta->type();
    const AttrType value_type             = update.value[i].attr_type();
    const int      value_length_istoolong = update.value[i].length();
    if (value_length_istoolong > 65535) {
      LOG_WARN("text is too long to insert.");
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
    if (field_type != value_type) {  // TODO try to convert the value type to field type
      if (value_type == AttrType::NULLS &&
          !(field_meta->nullable()))  // 如果value为null且该字段不能为空 返回failure 如果为null 返回failure
      {
        LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
          table_name, field_meta->name(), field_type, value_type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      } else if (value_type != AttrType::NULLS) {
        //  LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
        //   table_name, field_meta->name(), field_type, value_type);
        //   return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        input_typecast(&update.value[i], field_type);
      }
    }
  }

  // 过滤条件
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(
      db, table, &table_map, update.conditions.data(), static_cast<int>(update.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // 初始化attr_name容器  //储存要更改的变量名
  std::vector<std::string> value_name;
  for (int i = 0; i < value_num; i++) {
    value_name.emplace_back(update.attribute_name[i]);
  }

  // everything alright
  stmt = new UpdateStmt(table, values, value_num, filter_stmt, value_name);
  return RC::SUCCESS;
}
