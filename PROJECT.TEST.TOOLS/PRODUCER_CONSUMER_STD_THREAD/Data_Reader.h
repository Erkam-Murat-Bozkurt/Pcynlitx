
#ifndef DATA_READER_H
#define DATA_READER_H

#include <cstring>
#include <string>
#include <iostream>
#include "Cpp_FileOperations.h"

struct Read_Data {

    std::string number_string;

    bool read_status;

    bool record_status;

    int  position;
};

struct Thread_Data {

    int record_number;

    int thread_number;
};

class Data_Reader
{
public:
  Data_Reader();
  virtual ~Data_Reader();
  void SetFilePath(std::string FilePATH);
  void SetFilePath(char * String);
  void SetFilePath(const char * String);
  void Receive_Data();
  void Print_Data();
  void Increase_String_Line_Index();
  void Set_String_Line_Index(int index);
  int  Get_String_Line_Index() const;
  int  Get_Data_Size() const;
  void Set_Data_Record_Ready_Status(bool condition);
  bool Get_Data_Record_Ready_Status();
  int  Get_Data_Position(int index);
  bool Get_Data_Read_Status(int index);
  bool Get_Data_Record_Status(int index);
  void Set_Data_Read_Status(int index, bool status);
  void Set_Thread_Data_Record_Status(int index, bool status);
  void Set_Thread_Record_Data(int index, int thread_number);
  int  Get_Thread_Number(int index) const;
  int  Get_Record_Number(int index) const;
  void Increase_Thread_Data_Size();
  int  Get_Record_Data_Size();
  void Set_Thread_Data_Size(int size);
  std::string Get_String_Data(int index) const;
protected:
  void Set_Data(std::string string_line, int i);
  void Determine_File_Length();
  void Allocate_Memory_For_Each_Line();
  void Clear_Dynamic_Memory();
  Cpp_FileOperations FileManager;
  bool Memory_Delete_Condition;
  int File_Lenght;
  int Line_index;
  int Thread_Data_Size;
  int Record_List_Length;
  Read_Data ** Read_Data_Pointer;
  Thread_Data * Thread_Data_Pointer;
};

#endif /* DATA_READER_H */
