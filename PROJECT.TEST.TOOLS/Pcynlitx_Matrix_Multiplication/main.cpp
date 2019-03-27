
 #include "MT_Library_Headers.h"
 #include <sys/time.h>
 #include <sys/resource.h>
 #include <unistd.h>
 #include <iostream>
 #include <random>

 int matrix_size = 500;

 int Elapsed_Time = 0;

 bool Memory_Clear_Condition = false;

 double lower_bound = 0;

 double upper_bound = 5;

 std::uniform_real_distribution<double> unif(lower_bound,upper_bound);

 std::default_random_engine re;

 double ** Matrix_1_Pointer = nullptr;

 double ** Matrix_2_Pointer = nullptr;

 double ** result_matrix = nullptr;

void Construct_Random_Matrices();

 void Clear_Heap_Memory();

 int main(int argc, char ** argv){

     struct rusage usage;

     struct timeval start, end;

     int return_value = getrusage(RUSAGE_SELF,&usage);

     if(return_value!= 0){

        std::cout << "\n The usage data can not be obtain..\n";

        return 0;
     }

     start = usage.ru_utime;

     Thread_Server Server;

     Server.Matrix_Data_IT.Receive_Matrix_Size(matrix_size);

     Construct_Random_Matrices();

     for(int i=0;i<4;i++){

         Server.Activate(i,Multiply);
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

     std::cout << Elapsed_Time;

     Clear_Heap_Memory();

     return 0;
 }

 void Multiply(thds * thread_data){

      Synchronizer_Client Synchronizer(thread_data,"Multiply");

      Matrix_Data_Client Matrix_Data_IT(thread_data);

      int Thread_Number = Synchronizer.Get_Thread_Number();

      int start_row = Matrix_Data_IT.Get_Start_Row(Thread_Number);

      int end_row = Matrix_Data_IT.Get_End_Row(Thread_Number);

      for(int i=start_row;i<end_row;i++){

          int sum = 0;

          for(int j=0;j<matrix_size;j++){

              for(int k=0;k<matrix_size;k++){

                  sum = sum + Matrix_1_Pointer[i][k]*Matrix_2_Pointer[k][j];
              }

              result_matrix[i][j] = sum;
          }
      }

      Synchronizer.Exit();
 }

 void Construct_Random_Matrices(){

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


 void Clear_Heap_Memory(){

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
