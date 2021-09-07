
#ifndef DATA_EXTRACTER_H
#define DATA_EXTRACTER_H

#include <iostream>
#include "StringOperator.h"
#include "CharOperator.h"

class data_extracter
{
public:
  data_extracter();
  data_extracter(const data_extracter & orig);
  virtual ~data_extracter();
  void extract_json_line_data(char * string_data);
  char * getExtractedString();
  char * getExtractedInteger();
  char * getExtractedBolean();
  void Clear_Dynamic_Memory();
private:
  void Clear_String_Memory();
  void Clear_Integer_Memory();
  void Clear_Bool_Memory();
  void Clear_Key_Value_Memory();
  void receive_string_data(char * string_data);
  void extract_string_data();
  void extract_integer_data();
  void extract_bolean_data();
  char * get_next_key_value(char * data);
  bool is_a_valid_character(char c);
  bool include_integer_character(char * key_value);
  bool is_this_key_value_a_string(char * key_value);
  bool is_this_key_value_a_bolean(char * key_value);
  CharOperator CharProcessor;
  StringOperator StringOpr;
  char * key_value;
  char * string_pointer;
  char * string_data;
  char * bool_data;
  char * int_data;
  bool this_key_value_is_a_string;
  bool string_memory_clear_status;
  bool integer_memory_clear_status;
  bool key_value_memory_clear_status;
  bool bool_memory_clear_status;
  bool dynamic_memory_clear_status;
  bool is_this_key_value_an_integer;
  bool this_key_value_is_a_bolean;
  bool is_this_a_valid_character;
  int key_vale_reference_position;
};

#endif /* DATA_EXTRACTER_H */
