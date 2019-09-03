
#include "Matrix_Data.h"

Matrix_Data::Matrix_Data(){

     this->Matrix_Size = 0;
}

Matrix_Data::Matrix_Data(const Matrix_Data & orig){

}

Matrix_Data::~Matrix_Data(){

}

void Matrix_Data::Receive_Matrix_Size(int size){

     this->Matrix_Size = size;

     int quotient  = this->Matrix_Size / 4;

     this->Receive_Start_Row(0,0);

     this->Receive_End_Row(0,quotient);

     this->Receive_Start_Row(1,quotient);

     this->Receive_End_Row(1,2*quotient);

     this->Receive_Start_Row(2,2*quotient);

     this->Receive_End_Row(2,3*quotient);

     this->Receive_Start_Row(3,3*quotient);

     this->Receive_End_Row(3,this->Matrix_Size);
}

void Matrix_Data::Receive_Start_Row(int thread_number, int start_row){

    this->sections[thread_number][0] = start_row;
}

void Matrix_Data::Receive_End_Row(int thread_number, int end_row){

    this->sections[thread_number][1] = end_row;
}

int  Matrix_Data::Get_Start_Row(int thread_number){

     return this->sections[thread_number][0];
}

int  Matrix_Data::Get_End_Row(int thread_number){

    return this->sections[thread_number][1];
}

int  Matrix_Data::Get_Matrix_Size(){

     return this->Matrix_Size;
}

void Matrix_Data::Print_Random_Matrix(double *** pointer){

     for(int i=0;i<this->Matrix_Size;i++){

         std::cout << "\n";

         for(int k=0;k<this->Matrix_Size;k++){

             std::cout << " " << (*pointer)[i][k];
         }
     }
}
