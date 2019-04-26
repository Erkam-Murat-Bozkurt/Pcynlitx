
/*

Copyright ©  2019,  Erkam Murat Bozkurt

This file is part of the research project which is carried by Erkam Murat Bozkurt.

This is a free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation
either version 3 of the License, or any later version.

This software is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.

*/

#include "Thread_Manager_Header_File_Builder.h"

Thread_Manager_Header_File_Builder::Thread_Manager_Header_File_Builder(){

};

Thread_Manager_Header_File_Builder::Thread_Manager_Header_File_Builder(const Thread_Manager_Header_File_Builder & orig){

};

Thread_Manager_Header_File_Builder::~Thread_Manager_Header_File_Builder(){

};

void Thread_Manager_Header_File_Builder::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Pointer){

     this->Reader_Pointer = Pointer;
}

void Thread_Manager_Header_File_Builder::Build_Thread_Manager_Header_File(){

     int Thread_Function_Number = this->Reader_Pointer->Get_Thread_Function_Number();

     int Thread_Number = this->Reader_Pointer->Get_Thread_Number();

     this->FileManager.SetFilePath("Thread_Manager.h");

     this->FileManager.FileOpen(RWC);

     this->FileManager.WriteToFile("\n #ifndef THREAD_MANAGER_H");

     this->FileManager.WriteToFile("\n #define THREAD_MANAGER_H");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n #include \"Thread_Locker.h\"");

     this->FileManager.WriteToFile("\n #include <thread>");

     this->FileManager.WriteToFile("\n #include <mutex>");

     this->FileManager.WriteToFile("\n #include <iostream>");

     this->FileManager.WriteToFile("\n #include <string>");

     this->FileManager.WriteToFile("\n #include <cstdlib>");

     this->FileManager.WriteToFile("\n #include <semaphore.h>");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n class Thread_Manager");

     this->FileManager.WriteToFile("\n {");

     this->FileManager.WriteToFile("\n public:");

     this->FileManager.WriteToFile("\n  Thread_Manager();");

     this->FileManager.WriteToFile("\n  Thread_Manager(const Thread_Manager & orig);");

     this->FileManager.WriteToFile("\n  virtual ~Thread_Manager();");

     this->FileManager.WriteToFile("\n  void lock();");

     this->FileManager.WriteToFile("\n  void unlock();");

     this->FileManager.WriteToFile("\n  void barier_wait();");

     this->FileManager.WriteToFile("\n  void wait(int Number);");

     this->FileManager.WriteToFile("\n  void wait(int * wait_list, int wait_list_size, int rescuer_thread_number);");

     this->FileManager.WriteToFile("\n  void wait(int Number, int Rescuer_Thread);");

     this->FileManager.WriteToFile("\n  void wait_until_exit(int Number, int Rescuer_Thread);");

     this->FileManager.WriteToFile("\n  void wait(std::string Function_Name, int Rescuer_Thread_Number);");

     this->FileManager.WriteToFile("\n  void wait(std::string Function_Name);");

     this->FileManager.WriteToFile("\n  void Exit();");

     this->FileManager.WriteToFile("\n  void rescue(int Number);");

     this->FileManager.WriteToFile("\n  void rescue(int Number, int Rescuer_Thread_Number);");

     this->FileManager.WriteToFile("\n  void rescue(int * wait_list, int wait_list_size, int rescuer_thread_number);");

     this->FileManager.WriteToFile("\n  void rescue(std::string Function_Name, int Rescuer_Thread_Number);");

     this->FileManager.WriteToFile("\n  void Receive_Thread_ID(std::string Function_Name, int Thread_Number);");

     this->FileManager.WriteToFile("\n  int Get_Thread_Number();");

     this->FileManager.WriteToFile("\n  int Get_Operational_Thread_Number() const;");

     this->FileManager.WriteToFile("\n  bool Get_Block_Status(int Thread_Number);");

     this->FileManager.WriteToFile("\n private:");

     this->FileManager.WriteToFile("\n  void Clear_Send_Rescue_Signal_Conditions();");

     this->FileManager.WriteToFile("\n  void Check_Is_There_Waiting_Until_Exit();");

     this->FileManager.WriteToFile("\n  Thread_Locker Outside_Locker;");

     this->FileManager.WriteToFile("\n  Thread_Locker Inside_Locker;");

     this->FileManager.WriteToFile("\n  struct Thread_Data");

     this->FileManager.WriteToFile("\n  {");

     this->FileManager.WriteToFile("\n     std::thread::id Thread_ID_Number;");

     this->FileManager.WriteToFile("\n     int  Thread_Number;");

     this->FileManager.WriteToFile("\n     int  wait_enter_counter;");

     this->FileManager.WriteToFile("\n     int  wait_untill_exit_thread_number;");

     this->FileManager.WriteToFile("\n     std::string Thread_Function_Name;");

     this->FileManager.WriteToFile("\n     sem_t Thread_Semaphore;");

     this->FileManager.WriteToFile("\n     bool Thread_Operational_Status;");

     this->FileManager.WriteToFile("\n     bool Send_Rescue_Signal_Enter_Condition;");

     this->FileManager.WriteToFile("\n     bool block_condition;");

     this->FileManager.WriteToFile("\n  };");

     this->FileManager.WriteToFile("\n  struct Function_Names_Data");

     this->FileManager.WriteToFile("\n  {");

     this->FileManager.WriteToFile("\n     int Function_Number;");

     this->FileManager.WriteToFile("\n     int Member_Counter;");

     this->FileManager.WriteToFile("\n     bool Signaling_Condition;");

     this->FileManager.WriteToFile("\n     bool barier_pass_condition;");

     this->FileManager.WriteToFile("\n     int Barier_Enter_Counter;");

     this->FileManager.WriteToFile("\n     int Barier_Exit_Counter;");

     this->FileManager.WriteToFile("\n     std::string Thread_Function_Name;");

     this->FileManager.WriteToFile("\n     sem_t function_block_wait;");

     this->FileManager.WriteToFile("\n  };");

     this->FileManager.WriteToFile("\n  void Get_Thread_Function_Name_Number(std::string Function_Name, int * Function_Name_Number);");

     this->FileManager.WriteToFile("\n  sem_t barier_wait_function;");

     this->FileManager.WriteToFile("\n  sem_t list_wait;");

     this->FileManager.WriteToFile("\n  std::mutex thread_exit_mutex;");

     this->FileManager.WriteToFile("\n  std::mutex get_thread_number_mutex;");

     this->FileManager.WriteToFile("\n  std::mutex function_block_wait_mutex[");

     this->FileManager.WriteToFile(this->Translater.Translate(Thread_Function_Number));

     this->FileManager.WriteToFile("];");

     this->FileManager.WriteToFile("\n  std::mutex function_wait_mutex[");

     this->FileManager.WriteToFile(this->Translater.Translate(Thread_Function_Number));

     this->FileManager.WriteToFile("];");

     this->FileManager.WriteToFile("\n  int Total_Thread_Number;");

     this->FileManager.WriteToFile("\n  int Operational_Thread_Number;");

     this->FileManager.WriteToFile("\n  int Thread_Function_Number;");

     this->FileManager.WriteToFile("\n  Thread_Data Thread_Data_List[");

     this->FileManager.WriteToFile(this->Translater.Translate(Thread_Number));

     this->FileManager.WriteToFile("];");

     this->FileManager.WriteToFile("\n  Function_Names_Data Function_Names_Data_List[");

     this->FileManager.WriteToFile(this->Translater.Translate(Thread_Function_Number));

     this->FileManager.WriteToFile("];");

     this->FileManager.WriteToFile("\n  int waiting_thread_number_in_barier;");

     this->FileManager.WriteToFile("\n  int entered_thread_number_for_wait_function;");

     this->FileManager.WriteToFile("\n  bool wait_list_setup_condition;");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n #endif");

     this->FileManager.FileClose();

     this->FileManager.Clear_Dynamic_Memory();
}
