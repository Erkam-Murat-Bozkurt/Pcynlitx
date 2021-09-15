
#include <iostream>
#include "string_reader.h"


int main(int argc, char** argv){

    string_reader reader;

    char data_file_path [] = "json_data.json";

    reader.receive_thread_number(4);

    reader.read_string_data(data_file_path);

    reader.print_string_data();

    std::cout << "\n Printing file index line by line";

    std::cout << "\n";

    for(int i=0;i<reader.getDataFileLength();i++){

       std::cout << "\n File line " << i << ":"

                 << reader.getFileLine(i) << std::endl;
    }

    for(int i=0;i<4;i++){

        std::cout << "\n Thread data " << i << ":" << std::endl;

        std::cout << "\n";

        for(int k=0;k<reader.get_thread_data_length(i);k++){

           std::cout << reader.getThreadData(i)[k] << std::endl;
        }

        std::cout << "\n\n\n";
    }

    std::cout << "\n\n the end of program..\n\n";

    return 0;
}
