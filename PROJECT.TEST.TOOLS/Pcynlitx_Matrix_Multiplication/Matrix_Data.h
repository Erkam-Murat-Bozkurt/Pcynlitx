
#ifndef MATRIX_DATA_H
#define MATRIX_DATA_H

class Matrix_Data
{
public:
  Matrix_Data();
  Matrix_Data(const Matrix_Data & orig);
  virtual ~Matrix_Data();
  void Receive_Matrix_Size(int matrix_size);
  void Print_Random_Matrix(double *** pointer);
  void Receive_Start_Row(int thread_number, int start_row);
  void Receive_End_Row(int thread_number, int start_row);
  int  Get_Start_Row(int thread_number);
  int  Get_End_Row(int thread_number);
  int  Get_Matrix_Size();
private:
  int sections[4][2];
  int Matrix_Size;
};

#endif /* MATRIX_DATA_H */
