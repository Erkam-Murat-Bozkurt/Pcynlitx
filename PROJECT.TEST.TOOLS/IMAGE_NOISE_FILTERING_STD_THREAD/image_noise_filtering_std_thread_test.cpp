
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <sstream>
#include "Cpp_FileOperations.h"

void Convert_char_to_std_string(std::string * string_line, char * cstring_pointer);

void Determine_Test_Command(char ** test_command, char * arg);

int main(int argc, char ** argv){

    std::cout << "\n\n THE MULTITHREAD IMAGE NOISE FILTERING TEST";

    std::cout << "\n";

    char * test_command = nullptr;

    Determine_Test_Command(&test_command,argv[1]);

    int sum = 0;

    std::string test_repitation = "";

    Convert_char_to_std_string(&test_repitation,argv[2]);

    std::stringstream s(test_repitation);

    int repitation = 0;

    s >> repitation;

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

    delete [] test_command;

    std::cout << "\n the average:" << ((double)sum)/repitation << std::endl;

    return 0;
}


void Convert_char_to_std_string(std::string * string_line, char * cstring_pointer){

    int string_length = strlen(cstring_pointer);

    for(int i=0;i<string_length;i++){

        *string_line = *string_line + cstring_pointer[i];
    }
}


void Determine_Test_Command(char ** test_command, char * input_file){

     char test_binary [] = "./image_noise_filtering_std_thread";

     char record_file [] = ">> Test_Record_File";

     int string_length = strlen(input_file);

     int binary_lenght = strlen(test_binary);

     int record_file_lenght = strlen(record_file);

     int command_lenght = string_length + binary_lenght;

     *test_command = new char [5*command_lenght];

     int increment = 0;

     for(int i=0;i<binary_lenght;i++){

         (*test_command)[increment] = test_binary[i];

         increment++;
     }

     (*test_command)[increment] = ' ';

     increment++;

     for(int i=0;i<string_length;i++){

         (*test_command)[increment] = input_file[i];

         increment++;
     }

     (*test_command)[increment] = ' ';

     increment++;

     for(int i=0;i<record_file_lenght;i++){

        (*test_command)[increment] = record_file[i];

        increment++;
     }

     (*test_command)[increment] = '\0';
}
