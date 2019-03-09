
#ifndef PROCESS_SUPERVISOR_HEADER_FILE_BUILDER_H
#define PROCESS_SUPERVISOR_HEADER_FILE_BUILDER_H

#include <cstring>
#include <ctype.h>
#include "CFileOperations.h"
#include "IntToCharTranslater.h"
#include "Process_Supervisor_Descriptor_File_Reader.h"
#include "MemberFunctionReader.h"

class Process_Supervisor_Header_File_Builder
{
public:
 Process_Supervisor_Header_File_Builder();
 Process_Supervisor_Header_File_Builder(const Process_Supervisor_Header_File_Builder & orig);
 virtual ~Process_Supervisor_Header_File_Builder();
 void Receive_Process_Descriptor_File_Reader(Process_Supervisor_Descriptor_File_Reader * Pointer);
 void Build_Supervisor_Header_File();
 void Move_Header_File();
 void Clear_Dynamic_Memory();
private:
 void Determine_Inclusion_Word();
 void Place_Information(char ** Pointer,char * String,int * index_counter);
 char ConvertToUpper(char character);
 CFileOperations FileManager;
 IntToCharTranslater Translater;
 Process_Supervisor_Descriptor_File_Reader * Reader_Pointer;
 MemberFunctionReader FunctionReader;
 bool Memory_Delete_Condition;
 char * InclusionWord;
 char * New_Include_Directory;
 char * Construction_Point;
 char * Move_Command;
 char   character;
};

#endif /* PROCESS_SUPERVISOR_HEADER_FILE_BUILDER_H */
