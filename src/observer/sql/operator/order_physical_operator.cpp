#include "sql/operator/order_physical_operator.h"
#include "common/log/log.h"
#include "sql/stmt/order_by_stmt.h"
#include <algorithm>
#include "storage/record/record.h"
#include "storage/field/field.h"
#include "sql/expr/tuple_cell.h"
#include "sql/expr/tuple.h"


//还需要解决的有 表头如何打印

RC OrderPhysicalOperator::open(Trx *trx)
{
   if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->open(trx);
}

RC OrderPhysicalOperator::fetch_and_OrderPhysical_table()
{
  RC rc = RC::SUCCESS;

  int index = 0;
  typedef std::pair<std::vector<Value>, int> CmpPair;
  std::vector<CmpPair> cell_index_table;
  std::vector<Value> pair_cell;

  auto &units = orderby_stmt_->orderby_units();
  while (RC::SUCCESS == (rc = children_[0]->next())) {
    // construct pair OrderPhysical table
    // 1 cons vector<Value>
    pair_cell.clear();
    for (const OrderByUnit *unit : units) { //把排序字段拿出来
      Expression *expr = unit->expr();//这个是FieldExpr
      Value cell;
      expr->get_value(*children_[0]->current_tuple(), cell);//获取到对应字段数据
      pair_cell.emplace_back(cell);//这里面是某一个tuple在不同orderby条件下的集合 比如三个字段的话 就有三个
    }
    // 2 cons pair
    // 3 cons pair vector
    cell_index_table.emplace_back(std::make_pair(pair_cell, index++));//index应该就是用来标识不同的tuple
   
    //拷贝一份下层传上来的tuple
    st_.emplace_back(children_[0]->current_tuple());//不需要深拷贝了 因为只用到一次
  }
  if (RC::RECORD_EOF != rc) {
    LOG_ERROR("Fetch Table Error In OrderPhysicalOperator. RC: %d", rc);
    return rc;
  }
  rc = RC::SUCCESS;
  LOG_INFO("Fetch Table Success In OrderPhysicalOperator");
  // print_info();

  // then OrderPhysical table 解析规则
  bool order[units.size()];  // specify 1 asc or 2 desc
  for (std::vector<OrderByUnit *>::size_type i = 0; i < units.size(); ++i) {
    order[i] = units[i]->sort_type();
  }
  // consider null  建立比较规则
  auto cmp = [&order](const CmpPair &a, const CmpPair &b) {
    auto &cells_a = a.first;//用所有排序字段来确定俩个cell的顺序
    auto &cells_b = b.first;
    assert(cells_a.size() == cells_b.size());
    for (size_t i = 0; i < cells_a.size(); ++i) {
      auto &cell_a = cells_a[i];
      auto &cell_b = cells_b[i];
      if (cell_a.is_null() && cell_b.is_null()) {//都是null 看看有无下一个
        continue;
      }
      if (cell_a.is_null()) {
        return order[i] ? true : false;
      }
      if (cell_b.is_null()) {
        return order[i] ? false : true;
      }
      if (cell_a != cell_b) {
        return order[i] ? cell_a < cell_b : cell_a > cell_b;
      }
    }
    return false;  // completely same
  };
  std::sort(cell_index_table.begin(), cell_index_table.end(), cmp);//对所有字段进行排序
  LOG_INFO("OrderPhysical Table Success In OrderPhysicalOperator");

  // fill ordered_idx_
  for (size_t i = 0; i < cell_index_table.size(); ++i) {
    ordered_idx_.emplace_back(cell_index_table[i].second);//记录排序结果 int 本来的顺序是012345 排序后变成32145 读取顺序因此改变
  }
  it_ = ordered_idx_.begin();

  return rc;  // return RC::SUCCESS
}

void OrderPhysicalOperator::print_info()
{
  std::cout << "OrderPhysical table info: " << std::endl;
  for (auto idx : ordered_idx_) {
    std::cout << idx << std::endl;
  }
  std::cout << "current child OrderPhysical table iter: " << std::endl;
  std::cout << it_ - ordered_idx_.begin() << std::endl;
  // std::cout << "current tuple: " << std::endl;
}

RC OrderPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  // at first cache child tuple and OrderPhysical them
  if (is_first_) {
    is_first_ = false;
    rc = fetch_and_OrderPhysical_table();
    if (RC::SUCCESS != rc) {
      return rc;
    }
  }

  if (ordered_idx_.end() != it_) {
    // NOTE: PAY ATTENTION HERE
    tuple_ = st_[*it_];
    it_++;
    return RC::SUCCESS;
  }

  return RC::RECORD_EOF;
}

RC OrderPhysicalOperator::close()
{
  RC rc = RC::SUCCESS;
  children_[0]->close();
  return rc;
}

Tuple *OrderPhysicalOperator::current_tuple()
{
  return tuple_;
}
