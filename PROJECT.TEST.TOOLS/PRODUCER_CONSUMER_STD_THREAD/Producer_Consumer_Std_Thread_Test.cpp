
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <sstream>
#include "Cpp_FileOperations.h"

void Convert_char_to_std_string(std::string * string_line, char * cstring_pointer);

void Determine_Test_Command(char ** test_command, char * thread_number, char * input_file);

int main(int argc, char ** argv){

    if(argc < 4){

       std::cout << "\n\n usage: " << argv[0] << " <test reputation> <thread number> <input file>";

       std::cout << "\n\n";

       exit(0);
    }

    std::cout << "\n\n THE PRODUCER-CONSUMER STD-THREAD TEST";

    std::cout << "\n";


    Cpp_FileOperations FileManager;

    FileManager.SetFilePath("Test_Record_File");

    FileManager.FileOpen(RWCf);

    FileManager.FileClose();

    int sum = 0;

    char * test_command = nullptr;

    Determine_Test_Command(&test_command,argv[2],argv[3]);

    std::string test_repitation = "";

    Convert_char_to_std_string(&test_repitation,argv[1]);

    std::stringstream s(test_repitation);

    int repitation = 0;

    s >> repitation;

    std::cout << "\n The repitation of the test:" << repitation;

    std::cout << "\n\n";

    std::cout << "\n Test Command:" << test_command;

    std::cin.get();

    for(int i=0;i<repitation;i++){

        int return_value = system(test_command);

        std::cout << "\n";

        std::cout << "\n Elapsed time for the test[" << i << "]: ";

        std::cout <<  " " << return_value << std::endl;

        if(return_value == -1){

            repitation++;
        }
        else{

              sum = sum + return_value;
        }
    }

    int average = ((double)sum)/repitation;

    std::cout << "\n\n -------------------------------------";

    std::cout << "\n the average:" << average << std::endl;

    std::cout << "\n\n";

    return 0;
}

void Convert_char_to_std_string(std::string * string_line, char * cstring_pointer){

    int string_length = strlen(cstring_pointer);

    for(int i=0;i<string_length;i++){

        *string_line = *string_line + cstring_pointer[i];
    }
}

void Determine_Test_Command(char ** test_command, char * thread_number, char * input_file){

     char test_binary [] = "./std_thread_producer_consumer";

     char Test_Record_File [] = " >> Test_Record_File";

     int input_file_name_size = strlen(input_file);

     int binary_name_size = strlen(test_binary);

     int record_file_name_size = strlen(Test_Record_File);

     int thread_number_name_size = strlen(thread_number);

     int command_lenght = input_file_name_size + binary_name_size + record_file_name_size

                          + thread_number_name_size;

     *test_command = new char [5*command_lenght];

     int increment = 0;

     for(int i=0;i<binary_name_size;i++){

         (*test_command)[increment] = test_binary[i];

         increment++;
     }

     (*test_command)[increment] = ' ';

     increment++;


     for(int i=0;i<thread_number_name_size;i++){

         (*test_command)[increment] = thread_number[i];

         increment++;
     }


     (*test_command)[increment] = ' ';

     increment++;


     for(int i=0;i<input_file_name_size;i++){

         (*test_command)[increment] = input_file[i];

         increment++;
     }

     for(int i=0;i<record_file_name_size;i++){

         (*test_command)[increment] = Test_Record_File[i];

         increment++;
     }

     (*test_command)[increment] = '\0';
}
