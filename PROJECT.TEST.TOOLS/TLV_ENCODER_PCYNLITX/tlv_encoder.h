

#ifndef TLV_ENCODER_H
#define TLV_ENCODER_H

#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include "IntToCharTranslater.h"

class tlv_encoder
{
public:
  tlv_encoder();
  tlv_encoder(const tlv_encoder & orig);
  virtual ~tlv_encoder();
  void receive_data_length(int length);
  void receive_dictionary_data(char *** data);
  std::string convert_string_to_binary_form(char * string);
  std::string convert_binary_to_string(std::string s);
  std::string data_encoder(char * data, int type);
  std::string construct_data_stream();
  void Clear_Dynamic_Memory();
private:
  IntToCharTranslater Translater;
  int data_length;
  char *** dictionary;
  bool dynamic_memory_clear_status;
  std::string binary_stream;
  std::string string_stream;
  std::string string_type;
  std::string int_type;
  std::string bool_type;
  std::string encoded_data;
  std::string data_stream;
};

#endif /* TVL_ENCODER_H */
