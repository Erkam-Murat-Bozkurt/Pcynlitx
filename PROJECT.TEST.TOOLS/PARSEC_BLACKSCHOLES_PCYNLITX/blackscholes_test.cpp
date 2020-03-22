

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

void Determination_of_test_command(char ** test_command, char * exe_file,  char * threadNumber, char * inputFile, char * targetFile);

int main(int argc, char ** argv){

    std::cout << "\n\n PARSEC BLACKSCHOLES PCYNLITX TEST";

    std::cout << "\n";

    int sum = 0;

    std::string test_repitation = "";

    Convert_char_to_std_string(&test_repitation,argv[1]);

    std::stringstream s(test_repitation);

    int repitation = 0;

    s >> repitation;

    std::cout << "\n The number of repitation:" << repitation;

    std::cout << "\n";

    char * test_command = nullptr;

    Determination_of_test_command(&test_command,argv[2],argv[3],argv[4],argv[5]);

    Cpp_FileOperations FileManager;

    system("rm Test_Record_File");

    for(int i=0;i<repitation;i++){

       system(test_command);

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


    std::cout << "\n\n -------------------------------------";

    std::cout << "\n the average:" << ((double)sum)/repitation << std::endl;

    std::cout << "\n\n";

    delete [] test_command;

    return 0;
}


void Convert_char_to_std_string(std::string * string_line, char * cstring_pointer){

    int string_length = strlen(cstring_pointer);

    for(int i=0;i<string_length;i++){

        *string_line = *string_line + cstring_pointer[i];
    }
}

void Determination_of_test_command(char ** test_command, char * exe_file, char * threadNumber, char * inputFile, char * targetFile){

     char space = ' ';

     char send_command [] = ">>";

     char Test_Record_File [] = "Test_Record_File";

     int exe_file_character_size = strlen(exe_file);

     int inputFile_character_size = strlen(inputFile);

     int targetFile_character_size = strlen(targetFile);

     int threadNumber_size = strlen(threadNumber);

     int Send_Command_Name_Size = strlen(send_command);

     int Test_Record_File_Character_Size = strlen(Test_Record_File);

     int command_size = exe_file_character_size + inputFile_character_size

                        + targetFile_character_size + threadNumber_size

                        + Test_Record_File_Character_Size;

     *test_command = new char [5*command_size];

     int index_number = 0;

     for(int i=0;i<exe_file_character_size;i++)
     {
         (*test_command)[index_number] = exe_file[i];

         index_number++;
     }

     (*test_command)[index_number] = space;

     index_number++;

     for(int i=0;i<threadNumber_size;i++){

         (*test_command)[index_number] = threadNumber[i];

         index_number++;
     }

     (*test_command)[index_number] = space;

     index_number++;

     for(int i=0;i<inputFile_character_size;i++){

        (*test_command)[index_number] = inputFile[i];

        index_number++;
     }

     (*test_command)[index_number] = space;

     index_number++;

     for(int i=0;i<targetFile_character_size;i++)
     {
        (*test_command)[index_number] = targetFile[i];

        index_number++;
     }

     (*test_command)[index_number] = space;

     index_number++;

     for(int i=0;i<Send_Command_Name_Size;i++){

         (*test_command)[index_number] = send_command[i];

         index_number++;
     }

     (*test_command)[index_number] = space;

     index_number++;

     for(int i=0;i<Test_Record_File_Character_Size;i++){

         (*test_command)[index_number] = Test_Record_File[i];

         index_number++;
     }

     (*test_command)[index_number] = '\0';
}
