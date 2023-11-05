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
// Created by Wangyunlai on 2022/6/6.
//
// #define DEFER_WHEN_NOT_NULL(ptr) \
//   DEFER([ptr]() {                \
//     if (nullptr != (ptr)) {      \
//       delete (ptr);              \
//     }                            \
//   });


#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/having_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/stmt/order_by_stmt.h"



SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num()- table_meta.extra_filed_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

void dfs(Expression* current, std::vector<RelAttrSqlNode>& attr)
{
  //终止节点
  if(current->type() == ExprType::VALUE){
    return;
  }
  else if(current->type() == ExprType::FIELD){
    FieldExpr* fieldnode = static_cast<FieldExpr*>(current);
    RelAttrSqlNode node;
    node.relation_name = fieldnode->str_table_name();
    node.attribute_name = fieldnode->str_attribute_name();
    node.aggr_func = fieldnode->aggr_name();
    node.alias = fieldnode->str_alias_name();
    attr.push_back(node);
    return;
  }
  else if(current->type() == ExprType::FUNC){
    FuncExpr* fieldnode = static_cast<FuncExpr*>(current);
    if(fieldnode->child()->type() == ExprType::VALUE){
      ValueExpr* child_node = static_cast<ValueExpr*>(fieldnode->child());
      RelAttrSqlNode node;
      node.aggr_func = UNKNOWN;
      node.flag = true;
       if(fieldnode->alias_name().empty())
      {
        //如果为空

        std::string func_alias;
        switch(fieldnode->func_op())
        {
         case LENGTHS:{
          func_alias = "LENGTH("+child_node->get_value().to_string()+")";
          break;
        }
         case ROUNDS:{
          ValueExpr* value_node = static_cast<ValueExpr*>(fieldnode->constrain());
          if(value_node==nullptr)
          {
          func_alias = "ROUND("+child_node->get_value().to_string()+")";
          
          }
          else{
            func_alias = "ROUND("+child_node->get_value().to_string()+","+value_node->get_value().to_string()+")";
          }
          break;
        }
         case DATE_FORMATS:{
           ValueExpr* value_node = static_cast<ValueExpr*>(fieldnode->constrain());
          //func_alias = "DATE_FORMAT("+child_node->str_attribute_name()+")";
           func_alias = "DATE_FORMAT("+child_node->get_value().get_date()+","+value_node->get_value().to_string()+")";
          break;
        }
        }
      
        node.alias = func_alias;
      }
      else{
        node.alias = fieldnode->alias_name();
      }

      attr.push_back(node);
      return;
    }
    else if(fieldnode->child()->type() == ExprType::FIELD){
      FieldExpr* child_node = static_cast<FieldExpr*>(fieldnode->child());
      RelAttrSqlNode node;
      node.relation_name = child_node->str_table_name();
      node.attribute_name = child_node->str_attribute_name();
      node.aggr_func = UNKNOWN;
      //直接在这里处理alias
      if(fieldnode->alias_name().empty())
      {
        //如果为空
        std::string func_alias;
        switch(fieldnode->func_op())
        {
         case LENGTHS:{
          func_alias = "LENGTH("+child_node->str_attribute_name()+")";
          break;
        }
         case ROUNDS:{
          ValueExpr* value_node = static_cast<ValueExpr*>(fieldnode->constrain());
          if(value_node==nullptr)
          {
          func_alias = "ROUND("+child_node->str_attribute_name()+")";
          
          }
          else{
            func_alias = "ROUND("+child_node->str_attribute_name()+","+value_node->get_value().to_string()+")";
          }
          break;
        }
         case DATE_FORMATS:{
           ValueExpr* value_node = static_cast<ValueExpr*>(fieldnode->constrain());
          //func_alias = "DATE_FORMAT("+child_node->str_attribute_name()+")";
           func_alias = "DATE_FORMAT('"+child_node->str_attribute_name()+"',"+value_node->get_value().to_string()+")";
          break;
        }
        }
      
        node.alias = func_alias;
      }
      else{
        node.alias = fieldnode->alias_name();
      }
     
      attr.push_back(node);
    }
    return;
  }
  //计算节点
  ALUExpr* arithnode = static_cast<ALUExpr*>(current);
  if(arithnode->left() != nullptr){
    dfs(arithnode->left(), attr);
  }
  if(arithnode->right() != nullptr){
    dfs(arithnode->right(), attr);
  }
}

//计算节点时必须根据field拿到这个属性的Attrtype，所以要遍历一遍赋值上field
void dfs_for_field(Expression* current, int &index, std::vector<Field> &fields)
{
  //终止节点
  if(current->type() == ExprType::VALUE){
    return;
  }
  else if(current->type() == ExprType::FIELD){
    FieldExpr* fieldnode = static_cast<FieldExpr*>(current);
    fieldnode->set_field(fields[index]);
    index++;
    return;
  }
  else if(current->type() == ExprType::FUNC){
    FuncExpr* fieldnode = static_cast<FuncExpr*>(current);
    if(fieldnode->child()->type() == ExprType::VALUE){
      return;
    }
    else if(fieldnode->child()->type() == ExprType::FIELD){
      FieldExpr* child_node = static_cast<FieldExpr*>(fieldnode->child());
      child_node->set_field(fields[index]);
      index++;
    }
    return;
  }
  //计算节点
  ALUExpr* arithnode = static_cast<ALUExpr*>(current);
  if(arithnode->left() != nullptr){
    dfs_for_field(arithnode->left(), index, fields);
  }
  if(arithnode->right() != nullptr){
    dfs_for_field(arithnode->right(), index, fields);
  }
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt,std::unordered_map<std::string,Table* > parents)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }
  
  //处理表头
  bool is_expr = false;
  for(size_t i = 0; i < select_sql.expressions.size(); i++){
    if(select_sql.expressions[i]->type() == ExprType::ALU){
      is_expr = true;
      break;
    }
  }

// ---------- 首先通过深度优先搜索把expression树中的内容解析出来,并且为Field节点附上表名 ----------
  std::vector<RelAttrSqlNode> all_relAttrNodes;
  for(size_t i = 0; i < select_sql.expressions.size(); i++){
    dfs(select_sql.expressions[i], all_relAttrNodes);
  }
  //把having里面的也放进去
  for(size_t i = 0; i < select_sql.havingcConditions.size(); i++){
    ConditionSqlNode having_condiction = select_sql.havingcConditions[i];
    if(having_condiction.left_is_attr == 0){
      if(having_condiction.left_expr->type() == ExprType::FIELD){
        FieldExpr* fieldnode = static_cast<FieldExpr*>(having_condiction.left_expr);
        RelAttrSqlNode temp;
        temp.relation_name = fieldnode->str_table_name();
        temp.attribute_name = fieldnode->str_attribute_name();
        temp.aggr_func = fieldnode->aggr_name();
        all_relAttrNodes.push_back(temp);
      }
    }
    if(having_condiction.right_is_attr == 0){
      if(having_condiction.right_expr->type() == ExprType::FIELD){
        FieldExpr* fieldnode = static_cast<FieldExpr*>(having_condiction.right_expr);
        RelAttrSqlNode temp;
        temp.relation_name = fieldnode->str_table_name();
        temp.attribute_name = fieldnode->str_attribute_name();
        temp.aggr_func = fieldnode->aggr_name();
        all_relAttrNodes.push_back(temp);
      }
    }
  }
  //特殊情况: 不经过表的function sql
 
    bool flag_alias = false;
    for (size_t i = 0; i < (int)all_relAttrNodes.size(); i++)
    {
      int count = 0;
      if(all_relAttrNodes[i].flag)
      {
         count++;
      }
      else{
        break;
      }
      if(count == ((int)all_relAttrNodes.size())){
        flag_alias = true;
      }
    
    }


  if(flag_alias)
  {
    bool all_func = true;
    for(size_t i = 0; i < select_sql.expressions.size(); i++){
      if(select_sql.expressions[i]->type() != ExprType::FUNC){
        all_func = false;
        break;
      }
    }
    if(all_func == false){
      return RC::INVALID_ARGUMENT;
    }
    SelectStmt *select_stmt = new SelectStmt();
    select_stmt->enter_volcano_ = false;
    //select_stmt->is_expr_ = true; //.

    for(size_t j = 0; j < select_sql.expressions.size(); j++){
      select_stmt->alias_fields_.emplace_back(Field(all_relAttrNodes[j].alias));
      select_stmt->expressions_.emplace_back(select_sql.expressions[j]);
    }
    stmt = select_stmt;
    return RC::SUCCESS;
  }
   
  
 

// ---------- collect tables in `from` statement ----------
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  std::unordered_map<std::string, Table *> alias_map;
  //位于from里的所有表
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].relation.c_str();
    std::string alias_name = select_sql.relations[i].alias;
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
    if(!select_sql.relations[i].alias.empty()&&alias_name!="")
    {
       std::pair<std::unordered_map<std::string, Table *>::iterator, bool> ret = alias_map.insert(std::pair<std::string, Table *>(alias_name, table));
      if(!ret.second)
      {
        return RC::INVALID_ARGUMENT;//别名重复
      }
    }
  }
  //位于join里的所有表
  for(int i = 0; i < (int)select_sql.joinTables.size(); i++){
    InnerJoinSqlNode temp_node = select_sql.joinTables[i];
    const char *table_name = temp_node.join_relations.relation.c_str();
    std::string alias_name = temp_node.join_relations.alias;
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
    if(!temp_node.join_relations.alias.empty()&&alias_name!="")
    {
       std::pair<std::unordered_map<std::string, Table *>::iterator, bool> ret = alias_map.insert(std::pair<std::string, Table *>(alias_name, table));
      if(!ret.second)
      {
        return RC::INVALID_ARGUMENT;//别名重复
      }
    }
  }

  bool is_star = false;
  int star_index = 10000;//标识star的位置

  for(int i = 0; i < all_relAttrNodes.size() - select_sql.havingcConditions.size();i++)
  {
    if(0 == strcmp(all_relAttrNodes[i].attribute_name.c_str(), "*")&&all_relAttrNodes[0].aggr_func==UNKNOWN){ //这里只判断了第一个是不是为*号
    is_star = true;
    star_index = i;
    break;

  }
  }

  select_sql.attributes = all_relAttrNodes;

// ---------- collect query fields in `select` statement ----------
  std::vector<Field> query_fields;
  std::vector<Field> alias_fields;
  std::vector<AggrOp> aggr_fields;
  std::vector<std::string> aggr_specs;
  std::vector<std::pair<bool,std::string>> aggr_alias;

  const RelAttrSqlNode &relation_attr = select_sql.attributes[0];
  AggrOp aggr_flag = relation_attr.aggr_func;   //是否带有聚合

  for (int i = 0; i < (int)select_sql.attributes.size(); i++) {
    const RelAttrSqlNode &relation_attr = select_sql.attributes[i];
    if(relation_attr.flag)
    {
      alias_fields.push_back(select_sql.attributes[i].alias);
      continue;
    }
    
  //1. 检查聚合的语法, 如果是group by的话可以不做这个检查

    if(select_sql.groupBy.empty()){
      //要么全部都是聚合或者全部都不是聚合
      if(aggr_flag == UNKNOWN){
        if(relation_attr.aggr_func != UNKNOWN){
          LOG_WARN("ID, AGGR(ID) is not allowed.");
          return RC::INVALID_ARGUMENT;
        }
      }
      else{
        if(relation_attr.aggr_func == UNKNOWN){
          LOG_WARN("ID, AGGR(ID) is not allowed.");
          return RC::INVALID_ARGUMENT;
        }
        //检查是否会出现max(*)这种错误语法
        if(relation_attr.aggr_func != COUNTF && (relation_attr.attribute_name == "*")){
          LOG_WARN("MAX(*)/MIN(*)/AVG(*)/SUM(*) is not allowed.");
          return RC::INVALID_ARGUMENT;
        }
      }
    }

  //2. 创建stmt

    //case 1: select * from a;
    if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
      for (Table *table : tables) {
        if(relation_attr.aggr_func != UNKNOWN){

          query_fields.push_back(Field(table, table->table_meta().field(0)));//这里放了字段进去
          alias_fields.push_back(Field(table, table->table_meta().field(0)));
          break;
        }
        else{
          wildcard_fields(table, query_fields);
          wildcard_fields(table, alias_fields);
        }
      }
      aggr_specs.push_back("*");
      if(!relation_attr.alias.empty())//标识该聚合字段是否有别名o
      {
        aggr_alias.push_back(std::pair<bool, std::string>(true, relation_attr.alias));
      }
      else{
        aggr_alias.push_back(std::pair<bool, std::string>(false, relation_attr.alias));
      }
    
    } 
    //case 2: select a.id from a;
    else if (!common::is_blank(relation_attr.relation_name.c_str())) {
      const char *table_name = relation_attr.relation_name.c_str();
      const char *field_name = relation_attr.attribute_name.c_str();

      //2-1：select *.id from a; 一般不会进入到这里 
      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        for (Table *table : tables) {
          if(relation_attr.aggr_func != UNKNOWN){
            query_fields.push_back(Field(table, table->table_meta().field(0)));
            alias_fields.push_back(Field(table, table->table_meta().field(0)));
            
           // break;
          }
          else{
            wildcard_fields(table, query_fields);
            wildcard_fields(table, alias_fields);
          }
        }
        aggr_specs.push_back("*");
        if(!relation_attr.alias.empty()&&relation_attr.alias!="")//标识该聚合字段是否有别名o
        {
          aggr_alias.push_back(std::pair<bool, std::string>(true, relation_attr.alias));
        }
        else{
          aggr_alias.push_back(std::pair<bool, std::string>(false, relation_attr.alias));
        }
      } 
      else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {//在当前表寻找

           iter = alias_map.find(table_name);//在别名中找对比
        if (iter == alias_map.end()) {
           
           iter = parents.find(table_name);//在父表中找对比
        if (iter == parents.end()) {
            LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        }
   
        }

        Table *table = iter->second;
        //2-2-1：select a.* from a; 一般不会进入到这里
        if (0 == strcmp(field_name, "*")) {
          if(relation_attr.aggr_func != UNKNOWN){
            query_fields.push_back(Field(table, table->table_meta().field(0)));
             alias_fields.push_back(Field(table, table->table_meta().field(0)));
          }
          else{
            wildcard_fields(table, query_fields);
            wildcard_fields(table, alias_fields);
          }
          aggr_specs.push_back("*");
          if(!relation_attr.alias.empty()&&relation_attr.alias!="")//标识该聚合字段是否有别名o
          {
            aggr_alias.push_back(std::pair<bool, std::string>(true, relation_attr.alias));
          }
          else{
            aggr_alias.push_back(std::pair<bool, std::string>(false, relation_attr.alias));
          }
        } else {

          const FieldMeta *field_meta = table->table_meta().field(field_name);
          std::string alias_name = relation_attr.alias;
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          query_fields.push_back(Field(table, field_meta,alias_name));
          alias_fields.push_back(Field(table, field_meta,alias_name));
          aggr_specs.push_back(relation_attr.attribute_name);
          if(!relation_attr.alias.empty()&&relation_attr.alias!="")//标识该聚合字段是否有别名o
            {
              aggr_alias.push_back(std::pair<bool, std::string>(true, relation_attr.alias));
            }
            else{
              aggr_alias.push_back(std::pair<bool, std::string>(false, relation_attr.alias));
            }
          }
      }
    } 
    //case 3: select id from a;
    else {
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table *table = tables[0];
      std::string alias_name = relation_attr.alias;
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      query_fields.push_back(Field(table, field_meta, alias_name));
      alias_fields.push_back(Field(table, field_meta,alias_name));
      aggr_specs.push_back(relation_attr.attribute_name);
      if(!relation_attr.alias.empty()&&relation_attr.alias!="")//标识该聚合字段是否有别名o
      {
        aggr_alias.push_back(std::pair<bool, std::string>(true, relation_attr.alias));
      }
      else{
        aggr_alias.push_back(std::pair<bool, std::string>(false, relation_attr.alias));
      }
    }
    aggr_fields.push_back(relation_attr.aggr_func);
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

// ---------- create filter statement in `where` statement ----------
  FilterStmt *filter_stmt = nullptr;
  std::vector<ConditionSqlNode> all_filters;
  int conjunction_flag = -1;
  //conjunction flag
  if((int)select_sql.conditions.size() > 1){
    conjunction_flag = select_sql.conditions[1].conjunction;
  }
  //一般的where条件
  for(size_t i = 0; i < select_sql.conditions.size(); i++){
    all_filters.push_back(select_sql.conditions[i]);
  }
  //join里面的on条件
  for(size_t i = 0; i < select_sql.joinTables.size(); i++){
    for(size_t j = 0; j < select_sql.joinTables[i].join_conditions.size(); j++){
      all_filters.push_back(select_sql.joinTables[i].join_conditions[j]);
    }
  }
  //检查复杂子查询中是否有此父表
  std::unordered_map<std::string, Table *> all_parents = table_map;
  for(std::pair<std::string, Table *> it : parents){
    all_parents.insert(it);
  }
  for(std::pair<std::string, Table *> it : alias_map){
    all_parents.insert(it);
  }
  RC rc = FilterStmt::create(db,
      default_table,
      &all_parents,
      &alias_map,
      all_filters.data(),
      static_cast<int>(all_filters.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

// ---------- create filter statement in `having` statement ----------
  HavingStmt *having_stmt = nullptr;
  std::vector<ConditionSqlNode> all_havings;
  //一般的having条件
  for(size_t i = 0; i < select_sql.havingcConditions.size(); i++){
    all_havings.push_back(select_sql.havingcConditions[i]);
  }
  //create stmt
  rc = HavingStmt::create(db,
      default_table,
      &all_parents,
      all_havings.data(),
      static_cast<int>(all_havings.size()),
      having_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

// ---------- create filter statement in `order by` statement ----------
  OrderByStmt *orderby_stmt = nullptr;
  //DEFER_WHEN_NOT_NULL(orderby_stmt);//在离开作用域时，检查orderby_stmt,如果不为空 delete
  if (0 != select_sql.orderBy.size()) {
    rc = OrderByStmt::create(db, default_table, &table_map,&alias_map, select_sql.orderBy, select_sql.orderBy.size(), orderby_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct order by stmt");
      return rc;
    }
  }

// ----------------- check group by --------------------
/*
 * 在SELECT子句中出现的列必须要么包含在GROUP BY子句中，要么为聚合函数的结果。否则，在执行查询时将会抛出错误。
 */ 
  std::vector<Field> group_by_fields;
  bool groupby_flag = false;
  if((int)select_sql.groupBy.size() > 0){
    groupby_flag = true;
    for(size_t i = 0; i < all_relAttrNodes.size(); i++){
      if(all_relAttrNodes[i].aggr_func == UNKNOWN){
        if(i > (int)select_sql.groupBy.size()-1){
          LOG_WARN("group by mismatch field\n");
          return RC::SCHEMA_FIELD_MISSING;
        }
        if(0 != strcmp(all_relAttrNodes[i].attribute_name.c_str(), select_sql.groupBy[i].attribute_name.c_str())){
          LOG_WARN("group by mismatch field\n");
          return RC::SCHEMA_FIELD_MISSING;
        }
        else{
          //这里假设不会出现select *这种情况
          group_by_fields.push_back(query_fields[i]);
        }
      }
      else break;
    }
  }


// ---------------- everything alright ------------------

  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->alias_fields_.swap(alias_fields);
  //
  select_stmt->aggr_fields_.swap(aggr_fields);
  select_stmt->aggr_specs_.swap(aggr_specs);
  select_stmt->aggr_alias_.swap(aggr_alias);
  select_stmt->having_num_ = (int)select_sql.havingcConditions.size();
  //
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->conjunction_flag_ = conjunction_flag;
  //
  select_stmt->group_by_fields_.swap(group_by_fields);
  select_stmt->having_stmt_ = having_stmt;
  select_stmt->groupby_flag_ = groupby_flag;
  //
  select_stmt->order_by_stmt_ = orderby_stmt;
  //放入表达式
  //这里还得进行一次深度优先遍历，用于把query_fields中解析出来的属性对应的类型写入到expr树对应的Field中
  //否则运算时不知道类型
  select_stmt->is_expr_ = is_expr;
  int expr_index = 0;
  for(size_t i = 0; i < select_sql.expressions.size(); i++){
    dfs_for_field(select_sql.expressions[i], expr_index, select_stmt->query_fields_);
  }

  for(int i = 0;i<star_index&&i<select_sql.expressions.size();i++){
    select_stmt->expressions_.emplace_back(select_sql.expressions[i]);
  }

  if(is_star == true && select_stmt->aggr_fields_[0] == UNKNOWN){
    for(size_t i = star_index; i < select_stmt->query_fields_.size(); i++){
      std::string tablename = select_stmt->query_fields_[i].table_name();
      std::string fieldname = select_stmt->query_fields_[i].field_name();
      FieldExpr *expr = new FieldExpr(tablename, fieldname, UNKNOWN);
      expr->set_field(select_stmt->query_fields_[i]);
      if(select_stmt->tables_.size() > 1){
        std::string s = tablename + "." + fieldname;
        expr->set_name(s);
      }
      else{
        expr->set_name(fieldname);
      }
      select_stmt->expressions_.emplace_back(expr);
    }
  }
  else {
    // for (Expression * const expr : select_sql.expressions) {
    //   select_stmt->expressions_.emplace_back(expr);
    // }
  }

  stmt = select_stmt;
  return RC::SUCCESS;
}