
#include "Data_Receiver.h"

Data_Receiver::Data_Receiver(){

     this->File_Lenght = 0;

     this->data_list = nullptr;

     this->target_memory = nullptr;

     this->Buffer_1 =nullptr;

     this->Buffer_2 =nullptr;

     this->Memory_Delete_Condition = true;

     this->Buffer_1_Empty_Condition = true;

     this->Buffer_2_Empty_Condition = true;

     this->Target_Memory_Index_1 = 0;

     this->Target_Memory_Index_2 = 0;

     this->second_group_order_violation = false;

     this->first_group_order_violation = false;

     this->first_group_list_increment = 0;

     this->second_group_list_increment = 0;

     this->first_group_list  = nullptr;

     this->second_group_list = nullptr;
}

Data_Receiver::~Data_Receiver(){

      if(!this->Memory_Delete_Condition){

          this->Clear_Dynamic_Memory();
      }
}

void Data_Receiver::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         for(int i=0;i<this->File_Lenght;i++){

             delete [] this->data_list[i];

             delete [] this->target_memory[i];
         }

         delete [] this->data_list;

         delete [] this->target_memory;

         delete this->first_group_list;

         delete this->second_group_list;

         if(this->Buffer_1 != nullptr){

            delete [] this->Buffer_1;
         }

         if(this->Buffer_2 != nullptr){

            delete [] this->Buffer_2;
         }
     }
}

void Data_Receiver::SetFilePath(std::string FilePATH){

     this->FileManager.SetFilePath(FilePATH);
}

void Data_Receiver::SetFilePath(char * FilePATH){

     this->FileManager.SetFilePath(FilePATH);
}

void Data_Receiver::SetFilePath(const char * FilePATH){

     this->FileManager.SetFilePath(FilePATH);
}

void Data_Receiver::Receive_Data(){

     this->Determine_File_Length();

     this->Allocate_Memory_For_Each_Line();

     this->FileManager.FileOpen(Rf);

     for(int i=0;i<this->File_Lenght;i++){

         std::string string_line = this->FileManager.ReadLine();

         this->Set_Data(string_line,&this->data_list[i]);
     }

     this->FileManager.FileClose();
}

void Data_Receiver::Determine_File_Length(){

     this->FileManager.FileOpen(Rf);

     while(!this->FileManager.Control_End_of_File()){

           std::string string_line = this->FileManager.ReadLine();

           this->File_Lenght++;
     }

     this->FileManager.FileClose();
}

void Data_Receiver::Allocate_Memory_For_Each_Line(){

     this->FileManager.FileOpen(Rf);

     this->Memory_Delete_Condition = false;

     this->data_list = new char * [2*this->File_Lenght];

     this->target_memory = new char * [2*this->File_Lenght];

     for(int i=0;i<this->File_Lenght;i++){

         std::string string_line = this->FileManager.ReadLine();

         int string_size = string_line.length();

         this->data_list[i] = new char [2*string_size];

         this->target_memory[i] = new char [2*string_size];
     }

     this->FileManager.FileClose();

     this->Initialize_Acess_Order_Holders();
}

void Data_Receiver::Initialize_Acess_Order_Holders(){

     this->first_group_list  = new first_group_order_data [2*this->File_Lenght];

     this->second_group_list = new second_gorup_order_data [2*this->File_Lenght];

     for(int i=0;i<this->File_Lenght;i++){

         this->first_group_list[i].first_group_data_holder[0] = 5;

         this->first_group_list[i].first_group_data_holder[1] = 5;

         this->first_group_list[i].empty_status[0] = true;

         this->first_group_list[i].empty_status[1] = true;


         this->second_group_list[i].second_group_data_holder[0] = 5;

         this->second_group_list[i].second_group_data_holder[1] = 5;

         this->second_group_list[i].empty_status[0] = true;

         this->second_group_list[i].empty_status[1] = true;
     }
}

void Data_Receiver::Print_Data(){

     for(int i=0;i<this->File_Lenght;i++){

         int string_size = strlen(this->data_list[i]);

         for(int k=0;k<string_size;k++){

             std::cout << this->data_list[i][k];
         }
     }
}

void Data_Receiver::Set_Data(std::string string_line, char ** pointer){

     int string_size = string_line.length();

     int index_counter = 0;

     for(int i=0;i<string_size;i++){

         (*pointer)[index_counter] = string_line[i];

         index_counter++;
     }

     (*pointer)[index_counter] = '\n';
}

void Data_Receiver::SetBuffer_1(char * string){

     int string_size = strlen(string);

     if(this->Buffer_1 != nullptr){

        delete [] this->Buffer_1;
     }

     this->Buffer_1 = new char [5*string_size];

     int index_counter = 0;

     for(int i=0;i<string_size;i++){

        this->Buffer_1[index_counter] = string[i];

        index_counter++;
     }

     this->Buffer_1[index_counter] = '\0';

     this->Buffer_1_Empty_Condition = false;
}

void Data_Receiver::SetBuffer_2(char * string){

     int string_size = strlen(string);

     if(this->Buffer_2 != nullptr){

        delete [] this->Buffer_2;
     }

     this->Buffer_2 = new char [5*string_size];

     int index_counter = 0;

     for(int i=0;i<string_size;i++){

        this->Buffer_2[index_counter] = string[i];

        index_counter++;
     }

     this->Buffer_2[index_counter] = '\0';

     this->Buffer_2_Empty_Condition = false;
}

void Data_Receiver::SetTargetMemory(char * string, int index){

     int string_size = strlen(string);

     int index_counter = 0;

     for(int i=0;i<string_size;i++){

         this->Get_Target_Memory_Pointer()[index][index_counter] = string[i];
     }

     this->Get_Target_Memory_Pointer()[index][index_counter] = '\0';
}

void Data_Receiver::SetBuffer_1_Empty_Condition(bool condition){

     this->Buffer_1_Empty_Condition = condition;
}

void Data_Receiver::SetBuffer_2_Empty_Condition(bool condition){

     this->Buffer_2_Empty_Condition = condition;
}

char ** Data_Receiver::Get_Data_Pointer(){

        return this->data_list;
}

char ** Data_Receiver::Get_Target_Memory_Pointer(){

        return this->target_memory;
}

char * Data_Receiver::Get_Buffer_1_Pointer(){

       return this->Buffer_1;
}

char * Data_Receiver::Get_Buffer_2_Pointer(){

       return this->Buffer_2;
}

int Data_Receiver::Get_Data_length(){

    return this->File_Lenght;
}

bool Data_Receiver::Get_Buffer_1_Empty_Condition(){

     return this->Buffer_1_Empty_Condition;
}

bool Data_Receiver::Get_Buffer_2_Empty_Condition(){

     return this->Buffer_2_Empty_Condition;
}

void Data_Receiver::SetTargetMemoryIndex_1(int index){

     this->Target_Memory_Index_1 = index;
}

void Data_Receiver::SetTargetMemoryIndex_2(int index){

     this->Target_Memory_Index_2 = index;
}

int Data_Receiver::Get_Target_Memory_Index_1(){

    return this->Target_Memory_Index_1;
}

int Data_Receiver::Get_Target_Memory_Index_2(){

     return this->Target_Memory_Index_2;
}

first_group_order_data * Data_Receiver::Get_First_Group_Acess_Order() const
{
      return this->first_group_list;
}

second_gorup_order_data * Data_Receiver::Get_Second_Group_Acess_Order() const
{
      return this->second_group_list;
}

void Data_Receiver::Set_First_Group_Acess_Order(int thread_number)
{
     if(this->first_group_list[this->first_group_list_increment].empty_status[0]){

        this->first_group_list[this->first_group_list_increment].first_group_data_holder[0] = thread_number;

        this->first_group_list[this->first_group_list_increment].empty_status[0] = false;
     }
     else{

             this->first_group_list[this->first_group_list_increment].first_group_data_holder[1] = thread_number;

             this->first_group_list[this->first_group_list_increment].empty_status[1] = false;

             this->first_group_list_increment++;
     }
}

void Data_Receiver::Set_Second_Group_Acess_Order(int thread_number)
{
     if(this->second_group_list[this->second_group_list_increment].empty_status[0]){

        this->second_group_list[this->second_group_list_increment].second_group_data_holder[0] = thread_number;

        this->second_group_list[this->second_group_list_increment].empty_status[0] = false;
     }
     else{

           this->second_group_list[this->second_group_list_increment].second_group_data_holder[1] = thread_number;

           this->second_group_list[this->second_group_list_increment].empty_status[1] = false;

           this->second_group_list_increment++;
     }
}


void Data_Receiver::Print_First_Group_Acess_Order()
{
     this->FileManager.SetFilePath("The_First_Group_Acess_Orders");

     this->FileManager.FileOpen(RWCf);

     for(int i=0;i<this->File_Lenght;i++){

         if(!(this->first_group_list[i].empty_status[0])){

             int sequence_0 = this->first_group_list[i].first_group_data_holder[0];

             char * value_0 = this->Translater.Translate(sequence_0);

             this->FileManager.WriteToFile("\n ");

             this->FileManager.WriteToFile(value_0);

             this->FileManager.WriteToFile(" ");
         }

         if(!(this->first_group_list[i].empty_status[1])){

             int sequence_1 = this->first_group_list[i].first_group_data_holder[1];

             char * value_1 = this->Translater.Translate(sequence_1);

             this->FileManager.WriteToFile("\n ");

             this->FileManager.WriteToFile(value_1);

             this->FileManager.WriteToFile(" ");
         }
     }

    this->FileManager.FileClose( );
}

void Data_Receiver::Print_Second_Group_Acess_Order()
{
     this->FileManager.SetFilePath("The_Second_Group_Acess_Orders");

     this->FileManager.FileOpen(RWCf);

     for(int i=0;i<this->File_Lenght;i++){

         if(!(this->second_group_list[i].empty_status[0])){

              int sequence_0 = this->second_group_list[i].second_group_data_holder[0];

              char * value_0 = this->Translater.Translate(sequence_0);

              this->FileManager.WriteToFile("\n ");

              this->FileManager.WriteToFile(value_0);

              this->FileManager.WriteToFile(" ");
         }

         if(!(this->second_group_list[i].empty_status[1])){

             int sequence_1 = this->second_group_list[i].second_group_data_holder[1];

             char * value_1 = this->Translater.Translate(sequence_1);

             this->FileManager.WriteToFile("\n ");

             this->FileManager.WriteToFile(value_1);

             this->FileManager.WriteToFile(" ");
         }
     }

     this->FileManager.FileClose( );
}

// The member function that check access order of the first group..

bool Data_Receiver::Check_First_Group_Order_Violation()
{
     this->first_group_order_violation = false;

     for(int i=0;i<this->File_Lenght;i++){

        if(!(this->first_group_list[i].empty_status[0])){

            int sequence_0 = this->first_group_list[i].first_group_data_holder[0];

            if(sequence_0 != 0){

               this->first_group_order_violation = true;

               return this->first_group_order_violation;
            }
        }
     }

     return this->first_group_order_violation;
}

// The member function that check access order of the second group..

bool Data_Receiver::Check_Second_Group_Order_Violation()
{
     this->second_group_order_violation = false;

     for(int i=0;i<this->File_Lenght;i++){

         if(!(this->second_group_list[i].empty_status[0])){

             int sequence_0 = this->second_group_list[i].second_group_data_holder[0];

             if(sequence_0 != 1){

                this->second_group_order_violation = true;

                return this->second_group_order_violation;
             }
         }
      }

      return this->second_group_order_violation;
}
