

 #include "MT_Library_Headers.h"
 #include <sys/time.h>
 #include <sys/resource.h>
 #include <unistd.h>

 #define LOOP_BREAK_CONDITION (Reader.Get_Line_Index() == Reader.Get_Data_length())

 StringOperator StringManager_TH02;

 StringOperator StringManager_TH13;

 char search_word [] = "100.00";

 int th0_number_reputation = 0;

 int th1_number_reputation = 0;

 int record_index_02 = 0;

 int record_index_13 = 0;

 int Elapsed_Time = 0;

 int waiting_thread_number = 0;

 int main(int argc, char ** argv){

     struct rusage usage;

     struct timeval start, end;

     int return_value = getrusage(RUSAGE_SELF,&usage);

     if(return_value!= 0){

        std::cout << "\n The usage data can not be obtain..\n";

        return 0;
     }

     start = usage.ru_utime;

     pcynlitx::Thread_Server Server;

     Server.Data_Reader_IT.SetFilePath(argv[1]);

     Server.Data_Reader_IT.Receive_Data();

     for(int i=0;i<4;i++){

         Server.Activate(i,Function);
     }

     for(int i=0;i<4;i++){

         Server.Join(i);
     };

     int number = 0;

     for(int i=0;i< Server.Data_Reader_IT.Get_Data_length();i++){

         number = number + Server.Data_Reader_IT.Get_Record_Point_Pointer_02()[i];
     }

     for(int i=0;i<Server.Data_Reader_IT.Get_Data_length();i++){

         number = number + Server.Data_Reader_IT.Get_Record_Point_Pointer_13()[i];
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

 void Function(pcynlitx::thds * thread_data){

      pcynlitx::TM_Client Manager(thread_data,"Function");

      pcynlitx::Data_Reader_Client Reader(thread_data);

      int Thread_Number = Manager.Get_Thread_Number();

      do {

           if(Thread_Number == 2){

              Manager.wait(2);
           }

           if(Thread_Number == 0){

              if(!LOOP_BREAK_CONDITION){

                // Thread [0] reads the data

                int index = Reader.Get_Line_Index();

                char * string_line = Reader.Get_Data_Pointer()[index];

                th0_number_reputation = StringManager_TH02.Get_Word_Number_on_String(string_line,search_word);

                Manager.lock();

                Reader.Increase_Line_Index();

                Manager.unlock();

             }
             else{

                   break;
             }
          }

          if(Thread_Number == 0){

             Manager.rescue(2);

             Manager.wait(0);
          }

          if(Thread_Number == 2){

             if(!LOOP_BREAK_CONDITION){

                 Reader.Get_Record_Point_Pointer_02()[record_index_02] = th0_number_reputation;

                 Manager.lock();

                 record_index_02++;

                 Manager.unlock();
             }
             else{
                    break;
             }
          }

          if(Thread_Number == 2){

             Manager.rescue(0);
          }


          if(Thread_Number == 3){

              Manager.wait(3);
          }


          if(Thread_Number == 1){

             if(!LOOP_BREAK_CONDITION){

                // Thread [1] reads data

                int index = Reader.Get_Line_Index();

                char * string_line = Reader.Get_Data_Pointer()[index];

                th1_number_reputation = StringManager_TH13.Get_Word_Number_on_String(string_line,search_word);

                Manager.lock();

                Reader.Increase_Line_Index();

                Manager.unlock();
             }
             else{

                    break;
             }
          }

          if(Thread_Number == 1){

             Manager.rescue(3);

             Manager.wait(1);
          }

          if(Thread_Number == 3){

             if(!LOOP_BREAK_CONDITION){

                 // Thread [3] records data

                 Reader.Get_Record_Point_Pointer_13()[record_index_13] = th1_number_reputation;

                 Manager.lock();

                 record_index_13++;

                 Manager.unlock();
             }
             else{

                  break;
             }
           }

           if(Thread_Number == 3){

              Manager.rescue(1);
           }

       }while(Reader.Get_Line_Index() < Reader.Get_Data_length());

       for(int i=0;i<4;i++){

           if(i!=Thread_Number){

              if(Manager.Get_Block_Status(i)){

                 Manager.rescue(i);
              }
           }
       }

      Manager.Exit();
 }
