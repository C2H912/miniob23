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
#include "sql/operator/aggre_physical_operator.h"
#include "storage/record/record.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/field/field.h"

AggrePhysicalOperator::AggrePhysicalOperator(const std::vector<Field> &fields, const std::vector<AggrOp> &aggr_fields)
: fields_(fields), aggr_fields_(aggr_fields)
{}

RC AggrePhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->open(trx);
}

RC AggrePhysicalOperator::next()
{
  if(enter_flag_ == true){
    return RC::RECORD_EOF;
  }

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

    std::vector<Value> one_tuple;
    for(int i = 0; i < (int)fields_.size(); i++){
      Value value;
      FieldExpr field_exp(fields_[i]);
      rc = field_exp.get_value(*tuple, value);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      one_tuple.push_back(value);
    }

    all_tuple.push_back(one_tuple);
  }
  
  rc = do_aggre_func(all_tuple);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  enter_flag_ = true;

  return rc;
}

RC AggrePhysicalOperator::do_aggre_func(std::vector<std::vector<Value>>& all_tuple)
{
  std::vector<Value> ret_tuple;
  std::vector<Field> ret_specs;
  for(int i = 0; i < (int)fields_.size(); i++){
    Field ret_field;
    ret_field.set_table(fields_[i].table());
    ret_field.set_field(fields_[i].meta());
    ret_specs.push_back(ret_field);
    if(aggr_fields_[i] == COUNTF){
      Value ret;
      ret.set_int((int)all_tuple.size());
      ret_tuple.push_back(ret);
      continue;
    }
    switch(all_tuple[0][i].attr_type()){
    case INTS:{
      ret_tuple.push_back(do_int(all_tuple, i));
      break;
    }
    case CHARS:{
      //ret = do_char(all_tuple, i);
      break;
    }
    case FLOATS:{
      //ret = do_float(all_tuple, i);
      break;
    }
    //case DATES:{
    //  do_date(all_tuple, i);
    //  break;
    //}
    default: {
      LOG_ERROR("Unsupported type\n");
    }
    }
  }
  tuple_.set_cells(ret_tuple);
  tuple_.set_specs(ret_specs);
  return RC::SUCCESS;
}

Value AggrePhysicalOperator::do_int(std::vector<std::vector<Value>>& all_tuple, int index)
{
  int max_value = all_tuple[0][index].get_int();
  int min_value = all_tuple[0][index].get_int();
  int sum = 0;
  int avg = 0;

  int size = all_tuple.size();
  for(int i = 0; i < size; i++){
    Value tuplecell = all_tuple[i][index];
    int temp = tuplecell.get_int();
    if(max_value < temp){
      max_value = temp;
    }
    if(min_value > temp){
      min_value = temp;
    }
    sum += temp;
  }
  avg = sum / (int)all_tuple.size();

  Value ret;
  if(aggr_fields_[index] == MAXF){
    ret.set_int(max_value);
  }
  if(aggr_fields_[index] == MINF){
    ret.set_int(min_value);
  }
  if(aggr_fields_[index] == SUMF){
    ret.set_int(sum);
  }
  if(aggr_fields_[index] == AVGF){
    ret.set_int(avg);
  }

  return ret;
}

#if 0
Value AggrePhysicalOperator::do_char(std::vector<std::vector<Value>>& all_tuple, int index)
{
  char *max_value = (char *)(all_tuple[0][index].data());
  int max_length = all_tuple[0][index].length();
  char *min_value = (char *)(all_tuple[0][index].data());
  int min_length = all_tuple[0][index].length();
  double sum = 0.0;
  double avg = 0.0;

  int size = all_tuple.size();
  for(int i = 0; i < size; i++){
    TupleCell tuplecell = all_tuple[i][index];
    char *temp = (char *)(tuplecell.data());
    sum += strtod(temp, nullptr);
    if(compare_string(max_value, max_length, temp, tuplecell.length()) < 0){
      max_value = temp;
      max_length = tuplecell.length();
    }
    if(compare_string(min_value, min_length, temp, tuplecell.length()) > 0){
      min_value = temp;
      min_length = tuplecell.length();
    }
  }
  avg = sum / (int)all_tuple.size();

  char *str = new char[8];
  memset(str, 0, 8*sizeof(char));
  if(type == MAXF){
    TupleCell temp_cell(CHARS, strdup(max_value));
    temp_cell.set_length(max_length);
    result_tuple_.push_back(temp_cell);
  }
  if(type == MINF){
    TupleCell temp_cell(CHARS, strdup(min_value));
    temp_cell.set_length(max_length);
    result_tuple_.push_back(temp_cell);
  }
  if(type == SUMF){
    memcpy(str, &sum, sizeof(sum));
    TupleCell temp_cell(INTS, mystrdup(str));
    result_tuple_.push_back(temp_cell);
  }
  if(type == AVGF){
    memcpy(str, &avg, sizeof(avg));
    TupleCell temp_cell(INTS, mystrdup(str));
    result_tuple_.push_back(temp_cell);
  }
  delete str;
  str = nullptr;
}

Value AggrePhysicalOperator::do_float(std::vector<std::vector<Value>>& all_tuple, int index)
{
  float max_value = *(float *)(all_tuple[0][index].data());
  float min_value = *(float *)(all_tuple[0][index].data());
  float sum = 0;
  float avg = 0;

  int size = all_tuple.size();
  for(int i = 0; i < size; i++){
    TupleCell tuplecell = all_tuple[i][index];
    int temp = *(float *)(tuplecell.data());
    if(max_value < temp){
      max_value = temp;
    }
    if(min_value > temp){
      min_value = temp;
    }
    sum += temp;
  }
  avg = sum / (int)all_tuple.size();

  char *str = new char[8];
  memset(str, 0, 8*sizeof(char));
  if(type == MAXF){
    memcpy(str, &max_value, sizeof(max_value));
    TupleCell temp_cell(FLOATS, mystrdup(str));
    result_tuple_.push_back(temp_cell);
  }
  if(type == MINF){
    memcpy(str, &min_value, sizeof(min_value));
    TupleCell temp_cell(FLOATS, mystrdup(str));
    result_tuple_.push_back(temp_cell);
  }
  if(type == SUMF){
    memcpy(str, &sum, sizeof(sum));
    TupleCell temp_cell(FLOATS, mystrdup(str));
    result_tuple_.push_back(temp_cell);
  }
  if(type == AVGF){
    memcpy(str, &avg, sizeof(avg));
    TupleCell temp_cell(FLOATS, mystrdup(str));
    result_tuple_.push_back(temp_cell);
  }
  delete str;
  str = nullptr;
}
#endif

RC AggrePhysicalOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *AggrePhysicalOperator::current_tuple()
{
  return static_cast<Tuple*>(&tuple_);
}
