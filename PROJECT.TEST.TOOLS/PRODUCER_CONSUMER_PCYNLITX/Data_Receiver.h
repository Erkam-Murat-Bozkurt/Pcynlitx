
#ifndef DATA_RECEIVER_H
#define DATA_RECEIVER_H

#include <cstring>
#include <iostream>
#include "Cpp_FileOperations.h"
#include "IntToCharTranslater.h"
#include "acess_sequence_data_types.h"

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
  void Set_First_Group_Acess_Order(int thread_number);
  void Set_Second_Group_Acess_Order(int thread_number);
  void Initialize_Acess_Order_Holders();
  void Print_First_Group_Acess_Order();
  void Print_Second_Group_Acess_Order();
  bool Check_First_Group_Order_Violation();
  bool Check_Second_Group_Order_Violation();
  first_group_order_data  * Get_First_Group_Acess_Order() const;
  second_gorup_order_data * Get_Second_Group_Acess_Order() const;
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
  IntToCharTranslater Translater;
  bool Memory_Delete_Condition;
  bool Buffer_1_Empty_Condition;
  bool Buffer_2_Empty_Condition;
  int File_Lenght;
  int Target_Memory_Index_1;
  int Target_Memory_Index_2;
  first_group_order_data * first_group_list;
  second_gorup_order_data * second_group_list;
  int  first_group_list_increment;
  int  second_group_list_increment;
  bool first_group_order_violation;
  bool second_group_order_violation;
  char ** data_list;
  char ** target_memory;
  char *  Buffer_1;
  char *  Buffer_2;
};

#endif /* DATA_RECEIVER_H */
