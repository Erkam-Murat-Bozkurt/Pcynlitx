
/*

   The instances of this class extract json data from a data file

   including json data.

*/

#include "data_extracter.h"

data_extracter::data_extracter(){

  this->string_data = nullptr;

  this->int_data = nullptr;

  this->bool_data = nullptr;

  this->key_value = nullptr;


  this->key_value_memory_clear_status = true;

  this->string_memory_clear_status = true;

  this->integer_memory_clear_status = true;

  this->bool_memory_clear_status = true;

  this->dynamic_memory_clear_status = true;



  this->this_key_value_is_a_string = false;

  this->this_key_value_is_a_bolean = false;

  this->key_vale_reference_position = 0;
}

data_extracter::data_extracter(const data_extracter & orig){

}

data_extracter::~data_extracter(){

    this->Clear_Dynamic_Memory();
}

void data_extracter::Clear_Dynamic_Memory(){

     if(!this->dynamic_memory_clear_status){

         this->dynamic_memory_clear_status = true;

         this->Clear_String_Memory();

         this->Clear_Integer_Memory();

         this->Clear_Bool_Memory();

         this->Clear_Key_Value_Memory();
     }
}

void data_extracter::Clear_String_Memory(){

     if(!this->string_memory_clear_status){

       if(this->string_data != nullptr){

          delete [] this->string_data;
       }

       this->string_memory_clear_status = true;
     }
}

void data_extracter::Clear_Integer_Memory(){

     if(!this->integer_memory_clear_status){

       if(this->int_data != nullptr){

          delete [] this->int_data;
       }

       this->integer_memory_clear_status = true;
     }
}

void data_extracter::Clear_Bool_Memory(){

     if(!this->bool_memory_clear_status){

       if(this->bool_data != nullptr){

          delete [] this->bool_data;
       }

       this->bool_memory_clear_status = true;
     }
}

void data_extracter::Clear_Key_Value_Memory(){

     if(!this->key_value_memory_clear_status){

        if(this->key_value != nullptr){

           delete [] this->key_value;
        }

        this->key_value_memory_clear_status = true;
     }
}

void data_extracter::extract_json_line_data(char * string_data){

     this->dynamic_memory_clear_status = false;

     this->key_vale_reference_position = 0;

     this->receive_string_data(string_data);

     this->extract_string_data();

     this->extract_integer_data();

     this->extract_bolean_data();
}

void data_extracter::extract_string_data(){

     char * key_value = nullptr;

     bool string_exist = false;

     for(int i=0;i<3;i++){

         key_value = this->get_next_key_value(this->string_pointer);

         if(this->is_this_key_value_a_string(key_value)){

            string_exist = true;

            break;
         }
     }

     if(!string_exist){

        std::cout << "\n this record does not include string variable";

        std::cout << "\n corrupted data";

        exit(EXIT_FAILURE);
     }

     // Memory allocation for the key value.

     size_t string_size = strlen(key_value);

     this->Clear_String_Memory();

     this->string_memory_clear_status = false;

     this->string_data = new char [2*string_size];


     // The placement of the characters between the first quotes and the second qoutes

     int index_counter = 0;

     for(size_t i=0;i<string_size;i++){

         if(key_value[i] != '\"'){

            this->string_data[index_counter] = key_value[i];

            index_counter++;
         }
     }

     this->string_data[index_counter] = '\0';
}

void data_extracter::extract_integer_data(){

     char * key_value = nullptr;

     bool integer_exist = false;

     for(int i=0;i<3;i++){

         key_value = this->get_next_key_value(this->string_pointer);

         if(this->include_integer_character(key_value)){

            integer_exist = true;

            break;
         }
     }

     if(!integer_exist){

         std::cout << "\n this record does not include integer variable";

         std::cout << "\n corrupted data";

         exit(EXIT_FAILURE);
     }


     size_t string_size = strlen(key_value);

     int start_point = 0;

     // The spaces must be eliminated before assignment


     while (!this->is_a_valid_character(key_value[start_point]))
     {
         start_point++;
     }


     this->Clear_Integer_Memory();


     this->integer_memory_clear_status = false;

     this->int_data = new char [5*string_size];

     int index_counter = 0;

     for(int i=start_point;i<string_size;i++){

         this->int_data[index_counter] = key_value[i];

         index_counter++;
     }

     this->int_data[index_counter] = '\0';
}

void data_extracter::extract_bolean_data(){

     char * key_value = nullptr;

     // Checking the existance of bolean data

     // and finding the key_value including bolean data

     bool bolean_exist = false;

     for(int i=0;i<3;i++){

         key_value = this->get_next_key_value(this->string_pointer);

         if(this->is_this_key_value_a_bolean(key_value)){

            bolean_exist = true;

            break;
          }
     }

     if(!bolean_exist){

         std::cout << "\n this record does not include integer variable";

         std::cout << "\n corrupted data";

        exit(EXIT_FAILURE);
     }


     this->Clear_Bool_Memory();

     // placement of bolean data into dynamic memory

     this->bool_memory_clear_status = false;

     size_t string_size = strlen(key_value);

     this->bool_data = new char [5*string_size];

     int index_counter = 0;

     for(size_t i=0;i<string_size;i++){

         this->bool_data[index_counter] = key_value[i];

         index_counter++;
     }

     this->bool_data[index_counter] = '\0';
}


void data_extracter::receive_string_data(char * string_line){

     this->string_pointer = string_line;
}

bool data_extracter::is_a_valid_character(char c){

     this->is_this_a_valid_character = true;

     if(c == ' '){

        this->is_this_a_valid_character = false;
     }

     if(c == '\b'){

        this->is_this_a_valid_character = false;
     }

     if(c == '\t'){

        this->is_this_a_valid_character = false;
     }

     return this->is_this_a_valid_character;
}

bool data_extracter::include_integer_character(char * key_value){

     this->is_this_key_value_an_integer = false;

     size_t key_value_size = strlen(key_value);

     for(int i=0;i<key_value_size;i++){

         if((key_value[i] == '0') || (key_value[i] == '1')

             || (key_value[i] == '2') || (key_value[i] == '3')

             || (key_value[i] == '4') || (key_value[i] == '5')

             || (key_value[i] == '6') || (key_value[i] == '7')

             || (key_value[i] == '8') || (key_value[i] == '9')

          ){

            this->is_this_key_value_an_integer = true;
          }
     }

     return this->is_this_key_value_an_integer;
}

bool data_extracter::is_this_key_value_a_string(char * key_value){

     this->this_key_value_is_a_string = false;

     int character_repitation = this->CharProcessor.DetermineCharacterRepitation(this->string_pointer,'\"');

     if(character_repitation > 0){

        this->this_key_value_is_a_string = true;
     }

     return this->this_key_value_is_a_string;
}

bool data_extracter::is_this_key_value_a_bolean(char * key_value){

     this->this_key_value_is_a_bolean = false;

     char true_word [] = "true";

     char false_word [] = "false";

     int bolean_word_counter = 0;

     int true_word_counter = this->StringOpr.Get_Word_Number_on_String(key_value,true_word);

     int false_word_counter = this->StringOpr.Get_Word_Number_on_String(key_value,false_word);

     bolean_word_counter = true_word_counter + false_word_counter;

     if(bolean_word_counter > 0){

        this->this_key_value_is_a_bolean = true;
     }

     return this->this_key_value_is_a_bolean;
}

char * data_extracter::get_next_key_value(char * data){

       // Clearing previously allocated dynamic memory

       this->Clear_Key_Value_Memory();

       this->key_value_memory_clear_status = false;


       // Find the next character ":" position

       int ref_point = this->key_vale_reference_position;

       ref_point  = this->CharProcessor.FindNextCharacterPositon(data,ref_point+1,':');

       this->key_vale_reference_position = ref_point; // Next reference point


       // Find the key value character size

       size_t string_size = strlen(data);

       int character_size = 0;

       for(size_t i=ref_point;i<string_size;i++){

           if(((this->string_pointer[i] == ',') || (this->string_pointer[i] == '}'))){

              break;
           }
           else{

               character_size++;
           }
       }


       // Replacing the key value into dynamic memory

       this->key_value = new char [5*character_size];

       for(int i=0;i<5*character_size;i++){

           this->key_value[i] = '\0';
       }

       int index_counter = 0;

       for(int i=ref_point+1;i<ref_point+character_size;i++){

           this->key_value[index_counter] = data[i];

           index_counter++;
       }

       this->key_value[index_counter] = '\0';

       return this->key_value; // Return new key value
}

char * data_extracter::getExtractedString(){

       return this->string_data;
}

char * data_extracter::getExtractedInteger(){

       return this->int_data;
}

char * data_extracter::getExtractedBolean(){

       return this->bool_data;
}
