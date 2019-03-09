
#ifndef PROCESS_SUPERVISOR_BUILDER_H
#define PROCESS_SUPERVISOR_BUILDER_H

#include <cstring>
#include <cstdlib>
#include <iostream>
#include "CFileOperations.h"
#include "IntToCharTranslater.h"
#include "DirectoryOperations.h"
#include "Process_Supervisor_Header_File_Builder.h"
#include "Process_Supervisor_Descriptor_File_Reader.h"
#include <unistd.h>

class Process_Supervisor_Builder
{
public:
 Process_Supervisor_Builder();
 Process_Supervisor_Builder(const Process_Supervisor_Builder & orig);
 virtual ~Process_Supervisor_Builder();
 void Receive_Process_Descriptor_File_Reader(Process_Supervisor_Descriptor_File_Reader * Pointer);
 void Receive_Newly_Constructed_Include_Directory(char * New_Include_Directory);
 void Build_Supervisor_Class();
 void Run_System_Commands();
 void Clear_Dynamic_Memory();
 char * Get_Compiler_Command();
 char * Get_Supervisor_Class_Object_File_Name();
 char * Get_Supervisor_Class_Source_File_Name();
 char * Get_Remove_Command_For_Source_File_Name();
private:
 void Place_String(char ** Pointer, char * String, int String_Size);
 void Place_String(char ** Pointer, const char * String, int String_Size);
 void Place_Information(char ** Pointer, char * Information, int * index_counter);
 void Determine_File_Names();
 void Determine_Compiler_Command_For_Supervisor_Class();
 void Clear_Pointer_Memory(char ** Pointer);
 void Write_Space(char * String);
 void Write_Space(const char * String);
 void Update_String_Length(char * String, int * index_counter);
 void Remove_Source_File();
 void Move_Header_File();
 void Write_Thread_Activation_Member_Function();
 void Write_Join_Member_Function();
 Process_Supervisor_Header_File_Builder Header_File_Builder;
 Process_Supervisor_Descriptor_File_Reader * Reader_Pointer;
 CFileOperations FileManager;
 DirectoryOperations Directory_Manager;
 IntToCharTranslater Translater;
 bool Memory_Delete_Condition;
 char *  New_Include_Directory;
 char *  Supervisor_Class_Implementation_File_Name;
 char *  Supervisor_Class_Object_File_Name;
 char *  Compiler_Command_For_Supervisor_Class;
};

#endif /* PROCESS_SUPERVISOR_BUILDER_H */
