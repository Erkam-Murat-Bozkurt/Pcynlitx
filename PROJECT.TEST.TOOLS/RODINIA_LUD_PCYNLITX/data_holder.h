
#ifndef DATA_HOLDER_H
#define DATA_HOLDER_H

class data_holder
{
public:
  data_holder();
  virtual ~data_holder();
  void receive_datas(int size, int chunks_per_inter, int chunks_in_inter_row, int offset, float * a);
  int get_chunks_per_inter();
  int get_chunks_in_inter_row();
  int get_offset();
  float * get_Matrix_Th0();
  float * get_Matrix_Th1();
  float * get_Matrix_Th2();
  float * get_Matrix_Th3();
  float * get_duplicated_matrix();
  int  get_Matrix_Size();
  void set_Matrix_Size(int size);
  void set_chunks_per_inter(int arg);
  void set_chunks_in_inter_row(int arg);
  void set_offset(int arg);
  void set_Matrix_Th0(float * mt0);
  void set_Matrix_Th1(float * mt1);
  void set_Matrix_Th2(float * mt2);
  void set_Matrix_Th3(float * mt3);
  void set_duplicated_matrix(float * m);
private:
  int size;
  int chunks_per_inter;
  int chunks_in_inter_row;
  int offset;
  int matrix_size;
  float * matrix_t0;
  float * matrix_t1;
  float * matrix_t2;
  float * matrix_t3;
  float * duplicated_matrix;
};






#endif /* DATA_HOLDER_H */
