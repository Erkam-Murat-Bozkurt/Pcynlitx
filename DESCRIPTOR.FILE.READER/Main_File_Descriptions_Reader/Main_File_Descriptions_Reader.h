
#ifndef MAIN_FILE_DESCRIPTIONS_READER_H
#define MAIN_FILE_DESCRIPTIONS_READER_H

#include <cstring>
#include <cstdlib>
#include <iostream>
#include "Process_Supervisor_Descriptor_File_Data_Collector.h"
#include "Process_Supervisor_Descriptor_File_Reader_Initializer.h"
#include "Process_Supervisor_Descriptor_File_Number_Processor.h"

class Main_File_Descriptions_Reader
{
public:
  Main_File_Descriptions_Reader();
  Main_File_Descriptions_Reader(const Main_File_Descriptions_Reader & orig);
  virtual ~Main_File_Descriptions_Reader();
  void Receive_Data_Collector(Process_Supervisor_Descriptor_File_Data_Collector * Pointer);
  void Receive_Initializer(Process_Supervisor_Descriptor_File_Reader_Initializer * Pointer);
  void Receive_Number_Processor(Process_Supervisor_Descriptor_File_Number_Processor * Pointer);
  void Read_Main_File_Descriptions();
  void Clear_Dynamic_Memory();
  char *  Get_Server_Class_Name();
  char *  Get_Server_Class_Header_File_Name();
  char *  Get_Main_File_Name();
  char *  Get_Executable_File_Name();
  char *  Get_Construction_Point();
  char ** Get_Thread_Function_Names();
  int     Get_Thread_Number();
  int     Get_Thread_Function_Number();
private:
  void Set_Informations_Comes_From_Data_Collector();
  void Receive_Construction_Point();
  void Receive_Main_File_Name();
  void Receive_Executable_File_Name();
  void Receive_Server_Class_Name();
  void Receive_Thread_Function_Names();
  void Place_String(char ** Pointer, char * String);
  void Clear_Pointer_Memory(char ** Pointer);
  void Print_Read_Error_Information();
  void Print_End_of_Program();
  Process_Supervisor_Descriptor_File_Data_Collector * Data_Collector_Pointer;
  Process_Supervisor_Descriptor_File_Reader_Initializer * Initializer_Pointer;
  Process_Supervisor_Descriptor_File_Number_Processor * Number_Processor_Pointer;
  char *  Construction_Point;
  char *  Executable_File_Name;
  char *  Main_File_Name;
  char *  Server_Class_Name;
  char *  Server_Class_Header_File_Name;
  char ** Thread_Function_Names;
  bool Memory_Delete_Condition;
  int Thread_Function_Number;
  int Thread_Number;
};

#endif /* MAIN_FILE_DESCRIPTIONS_READER_H */
