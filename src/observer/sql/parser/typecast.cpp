
#include "sql/parser/typecast.h"

std::string double2string(double v)
{
  char buf[256];
  snprintf(buf, sizeof(buf), "%.2f", v);
  size_t len = strlen(buf);
  while (buf[len - 1] == '0') {
    len--;
      
  }
  if (buf[len - 1] == '.') {
    len--;
  }

  return std::string(buf, len);
}

void string2number2(const char * s, int &ret1, float &ret2)
{
  if(s[0] < '0' || s[0] > '9'){
    ret1 = 0;
    ret2 = 0.0;
    return;
  }
  ret2 = strtod(s, nullptr);
  ret1 = (int)ret2;
}

void input_typecast(Value *input, AttrType output_type)
{
  AttrType input_type = input->attr_type();
  if(output_type == INTS){
    switch(input_type){
    case FLOATS: {
      float tempf = input->get_float();
      int tempi = 0;
      if(((int)(tempf + 0.5)) > ((int)tempf))
        tempi = (int)(tempf + 0.5);
      else
        tempi = (int)tempf;
      input->set_int(tempi);
      break;
    }
    case CHARS: {
      int tempi = 0;
      float tempf = 0.0;
      string2number2(input->ret_str().c_str(), tempi, tempf);
      if(((int)(tempf + 0.5)) > ((int)tempf))
        tempi = (int)(tempf + 0.5);
      else
        tempi = (int)tempf;
      input->set_int(tempi);
      break;
    } 
    }
  }
  if(output_type == FLOATS){
    switch(input_type){
    case INTS: {
      float tempd = input->get_int();
      input->set_float(tempd);
      break;
    }
    case CHARS: {
      int tempi = 0;
      float tempf = 0.0;
      string2number2(input->ret_str().c_str(), tempi, tempf);
      input->set_float(tempi);
      break;
    } 
    }
  }
  if(output_type == CHARS){
    switch(input_type){
    case FLOATS: {
      std::string temps = double2string(input->get_float());
      input->set_string(temps.c_str());
      break;
    }
    case INTS: {
      float tempf = input->get_int();
      std::string temps = double2string(tempf);
      input->set_string(temps.c_str());
      break;
    } 
    }
  }
}