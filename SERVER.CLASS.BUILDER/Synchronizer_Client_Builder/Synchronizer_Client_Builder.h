
#ifndef SYNCHRONIZER_CLIENT_BULDER_H
#define SYNCHRONIZER_CLIENT_BULDER_H

#include "Process_Supervisor_Descriptor_File_Reader.h"
#include "Synchronizer_Client_Header_Builder.h"
#include "CFileOperations.h"
#include "DirectoryOperations.h"
#include <cstring>
#include <cstdlib>

class Synchronizer_Client_Builder
{
public:
  Synchronizer_Client_Builder();
  Synchronizer_Client_Builder(const Synchronizer_Client_Builder & orig);
  virtual ~Synchronizer_Client_Builder();
  void Receive_Process_Supervisor_Descriptor_File_Reader(Process_Supervisor_Descriptor_File_Reader * Pointer);
  void Build_Synchronizer_Client();
  void Run_System_Commands();
  void Clear_Dynamic_Memory();
private:
  void Clear_Pointer_Memory(char ** Pointer);
  void Place_Information(char ** Pointer,char * String,int * index_counter);
  void Determine_Compiler_Command();
  void Write_Space(int Space_Number);
  void Remove_Source_File();
  Process_Supervisor_Descriptor_File_Reader * Reader_Pointer;
  Synchronizer_Client_Header_Builder Header_Builder;
  CFileOperations File_Manager;
  DirectoryOperations Directory_Manager;
  char * Compiler_Command;
  char * Newly_Constructed_Include_Directory;
  bool Memory_Delete_Condition;
};

#endif /* SYNCHRONIZER_CLIENT_BULDER_H */
