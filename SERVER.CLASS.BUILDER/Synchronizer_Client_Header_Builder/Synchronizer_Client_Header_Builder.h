
#ifndef SYNCHRONIZER_CLIENT_HEADER_BUILDER_H
#define SYNCHRONIZER_CLIENT_HEADER_BUILDER_H

#include <cstring>
#include <ctype.h>
#include "CFileOperations.h"
#include "Process_Supervisor_Descriptor_File_Reader.h"

class Synchronizer_Client_Header_Builder
{
public:
  Synchronizer_Client_Header_Builder();
  Synchronizer_Client_Header_Builder(const Synchronizer_Client_Header_Builder & orig);
  virtual ~Synchronizer_Client_Header_Builder();
  void Receive_Process_Supervisor_Descriptor_File_Reader(Process_Supervisor_Descriptor_File_Reader * Pointer);
  void Build_Header_File();
  void Move_Header_File();
  void Clear_Dynamic_Memory();
private:
  char ConvertToUpper(char character);
  void Determine_Inclusion_Word();
  void Place_Information(char ** Pointer,char * String,int * index_counter);
  void Clear_Pointer_Memory(char ** Pointer);
  Process_Supervisor_Descriptor_File_Reader * Reader_Pointer;
  CFileOperations File_Manager;
  char character;
  char * New_Include_Directory;
  char * Construction_Point;
  char * Inclusion_Word;
  char * Move_Command;
  bool Memory_Delete_Condition;
};

#endif /* SYNCHRONIZER_CLIENT_HEADER_BUILDER_H */
