
#ifndef JSONREADER_H
#define JSONREADER_H

#include <iostream>
#include "data_extracter.h"
#include "string_reader.h"
#include "Cpp_FileOperations.h"


class jsonreader
{
public:
  jsonreader();
  jsonreader(const jsonreader & orig);
  virtual ~jsonreader();
  void collect_json_data(char * data_file_path);
  void print_dictionary();
  char *** getDictionary();
  int  getDataLength();
  void Clear_Dynamic_Memory();
private:
  Cpp_FileOperations FileManager;
  string_reader  data_reader;
  data_extracter json_extracter;
  void initialize_data_memory();
  void transfer_string(char ** target, char * source);
  int data_length;
  char *** dictionary;
  bool dynamic_memory_clear_status;
};

#endif /* JSONREADER_H */
