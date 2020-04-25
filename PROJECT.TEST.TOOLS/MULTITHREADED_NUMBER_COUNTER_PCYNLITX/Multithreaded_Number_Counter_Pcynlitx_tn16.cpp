

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
#include "Data_Types.h"

#define LOOP_BREAK_CONDITION (Line_index >= Reader.Get_Data_length())

#define INDEX_INCREMENT_STATUS (Reader.Get_Data_List_Member_Record_Status(index))

int total_reputation = 0;

int num_threads = 16;

int Elapsed_Time = 0;

int Line_index = 0;

int tur_index = 0;

int entered_thread_number = 0;

int exit_thread_number = 0;

char search_word [] = "100.00";

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n usage: " << argv[0] << " <input file>";

       std::cout << "\n\n";

       exit(0);
    }

    pcynlitx::Thread_Server Server;

    Server.Data_Reader_IT.SetFilePath(argv[1]);

    Server.Data_Reader_IT.Receive_Total_Thread_Number(num_threads);

    Server.Data_Reader_IT.Receive_Data();


    struct rusage usage;

    struct timeval start, end;

    int return_value = getrusage(RUSAGE_SELF,&usage);

    if(return_value!= 0){

       std::cout << "\n The usage data can not be obtain..\n";

       return 0;
    }

    start = usage.ru_utime;


    for(int i=0;i<num_threads;i++){

        Server.Activate(i,Function);
    }

    for(int i=0;i<num_threads;i++){

        Server.Join(i);
    };


    return_value = getrusage(RUSAGE_SELF, &usage);

    if(return_value!= 0){

       std::cout << "\n The usage data can not be obtain..\n";

       return 0;
    }

    end = usage.ru_utime;

    Elapsed_Time = end.tv_sec - start.tv_sec;

    std::cout << "\n\n Elapsed_Time:" << Elapsed_Time;

    std::cout << "\n\n";


    int number = 0;

    for(int i=0;i<Server.Data_Reader_IT.Get_Record_List_Length();i++){

        if(Server.Data_Reader_IT.Get_Record_Number(i) <= 1){

           number = number + Server.Data_Reader_IT.Get_Reputation(i);
        }
    }

    std::cout << "\n\n number:" << number << std::endl;

    std::cout << "\n\n total_reputation:" << total_reputation << std::endl;

    for(int i=0;i< Server.Data_Reader_IT.Get_Data_length();i++){

        if(Server.Data_Reader_IT.Get_Record_Number(i) > 1){

           std::cout << "\n There is overrite ..";
        }
    }


    bool acess_order_violation = Server.Data_Reader_IT.Check_Acess_Order_Violation();

    if(acess_order_violation){

       std::cout << "\n There is acess order violation.." << std::endl;

       std::cout << "\n\n";
    }
    else{

        std::cout << "\n There is no acess order violation..";

        std::cout << "\n\n";
    }

    Server.Data_Reader_IT.Print_Acess_Order();

    Cpp_FileOperations FileManager;

    IntToCharTranslater Translater;

    FileManager.SetFilePath("Test_Record_File");

    FileManager.FileOpen(Af);

    FileManager.WriteToFile(Translater.Translate(Elapsed_Time));

    FileManager.WriteToFile("\n");

    FileManager.FileClose();

    return 0;
}

void Function(pcynlitx::thds * thread_data){

     pcynlitx::TM_Client Manager(thread_data,"Function");

     pcynlitx::Data_Reader_Client Reader(thread_data);

     int thread_number = Manager.Get_Thread_Number();

     // THE END OF THE ENTRANCE BARRIER

     int index = 0;

     do {
             // STARTING OF THE PARALLEL EXECUTION REGION

             if(LOOP_BREAK_CONDITION){

                break;
             }



             StringOperator StringManager;

             Manager.lock();

             index = Line_index;

             Line_index++;

             Manager.unlock();


             Manager.lock();

             while(Reader.Get_Data_List_Member_Record_Status(index)){

                   Line_index++;

                   index = Line_index;
             }

             Manager.unlock();

             // THE END OF THE PARALLEL EXECUTION

             Manager.lock();

             if(thread_number != 0){

                Manager.unlock();

                Manager.wait(thread_number,thread_number-1);
             }
             else{

                Manager.unlock();
             }


             if(LOOP_BREAK_CONDITION){

                break;
             }



             // START OF THE SERIAL EXECUTION  ------------------------------------------------

             // The critical section

             Manager.lock();

             char * string_line = Reader.Get_Data_List_Member_String(index);

             int reputation = StringManager.Get_Word_Number_on_String(string_line,search_word);

             total_reputation = total_reputation + reputation;

             Manager.unlock();


             Manager.lock();

             if((!Reader.Get_Data_List_Member_Record_Status(index))){

                  Reader.Set_Record_Data(index,thread_number,reputation);
             };

             Manager.unlock();


             Manager.lock();

             Reader.Set_Acess_Order(thread_number);

             Manager.unlock();



             // THE END OF SERIAL EXECUTION -------------------------------------------------


             Manager.lock();

             if(thread_number != (num_threads-1)){

                Manager.unlock();

                Manager.rescue(thread_number+1,thread_number);
             }
             else{

                    Manager.unlock();

                    Manager.rescue(0,num_threads-1);
             }

             Manager.lock();

             if(thread_number == 0){

                Manager.unlock();

                Manager.wait(0,num_threads-1);
             }
             else{

                  Manager.unlock();
             }

     }while(!LOOP_BREAK_CONDITION);


     Manager.lock();

     exit_thread_number++;

     Manager.unlock();


     do {

         if(exit_thread_number<num_threads){

             for(int i=0;i<num_threads;i++){

                 if(i!=thread_number){

                    Manager.lock();

                    if(Manager.Get_Thread_Block_Status(i)){

                       Manager.rescue(i);
                    }

                    Manager.unlock();
                 }
             }
         }

     } while(exit_thread_number<num_threads);


     Manager.Exit();
}
