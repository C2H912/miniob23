#pragma once
#include <string>
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
std::string double2string(double v);
void string2number2(const char * s, int &ret1, float &ret2);
void input_typecast(Value *input, AttrType output_type);