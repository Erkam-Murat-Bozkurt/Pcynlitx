
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <sstream>
#include "Cpp_FileOperations.h"

void Convert_char_to_std_string(std::string * string_line, char * cstring_pointer);

int main(int argc, char ** argv){

    int sum = 0;

    std::string test_repitation = "";

    Convert_char_to_std_string(&test_repitation,argv[2]);

    std::stringstream s(test_repitation);

    int repitation = 0;

    s >> repitation;

    Cpp_FileOperations FileManager;

    FileManager.SetFilePath("Matrix_Dimention");

    FileManager.FileOpen(RWCf);

    FileManager.WriteToFile(argv[1]);

    FileManager.FileClose();

    system("rm Test_Record_File");

    for(int i=0;i<repitation;i++){

       system("./C++_Std_Thread_Matrix_Multiplication >> Test_Record_File");

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
