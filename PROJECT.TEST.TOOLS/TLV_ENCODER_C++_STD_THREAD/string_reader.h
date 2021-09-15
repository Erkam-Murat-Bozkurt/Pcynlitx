
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
  void receive_thread_number(int thread_number);
  void read_string_data(char * data_file_path);
  int  getDataFileLength();
  void print_string_data();
  void place_thread_data();
  void initialize_thread_containers();
  void determine_thread_data_length();
  int get_thread_data_length(int thread_number);
  char * getFileLine(int line_number);
  char ** getThreadData(int thread_number);
protected:
  void receive_data_file_path(char * data_file_path);
  void determine_data_file_length();
  void initialize_string_memory();
  void place_string_data();
  Cpp_FileOperations FileManager;
  int data_length;
  int thread_number;
  int * thread_data_lenghts;
  bool memory_clear_status;
  char ** string_pointer;
  char *** thread_data;
};


#endif /* JSONREADER_H */
