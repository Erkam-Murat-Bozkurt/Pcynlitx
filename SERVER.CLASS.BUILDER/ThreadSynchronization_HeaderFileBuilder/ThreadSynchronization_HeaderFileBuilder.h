
#ifndef THREADSYNCHRONIZATION_HEADERFILEBUILDER_H
#define THREADSYNCHRONIZATION_HEADERFILEBUILDER_H

#include "CFileOperations.h"
#include "IntToCharTranslater.h"
#include "Process_Supervisor_Descriptor_File_Reader.h"

class ThreadSynchronization_HeaderFileBuilder
{
public:
 ThreadSynchronization_HeaderFileBuilder();
 ThreadSynchronization_HeaderFileBuilder(const ThreadSynchronization_HeaderFileBuilder & orig);
 virtual ~ThreadSynchronization_HeaderFileBuilder();
 void Receive_Process_Supervisor_Descriptor_File_Reader(Process_Supervisor_Descriptor_File_Reader * Pointer);
 void Build_ThreadSynchronization_Header_File();
private:
 CFileOperations FileManager;
 IntToCharTranslater Translater;
 Process_Supervisor_Descriptor_File_Reader * Reader_Pointer;
};

#endif /* THREADSYNCHRONIZATION_HEADERFILEBUILDER_H */
