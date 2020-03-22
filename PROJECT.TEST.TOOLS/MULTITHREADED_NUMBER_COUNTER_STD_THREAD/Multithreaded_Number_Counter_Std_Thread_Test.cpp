
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <sstream>

void Convert_char_to_std_string(std::string * string_line, char * cstring_pointer);

void Determine_Test_Command(char ** test_command, char * arg);


int main(int argc, char ** argv){

    std::cout << "\n\n THE NUMBER COUNTER TEST FOR STD-THREAD LIBRARY:";

    std::cout << "\n";

    int sum = 0;

    char * test_command = nullptr;

    Determine_Test_Command(&test_command,argv[1]);

    std::string test_repitation = "";

    Convert_char_to_std_string(&test_repitation,argv[2]);

    std::stringstream s(test_repitation);

    int repitation = 0;

    s >> repitation;

    std::cout << "\n The repitation of the test:" << repitation;

    std::cout << "\n\n";

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


void Determine_Test_Command(char ** test_command, char * input_file){

     char test_binary [] = "./std_thread_number_counter";

     int string_length = strlen(input_file);

     int binary_lenght = strlen(test_binary);

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

     (*test_command)[increment] = '\0';
}
