
#include "Data_Reader.h"

Data_Reader::Data_Reader(){

     this->File_Lenght = 0;

     this->data_list = nullptr;

     this->Memory_Delete_Condition = true;

     this->Record_point_index = 0;

     this->Index_Writing_Condition = false;

     this->Line_index = 0;

     this->Record_Memory_02 = nullptr;

     this->Record_Memory_13 = nullptr;
}

Data_Reader::~Data_Reader(){

      if(!this->Memory_Delete_Condition){

          this->Clear_Dynamic_Memory();
      }
}

void Data_Reader::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         for(int i=0;i<this->File_Lenght;i++){

             delete [] this->data_list[i];
         }

         delete [] this->data_list;

         if(this->Record_Memory_02 != nullptr){

             delete [] this->Record_Memory_02;
         }

         if(this->Record_Memory_13 != nullptr){

             delete [] this->Record_Memory_13;
         }
     }
}

void Data_Reader::SetFilePath(std::string FilePATH){

     this->FileManager.SetFilePath(FilePATH);
}

void Data_Reader::SetFilePath(char * FilePATH){

     this->FileManager.SetFilePath(FilePATH);
}

void Data_Reader::SetFilePath(const char * FilePATH){

     this->FileManager.SetFilePath(FilePATH);
}

void Data_Reader::Receive_Data(){

     this->Determine_File_Length();

     this->Allocate_Memory_For_Each_Line();

     this->FileManager.FileOpen(Rf);

     for(int i=0;i<this->File_Lenght;i++){

         std::string string_line = this->FileManager.ReadLine();

         this->Set_Data(string_line,&this->data_list[i]);
     }

     this->FileManager.FileClose();
}

void Data_Reader::Determine_File_Length(){

     this->FileManager.FileOpen(Rf);

     while(!this->FileManager.Control_End_of_File()){

           std::string string_line = this->FileManager.ReadLine();

           this->File_Lenght++;
     }

     this->FileManager.FileClose();
}

void Data_Reader::Allocate_Memory_For_Each_Line(){

     this->FileManager.FileOpen(Rf);

     this->Memory_Delete_Condition = false;

     this->data_list = new char * [5*this->File_Lenght];

     for(int i=0;i<this->File_Lenght;i++){

         std::string string_line = this->FileManager.ReadLine();

         int string_size = string_line.length();

         this->data_list[i] = new char [2*string_size];
     }

     this->FileManager.FileClose();

     this->Record_Memory_02 = new int [5*this->File_Lenght];

     for(int i=0;i<2*this->File_Lenght;i++){

         this->Record_Memory_02[i] = 0;
     }

     this->Record_Memory_13 = new int [5*this->File_Lenght];

     for(int i=0;i<2*this->File_Lenght;i++){

         this->Record_Memory_13[i] = 0;
     }
}

void Data_Reader::Print_Data(){

     for(int i=0;i<this->File_Lenght;i++){

         int string_size = strlen(this->data_list[i]);

         for(int k=0;k<string_size;k++){

             std::cout << this->data_list[i][k];
         }
     }
}

void Data_Reader::Set_Data(std::string string_line, char ** pointer){

     int string_size = string_line.length();

     int index_counter = 0;

     for(int i=0;i<string_size;i++){

         (*pointer)[index_counter] = string_line[i];

         index_counter++;
     }

     (*pointer)[index_counter] = '\n';
}

void Data_Reader::Increase_Line_Index(){

     this->Line_index++;
}

void Data_Reader::Set_Ready_For_Writing_Condition(bool condition){

      this->Index_Writing_Condition = condition;
}

bool Data_Reader::Get_Ready_For_Writing_Condition(){

     return this->Index_Writing_Condition;
}

char ** Data_Reader::Get_Data_Pointer(){

        return this->data_list;
}

int Data_Reader::Get_Data_length(){

    return this->File_Lenght;
}

int Data_Reader::Get_Line_Index(){

    return this->Line_index;
}

int * Data_Reader::Get_Record_Point_Pointer_02(){

    return this->Record_Memory_02;
}


int * Data_Reader::Get_Record_Point_Pointer_13(){

    return this->Record_Memory_13;
}
