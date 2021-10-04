




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
#include <vector>


int ** data = nullptr;

void Construct_Random_Data(int *** pointer, int data_size);

void Convert_char_to_std_string(std::string * string_line, char * cstring_pointer);

void Clear_Data_Memory(int *** pointer, int data_size);


int data_size = 0;

int lower_bound = 0;

int counter = 0;

int thread_counter = 0;

int upper_bound = 100000;

std::uniform_int_distribution<int> unif(lower_bound,upper_bound);

std::default_random_engine re;

int Elapsed_Time_for_user = 0;

int Elapsed_Time_for_sys = 0;

int Elapsed_Time_for_total = 0;

int num_threads = 0;

std::mutex mtx;

std::condition_variable cv;

bool buffer_ready = true;

std::vector<int> v(0,0);

void select_prime_numbers(int rank);

int main(int argc, char** argv){

    if(argc < 3){

       std::cout << "\n\n usage: " << argv[0] << " <thread number> <data size>";

       std::cout << "\n\n";

       exit(0);
    }

    IntToCharTranslater Translater;

    num_threads = Translater.TranslateFromCharToInt(argv[1]);

    if((num_threads%2)!=0){

        std::cout << "\n\n The number of the threads must be selected as multiple of two..";

        std::cout << "\n\n";

        exit(0);
    }


    // THE CONSTRUCTION OF ARTIFICIAL WORKLOAD

    std::string dataLength = "";

    Convert_char_to_std_string(&dataLength,argv[2]);

    std::stringstream sd(dataLength);

    sd >> data_size;

    Construct_Random_Data(&data,data_size);

    // --------------------------------------------


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

        threads[i] = std::thread(select_prime_numbers,i);
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

    Clear_Data_Memory(&data,data_size);

    return 0;
}

void select_prime_numbers(int rank){

     std::unique_lock<std::mutex> lck(mtx);

     lck.unlock();


     long long local_data_size = data_size / num_threads;

     long long local_start = local_data_size * (long) rank;

     long long local_end = local_start + local_data_size;

     for(int i=local_start;i<local_end;i++){

         for(int j=0;j<data_size;j++){

             bool is_prime = true;

             if(data[i][j]==0 || data[i][j]==1){

                is_prime = false;
             }
             else{

                  for(int k=2;k<data[i][j];k++){

                      if(data[i][j]%k ==0){

                         is_prime = false;

                         break;
                      }
                  }
             }

             if(is_prime){

                bool record_complated = false;

                do {

                     lck.lock();

                     if(buffer_ready){

                        buffer_ready = false;

                        lck.unlock();


                        v.push_back(data[i][j]);


                        lck.lock();

                        buffer_ready = true;

                        record_complated = true;

                        counter++;

                        lck.unlock();


                        cv.notify_all();

                      }
                      else{

                            lck.unlock();


                            lck.lock();

                            cv.wait(lck);

                            lck.unlock();
                      }

                }while(!record_complated);
           }
        }
     }
 }

 void Construct_Random_Data(int *** pointer, int data_size){

      *pointer = new int * [5*data_size];

      for(int i=0;i<data_size;i++){

          (*pointer)[i] = new int [5*data_size];

          for(int k=0;k<data_size;k++){

             (*pointer)[i][k] = unif(re);
          }
      }
 }

 void Convert_char_to_std_string(std::string * string_line, char * cstring_pointer){

     int string_length = strlen(cstring_pointer);

     for(int i=0;i<string_length;i++){

         *string_line = *string_line + cstring_pointer[i];
     }
 }

 void Clear_Data_Memory(int *** pointer, int data_size){

      for(int i=0;i<data_size;i++){

          delete [] (*pointer)[i];
      }

      delete [] (*pointer);
 }
