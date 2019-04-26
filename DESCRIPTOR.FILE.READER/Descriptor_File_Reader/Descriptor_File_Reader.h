
#ifndef DESCRIPTOR_FILE_READER_H
#define DESCRIPTOR_FILE_READER_H

#include "Inter_Thread_Class_Description_Reader.h"
#include "Inter_Thread_Data_Type_Description_Reader.h"
#include "Header_File_Descriptions_Reader.h"
#include "Source_File_Descriptions_Reader.h"
#include "Library_Descriptions_Reader.h"
#include "Main_File_Descriptions_Reader.h"
#include "Include_Directory_Description_Reader.h"
#include "Descriptor_File_Data_Collector.h"
#include "Descriptor_File_Reader_Initializer.h"
#include "Descriptor_File_Number_Processor.h"
#include "Descriptor_File_Reader_Syntax_Controller.h"
#include <cstring>
#include <cstdlib>
#include <unistd.h>

class Descriptor_File_Reader
{
public:
 Descriptor_File_Reader();
 Descriptor_File_Reader(const Descriptor_File_Reader & orig);
 virtual ~Descriptor_File_Reader();
 void Receive_Descriptor_File_Directory(const char * DescriptorFileDirectory);
 void Receive_Descriptor_File_Directory(char * DescriptorFileDirectory);
 void Receive_Descriptor_File_Name(const char * DescriptorFileName);
 void Receive_Descriptor_File_Name(char * DescriptorFileName);
 void Receive_Descriptor_File_Infomations();
 int  Get_Class_Number();
 int  Get_Source_File_Location_Number();
 int  Get_Source_File_Names_Number();
 int  Get_Thread_Number();
 int  Get_Thread_Function_Number();
 int  Get_Shared_Data_Types_Number();
 int  Get_Shared_Data_Types_Include_File_Names_Number();
 int  Get_Header_Files_Number();
 int  Get_Include_Directory_Number();
 int  Get_Library_Directory_Number();
 int  Get_Library_Names_Number();
 Include_Directory_Type   * Get_Include_Directory();
 Class_Data_Type          * Get_Class_Names();
 Shared_Memory_Data_Type  * Get_Shared_Data_Types();
 char *  Get_Server_Class_Name();
 char *  Get_Server_Class_Header_File_Name();
 char *  Get_Main_File_Name();
 char *  Get_Executable_File_Name();
 char *  Get_Construction_Point();
 char *  Get_Constructed_Include_Directory();
 char ** Get_Thread_Function_Names();
 char ** Get_Library_Directories();
 char ** Get_Library_Names();
 char ** Get_Source_File_Locations();
 char ** Get_Source_File_Names();
 char ** Get_Header_File_Names();
 char ** Get_Header_File_Paths();
 void Clear_Dynamic_Memory();
private:
 void Receive_Include_Directory_Descriptions();
 void Receive_Source_File_Descriptions();
 void Receive_Header_File_Descriptions();
 void Receive_Library_Descriptions();
 void Receive_Inter_Thread_Class_Names();
 void Receive_Shared_Memory_Data_Types();
 void Receive_Main_File_Descriptions();
 void Remove_Compiler_Output_File();
 void Determine_Newly_Constructed_Include_Directory();
 void Control_Process_Header_Files_Syntax();
 Descriptor_File_Data_Collector File_Data_Collector;
 Descriptor_File_Reader_Initializer Reader_Initializer;
 Descriptor_File_Number_Processor Number_Processor;
 Inter_Thread_Class_Description_Reader IT_Class_Reader;
 Inter_Thread_Data_Type_Description_Reader IT_Data_Type_Reader;
 Include_Directory_Description_Reader ID_Description_Reader;
 Source_File_Descriptions_Reader SF_Descriptions_Reader;
 Header_File_Descriptions_Reader HF_Descriptions_Reader;
 Library_Descriptions_Reader Lib_Descriptions_Reader;
 Main_File_Descriptions_Reader MF_Descriptions_Reader;
 Descriptor_File_Reader_Syntax_Controler Syntax_Controler;
 bool Memory_Delete_Condition;
 char * Compiler_Output_File_Path;
 char * Constructed_Include_Directory;
};

#endif /* DESCRIPTOR_FILE_READER_H */
