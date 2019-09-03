
#ifndef DATA_RECEIVER_H
#define DATA_RECEIVER_H

#include <cstring>
#include <iostream>
#include "Cpp_FileOperations.h"

class Data_Receiver
{
public:
  Data_Receiver();
  virtual ~Data_Receiver();
  void SetFilePath(std::string FilePATH);
  void SetFilePath(char * String);
  void SetFilePath(const char * String);
  void Receive_Data();
  void Determine_File_Length();
  void Allocate_Memory_For_Each_Line();
  void Print_Data();
  void SetBuffer_1(char * string);
  void SetBuffer_2(char * string);
  void SetTargetMemoryIndex_1(int index);
  void SetTargetMemoryIndex_2(int index);
  void SetTargetMemory(char * string, int index);
  void Set_Data(std::string string_line, char ** pointer);
  void SetBuffer_1_Empty_Condition(bool condition);
  void SetBuffer_2_Empty_Condition(bool condition);
  bool Get_Buffer_1_Empty_Condition();
  bool Get_Buffer_2_Empty_Condition();
  char ** Get_Data_Pointer();
  char ** Get_Target_Memory_Pointer();
  char *  Get_Buffer_1_Pointer();
  char *  Get_Buffer_2_Pointer();
  int     Get_Data_length();
  int     Get_Target_Memory_Index_1();
  int     Get_Target_Memory_Index_2();
private:
  void Set_Data(std::string string_line);
  void Clear_Dynamic_Memory();
  Cpp_FileOperations FileManager;
  bool Memory_Delete_Condition;
  bool Buffer_1_Empty_Condition;
  bool Buffer_2_Empty_Condition;
  int File_Lenght;
  int Target_Memory_Index_1;
  int Target_Memory_Index_2;
  char ** data_list;
  char ** target_memory;
  char *  Buffer_1;
  char *  Buffer_2;
};

#endif /* DATA_RECEIVER_H */
