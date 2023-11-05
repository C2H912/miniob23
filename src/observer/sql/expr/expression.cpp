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
// Created by Wangyunlai on 2022/07/05.
//

#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/stmt/select_stmt.h"
#include "sql/operator/physical_operator.h"
#include "sql/optimizer/optimize_stage.h"
#include <regex>
#include <cmath>
#include <iomanip>

using namespace std;

RC FieldExpr::get_value(Tuple &tuple, Value &value)
{
  return tuple.find_cell(TupleCellSpec(table_name(), field_name()), value, 0);
}
RC FieldExpr::get_expr_value(Tuple &tuple, Value &value)
{
  if(tuple.type() == 5){      //聚合
    return tuple.find_cell(TupleCellSpec(str_attribute_name().c_str(), aggr_name(), 0), value, 0);
  }
  return tuple.find_cell(TupleCellSpec(table_name(), field_name()), value, 0);
}

RC ComplexFieldExpr::get_value(Tuple &tuple, Value &value)
{
  return tuple.find_cell(TupleCellSpec(table_name(), field_name()), value, 0);
}
RC ComplexFieldExpr::get_expr_value(Tuple &tuple, Value &value)
{
  RC rc = tuple.find_cell(TupleCellSpec(table_name(), field_name()), value, 0);
  if(rc == RC::SUCCESS){
    return rc;
  }
  else{
    for(size_t i = 0; i < parents_tuples_.size(); i++){
      Tuple *current = parents_tuples_[i];
      rc = current->find_cell(TupleCellSpec(table_name(), field_name()), value, 0);
      if(rc == RC::SUCCESS){
        return rc;
      }
    }
  }
  return RC::NOTFOUND;
}


RC ValueExpr::get_value(Tuple &tuple, Value &value)
{
  value = value_;//用户输入的NULL的AttrType就为NULL，所以这里就不需要了
  return RC::SUCCESS;
}

//注意这里只提供一个get_value()的接口实现了纯虚函数的多态，实际上这个函数应该永远也不被调用！
RC ValueListExpr::get_value(Tuple &tuple, Value &value)
{
  return RC::SUCCESS;
}

//注意这里只提供一个get_value()的接口实现了纯虚函数的多态，实际上这个函数应该永远也不被调用！
RC SubQueryExpr::get_value(Tuple &tuple, Value &value)
{
  return RC::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
ValueListExpr::ValueListExpr(const std::vector<Value> &value_list)
  : value_list_(value_list)
{}

ValueListExpr::~ValueListExpr()
{}

SubQueryExpr::SubQueryExpr(std::vector<std::vector<Value>> &sub_table)
  : sub_table_(sub_table)
{}

SubQueryExpr::SubQueryExpr(SelectStmt *sub_select_stmt)
  : sub_select_stmt_(sub_select_stmt)
{}

SubQueryExpr::SubQueryExpr(SelectStmt *sub_select_stmt, std::vector<Tuple*> &parents_tuples)
  : sub_select_stmt_(sub_select_stmt), parents_tuples_(parents_tuples)
{}

SubQueryExpr::~SubQueryExpr()
{}

RC SubQueryExpr::get_expr_value(Tuple &outer_tuple, Value &value)
{
  //如果子火山为空先创建子火山
  if(!sub_volcano_){
    parents_tuples_.push_back(&outer_tuple);
    OptimizeStage caller;
    RC rc = caller.create_complex_sub_request(parents_tuples_, sub_select_stmt_, sub_volcano_);
    if(rc != RC::SUCCESS){
      LOG_WARN("failed to get SUB TABLE from operator");
      return rc;
    }
  }
  //执行子火山把结果写入到sub_table_中
  RC rc = RC::SUCCESS;
  sub_volcano_->open(nullptr);
  while (RC::SUCCESS == (rc = sub_volcano_->next())) {
    Tuple * tuple = sub_volcano_->current_tuple();
    std::vector<Value> row;
    for(int i = 0; i < tuple->cell_num(); i++){
      Value value;
      rc = tuple->cell_at(i, value);
      if (rc != RC::SUCCESS) {
        sub_volcano_->close();
        LOG_WARN("failed to get SUB TABLE from operator");
        return rc;
      }
      row.push_back(value);
    }
    sub_table_.push_back(row);
  }
  sub_volcano_->close();
  if (rc == RC::RECORD_EOF) {
    rc = RC::SUCCESS;
  }
  else{
    LOG_WARN("failed to get SUB TABLE from operator");
    return rc;
  }
}

/////////////////////////////////////////////////////////////////////////////////

CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type)
    : child_(std::move(child)), cast_type_(cast_type)
{}

CastExpr::~CastExpr()
{}

RC CastExpr::cast(const Value &value, Value &cast_value) const
{
  RC rc = RC::SUCCESS;
  if (this->value_type() == value.attr_type()) {
    cast_value = value;
    return rc;
  }

  switch (cast_type_) {
    case BOOLEANS: {
      bool val = value.get_boolean();
      cast_value.set_boolean(val);
    } break;
    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported convert from type %d to %d", child_->value_type(), cast_type_);
    }
  }
  return rc;
}

RC CastExpr::get_value(Tuple &tuple, Value &cell)
{
  RC rc = child_->get_value(tuple, cell);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(cell, cell);
}

RC CastExpr::try_get_value(Value &value) const
{
  RC rc = child_->try_get_value(value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, value);
}

////////////////////////////////////////////////////////////////////////////////

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right))
{}

ComparisonExpr::~ComparisonExpr()
{}

RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
{
  RC rc = RC::SUCCESS;

  if(IS_NULL==comp_&&left.attr_type()==AttrType::NULLS)//NULL IS NULL
  {
    result =true;
    return rc;
  }
  if(left.attr_type()==AttrType::NULLS||right.attr_type()==AttrType::NULLS){
    result =false;
    return rc;
  }

  if(comp_ == REGEX_LIKE || comp_ == REGEX_NOT_LIKE){
    std::string sentence = right.data();
    //生成模式
    std::string res;
    for(int i = 0; i < sentence.size(); i++){
      if(sentence[i] == '%'){
        res.push_back('.');
        res.push_back('*');
      }
      else if(sentence[i] == '_'){
        //res.push_back('\\');
        res.push_back('.');
      }
      else{
        res.push_back(sentence[i]);
      }
    }
    std::regex pattern(res);
    //进行匹配
    std::string line = left.data();
    std::smatch matches;
    result = true;
    if(!regex_match(line, matches, pattern) && comp_ == REGEX_LIKE){
      result = false;
    }
    if(regex_match(line, matches, pattern) && comp_ == REGEX_NOT_LIKE){
      result =  false;
    }
    return RC::SUCCESS;
  }

  int cmp_result = left.compare(right);
  result = false;
  switch (comp_) {
    case EQUAL_TO: {
      result = (0 == cmp_result);
    } break;
    case LESS_EQUAL: {
      result = (cmp_result <= 0);
    } break;
    case NOT_EQUAL: {
      result = (cmp_result != 0);
    } break;
    case LESS_THAN: {
      result = (cmp_result < 0);
    } break;
    case GREAT_EQUAL: {
      result = (cmp_result >= 0);
    } break;
    case GREAT_THAN: {
      result = (cmp_result > 0);
    } break;
    default: {
      LOG_WARN("unsupported comparison. %d", comp_);
      rc = RC::INTERNAL;
    } break;
  }

  return rc;
}

RC ComparisonExpr::try_get_value(Value &cell) const //尝试直接获取表达式的值
{
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr *left_value_expr = static_cast<ValueExpr *>(left_.get());
    ValueExpr *right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell = left_value_expr->get_value();
    const Value &right_cell = right_value_expr->get_value();

    bool value = false;
    RC rc = compare_value(left_cell, right_cell, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(Tuple &tuple, Value &value)
{
  // ------------ IN、EXISTS、IS_NULL ------------
  //1. IN
  if(comp_ == IN_QUERY || comp_ == NOT_IN_QUERY){
    //读取左值
    Value left_value;
    RC rc = left_->get_expr_value(tuple, left_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
      return rc;
    }
    //返回子表
    if(right_->type() == ExprType::VALUELIST){
      //
    }
    else{
      Value not_used;
      rc = right_->get_expr_value(tuple, not_used);
      if(rc != RC::SUCCESS){
        LOG_WARN("failed to get SUB TABLE from operator");
        return rc;
      }
    }
    std::vector<std::vector<Value>> sub_table = right_->sub_table();
    right_->clear_table();    //非常关键，不然越push_back越多
    if ((int)sub_table.size() == 0) {
      if(comp_ == NOT_IN_QUERY){
        value.set_boolean(true);
        return RC::SUCCESS;
      }
      else{
        value.set_boolean(false);
        return RC::SUCCESS;
      }
    }
    if(sub_table[0].size() > 1){
      LOG_WARN("IN column is more than one!");
      return RC::INVALID_ARGUMENT;
    }
    //判断是否IN
    size_t i = 0;
    for(i = 0; i < sub_table.size(); i++){
      Value right_value = sub_table[i][0];
      int cmp_result = left_value.compare(right_value);
      if(cmp_result == 0){
        break;
      }
    }
    if(i == sub_table.size()){
      if(comp_ == IN_QUERY){
        value.set_boolean(false);
        return RC::SUCCESS;
      }
      if(comp_ == NOT_IN_QUERY){
        value.set_boolean(true);
        return RC::SUCCESS;
      }
    }
    else{
      if(comp_ == IN_QUERY){
        value.set_boolean(true);
        return RC::SUCCESS;
      }
      if(comp_ == NOT_IN_QUERY){
        value.set_boolean(false);
        return RC::SUCCESS;
      }
    }
  }
  //2. EXISTS
  if(comp_ == EXISTS_QUERY || comp_ == NOT_EXISTS_QUERY){
    //返回子表
    Value not_used;
    RC rc = right_->get_expr_value(tuple, not_used);
    if(rc != RC::SUCCESS){
      LOG_WARN("failed to get SUB TABLE from operator");
      return rc;
    }
    std::vector<std::vector<Value>> sub_table = right_->sub_table();
    right_->clear_table();
    //判断
    if((int)sub_table.size() > 0){
      value.set_boolean(true);
      return RC::SUCCESS;
    }
    else{
      value.set_boolean(false);
      return RC::SUCCESS;
    }
  }
  //3. IS NULL
  if(comp_ == IS_NULL || comp_ == IS_NOT_NULL){
    Value left_v;
    Value right_v;
    RC rc = left_->get_expr_value(tuple, left_v);
    if(left_v.attr_type() == NULLS && comp_ == IS_NULL){
      value.set_boolean(true);
      return RC::SUCCESS;
    }
    if(left_v.attr_type() != NULLS && comp_ == IS_NULL){
      value.set_boolean(false);
      return RC::SUCCESS;
    }
    if(left_v.attr_type() == NULLS && comp_ == IS_NOT_NULL){
      value.set_boolean(false);
      return RC::SUCCESS;
    }
    if(left_v.attr_type() != NULLS && comp_ == IS_NOT_NULL){
      value.set_boolean(true);
      return RC::SUCCESS;
    }
  }

  // ---------- 一般的比较语句 -----------
  Value left_value;
  Value right_value;
  RC rc = RC::SUCCESS;

  if(left_->type() == ExprType::QUERY){
    Value not_used;
    rc = left_->get_expr_value(tuple, not_used);
    if(rc != RC::SUCCESS){
      LOG_WARN("failed to get SUB TABLE from operator\n");
      return rc;
    }
    std::vector<std::vector<Value>> left_sub_table = left_->sub_table();
    left_->clear_table();
    if((int)left_sub_table.size() == 0){
      value.set_boolean(false);
      return RC::SUCCESS;
      //LOG_WARN("EMPTY TABLE\n");
      //return RC::EMPTY;
    }
    if((int)left_sub_table.size() > 1 || (int)left_sub_table[0].size() > 1){
      LOG_WARN("table size is incorrect\n");
      return RC::INVALID_ARGUMENT;
    }
    left_value = left_sub_table[0][0];
  }
  else{
    rc = left_->get_expr_value(tuple, left_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of left expression. rc=%s\n", strrc(rc));
      return rc;
    }
  }

  int right_type = right_->expr_type();
  if(right_->type() == ExprType::QUERY){
    Value not_used;
    rc = right_->get_expr_value(tuple, not_used);
    if(rc != RC::SUCCESS){
      LOG_WARN("failed to get SUB TABLE from operator\n");
      return rc;
    }
    std::vector<std::vector<Value>> right_sub_table = right_->sub_table();
    right_->clear_table();
    if((int)right_sub_table.size() == 0){
      value.set_boolean(false);
      return RC::SUCCESS;
      //LOG_WARN("EMPTY TABLE\n");
      //return RC::EMPTY;
    }
    if((int)right_sub_table.size() > 1 || (int)right_sub_table[0].size() > 1){
      LOG_WARN("table size is incorrect\n");
      return RC::INVALID_ARGUMENT;
    }
    right_value = right_sub_table[0][0];
  }
  else{
    rc = right_->get_expr_value(tuple, right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of left expression. rc=%s\n", strrc(rc));
      return rc;
    }
  }

  bool bool_value = false;
  rc = compare_value(left_value, right_value, bool_value);
  if (rc == RC::SUCCESS) {
    value.set_boolean(bool_value);
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
ConjunctionExpr::ConjunctionExpr(Type type, vector<unique_ptr<Expression>> &children)
    : conjunction_type_(type), children_(std::move(children))
{}

RC ConjunctionExpr::get_value(Tuple &tuple, Value &value)
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    value.set_boolean(true);
    return rc;
  }

  Value tmp_value;
  for (const unique_ptr<Expression> &expr : children_) {
    rc = expr->get_value(tuple, tmp_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
      return rc;
    }
    bool bool_value = tmp_value.get_boolean();
    if ((conjunction_type_ == Type::AND && !bool_value) || (conjunction_type_ == Type::OR && bool_value)) {
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
  value.set_boolean(default_value);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left, Expression *right)
    : arithmetic_type_(type), left_(left), right_(right)
{}
ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : arithmetic_type_(type), left_(std::move(left)), right_(std::move(right))
{}

AttrType ArithmeticExpr::value_type() const
{
  if (!right_) {
    return left_->value_type();
  }

  if (left_->value_type() == AttrType::INTS &&
      right_->value_type() == AttrType::INTS &&
      arithmetic_type_ != Type::DIV) {
    return AttrType::INTS;
  }
  
  return AttrType::FLOATS;
}

RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();

  switch (arithmetic_type_) {
    case Type::ADD: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() + right_value.get_int());
      } else {
        value.set_float(left_value.get_float() + right_value.get_float());
      }
    } break;

    case Type::SUB: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() - right_value.get_int());
      } else {
        value.set_float(left_value.get_float() - right_value.get_float());
      }
    } break;

    case Type::MUL: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() * right_value.get_int());
      } else {
        value.set_float(left_value.get_float() * right_value.get_float());
      }
    } break;

    case Type::DIV: {
      if (target_type == AttrType::INTS) {
        if (right_value.get_int() == 0) {
          // NOTE: 设置为整数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为整数最大值。
          value.set_int(numeric_limits<int>::max());
        } else {
          value.set_int(left_value.get_int() / right_value.get_int());
        }
      } else {
        if (right_value.get_float() > -EPSILON && right_value.get_float() < EPSILON) {
          // NOTE: 设置为浮点数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为浮点数最大值。
          value.set_float(numeric_limits<float>::max());
        } else {
          value.set_float(left_value.get_float() / right_value.get_float());
        }
      }
    } break;

    case Type::NEGATIVE: {
      if (target_type == AttrType::INTS) {
        value.set_int(-left_value.get_int());
      } else {
        value.set_float(-left_value.get_float());
      }
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
    } break;
  }
  return rc;
}

RC ArithmeticExpr::get_value(Tuple &tuple, Value &value)
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_value(left_value, right_value, value);
}

RC ArithmeticExpr::try_get_value(Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

////////////////////////////////////////////////////////////////////////////////

ALUExpr::ALUExpr(ALUExpr::Type2 type, Expression *left, Expression *right)
    : alu_type_(type), left_(left), right_(right)
{}

AttrType ALUExpr::value_type() const
{
  if (!right_) {
    return left_->value_type();
  }
  if (left_->value_type() == AttrType::INTS &&
      right_->value_type() == AttrType::INTS &&
      alu_type_ != Type2::DIV) {
    return AttrType::INTS;
  } 
  return AttrType::FLOATS;
}

RC ALUExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  if(left_value.attr_type() == NULLS || right_value.attr_type() == NULLS){
    value.set_null_value();
    return RC::SUCCESS;
  }

  const AttrType target_type = value_type();

  switch (alu_type_) {
    case Type2::ADD: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() + right_value.get_int());
      } else {
        value.set_float(left_value.get_float() + right_value.get_float());
      }
    } break;

    case Type2::SUB: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() - right_value.get_int());
      } else {
        value.set_float(left_value.get_float() - right_value.get_float());
      }
    } break;

    case Type2::MUL: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() * right_value.get_int());
      } else {
        value.set_float(left_value.get_float() * right_value.get_float());
      }
    } break;

    case Type2::DIV: {
      if (target_type == AttrType::INTS) {
        if (right_value.get_int() == 0) {
          // NOTE: 设置为整数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为整数最大值。
          value.set_null_value();
        } else {
          value.set_int(left_value.get_int() / right_value.get_int());
        }
      } else {
        if (right_value.get_float() > -EPSILON && right_value.get_float() < EPSILON) {
          // NOTE: 设置为浮点数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为浮点数最大值。
          value.set_null_value();
        } else {
          value.set_float(left_value.get_float() / right_value.get_float());
        }
      }
    } break;

    case Type2::NEGATIVE: {
      if (target_type == AttrType::INTS) {
        value.set_int(-left_value.get_int());
      } else {
        value.set_float(-left_value.get_float());
      }
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported arithmetic type. %d", alu_type_);
    } break;
  }
  return rc;
}

RC ALUExpr::get_value(Tuple &tuple, Value &value)
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_value(left_value, right_value, value);
}

RC ALUExpr::try_get_value(Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

RC ALUExpr::get_expr_value(Tuple &tuple, Value &value)
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_expr_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->get_expr_value(tuple, right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

#if 0
RC FuncExpression::create_expression(const RelAttrSqlNode *expr, Expression *&res_expr)
{
  RC rc = RC::SUCCESS;
  Expression *param_expr1 = nullptr;
  Expression *param_expr2 = nullptr;
  FuncExpr func = expr->func;
  std::pair<Value,Value> value = func.value;
  //FuncOp *fexp = expr->fun_op;
  switch (expr->fun_op) {
    case FUNC_LENGTH: {
      //生成FieldExpr或者ValueExpr
      if(func.is_func){ //如果是

      }
      else{
        param_expr1 = new ValueExpr(value.first);
      }
      break;
    }
    case FUNC_ROUND: {
      if(func.is_func){ //如果是

      }
      else{
        param_expr1 = new ValueExpr(value.first);
        param_expr2 = new ValueExpr(value.second);
      }
      break;
    }
    case FUNC_DATE_FORMAT: {
         if(func.is_func){ //如果是

      }
      else{
        param_expr1 = new ValueExpr(value.first);
        param_expr2 = new ValueExpr(value.second);
      }
      break;
    }
    default:
      return RC::UNIMPLENMENT;
      break;
  }

  //res_expr = new FuncExpression(expr->fexp->type, expr->fexp->param_size, param_expr1, param_expr2, 0);
  return rc;
}
#endif

///////////////////////////////////////////////

FuncExpr::FuncExpr(FuncOp type, Expression *child, Expression *constrain, std::string alias)
    : func_type_(type), child_(child), constrain_(constrain), alias_name_(alias)
{}

FuncExpr::FuncExpr(FuncOp type, Expression *child, Expression *constrain)
    : func_type_(type), child_(child), constrain_(constrain)
{}

AttrType FuncExpr::value_type() const
{
  return AttrType::FLOATS;
}

RC FuncExpr::calc_value(const Value &child_value, const Value &constrain_value, Value &value) const
{
  RC rc = RC::SUCCESS;
  switch(func_type_){
    case LENGTHS:{
      if(child_value.attr_type() != CHARS)
      {
        return RC::INVALID_ARGUMENT;
      }
      int length = strlen(child_value.get_string().c_str());
      value.set_int(length);
      break;
    }
    case ROUNDS:{
      rc = calc_round(child_value, constrain_value, value);
      if(rc != RC::SUCCESS){
        return rc;
      }
      break;
    }
    case DATE_FORMATS:{
      rc = calc_date(child_value, constrain_value, value);
      if(rc != RC::SUCCESS){
        return rc;
      }
      break;
    }
    default:
      return RC::INVALID_ARGUMENT;
  }

  return rc;
}

double round2decimal(double num, int decimal) {
    double multi = pow(10, decimal);
    return round(num * multi+0.09) / multi;
}

RC FuncExpr::calc_round(const Value &child_value, const Value &constrain_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  if (child_value.attr_type() != FLOATS) {
    return RC::INVALID_ARGUMENT;
  }

  if(constrain_ == nullptr){
    float cell = child_value.get_float();
    double temp = round2decimal((double)cell, 0);
    value.set_int(static_cast<int>(temp));
  }
  else{
    if(constrain_value.attr_type() != INTS){
      return RC::INVALID_ARGUMENT;
    }
    float cell = child_value.get_float();
    //double temp;
    double temp = round2decimal((double)cell, constrain_value.get_int());
    //std::stringstream ss;
    //ss << std::fixed << std::setprecision(constrain_value.get_int()) << cell;

    // 从字符串流中提取格式化后的浮点数
    //ss >> temp;
    value.set_float(static_cast<float>(temp));
  }

  return rc;
}

RC FuncExpr::calc_date(const Value &child_value, const Value &constrain_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  if (child_value.attr_type() != DATES) {
    return RC::INVALID_ARGUMENT;
  }
  if (constrain_value.attr_type() != CHARS) {
    return RC::INVALID_ARGUMENT;
  }

  std::string sdate = child_value.get_string();
  int idate = 0;
  if(sdate.empty()){
    idate = child_value.ret_int();
  }
  else{
    idate = date2int(sdate.c_str());
  }

  //int idate = date2int(sdate.c_str());
  std::string format = constrain_value.get_string();
  

  std::string result;
  int year = idate / 10000;
  int month = (idate / 100) % 100;
  int day = idate % 100;
  for (size_t i = 0; i < format.length(); i++) {
    // A ~ z
    if (65 <= format[i] && format[i] <= 122) {
      switch (format[i]) {
        case 'Y': {
          char tmp[5];
          sprintf(tmp, "%d", year);
          result += tmp;
          break;
        }
        case 'y': {
          char tmp[5];
          sprintf(tmp, "%d", year % 100);
          if (0 <= (year % 100) && (year % 100) <= 9) {
            result += "0";
          }
          result += tmp;
          break;
        }
        case 'M': {
          switch (month) {
            case 1: {
              result += "January";
              break;
            }
            case 2: {
              result += "February";
              break;
            }
            case 3: {
              result += "March";
              break;
            }
            case 4: {
              result += "April";
              break;
            }
            case 5: {
              result += "May";
              break;
            }
            case 6: {
              result += "June";
              break;
            }
            case 7: {
              result += "July";
              break;
            }
            case 8: {
              result += "August";
              break;
            }
            case 9: {
              result += "September";
              break;
            }
            case 10: {
              result += "October";
              break;
            }
            case 11: {
              result += "November";
              break;
            }
            case 12: {
              result += "December";
              break;
            }
            default: {
              return RC::INTERNAL;
              break;
            }
          }
          break;
        }
        case 'm': {
          char tmp[3];
          sprintf(tmp, "%d", month);
          if (0 <= month && month <= 9) {
            result += "0";
          }
          result += tmp;
          break;
        }
        case 'D': {
          char tmp[3];
          sprintf(tmp, "%d", day);
          if (10 <= day && day <= 20) {
            result += tmp;
            result += "th";
          } else {
            switch (day % 10) {
              case 1: {
                result += tmp;
                result += "st";
                break;
              }
              case 2: {
                result += tmp;
                result += "nd";
                break;
              }
              case 3: {
                result += tmp;
                result += "rd";
                break;
              }
              default: {
                result += tmp;
                result += "th";
                break;
              }
            }
          }
          break;
        }
        case 'd': {
          char tmp[3];
          sprintf(tmp, "%d", day);
          if (0 <= day && day <= 9) {
            result += "0";
          }
          result += tmp;
          break;
        }
        default: {
          result += format[i];
          break;
        }
      }
    } else if (format[i] != '%') {
      result += format[i];
    }
  }
  // std::cout << result_date_str << std::endl;
  value.set_string(result.c_str());
  value.set_type(DATES);

  return rc;
}

RC FuncExpr::get_value(Tuple &tuple, Value &value)
{
  return RC::SUCCESS;
}

RC FuncExpr::try_get_value(Value &value) const
{
  return RC::SUCCESS;
}

RC FuncExpr::get_expr_value(Tuple &tuple, Value &value)
{
  RC rc = RC::SUCCESS;

  Value child_value;
  Value constrain_value;

  rc = child_->get_expr_value(tuple, child_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if(constrain_ != nullptr){
    rc = constrain_->get_expr_value(tuple, constrain_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(child_value, constrain_value, value);
}