
#include "Process_Supervisor_Descriptor_File_Reader.h"
#include "Inter_Thread_Data_Structure_Builder.h"
#include "Synchronizer_Client_Builder.h"
#include <iostream>
#include <cstring>

int main(int argc, char ** argv){

    Process_Supervisor_Descriptor_File_Reader File_Reader;

    File_Reader.Receive_Descriptor_File_Directory("/home/erkam/Project_Apps");

    File_Reader.Receive_Descriptor_File_Name("Project_Descriptor_File");

    File_Reader.Receive_Descriptor_File_Infomations();

    Synchronizer_Client_Builder Builder;

    Builder.Receive_Process_Supervisor_Descriptor_File_Reader(&File_Reader);

    Builder.Build_Synchronizer_Client();

    Builder.Clear_Dynamic_Memory();

    File_Reader.Clear_Dynamic_Memory();

    std::cout << "\n\n The end of the program .. \n\n";

    return 0;
}
