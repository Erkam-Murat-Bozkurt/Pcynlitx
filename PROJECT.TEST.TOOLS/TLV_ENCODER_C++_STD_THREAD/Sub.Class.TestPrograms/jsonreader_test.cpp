
#include <iostream>
#include "jsonreader.h"
#include "string_reader.h"
#include "IntToCharTranslater.h"

int main(int argc, char** argv){

    if(argc < 3){

       std::cout << "\n usage: ./jsonreader <thread number> <data_file_path>" << std::endl;

       std::cout << std::endl;

       exit(0);
    }

    IntToCharTranslater Translater;

    int num_threads = Translater.TranslateFromCharToInt(argv[1]);

    if((num_threads%2)!=0){

        std::cout << "\n\n The number of the threads must be selected as multiple of two..";

        std::cout << "\n\n";

        exit(0);
    }

    jsonreader jsrd;

    jsrd.receive_thread_number(num_threads);

    jsrd.collect_json_data(argv[2]);


    for(int k=0;k<num_threads;k++){

        std::cout << "\n Dictionary data for thread[" << k << "]:" << std::endl;

        int record_number = jsrd.get_thread_data_length(k);

        for(int i=0;i<record_number;i++){

            std::cout << " {";

            for(int j=0;j<3;j++){

                std::cout << " " << j+1 << ": " << jsrd.getThreadDictionary(k)[i][j];

                if(j<2){

                   std::cout << ", ";
                }
                else{

                      std::cout << " };";
                }
            }

            std::cout << std::endl;
         }
     }

    //jsrd.print_dictionary();

    return 0;
}
