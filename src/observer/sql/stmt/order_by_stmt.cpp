#include "rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/order_by_stmt.h"
#include "sql/stmt/filter_stmt.h"

OrderByStmt::~OrderByStmt()
{
  for (OrderByUnit *unit : orderby_units_) {
    delete unit;
  }
  orderby_units_.clear();
}
//生成orderbystmt
RC OrderByStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
     std::vector<OrderBySqlNode> &orderbys, int orderby_num, OrderByStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  OrderByStmt *tmp_stmt = new OrderByStmt();
  for (int i = 0; i < orderby_num; i++) {
    OrderByUnit *orderby_unit = nullptr;
    rc = create_orderby_unit(db, default_table, tables, orderbys[i], orderby_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->orderby_units_.push_back(orderby_unit);
  }

  stmt = tmp_stmt;
  return rc;
}


RC OrderByStmt::create_orderby_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const OrderBySqlNode &orderby, OrderByUnit *&orderby_unit)
{
  RC rc = RC::SUCCESS;

  bool sort_type = orderby.asc_type;

  Expression *expr = nullptr;
  Table *table = nullptr;
  const FieldMeta *field = nullptr;
  RelAttrSqlNode *relAttr = new RelAttrSqlNode();
  relAttr->attribute_name = orderby.field;
  relAttr->relation_name = orderby.order_relation; 
  rc = get_table_and_field(db, default_table, tables, *relAttr, table, field);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot find attr");
    return rc;
  }
  expr = new FieldExpr(table, field);
  orderby_unit = new OrderByUnit;
  orderby_unit->set_sort_type(sort_type);
  orderby_unit->set_expr(expr);
  return rc;
}
