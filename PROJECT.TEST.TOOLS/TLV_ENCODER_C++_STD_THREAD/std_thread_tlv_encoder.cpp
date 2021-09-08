




/*
    This software has been tested agains memory leaks

    with valgrind.

    There is a json data file on the directory "Test.Binaries" and it is named as "json_data.json"

    This data file can be used in tests. In addition, the memory check can be made with the

    command given in below.

    valgrind --leak-check=full ./tvl_encoder_test ~/NXLog.Project/Test.Binaries/json_data.json

*/

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

double lower_bound = 0;

double upper_bound = 10;

std::default_random_engine re;

std::uniform_real_distribution<double> unif(lower_bound,upper_bound);

int work_load_data_size = 0;


int Elapsed_Time = 0;

int num_threads = 0;

int stream_index = 0;

std::mutex mtx_barrier;
std::mutex mtx;

std::condition_variable cv_transfer;
std::condition_variable cv_br;


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

    reader = new jsonreader [2*num_threads];

    // THE CONSTRUCTION OF ARTIFICIAL WORKLOAD


    std::thread threads[num_threads];

    struct rusage usage;

    struct timeval start, end;

    for(int i=0;i<num_threads;i++){

        reader[i].collect_json_data(argv[2]);
    }


    int return_value = getrusage(RUSAGE_SELF,&usage);

    if(return_value!= 0){

       std::cout << "\n The usage data can not be obtain..\n";

       return 0;
    }

    start = usage.ru_utime;


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

    end = usage.ru_utime;

    Elapsed_Time = end.tv_sec - start.tv_sec;

    std::cout << Elapsed_Time << std::endl;

    return 0;
}

void data_encoder(int thread_number){

     std::unique_lock<std::mutex> barrier_lck(mtx_barrier);

     barrier_lck.unlock();

     std::unique_lock<std::mutex> transfer_lck(mtx);

     transfer_lck.unlock();


     // START OF THE ENTRANCE BARRIER

     barrier_lck.lock();

     entered_thread_number_in_barrier++;

     if(entered_thread_number_in_barrier < num_threads ){

        cv_br.wait(barrier_lck);

        barrier_lck.unlock();
     }
     else{

          barrier_lck.unlock();
     }

     barrier_lck.lock();

     entered_thread_number_in_barrier--;

     barrier_lck.unlock();


     barrier_lck.lock();

     if(entered_thread_number_in_barrier > 0){

        cv_br.notify_all();
     }

     barrier_lck.unlock();

     // THE END OF THE ENTRANCE BARRIER


     // STARTING OF THE PARALLEL EXECUTION REGION

    encoder[thread_number].receive_data_length(reader[thread_number].getDataLength());

    encoder[thread_number].receive_dictionary_data(reader[thread_number].getDictionary());

    // THE END OF THE PARALLEL EXECUTION


    do{

       transfer_lck.lock();

       if(stream_ready){

          stream_ready = false;

          stream_index++;

          output_data_stream = output_data_stream + encoder[thread_number].construct_data_stream();

          stream_ready = true;

          cv_br.notify_all();

          transfer_lck.unlock();
       }
       else{
             cv_transfer.wait(transfer_lck);


             transfer_lck.unlock();
       }

    }while(stream_index<num_threads);
}
