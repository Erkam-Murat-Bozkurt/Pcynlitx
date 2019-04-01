
#include "C++_Std_Thread_File_Search.h"

int main( ){

    struct rusage usage;

    struct timeval start, end;

    int return_value = getrusage(RUSAGE_SELF,&usage);

    if(return_value!= 0){

       std::cout << "\n The usage data can not be obtain..\n";

       return 0;
    }

    start = usage.ru_utime;

    Searcher[0].SetFilePath(Target_File);

    Searcher[1].SetFilePath(Target_File);

    Reader.SetFilePath(Target_File);

    Writer[0].SetFilePath(Record_File);

    Writer[0].FileOpen(RWCf);

    Writer[1].SetFilePath(Record_File);

    Writer[1].FileOpen(RWCf);

    int File_Lenght = File_Length_Determine();

    thread_1 = std::thread(Readers_Function,0,File_Lenght/2,0);

    thread_2 = std::thread(Readers_Function,File_Lenght/2,File_Lenght,1);

    thread_3 = std::thread(Writers_Function,0);

    thread_4 = std::thread(Writers_Function,1);

    thread_1.join();

    thread_2.join();

    thread_3.join();

    thread_4.join();

    Writer[0].FileClose();

    Writer[1].FileClose();

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

void Readers_Function(int start_point, int end_point, int thread_number){

     std::unique_lock<std::mutex> rd_lck(mtx_1);

     rd_lck.unlock();

     rd_lck.lock();

     reader_thread_wait_at_start++;

     rd_lck.unlock();

     rd_lck.lock();

     while(read_start_condition){

           cv_1.wait(rd_lck);
     }

     rd_lck.unlock();

     for(int i=start_point;i<end_point;i++){

         rd_lck.lock();

         while(write_condition){

               cv_1.wait(rd_lck);
         }

         if(Is_Word_Included(thread_number,i)){

            write_condition = true;

            Buffer = Searcher[thread_number].GetStringBuffer();

            cv_2.notify_one();

            while(write_condition){

                  cv_1.wait(rd_lck);
            }
         }

         rd_lck.unlock();
     }

     rd_lck.lock();

     read_operation_counter++;

     rd_lck.unlock();

     rd_lck.lock();

     if(read_operation_counter > 1){

        write_condition = true;

        cv_2.notify_all();
     }

     rd_lck.unlock();
   }

// -----------------------------------------------------------------------------

//  Writer threads function

void Writers_Function(int thread_number){

     std::unique_lock<std::mutex> wr_lck(mtx_2);

     wr_lck.unlock();

     wr_lck.lock();

     writer_thread_wait_at_start++;

     wr_lck.unlock();

     Check_Read_Start_Condition();

     // write operations started ...

     do {
           wr_lck.lock();

           if(!write_condition){

              do{

                 cv_2.wait(wr_lck);

              }while(!write_condition);
           }

           wr_lck.unlock();

           if(read_operation_counter < 2){

              wr_lck.lock();

              Writer[thread_number].WriteToFile(Buffer);

              Writer[thread_number].WriteToFile("\n");

              Buffer = nullptr;

              write_condition = false;

              cv_1.notify_all();

              wr_lck.unlock();
           }

     }while(read_operation_counter<2);
}

int File_Length_Determine(){

     end_of_file_position = 0;

     Reader.FileOpen(Rf);

     while(!Reader.Control_End_of_File()){

            Reader.ReadLine();

            end_of_file_position++;
     }

     Reader.FileClose();

     return end_of_file_position;
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

             cv_1.notify_all();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
     }
}

bool Is_Word_Included(int thread_number, int line_number){

     include_condition = false;

     Searcher[thread_number].ReadFileLine(line_number);

     char * string_buffer = Searcher[thread_number].GetStringBuffer();

     bool include_condition = Searcher[thread_number].CheckStringInclusion(string_buffer,search_word);

     return include_condition;
}
