
#ifndef DATA_RECORDER_H
#define DATA_RECORDER_H

#include <cstring>
#include <string>
#include <iostream>

struct Record_Data {

    std::string string_line;

    bool record_status;

    int  position;
};

struct Thread_Record_Data {

    int record_number;

    int thread_number;
};

class Data_Recorder
{
public:
  Data_Recorder();
  virtual ~Data_Recorder();
  void Receive_Data_Size(int size);
  void Set_Thread_Record_Data(int index, int thread_number);
  void Set_Thread_Data_Size(int size);
  void Set_Record_Data(std::string string_line, int i);
  int  Get_Record_Data_Size() const;
  int  Get_Data_Position(int index);
  bool Get_Data_Record_Status(int index);
  int  Get_Recorded_Thread_Number(int index) const;
  int  Get_Record_Number(int index) const;
  int  Get_Thread_Record_Data_Size();
  std::string Get_String_Data(int index) const;
protected:
  void Allocate_Memory_For_Each_Line(int size);
  void Clear_Dynamic_Memory();
  bool Memory_Delete_Condition;
  int  Record_Data_Size;
  int  Thread_Data_Size;
  int  Record_Index;
  Record_Data ** Record_Data_Pointer;
  Thread_Record_Data * Thread_Data_Pointer;
};

#endif /* DATA_RECORDER_H */
