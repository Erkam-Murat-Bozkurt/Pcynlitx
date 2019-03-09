
#ifndef PROCESS_SUPERVISOR_FACTORY_H
#define PROCESS_SUPERVISOR_FACTORY_H

#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include "CFileOperations.h"
#include "ClassRebuilder.h"
#include "Inter_Thread_Data_Structure_Builder.h"
#include "Multi_Thread_Pointer_Builder.h"
#include "Process_Supervisor_Descriptor_File_Reader.h"
#include "Process_Supervisor_Builder.h"
#include "Multi_Thread_Pointer_File_Data_Collector.h"
#include "ThreadSynchronization_Builder.h"
#include "Synchronizer_Client_Builder.h"
#include "Main_File_Builder.h"
#include "Process_Supervisor_Factory_Data_Collector.h"
#include "IntToCharTranslater.h"


class Process_Supervisor_Factory
{
public:
 Process_Supervisor_Factory();
 Process_Supervisor_Factory(const Process_Supervisor_Factory & orig);
 virtual ~Process_Supervisor_Factory();
 void Receive_Descriptor_File_Directory(const char * DescriptorFileDirectory);
 void Receive_Descriptor_File_Directory(char * DescriptorFileDirectory);
 void Receive_Descriptor_File_Name(const char * DescriptorFileName);
 void Receive_Descriptor_File_Name(char * DescriptorFileName);
 void Build_Process_Supervisor();
 void Clear_Dynamic_Memory();
private:
 void Construct_Smart_Pointers();
 void Construct_Synchronization_Class();
 void Construct_Synchronization_Class_Client();
 void Construct_Client_Clases();
 void Construct_Smart_Pointers_Clients();
 void Construct_Inter_Thread_Data_Structure();
 void Construct_Server_Class();
 void Construct_New_Library();
 void Construct_Main_File();
 void Construct_Compiler_Descriptor_File();
 void Remove_Compiler_Output_File();
 Process_Supervisor_Descriptor_File_Reader Supervisor_Descriptor_File_Reader;
 Inter_Thread_Data_Structure_Builder ITDS_Builder;
 Process_Supervisor_Builder Supervisor_Builder;
 Multi_Thread_Pointer_Builder Smart_Pointer_Builder;
 Multi_Thread_Pointer_File_Data_Collector File_Data_Collector;
 Process_Supervisor_Factory_Data_Collector Factory_Data_Collector;
 ClassRebuilder ReBuilder;
 ThreadSynchronization_Builder Synchronization_Class_Builder;
 Synchronizer_Client_Builder Synchronizer_Client_Builder_Pointer;
 Main_File_Builder Main_File_Builder_Object;
 IntToCharTranslater Translater;
 char * Compiler_Output_File_Path;
};

#endif /* PROCESS_SUPERVISOR_FACTORY_H */
