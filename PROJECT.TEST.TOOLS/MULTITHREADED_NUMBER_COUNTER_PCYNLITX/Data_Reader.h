
#ifndef DATA_READER_H
#define DATA_READER_H

#include <cstring>
#include <iostream>
#include "Cpp_FileOperations.h"
#include "StringOperator.h"

class Data_Reader
{
public:
  Data_Reader();
  virtual ~Data_Reader();
  void SetFilePath(std::string FilePATH);
  void SetFilePath(char * String);
  void SetFilePath(const char * String);
  void Receive_Data();
  void Determine_File_Length();
  void Allocate_Memory_For_Each_Line();
  void Print_Data();
  void Increase_Line_Index();
  int  Get_Line_Index();
  int  Get_Data_length();
  void Set_Data(std::string string_line, char ** pointer);
  void Set_Ready_For_Writing_Condition(bool condition);
  bool Get_Ready_For_Writing_Condition();
  char ** Get_Data_Pointer();
  int *  Get_Record_Point_Pointer_02();
  int *  Get_Record_Point_Pointer_13();
private:
  void Set_Data(std::string string_line);
  void Clear_Dynamic_Memory();
  Cpp_FileOperations FileManager;
  bool Memory_Delete_Condition;
  bool Index_Writing_Condition;
  int File_Lenght;
  int Line_index;
  int Record_point_index;
  char ** data_list;
  int *  Record_Memory_02;
  int *  Record_Memory_13;
};

#endif /* DATA_READER_H */
