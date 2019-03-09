
#ifndef PROCESS_SUPERVISOR_FACTORY_DATA_COLLECTOR_H
#define PROCESS_SUPERVISOR_FACTORY_DATA_COLLECTOR_H

#include <cstdlib>
#include <cstring>
#include "DirectoryOperations.h"
#include "Process_Supervisor_Descriptor_File_Reader.h"
#include <unistd.h>

class Process_Supervisor_Factory_Data_Collector
{
public:
  Process_Supervisor_Factory_Data_Collector();
  Process_Supervisor_Factory_Data_Collector(const Process_Supervisor_Factory_Data_Collector & orig);
  virtual ~Process_Supervisor_Factory_Data_Collector();
  void Receive_Process_Supervisor_Descriptor_File_Reader(Process_Supervisor_Descriptor_File_Reader * Pointer);
  void Clear_Dynamic_Memory();
  void Jump_To_Construction_Point();
  void Determine_Object_File_List();
  void Remove_Object_Files();
  void Construct_New_Library();
  void Construct_New_Include_Directory();
  char * Get_New_Include_Directory_Name();
private:
  void Clear_Pointer_Memory(char ** Pointer);
  void Place_String(char ** Pointer,char * String, int String_Size);
  void Place_Information(char ** Pointer, char * Information, int * index_counter);
  Process_Supervisor_Descriptor_File_Reader * Reader_Pointer;
  DirectoryOperations DirectoryManager;
  bool Memory_Delete_Condition;
  char * New_Include_Directory_Name;
  char * Object_File_List;
  char * Library_Construction_Command;
};


#endif /* PROCESS_SUPERVISOR_FACTORY_DATA_COLLECTOR_H */
