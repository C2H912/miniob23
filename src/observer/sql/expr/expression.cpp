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
#include <regex>

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

SubQueryExpr::~SubQueryExpr()
{}

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
    std::vector<std::vector<Value>> sub_table = right_->sub_table();
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
    std::vector<std::vector<Value>> sub_table = right_->sub_table();
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
    std::vector<std::vector<Value>> left_sub_table = left_->sub_table();
    if((int)left_sub_table.size() == 0){
      value.set_boolean(false);
      return RC::SUCCESS;
    }
    if((int)left_sub_table.size() > 1 || (int)left_sub_table[0].size() > 1){
      LOG_WARN("table size is incorrect");
      return RC::INVALID_ARGUMENT;
    }
    left_value = left_sub_table[0][0];
  }
  else{
    rc = left_->get_expr_value(tuple, left_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  int right_type = right_->expr_type();
  if(right_->type() == ExprType::QUERY){
    std::vector<std::vector<Value>> right_sub_table = right_->sub_table();
    if((int)right_sub_table.size() == 0){
      value.set_boolean(false);
      return RC::SUCCESS;
    }
    if((int)right_sub_table.size() > 1 || (int)right_sub_table[0].size() > 1){
      LOG_WARN("table size is incorrect");
      return RC::INVALID_ARGUMENT;
    }
    right_value = right_sub_table[0][0];
  }
  else{
    rc = right_->get_expr_value(tuple, right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
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