
#ifndef LIBRARY_DESCRIPTIONS_READER_H
#define LIBRARY_DESCRIPTIONS_READER_H

#include <cstring>
#include <cstdlib>
#include "Process_Supervisor_Descriptor_File_Data_Collector.h"
#include "Process_Supervisor_Descriptor_File_Reader_Initializer.h"
#include "Process_Supervisor_Descriptor_File_Number_Processor.h"
#include "DirectoryOperations.h"

class Library_Descriptions_Reader
{
public:
  Library_Descriptions_Reader();
  Library_Descriptions_Reader(const Library_Descriptions_Reader & orig);
  virtual ~Library_Descriptions_Reader();
  void Receive_Data_Collector(Process_Supervisor_Descriptor_File_Data_Collector * Pointer);
  void Receive_Initializer(Process_Supervisor_Descriptor_File_Reader_Initializer * Pointer);
  void Receive_Number_Processor(Process_Supervisor_Descriptor_File_Number_Processor * Pointer);
  void Read_Library_Descriptions();
  int  Get_Library_Directory_Number();
  int  Get_Library_Names_Number();
  char ** Get_Library_Directories();
  char ** Get_Library_Names();
  void Clear_Dynamic_Memory();
private:
  void Set_Informations_Comes_From_Data_Collector();
  void Place_String(char ** Pointer, char * String);
  void Place_Information(char ** Pointer, char * String, int * index_counter);
  void Clear_Pointer_Memory(char ** Pointer);
  void Receive_Library_Directories();
  void Receive_Library_Names();
  void Print_End_of_Program();
  void Print_Read_Error_Information();
  bool Check_Empty_Decleration(char * String);
  Process_Supervisor_Descriptor_File_Data_Collector * Data_Collector_Pointer;
  Process_Supervisor_Descriptor_File_Reader_Initializer * Initializer_Pointer;
  Process_Supervisor_Descriptor_File_Number_Processor * Number_Processor_Pointer;
  DirectoryOperations Directory_Manager;
  char ** Library_Directories;
  char ** Library_Names;
  int Library_Directory_Number;
  int Library_Names_Number;
  bool Memory_Delete_Condition;
  bool is_empty_decleration;
};

#endif  /* LIBRARY_DESCRIPTIONS_READER_H */
