
#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream>
#include <cstring>
#include "Cpp_FileOperations.h"

void Produce_System_Command(char * Matrix_Dimention);

void Convert_char_to_std_string(std::string * string_line, char * cstring_pointer);

char * system_command = nullptr;

int main(int argc, char ** argv){

    int sum = 0;

    std::string test_repitation = "";

    Convert_char_to_std_string(&test_repitation,argv[2]);

    std::stringstream s(test_repitation);

    int repitation = 0;

    s >> repitation;

    Cpp_FileOperations FileManager;

    Produce_System_Command(argv[1]);

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

    return 0;
}

void Convert_char_to_std_string(std::string * string_line, char * cstring_pointer){

    int string_length = strlen(cstring_pointer);

    for(int i=0;i<string_length;i++){

        *string_line = *string_line + cstring_pointer[i];
    }
}

void Produce_System_Command(char * Matrix_Dimention){

     char run_command [] =  "./Pcynlitx_Matrix_Multiplication";

     char Test_Record_File [] = " >> Test_Record_File";

     char space [] = " ";

     int Matrix_Dimention_Character_Size = strlen(Matrix_Dimention);

     int run_command_size = strlen(run_command);

     int Test_Record_File_Character_Size = strlen(Test_Record_File);

     int system_command_size = Matrix_Dimention_Character_Size +

          run_command_size + Test_Record_File_Character_Size;

     system_command = new char [5*system_command_size];

     int index_counter = 0;

     for(int i=0;i<run_command_size;i++){

         system_command[index_counter] = run_command[i];

         index_counter++;
     }

     for(int i=0;i<strlen(space);i++){

         system_command[index_counter] = space[i];

         index_counter++;
     }

     for(int i=0;i<Matrix_Dimention_Character_Size;i++){

         system_command[index_counter] = Matrix_Dimention[i];

         index_counter++;
     }

     for(int i=0;i<Test_Record_File_Character_Size;i++){

         system_command[index_counter] = Test_Record_File[i];

         index_counter++;
     }

     system_command[index_counter] = '\0';
}
