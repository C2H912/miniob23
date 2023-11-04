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
    const std::vector<std::string> &spec, std::unique_ptr<Expression> expr, bool having_flag)
:fields_(fields), aggr_fields_(aggr_fields), spec_(spec), expression_(std::move(expr)), having_flag_(having_flag)
{}

AggrePhysicalOperator::AggrePhysicalOperator(const std::vector<Field> &fields, const std::vector<AggrOp> &aggr_fields,
    const std::vector<std::string> &spec, bool having_flag)
:fields_(fields), aggr_fields_(aggr_fields), spec_(spec), having_flag_(having_flag)
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
  //这里控制火山的执行，第一次进入时执行，之后进入只是读取结果而已，直到读取到记录尾下次进入就重新执行
  if(enter_flag_ == true){
    scan_index_++;
    if(scan_index_ == (int)tuple_.size()){
      enter_flag_ = false;
      tuple_.clear();
      return RC::RECORD_EOF;
    }
    else{
      return RC::SUCCESS;
    }
  }
  else{
    scan_index_ = 0;
    enter_flag_ = true;
  }

  RC rc = RC::SUCCESS;
  PhysicalOperator *oper = children_.front().get();

/*
 * 其实像下面这样写不太好，但是兼容的成本低，不用大改
 */
// ------------- case 1: 下面是GROUP算子 --------------
  if(oper->type() == PhysicalOperatorType::GROUP){
    std::map<Key, std::vector<ValueListTuple>> group_result;
    rc = oper->next();
    if(rc != RC::SUCCESS){
      LOG_WARN("GROUP BY FAILED\n");
      return rc;
    }
    group_result = oper->current_group();
    rc = do_group_aggre(group_result);
    if(rc != RC::SUCCESS && rc != RC::RECORD_EOF){
      LOG_WARN("GROUP BY AGGRE FAILED\n");
      return rc;
    }
    return rc;
  }
// ---------------- case 2: 一般情况 ------------------
  else{
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
    if (rc != RC::RECORD_EOF) {
      return rc;
    }
    
    if((int)all_tuple.size() == 0){
      return RC::RECORD_EOF;
    }
    rc = do_aggre_func(all_tuple);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  return rc;
}

RC AggrePhysicalOperator::do_group_aggre(std::map<Key, std::vector<ValueListTuple>>& groups)
{
  RC rc = RC::SUCCESS;
  
  //取出每个组
  for(const auto& group : groups){
    //当前组的数据, 将每个组的非聚合部分写入结果
    AggreListTuple current_group;
    std::vector<Value> group_cells;
    Key current_key = group.first;
    group_cells = current_key.get_value();
    current_group.set_specs(spec_);
    current_group.set_aggre(aggr_fields_);

    //对剩下的部分进行聚合
    std::vector<ValueListTuple> group_aggre = group.second;
    std::vector<std::vector<Value>> aggre_values;
    for(size_t j = 0; j < group_aggre.size(); j++){
      aggre_values.push_back(group_aggre[j].get_cells());
    }
    std::vector<Value> ret_tuple;
    for(size_t i = group_cells.size(); i < (int)fields_.size(); i++){
      if(aggr_fields_[i] == COUNTF){
        if(spec_[i] == "*"){
          Value ret;
          ret.set_int((int)aggre_values.size());
          ret_tuple.push_back(ret);
          continue;
        }
        else{
          int count = 0;
          for(int j = 0; j < (int)aggre_values.size(); j++){
            if(aggre_values[j][i].attr_type() == NULLS){
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
        ret_tuple.push_back(do_int(aggre_values, i));
        break;
      }
      case CHARS:{
        ret_tuple.push_back(do_char(aggre_values, i));
        break;
      }
      case FLOATS:{
        ret_tuple.push_back(do_float(aggre_values, i));
        break;
      }
      case DATES:{
        ret_tuple.push_back(do_date(aggre_values, i));
        break;
      }
      default: {
        LOG_ERROR("Unsupported type\n");
      }
      }
    }
    for(size_t k = 0; k < ret_tuple.size(); k++){
      group_cells.push_back(ret_tuple[k]);
    }

    //检查having
    if(having_flag_ == true){
      //当前结果ListTuple
      AggreListTuple having_tuple;
      having_tuple.set_cells(group_cells);
      having_tuple.set_specs(spec_);
      having_tuple.set_aggre(aggr_fields_);
      Tuple *tuple = static_cast<Tuple*>(&having_tuple);
      //通过tuple计算value的值
      Value value;
      rc = expression_->get_value(*tuple, value);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      //判断是否应该写入
      if (value.get_boolean()) {
        current_group.set_cells(group_cells);
        tuple_.push_back(current_group);
        continue;
      }
      else{
        continue;
      }
    }

    //没有HAVING的话直接写入结果
    current_group.set_cells(group_cells);
    tuple_.push_back(current_group);
  }

  if((int)tuple_.size() == 0){
    enter_flag_ = false;
    return RC::RECORD_EOF;
  }

  return RC::SUCCESS;
}

RC AggrePhysicalOperator::do_aggre_func(std::vector<std::vector<Value>>& all_tuple)
{
  std::vector<Value> ret_tuple;
  for(int i = 0; i < (int)fields_.size(); i++){
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
  AggreListTuple result;
  result.set_cells(ret_tuple);
  result.set_specs(spec_);
  result.set_aggre(aggr_fields_);
  tuple_.push_back(result);
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
  return static_cast<Tuple*>(&tuple_[scan_index_]);
}
