
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/db/db.h"

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

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC OrderByStmt::create_orderby_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
     OrderBySqlNode &orderby, OrderByUnit *&orderby_unit)
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
