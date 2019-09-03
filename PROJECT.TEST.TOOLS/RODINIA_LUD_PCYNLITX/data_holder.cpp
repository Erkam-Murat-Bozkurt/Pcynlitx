
#include "data_holder.h"

data_holder::data_holder(){

    this->matrix_size = 0;

    this->chunks_per_inter = 0;

    this->chunks_in_inter_row = 0;

    this->offset = 0;

    this->matrix_t0 = nullptr;

    this->matrix_t1 = nullptr;

    this->matrix_t2 = nullptr;

    this->matrix_t3 = nullptr;

    this->duplicated_matrix = nullptr;
}

data_holder::~data_holder(){

};

void data_holder::receive_datas(int size, int chunks_per_inter, int chunks_in_inter_row, int offset, float * a){

     this->matrix_size = size;

     this->chunks_per_inter = chunks_per_inter;

     this->chunks_in_inter_row = chunks_in_inter_row;

     this->offset = offset;

     this->matrix_t0 = a;
}

int data_holder::get_chunks_per_inter(){

    return this->chunks_per_inter;
}

int data_holder::get_chunks_in_inter_row(){

    return this->chunks_in_inter_row;
}

int data_holder::get_offset(){

    return this->offset;
}

float * data_holder::get_Matrix_Th0(){

      return this->matrix_t0;
};

float * data_holder::get_Matrix_Th1(){

      return this->matrix_t1;
};

float * data_holder::get_Matrix_Th2(){

      return this->matrix_t2;
};

float * data_holder::get_Matrix_Th3(){

      return this->matrix_t3;
};

float * data_holder::get_duplicated_matrix(){

       return this->duplicated_matrix;
}

int data_holder::get_Matrix_Size(){

     return this->matrix_size;
}

void data_holder::set_Matrix_Th0(float * matrix){

     this->matrix_t0 = matrix;
}

void data_holder::set_Matrix_Th1(float * matrix){

     this->matrix_t1 = matrix;
}

void data_holder::set_Matrix_Th2(float * matrix){

     this->matrix_t2 = matrix;
}

void data_holder::set_Matrix_Th3(float * matrix){

     this->matrix_t3 = matrix;
}

void data_holder::set_duplicated_matrix(float * matrix){

     this->duplicated_matrix = matrix;
}

void data_holder::set_Matrix_Size(int size){

     this->matrix_size = size;
}

void data_holder::set_chunks_per_inter(int arg){

      this->chunks_per_inter = arg;
}

void data_holder::set_chunks_in_inter_row(int arg){

     this->chunks_in_inter_row;
}

void data_holder::set_offset(int arg){

     this->offset = arg;
}
