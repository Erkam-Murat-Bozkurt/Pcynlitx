

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <sstream>
#include "IntToCharTranslater.h"
#include "Cpp_FileOperations.h"

void Convert_String_To_Int(std::string, char ** cstring_pointer);

int main(int argc, char ** argv){

    int sum = 0, repitation = 20;

    std::string string_line;

    Cpp_FileOperations FileManager;

    IntToCharTranslater Translater;

    system("rm Test_Record_File");

    for(int i=0;i<repitation;i++){

       system("./C++_Std_Thread_File_Search >> Test_Record_File");

       system("echo \"\n\" >> Test_Record_File");
    }

    FileManager.SetFilePath("Test_Record_File");

    FileManager.FileOpen(Rf);

    while(!FileManager.Control_End_of_File()){

          string_line = FileManager.ReadLine();

          char * c_string_pointer = nullptr;

          Convert_String_To_Int(string_line,&c_string_pointer);

          if(c_string_pointer[0] != '\n'){

             sum = sum + Translater.TranslateFromCharToInt(c_string_pointer);
          }

          delete [] c_string_pointer;

          std::cout << "\n sum:" << sum;
    }

    FileManager.FileClose();

    std::cout << "\n the average:" << sum/repitation;

    return 0;
}
void Convert_String_To_Int(std::string string_line, char ** cstring_pointer){

    int string_length = string_line.length();

    *cstring_pointer = new char [2*string_length];

    for(int i=0;i<string_length;i++){

        (*cstring_pointer)[i] = string_line[i];
    }

    (*cstring_pointer)[string_length] = '\0';
}
