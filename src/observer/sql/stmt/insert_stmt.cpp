/* Copyright (c) 2021OceanBase and/or its affiliates. All rights reserved.
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

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/typecast.h"

InsertStmt::InsertStmt(Table *table, const ValueRecord *valuerecords, int valuerecord_amount)
    : table_(table), valuerecords_(valuerecords), valuerecord_amount_(valuerecord_amount)
{}

RC InsertStmt::create(Db *db, InsertSqlNode &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || inserts.valuerecords.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, valuerecords_num=%d",
        db, table_name, static_cast<int>(inserts.values.size()));
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the fields number
  const int        valuerecord_num = static_cast<int>(inserts.valuerecords.size());
  const TableMeta &table_meta      = table->table_meta();
  const int        field_num =
      table_meta.field_num() - table_meta.sys_field_num() - table_meta.extra_filed_num();  // 减去null字段
  for (int i = 0; i < valuerecord_num; i++) {
    // Value *values_ptr = inserts.valuerecords[i].values.data();
    int tmp_value_num = static_cast<int>(inserts.valuerecords[i].values.size());
    if (field_num != tmp_value_num) {
      LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", tmp_value_num, field_num);
      return RC::SCHEMA_FIELD_MISSING;
    }
  }
  const int value_num = static_cast<int>(inserts.valuerecords[0].values.size());

  // check fields type
  const int sys_field_num = table_meta.sys_field_num();
  for (int j = 0; j < valuerecord_num; j++) {
    Value *values_ptr = inserts.valuerecords[j].values.data();
    for (int i = 0; i < value_num; i++) {
      const FieldMeta *field_meta             = table_meta.field(i + sys_field_num);
      const AttrType   field_type             = field_meta->type();
      const AttrType   value_type             = values_ptr[i].attr_type();
      if ((field_type != value_type)) {  // TODO try to convert the value type to field type
        // LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
        //     table_name, field_meta->name(), field_type, value_type);
        // return RC::SCHEMA_FIELD_TYPE_MISMATCH;
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
          input_typecast(&values_ptr[i], field_type);
        }
        // input_typecast(&values_ptr[i], field_type);
      }
    }
  }

  Value       *values_ptr       = inserts.valuerecords[0].values.data();
  ValueRecord *valuerecords_ptr = inserts.valuerecords.data();

  // everything alright
  stmt = new InsertStmt(table, valuerecords_ptr, valuerecord_num);
  return RC::SUCCESS;
}
