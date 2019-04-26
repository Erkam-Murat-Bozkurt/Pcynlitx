
#ifndef THREAD_MANAGER_CLIENT_HEADER_BUILDER_H
#define THREAD_MANAGER_CLIENT_HEADER_BUILDER_H

#include <cstring>
#include <ctype.h>
#include "CFileOperations.h"
#include "Descriptor_File_Reader.h"

class Thread_Manager_Client_Header_Builder
{
public:
  Thread_Manager_Client_Header_Builder();
  Thread_Manager_Client_Header_Builder(const Thread_Manager_Client_Header_Builder & orig);
  virtual ~Thread_Manager_Client_Header_Builder();
  void Receive_Descriptor_File_Reader(Descriptor_File_Reader * Pointer);
  void Build_Header_File();
  void Move_Header_File();
  void Clear_Dynamic_Memory();
private:
  char ConvertToUpper(char character);
  void Determine_Inclusion_Word();
  void Place_Information(char ** Pointer,char * String,int * index_counter);
  void Clear_Pointer_Memory(char ** Pointer);
  Descriptor_File_Reader * Reader_Pointer;
  CFileOperations File_Manager;
  char character;
  char * New_Include_Directory;
  char * Construction_Point;
  char * Inclusion_Word;
  char * Move_Command;
  bool Memory_Delete_Condition;
};

#endif /* SYNCHRONIZER_CLIENT_HEADER_BUILDER_H */
