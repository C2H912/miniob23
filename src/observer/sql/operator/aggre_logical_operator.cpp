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
// Created by Wangyunlai on 2022/12/13.
//

#include "sql/operator/aggre_logical_operator.h"

AggreLogicalOperator::AggreLogicalOperator(const std::vector<Field> &fields, const std::vector<AggrOp> &aggr_fields,
        const std::vector<std::string> &spec, std::unique_ptr<Expression> expression, bool having, int having_num)
: fields_(fields), aggr_fields_(aggr_fields), spec_(spec), having_(having), having_num_(having_num)
{
        expressions_.emplace_back(std::move(expression));
}

AggreLogicalOperator::AggreLogicalOperator(const std::vector<Field> &fields, const std::vector<AggrOp> &aggr_fields,
        const std::vector<std::string> &spec, bool having, int having_num)
: fields_(fields), aggr_fields_(aggr_fields), spec_(spec), having_(having), having_num_(having_num)
{}