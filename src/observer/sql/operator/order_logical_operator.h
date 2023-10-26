#pragma once

#include <vector>
#include "sql/parser/parse.h"
#include "sql/operator/logical_operator.h"
#include "rc.h"

class OrderByStmt;

class OrderLogicalOperator : public LogicalOperator {
public:
  OrderLogicalOperator(OrderByStmt *orderby_stmt);

  virtual ~OrderLogicalOperator()= default;

   LogicalOperatorType type() const override
  {
    return LogicalOperatorType::ORDER;
  }

  OrderByStmt* orderby_stmt()
  {
    return orderby_stmt_;
  }



private:
  OrderByStmt *orderby_stmt_ = nullptr;
};
