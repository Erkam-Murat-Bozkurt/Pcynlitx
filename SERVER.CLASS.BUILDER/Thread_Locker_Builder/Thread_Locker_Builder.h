
#ifndef THREAD_LOCKER_BUILDER_H
#define THREAD_LOCKER_BUILDER_H

#include "CFileOperations.h"
#include "DirectoryOperations.h"
#include "Thread_Locker_Header_File_Builder.h"
#include <cstring>
#include <cstdlib>

class Thread_Locker_Builder
{
public:
 Thread_Locker_Builder();
 Thread_Locker_Builder(const Thread_Locker_Builder & orig);
 virtual ~Thread_Locker_Builder();
 void Build_Thread_Locker();
 void Receive_Supervisor_Newly_Constructed_Include_Directory(char * Directory);
 void Receive_Construction_Point(char * Construction_Point);
 void Run_System_Commands();
 void Clear_Dynamic_Memory();
private:
 void Determine_Compiler_Command();
 void Remove_Header_Extra_File();
 void Place_Information(char ** Pointer, char * Information, int * Counter);
 Thread_Locker_Header_File_Builder HeaderFileBuilder;
 CFileOperations FileManager;
 DirectoryOperations Directory_Manager;
 bool   Memory_Delete_Condition;
 char * Construction_Point_Holder;
 char * Compiler_Command;
 char * Supervisor_Constructed_Include_Directory;
};

#endif /* THREAD_LOCKER_BUILDER_H */
