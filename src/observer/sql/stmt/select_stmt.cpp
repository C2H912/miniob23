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

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt,std::unordered_map<std::string,Table* > parents)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

// ---------- collect tables in `from` statement ----------
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  std::unordered_map<std::string, Table *> alias_map;
  //位于from里的所有表  //需要修改 这里才是定义表 确定了 只有join和from后面可以定义别名
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
    if(!select_sql.relations[i].alias.empty())
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

    Table *table = db->find_table(table_name);//因为用的是别名，所以很很可能找不到 nonono join的表使用的是本名
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
    if(!temp_node.join_relations.alias.empty())
    {
      //往别名表里面插入数据 同时判断是否重复
      std::pair<std::unordered_map<std::string, Table *>::iterator, bool> ret = alias_map.insert(std::pair<std::string, Table *>(alias_name, table));
      if(!ret.second)
      {
        return RC::INVALID_ARGUMENT;//别名重复
      }
    }
  }
//别名注意事项 不能重复 
// ---------- collect query fields in `select` statement ----------
  std::vector<Field> query_fields;
  std::vector<AggrOp> aggr_fields;
  std::vector<std::string> aggr_specs;
  std::vector<std::pair<bool,std::string>> aggr_alias;

  const RelAttrSqlNode &relation_attr = select_sql.attributes[static_cast<int>(select_sql.attributes.size()) - 1];
  AggrOp aggr_flag = relation_attr.aggr_func;   //是否带有聚合

  for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
    const RelAttrSqlNode &relation_attr = select_sql.attributes[i];
    
  //1. 检查聚合的语法

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

  //2. 创建stmt

    if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
      for (Table *table : tables) {
        if(relation_attr.aggr_func != UNKNOWN){
          query_fields.push_back(Field(table, table->table_meta().field(0)));//*不允许起别名
        }
        else{
          wildcard_fields(table, query_fields);
        }
      }
      aggr_specs.push_back("*");
      if(!relation_attr.alias.empty()&&relation_attr.alias.c_str()!=nullptr)//标识该聚合字段是否有别名o
      {
        aggr_alias.push_back(std::pair<bool, std::string>(true, relation_attr.alias));
      }
      else{
        aggr_alias.push_back(std::pair<bool, std::string>(false, relation_attr.alias));
      }

    } else if (!common::is_blank(relation_attr.relation_name.c_str())) {
      const char *table_name = relation_attr.relation_name.c_str();
      const char *field_name = relation_attr.attribute_name.c_str();
      std::string alias_name = relation_attr.alias;

      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        for (Table *table : tables) {
          if(relation_attr.aggr_func != UNKNOWN){
            query_fields.push_back(Field(table, table->table_meta().field(0)));//这里就不加别名了
          }
          else{
            wildcard_fields(table, query_fields);
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

      } else {
        auto iter = table_map.find(table_name);//在map中 即在表中找
        if (iter == table_map.end()) {
          iter = alias_map.find(table_name);//在alias map中找
          if(iter == alias_map.end())
          {
            LOG_WARN("no such table in from list: %s", table_name);
            return RC::SCHEMA_FIELD_MISSING;
          }
        
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          if(relation_attr.aggr_func != UNKNOWN){
            query_fields.push_back(Field(table, table->table_meta().field(0)));
          }
          else{
            wildcard_fields(table, query_fields);
          }
          aggr_specs.push_back("*");
          if(!relation_attr.alias.empty())//标识该聚合字段是否有别名o
      {
        aggr_alias.push_back(std::pair<bool, std::string>(true, relation_attr.alias));
      }
      else{
        aggr_alias.push_back(std::pair<bool, std::string>(false, relation_attr.alias));
      }
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          query_fields.push_back(Field(table, field_meta,alias_name));
          aggr_specs.push_back(relation_attr.attribute_name);
          if(!relation_attr.alias.empty()&&relation_attr.alias.c_str()!=nullptr)//标识该聚合字段是否有别名o
      {
        aggr_alias.push_back(std::pair<bool, std::string>(true, relation_attr.alias));
      }
      else{
        aggr_alias.push_back(std::pair<bool, std::string>(false, relation_attr.alias));
      }
        }
      }
    } else { //只有属性名

      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table *table = tables[0];//只会有一个表？
       std::string alias_name = relation_attr.alias;
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      query_fields.push_back(Field(table, field_meta,alias_name));
      aggr_specs.push_back(relation_attr.attribute_name);
      if(relation_attr.alias.c_str()!=nullptr)//标识该聚合字段是否有别名o
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

  OrderByStmt *orderby_stmt = nullptr;
  //DEFER_WHEN_NOT_NULL(orderby_stmt);//在离开作用域时，检查orderby_stmt,如果不为空 delete
  if (0 != select_sql.orderBy.size()) {
    rc = OrderByStmt::create(db, default_table, &table_map, select_sql.orderBy, select_sql.orderBy.size(), orderby_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct order by stmt");
      return rc;
    }
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->aggr_fields_.swap(aggr_fields);
  select_stmt->aggr_specs_.swap(aggr_specs);
  select_stmt->aggr_alias_.swap(aggr_alias);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->conjunction_flag_ = conjunction_flag;
  select_stmt->order_by_stmt_ = orderby_stmt;
  stmt = select_stmt;
  return RC::SUCCESS;
}
