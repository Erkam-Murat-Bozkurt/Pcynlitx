
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

     this->second_group_order_violation = false;

     this->first_group_order_violation = false;

     this->first_group_list_increment = 0;

     this->second_group_list_increment = 0;

     this->first_group_list  = nullptr;

     this->second_group_list = nullptr;
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

         delete this->first_group_list;

         delete this->second_group_list;

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

     this->Initialize_Acess_Order_Holders();
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

first_group_order_data * Data_Reader::Get_First_Group_Acess_Order() const
{
      return this->first_group_list;
}

second_gorup_order_data * Data_Reader::Get_Second_Group_Acess_Order() const
{
      return this->second_group_list;
}

void Data_Reader::Initialize_Acess_Order_Holders(){

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

void Data_Reader::Set_First_Group_Acess_Order(int thread_number)
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

void Data_Reader::Set_Second_Group_Acess_Order(int thread_number)
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


void Data_Reader::Print_First_Group_Acess_Order()
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

void Data_Reader::Print_Second_Group_Acess_Order()
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

bool Data_Reader::Check_First_Group_Order_Violation()
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

bool Data_Reader::Check_Second_Group_Order_Violation()
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
