
#include "Data_Reader.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include <cstring>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <string>
#include <sstream>
#include "Cpp_FileOperations.h"
#include "IntToCharTranslater.h"

#define LOOP_BREAK_CONDITION (Line_index >= Reader->Get_Data_length())

#define INDEX_INCREMENT_STATUS (Reader->Get_Data_List_Member_Record_Status(index))

void Counter_Function(Data_Reader * Reader,int thread_number);

int thread_wait_number = 0;

int exit_thread_number = 0;

int entered_thread_number = 0;


int total_reputation = 0;

int num_threads = 0;

int Elapsed_Time = 0;

int Line_index = 0;

std::mutex mtx_serial;
std::mutex mtx_parallel;


std::condition_variable cv;

char search_word [] = "100.00";

int main(int argc, char ** argv){

    if(argc < 3){

       std::cout << "\n\n usage: " << argv[0] << " <thread number> <input file>";

       std::cout << "\n\n";

       exit(0);
    }

    IntToCharTranslater Translater;

    num_threads = Translater.TranslateFromCharToInt(argv[1]);

    if((num_threads%2)!=0){

       std::cout << "\n\n The number of the threads must be selected as multiple of two..";

       std::cout << "\n\n";
    }

    Data_Reader Reader;

    Reader.SetFilePath(argv[2]);

    Reader.Receive_Data();

    struct rusage usage;

    struct timeval start, end;

    int return_value = getrusage(RUSAGE_SELF,&usage);

    if(return_value!= 0){

       std::cout << "\n The usage data can not be obtain..\n";

       return 0;
    }

    start = usage.ru_utime;

    std::thread threads[num_threads];

    for(int i=0;i<num_threads;i++){

        threads[i] = std::thread(Counter_Function,&Reader,i);
    }


    for(int i=0;i<num_threads;i++){

        threads[i].join();
    }


    int number = 0;

    for(int i=0;i<Reader.Get_Record_List_Length();i++){

        if(Reader.Get_Record_Number(i) <= 1){

           number = number + Reader.Get_Reputation(i);
        }
    }

    std::cout << "\n\n number:" << number << std::endl;

    std::cout << "\n\n total_reputation:" << total_reputation << std::endl;

    for(int i=0;i<Reader.Get_Data_length();i++){

        if(Reader.Get_Record_Number(i) > 1){

           std::cout << "\n There is overrite ..";
        }
    }

    return_value = getrusage(RUSAGE_SELF, &usage);

    if(return_value!= 0){

       std::cout << "\n The usage data can not be obtain..\n";

       return 0;
    }

    end = usage.ru_utime;

    Elapsed_Time = end.tv_sec - start.tv_sec;

    std::cout << "\n\n Elapsed_Time:" << Elapsed_Time;

    std::cout << "\n\n";

    Cpp_FileOperations FileManager;

    FileManager.SetFilePath("Test_Record_File");

    FileManager.FileOpen(Af);

    FileManager.WriteToFile(Translater.Translate(Elapsed_Time));

    FileManager.WriteToFile("\n");

    FileManager.FileClose();

    return 0;
}

void Counter_Function(Data_Reader * Reader,int thread_number){

     std::unique_lock<std::mutex> serial_lck(mtx_serial);

     serial_lck.unlock();


     std::unique_lock<std::mutex> parallel_lck(mtx_parallel);

     parallel_lck.unlock();



     // START OF THE ENTRANCE BARRIER

     serial_lck.lock();

     entered_thread_number++;

     if(entered_thread_number < num_threads ){

        cv.wait(serial_lck);

        serial_lck.unlock();
     }
     else{

          serial_lck.unlock();
     }

     cv.notify_one();


     // THE END OF THE ENTRANCE BARRIER

     int index = 0;

     do {
             // STARTING OF THE PARALLEL EXECUTION REGION

             StringOperator StringManager;

             parallel_lck.lock();

             index = Line_index;

             Line_index++;

             parallel_lck.unlock();


             parallel_lck.lock();

             while(Reader->Get_Data_List_Member_Record_Status(index)){

                   Line_index++;

                   index = Line_index;
             }

             parallel_lck.unlock();

             // THE END OF THE PARALLEL EXECUTION



             serial_lck.lock();

             thread_wait_number++;

             if(thread_wait_number < (num_threads - exit_thread_number)){  // SERIAL EXECUTION BARRIER

                cv.wait(serial_lck);

                serial_lck.unlock();


                serial_lck.lock();

                thread_wait_number--;

                serial_lck.unlock();

             }
             else{

                   serial_lck.unlock();


                   // START OF THE SERIAL EXECUTION  ------------------------------------------------

                   // The critical section

                   serial_lck.lock();

                   char * string_line = Reader->Get_Data_List_Member_String(index);

                   int reputation = StringManager.Get_Word_Number_on_String(string_line,search_word);

                   total_reputation = total_reputation + reputation;

                   serial_lck.unlock();


                   serial_lck.lock();

                   if((!Reader->Get_Data_List_Member_Record_Status(index))){

                        Reader->Set_Record_Data(index,thread_number,reputation);
                   };

                   serial_lck.unlock();


                   // THE END OF SERIAL EXECUTION -------------------------------------------------



                   cv.notify_one();   // Notifies all threads waiting


                   serial_lck.lock();

                   cv.wait(serial_lck);

                   serial_lck.unlock();


                   serial_lck.lock();

                   thread_wait_number--;

                   serial_lck.unlock();
             }


     }while(!LOOP_BREAK_CONDITION);


     parallel_lck.lock();

     exit_thread_number++;

     parallel_lck.unlock();


     do {

          if(exit_thread_number<num_threads){

             cv.notify_all();

          }

     } while(exit_thread_number<num_threads);
}
