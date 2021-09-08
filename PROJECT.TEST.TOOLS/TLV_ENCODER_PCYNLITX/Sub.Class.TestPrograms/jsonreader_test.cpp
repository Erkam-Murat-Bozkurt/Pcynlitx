
#include <iostream>
#include "jsonreader.h"
#include "string_reader.h"

int main(int argc, char** argv){

    if(argc < 2){

       std::cout << "\n usage: ./jsonreader <data_file_path>";
    }

    jsonreader jsrd;

    jsrd.collect_json_data(argv[1]);

    jsrd.print_dictionary();

    return 0;
}
