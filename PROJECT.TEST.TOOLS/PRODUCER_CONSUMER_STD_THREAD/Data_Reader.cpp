
#include "Data_Reader.h"

Data_Reader::Data_Reader(){

     this->File_Lenght = 0;

     this->Read_Data_Pointer = nullptr;

     this->Thread_Data_Pointer = nullptr;

     this->Memory_Delete_Condition = true;

     this->Line_index = 0;

     this->Thread_Data_Size = 0;
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

             delete this->Read_Data_Pointer[i];
         }

         delete [] this->Read_Data_Pointer;

         if(this->Thread_Data_Pointer != nullptr){

             delete [] this->Thread_Data_Pointer;
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

         this->Set_Data(string_line,i);
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

     this->Read_Data_Pointer = new Read_Data * [5*this->File_Lenght];

     for(int i=0;i<this->File_Lenght;i++){

         this->Read_Data_Pointer[i] = new Read_Data;

         this->Read_Data_Pointer[i]->number_string = "";

         this->Read_Data_Pointer[i]->position = i;

         this->Read_Data_Pointer[i]->read_status = false;

         this->Read_Data_Pointer[i]->record_status = false;
     }

     this->FileManager.FileClose();

     this->Thread_Data_Pointer = new Thread_Data [5*this->File_Lenght];

     for(int i=0;i<2*this->File_Lenght;i++){

         this->Thread_Data_Pointer[i].record_number = 0;

         this->Thread_Data_Pointer[i].thread_number = 0;
     }
}


void Data_Reader::Set_Data(std::string string_line, int i){

     this->Read_Data_Pointer[i]->number_string = string_line;
}

void Data_Reader::Increase_String_Line_Index(){

     this->Line_index++;
}

void Data_Reader::Set_String_Line_Index(int index){

     this->Line_index = index;
}

std::string Data_Reader::Get_String_Data(int index) const {

        return this->Read_Data_Pointer[index]->number_string;
}

int Data_Reader::Get_Data_Position(int index){

    return this->Read_Data_Pointer[index]->position;
}

bool Data_Reader::Get_Data_Read_Status(int index){

     return this->Read_Data_Pointer[index]->read_status;
}

bool Data_Reader::Get_Data_Record_Status(int index){

     return this->Read_Data_Pointer[index]->record_status;
}

void Data_Reader::Set_Data_Read_Status(int index, bool status){

     this->Read_Data_Pointer[index]->read_status = status;
}

void Data_Reader::Set_Thread_Data_Record_Status(int index, bool status){

     this->Read_Data_Pointer[index]->record_status = status;
}

int Data_Reader::Get_Data_Size() const {

    return this->File_Lenght;
}

int Data_Reader::Get_String_Line_Index() const {

    return this->Line_index;
}

void Data_Reader::Set_Thread_Record_Data(int index, int thread_number){

     this->Thread_Data_Pointer[index].thread_number = thread_number;

     this->Thread_Data_Pointer[index].record_number++;

     this->Set_Thread_Data_Record_Status(index,true);

     this->Increase_Thread_Data_Size();
}


void Data_Reader::Increase_Thread_Data_Size(){

     this->Thread_Data_Size++;
}

void Data_Reader::Set_Thread_Data_Size(int size){

     this->Thread_Data_Size = size;
}

int Data_Reader::Get_Record_Data_Size() {

    return this->Thread_Data_Size;
}

int  Data_Reader::Get_Thread_Number(int index) const {

     return this->Thread_Data_Pointer[index].thread_number;
}

int  Data_Reader::Get_Record_Number(int index) const {

     return this->Thread_Data_Pointer[index].record_number;
}
