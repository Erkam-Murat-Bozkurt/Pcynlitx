
#include "Producer_Consumer_Std_Thread.h"

int main(int argc, char ** argv){

    struct rusage usage;

    struct timeval start, end;

    int return_value = getrusage(RUSAGE_SELF,&usage);

    if(return_value!= 0){

       std::cout << "\n The usage data can not be obtain..\n";

       return 0;
    }

    start = usage.ru_utime;

    Data_Receiver Receiver;

    Receiver.SetFilePath(argv[1]);

    Receiver.Receive_Data();

    Data_Size = Receiver.Get_Data_length();

    thread_1 = std::thread(Readers_Function,&Receiver,0);

    thread_2 = std::thread(Readers_Function,&Receiver,1);

    thread_3 = std::thread(Writers_Function,&Receiver,2);

    thread_4 = std::thread(Writers_Function,&Receiver,3);

    thread_1.join();

    thread_2.join();

    thread_3.join();

    thread_4.join();

    return_value = getrusage(RUSAGE_SELF, &usage);

    if(return_value!= 0){

       std::cout << "\n The usage data can not be obtain..\n";

       return 0;
    }

    end = usage.ru_utime;

    Elapsed_Time = end.tv_sec - start.tv_sec;

    /* std::cout << "\n Checking data mismatch"; */

    bool Result = Data_Checking(Receiver.Get_Data_Pointer(),Receiver.Get_Target_Memory_Pointer());

    /* std::cout << "\n Is there any data mismatch:" << Result; */

    /* std::cout << "\n The end of the program.."; */

    std::cout << Elapsed_Time;

    return 0;
}

void Readers_Function(Data_Receiver * Receiver,int thread_number){

     std::unique_lock<std::mutex> rd_lck(mtx_rd);

     rd_lck.unlock();

     rd_lck.lock();

     reader_thread_wait_at_start++;

     rd_lck.unlock();

     rd_lck.lock();

     while(read_start_condition){

           cv_rd.wait(rd_lck);
     }

     rd_lck.unlock();

     // Operation enterence for thread[0] and thread[1]


     std::unique_lock<std::mutex> TH02_lck(mtx_02);

     TH02_lck.unlock();

     if(thread_number == 0){

        thread_0_exit_condition = false;

        int j=0;

        do{

            int i=0;

            do {

                TH02_lck.lock();

                if(Receiver->Get_Buffer_1_Empty_Condition()){

                   TH02_lck.unlock();

                   char * string = Receiver->Get_Data_Pointer()[i];

                   Receiver->SetBuffer_1(string);

                   Receiver->SetTargetMemoryIndex_1(i);

                   Receiver->SetBuffer_1_Empty_Condition(false);
                }
                else{

                      TH02_lck.unlock();

                      TH02_lck.lock();

                      cv_02.notify_one();

                      cv_02.wait(TH02_lck);

                      TH02_lck.unlock();

                      if(i>0){

                          i--;
                      }
                }

                i++;

            }while(i<Data_Size/2);

           j++;

        }while(j<2);

        thread_0_exit_condition = true;

        if(thread_2_wait_condition == true){

            cv_02.notify_one();
        }
     }


     std::unique_lock<std::mutex> TH13_lck(mtx_13);

     TH13_lck.unlock();

     if(thread_number == 1){

        thread_1_exit_condition = false;

        int j=0;

        do{

            int i=Data_Size/2;

            do {

                TH13_lck.lock();

                if(Receiver->Get_Buffer_2_Empty_Condition()){

                   TH13_lck.unlock();

                   char * string = Receiver->Get_Data_Pointer()[i];

                   Receiver->SetBuffer_2(string);

                   Receiver->SetTargetMemoryIndex_2(i);

                   Receiver->SetBuffer_2_Empty_Condition(false);
                }
                else{

                      TH13_lck.unlock();

                      TH13_lck.lock();

                      cv_13.notify_one();

                      cv_13.wait(TH13_lck);

                      TH13_lck.unlock();

                      if(i>0){

                         i--;
                      }
                }

                i++;

          }while(i<Data_Size);

          j++;

        }while(j<2);

         thread_1_exit_condition = true;

         if(thread_3_wait_condition == true){

            cv_13.notify_one();
         }
     }
   }

// -----------------------------------------------------------------------------

//  Writer threads function

void Writers_Function(Data_Receiver * Receiver,int thread_number){

     std::unique_lock<std::mutex> wr_lck(mtx_wr);

     wr_lck.unlock();

     wr_lck.lock();

     writer_thread_wait_at_start++;

     wr_lck.unlock();

     Check_Read_Start_Condition();

     // write operations started ...


     std::unique_lock<std::mutex> TH02_lck(mtx_02);

     TH02_lck.unlock();

     if(thread_number == 2){

        do {

             if(!thread_0_exit_condition){

                TH02_lck.lock();

                if(!Receiver->Get_Buffer_1_Empty_Condition()){

                    TH02_lck.unlock();

                    char * buffer = Receiver->Get_Buffer_1_Pointer();

                    int index = Receiver->Get_Target_Memory_Index_1();

                    Receiver->SetTargetMemory(buffer,index);

                    Receiver->SetBuffer_1_Empty_Condition(true);
                }
                else{

                     TH02_lck.unlock();

                     TH02_lck.lock();

                     thread_2_wait_condition = true;

                     cv_02.notify_one();

                     cv_02.wait(TH02_lck);

                     thread_2_wait_condition = false;

                     TH02_lck.unlock();
                }
             }
             else{

                   break;
            }

        }while(!thread_0_exit_condition);
      }

      std::unique_lock<std::mutex> TH13_lck(mtx_13);

      TH13_lck.unlock();

      if(thread_number == 3){

         do {

             if(!thread_1_exit_condition){

                 TH13_lck.lock();

                 if(!Receiver->Get_Buffer_2_Empty_Condition()){

                     TH13_lck.unlock();

                     char * buffer = Receiver->Get_Buffer_2_Pointer();

                     int index = Receiver->Get_Target_Memory_Index_2();

                     Receiver->SetTargetMemory(buffer,index);

                     Receiver->SetBuffer_2_Empty_Condition(true);
                 }
                 else{

                       TH13_lck.unlock();

                       TH13_lck.lock();

                       thread_3_wait_condition = true;

                       cv_13.notify_one();

                       cv_13.wait(TH13_lck);

                       thread_3_wait_condition = false;

                       TH13_lck.unlock();
                 }
            }
            else{

                  break;
            }

         }while(!thread_1_exit_condition);
      }
}

void Check_Read_Start_Condition(){

     while(read_start_condition)
     {
        if(writer_thread_wait_at_start < 2){

           std::this_thread::yield();

           std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        if(((read_start_condition) && (reader_thread_wait_at_start > 1)

             && (writer_thread_wait_at_start > 1))){

             read_start_condition = false;

             cv_rd.notify_all();
        }
        else{

              std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
     }
}


 bool Data_Checking(char ** data_pointer_1, char ** data_pointer_2){

      data_mismatch = false;

      for(int i=0;i<Data_Size;i++){

          int row_size = strlen(data_pointer_1[i]);

          for(int j=0;j<row_size;j++){

             if(data_pointer_1[i][j] != data_pointer_1[i][j]){

                data_mismatch = true;

                break;
              }
          }
      }

      return data_mismatch;
 }
