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
// Created by Wangyunlai on 2021/5/14.
//

#pragma once

#include <memory>
#include <vector>
#include <string>
#include "common/lang/bitmap.h"
#include "common/log/log.h"
#include "sql/expr/tuple_cell.h"
#include "sql/parser/parse.h"
#include "sql/parser/value.h"
#include "sql/expr/expression.h"
#include "storage/record/record.h"

class Table;

/**
 * @defgroup Tuple
 * @brief Tuple 元组，表示一行数据，当前返回客户端时使用
 * @details 
 * tuple是一种可以嵌套的数据结构。
 * 比如select t1.a+t2.b from t1, t2;
 * 需要使用下面的结构表示：
 * @code {.cpp}
 *  Project(t1.a+t2.b)
 *        |
 *      Joined
 *      /     \
 *   Row(t1) Row(t2)
 * @endcode
 * 
 */

/**
 * @brief 元组的结构，包含哪些字段(这里成为Cell)，每个字段的说明
 * @ingroup Tuple
 */
class TupleSchema 
{
public:
  void append_cell(const TupleCellSpec &cell)
  {
    cells_.push_back(cell);
  }
  void append_cell(const char *table, const char *Field)
  {
    append_cell(TupleCellSpec(table, Field, nullptr));
  }
  void append_cell(const char *table, const char *Field,const char* alias)
  {
    append_cell(TupleCellSpec(table, Field, alias));
  }
  void append_cell(std::string s, AggrOp aggr)
  {
    append_cell(TupleCellSpec(s, aggr));
  }
  void append_cell(const char *alias)
  {
    append_cell(TupleCellSpec(alias));
  }
  int cell_num() const
  {
    return static_cast<int>(cells_.size());
  }
  const TupleCellSpec &cell_at(int i) const
  {
    return cells_[i];
  }

private:
  std::vector<TupleCellSpec> cells_;
};

/**
 * @brief 元组的抽象描述
 * @ingroup Tuple
 */
class Tuple 
{
public:
  Tuple() = default;
  virtual ~Tuple() = default;

  /**
   * @brief 获取元组中的Cell的个数
   * @details 个数应该与tuple_schema一致
   */
  virtual int cell_num() const = 0;

  virtual int type() const = 0;
  //为了深拷贝 来选择派生类类型来构造函数

  /**
   * @brief 获取指定位置的Cell
   * 
   * @param index 位置
   * @param[out] cell  返回的Cell
   */
  virtual RC cell_at(int index, Value &cell) const = 0;

  virtual Tuple* getTuple() = 0;
  virtual std::vector<TupleCellSpec *> &getspeces_() = 0;

  /**
   * @brief 根据cell的描述，获取cell的值
   * 
   * @param spec cell的描述
   * @param[out] cell 返回的cell
   */
  virtual RC find_cell(const TupleCellSpec &spec, Value &cell, int index) const = 0;

  virtual std::string to_string() const
  {
    std::string str;
    const int cell_num = this->cell_num();
    for (int i = 0; i < cell_num - 1; i++) {
      Value cell;
      cell_at(i, cell);
      str += cell.to_string();
      str += ", ";
    }

    if (cell_num > 0) {
      Value cell;
      cell_at(cell_num - 1, cell);
      str += cell.to_string();
    }
    return str;
  }
};

/**
 * @brief 一行数据的元组
 * @ingroup Tuple
 * @details 直接就是获取表中的一条记录
 */
class RowTuple : public Tuple 
{
public:
  RowTuple() = default;
  virtual ~RowTuple()
  {
    for (FieldExpr *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }
  Tuple* getTuple()
  {
      return nullptr;
  }
  std::vector<TupleCellSpec *> &getspeces_(){
    std::vector<TupleCellSpec *> aa;
    return aa;
  }

  void set_record(Record *record)
  {
    this->record_ = record;
    const Field filed_ = this->speces_.back()->field();
    const FieldMeta *null_filed_meta = filed_.meta();
    bitmap_.init(record->data() + null_filed_meta->offset(), null_filed_meta->len());
  }

  int type() const
  {
    return 0;
  }

  void set_schema(const Table *table, const std::vector<FieldMeta> *fields)
  {
    table_ = table;
    this->speces_.reserve(fields->size());
    for (const FieldMeta &field : *fields) {
      speces_.push_back(new FieldExpr(table, &field));
    }
  }

  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    //const FieldMeta *null_field = table_->table_meta().null_bitmap_field();
    //common::Bitmap bitmap(const_cast<char *>(record_->data()) + null_field->offset(), null_field->len());
    if(table_->table_meta().field(index)->nullable()==true&&bitmap_.get_bit(index))
    {
      //当该值为NULL时
      cell.set_type(AttrType::NULLS);
      //cell.set_data(this->record_->data() + null_field->offset(), field_meta->len());
      //cell.set_data(this->record_->data() + null_field->offset(), field_meta->len());
      //cell.set_data(this->record_->data() + field_meta->offset(), field_meta->len());
      return RC::SUCCESS;
    }
    else{
      FieldExpr *field_expr = speces_[index];
      const FieldMeta *field_meta = field_expr->field().meta();
      //TODONULL 在这里加一个判断 如果这个record的null_field指示这个字段为NULL，则返回NOT_FOUND
      cell.set_type(field_meta->type());
      cell.set_data(this->record_->data() + field_meta->offset(), field_meta->len());
      return RC::SUCCESS;
    }
   
  }

  RC find_cell(const TupleCellSpec &spec, Value &cell, int index) const override
  {
    const char *table_name = spec.table_name();
    const char *field_name = spec.field_name();
    if (0 != strcmp(table_name, table_->name())) { //表名不对
      return RC::NOTFOUND;
    }

    for (size_t i = 0; i < speces_.size(); ++i) {
      const FieldExpr *field_expr = speces_[i];
      const Field &field = field_expr->field();
      if (0 == strcmp(field_name, field.field_name())) {
        return cell_at(i, cell);//找到字段后 赋赋值给cell Value类型
      }
    }
    return RC::NOTFOUND;
  }


#if 0
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }
#endif

  Record &record()
  {
    return *record_;
  }

  const Record &record() const
  {
    return *record_;
  }

private:
  common::Bitmap bitmap_;
  Record *record_ = nullptr;
  const Table *table_ = nullptr;
  std::vector<FieldExpr *> speces_;
};

/**
 * @brief 从一行数据中，选择部分字段组成的元组，也就是投影操作
 * @ingroup Tuple
 * @details 一般在select语句中使用。
 * 投影也可以是很复杂的操作，比如某些字段需要做类型转换、重命名、表达式运算、函数计算等。
 * 当前的实现是比较简单的，只是选择部分字段，不做任何其他操作。
 */
class ProjectTuple : public Tuple 
{
public:
  ProjectTuple() = default;
  virtual ~ProjectTuple()
  {
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_tuple(Tuple *tuple)
  {
    this->tuple_ = tuple;
  }

   void set_speces(std::vector<TupleCellSpec *> &speces)
  {
    this->speces_ = speces;
  }

  
  int type() const
  {
    return 1;
  }

  void add_cell_spec(TupleCellSpec *spec)
  {
    speces_.push_back(spec);
  }
  int cell_num() const override
  {
    return speces_.size();
  }
  //  void get_record(CompoundRecord &record) const override
  // {
  //   record.emplace_back(record_);
  // }
  Tuple* getTuple()
  {

    return tuple_;
  }

  Tuple* setMyTuple(Tuple *tuple)
  {
    switch(tuple->type())
    {
      case 0:{
        RowTuple *tuple = new RowTuple();    
      }
    }
  }
  std::vector<TupleCellSpec *> &getspeces_()
  {
    return speces_;
  }


  RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::INTERNAL;
    }
    if (tuple_ == nullptr) {
      return RC::INTERNAL;
    }

    const TupleCellSpec *spec = speces_[index];
    return tuple_->find_cell(*spec, cell, index);
  }

  RC find_cell(const TupleCellSpec &spec, Value &cell, int index) const override
  {
    return tuple_->find_cell(spec, cell, index);
  }

#if 0
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::NOTFOUND;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }
#endif
private:
  std::vector<TupleCellSpec *> speces_;
  Tuple *tuple_ = nullptr;
};

class ExpressionTuple : public Tuple 
{
public:
  ExpressionTuple(std::vector<std::unique_ptr<Expression>> &expressions)
    : expressions_(expressions)
  {}
  
  virtual ~ExpressionTuple(){}
  
  Tuple* getTuple()
  {
      return nullptr;
  }
  std::vector<TupleCellSpec *> &getspeces_()
  {
    std::vector<TupleCellSpec *> aa;
    return aa;
  }

  int type() const
  {
    return 2;
  }

  int cell_num() const override
  {
    return expressions_.size();
  }

  RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(expressions_.size())) {
      return RC::INTERNAL;
    }
    const Expression *expr = expressions_[index].get();
    return expr->try_get_value(cell);
  }

  RC find_cell(const TupleCellSpec &spec, Value &cell, int index) const override
  {
    for (const std::unique_ptr<Expression> &expr : expressions_) {
      if (0 == strcmp(spec.alias(), expr->name().c_str())) {
        return expr->try_get_value(cell);
      }
    }
    return RC::NOTFOUND;
  }

  RC get_expr_value(Tuple &tuple, Value &value, int index)
  {
    if (index < 0 || index >= static_cast<int>(expressions_.size())) {
      return RC::INTERNAL;
    }
    Expression *expr = expressions_[index].get();
    return expr->get_expr_value(tuple, value);
  }

private:
  const std::vector<std::unique_ptr<Expression>> &expressions_;
};

/**
 * @brief 一些常量值组成的Tuple
 * @ingroup Tuple
 */
class ValueListTuple : public Tuple 
{
public:
  ValueListTuple() = default;
  virtual ~ValueListTuple() = default;

  void set_cells(const std::vector<Value> &cells)
  {
    cells_ = cells;
  }

  void set_specs(const std::vector<Field> &specs)
  {
    spec_ = specs;
  }

  std::vector<Value> get_cells()
  {
    return cells_;
  }

  std::vector<Field> get_specs()
  {
    return spec_;
  }

   Tuple* getTuple()
  {
      return nullptr;
  }
  std::vector<TupleCellSpec *> &getspeces_(){
    std::vector<TupleCellSpec *> aa;
    return aa;
  }

  virtual int cell_num() const override
  {
    return static_cast<int>(cells_.size());
  }

  int type() const
  {
    return 3;
  }

  virtual RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= cell_num()) {
      return RC::NOTFOUND;
    }

    cell = cells_[index];
    return RC::SUCCESS;
  }

  virtual RC find_cell(const TupleCellSpec &spec, Value &cell, int index) const override
  {
    //return RC::INTERNAL;
    cell_at(index, cell);
    return RC::SUCCESS;
  }

  int compare_valueList(const ValueListTuple &other) const 
  {
    if(this == &other){
      return 0;
    }
    for(size_t i = 0; i < cell_num(); i++){
      Value this_cell, other_cell;
      this->cell_at(i, this_cell);
      other.cell_at(i, other_cell);
      int cmp_result = this_cell.compare(other_cell);
      if(cmp_result != 0) {
        return cmp_result;
      }
    }
    return 0;
  }

private:
  std::vector<Value> cells_;
  std::vector<Field> spec_;
  int index_ = 0;
};

/**
 * @brief 将两个tuple合并为一个tuple
 * @ingroup Tuple
 * @details 在join算子中使用
 */
class JoinedTuple : public Tuple 
{
public:
  JoinedTuple() = default;
  virtual ~JoinedTuple() = default;

  void set_left(Tuple *left)
  {
    left_ = left;
  }
  void set_right(Tuple *right)
  {
    right_ = right;
  }

  int cell_num() const override
  {
    return left_->cell_num() + right_->cell_num();
  }

  int type() const
  {
    return 4;
  }

   Tuple* getTuple()
  {
      return nullptr;
  }
  std::vector<TupleCellSpec *> &getspeces_(){
    std::vector<TupleCellSpec *> aa;
    return aa;
  }

  RC cell_at(int index, Value &value) const override
  {
    const int left_cell_num = left_->cell_num();
    if (index > 0 && index < left_cell_num) {
      return left_->cell_at(index, value);
    }

    if (index >= left_cell_num && index < left_cell_num + right_->cell_num()) {
      return right_->cell_at(index - left_cell_num, value);
    }

    return RC::NOTFOUND;
  }

  RC find_cell(const TupleCellSpec &spec, Value &value, int index) const override
  {
    RC rc = left_->find_cell(spec, value, index);
    if (rc == RC::SUCCESS || rc != RC::NOTFOUND) {
      return rc;
    }

    return right_->find_cell(spec, value, index);
  }

private:
  Tuple *left_ = nullptr;
  Tuple *right_ = nullptr;
};

//typedef std::vector<ProjectTuple*> CompoundTuple;

/**
 * @brief 一些常量值组成的Tuple
 * @ingroup Tuple
 */
class AggreListTuple : public Tuple 
{
public:
  AggreListTuple() = default;
  virtual ~AggreListTuple() = default;

  void set_cells(const std::vector<Value> &cells)
  {
    cells_ = cells;
  }
  void set_specs(const std::vector<std::string> &specs)
  {
    spec_ = specs;
  }
  void set_aggre(const std::vector<AggrOp> &aggr)
  {
    aggr_ = aggr;
  }

  //not used
  Tuple* getTuple()
  {
    return nullptr;
  }
  std::vector<TupleCellSpec *> &getspeces_(){
    std::vector<TupleCellSpec *> aa;
    return aa;
  }

  virtual int cell_num() const override
  {
    return static_cast<int>(cells_.size());
  }

  int type() const
  {
    return 5;
  }

  virtual RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= cell_num()) {
      return RC::NOTFOUND;
    }
    cell = cells_[index];
    return RC::SUCCESS;
  }

  virtual RC find_cell(const TupleCellSpec &spec, Value &cell, int index) const override
  {
    const char *s = spec.alias();
    AggrOp op = spec.aggr_name();

    for (size_t i = 0; i < spec_.size(); ++i) {
      const char *aggr_s = spec_[i].c_str();
      AggrOp aggr_op = aggr_[i];
      if (0 == strcmp(s, aggr_s)) {
        if(op == aggr_op){
          return cell_at(i, cell);
        }
      }
    }
    return RC::NOTFOUND;
  }

private:
  std::vector<Value> cells_;
  std::vector<std::string> spec_;
  std::vector<AggrOp> aggr_;
};

class Key
{
public:
  Key() = default;
  ~Key() = default;

  void set_valueList(const ValueListTuple &cur)
  {
    key_ = cur;
  }

  std::vector<Value> get_value()
  {
    return key_.get_cells();
  }

  std::vector<Field> get_field()
  {
    return key_.get_specs();
  }

  bool operator < (const Key &other) const
  {
    return (key_.compare_valueList(other.key_) < 0);
  }

private:
  ValueListTuple key_;
};