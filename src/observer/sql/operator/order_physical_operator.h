#pragma once

#include <vector>
#include "sql/parser/parse.h"
#include "sql/expr/expression.h"
#include "sql/operator/physical_operator.h"
#include "sql/expr/tuple.h"


class OrderByStmt;//这个算子可以实现OrderBy 同时帮助实现groupBy

class OrderPhysicalOperator : public PhysicalOperator {
public:
  OrderPhysicalOperator(OrderByStmt *orderby_stmt) : orderby_stmt_(orderby_stmt)
  {}

  virtual ~OrderPhysicalOperator() = default;

   PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::ORDER;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

  void print_info();

private:
  RC fetch_and_OrderPhysical_table();

private:
  OrderByStmt *orderby_stmt_ = nullptr;
  bool is_first_ = true;//是否打开？
  std::vector<int> ordered_idx_;
  std::vector<int>::iterator it_;
  std::vector<TupleCellSpec*> speces_;
  std::vector<std::vector<Value>> all_tuple;
  ProjectTuple tuple_;
  ValueListTuple valueTuple_;
};
