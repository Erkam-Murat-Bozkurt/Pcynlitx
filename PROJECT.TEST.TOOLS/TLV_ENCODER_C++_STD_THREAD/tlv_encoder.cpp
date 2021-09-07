

/*

   The instances of this class perform data encoding based on type length value format.

   It receives the data in the form of character array ( a kind of data represented

   as dictionary ).

*/

#include "tlv_encoder.h"

tlv_encoder::tlv_encoder(){

     this->data_length = 0;

     // Type value dectrations

     this->string_type = "00000000";
     this->int_type    = "00000001";
     this->bool_type   = "00000010";

     this->binary_stream = "";
     this->string_stream = "";

     this->encoded_data  = ""; // the string type holds json line data

     this->data_stream   = ""; // The output of the data encoding

     this->dictionary = nullptr;
     this->dynamic_memory_clear_status = true;
}

tlv_encoder::tlv_encoder(const tlv_encoder & orig){

}

tlv_encoder::~tlv_encoder(){

}

void tlv_encoder::receive_data_length(int length){

     this->data_length = length;
}

void tlv_encoder::receive_dictionary_data(char *** data){

     this->dictionary = data;
}

void tlv_encoder::Clear_Dynamic_Memory(){


}

std::string tlv_encoder::construct_data_stream(){

     for(int i=0;i<this->data_length;i++){

         std::string line_data = "";

         for(int k=0;k<3;k++){

             line_data = line_data + this->data_encoder(this->dictionary[i][k],k);
         }

         this->data_stream = this->data_stream + line_data;
     }

     return this->data_stream;
}

std::string tlv_encoder::data_encoder(char * data, int data_tp){

     std::string type = "" ;

     if(data_tp == 0){  // The first element of the dictionary

        type  = this->string_type;
     }

     if(data_tp == 1){  // The second element of the dictionary

        type = this->int_type;
     }

     if(data_tp == 2){  // The thirth element of the dictionary

        type  = this->bool_type;
     }

     std::string value  = this->convert_string_to_binary_form(data);

     char * length = this->Translater.Translate(value.length());

     std::string length_binary_form = this->convert_string_to_binary_form(length);

     this->encoded_data  = type + length_binary_form + value;

     return this->encoded_data; // This data holds binary form of the json line data
}


std::string tlv_encoder::convert_binary_to_string(std::string s){

     // This member function can be considered as a data converter.

     // It converts the string data that is represented in the form of

     // eight bit binary ( one byte binary data which is holded as string)

     // to the standart  std::string

     size_t length = s.length();

     for(size_t t=0;t<length;t=t+8){

         std::string temp = "";

         for(size_t k=t;k<t+8;k++){

             temp = temp + s[k];
         }

          std::bitset<8> bit(temp);

          unsigned long ch = bit.to_ulong();

          char c = ch;

          this->string_stream.append(1,c) ;
     }

     this->string_stream.append(1,'\0');

     return this->string_stream;
}

std::string tlv_encoder::convert_string_to_binary_form(char * string){

     // This member function can be considered as a binary encoder

     // It converts the c string data to eigth bit binary data

     // ( one byte binary data which is holded as string)

     this->binary_stream = "";

     size_t string_size = strlen(string);

     for(size_t i=0; i<string_size; i++){

         std::bitset<8> bit(string[i]);

         std::string temp = bit.to_string();

         this->binary_stream = this->binary_stream + temp;
     }

     return this->binary_stream;
}
