
 #include "MT_Library_Headers.h"
 #include <sys/time.h>
 #include <sys/resource.h>
 #include <unistd.h>
 #include <iostream>
 #include <random>
 #include <iostream>
 #include <random>
 #include <string>
 #include <sstream>
 #include <cstring>

 #define NTHREAD 32

 int Elapsed_Time_for_user = 0;

 int Elapsed_Time_for_sys = 0;

 int Elapsed_Time_for_total = 0;


 bool Memory_Clear_Condition = false;

 double lower_bound = 0;

 double upper_bound = 5;

 std::uniform_real_distribution<double> unif(lower_bound,upper_bound);

 std::default_random_engine re;

 double ** Matrix_1_Pointer = nullptr;

 double ** Matrix_2_Pointer = nullptr;

 double ** result_matrix = nullptr;

 void Construct_Random_Matrices(int matrix_size);

 void Convert_char_to_std_string(std::string * string_line, char * cstring_pointer);

 void Clear_Heap_Memory(int matrix_size);

 int main(int argc, char ** argv){

     if(argc != 2) {

        std::cout << "\n\n   Usage: " << argv[0] << " [Matrix Size]" << std::endl;

        std::cout << "\n\n";

        exit(1);
     }

     struct rusage usage;

     struct timeval start_us, end_us, start_sys, end_sys;

     int return_value = getrusage(RUSAGE_SELF,&usage);

     if(return_value!= 0){

        std::cout << "\n The usage data can not be obtain..\n";

        return 0;
     }

     start_us = usage.ru_utime;

     start_sys = usage.ru_stime;

     std::string Dimention;

     Convert_char_to_std_string(&Dimention,argv[1]);

     std::stringstream s(Dimention);

     int matrix_size = 0;

     s >> matrix_size;

     pcynlitx::Thread_Server Server;

     Server.Matrix_Data_IT.Receive_Matrix_Size(matrix_size);

     Construct_Random_Matrices(matrix_size);

     for(int i=0;i<NTHREAD;i++){

         Server.Activate(i,Multiply);
     }

     for(int i=0;i<NTHREAD;i++){

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

     Clear_Heap_Memory(matrix_size);

     return 0;
 }

 void Multiply(pcynlitx::thds * thread_data){

      pcynlitx::TM_Client Manager(thread_data,"Multiply");

      pcynlitx::Matrix_Data_Client Matrix_Data_IT(thread_data);

      int matrix_size = Matrix_Data_IT.Get_Matrix_Size();

      for(int i=0;i<matrix_size;i++){

          int sum = 0;

          for(int j=0;j<matrix_size;j++){

              for(int k=0;k<matrix_size;k++){

                  sum = sum + Matrix_1_Pointer[i][k]*Matrix_2_Pointer[k][j];
              }

              result_matrix[i][j] = sum;
          }
      }

      Manager.Exit();
 }

 void Construct_Random_Matrices(int matrix_size){

      Matrix_1_Pointer = new double * [5*matrix_size];

      for(int i=0;i<matrix_size;i++){

          Matrix_1_Pointer[i] = new double [5*matrix_size];

          for(int k=0;k<matrix_size;k++){

              Matrix_1_Pointer[i][k] = unif(re);
          }
      }

      Matrix_2_Pointer = new double * [5*matrix_size];

      for(int i=0;i<matrix_size;i++){

          Matrix_2_Pointer[i] = new double [5*matrix_size];

          for(int k=0;k<matrix_size;k++){

              Matrix_2_Pointer[i][k] = unif(re);
          }
      }

      result_matrix = new double * [5*matrix_size];

      for(int i=0;i<matrix_size;i++){

          result_matrix[i] = new double [5*matrix_size];

          for(int k=0;k<matrix_size;k++){

              result_matrix[i][k] = 0;
          }
      }
 }

 void Clear_Heap_Memory(int matrix_size){

      if(!Memory_Clear_Condition){

          Memory_Clear_Condition = true;

          for(int i=0;i<matrix_size;i++){

             delete [] Matrix_1_Pointer[i];
          }

          delete [] Matrix_1_Pointer;

          for(int i=0;i<matrix_size;i++){

              delete [] Matrix_2_Pointer[i];
          }

          delete [] Matrix_2_Pointer;

          for(int i=0;i<matrix_size;i++){

              delete [] result_matrix[i];
         }

          delete [] result_matrix;
      }
 }

 void Convert_char_to_std_string(std::string * string_line, char * cstring_pointer){

     int string_length = strlen(cstring_pointer);

     for(int i=0;i<string_length;i++){

         *string_line = *string_line + cstring_pointer[i];
     }
 }
