


#include <iostream>
#include <string>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>
#include <sstream>
#include <cstring>
#include "tlv_encoder.h"
#include "jsonreader.h"
#include "string_reader.h"

std::string output_data_stream = "";


int Elapsed_Time_for_user = 0;

int Elapsed_Time_for_sys = 0;

int Elapsed_Time_for_total = 0;

int num_threads = 0;

int stream_index = 0;

std::mutex mtx_barrier;
std::mutex mtx;

std::condition_variable cv_transfer;
std::condition_variable cv_br;

int thread_number_in_serial_region = 0;


int entered_thread_number_in_barrier = 0;

bool stream_ready = true;

tlv_encoder * encoder;

jsonreader * reader;

void data_encoder(int thread_number);

int main(int argc, char** argv){

    if(argc < 3){

       std::cout << "\n\n usage: " << argv[0] << " <thread number> <data file path>";

       std::cout << "\n\n";

       exit(0);
    }

    IntToCharTranslater Translater;

    num_threads = Translater.TranslateFromCharToInt(argv[1]);

    if((num_threads%2)!=0){

        std::cout << "\n\n The number of the threads must be selected as multiple of two..";

        std::cout << "\n\n";
    }


    encoder = new tlv_encoder [2*num_threads];

    reader  = new jsonreader;

    reader->receive_thread_number(num_threads);

    reader->collect_json_data(argv[2]);


    // THE CONSTRUCTION OF ARTIFICIAL WORKLOAD


    std::thread threads[num_threads];

    struct rusage usage;

    struct timeval start_us, end_us, start_sys, end_sys;

    int return_value = getrusage(RUSAGE_SELF,&usage);

    if(return_value!= 0){

       std::cout << "\n The usage data can not be obtain..\n";

       return 0;
    }

    start_us = usage.ru_utime;

    start_sys = usage.ru_stime;

    for(int i=0;i<num_threads;i++){

        threads[i] = std::thread(data_encoder,i);
    }

    for(int i=0;i<num_threads;i++){

        threads[i].join();
    }

    return_value = getrusage(RUSAGE_SELF, &usage);

    if(return_value!= 0){

       std::cout << "\n The usage data can not be obtain..\n";

       return 0;
    }

    end_us = usage.ru_utime;

    end_sys = usage.ru_stime;

    Elapsed_Time_for_user = end_us.tv_sec - start_us.tv_sec;

    Elapsed_Time_for_sys = end_sys.tv_sec - start_sys.tv_sec;


    Elapsed_Time_for_total = Elapsed_Time_for_user + Elapsed_Time_for_sys;

    std::cout << Elapsed_Time_for_total << std::endl;

    delete [] encoder;

    delete reader;

    return 0;
}

void data_encoder(int thread_number){

     std::unique_lock<std::mutex> transfer_lck(mtx);

     transfer_lck.unlock();


     encoder[thread_number].receive_data_length(reader->get_thread_data_length(thread_number));

     encoder[thread_number].receive_dictionary_data(reader->getThreadDictionary(thread_number));

     std::string thread_data_stream = encoder[thread_number].construct_data_stream();

     // THE END OF THE PARALLEL EXECUTION



     transfer_lck.lock();

     output_data_stream = output_data_stream + thread_data_stream ;

     transfer_lck.unlock();
}
