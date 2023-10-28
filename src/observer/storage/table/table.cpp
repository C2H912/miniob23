/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi & Wangyunlai on 2021/5/13.
//

#include <limits.h>
#include <string.h>
#include <algorithm>

#include "common/defs.h"
#include "storage/table/table.h"
#include "storage/table/table_meta.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/buffer/disk_buffer_pool.h"
#include "storage/record/record_manager.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/index/index.h"
#include "storage/index/bplus_tree_index.h"
#include "storage/trx/trx.h"
#include "sql/parser/typecast.h"

Table::~Table()
{
  if (record_handler_ != nullptr) {
    delete record_handler_;
    record_handler_ = nullptr;
  }

  if (data_buffer_pool_ != nullptr) {
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
  }

  for (std::vector<Index *>::iterator it = indexes_.begin(); it != indexes_.end(); ++it) {
    Index *index = *it;
    delete index;
  }
  indexes_.clear();

  LOG_INFO("Table has been closed: %s", name());
}

RC Table::drop(const char *path, const char *name, const char *base_dir)
{

  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }

  RC                 rc  = RC::SUCCESS;
  BufferPoolManager &bpm = BufferPoolManager::instance();
  // 删除索引
  for (Index *index : indexes_) {
    const char *index_name      = index->index_meta().name();
    std::string index_file_path = table_index_file(base_dir_.c_str(), name, index_name);
    remove(index_file_path.c_str());
    rc = bpm.close_file(index_file_path.c_str());
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  //
  record_handler_->close();
  delete record_handler_;
  record_handler_ = nullptr;

  // 删除元数据文件
  std::string meta_file_path = table_meta_file(base_dir_.c_str(), name);
  remove(meta_file_path.c_str());
  rc = bpm.close_file(meta_file_path.c_str());

  // 删除数据文件
  std::string data_file_path = table_data_file(base_dir_.c_str(), name);
  remove(data_file_path.c_str());
  rc = bpm.close_file(data_file_path.c_str());

  return rc;
}

RC Table::create(int32_t table_id, const char *path, const char *name, const char *base_dir, int attribute_count,
    const AttrInfoSqlNode attributes[])
{
  if (table_id < 0) {
    LOG_WARN("invalid table id. table_id=%d, table_name=%s", table_id, name);
    return RC::INVALID_ARGUMENT;
  }

  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attribute_count <= 0 || nullptr == attributes) {
    LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d, attributes=%p", name, attribute_count, attributes);
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 table_name.table记录一个表的元数据
  // 判断表文件是否已经存在
  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (fd < 0) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s", path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", path, errno, strerror(errno));
    return RC::IOERR_OPEN;
  }

  close(fd);

  // 创建文件
  if ((rc = table_meta_.init(table_id, name, attribute_count, attributes)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc;  // delete table file
  }

  std::fstream fs;
  fs.open(path, std::ios_base::out | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
    return RC::IOERR_OPEN;
  }

  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();

  std::string        data_file = table_data_file(base_dir, name);
  BufferPoolManager &bpm       = BufferPoolManager::instance();
  rc                           = bpm.create_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
    return rc;
  }

  rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create table %s due to init record handler failed.", data_file.c_str());
    // don't need to remove the data_file
    return rc;
  }

  base_dir_ = base_dir;
  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}

RC Table::open(const char *meta_file, const char *base_dir)
{
  // 加载元数据文件
  std::fstream fs;
  std::string  meta_file_path = std::string(base_dir) + common::FILE_PATH_SPLIT_STR + meta_file;
  fs.open(meta_file_path, std::ios_base::in | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file_path.c_str(), strerror(errno));
    return RC::IOERR_OPEN;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file_path.c_str());
    fs.close();
    return RC::INTERNAL;
  }
  fs.close();

  // 加载数据文件
  RC rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open table %s due to init record handler failed.", base_dir);
    // don't need to remove the data_file
    return rc;
  }

  base_dir_ = base_dir;

  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {
    const IndexMeta *index_meta = table_meta_.index(i);
    // const FieldMeta *field_meta = table_meta_.field(index_meta->field());
    const std::vector<std::string> *index_field_names = index_meta->field();
    std::vector<FieldMeta>          field_metas;
    for (size_t i = 0; i < index_field_names->size(); i++) {
      const char      *field_name = index_field_names->at(i).data();
      const FieldMeta *field_meta = table_meta_.field(field_name);
      if (field_meta == nullptr) {
        LOG_ERROR("Found invalid index meta info which has a non-exists field. table=%s, index=%s, field=%s",
            name(),
            index_meta->name(),
            index_meta->field());
        // skip cleanup
        //  do all cleanup action in destructive Table function
        return RC::INTERNAL;
      }
      field_metas.push_back(*field_meta);
    }

    BplusTreeIndex *index      = new BplusTreeIndex();
    std::string     index_file = table_index_file(base_dir, name(), index_meta->name());
    rc                         = index->open(index_file.c_str(), *index_meta, field_metas);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%s",
                name(), index_meta->name(), index_file.c_str(), strrc(rc));
      // skip cleanup
      //  do all cleanup action in destructive Table function.
      return rc;
    }
    indexes_.push_back(index);
  }

  return rc;
}

RC Table::insert_record(Record &record)
{
  RC rc = RC::SUCCESS;
  rc    = record_handler_->insert_record(record.data(), table_meta_.record_size(), &record.rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }
  // 记录一下插入和删除操作的rid
  rc = insert_entry_of_indexes(record.data(), record.rid());
  if (rc != RC::SUCCESS) {  // 可能出现了键值重复  奇怪的是 这两个的rid怎么会是一样的
    // RC rc2 = delete_entry_of_indexes(record.data(), record.rid(), false/*error_on_not_exists*/);
    // if (rc2 != RC::SUCCESS) {
    //   LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
    //             name(), rc2, strrc(rc2));
    // }
    RC rc2 = record_handler_->delete_record(&record.rid());
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
  }
  return rc;
}

RC Table::visit_record(const RID &rid, bool readonly, std::function<void(Record &)> visitor)
{
  return record_handler_->visit_record(rid, readonly, visitor);
}

RC Table::get_record(const RID &rid, Record &record)
{
  const int record_size = table_meta_.record_size();
  char     *record_data = (char *)malloc(record_size);
  ASSERT(nullptr != record_data, "failed to malloc memory. record data size=%d", record_size);

  auto copier = [&record, record_data, record_size](Record &record_src) {
    memcpy(record_data, record_src.data(), record_size);
    record.set_rid(record_src.rid());
  };
  RC rc = record_handler_->visit_record(rid, true /*readonly*/, copier);
  if (rc != RC::SUCCESS) {
    free(record_data);
    LOG_WARN("failed to visit record. rid=%s, table=%s, rc=%s", rid.to_string().c_str(), name(), strrc(rc));
    return rc;
  }

  record.set_data_owner(record_data, record_size);
  return rc;
}

RC Table::recover_insert_record(Record &record)
{
  RC rc = RC::SUCCESS;
  rc    = record_handler_->recover_insert_record(record.data(), table_meta_.record_size(), record.rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }

  rc = insert_entry_of_indexes(record.data(), record.rid());
  if (rc != RC::SUCCESS) {  // 可能出现了键值重复
    RC rc2 = delete_entry_of_indexes(record.data(), record.rid(), false /*error_on_not_exists*/);
    if (rc2 != RC::SUCCESS) {
      LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    rc2 = record_handler_->delete_record(&record.rid());
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
  }
  return rc;
}

const char *Table::name() const { return table_meta_.name(); }

const TableMeta &Table::table_meta() const { return table_meta_; }

RC Table::make_record(int value_num, const Value *values, Record &record)
{
  // 检查字段类型是否一致
  if (value_num + table_meta_.sys_field_num() != table_meta_.field_num() - table_meta_.extra_filed_num()) {
    LOG_WARN("Input values don't match the table's schema, table name:%s", table_meta_.name());
    return RC::SCHEMA_FIELD_MISSING;
  }

  const int normal_field_start_index = table_meta_.sys_field_num();
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value     &value = values[i];
    if (field->type() != value.attr_type()&&(value.attr_type()!=AttrType::NULLS)) {
      LOG_ERROR("Invalid value type. table name =%s, field name=%s, type=%d, but given=%d",
                table_meta_.name(), field->name(), field->type(), value.attr_type());
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }

  // 复制所有字段的值
  int              record_size = table_meta_.record_size();
  char            *record_data = (char *)malloc(record_size);
  const FieldMeta *null_field  = table_meta_.null_bitmap_field();
  common::Bitmap   bitmap(record_data + null_field->offset(), null_field->len());
  //common::Bitmap   bitmap(record.data() + null_field->offset(), null_field->len());//你这个bitmap根本就是随便找的

  for (int i = 0; i < value_num; i++) {
    int              idx   = i + normal_field_start_index;
    const FieldMeta *field = table_meta_.field(idx);  // i + normal_field_start_index = idx
    const Value     &value = values[i];
    if (AttrType::NULLS == value.attr_type()) {  // 检查是否为空值
      if (!field->nullable()) {
        LOG_ERROR("Invalid value type. Cannot be null. table name =%s, field name=%s, type=%d, but given=%d",
          table_meta_.name(),
          field->name(),
          field->type(),
          value.attr_type());
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      bitmap.set_bit(idx);  // 这里已经改变了bitmap
      // make sure data all zero bit
      memset(record_data + field->offset(), 0, field->len());  // 把全0存进null字段的位置
    } else {
      // 非空的情况
      size_t copy_len = field->len();
      if (field->type() == CHARS) {
        const size_t data_len = value.length();
        if (copy_len > data_len) {
          copy_len = data_len + 1;
        }
      }
      memcpy(record_data + field->offset(), value.data(), copy_len);
      bitmap.clear_bit(idx);

    }
  }

  record.set_data_owner(record_data, record_size);
  return RC::SUCCESS;
}

RC Table::make_record_for_update(
    int value_num,  Value *values, Record &record, std::vector<std::string> values_name, char *record_in)
{
  // 由make_record修改而来，修改对应字段的record位置即可
  // 检查字段是否存在 类型是否正确 但是stmt好像也检查了一遍 等下对比一下

  int attr_num = table_meta_.field_num() - table_meta_.sys_field_num() - table_meta_.extra_filed_num();  // 该表的字段数量
  const int normal_field_start_index = table_meta_.sys_field_num();
  
  for (int j = 0; j < value_num; j++) {
    // 测试不同字段是否存在于表中
    int count = 0;
    Value &value = values[j];
    //如果是无效的数据直接返回失败即可
    if(value.attr_type() == UPDATE_FAIL){
      LOG_ERROR("update sub query table invalid");
      return RC::INVALID_ARGUMENT;
    }

    for (int i = 0; i < attr_num; i++) {
      int idx = i + normal_field_start_index;
      const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
      // 先找到对应的字段 检查属性
      if (0 == strcmp(field->name(), values_name[j].c_str())) {
        if (field->type() != value.attr_type()) {
          // 字段类型不等 还可能是NULL
          if (value.attr_type() == AttrType::NULLS) {
            if (!field->nullable()) {  // 检查是否可为空
              return RC::SCHEMA_FIELD_TYPE_MISMATCH;
            }
          } else {
            //return RC::SCHEMA_FIELD_TYPE_MISMATCH;
            input_typecast(&value, field->type());
          }
        }
        break;//找到之后之间跳过内层循环
      } else {
        count++;
      }
    }
    if (count == attr_num)  // 表示update的字段和表中所有字段不符合
    {
      LOG_ERROR("make_record_for_update: Invalid attribute name");
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }
  // 感觉很浪费欸 进行了两次循环

  // 复制所有字段的值
  int record_size = table_meta_.record_size();
  char *record_data = (char *)malloc(record_size);

  const FieldMeta *null_field  = table_meta_.null_bitmap_field();
  memcpy(record_data + null_field->offset(), record_in + null_field->offset(), null_field->len());
  common::Bitmap bitmap(record_data + null_field->offset(), null_field->len());//你这个bitmap根本就是随便找的
  //拿的不是record的bitmap

  for (int i = 0; i < attr_num; i++) {
    int idx = i + normal_field_start_index;//关键是在整个record中的位置，所以说不是j是i
    const FieldMeta *field = table_meta_.field(idx);
    // 这里是找到匹配的字段
    // 新增的for循环
    for (int j = 0; j < value_num; j++) {
      if (0 == strcmp(field->name(), values_name[j].c_str())) {
        size_t copy_len = field->len();
        const Value &value = values[j];

        if (AttrType::NULLS == value.attr_type()) {  // 检查是否为空值
          if (!field->nullable()) {
            LOG_ERROR("Invalid value type. Cannot be null. table name =%s, field name=%s, type=%d, but given=%d",
              table_meta_.name(),
              field->name(),
              field->type(),
              value.attr_type());
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
          bitmap.set_bit(idx);  // 这里已经改变了bitmap
          // make sure data all zero bit
          memset(record_data + field->offset(), 0, field->len());  // 把全0存进null字段的位置
        } else {
          // 非空的情况
          size_t copy_len = field->len();
          if (field->type() == CHARS) {
            const size_t data_len = value.length();
            if (copy_len > data_len) {
              copy_len = data_len + 1;
            }
          }
          memcpy(record_data + field->offset(), value.data(), copy_len);
          bitmap.clear_bit(idx);//匹配完的话，应该跳过该循环，因为字段是一一对应的
        }
        break;
      } else {
        // 没有匹配的话，就直接用原来的record
        if (j == value_num - 1)  // 最后一次才执行 节约时间
          memcpy(record_data + field->offset(), record_in + field->offset(), field->len());
      }
    }
  }

  record.set_data_owner(record_data, record_size);
  return RC::SUCCESS;
}

RC Table::init_record_handler(const char *base_dir)
{
  std::string data_file = table_data_file(base_dir, table_meta_.name());

  RC rc = BufferPoolManager::instance().open_file(data_file.c_str(), data_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s", data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  record_handler_ = new RecordFileHandler();
  rc              = record_handler_->init(data_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%s", strrc(rc));
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
    delete record_handler_;
    record_handler_ = nullptr;
    return rc;
  }

  return rc;
}

RC Table::get_record_scanner(RecordFileScanner &scanner, Trx *trx, bool readonly)
{
  RC rc = scanner.open_scan(this, *data_buffer_pool_, trx, readonly, nullptr);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%s", strrc(rc));
  }
  return rc;
}
// 这个函数是关键 多列索引要修改的有  每个entry的key生成 key之间的对比 是否为unique
RC Table::create_index(Trx *trx, std::vector<FieldMeta> &field_meta, const char *index_name, bool unique)
{
  if (common::is_blank(index_name) || field_meta.empty() == true) {
    LOG_INFO("Invalid input arguments, table name is %s, index_name is blank or attribute_name is blank", name());
    return RC::INVALID_ARGUMENT;
  }

  // 转换成string类型
  std::vector<std::string> field_names;  // 字段名 里面没有null_field
  for (const FieldMeta &field_meta_temp : field_meta) {
    std::string field_name = field_meta_temp.name();
    field_names.push_back(field_name);
  }

  IndexMeta new_index_meta;
  RC rc = new_index_meta.init(index_name, unique, field_names);  // 初始化索引文件 但是怎么只有一个field 需要修改
  if (rc != RC::SUCCESS) {

    return rc;
  }

  FieldMeta tmp_field_meat = *table_meta_.null_bitmap_field();
  //field_meta.push_back(tmp_field_meat);//把null_field放最后面
  field_meta.insert(field_meta.begin(),tmp_field_meat);
  // 创建索引相关数据
  BplusTreeIndex *index      = new BplusTreeIndex();
  std::string     index_file = table_index_file(base_dir_.c_str(), name(), index_name);
  rc                         = index->create(index_file.c_str(), new_index_meta, field_meta);  // TODO
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  // 应该是创建索引时候产生的问题
  RecordFileScanner scanner;
  rc = get_record_scanner(scanner, trx, true /*readonly*/);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create scanner while creating index. table=%s, index=%s, rc=%s", 
             name(), index_name, strrc(rc));
    return rc;
  }

  Record record;
  while (scanner.has_next()) {
    rc = scanner.next(record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to scan records while creating index. table=%s, index=%s, rc=%s",
               name(), index_name, strrc(rc));
      return rc;
    }
    rc = index->insert_entry(record.data(), &record.rid());  // 这里要改 把单个key改成多个key
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
               name(), index_name, strrc(rc));
      return rc;
    }
  }
  scanner.close_scan();
  LOG_INFO("inserted all records into new index. table=%s, index=%s", name(), index_name);

  indexes_.push_back(index);

  /// 接下来将这个索引放到表的元数据中
  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }

  /// 内存中有一份元数据，磁盘文件也有一份元数据。修改磁盘文件时，先创建一个临时文件，写入完成后再rename为正式文件
  /// 这样可以防止文件内容不完整
  // 创建元数据临时文件
  std::string  tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  std::fstream fs;
  fs.open(tmp_file, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR_OPEN;  // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }
  fs.close();

  // 覆盖原始元数据文件
  std::string meta_file = table_meta_file(base_dir_.c_str(), name());
  int         ret       = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). "
              "system error=%d:%s",
              tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("Successfully added a new index (%s) on the table (%s)", index_name, name());
  return rc;
}

RC Table::delete_record(const Record &record)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record.data(), &record.rid());
    ASSERT(RC::SUCCESS == rc,
        "failed to delete entry from index. table name=%s, index name=%s, rid=%s, rc=%s",
        name(),
        index->index_meta().name(),
        record.rid().to_string().c_str(),
        strrc(rc));
  }
  rc = record_handler_->delete_record(&record.rid());
  return rc;
}

RC Table::insert_entry_of_indexes(const char *record, const RID &rid)
{
  // 按理来说，由于RID的存在，删除索引应该不会出现数据一样但是被删的情况
  RC rc = RC::SUCCESS;

  // for (Index *index : indexes_) {
  //   rc = index->insert_entry(record, &rid);
  //   if (rc != RC::SUCCESS) {
  //     break;
  //   }
  // }
  for (int i = 0; i < indexes_.size(); i++) {
    rc = indexes_[i]->insert_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      for (int j = i - 1; j >= 0; j++)  // 不成功的话 当场回退
      {
        RC rc2 = indexes_[i]->delete_entry(record, &rid);
        if (rc2 != RC::SUCCESS) {
          return rc2;
        }
      }
      break;
    }
  }

  return rc;
}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}

Index *Table::find_index(const char *index_name) const
{
  for (Index *index : indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }
  return nullptr;
}
Index *Table::find_index_by_field(const char *field_name) const
{
  const TableMeta &table_meta = this->table_meta();
  const IndexMeta *index_meta = table_meta.find_index_by_field(field_name);
  if (index_meta != nullptr) {
    return this->find_index(index_meta->name());
  }
  return nullptr;
}

RC Table::sync()
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
          name(),
          index->index_meta().name(),
          rc,
          strrc(rc));
      return rc;
    }
  }
  LOG_INFO("Sync table over. table=%s", name());
  return rc;
}
