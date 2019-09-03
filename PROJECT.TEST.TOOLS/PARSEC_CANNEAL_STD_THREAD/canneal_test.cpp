

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <string>
#include <sstream>
#include "Cpp_FileOperations.h"

void Convert_char_to_std_string(std::string * string_line, char * cstring_pointer);

int main(int argc, char ** argv){

    int sum = 0;

    std::string test_repitation = "";

    Convert_char_to_std_string(&test_repitation,argv[1]);

    std::stringstream s(test_repitation);

    int repitation = 0;

    s >> repitation;

    int Target_File_Name_Size = strlen(argv[2]);

    char * target_file_name = argv[2];

    char TestOutputs_Record_File [] = "TestOutputs";

    char canneal [] = "./canneal 4 10 0";

    char send_command [] = ">> Test_Record_File";

    int  Executable_File_Name_Size = strlen(canneal);

    int  TestOutputs_Record_File_Name_Size = strlen(TestOutputs_Record_File);

    int  Send_Command_Name_Size = strlen(send_command);

    int system_command_name_size = Target_File_Name_Size + TestOutputs_Record_File_Name_Size +

                                   Executable_File_Name_Size + Send_Command_Name_Size;

    char * system_command = new char [10*system_command_name_size];

    int index_number = 0;

    for(int i=0;i<Executable_File_Name_Size;i++){

        system_command[index_number] = canneal[i];

        index_number++;
    }

    system_command[index_number] = ' ';

    index_number++;

    for(int i=0;i<Target_File_Name_Size;i++){

        system_command[index_number] = target_file_name[i];

        index_number++;
    }

    system_command[index_number] = ' ';

    index_number++;

    for(int i=0;i<TestOutputs_Record_File_Name_Size;i++){

        system_command[index_number] = TestOutputs_Record_File[i];

        index_number++;
    }

    system_command[index_number] = ' ';

    index_number++;

    for(int i=0;i<Send_Command_Name_Size;i++){

        system_command[index_number] = send_command[i];

        index_number++;
    }

    system_command[index_number] = '\0';

    Cpp_FileOperations FileManager;

    system("rm Test_Record_File");

    for(int i=0;i<repitation;i++){

       system(system_command);

       system("echo \"\n\" >> Test_Record_File");
    }

    FileManager.SetFilePath("Test_Record_File");

    FileManager.FileOpen(Rf);

    std::string test_result = "";

    while(!FileManager.Control_End_of_File()){

          test_result = FileManager.ReadLine();

          if(test_result[0] != '\n'){

             std::stringstream s(test_result);

             int test_output = 0;

             s >> test_output;

             sum = sum + test_output;
          }

          std::cout << "\n sum:" << sum;
    }

    FileManager.FileClose();

    std::cout << "\n the average:" << ((double)sum)/repitation;

    delete [] system_command;

    return 0;
}


void Convert_char_to_std_string(std::string * string_line, char * cstring_pointer){

    int string_length = strlen(cstring_pointer);

    for(int i=0;i<string_length;i++){

        *string_line = *string_line + cstring_pointer[i];
    }
}
