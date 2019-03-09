
#ifndef PROCESS_SUPERVISOR_DESCRIPTOR_FILE_READER_INITIALIZER_H
#define PROCESS_SUPERVISOR_DESCRIPTOR_FILE_READER_INITIALIZER_H

#include "Process_Supervisor_Descriptor_File_Data_Collector.h"
#include "IntToCharTranslater.h"

class Process_Supervisor_Descriptor_File_Reader_Initializer
{
public:
  Process_Supervisor_Descriptor_File_Reader_Initializer();
  Process_Supervisor_Descriptor_File_Reader_Initializer(const Process_Supervisor_Descriptor_File_Reader_Initializer & orig);
  virtual ~Process_Supervisor_Descriptor_File_Reader_Initializer();
  void Receve_Data_Collector(Process_Supervisor_Descriptor_File_Data_Collector * Data_Collector);
  void Read_File_Lists();
  void Clear_Dynamic_Memory();
  int     Get_Thread_Number();
  int     Get_Source_File_Number();
  char *  Get_Main_File_Name();
  char *  Get_Executable_File_Name();
  char *  Get_Server_Class_Name();
  char *  Get_Server_Class_Header_File_Name();
  char *  Get_Construction_Directory();
  char ** Get_Include_Directory_List();
  char ** Get_Library_Directory_List();
  char ** Get_Source_File_Location_List();
  char ** Get_Library_Name_List();
  char ** Get_Source_File_List();
  char ** Get_Header_File_List();
  char ** Get_Inter_Thread_Class_Header_File_List();
  char ** Get_Inter_Thread_Class_Names_List();
  char ** Get_Inter_Thread_Class_Instance_Name_List();
  char ** Get_Shared_Data_Type_List();
  char ** Get_Shared_Memory_Pointer_Name_List();
  char ** Get_Shared_Data_Type_Header_File_List();
  char ** Get_Thread_Names_List();
  bool *  Get_Thread_Attributes_List();
private:
  void Clear_Pointer_Memory(char ** Pointer);
  void Receive_Include_Directory_List();
  void Receive_Library_Directory_List();
  void Receive_Source_File_Location_List();
  void Receive_Library_Name_List();
  void Receive_Header_File_Names();
  void Receive_Source_File_Name_List();
  void Receive_Main_File_Name();
  void Receive_Executable_File_Name();
  void Receive_Inter_Thread_Class_Header_File_Names();
  void Receive_Inter_Thread_Class_Names();
  void Receive_Inter_Thread_Class_Instance_Names();
  void Receive_Shared_Memory_Data_Types();
  void Receive_Shared_Memory_Pointer_Names();
  void Receive_Shared_Memory_Data_Types_Header_File_Names();
  void Receive_Construction_Point();
  void Receive_Supervisor_Class_Name();
  void Receive_Thread_Function_Names();
  void Receive_Thread_Number();
  Process_Supervisor_Descriptor_File_Data_Collector * File_Data_Collector;
  IntToCharTranslater Translater;
  bool Memory_Delete_Condition;
  int     Thread_Number;
  char *  Main_File_Name;
  char *  Executable_File_Name;
  char *  Supervisor_Class_Name;
  char *  Supervisor_Class_Header_File_Name;
  char *  Construction_Directory;
  char ** Include_Directory_List;
  char ** Source_File_Location_List;
  char ** Source_File_Name_List;
  char ** Library_Directory_List;
  char ** Library_Name_List;
  char ** Header_File_List;
  char ** Inter_Thread_Class_Header_File_List;
  char ** Inter_Thread_Class_Name_List;
  char ** Inter_Thread_Class_Instance_Name_List;
  char ** Shared_Data_Type_List;
  char ** Shared_Memory_Pointer_Name_List;
  char ** Shared_Data_Type_Header_File_List;
  char ** Thread_Name_List;
};

#endif /* PROCESS_SUPERVISOR_DESCRIPTOR_FILE_READER_INITIALIZER_H */
