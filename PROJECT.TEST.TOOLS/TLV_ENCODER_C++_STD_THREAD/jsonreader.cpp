

#include "jsonreader.h"

jsonreader::jsonreader(){

     this->dynamic_memory_clear_status = true;

     this->data_length = 0;

     this->dictionary_pointer = nullptr;

     this->total_thread_number = 0;
}

jsonreader::jsonreader(const jsonreader & orig){

}

jsonreader::~jsonreader(){

    if(!this->dynamic_memory_clear_status){

        this->Clear_Dynamic_Memory();
    }
}

void jsonreader::Clear_Dynamic_Memory(){

     if(!this->dynamic_memory_clear_status){

        this->dynamic_memory_clear_status = true;

        for(int k=0;k<this->total_thread_number;k++){

            int record_number = this->data_reader.get_thread_data_length(k);

            for(int i=0;i<2*record_number;i++){

               for(int j=0;j<5;j++){

                   delete [] this->dictionary_pointer[k].dictionary[i][j];
               }

               delete [] this->dictionary_pointer[k].dictionary[i];
            }

            delete [] this->dictionary_pointer[k].dictionary;
        }

        delete [] this->dictionary_pointer;
     }
}

void jsonreader::receive_thread_number(int number){

     this->total_thread_number = number;
}

void jsonreader::collect_json_data(char * data_file_path)
{
     bool exist = this->FileManager.Is_Path_Exist(data_file_path);

     if(!exist){

         std::cout << "\n The data file does not exist";

         exit(EXIT_FAILURE);
     }

     this->data_reader.receive_thread_number(this->total_thread_number);

     this->data_reader.read_string_data(data_file_path);

     this->initialize_data_memory();

     int data_length = this->data_reader.getDataFileLength();

     this->data_length = data_length;

     for(int k=0;k<this->total_thread_number;k++){

         int record_number = this->data_reader.get_thread_data_length(k);

         for(int i=0;i<record_number;i++){

             char * line_data = this->data_reader.getThreadData(k)[i];

             this->json_extracter.extract_json_line_data(line_data);

             char * string_data = this->json_extracter.getExtractedString();

             char * int_data    = this->json_extracter.getExtractedInteger();

             char * bool_data   = this->json_extracter.getExtractedBolean();

             this->transfer_string(&(this->dictionary_pointer[k].dictionary[i][0]),string_data);

             this->transfer_string(&(this->dictionary_pointer[k].dictionary[i][1]),int_data);

             this->transfer_string(&(this->dictionary_pointer[k].dictionary[i][2]),bool_data);
         }
     }
}

void jsonreader::initialize_data_memory(){

     this->dynamic_memory_clear_status = false;

     this->dictionary_pointer = new Dictionary_Data [2*this->total_thread_number];

     for(int k=0;k<this->total_thread_number;k++){

         int record_number = this->data_reader.get_thread_data_length(k);

         this->dictionary_pointer[k].dictionary = new char ** [2*record_number];

         for(int i=0;i<2*record_number;i++){

             this->dictionary_pointer[k].dictionary[i] = new char * [5];

             for(int j=0;j<5;j++){

                this->dictionary_pointer[k].dictionary[i][j] = nullptr;
             }
         }
     }
}

void jsonreader::print_dictionary(){

     for(int k=0;k<this->total_thread_number;k++){

         int record_number = this->data_reader.get_thread_data_length(k);

         for(int i=0;i<2*record_number;i++){

             std::cout << " {";

             for(int j=0;j<3;j++){

                 std::cout << " " << j+1 << ": " << this->dictionary_pointer[k].dictionary[i][j];

                 if(j<2){

                    std::cout << ", ";
                 }
                 else{

                       std::cout << " };";
                 }
             }
          }
      }
}

void jsonreader::transfer_string(char ** target, char * source){

     size_t string_size = strlen(source);

     *target = new char [5*string_size];

     for(size_t i=0;i<string_size;i++){

         (*target)[i] = source[i];
     }

     (*target)[string_size] = '\0';
}

char *** jsonreader::getThreadDictionary(int thread_number){

    return this->dictionary_pointer[thread_number].dictionary;
}

int jsonreader::get_thread_data_length(int thread_number){

    return this->data_reader.get_thread_data_length(thread_number);
}

int jsonreader::getDataLength(){

    return this->data_length;
}
