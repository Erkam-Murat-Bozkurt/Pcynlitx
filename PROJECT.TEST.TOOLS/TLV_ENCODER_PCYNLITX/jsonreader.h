
#ifndef JSONREADER_H
#define JSONREADER_H

#include <iostream>
#include "data_extracter.h"
#include "string_reader.h"
#include "Cpp_FileOperations.h"


struct Dictionary_Data {

  char *** dictionary;
  int thread_number;
};

class jsonreader
{
public:
  jsonreader();
  jsonreader(const jsonreader & orig);
  virtual ~jsonreader();
  void receive_thread_number(int thread_number);
  void collect_json_data(char * data_file_path);
  void print_dictionary();
  char *** getThreadDictionary(int thread_number);
  int  get_thread_data_length(int thread_number);
  int  getDataLength();
  void Clear_Dynamic_Memory();
private:
  Cpp_FileOperations FileManager;
  string_reader  data_reader;
  data_extracter json_extracter;
  void initialize_data_memory();
  void transfer_string(char ** target, char * source);
  int data_length;
  int total_thread_number;
  Dictionary_Data * dictionary_pointer;
  bool dynamic_memory_clear_status;
};

#endif /* JSONREADER_H */
