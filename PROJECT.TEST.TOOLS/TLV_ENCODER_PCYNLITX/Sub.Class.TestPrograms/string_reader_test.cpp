
#include <iostream>
#include "string_reader.h"


int main(int argc, char** argv){

    string_reader reader;

    char data_file_path [] = "json_data.json";

    reader.read_string_data(data_file_path);

    reader.print_string_data();

    std::cout << "\n Printing file index line by line";

    std::cout << "\n";

    for(int i=0;i<reader.getDataFileLength();i++){

       std::cout << "\n File line " << i << ":" << reader.getFileLine(i) << std::endl;
    }

    std::cout << "\n\n the end of program..\n\n";

    return 0;
}
