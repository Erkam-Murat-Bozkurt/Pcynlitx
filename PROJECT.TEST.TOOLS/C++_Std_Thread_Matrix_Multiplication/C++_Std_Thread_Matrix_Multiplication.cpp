

#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <random>
#include <sstream>
#include "Cpp_FileOperations.h"

void Multiply(double *** matrix_1, double *** matrix_2, double *** result_matrix, int start_row, int end_row, int matrix_size);

void Clear_Heap_Memory(double *** pointer, int matrix_size);

void Construct_Random_Matrix(double *** pointer, int matrix_size);

void Print_Random_Matrix(double *** pointer, int matrix_size);

std::mutex mtx;

int Elapsed_Time = 0;

double lower_bound = 0;

double upper_bound = 5;

std::uniform_real_distribution<double> unif(lower_bound,upper_bound);

std::default_random_engine re;

int main(int argc, char** argv){

    struct rusage usage;

    struct timeval start, end;

    int return_value = getrusage(RUSAGE_SELF,&usage);

    if(return_value!= 0){

       std::cout << "\n The usage data can not be obtain..\n";

       return 0;
    }

    start = usage.ru_utime;

    Cpp_FileOperations FileManager;

    FileManager.SetFilePath("Matrix_Dimention");

    FileManager.FileOpen(Rf);

    std::string Dimention = FileManager.ReadLine();

    std::stringstream s(Dimention);

    int matrix_size = 0;

    s >> matrix_size;

    FileManager.FileClose();

    double ** result_matrix = nullptr;

    double ** matrix_1 = nullptr;

    double ** matrix_2 = nullptr;

    Construct_Random_Matrix(&matrix_1,matrix_size);

    Construct_Random_Matrix(&matrix_2,matrix_size);

    Construct_Random_Matrix(&result_matrix,matrix_size);

    int quotient  = matrix_size / 4;

    int remainder = matrix_size % 4;

    std::thread thread_1(Multiply,&matrix_1,&matrix_2,&result_matrix,0,quotient,matrix_size);

    std::thread thread_2(Multiply,&matrix_1,&matrix_2,&result_matrix,quotient,2*quotient,matrix_size);

    std::thread thread_3(Multiply,&matrix_1,&matrix_2,&result_matrix,2*quotient,3*quotient,matrix_size);

    std::thread thread_4(Multiply,&matrix_1,&matrix_2,&result_matrix,3*quotient,(4*quotient+remainder),matrix_size);

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

    std::cout << Elapsed_Time;

    Clear_Heap_Memory(&matrix_1,matrix_size);

    Clear_Heap_Memory(&matrix_2,matrix_size);

    Clear_Heap_Memory(&result_matrix,matrix_size);

    return 0;
}

void Multiply(double *** matrix_1, double *** matrix_2, double *** result_matrix, int start_row, int end_row,int matrix_size){

     for(int i=start_row;i<end_row;i++){

         int sum = 0;

         for(int j=0;j<matrix_size;j++){

             for(int k=0;k<matrix_size;k++){

                 sum = sum + (*matrix_1)[i][k]*(*matrix_2)[k][j];
             }

             (*result_matrix)[i][j] = sum;
         }
     }
}

void Construct_Random_Matrix(double *** pointer, int matrix_size){

     *pointer = new double * [5*matrix_size];

     for(int i=0;i<matrix_size;i++){

         (*pointer)[i] = new double [5*matrix_size];

         for(int k=0;k<matrix_size;k++){

             (*pointer)[i][k] = unif(re);
         }
     }
}

void Clear_Heap_Memory(double *** pointer, int matrix_size){

     for(int i=0;i<matrix_size;i++){

         delete [] (*pointer)[i];
     }
}

void Print_Random_Matrix(double *** pointer, int matrix_size){

     for(int i=0;i<matrix_size;i++){

         std::cout << "\n";

         for(int k=0;k<matrix_size;k++){

             std::cout << " " << (*pointer)[i][k];
         }
     }
}
