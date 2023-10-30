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

AggrePhysicalOperator::AggrePhysicalOperator(const std::vector<Field> &fields, const std::vector<AggrOp> &aggr_fields,
    const std::vector<std::string> &spec)
:fields_(fields), aggr_fields_(aggr_fields), spec_(spec)
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
  
  if((int)all_tuple.size() == 0){
    return RC::RECORD_EOF;
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
      if(spec_[i] == "*"){
        Value ret;
        ret.set_int((int)all_tuple.size());
        ret_tuple.push_back(ret);
        continue;
      }
      else{
        int count = 0;
        for(int j = 0; j < (int)all_tuple.size(); j++){
          if(all_tuple[j][i].attr_type() == NULLS){
            continue;
          }
          else{
            count++;
          }
        }
        Value ret;
        ret.set_int(count);
        ret_tuple.push_back(ret);
        continue;
      }
    }
    switch(fields_[i].attr_type()){
    case INTS:{
      ret_tuple.push_back(do_int(all_tuple, i));
      break;
    }
    case CHARS:{
      ret_tuple.push_back(do_char(all_tuple, i));
      break;
    }
    case FLOATS:{
      ret_tuple.push_back(do_float(all_tuple, i));
      break;
    }
    case DATES:{
      ret_tuple.push_back(do_date(all_tuple, i));
      break;
    }
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
  Value max_value(all_tuple[0][index]);
  Value min_value(all_tuple[0][index]);
  int sum = 0;
  float avg = 0.0;

  int size = all_tuple.size();
  for(int i = 0; i < size; i++){
    Value tuplecell = all_tuple[i][index];
    if(tuplecell.attr_type() == NULLS){
      continue;
    }
    int temp = tuplecell.get_int();
    if(max_value.attr_type() == NULLS){
      max_value = tuplecell;
    }
    else{
      if(max_value.get_int() < temp){
        max_value = tuplecell;
      }
    }
    if(min_value.attr_type() == NULLS){
      //
    }
    else{
      if(min_value.get_int() > temp){
        min_value = tuplecell;
      }
    }
    sum += temp;
  }

  int count = 0;
  for(int j = 0; j < (int)all_tuple.size(); j++){
    if(all_tuple[j][index].attr_type() == NULLS){
      continue;
    }
    else{
      count++;
    }
  }
  if(count == 0){
    avg = 0.0;
  }
  else{
    avg = (float)sum / (float)count;
  }

  Value ret;
  if(aggr_fields_[index] == MAXF){
    ret = max_value;
  }
  if(aggr_fields_[index] == MINF){
    ret = min_value;
  }
  if(aggr_fields_[index] == SUMF){
    if(count == 0){
      ret.set_null_value();
    }
    else{
      ret.set_int(sum);
    }
  }
  if(aggr_fields_[index] == AVGF){
    if(count == 0){
      ret.set_null_value();
    }
    else{
      ret.set_float(avg);
    }
  }

  return ret;
}

Value AggrePhysicalOperator::do_char(std::vector<std::vector<Value>>& all_tuple, int index)
{
  Value max_value(all_tuple[0][index]);
  Value min_value(all_tuple[0][index]);
  float sum = 0.0;
  float avg = 0.0;

  int size = all_tuple.size();
  for(int i = 0; i < size; i++){
    Value tuplecell(all_tuple[i][index]);
    if(tuplecell.attr_type() == NULLS){
      continue;
    }
    if(max_value.attr_type() == NULLS){
      max_value = tuplecell;
    }
    else{
      if((max_value.compare(tuplecell)) < 0){
        max_value = tuplecell;
      }
    }
    if(min_value.attr_type() == NULLS){
      //
    }
    else{
      if((min_value.compare(tuplecell)) > 0){
        min_value = tuplecell;
      }
    }
    sum += strtod(tuplecell.data(), nullptr);
  }

  int count = 0;
  for(int j = 0; j < (int)all_tuple.size(); j++){
    if(all_tuple[j][index].attr_type() == NULLS){
      continue;
    }
    else{
      count++;
    }
  }
  if(count == 0){
    avg = 0.0;
  }
  else{
    avg = (float)sum / (float)count;
  }

  Value ret;
  if(aggr_fields_[index] == MAXF){
    ret = max_value;
  }
  if(aggr_fields_[index] == MINF){
    ret = min_value;
  }
  if(aggr_fields_[index] == SUMF){
    if(count == 0){
      ret.set_null_value();
    }
    else{
      ret.set_float(sum);
    }
  }
  if(aggr_fields_[index] == AVGF){
    if(count == 0){
      ret.set_null_value();
    }
    else{
      ret.set_float(avg);
    }
  }

  return ret;
}

Value AggrePhysicalOperator::do_float(std::vector<std::vector<Value>>& all_tuple, int index)
{
  Value max_value(all_tuple[0][index]);
  Value min_value(all_tuple[0][index]);
  float sum = 0;
  float avg = 0;

  int size = all_tuple.size();
  for(int i = 0; i < size; i++){
    Value tuplecell = all_tuple[i][index];
    if(tuplecell.attr_type() == NULLS){
      continue;
    }
    float temp = tuplecell.get_float();
    if(max_value.attr_type() == NULLS){
      max_value = tuplecell;
    }
    else{
      if(max_value.get_float() < temp){
        max_value = tuplecell;
      }
    }
    if(min_value.attr_type() == NULLS){
      //
    }
    else{
      if(min_value.get_float() > temp){
        min_value = tuplecell;
      }
    }
    sum += temp;
  }

  int count = 0;
  for(int j = 0; j < (int)all_tuple.size(); j++){
    if(all_tuple[j][index].attr_type() == NULLS){
      continue;
    }
    else{
      count++;
    }
  }
  if(count == 0){
    avg = 0.0;
  }
  else{
    avg = (float)sum / (float)count;
  }

  Value ret;
  if(aggr_fields_[index] == MAXF){
    ret = max_value;
  }
  if(aggr_fields_[index] == MINF){
    ret = min_value;
  }
  if(aggr_fields_[index] == SUMF){
    if(count == 0){
      ret.set_null_value();
    }
    else{
      ret.set_float(sum);
    }
  }
  if(aggr_fields_[index] == AVGF){
    if(count == 0){
      ret.set_null_value();
    }
    else{
      ret.set_float(avg);
    }
  }

  return ret;
}

Value AggrePhysicalOperator::do_date(std::vector<std::vector<Value>>& all_tuple, int index)
{
  Value max_value(all_tuple[0][index]);
  Value min_value(all_tuple[0][index]);
  int sum = 0;
  float avg = 0;

  int size = all_tuple.size();
  for(int i = 0; i < size; i++){
    Value tuplecell = all_tuple[i][index];
    if(tuplecell.attr_type() == NULLS){
      continue;
    }
    char* tmp = (char *)tuplecell.ret_str().c_str();
    int tempdate = date2int(tmp);
    tuplecell.set_only_int(tempdate);
    if(max_value.attr_type() == NULLS){
      max_value = tuplecell;
    }
    else{
      if(max_value.compare(tuplecell) < 0){
        max_value = tuplecell;
      }
    }
    if(min_value.attr_type() == NULLS){
      //
    }
    else{
      if(min_value.compare(tuplecell) > 0){
        min_value = tuplecell;
      }
    }
    sum += tempdate;
  }

  int count = 0;
  for(int j = 0; j < (int)all_tuple.size(); j++){
    if(all_tuple[j][index].attr_type() == NULLS){
      continue;
    }
    else{
      count++;
    }
  }
  if(count == 0){
    avg = 0.0;
  }
  else{
    avg = (float)sum / (float)count;
  }

  Value ret;
  if(aggr_fields_[index] == MAXF){
    ret = max_value;
  }
  if(aggr_fields_[index] == MINF){
    ret = min_value;
  }
  if(aggr_fields_[index] == SUMF){
    if(count == 0){
      ret.set_null_value();
    }
    else{
      ret.set_float(sum);
    }
  }
  if(aggr_fields_[index] == AVGF){
    if(count == 0){
      ret.set_null_value();
    }
    else{
      ret.set_float(avg);
    }
  }

  return ret;
}

RC AggrePhysicalOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *AggrePhysicalOperator::current_tuple()
{
  return static_cast<Tuple*>(&tuple_);
}
