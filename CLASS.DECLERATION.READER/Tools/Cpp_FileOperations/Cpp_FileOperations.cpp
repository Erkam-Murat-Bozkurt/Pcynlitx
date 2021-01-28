
/*

Copyright ©  2019,  Erkam Murat Bozkurt

This file is part of the research project which is carried by Erkam Murat Bozkurt.

This is a free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation
either version 3 of the License, or any later version.

This software is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.

*/

#include "Cpp_FileOperations.h"

Cpp_FileOperations::Cpp_FileOperations(){

   // Constructor Function

     this->CString = nullptr;

     this->CString_FilePATH = nullptr;

     this->Memory_Delete_Condition = false;

     this->is_path_exist = false;
};

Cpp_FileOperations::Cpp_FileOperations(const Cpp_FileOperations & orig){

   // Copy Constructor
};

Cpp_FileOperations::~Cpp_FileOperations(){

    // Destructor Function

     if(!this->Memory_Delete_Condition){

        this->Clear_Dynamic_Memory();
     }
};

void Cpp_FileOperations::Clear_Dynamic_Memory(){

      if(!this->Memory_Delete_Condition){

          this->Memory_Delete_Condition = true;

          if(this->CString != nullptr){

             delete [] this->CString;

             this->CString = nullptr;
          }

          if(this->CString_FilePATH != nullptr){

             delete [] this->CString_FilePATH;

             this->CString_FilePATH = nullptr;
          }
      }
}

void Cpp_FileOperations::SetFilePath(std::string FilePATH){

     this->isFilePathReceive = true;

     this->FilePath = "";

     size_t Name_Size = FilePATH.length();

     for(int i=0;i<Name_Size;i++){

         this->FilePath.append(1,FilePATH[i]) ;
     }

     this->FilePath.append(1,'\0');


     size_t string_size = this->FilePath.length();

     if(this->CString_FilePATH != nullptr){

        delete [] this->CString_FilePATH;

        this->CString_FilePATH = nullptr;
     }

     int index_counter = 0;

     this->Memory_Delete_Condition = false;

     this->CString_FilePATH = new char [5*string_size];

     for(int i=0;i<string_size;i++){

         this->CString_FilePATH[index_counter] = this->FilePath[i];

         index_counter++;
     }

     this->CString_FilePATH[index_counter] = '\0';
}

void Cpp_FileOperations::SetFilePath(const char * String){

     this->isFilePathReceive = true;

     this->FilePath = "";

     size_t String_Size = strlen(String);

     for(int i=0;i<String_Size;i++){

         this->FilePath.append(1,String[i]);
     }

     size_t string_size = this->FilePath.length();

     if(this->CString_FilePATH != nullptr){

        delete [] this->CString_FilePATH;

        this->CString_FilePATH = nullptr;
     }

     int index_counter = 0;

     this->Memory_Delete_Condition = false;

     this->CString_FilePATH = new char [5*string_size];

     for(int i=0;i<string_size;i++){

         this->CString_FilePATH[index_counter] = this->FilePath[i];

         index_counter++;
     }

     this->CString_FilePATH[index_counter] = '\0';
}

void Cpp_FileOperations::SetFilePath(char * String){

     this->isFilePathReceive = true;

     this->FilePath = "";

     size_t String_Size = strlen(String);

     for(int i=0;i<String_Size;i++){

         this->FilePath.append(1,String[i]);
     }

     int string_size = this->FilePath.length();

     if(this->CString_FilePATH != nullptr){

        delete [] this->CString_FilePATH;

        this->CString_FilePATH = nullptr;
     }

     int index_counter = 0;

     this->Memory_Delete_Condition = false;

     this->CString_FilePATH = new char [5*string_size];

     for(int i=0;i<string_size;i++){

         this->CString_FilePATH[index_counter] = this->FilePath[i];

         index_counter++;
     }

     this->CString_FilePATH[index_counter] = '\0';
}

void Cpp_FileOperations::FileOpen(char Open_Mode){

     if(Open_Mode == 'r'){

        this->DataFile.open(this->FilePath,std::ios::in);
     }

     if(Open_Mode == 'w'){

        this->DataFile.open(this->FilePath,std::ios::out);
     }

     if(Open_Mode == 'x'){

        this->DataFile.open(this->FilePath,std::ios::in | std::ios::out);
     }

     if(Open_Mode == 'b'){

        this->DataFile.open(this->FilePath,std::ios::out | std::ios::trunc);
     }

     if(Open_Mode == 'a'){

        this->DataFile.open(this->FilePath,std::ios::out | std::ios::app);
     }

     if(!this->DataFile.is_open()){

        std::cout << "\n The file" << this->FilePath << " can not be opened ..";
     }
}


bool Cpp_FileOperations::Is_Path_Exist(char * path){

     this->is_path_exist = true;

     struct stat buf;

     int result = 0;

     result = stat( path, &buf );

     if( result != 0 ){

       this->is_path_exist = false;
     }

     return this->is_path_exist;
}

void Cpp_FileOperations::Delete_File(char * path){

      int return_value = unlink(path);

      if(return_value != 0){

         std::cout << "\n\n ERROR in Cpp_FileOperations::Delete_File:";

         std::cout << "\n\n the file in path:" << path << " can not be removed ";

         exit(0);
      }
}

void Cpp_FileOperations::FileClose(){

     this->DataFile.close();
}

void Cpp_FileOperations::WriteToFile(std::string string_list){

     this->DataFile <<  string_list;
}

void Cpp_FileOperations::WriteToFile(const char * string_list){

     std::string transfer_string;

     size_t String_Size = strlen(string_list);

     for(int i=0;i<String_Size;i++){

         transfer_string.append(1,string_list[i]);
     }

     this->DataFile << transfer_string;
}


void Cpp_FileOperations::WriteToFile(char * string_list){

     std::string transfer_string;

     size_t String_Size = strlen(string_list);

     for(int i=0;i<String_Size;i++){

         transfer_string.append(1,string_list[i]);
     }

     this->DataFile << transfer_string;
}

std::string Cpp_FileOperations::ReadLine(){

     this->String_Line = "";

     std::getline(this->DataFile,this->String_Line);

     this->String_Line = this->String_Line + '\0';

     return this->String_Line;
}

std::string Cpp_FileOperations::Read(){

     this->DataFile >> this->string_word;

     return this->string_word;
}

bool Cpp_FileOperations::Control_End_of_File(){

     this->End_Of_File_Condition = false;

     this->End_Of_File_Condition = this->DataFile.eof();

     return this->End_Of_File_Condition;
}

char * Cpp_FileOperations::Convert_Std_String_To_Char(std::string string_line){

       if(this->CString != nullptr){

          delete [] this->CString;

          this->CString = nullptr;
       }

       size_t string_size = string_line.length();

       this->Memory_Delete_Condition = false;

       this->CString = new char [5*string_size];

       for(int i=0;i<string_size;i++){

           this->CString[i] = string_line[i];
       }

       this->CString[string_size] = '\0';

       return this->CString;
}


void Cpp_FileOperations::Copy_File(char * Base_Location, char * Target_Location){

     int read_fd = 0;

     int write_fd = 0;

     struct stat stat_buf;

     stat_buf.st_mode = S_IFREG;

     off_t offset = 0;

     /* Open the input file. */

     read_fd = open(Base_Location,O_RDONLY,stat_buf.st_mode);

     int stat_return = fstat (read_fd, &stat_buf);

     /* Open the output file for writing, with the same permissions as the source file. */

     write_fd = open(Target_Location, O_WRONLY | O_CREAT,stat_buf.st_mode);

     /* Blast the bytes from one file to the other. */

     sendfile(write_fd,read_fd,&offset,stat_buf.st_size);

     /* Close up. */

     close (read_fd);

     close (write_fd);
}

char * Cpp_FileOperations::ReadLine_as_Cstring(){;

       this->ReadLine();

       return this->Convert_Std_String_To_Char(this->String_Line);
}

void Cpp_FileOperations::Move_File(char * File_Path, char * New_File_Path){

     this->Copy_File(File_Path,New_File_Path);

     this->Delete_File(File_Path);
}


char * Cpp_FileOperations::GetFilePath()
{
       return this->CString_FilePATH;
}
