
#ifndef THREADSYNCHRONIZATION_BUILDER_H
#define THREADSYNCHRONIZATION_BUILDER_H

#include <cstring>
#include <cstdlib>
#include "CFileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"
#include "Thread_Locker_Builder.h"
#include "ThreadSynchronization_HeaderFileBuilder.h"
#include "Process_Supervisor_Descriptor_File_Reader.h"

class ThreadSynchronization_Builder
{
public:
 ThreadSynchronization_Builder();
 ThreadSynchronization_Builder(const ThreadSynchronization_Builder & orig);
 virtual ~ThreadSynchronization_Builder();
 void Receive_Process_Supervisor_Descriptor_File_Reader(Process_Supervisor_Descriptor_File_Reader * Pointer);
 void Build_ThreadSynchronization();
 void Receive_Supervisor_Newly_Constructed_Include_Directory(char * Directory);
 void Run_System_Commands();
 void Clear_Dynamic_Memory();
private:
 void Determine_Compiler_Command();
 void Remove_Source_File();
 void Remove_Header_Extra_File();
 void Move_Header_File();
 void Place_Information(char ** Pointer, char * Information, int * Counter);
 Thread_Locker_Builder Locker_Builder;
 Process_Supervisor_Descriptor_File_Reader * Reader_Pointer;
 ThreadSynchronization_HeaderFileBuilder HeaderFileBuilder;
 CFileOperations FileManager;
 DirectoryOperations Directory_Manager;
 IntToCharTranslater Translater;
 bool   Memory_Delete_Condition;
 char * Compiler_Command;
 char * Supervisor_Constructed_Include_Directory;
};

#endif /* THREADSYNCHRONIZATION_BUILDER_H */
