
 #include "MT_Library_Headers.h"
 #include <sys/time.h>
 #include <sys/resource.h>
 #include <unistd.h>
 #include <iostream>

 void Readers_Function(pcynlitx::thds * thread_data);

 void Writers_Function(pcynlitx::thds * thread_data);

 int  File_Length_Determine();

 void Is_Word_Included(int thread_number, int line_number, bool * include_condition);

 char Target_File [] = "Target_File";

 char Record_File [] = "Record_File";

 char search_word [] = "File";

 StringOperator Searcher[2];

 Cpp_FileOperations Reader;

 Cpp_FileOperations Writer[2];

 bool thread_0_exit_condition = false;

 bool thread_1_exit_condition = false;

 bool thread_2_wait_condition = false;

 bool thread_3_wait_condition = false;

 int File_Lenght = 0;

 char * Buffer_1 = nullptr;

 char * Buffer_2 = nullptr;

 int end_of_file_position = 0; // The number of line from the start of the file to the enf of file

 int Elapsed_Time = 0;

 int main(int argc, char ** argv){

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

     File_Lenght = File_Length_Determine();

     pcynlitx::Thread_Server Server;

     for(int i=0;i<2;i++){

        Server.Activate(i,Readers_Function);
     }

     for(int i=2;i<4;i++){

        Server.Activate(i,Writers_Function);
     }

     for(int i=0;i<4;i++){

         Server.Join(i);
     };

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

 void Readers_Function(pcynlitx::thds * thread_data){

      pcynlitx::TM_Client Manager(thread_data,"Readers_Function");

      int thread_number = Manager.Get_Thread_Number();

      if(thread_number == 0){

         Manager.barier_wait();

         for(int i=0;i<File_Lenght/2;i++){

             bool include_condition = false;

             Is_Word_Included(thread_number,i,&include_condition);

             if(include_condition){

                Buffer_1 = Searcher[thread_number].GetStringBuffer();

                Manager.rescue(2);

                Manager.wait(0);
             }
         }

         thread_0_exit_condition = true;

         if(Manager.Get_Block_Status(2)){

            Manager.rescue(2);
         }
      }

      if(thread_number == 1){

         Manager.barier_wait();

         for(int i=File_Lenght/2;i<File_Lenght;i++){

             bool include_condition = false;

             Is_Word_Included(thread_number,i,&include_condition);

             if(include_condition){

                Buffer_2 = Searcher[thread_number].GetStringBuffer();

                Manager.rescue(3);

                Manager.wait(1);
             }
         }

         thread_1_exit_condition = true;

         if(Manager.Get_Block_Status(3)){

            Manager.rescue(3);
         }
      }

      Manager.Exit();
 }

 void Writers_Function(pcynlitx::thds * thread_data){

      pcynlitx::TM_Client Manager(thread_data,"Writers_Function");

      int thread_number = Manager.Get_Thread_Number();

      if( thread_number == 2){

          Manager.barier_wait();

          do {

               if(!thread_0_exit_condition){

                   Manager.wait(2);

                   if(thread_0_exit_condition){

                      break;
                   }
               }
               else{

                   break;
               }

               Writer[0].WriteToFile(Buffer_1);

               Writer[0].WriteToFile("\n");

               Buffer_1 = nullptr;

               if(!thread_0_exit_condition){

                   Manager.rescue(0);
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

                  Manager.wait(3);

                  if(thread_1_exit_condition){

                     break;
                  }
              }
              else{

                   break;
              }

              Writer[1].WriteToFile(Buffer_2);

              Writer[1].WriteToFile("\n");

              Buffer_2 = nullptr;

              if(!thread_1_exit_condition){

                  Manager.rescue(1);
              }
              else{

                  break;
              }

         }while(!thread_1_exit_condition);
      }

      Manager.Exit();
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

 void Is_Word_Included(int thread_number, int line_number, bool * include_condition){

      *include_condition = false;

      Searcher[thread_number].ReadFileLine(line_number);

      char * string_buffer = Searcher[thread_number].GetStringBuffer();

      *include_condition = Searcher[thread_number].CheckStringInclusion(string_buffer,search_word);
 }
