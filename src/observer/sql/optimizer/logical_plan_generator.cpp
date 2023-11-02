/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/optimize_stage.h"
#include "event/sql_debug.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/aggre_logical_operator.h"
#include "sql/operator/order_logical_operator.h"

#include "sql/stmt/stmt.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/order_by_stmt.h"

using namespace std;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);
      rc = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);
      rc = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);
      rc = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::UPDATE: {
      UpdateStmt *Update_stmt = static_cast<UpdateStmt *>(stmt);
      rc = create_plan(Update_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);
      rc = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);
      rc = create_plan(explain_stmt, logical_operator);
    } break;
    default: {
      rc = RC::UNIMPLENMENT;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_sub_query(SelectStmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
#if 0
  //复杂子查询
  std::vector<FilterUnit*> all_filters = stmt->filter_stmt()->filter_units();
  for(size_t i = 0; i < all_filters.size(); i++){
    FilterObj left = all_filters[i]->left();
    FilterObj right = all_filters[i]->right();
    if(left.type == 1){
      Field left_field = left.field;
      const char *left_table_name = left_field.table_name();
      if(0 != strcmp(stmt->tables()[0]->name(), left_table_name)){
        stmt->tables_without_const().push_back(const_cast<Table*>(left_field.table()));
      }
    }
    if(right.type == 1){
      Field right_field = right.field;
      const char *right_table_name = right_field.table_name();
      if(0 != strcmp(stmt->tables()[0]->name(), right_table_name)){
        stmt->tables_without_const().push_back(const_cast<Table*>(right_field.table()));
      }
    }
  }
#endif
  rc = create_plan(stmt, logical_operator);
  return rc;
}

RC LogicalPlanGenerator::create_complex_sub_query(std::vector<Tuple*> &paretnts, SelectStmt *stmt, 
    std::unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  rc = create_complex_sub_plan(paretnts, stmt, logical_operator);
  return rc;
}

RC LogicalPlanGenerator::create_complex_sub_plan(std::vector<Tuple*> &paretnts, SelectStmt *select_stmt, 
    std::unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> table_oper(nullptr);

  const std::vector<Table *> &tables = select_stmt->tables();
  const std::vector<Field> &all_fields = select_stmt->query_fields();
  const std::vector<AggrOp> &aggr_fields = select_stmt->aggr_fields();//解析后的字段
  const std::vector<string> &aggr_specs = select_stmt->aggr_specs();//用户输入

  for (Table *table : tables) {
    std::vector<Field> fields;
    for (const Field &field : all_fields) {
      if (0 == strcmp(field.table_name(), table->name())) {
        fields.push_back(field);
      }
    }

    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, true/*readonly*/));
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
  }

  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_complex_filter_plan(select_stmt->filter_stmt(), predicate_oper, select_stmt->conjunction_flag(), paretnts);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  unique_ptr<LogicalOperator> aggr_oper;
  if (aggr_fields[0] != UNKNOWN) {
    aggr_oper = unique_ptr<AggreLogicalOperator>(new AggreLogicalOperator(all_fields, aggr_fields, aggr_specs));
  }

  unique_ptr<LogicalOperator> project_oper(new ProjectLogicalOperator(all_fields, aggr_fields, aggr_specs, std::move(select_stmt->expressions())));

  if (aggr_oper) {
    if (predicate_oper) {
      if (table_oper) {
        predicate_oper->add_child(std::move(table_oper));
      }
      aggr_oper->add_child(std::move(predicate_oper));
    } else {
      if (table_oper) {
        aggr_oper->add_child(std::move(table_oper));
      }
    }
    project_oper->add_child(std::move(aggr_oper));
  }
  else{
    if (predicate_oper) {
      if (table_oper) {
        predicate_oper->add_child(std::move(table_oper));
      }
      project_oper->add_child(std::move(predicate_oper));
    } else {
      if (table_oper) {
        project_oper->add_child(std::move(table_oper));
      }
    }
  }

  logical_operator.swap(project_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> table_oper(nullptr);

  const std::vector<Table *> &tables = select_stmt->tables();
  const std::vector<Field> &all_fields = select_stmt->query_fields();
  const std::vector<AggrOp> &aggr_fields = select_stmt->aggr_fields();//解析后的字段
  const std::vector<string> &aggr_specs = select_stmt->aggr_specs();//用户输入

  for (Table *table : tables) {
    std::vector<Field> fields;
    for (const Field &field : all_fields) {
      if (0 == strcmp(field.table_name(), table->name())) {
        fields.push_back(field);
      }
    }

    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, true/*readonly*/));
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
  }

  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(select_stmt->filter_stmt(), predicate_oper, select_stmt->conjunction_flag());
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  unique_ptr<LogicalOperator> aggr_oper;
  if (aggr_fields[0] != UNKNOWN) {
    aggr_oper = unique_ptr<AggreLogicalOperator>(new AggreLogicalOperator(all_fields, aggr_fields, aggr_specs));
  }

  unique_ptr<LogicalOperator> project_oper(new ProjectLogicalOperator(all_fields, aggr_fields, aggr_specs, std::move(select_stmt->expressions())));

  unique_ptr<LogicalOperator> order_oper;
  if(select_stmt->order_by_stmt()!=nullptr)
  {
    //初始化order算子
    order_oper = unique_ptr<OrderLogicalOperator>(new OrderLogicalOperator(select_stmt->order_by_stmt()));
    // order_oper->add_child(std::move(project_oper));
    // logical_operator.swap(order_oper);
  }
 
  if (aggr_oper) {
    if (predicate_oper) {
      if (table_oper) {
        predicate_oper->add_child(std::move(table_oper));
      }
      aggr_oper->add_child(std::move(predicate_oper));
    } else {
      if (table_oper) {
        aggr_oper->add_child(std::move(table_oper));
      }
    }
    project_oper->add_child(std::move(aggr_oper));
    if(order_oper){
      order_oper->add_child(std::move(project_oper));
    }
  }
  else{
    if (predicate_oper) {
      if (table_oper) {
        predicate_oper->add_child(std::move(table_oper));
      }
      project_oper->add_child(std::move(predicate_oper));
      if(order_oper){
        order_oper->add_child(std::move(project_oper));
      }
    } else {
      if (table_oper) {
        project_oper->add_child(std::move(table_oper));
        if(order_oper){
          order_oper->add_child(std::move(project_oper));
        }
      }
    }
  }

  if(order_oper){
    logical_operator.swap(order_oper);
  }
  else{
    logical_operator.swap(project_oper);
  }
  // unique_ptr<LogicalOperator> order_oper(new OrderLogicalOperator(select_stmt->order_by_stmt()));
  // order_oper->add_child(std::move(project_oper));
  
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_complex_filter_plan(FilterStmt *filter_stmt, std::unique_ptr<LogicalOperator> &logical_operator, 
    int conjunction_flag, std::vector<Tuple*> &paretnts)
{
  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *> &filter_units = filter_stmt->filter_units();
  for (const FilterUnit *filter_unit : filter_units) {
    const FilterObj &filter_obj_left = filter_unit->left();
    const FilterObj &filter_obj_right = filter_unit->right();

    //生成带有外表信息的FieldExpr
    Expression *left_expr;
    if(filter_obj_left.type == 0){
      if(filter_obj_left.expr->type() == ExprType::VALUE){
        left_expr = static_cast<Expression *>(filter_obj_left.expr);
      }
      else if(filter_obj_left.expr->type() == ExprType::FIELD){
        FieldExpr* fieldnode = static_cast<FieldExpr*>(filter_obj_left.expr);
        left_expr = static_cast<Expression *>(new ComplexFieldExpr(fieldnode->str_table_name(), 
            fieldnode->str_attribute_name(), fieldnode->aggr_name(), fieldnode->field(), paretnts));
      }
    }
    Expression *right_expr;
    if(filter_obj_right.type == 0){
      if(filter_obj_right.expr->type() == ExprType::VALUE){
        right_expr = static_cast<Expression *>(filter_obj_right.expr);
      }
      else if(filter_obj_right.expr->type() == ExprType::FIELD){
        FieldExpr* fieldnode = static_cast<FieldExpr*>(filter_obj_right.expr);
        right_expr = static_cast<Expression *>(new ComplexFieldExpr(fieldnode->str_table_name(), 
            fieldnode->str_attribute_name(), fieldnode->aggr_name(), fieldnode->field(), paretnts));
      }
    }

    unique_ptr<Expression> left(filter_obj_left.type == 0
                                         ? left_expr :
                                (filter_obj_left.type == 1
                                         ? static_cast<Expression *>(new SubQueryExpr(filter_obj_left.stmt, paretnts)) 
                                         : static_cast<Expression *>(new FieldExpr())));

    unique_ptr<Expression> right(filter_obj_right.type == 0
                                          ? right_expr :
                                (filter_obj_right.type == 1
                                         ? static_cast<Expression *>(new SubQueryExpr(filter_obj_right.stmt, paretnts)) :
                                (filter_obj_right.type == 2
                                         ? static_cast<Expression *>(new ValueListExpr(filter_obj_right.value_list)) 
                                         : static_cast<Expression *>(new FieldExpr()))));

    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    if(conjunction_flag == 1){
      unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::OR, cmp_exprs));
      predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
    }
    else{
      unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
      predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
    }
  }

  logical_operator = std::move(predicate_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator, int conjunction_flag)
{
  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *> &filter_units = filter_stmt->filter_units();
  for (const FilterUnit *filter_unit : filter_units) {
    const FilterObj &filter_obj_left = filter_unit->left();
    const FilterObj &filter_obj_right = filter_unit->right();
#if 0
    //递归地生成子查询的火山
    unique_ptr<PhysicalOperator> left_volcano;
    unique_ptr<PhysicalOperator> right_volcano;
    if(filter_obj_left.type == 1){
      OptimizeStage caller;   //无实际用途，就为了调用一下create_sub_request() :)
      RC rc = caller.create_sub_request(filter_obj_left.stmt, left_volcano);
      if(rc != RC::SUCCESS){
        LOG_WARN("failed to get SUB TABLE from operator");
        return rc;
      }
    }
    if(filter_obj_right.type == 1){
      OptimizeStage caller;   //无实际用途，就为了调用一下create_sub_request() :)
      RC rc = caller.create_sub_request(filter_obj_right.stmt, right_volcano);
      if(rc != RC::SUCCESS){
        LOG_WARN("failed to get SUB TABLE from operator");
        return rc;
      }
    }
    //这里拿到火山后马上执行，把子表读到SubQueryExpr中，因为expression表达式如果再包含PhysicalOperator.h
    //的话会形成自包含，编译不通过
    std::vector<std::vector<Value>> left_table;
    if(left_volcano){
      RC rc = RC::SUCCESS;
      //把子表读进sub_table中
      left_volcano->open(nullptr);
      while (RC::SUCCESS == (rc = left_volcano->next())) {
        Tuple * tuple = left_volcano->current_tuple();
        std::vector<Value> row;
        for(int i = 0; i < tuple->cell_num(); i++){
          Value value;
          rc = tuple->cell_at(i, value);
          if (rc != RC::SUCCESS) {
            left_volcano->close();
            LOG_WARN("failed to get SUB TABLE from operator");
            return rc;
          }
          row.push_back(value);
        }
        left_table.push_back(row);
      }
      left_volcano->close();
      if (rc == RC::RECORD_EOF) {
        rc = RC::SUCCESS;
      }
      else{
        LOG_WARN("failed to get SUB TABLE from operator");
        return rc;
      }
    }
    std::vector<std::vector<Value>> right_table;
    if(right_volcano){
      RC rc = RC::SUCCESS;
      //把子表读进sub_table中
      right_volcano->open(nullptr);
      while (RC::SUCCESS == (rc = right_volcano->next())) {
        Tuple * tuple = right_volcano->current_tuple();
        std::vector<Value> row;
        for(int i = 0; i < tuple->cell_num(); i++){
          Value value;
          rc = tuple->cell_at(i, value);
          if (rc != RC::SUCCESS) {
            right_volcano->close();
            LOG_WARN("failed to get SUB TABLE from operator");
            return rc;
          }
          row.push_back(value);
        }
        right_table.push_back(row);
      }
      right_volcano->close();
      if (rc == RC::RECORD_EOF) {
        rc = RC::SUCCESS;
      }
      else{
        LOG_WARN("failed to get SUB TABLE from operator");
        return rc;
      }
    }
#endif
    unique_ptr<Expression> left(filter_obj_left.type == 0
                                         ? std::move(filter_obj_left.expr) :
                                (filter_obj_left.type == 1
                                         ? static_cast<Expression *>(new SubQueryExpr(filter_obj_left.stmt)) 
                                         : static_cast<Expression *>(new FieldExpr())));

    unique_ptr<Expression> right(filter_obj_right.type == 0
                                          ? std::move(filter_obj_right.expr) :
                                (filter_obj_right.type == 1
                                         ? static_cast<Expression *>(new SubQueryExpr(filter_obj_right.stmt)) :
                                (filter_obj_right.type == 2
                                         ? static_cast<Expression *>(new ValueListExpr(filter_obj_right.value_list)) 
                                         : static_cast<Expression *>(new FieldExpr()))));

    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    if(conjunction_flag == 1){
      unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::OR, cmp_exprs));
      predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
    }
    else{
      unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
      predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
    }
  }

  logical_operator = std::move(predicate_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table *table = insert_stmt->table();
  vector<ValueRecord> valuerecords(insert_stmt->valuerecords(), insert_stmt->valuerecords() + insert_stmt->valuerecord_amount());

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, valuerecords);
  logical_operator.reset(insert_operator);//重新设置只能指针的指向
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt *update_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  Table *table = update_stmt->table();
  std::vector<update_list> update_values = update_stmt->valueList();
  std::vector<std::string> value_name = update_stmt->names();
  FilterStmt *filter_stmt = update_stmt->filter_stmt();

  //用于update更新的所有Value，包括子查询解析出来的Value
  std::vector<Value> all_values;

  for(size_t i = 0; i < update_values.size(); i++){
    //case1. 子查询, 生成并运行子火山
    if(update_values[i].type == 1){
      unique_ptr<PhysicalOperator> sub_volcano;
      OptimizeStage caller;   //无实际用途，就为了调用一下create_sub_request() :)
      RC rc = caller.create_sub_request(update_values[i].sub_query, sub_volcano);
      if(rc != RC::SUCCESS){
        LOG_WARN("failed to get SUB TABLE from operator");
        return rc;
      }
      //这里拿到火山后马上执行，把子表读到SubQueryExpr中，因为expression表达式如果再包含PhysicalOperator.h
      //的话会形成自包含，编译不通过
      std::vector<std::vector<Value>> sub_table;
      if(sub_volcano){
        RC rc = RC::SUCCESS;
        //把子表读进sub_table中
        sub_volcano->open(nullptr);
        while (RC::SUCCESS == (rc = sub_volcano->next())) {
          Tuple * tuple = sub_volcano->current_tuple();
          std::vector<Value> row;
          for(int i = 0; i < tuple->cell_num(); i++){
            Value value;
            rc = tuple->cell_at(i, value);
            if (rc != RC::SUCCESS) {
              sub_volcano->close();
              LOG_WARN("failed to get SUB TABLE from operator");
              return rc;
            }
            row.push_back(value);
          }
          sub_table.push_back(row);
        }
        sub_volcano->close();
        if (rc == RC::RECORD_EOF) {
          rc = RC::SUCCESS;
        }
        else{
          LOG_WARN("failed to get SUB TABLE from operator");
          return rc;
        }
      }
      if((int)sub_table.size() == 0){
        Value invalid_value(-1);
        invalid_value.set_type(NULLS);
        all_values.push_back(invalid_value);
      }
      else if((int)sub_table.size() > 1 || (int)sub_table[0].size() > 1){
        Value invalid_value(-1);
        invalid_value.set_type(UPDATE_FAIL);
        all_values.push_back(invalid_value);
      }
      else{
        all_values.push_back(sub_table[0][0]);
      }
    }
    //case2. 一般的value
    else{
      all_values.push_back(update_values[i].value);
    }
  }

  std::vector<Field> fields;
  //这里有待商榷 毕竟null_field也是要存进去的 不需要 因为可以直接修改bit
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num() - table->table_meta().extra_filed_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false/*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(filter_stmt, predicate_oper, 0);  //先默认是AND
  if (rc != RC::SUCCESS) {
    return rc;
  }

  //新增一个update逻辑算子
  unique_ptr<LogicalOperator> update_oper(new UpdateLogicalOperator(table, all_values, value_name));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(update_oper);

  //输出调试信息 查看增加了哪些索引
  //sql_debug(value_name.data()->c_str());
  return rc;
}

RC LogicalPlanGenerator::create_plan(
    DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table *table = delete_stmt->table();
  FilterStmt *filter_stmt = delete_stmt->filter_stmt();
  std::vector<Field> fields;
  //删除的话 当然这一行都要删
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false/*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(filter_stmt, predicate_oper, 0); //先默认是AND
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(
    ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Stmt *child_stmt = explain_stmt->child();
  unique_ptr<LogicalOperator> child_oper;
  RC rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}
