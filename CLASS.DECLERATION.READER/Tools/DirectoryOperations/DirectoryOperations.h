
#ifndef DIRECTORYOPERATIONS_H
#define DIRECTORYOPERATIONS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <dirent.h>
#include <cstdio>

class DirectoryOperations
{
public:
 DirectoryOperations();
 DirectoryOperations(const DirectoryOperations & orig);
 virtual ~DirectoryOperations();
 void LoadSystemFunctionCommand(const char * command,char * DirectoryName);
 void RecordCurrentDirectoryPATH();
 void ReturnRecordedDirectoryPATH();
 void DetermineCurrentDirectory();
 void DetermineSubDirectoryName(char * DirectoryName);
 void DetermineUpperDirectoryName();
 void Determine_File_List_In_Directory(char * DirectoryName);
 void Remove_Directory_Recursively(char * DirectoryName);
 void Clear_Dynamic_Memory();
 int  MakeDirectory(const char * path, mode_t mode);
 int  MakeSubDirectory(char * path, mode_t mode);
 int  ChangeDirectory(const char * path);
 int  RemoveDirectory(const char * path);
 int  GoToUpperDirectory();
 int  GoToSubDirectory(char * DirectoryName);
 int  RemoveSubDirectory(char * DirectoryName);
 int  ChangeDirectoryMode(const char * path, mode_t mode);
 bool Search_File_in_Directory(char * Directory_Name, char * File_Name);
 char * GetRecordedDirectoryPATH();
 char * GetCurrentlyWorkingDirectory();
 char * GetSubDirectoryName();
 char * GetUpperDirectoryName();
 char * GetSystemFunctionCommand();
 std::string * Get_File_List_In_Directory();
 int    Get_File_Number_In_Directory();
private:
 void   Place_String(char ** Pointer, char * String, size_t String_Size);
 void   Place_Information(char ** Pointer, const char * Information, int * index_counter);
 void   Place_Information(char ** Pointer, char * Information, int * index_counter);
 bool   Memory_Delete_Condition;
 std::string * File_List;
 char * SystemCommand;
 char * CurrentDirectory;
 char * Sub_Directory;
 char * Upper_Directory;
 char * RecordDirectoryPATH;
 bool   File_Exist_Condition;
 int    ReturnCondition;
 int    File_Number;
};

#endif /* DIRECTORYOPERATIONS_H */
