
 #include "MT_Library_Headers.h"
 #include <sys/time.h>
 #include <sys/resource.h>
 #include <unistd.h>
 #include <iostream>

 #define TEST_RECORD_CONDITION !(first_group_order_violation || second_group_order_violation)

 bool Data_Checking(char ** data_pointer_1, char ** data_pointer_2);

 bool thread_0_exit_condition = false;

 bool thread_1_exit_condition = false;

 bool thread_2_wait_condition = false;

 bool thread_3_wait_condition = false;

 int Elapsed_Time = 0;

 int Data_Size = 0;

 bool data_mismatch = false;

 int reader_sequence_index = 0;

 int writer_sequence_index = 0;

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

     Server.Data_Receiver_IT.SetFilePath(argv[1]);

     Server.Data_Receiver_IT.Receive_Data();

     Data_Size = Server.Data_Receiver_IT.Get_Data_length();

     for(int i=0;i<2;i++){

        Server.Activate(i,Readers_Function);
     }

     for(int i=2;i<4;i++){

        Server.Activate(i,Writers_Function);
     }

     for(int i=0;i<4;i++){

         Server.Join(i);
     };

     return_value = getrusage(RUSAGE_SELF, &usage);

     if(return_value!= 0){

        std::cout << "\n The usage data can not be obtain..\n";

        return 0;
     }

     end = usage.ru_utime;

     Elapsed_Time = end.tv_sec - start.tv_sec;

     //   Checking data mismatch"

     bool data_mismatch = Data_Checking(Server.Data_Receiver_IT.Get_Data_Pointer(),Server.Data_Receiver_IT.Get_Target_Memory_Pointer());

     if(!data_mismatch){

         bool first_group_order_violation = Server.Data_Receiver_IT.Check_First_Group_Order_Violation();

         bool second_group_order_violation = Server.Data_Receiver_IT.Check_Second_Group_Order_Violation();

         if(TEST_RECORD_CONDITION)
         {
            return Elapsed_Time;
         }
         else
         {
            return -1;
         }
     }
     else{

          return -1;
     }


 }

 void Readers_Function(pcynlitx::thds * thread_data){

      pcynlitx::TM_Client Manager(thread_data,"Readers_Function");

      pcynlitx::Data_Receiver_Client Receiver(thread_data);

      int thread_number = Manager.Get_Thread_Number();

      if(thread_number == 0){

         Manager.barier_wait();

         int j = 0;

         do {

              int i=0;

              do {
                    Manager.lock();

                    if(Receiver.Get_Buffer_1_Empty_Condition()){

                       Manager.unlock();

                       char * string = Receiver.Get_Data_Pointer()[i];

                       Receiver.SetBuffer_1(string);

                       Receiver.SetTargetMemoryIndex_1(i);

                       Receiver.Set_First_Group_Acess_Order(thread_number);

                       Receiver.SetBuffer_1_Empty_Condition(false);
                    }
                    else{

                          Manager.unlock();

                          Manager.rescue(2);

                          Manager.wait(0);

                          if(i>0){

                             i--;
                          }
                    }

                    i++;

              }while(i<Data_Size/2);

              j++;

         }while(j<2);

         thread_0_exit_condition = true;

         if(Manager.Get_Block_Status(2)){

            Manager.rescue(2);
         }
      }

      if(thread_number == 1){

         Manager.barier_wait();

         int j=0;

         do{

            int i=Data_Size/2;

            do {

                Manager.lock();

                if(Receiver.Get_Buffer_2_Empty_Condition()){

                   Manager.unlock();

                   char * string = Receiver.Get_Data_Pointer()[i];

                   Receiver.SetBuffer_2(string);

                   Receiver.SetTargetMemoryIndex_2(i);

                   Receiver.SetBuffer_2_Empty_Condition(false);

                   Receiver.Set_Second_Group_Acess_Order(thread_number);
                }
                else{

                      Manager.unlock();

                      Manager.rescue(3);

                      Manager.wait(1);

                      if(i > Data_Size/2){

                         i--;
                      }
                }

                i++;

                }while(i<Data_Size);

            j++;

         }while (j<2);

         thread_1_exit_condition = true;

         if(Manager.Get_Block_Status(3)){

            Manager.rescue(3);
         }
      }

      Manager.Exit();
 }

 void Writers_Function(pcynlitx::thds * thread_data){

      pcynlitx::TM_Client Manager(thread_data,"Writers_Function");

      pcynlitx::Data_Receiver_Client Receiver(thread_data);

      int thread_number = Manager.Get_Thread_Number();

      if( thread_number == 2){

          Manager.barier_wait();

          do {

               if(!thread_0_exit_condition){

                  Manager.lock();

                  if(!Receiver.Get_Buffer_1_Empty_Condition()){

                     Manager.unlock();

                     char * buffer = Receiver.Get_Buffer_1_Pointer();

                     int index = Receiver.Get_Target_Memory_Index_1();

                     Receiver.SetTargetMemory(buffer,index);

                     Receiver.SetBuffer_1_Empty_Condition(true);

                     Receiver.Set_First_Group_Acess_Order(thread_number);

                  }
                  else{

                       Manager.unlock();

                       Manager.rescue(0);

                       Manager.wait(2);
                  }
               }
               else{

                   break;
               }

          }while(!thread_0_exit_condition);
      }

      if(thread_number == 3){

         Manager.barier_wait();

          do {

              if(!thread_1_exit_condition){

                  Manager.lock();

                  if(!Receiver.Get_Buffer_2_Empty_Condition()){

                     Manager.unlock();

                     char * buffer = Receiver.Get_Buffer_2_Pointer();

                     int index = Receiver.Get_Target_Memory_Index_2();

                     Receiver.SetTargetMemory(buffer,index);

                     Receiver.SetBuffer_2_Empty_Condition(true);

                     Receiver.Set_Second_Group_Acess_Order(thread_number);

                 }
                 else{

                      Manager.unlock();

                      Manager.rescue(1);

                      Manager.wait(3);
                 }
              }
              else{

                   break;
              }

         }while(!thread_1_exit_condition);
      }

      Manager.Exit();
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
