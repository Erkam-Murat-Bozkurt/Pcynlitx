


#include "string_reader.h"

string_reader::string_reader(){

  this->memory_clear_status = true;

  this->string_pointer = nullptr;

  this->thread_data_lenghts = nullptr;

  this->thread_number = 0;

  this->thread_data = nullptr;

}

string_reader::string_reader(const string_reader & orig){


}

string_reader::~string_reader(){

    if(!this->memory_clear_status){

       this->memory_clear_status = true;

       for(int i=0;i<2*this->data_length;i++){

           delete [] this->string_pointer[i];
       }

       delete [] this->string_pointer;

       for(int i=0;i<2*this->thread_number;i++){

           int data_length = this->thread_data_lenghts[i];

           for(int k=0;k<2*data_length;k++){

               delete [] this->thread_data[i][k];
           }

           delete [] this->thread_data[i];
       }

       delete [] this->thread_data;

       delete [] this->thread_data_lenghts;

    }
}

void string_reader::read_string_data(char * data_file_path){

     this->receive_data_file_path(data_file_path);

     this->determine_data_file_length();

     this->initialize_string_memory();

     this->place_string_data();

     this->determine_thread_data_length();

     this->initialize_thread_containers();

     this->place_thread_data();
}

void string_reader::receive_data_file_path(char * data_file_path)
{
     bool exist = this->FileManager.Is_Path_Exist(data_file_path);

     if(!exist){

         std::cout << "\n The data file does not exist";

         exit(EXIT_FAILURE);
     }

     this->FileManager.SetFilePath(data_file_path);
}

void string_reader::determine_data_file_length()
{
     this->data_length = 0;

     this->FileManager.FileOpen(Rf);

     do{

        this->FileManager.ReadLine();

        if(!this->FileManager.Control_End_of_File()){

            this->data_length++;
        }

     }while(!this->FileManager.Control_End_of_File());

     this->FileManager.FileClose();
}

void string_reader::initialize_string_memory(){

     this->memory_clear_status = false;

     this->string_pointer = new char * [2*this->data_length];

     for(int i=0;i<2*this->data_length;i++){

         this->string_pointer[i] = nullptr;
     }
}

void string_reader::print_string_data(){

     for(int i=0;i<this->data_length;i++){

         std::cout << "\n this->string_pointer["

                   << i << "]" << this->string_pointer[i] << std::endl;
     }

     std::cout << "\n" << std::endl;
}

void string_reader::receive_thread_number(int number){

     this->thread_number = number;
}

void string_reader::place_string_data(){

     this->FileManager.FileOpen(Rf);

     for(int i=0;i<this->data_length;i++){

        char * line_pointer = this->FileManager.ReadLine_as_Cstring();

        size_t string_size = strlen(line_pointer);

        this->string_pointer[i] = new char [2*string_size];

        for(size_t k=0;k<string_size;k++){

           this->string_pointer[i][k] = line_pointer[k];
        }

        this->string_pointer[i][string_size] = '\0';
     }

     this->FileManager.FileClose();
}

char * string_reader::getFileLine(int line_number){

       return this->string_pointer[line_number];
}

int string_reader::getDataFileLength(){

    return this->data_length;;
}

void string_reader::determine_thread_data_length(){

     int quotient = this->data_length / this->thread_number ;

     int remainder = this->data_length - (quotient * ( this->thread_number ) );

     this->thread_data_lenghts = new int [2*this->thread_number];

     for(int i=0;i<2*this->thread_number;i++){

        this->thread_data_lenghts[i] = 0;
     }

     for(int i=0;i<this->thread_number;i++){

         this->thread_data_lenghts[i] = quotient;
     }

     int last_thread_length = quotient + remainder;

     this->thread_data_lenghts[this->thread_number] = last_thread_length;
}

void string_reader::initialize_thread_containers(){

     this->thread_data = new char ** [2*this->thread_number];

     for(int i=0;i<2*this->thread_number;i++){

         int data_length = this->thread_data_lenghts[i];

         this->thread_data[i] = new char * [2*data_length];

         for(int k=0;k<2*data_length;k++){

             this->thread_data[i][k] = nullptr;
         }
     }
}

void string_reader::place_thread_data(){

     int thread_number = 0, index_number = 0;

     for(int i=0;i<this->data_length;i++){

         if(index_number < this->thread_data_lenghts[thread_number]){

            size_t string_size = strlen(this->string_pointer[i]);

            this->thread_data[thread_number][index_number] = new char [2*string_size];

            for(size_t k =0;k<string_size;k++){

                this->thread_data[thread_number][index_number][k] = this->string_pointer[i][k];
            }

            this->thread_data[thread_number][index_number][string_size] = '\0';

            this->thread_data[thread_number][index_number];

            index_number++;
         }
         else{
                thread_number++;

                index_number = 0;

                i--;
         }
     }
}

char ** string_reader::getThreadData(int thread_number){

       return this->thread_data[thread_number];
}


int string_reader::get_thread_data_length(int thread_number){

    return this->thread_data_lenghts[thread_number];
}
