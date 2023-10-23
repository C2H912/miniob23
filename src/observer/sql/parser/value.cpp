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
// Created by WangYunlai on 2023/06/28.
//

#include <sstream>
#include "sql/parser/value.h"
#include "storage/field/field.h"
#include "common/log/log.h"
#include "common/lang/comparator.h"
#include "common/lang/string.h"

const char *ATTR_TYPE_NAME[] = {"undefined", "chars", "ints", "dates", "nulls","floats", "booleans"};

const char *attr_type_to_string(AttrType type)
{
  if (type >= UNDEFINED && type <= FLOATS) {
    return ATTR_TYPE_NAME[type];
  }
  return "unknown";
}
AttrType attr_type_from_string(const char *s)
{
  for (unsigned int i = 0; i < sizeof(ATTR_TYPE_NAME) / sizeof(ATTR_TYPE_NAME[0]); i++) {
    if (0 == strcmp(ATTR_TYPE_NAME[i], s)) {
      return (AttrType)i;
    }
  }
  return UNDEFINED;
}

Value::Value(int val)
{
  set_int(val);
}

Value::Value(float val)
{
  set_float(val);
}

Value::Value(bool val)
{
  set_boolean(val);
}

Value::Value(const char *s, int len /*= 0*/)
{
  set_string(s, len);
}

Value::Value(bool is_date, const char *s, int len /*= 0*/)
{
  if (is_date){
    set_date(s);
  }
}

// Value::Value(bool is_null,char *ptr)
// {

// }
void Value::set_null_value()
{
  attr_type_ = NULLS;
  //num_value_ = nullptr;
  
}

void Value::set_data(char *data, int length)
{
  switch (attr_type_) {
    case CHARS: {
      set_string(data, length);
    } break;
    case INTS: {
      num_value_.int_value_ = *(int *)data;
      length_ = length;
    } break;
    case DATES: {
      // set_date(data);
      int tmp = *(int *)data;
      std::string tmpstring = idate2string(tmp);
      const char* tmpdate = tmpstring.c_str();
      length = sizeof(tmpstring);
      set_string(tmpdate, length);
      
      attr_type_ = DATES;

    }break;
    case FLOATS: {
      num_value_.float_value_ = *(float *)data;
      length_ = length;
    } break;
    case BOOLEANS: {
      num_value_.bool_value_ = *(int *)data != 0;
      length_ = length;
    } break;
    default: {
      LOG_WARN("unknown data type: %d", attr_type_);
    } break;
  }
}
void Value::set_int(int val)
{
  attr_type_ = INTS;
  num_value_.int_value_ = val;
  length_ = sizeof(val);
}
void Value::set_only_int(int val)
{
  num_value_.int_value_ = val;
}

void Value::set_float(float val)
{
  attr_type_ = FLOATS;
  num_value_.float_value_ = val;
  length_ = sizeof(val);
}
void Value::set_boolean(bool val)
{
  attr_type_ = BOOLEANS;
  num_value_.bool_value_ = val;
  length_ = sizeof(val);
}
void Value::set_string(const char *s, int len /*= 0*/)
{
  attr_type_ = CHARS;
  if (len > 0) {
    len = strnlen(s, len);
    str_value_.assign(s, len);
  } else {
    str_value_.assign(s);
  }
  length_ = str_value_.length();
}

void Value::set_date(const char *s){
  attr_type_ = DATES;
  int temp = date2int(s);
  if(temp == -1){
    attr_type_ = UNDEFINED;
    str_value_.assign(s);
    return;
  }
  num_value_.int_value_ = temp;
  length_ = sizeof(temp);
}

int date2int(const char *date)
{
  if(date == nullptr)
    return -1;
  //处理2022-1-1这种情况，转化为20220101
  // 计算日期字符串的长度
  int date_length = strlen(date);

  // 分配足够的内存来存储转换后的日期字符串
  char* trans_date = new char[date_length + 1]; // +1 for null terminator
  int i = 0, j = 0;
  // char trans_date[9];
  while(date[i] != '\0'){
    if(date[i] == '-'){
      if(date[i+2] == '\0' || date[i+2] == '-'){
        trans_date[j] = '0';
        trans_date[j+1] = date[i+1];
        j += 2;
        i += 2;
      }
      else{
        trans_date[j] = date[i+1];
        j++;
        i += 2;
      }
    }
    else{
      trans_date[j] = date[i];
      j++;
      i++;
    }
  }
  trans_date[j] = '\0';
  //转化为int型
  i = 0;
  int ret = 0, factor = 10000000;
  while (trans_date[i] != '\0'){
    ret += factor * (trans_date[i] - '0');
    i++;
    factor /= 10;
  }
  // 释放动态分配的内存
  delete[] trans_date;

  //判断闰年
  int temp = ret / 10000;
  bool flag = false;
  if(temp % 4 == 0 && temp % 100 != 0)
    flag = true;
  if(temp % 400 == 0)
    flag = true;
  //处理溢出
  std::unordered_map<int, int> hash;
  hash[1] = 31;
  hash[3] = 31;
  hash[5] = 31;
  hash[7] = 31;
  hash[8] = 31;
  hash[10] = 31;
  hash[12] = 31;
  hash[4] = 30;
  hash[6] = 30;
  hash[9] = 30;
  hash[11] = 30;
  if(flag == true)
    hash[2] = 29;
  else
    hash[2] = 28;
  int month = ret / 100;
  month = month % 100;
  if(month < 1 || month > 12)
    return -1;
  int day = ret % 100;
  if(day < 1 || day > hash[month])
    return -1;

  return ret;
}

void Value::set_value(const Value &value)
{
  switch (value.attr_type_) {
    case INTS: {
      set_int(value.get_int());
    } break;
    case FLOATS: {
      set_float(value.get_float());
    } break;
    case DATES: {
      set_date(value.get_date().c_str());
    }break;
    case CHARS: {
      set_string(value.get_string().c_str());
    } break;
    case BOOLEANS: {
      set_boolean(value.get_boolean());
    } break;
    case UNDEFINED: {
      ASSERT(false, "got an invalid value type");
    } break;
  }
}

const char *Value::data() const
{
  switch (attr_type_) {
    case CHARS: {
      return str_value_.c_str();
    } break;
    case NULLS:{
      return nullptr;
      break;
    }
    default: {
      return (const char *)&num_value_;
    } break;
  }
}

std::string Value::to_string() const
{
  std::stringstream os;
  switch (attr_type_) {
    case INTS: {
      os << num_value_.int_value_;
    } break;
    case FLOATS: {
      os << common::double_to_str(num_value_.float_value_);
    } break;
    case DATES: {
      os << str_value_;
    } break;
    case BOOLEANS: {
      os << num_value_.bool_value_;
    } break;
    case CHARS: {
      os << str_value_;
    } break;
    case NULLS: {
      os << "NULL";
    } break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
  return os.str();
}

void string2number(const char * s, int &ret1, float &ret2)
{
  if(s[0] < '0' || s[0] > '9'){
    ret1 = 0;
    ret2 = 0.0;
    return;
  }
  ret2 = strtod(s, nullptr);
  ret1 = (int)ret2;
}

int Value::compare(const Value &other) const
{
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case INTS: {
        return common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
      } break;
      case FLOATS: {
        return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other.num_value_.float_value_);
      } break;
      case DATES: {
        char* tmp = (char *)this->str_value_.c_str();
        int tempdate = date2int(tmp);
        void* datetocomp = &tempdate;

        return common::compare_int(datetocomp, (void *)&other.num_value_.int_value_);
      } break;
      case CHARS: {
        return common::compare_string((void *)this->str_value_.c_str(),
            this->str_value_.length(),
            (void *)other.str_value_.c_str(),
            other.str_value_.length());
      } break;
      case BOOLEANS: {
        return common::compare_int((void *)&this->num_value_.bool_value_, (void *)&other.num_value_.bool_value_);
      }
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = this->num_value_.int_value_;
    return common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = other.num_value_.int_value_;
    return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == FLOATS) {   //
    const char *this_data = this->ret_str().c_str();
    int ret1 = -1;
    float ret2 = -1.0;
    string2number(this_data, ret1, ret2);
    return common::compare_float((void *)&ret2, (void *)&other.num_value_.float_value_);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == INTS) {  //.
    const char *this_data = this->ret_str().c_str();
    int ret1 = -1;
    float ret2 = -1.0;
    string2number(this_data, ret1, ret2);
    float other_ret = *(int*)other.num_value_.int_value_;
    return common::compare_float((void *)&ret2, (void *)&other_ret);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == CHARS) {  //.
    const char *this_data = other.ret_str().c_str();
    int ret1 = -1;
    float ret2 = -1.0;
    string2number(this_data, ret1, ret2);
    return common::compare_float((void *)&this->num_value_.float_value_, (void *)&ret2);
  } else if (this->attr_type_ == INTS && other.attr_type_ == CHARS) {  //.
    const char *this_data = other.ret_str().c_str();
    int ret1 = -1;
    float ret2 = -1.0;
    string2number(this_data, ret1, ret2);
    float other_ret = *(int*)this->num_value_.int_value_;
    return common::compare_float((void *)&other_ret, (void *)&ret2);
  }
  LOG_WARN("not supported");
  return -1;  // TODO return rc?
}

int Value::get_int() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return (int)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case INTS: {
      return num_value_.int_value_;
    }
    case FLOATS: {
      return (int)(num_value_.float_value_);
    }
    case BOOLEANS: {
      return (int)(num_value_.bool_value_);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

float Value::get_float() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return std::stof(str_value_);
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0.0;
      }
    } break;
    case INTS: {
      return float(num_value_.int_value_);
    } break;
    case FLOATS: {
      return num_value_.float_value_;
    } break;
    case BOOLEANS: {
      return float(num_value_.bool_value_);
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

std::string Value::get_string() const
{
  return this->to_string();
}

std::string Value::get_date() const
{
  int tmp = num_value_.int_value_;
  return idate2string(tmp);
}

std::string idate2string(int idate)
{
  int year = idate / 10000;
  int month = idate / 100;
  month = month % 100;
  int day = idate % 100;
  std::string ret = std::to_string(year) + '-';
  ret += (month < 10 ? '0' + std::to_string(month) : std::to_string(month)) + '-';
  ret += (day < 10 ? '0' + std::to_string(day) : std::to_string(day));
  return ret;
}

bool Value::get_boolean() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        float val = std::stof(str_value_);
        if (val >= EPSILON || val <= -EPSILON) {
          return true;
        }

        int int_val = std::stol(str_value_);
        if (int_val != 0) {
          return true;
        }

        return !str_value_.empty();
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return !str_value_.empty();
      }
    } break;
    case INTS: {
      return num_value_.int_value_ != 0;
    } break;
    case FLOATS: {
      float val = num_value_.float_value_;
      return val >= EPSILON || val <= -EPSILON;
    } break;
    case BOOLEANS: {
      return num_value_.bool_value_;
    } break;
    case NULLS:{
      return false;//期望类型是NULL的话 肯定是false
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return false;
    }
  }
  return false;
}
