
#include "Data_Recorder.h"

Data_Recorder::Data_Recorder(){

     this->Memory_Delete_Condition = true;

     this->Record_Data_Pointer = nullptr;

     this->Thread_Data_Pointer = nullptr;

     this->Record_Data_Size = 0;

     this->Thread_Data_Size = 0;

     this->Record_Index = 0;
}

Data_Recorder::~Data_Recorder(){

      if(!this->Memory_Delete_Condition){

          this->Clear_Dynamic_Memory();
      }
}

void Data_Recorder::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         for(int i=0;i<this->Record_Data_Size;i++){

             delete this->Record_Data_Pointer[i];
         }

         delete [] this->Record_Data_Pointer;

         if(this->Thread_Data_Pointer != nullptr){

             delete [] this->Thread_Data_Pointer;
         }
     }
}

void Data_Recorder::Receive_Data_Size(int size){

     this->Allocate_Memory_For_Each_Line(size);
}

void Data_Recorder::Allocate_Memory_For_Each_Line(int Size){

     this->Record_Data_Size = Size;

     this->Memory_Delete_Condition = false;

     this->Record_Data_Pointer = new Record_Data * [5*this->Record_Data_Size];

     for(int i=0;i<this->Record_Data_Size;i++){

         this->Record_Data_Pointer[i] = new Record_Data;

         this->Record_Data_Pointer[i]->string_line = "";

         this->Record_Data_Pointer[i]->position = i;

         this->Record_Data_Pointer[i]->record_status = false;
     }

     this->Thread_Data_Pointer = new Thread_Record_Data [5*this->Record_Data_Size];

     for(int i=0;i<this->Record_Data_Size;i++){

         this->Thread_Data_Pointer[i].record_number = 0;

         this->Thread_Data_Pointer[i].thread_number = 0;
     }
}

void Data_Recorder::Set_Record_Data(std::string string_line, int i){

     this->Record_Data_Pointer[i]->string_line = string_line;

     this->Record_Data_Pointer[i]->position = i;

     this->Record_Data_Pointer[i]->record_status = true;

     //this->Record_Index++;
}

void Data_Recorder::Set_Thread_Record_Data(int index, int thread_number){

     this->Thread_Data_Pointer[index].thread_number = thread_number;

     this->Thread_Data_Pointer[index].record_number++;

     this->Record_Data_Pointer[index]->record_status = true;

     this->Thread_Data_Size++;
}

std::string Data_Recorder::Get_String_Data(int index) const {

     return this->Record_Data_Pointer[index]->string_line;
}

int Data_Recorder::Get_Data_Position(int index){

    return this->Record_Data_Pointer[index]->position;
}

bool Data_Recorder::Get_Data_Record_Status(int index){

     return this->Record_Data_Pointer[index]->record_status;
}

int Data_Recorder::Get_Record_Data_Size() const {

    return this->Record_Data_Size;
}

void Data_Recorder::Set_Thread_Data_Size(int size){

     this->Thread_Data_Size = size;
}

int Data_Recorder::Get_Thread_Record_Data_Size() {

    return this->Thread_Data_Size;
}

int Data_Recorder::Get_Recorded_Thread_Number(int index) const {

    return this->Thread_Data_Pointer[index].thread_number;
}

int Data_Recorder::Get_Record_Number(int index) const {

    return this->Thread_Data_Pointer[index].record_number;
}
