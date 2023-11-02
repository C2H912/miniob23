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

#pragma once

#include <string.h>
#include <memory>
#include <string>

#include "storage/field/field.h"
#include "sql/parser/value.h"
#include "common/log/log.h"

class Tuple;

/**
 * @defgroup Expression
 * @brief 表达式
 */

/**
 * @brief 表达式类型
 * @ingroup Expression
 */
enum class ExprType 
{
  NONE,
  STAR,         ///< 星号，表示所有字段
  FIELD,        ///< 字段。在实际执行时，根据行数据内容提取对应字段的值
  VALUE,        ///< 常量值
  VALUELIST,    ///< 常量列
  QUERY,        ///< 子查询
  CAST,         ///< 需要做类型转换的表达式
  COMPARISON,   ///< 需要做比较的表达式
  CONJUNCTION,  ///< 多个表达式使用同一种关系(AND或OR)来联结
  ALU,
  AGGRE,
  ARITHMETIC,   ///< 算术运算
  FUNC,
};

/**
 * @brief 表达式的抽象描述
 * @ingroup Expression
 * @details 在SQL的元素中，任何需要得出值的元素都可以使用表达式来描述
 * 比如获取某个字段的值、比较运算、类型转换
 * 当然还有一些当前没有实现的表达式，比如算术运算。
 *
 * 通常表达式的值，是在真实的算子运算过程中，拿到具体的tuple后
 * 才能计算出来真实的值。但是有些表达式可能就表示某一个固定的
 * 值，比如ValueExpr。
 */
class Expression 
{
public:
  Expression() = default;
  virtual ~Expression() = default;

  /**
   * @brief 根据具体的tuple，来计算当前表达式的值。tuple有可能是一个具体某个表的行数据
   */
  virtual RC get_value(Tuple &tuple, Value &value) = 0;

  /**
   * @brief 在没有实际运行的情况下，也就是无法获取tuple的情况下，尝试获取表达式的值
   * @details 有些表达式的值是固定的，比如ValueExpr，这种情况下可以直接获取值
   */
  virtual RC try_get_value(Value &value) const
  {
    return RC::UNIMPLENMENT;
  }
  virtual RC get_expr_value(Tuple &tuple, Value &value)
  {
    return RC::UNIMPLENMENT;
  }

  /**
   * @brief 表达式的类型
   * 可以根据表达式类型来转换为具体的子类
   */
  virtual ExprType type() const = 0;

  /**
   * @brief 表达式值的类型
   * @details 一个表达式运算出结果后，只有一个值
   */
  virtual AttrType value_type() const = 0;

  /**
   * @brief 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容
   */
  virtual std::string name() const { return name_; }
  virtual void set_name(std::string name) { name_ = name; }

  /**
   * 返回子表
   */
  virtual std::vector<std::vector<Value>> sub_table() const = 0;

  /**
   * 返回操作符类型
   */
  virtual int expr_type() const = 0;

private:
  std::string  name_;
};

/**
 * @brief 字段表达式
 * @ingroup Expression
 */
class FieldExpr : public Expression 
{
public:
  FieldExpr() = default;
  FieldExpr(std::string table_name, std::string attribute_name, AggrOp aggr_func) 
      : table_name_(table_name), attribute_name_(attribute_name), aggr_func_(aggr_func)
  {}
   FieldExpr(std::string table_name, std::string attribute_name, AggrOp aggr_func, std::string alias_name) 
      : table_name_(table_name), attribute_name_(attribute_name), aggr_func_(aggr_func),alias_name_(alias_name)
  {}
  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field)
  {}
  FieldExpr(const Field &field) : field_(field)
  {}

  virtual ~FieldExpr() = default;

  ExprType type() const override { return ExprType::FIELD; }
  AttrType value_type() const override { return field_.attr_type(); }

  Field &field() { return field_; }

  const Field &field() const { return field_; }

  const char *table_name() const { return field_.table_name(); }

  const char *field_name() const { return field_.field_name(); }

  RC get_value(Tuple &tuple, Value &value) override;
  RC try_get_value(Value &value) const override { return RC::SUCCESS; }
  RC get_expr_value(Tuple &tuple, Value &value) override;

  const std::string str_table_name() const { return table_name_; }
  const std::string str_attribute_name() const { return attribute_name_; }
  const std::string str_alias_name() const { return alias_name_; }
  AggrOp aggr_name() { return aggr_func_; }
  void set_table_name(std::string s){
    table_name_ = s;
  }
  void set_field(Field &field){
    field_ = field;
  }

  //这个函数永远不应该被调用
  std::vector<std::vector<Value>> sub_table() const override {
    std::vector<std::vector<Value>> ret;
    return ret;
  }
  int expr_type() const override {
    return 1;
  }

private:
  Field field_;
  std::string table_name_;
  std::string attribute_name_;
  AggrOp aggr_func_;
  std::string alias_name_;
};

/**
 * @brief 常量值表达式
 * @ingroup Expression
 */
class ValueExpr : public Expression 
{
public:
  ValueExpr() = default;
  explicit ValueExpr(const Value &value) : value_(value)
  {}

  virtual ~ValueExpr() = default;

  RC get_value(Tuple &tuple, Value &value) override;
  RC try_get_value(Value &value) const override { value = value_; return RC::SUCCESS; }
  RC get_expr_value(Tuple &tuple, Value &value) override { value = value_; return RC::SUCCESS; }

  ExprType type() const override { return ExprType::VALUE; }

  AttrType value_type() const override { return value_.attr_type(); }

  void get_value(Value &value) const { value = value_; }

  const Value &get_value() const { return value_; }

  //这个函数永远不应该被调用
  std::vector<std::vector<Value>> sub_table() const override {
    std::vector<std::vector<Value>> ret;
    return ret;
  }
  int expr_type() const override {
    return 0;
  }

private:
  Value value_;
};

/**
 * @brief 常量值列表达式
 * @ingroup Expression
 */
class ValueListExpr : public Expression 
{
public:
  ValueListExpr(const std::vector<Value> &value_list);
  virtual ~ValueListExpr();

  RC get_value(Tuple &tuple, Value &value) override;

  RC try_get_value(Value &value) const override { return RC::SUCCESS; }

  ExprType type() const override { return ExprType::VALUELIST; }

  AttrType value_type() const override { return INTS; }

  std::vector<std::vector<Value>> sub_table() const override {
    std::vector<std::vector<Value>> ret;
    for(size_t i = 0; i < value_list_.size(); i++){
      std::vector<Value> temp;
      temp.push_back(value_list_[i]);
      ret.push_back(temp);
    }
    return ret;
  }

  int expr_type() const override {
    return 3;
  }

private:
  std::vector<Value> value_list_;
};

/**
 * @brief 子查询表达式
 * @ingroup Expression
 */
class SubQueryExpr : public Expression 
{
public:
  //explicit SubQueryExpr(const SelectStmt &stmt, std::unique_ptr<PhysicalOperator> oper) 
  //  : sub_query_(stmt), operator_(std::move(oper))
  //{}
  SubQueryExpr(std::vector<std::vector<Value>> &sub_table);
  virtual ~SubQueryExpr();

  RC get_value(Tuple &tuple, Value &value) override;

  ExprType type() const override { return ExprType::QUERY; }

  AttrType value_type() const override { return INTS; }

  //void get_stmt(SelectStmt &stmt) const { stmt = sub_query_; }

  //const SelectStmt &get_stmt() const { return sub_query_; }

  RC try_get_value(Value &value) const override { return RC::SUCCESS; }

  std::vector<std::vector<Value>> sub_table() const override { return sub_table_; }

  int expr_type() const override {
    return -1;
  }

private:
  //SelectStmt sub_query_;
  std::vector<std::vector<Value>> sub_table_;
};

/**
 * @brief 类型转换表达式
 * @ingroup Expression
 */
class CastExpr : public Expression 
{
public:
  CastExpr(std::unique_ptr<Expression> child, AttrType cast_type);
  virtual ~CastExpr();

  ExprType type() const override
  {
    return ExprType::CAST;
  }
  RC get_value(Tuple &tuple, Value &value) override;

  RC try_get_value(Value &value) const override;

  AttrType value_type() const override { return cast_type_; }

  std::unique_ptr<Expression> &child() { return child_; }

  //这个函数永远不应该被调用
  std::vector<std::vector<Value>> sub_table() const override {
    std::vector<std::vector<Value>> ret;
    return ret;
  }

  int expr_type() const override {
    return 4;
  }

private:
  RC cast(const Value &value, Value &cast_value) const;

private:
  std::unique_ptr<Expression> child_;  ///< 从这个表达式转换
  AttrType cast_type_;  ///< 想要转换成这个类型
};

/**
 * @brief 比较表达式
 * @ingroup Expression
 */
class ComparisonExpr : public Expression 
{
public:
  ComparisonExpr(CompOp comp, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ComparisonExpr();

  ExprType type() const override { return ExprType::COMPARISON; }

  RC get_value(Tuple &tuple, Value &value) override;

  AttrType value_type() const override { return BOOLEANS; }

  //这个函数永远不应该被调用
  std::vector<std::vector<Value>> sub_table() const override {
    std::vector<std::vector<Value>> ret;
    return ret;
  }

  CompOp comp() const { return comp_; }

  std::unique_ptr<Expression> &left()  { return left_;  }
  std::unique_ptr<Expression> &right() { return right_; }

  /**
   * 尝试在没有tuple的情况下获取当前表达式的值
   * 在优化的时候，可能会使用到
   */
  RC try_get_value(Value &value) const override;

  /**
   * compare the two tuple cells
   * @param value the result of comparison
   */
  RC compare_value(const Value &left, const Value &right, bool &value) const;

  int expr_type() const override {
    return 5;
  }

private:
  CompOp comp_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

/**
 * @brief 联结表达式
 * @ingroup Expression
 * 多个表达式使用同一种关系(AND或OR)来联结
 * 当前miniob仅有AND操作
 */
class ConjunctionExpr : public Expression 
{
public:
  enum class Type {
    AND,
    OR,
  };

public:
  ConjunctionExpr(Type type, std::vector<std::unique_ptr<Expression>> &children);
  virtual ~ConjunctionExpr() = default;

  ExprType type() const override { return ExprType::CONJUNCTION; }

  AttrType value_type() const override { return BOOLEANS; }

  RC get_value(Tuple &tuple, Value &value) override;

  //这个函数永远不应该被调用
  std::vector<std::vector<Value>> sub_table() const override {
    std::vector<std::vector<Value>> ret;
    return ret;
  }

  Type conjunction_type() const { return conjunction_type_; }

  std::vector<std::unique_ptr<Expression>> &children() { return children_; }

  int expr_type() const override {
    return 6;
  }

private:
  Type conjunction_type_;
  std::vector<std::unique_ptr<Expression>> children_;
};

/**
 * @brief 算术表达式
 * @ingroup Expression
 */
class ArithmeticExpr : public Expression 
{
public:
  enum class Type {
    ADD,
    SUB,
    MUL,
    DIV,
    NEGATIVE,
  };

public:
  ArithmeticExpr(Type type, Expression *left, Expression *right);
  ArithmeticExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ArithmeticExpr() = default;

  ExprType type() const override { return ExprType::ARITHMETIC; }

  AttrType value_type() const override;

  RC get_value(Tuple &tuple, Value &value) override;
  RC try_get_value(Value &value) const override;

  //这个函数永远不应该被调用
  std::vector<std::vector<Value>> sub_table() const override {
    std::vector<std::vector<Value>> ret;
    return ret;
  }

  int expr_type() const override {
    return 7;
  }

  Type arithmetic_type() const { return arithmetic_type_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

private:
  RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;
  
private:
  Type arithmetic_type_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

/**
 * @brief 我自己的算术表达式，不想破坏原有的结构
 * @ingroup Expression
 */
class ALUExpr : public Expression 
{
public:
  enum class Type2 {
    ADD,
    SUB,
    MUL,
    DIV,
    NEGATIVE,
  };

public:
  ALUExpr(Type2 type, Expression *left, Expression *right);
  virtual ~ALUExpr() = default;

  ExprType type() const override { return ExprType::ALU; }

  AttrType value_type() const override;

  RC get_value(Tuple &tuple, Value &value) override;
  RC try_get_value(Value &value) const override;
  RC get_expr_value(Tuple &tuple, Value &value) override;

  //这个函数永远不应该被调用
  std::vector<std::vector<Value>> sub_table() const override {
    std::vector<std::vector<Value>> ret;
    return ret;
  }

  int expr_type() const override {
    return 8;
  }

  Type2 alu_type() const { return alu_type_; }

  Expression* left() { return left_; }
  Expression* right() { return right_; }

private:
  RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;
  
private:
  Type2 alu_type_;
  Expression* left_;
  Expression* right_;
};

class FuncExpression : public Expression {
public:
  FuncExpression() = default;
  FuncExpression(FuncOp func_type, int param_size, Expression *param1, Expression *param2, bool with_brace)
      : func_type_(func_type), param_size_(param_size)
  {
    // if (with_brace) {
    //   set_with_brace();
    // }
    if (param1 != NULL) {
      params_expr_.emplace_back(param1);
    }
    if (param2 != NULL) {
      params_expr_.emplace_back(param2);
    }
  }
  virtual ~FuncExpression() = default;

  RC get_func_length_value(const Tuple &tuple, Value &final_cell) const;

  RC get_func_round_value(const Tuple &tuple, Value &final_cell) const;

  RC get_func_data_format_value(const Tuple &tuple, Value &final_cell) const;

  RC get_value(const Tuple &tuple, Value &final_cell) const 
  {
    RC rc = RC::SUCCESS;
    switch (func_type_) {
      case FUNC_LENGTH: {
        rc = get_func_length_value(tuple, final_cell);
        break;
      }
      case FUNC_ROUND: {
        rc = get_func_round_value(tuple, final_cell);
        break;
      }
      case FUNC_DATE_FORMAT: {
        rc = get_func_data_format_value(tuple, final_cell);
        break;
      }
      default:
        break;
    }
    return rc;
  }

  ExprType type() const override
  {
    return ExprType::FUNC;
  }


  FuncOp get_func_type()
  {
    return func_type_;
  }

  std::vector<Expression *> get_params()
  {
    return params_expr_;
  }

  int get_param_size()
  {
    return param_size_;
  }
  static RC create_expression(const RelAttrSqlNode *expr, Expression *&res_expr);

private:
  FuncOp func_type_;
  std::vector<Expression *> params_expr_;
  int param_size_;
};