
#ifndef THREAD_MANAGER_CLIENT_BULDER_H
#define THREAD_MANAGER_CLIENT_BULDER_H

#include "Descriptor_File_Reader.h"
#include "Thread_Manager_Client_Header_Builder.h"
#include "CFileOperations.h"
#include "DirectoryOperations.h"
#include <cstring>
#include <cstdlib>

class Thread_Manager_Client_Builder
{
public:
  Thread_Manager_Client_Builder();
  Thread_Manager_Client_Builder(const Thread_Manager_Client_Builder & orig);
  virtual ~Thread_Manager_Client_Builder();
  void Receive_Descriptor_File_Reader(Descriptor_File_Reader * Pointer);
  void Build_Thread_Manager_Client();
  void Run_System_Commands();
  void Clear_Dynamic_Memory();
private:
  void Clear_Pointer_Memory(char ** Pointer);
  void Place_Information(char ** Pointer,char * String,int * index_counter);
  void Determine_Compiler_Command();
  void Write_Space(int Space_Number);
  void Remove_Source_File();
  Descriptor_File_Reader * Reader_Pointer;
  Thread_Manager_Client_Header_Builder Header_Builder;
  CFileOperations File_Manager;
  DirectoryOperations Directory_Manager;
  char * Compiler_Command;
  char * Constructed_Include_Directory;
  bool Memory_Delete_Condition;
};

#endif /* THREAD_MANAGER_CLIENT_BULDER_H */
