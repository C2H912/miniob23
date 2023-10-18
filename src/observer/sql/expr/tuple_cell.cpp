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
// Created by WangYunlai on 2022/07/05.
//

#include <sstream>
#include "sql/expr/tuple_cell.h"
#include "storage/field/field.h"
#include "common/log/log.h"
#include "common/lang/comparator.h"
#include "common/lang/string.h"

TupleCellSpec::TupleCellSpec(const char *table_name, const char *field_name, const char *alias, AggrOp aggr)
{
  if (table_name) {
    table_name_ = table_name;
  }
  if (field_name) {
    field_name_ = field_name;
  }
  if (alias) {
    alias_ = alias;
  } else {
    if (aggr != UNKNOWN) {
      std::string aggr_name;
      switch (aggr) {
      case MAXF: {
        aggr_name = "MAX(";
        break;
      }
      case MINF: {
        aggr_name = "MIN(";
        break;
      }
      case COUNTF: {
        aggr_name = "COUNT(";
        break;
      }
      case AVGF: {
        aggr_name = "AVG(";
        break;
      }
      case SUMF: {
        aggr_name = "SUM(";
        break;
      }
      }
      if (table_name_.empty()) {
        std::string all_alias = aggr_name + field_name_ + ")";
        alias_ = all_alias;
      } else {
        std::string all_alias = aggr_name + table_name_ + "." + field_name_ + ")";
        alias_ = all_alias;
      }
    }
    if (table_name_.empty()) {
      alias_ = field_name_;
    } else {
      alias_ = table_name_ + "." + field_name_;
    }
  }
}

TupleCellSpec::TupleCellSpec(const char *alias, AggrOp aggr)
{
  if (aggr != UNKNOWN) {
    std::string aggr_name;
    switch (aggr) {
    case MAXF: {
      aggr_name = "MAX(";
      break;
    }
    case MINF: {
      aggr_name = "MIN(";
      break;
    }
    case COUNTF: {
      aggr_name = "COUNT(";
      break;
    }
    case AVGF: {
      aggr_name = "AVG(";
      break;
    }
    case SUMF: {
      aggr_name = "SUM(";
      break;
    }
    }
    std::string field = alias;
    std::string all_alias = aggr_name + field + ")";
    alias_ = all_alias;
  }
  else{
    if (alias) {
      alias_ = alias;
    }
  }
}

TupleCellSpec::TupleCellSpec(const char *alias)
{
  if (alias) {
    alias_ = alias;
  }
}
