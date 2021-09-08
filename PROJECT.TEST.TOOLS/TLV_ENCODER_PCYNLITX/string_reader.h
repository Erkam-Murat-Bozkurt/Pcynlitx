
#ifndef STRING_READER_H
#define STRING_READER_H

#include <iostream>
#include "Cpp_FileOperations.h"
#include <string>
#include <cstring>

class string_reader
{
public:
  string_reader();
  string_reader(const string_reader & orig);
  virtual ~string_reader();
  void read_string_data(char * data_file_path);
  int getDataFileLength();
  void print_string_data();
  char * getFileLine(int line_number);
protected:
  void receive_data_file_path(char * data_file_path);
  void determine_data_file_length();
  void initialize_string_memory();
  void place_string_data();
  Cpp_FileOperations FileManager;
  int data_length;
  bool memory_clear_status;
  char ** string_pointer;
};


#endif /* JSONREADER_H */
