
#include "Data_Reader.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <chrono>

#define TH0_BLOCK_CONDITION (th0_read_counter - th2_record_counter) >= 1
#define TH1_BLOCK_CONDITION (th1_read_counter - th3_record_counter) >= 1
#define TH2_BLOCK_CONDITION (th0_read_counter - th2_record_counter) < 1
#define TH3_BLOCK_CONDITION (th1_read_counter - th3_record_counter) < 1
#define LOOP_BREAK_CONDITION (Reader->Get_Line_Index() == Reader->Get_Data_length())

void Function(Data_Reader * Reader,int thread_number);

std::thread thread_1;

std::thread thread_2;

std::thread thread_3;

std::thread thread_4;

int thread_wait_at_start = 0;

int Elapsed_Time = 0;

std::mutex mtx_rd;
std::mutex mtx_wr_02;
std::mutex mtx_wr_13;


std::condition_variable cv_rd;
std::condition_variable cv_wr_02;
std::condition_variable cv_wr_13;


StringOperator StringManager_TH02;

StringOperator StringManager_TH13;

int th0_read_counter = 0;

int th1_read_counter = 0;

int th2_record_counter = 0;

int th3_record_counter = 0;

int record_index_02 = 0;

int record_index_13 = 0;


int th0_number_reputation = 0;

int th1_number_reputation = 0;

int th02_wait_number = 0;

int th13_wait_number = 0;

char search_word [] = "100.00";

int main(int argc, char ** argv){

    struct rusage usage;

    struct timeval start, end;

    int return_value = getrusage(RUSAGE_SELF,&usage);

    if(return_value!= 0){

       std::cout << "\n The usage data can not be obtain..\n";

       return 0;
    }

    start = usage.ru_utime;

    Data_Reader Reader;

    Reader.SetFilePath(argv[1]);

    Reader.Receive_Data();

    thread_1 = std::thread(Function,&Reader,0);

    thread_2 = std::thread(Function,&Reader,1);

    thread_3 = std::thread(Function,&Reader,2);

    thread_4 = std::thread(Function,&Reader,3);

    thread_1.join();

    thread_2.join();

    thread_3.join();

    thread_4.join();

    int number = 0;

    for(int i=0;i<Reader.Get_Data_length();i++){

        number = number + Reader.Get_Record_Point_Pointer_02()[i];
    }

    for(int i=0;i<Reader.Get_Data_length();i++){

        number = number + Reader.Get_Record_Point_Pointer_13()[i];
    }

    return_value = getrusage(RUSAGE_SELF, &usage);

    if(return_value!= 0){

       std::cout << "\n The usage data can not be obtain..\n";

       return 0;
    }

    end = usage.ru_utime;

    Elapsed_Time = end.tv_sec - start.tv_sec;

    std::cout << Elapsed_Time;

    return 0;
}

void Function(Data_Reader * Reader,int thread_number){

     std::unique_lock<std::mutex> rd_lck(mtx_rd);

     rd_lck.unlock();

     std::unique_lock<std::mutex> wr_02_lck(mtx_wr_02);

     wr_02_lck.unlock();

     std::unique_lock<std::mutex> wr_13_lck(mtx_wr_13);

     wr_13_lck.unlock();

     do {

         if(thread_number == 0){

            wr_02_lck.lock();

            if(TH0_BLOCK_CONDITION){

                if(LOOP_BREAK_CONDITION){

                   break;
                }

                th0_read_counter = 1;

                if(th02_wait_number >=1){

                    cv_wr_02.notify_one();
                }

                th02_wait_number++;

                cv_wr_02.wait(wr_02_lck);

                wr_02_lck.unlock();


                wr_02_lck.lock();

                th02_wait_number--;

                wr_02_lck.unlock();
            }
            else{

                  wr_02_lck.unlock();
            }

            if(!LOOP_BREAK_CONDITION){

               int index = Reader->Get_Line_Index();

               char * string_line = Reader->Get_Data_Pointer()[index];

               th0_number_reputation = StringManager_TH02.Get_Word_Number_on_String(string_line,search_word);

               wr_02_lck.lock();

               th0_read_counter++;      // Increaing the number determines whetner the line is read or not

               wr_02_lck.unlock();


               rd_lck.lock();

               Reader->Increase_Line_Index();

               rd_lck.unlock();
            }
            else{

                 break;
            }
         }

         if(thread_number == 2){

            wr_02_lck.lock();

            if(TH2_BLOCK_CONDITION){     //   (th0_read_counter - th2_record_counter) >= 1

               if(LOOP_BREAK_CONDITION){

                  break;
               }

               th2_record_counter = 1;

               if(th02_wait_number >=1){

                  cv_wr_02.notify_one();
               }

               th02_wait_number++;

               cv_wr_02.wait(wr_02_lck);

               wr_02_lck.unlock();


               wr_02_lck.lock();

               th02_wait_number--;

               wr_02_lck.unlock();
            }
            else{

               wr_02_lck.unlock();
            }

            if(!LOOP_BREAK_CONDITION){

                Reader->Get_Record_Point_Pointer_02()[record_index_02] = th0_number_reputation;

                wr_02_lck.lock();

                record_index_02++;

                th2_record_counter++;

                wr_02_lck.unlock();
            }
            else{

                 break;
            }
         }

         if(thread_number == 1){

            wr_13_lck.lock();

            if(TH1_BLOCK_CONDITION){

               if(LOOP_BREAK_CONDITION){

                  break;
               }

               th1_read_counter = 1;

               if(th13_wait_number >=1){

                  cv_wr_13.notify_one();
               }

               th13_wait_number++;

               cv_wr_13.wait(wr_13_lck);

               wr_13_lck.unlock();

               wr_13_lck.lock();

               th13_wait_number--;

               wr_13_lck.unlock();
            }
            else{

                 wr_13_lck.unlock();
            }

            if(!LOOP_BREAK_CONDITION){

                int index = Reader->Get_Line_Index();

                char * string_line = Reader->Get_Data_Pointer()[index];

                th1_number_reputation = StringManager_TH13.Get_Word_Number_on_String(string_line,search_word);

                rd_lck.lock();

                Reader->Increase_Line_Index();

                rd_lck.unlock();


                wr_13_lck.lock();

                th1_read_counter++;

                wr_13_lck.unlock();
            }
            else{

                 break;
            }
          }

          if(thread_number == 3){

             wr_13_lck.lock();

             if(TH3_BLOCK_CONDITION){

                if(LOOP_BREAK_CONDITION){

                   break;
                }

                th3_record_counter = 1;

                if(th13_wait_number >=1){

                   cv_wr_13.notify_one();
                }

                th13_wait_number++;

                cv_wr_13.wait(wr_13_lck);

                th13_wait_number--;

                wr_13_lck.unlock();
             }
             else{

                    wr_13_lck.unlock();
             }

             if(!LOOP_BREAK_CONDITION){

                Reader->Get_Record_Point_Pointer_13()[record_index_13] = th1_number_reputation;

                wr_13_lck.lock();

                th3_record_counter++;

                record_index_13++;

                wr_13_lck.unlock();
             }
             else{

                   break;
             }
           }

     }while(Reader->Get_Line_Index() < Reader->Get_Data_length());

     if((thread_number == 1) || (thread_number == 3)){

        if(th13_wait_number >=1){

           cv_wr_13.notify_one();
        }
     }

     if((thread_number == 0) || (thread_number == 2)){

        if(th02_wait_number >=1){

           cv_wr_02.notify_one();
        }
     }
   }
