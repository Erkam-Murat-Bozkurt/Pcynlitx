


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

int row_counter = 0;

int column_counter = 0;

int thread_counter = 0;

int upper_bound = 100000;

std::uniform_int_distribution<int> unif(lower_bound,upper_bound);

std::default_random_engine re;

int Elapsed_Time_for_user = 0;

int Elapsed_Time_for_sys = 0;

int Elapsed_Time_for_total = 0;

int thread_number_in_end = 0;

int num_threads = 16;

std::mutex mtx;

std::condition_variable cv;

bool buffer_ready = true;

std::vector<int> v(0,0);

#define SEARCH_CONDITION  (column_counter < data_size) || (row_counter < data_size)

void select_prime_numbers(int rank);

int main(int argc, char** argv){

    if(argc < 2){

       std::cout << "\n\n usage: " << argv[0] << " <data size>";

       std::cout << "\n\n";

       exit(0);
    }


    // THE CONSTRUCTION OF ARTIFICIAL WORKLOAD

    std::string dataLength = "";

    Convert_char_to_std_string(&dataLength,argv[1]);

    std::stringstream sd(dataLength);

    sd >> data_size;

    Construct_Random_Data(&data,data_size);

    // --------------------------------------------


    struct rusage usage;

    struct timeval start_us, end_us, start_sys, end_sys;

    int return_value = getrusage(RUSAGE_SELF,&usage);

    if(return_value!= 0){

       std::cout << "\n The usage data can not be obtain..\n";

       return 0;
    }

    start_us = usage.ru_utime;

    start_sys = usage.ru_stime;


    pcynlitx::Thread_Server Server;

    for(int i=0;i<num_threads;i++){

        Server.Activate(i,select_prime_numbers);
    }

    for(int i=0;i<num_threads;i++){

        Server.Join(i);
    };

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

void select_prime_numbers(pcynlitx::thds * thread_data){

     pcynlitx::TM_Client Manager(thread_data,"select_prime_numbers");

     Manager.lock();

     int thread_number = Manager.Get_Thread_Number();

     Manager.unlock();


     long long local_data_size = data_size / num_threads;

     long long local_start = local_data_size * (long) thread_number;

     long long local_end = local_start + local_data_size;

     for(int i=local_start;i<local_end;i++){

         Manager.lock();

         row_counter++;

         Manager.unlock();


         for(int j=0;j<data_size;j++){

             Manager.lock();

             column_counter++;

             Manager.unlock();


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

                Manager.start_serial(0,num_threads,thread_number);

                v.push_back(data[i][j]);

                Manager.end_serial(0,num_threads,thread_number);
            }
         }
     }


     Manager.lock();

     thread_number_in_end++;

     Manager.unlock();


     do {

          if(!SEARCH_CONDITION){

             for(int i=0;i<num_threads;i++){

                 if(i!=thread_number){

                    Manager.rescue(i);
                 }
             }
          }

          Manager.yield();

     } while(thread_number_in_end < num_threads);


     Manager.Exit();
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
