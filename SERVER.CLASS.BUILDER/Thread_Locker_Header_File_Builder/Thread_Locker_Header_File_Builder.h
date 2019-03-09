
#ifndef THREAD_LOCKER_HEADER_FILE_BUILDER_H
#define THREAD_LOCKER_HEADER_FILE_BUILDER_H

#include "CFileOperations.h"

class Thread_Locker_Header_File_Builder
{
public:
 Thread_Locker_Header_File_Builder();
 Thread_Locker_Header_File_Builder(const Thread_Locker_Header_File_Builder & orig);
 virtual ~Thread_Locker_Header_File_Builder();
 void Build_thread_locker_header_file();
private:
 CFileOperations FileManager;
};

#endif /* THREAD_LOCKER_HEADER_FILE_BUILDER_H */
