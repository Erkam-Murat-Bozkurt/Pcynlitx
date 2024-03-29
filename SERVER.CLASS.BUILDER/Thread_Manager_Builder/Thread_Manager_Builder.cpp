
/*

Copyright ©  2021,  Erkam Murat Bozkurt

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

#include "Thread_Manager_Builder.h"

Thread_Manager_Builder::Thread_Manager_Builder(){

    this->Memory_Delete_Condition = false;

    this->Compiler_Command = nullptr;

    this->Constructed_Include_Directory = nullptr;
};

Thread_Manager_Builder::Thread_Manager_Builder(const Thread_Manager_Builder & orig){

};

Thread_Manager_Builder::~Thread_Manager_Builder(){

     if(!this->Memory_Delete_Condition){

        this->Clear_Dynamic_Memory();
     }
};

void Thread_Manager_Builder::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        if(this->Compiler_Command != nullptr){

           delete [] this->Compiler_Command;

           this->Compiler_Command = nullptr;
        }

        this->Locker_Builder.Clear_Dynamic_Memory();
     }
}

void Thread_Manager_Builder::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Pointer){

     this->Reader_Pointer = Pointer;

     this->HeaderFileBuilder.Receive_Descriptor_File_Reader(this->Reader_Pointer);

     this->Locker_Builder.Receive_Descriptor_File_Reader(this->Reader_Pointer);

     this->Data_Manager_Builder.Receive_Descriptor_File_Reader(this->Reader_Pointer);
}

void Thread_Manager_Builder::Receive_Constructed_Include_Directory(char * Directory){

     this->Constructed_Include_Directory = Directory;

     this->Data_Manager_Builder.Receive_Constructed_Include_Directory(Directory);
}

void Thread_Manager_Builder::Build_Thread_Manager(){

     this->Memory_Delete_Condition = false;

     this->Directory_Manager.DetermineCurrentDirectory();

     this->Determine_Compiler_Command();

     this->Locker_Builder.Build_Thread_Locker();

     this->Data_Manager_Builder.Build_Thread_Data_Manager();

     this->HeaderFileBuilder.Build_Thread_Manager_Header_File();

     char * name_space = this->Reader_Pointer->Get_Namespace();

     this->FileManager.SetFilePath("Thread_Manager.cpp");

     this->FileManager.FileOpen(RWCf);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n #include \"Thread_Manager.h\"");

     this->FileManager.WriteToFile("\n");



     // CONSTRUCTOR IMPLEMENTATION ----------------------------------------------------

     this->FileManager.WriteToFile("\n ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::Thread_Manager(){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Total_Thread_Number = ");

     int Total_Thread_Number = this->Reader_Pointer->Get_Thread_Number();

     char * Thread_Number = this->Translater.Translate(Total_Thread_Number);

     this->FileManager.WriteToFile(Thread_Number);

     this->FileManager.WriteToFile(";");

     int Thread_Function_Number = this->Reader_Pointer->Get_Thread_Function_Number();

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Thread_Function_Number = ");

     this->FileManager.WriteToFile(this->Translater.Translate(Thread_Function_Number));

     this->FileManager.WriteToFile(";");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Operational_Thread_Number = this->Total_Thread_Number;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Function_enter_counter_with_rescuer_thread = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Function_enter_counter = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->waiting_thread_number_in_barrier = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Thread_On_Point_Wait = -1;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Data_Manager.Initialize_Thread_Data();");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");



     // COPY CONSTRUCTOR--------------------------------------------------------------------------------------

     this->FileManager.WriteToFile("\n ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::Thread_Manager(const Thread_Manager & orig){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");


     // DESTRUCTOR IMPLEMENTATION ----------------------------------------------------------------------------

     this->FileManager.WriteToFile("\n ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::~Thread_Manager(){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");


     // MUTEX LOCK IMPLEMENTATION ----------------------------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::lock(){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Outside_Locker.lock();");

     this->FileManager.WriteToFile("\n }");

     this->FileManager.WriteToFile("\n");



     // MUTEX UNLOCK IMPLEMENTATION ------------------------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::unlock(){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Outside_Locker.unlock();");

     this->FileManager.WriteToFile("\n }");

     this->FileManager.WriteToFile("\n");




     // BARRIER WAIT FUNCTION IMPLEMENTATION ---------------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::barrier_wait(){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         std::unique_lock<std::mutex> barrier_wait_lock(this->mtx_barrier_wait);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->waiting_thread_number_in_barrier++;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         if(this->waiting_thread_number_in_barrier < this->Total_Thread_Number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n            this->cv.wait(barrier_wait_lock);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n            barrier_wait_lock.unlock();");

     this->FileManager.WriteToFile("\n         }");

     this->FileManager.WriteToFile("\n         else{");

     this->FileManager.WriteToFile("\n                barrier_wait_lock.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                this->waiting_thread_number_in_barrier = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                for(int i=0;i<(this->Total_Thread_Number)-1;i++){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                     this->cv.notify_one();");

     this->FileManager.WriteToFile("\n               }");

     this->FileManager.WriteToFile("\n        }");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");



     // WAIT ( INT NUMBER, INT RESCUER ) FUNCTION IMPLEMENTATION -----------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::wait(int Number, int Rescuer_Thread){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      std::unique_lock<std::mutex> Function_lock(this->mtx_two_parameter_wait);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int Thread_Number = this->Data_Manager.Get_Thread_Number();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      bool rescue_condition = this->Data_Manager.Get_Rescue_Permission(Rescuer_Thread);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(((Thread_Number == Number) || ((Thread_Number == Rescuer_Thread) && rescue_condition))){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n           this->Data_Manager.Increase_Wait_Enter_Counter(Number);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n           if(this->Data_Manager.Get_Wait_Enter_Counter(Number) > 1){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n              if(Thread_Number == Number){;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                 this->Data_Manager.Set_Wait_Enter_Counter(Number,0);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                 this->Data_Manager.Activate_Thread(Rescuer_Thread);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                 Function_lock.unlock();");

     this->FileManager.WriteToFile("\n              }");

     this->FileManager.WriteToFile("\n              else{");

     this->FileManager.WriteToFile("\n                       this->Data_Manager.Set_Wait_Enter_Counter(Number,0);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                       this->Data_Manager.Activate_Thread(Number);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                       Function_lock.unlock();");

     this->FileManager.WriteToFile("\n               }");

     this->FileManager.WriteToFile("\n          }");

     this->FileManager.WriteToFile("\n          else{");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                 if(Thread_Number == Rescuer_Thread){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                    this->Data_Manager.Stop_Thread(&Function_lock,Rescuer_Thread);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                 }");

     this->FileManager.WriteToFile("\n                 else {");

     this->FileManager.WriteToFile("\n                          this->Data_Manager.Stop_Thread(&Function_lock,Number);");

     this->FileManager.WriteToFile("\n                 }");

     this->FileManager.WriteToFile("\n          }");

     this->FileManager.WriteToFile("\n     }");

     this->FileManager.WriteToFile("\n     else{");

     this->FileManager.WriteToFile("\n              Function_lock.unlock();");

     this->FileManager.WriteToFile("\n      };");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");




     // RESCUE (INT NUMBER, INT RESCUER_THREAD) ---------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::rescue(int Number, int Rescuer_Thread){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      std::unique_lock<std::mutex> Function_lock(this->mtx_two_parameter_wait);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(this->Data_Manager.Get_Thread_Number() == Rescuer_Thread){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Data_Manager.Set_Rescue_Permission(Rescuer_Thread,true);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         Function_lock.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->wait(Number,Rescuer_Thread);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Data_Manager.Set_Rescue_Permission(Rescuer_Thread,false); ");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n      else{");

     this->FileManager.WriteToFile("\n               Function_lock.unlock();");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n }");

     this->FileManager.WriteToFile("\n");





     // WAIT (INT NUMBER) --------------------------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::wait(int Number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      std::unique_lock<std::mutex> thread_lock(this->Thread_Mutex[Number]);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Data_Manager.Stop_Thread(&thread_lock,Number);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      thread_lock.unlock();");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");



     // RESCUE (INT NUMBER) ----------------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::rescue(int Number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Data_Manager.Activate_Thread(Number);");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");



     // START SERIAL (INT START_NUMBER, INT END_NUMBER) ----------------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::start_serial(int start_number, int end_number, int thread_number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(thread_number > start_number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->wait(thread_number,thread_number-1);");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");



     // END SERIAL (INT START_NUMBER, INT END_NUMBER) ----------------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::end_serial(int start_number, int end_number, int thread_number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n     if(thread_number < (end_number -1)){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n          this->rescue(thread_number+1,thread_number);");

     this->FileManager.WriteToFile("\n     }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n     if(thread_number == start_number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n       this->wait(start_number,end_number-1);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n     }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n     if(thread_number == (end_number-1)){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->rescue(start_number,end_number-1);");

     this->FileManager.WriteToFile("\n     }");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");




     // REF_WAIT (INT NUMBER) --------------------------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::switch_wait(int Number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         std::unique_lock<std::mutex> thread_lock(this->mtx_switch_wait);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         if(this->Data_Manager.Get_Thread_Number() == Number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n            if(this->Thread_On_Point_Wait!= -1){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n               this->Data_Manager.Activate_Thread(this->Thread_On_Point_Wait);");

     this->FileManager.WriteToFile("\n            }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n            this->Thread_On_Point_Wait = Number;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n            if(!this->Data_Manager.Get_Dead_Lock_Risk()){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                this->Data_Manager.Stop_Thread(&thread_lock,this->Thread_On_Point_Wait);");

     this->FileManager.WriteToFile("\n            }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n            thread_lock.unlock();");

     this->FileManager.WriteToFile("\n         }");

     this->FileManager.WriteToFile("\n         else{");

     this->FileManager.WriteToFile("\n                   thread_lock.unlock();");

     this->FileManager.WriteToFile("\n         };");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");


     // WAIT(STD::STRING FUNCTION_NAME) ----------------------------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::wait(std::string Function_Name){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int Function_Number = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Data_Manager.Get_Thread_Function_Name_Number(Function_Name,&Function_Number);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      std::unique_lock<std::mutex> Function_lock(this->Function_Mutex[Function_Number]);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int Thread_Number = this->Data_Manager.Get_Thread_Number();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(this->Data_Manager.Get_Function_Name(Thread_Number) == Function_Name){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         int Function_Member_Number = this->Data_Manager.Get_Function_Member_Number(Function_Name);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Data_Manager.Increase_Function_Wait_Enter_Counter(Function_Name);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         if(this->Data_Manager.Get_Function_Wait_Enter_Counter(Function_Name) < Function_Member_Number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n            this->Data_Manager.Stop_Thread(&Function_lock,Thread_Number);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n            Function_lock.unlock();");

     this->FileManager.WriteToFile("\n         }");

     this->FileManager.WriteToFile("\n         else{");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                this->Data_Manager.Set_Function_Wait_Enter_Counter(Function_Name,0);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                this->Data_Manager.Rescue_Function_Members(Function_Name);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                Function_lock.unlock();");

     this->FileManager.WriteToFile("\n         }");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n      else{");

     this->FileManager.WriteToFile("\n                Function_lock.unlock();");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n }");

     this->FileManager.WriteToFile("\n");



     // WAIT(STD::STRING FUNCTION_NAME, INT RESCUER_THREAD) ---------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::wait(std::string Function_Name, int Rescuer_Thread){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int Function_Number = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Data_Manager.Get_Thread_Function_Name_Number(Function_Name,&Function_Number);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      std::unique_lock<std::mutex> Function_lock(this->Two_Pr_Function_Mutex[Function_Number]);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int Thread_Number = this->Data_Manager.Get_Thread_Number();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(((Thread_Number == Rescuer_Thread ) || (this->Data_Manager.Get_Function_Name(Thread_Number) == Function_Name))){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n           if(Thread_Number == Rescuer_Thread){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n              int status = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n              this->Data_Manager.Set_Block_Function_Wait_Status(Function_Name,status);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n              this->Data_Manager.Set_Function_Rescue_Permission(Function_Name,true);");

     this->FileManager.WriteToFile("\n           }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n           this->Data_Manager.Increase_Two_Prm_Function_Wait_Enter_Counter(Function_Name);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n           int Member_Number = this->Data_Manager.Get_Function_Member_Number(Function_Name);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n           int Enter_Counter = this->Data_Manager.Get_Two_Prm_Function_Wait_Enter_Counter(Function_Name);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n           bool Rescue_Permission = this->Data_Manager.Get_Function_Rescue_Permission(Function_Name);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n           if(((Enter_Counter == (Member_Number+1)) && Rescue_Permission )){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                this->Data_Manager.Set_Two_Prm_Function_Wait_Enter_Counter(Function_Name,0);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                if(this->Data_Manager.Get_Thread_Number() != Rescuer_Thread){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                      this->Data_Manager.Activate_Thread(Rescuer_Thread);");

     this->FileManager.WriteToFile("\n                }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                this->Data_Manager.Rescue_Function_Members(Function_Name);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                Function_lock.unlock();");

     this->FileManager.WriteToFile("\n           }");

     this->FileManager.WriteToFile("\n           else{");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                 int status = 1;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                 this->Data_Manager.Set_Block_Function_Wait_Status(Function_Name,status);");

     this->FileManager.WriteToFile("\n");


     this->FileManager.WriteToFile("\n                 this->Data_Manager.Stop_Thread(&Function_lock,Thread_Number);");   // Thread Stop Point

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                 Function_lock.unlock();");

     this->FileManager.WriteToFile("\n           }");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n      else{");

     this->FileManager.WriteToFile("\n              Function_lock.unlock();");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n }");

     this->FileManager.WriteToFile("\n");


     // RESCUE(STD::STRING FUNCTION_NAME, INT RESCUER_THREAD) ----------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::rescue(std::string Function_Name, int Rescuer_Thread){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int Function_Number = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Data_Manager.Get_Thread_Function_Name_Number(Function_Name,&Function_Number);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      std::unique_lock<std::mutex> Function_lock(this->Two_Pr_Function_Mutex[Function_Number]);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(this->Data_Manager.Get_Thread_Number() == Rescuer_Thread){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         Function_lock.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->wait(Function_Name,Rescuer_Thread);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Data_Manager.Set_Rescue_Permission(Rescuer_Thread,false); ");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n      else{");

     this->FileManager.WriteToFile("\n            Function_lock.unlock();");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n }");

     this->FileManager.WriteToFile("\n");


     // EXIT FUNCTION IMPLEMENTATION ----------------------------------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::Exit(){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Data_Manager.Exit();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Check_Is_There_Waiting_Until_Exit();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");


     // WAIT UNTIL EXIT ----------------------------------------------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::wait_until_exit(int Number, int Rescuer_Thread) {");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n     this->Data_Manager.Wait_Thread_Termination(Number,Rescuer_Thread);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n     this->wait(Number,Rescuer_Thread);");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");


     // CHECK WAIT UNTIL EXIT ------------------------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::Check_Is_There_Waiting_Until_Exit() {");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n     int Thread_Number = this->Data_Manager.Get_Thread_Number();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n     if(this->Data_Manager.Get_Thread_Waits_This_Thread_Termination(Thread_Number) != -1){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n        this->rescue(this->Data_Manager.Get_Thread_Waits_This_Thread_Termination(Thread_Number),Thread_Number);");

     this->FileManager.WriteToFile("\n     }");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");



     // RECEIVE THREAD ID ---------------------------------------------------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::Receive_Thread_ID(std::string Function_Name, int Thread_Number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Data_Manager.Receive_Thread_ID(Function_Name,Thread_Number);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");


     // GET THREAD NUMBER  ---------------------------------------------------------------------------------------------------

     this->FileManager.WriteToFile("\n int ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::Get_Thread_Number(){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      return this->Data_Manager.Get_Thread_Number();");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");


     // GET BLOCK STATUS  ---------------------------------------------------------------------------------------------------

     this->FileManager.WriteToFile("\n bool ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::Get_Thread_Block_Status(int Thread_Number) const {");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      return this->Data_Manager.Get_Thread_Block_Status(Thread_Number);");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");



     // GET BLOCK STATUS  ---------------------------------------------------------------------------------------------------

     this->FileManager.WriteToFile("\n int ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::Get_Operational_Thread_Number() const{");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      return this->Data_Manager.Get_Operational_Thread_Number();");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");



     // YEILD  ---------------------------------------------------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::function_switch(std::string function_1, std::string function_2){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int thr_num_func_1 = this->Data_Manager.GetFirstThreadExecutingFunction(function_1);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int thr_num_func_2 = this->Data_Manager.GetFirstThreadExecutingFunction(function_2);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int func_2_block_status = this->Data_Manager.Get_Block_Function_Wait_Status(function_2);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(func_2_block_status > 0){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->rescue(function_2,thr_num_func_1);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->wait(function_1,thr_num_func_2);");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");


     // YEILD  ---------------------------------------------------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::reset_function_switch(std::string function_1, std::string function_2){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int thr_num_func_1 = this->Data_Manager.GetFirstThreadExecutingFunction(function_1);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int thr_num_func_2 = this->Data_Manager.GetFirstThreadExecutingFunction(function_2);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int func_1_block_status = this->Data_Manager.Get_Block_Function_Wait_Status(function_1);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int func_2_block_status = this->Data_Manager.Get_Block_Function_Wait_Status(function_2);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(func_1_block_status > 0){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->rescue(function_1,thr_num_func_2);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(func_2_block_status > 0){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->rescue(function_2,thr_num_func_1);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");



     // YEILD  ---------------------------------------------------------------------------------------------------

     this->FileManager.WriteToFile("\n void ");

     this->FileManager.WriteToFile(name_space);

     this->FileManager.WriteToFile("::Thread_Manager::yield(){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      std::this_thread::yield;");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.FileClose();

     this->FileManager.Clear_Dynamic_Memory();

     this->Directory_Manager.Clear_Dynamic_Memory();
}

void Thread_Manager_Builder::Determine_Compiler_Command(){

     char Process_Command [] = "g++ -c -std=c++17 ";

     char Source_File_Name [] = "Thread_Manager.cpp";

     char Header_File_Name [] = "Thread_Manager.h";

     char Thread_Data_Manager_Header [] = "Thread_Data_Manager.h";

     char Locker_Class_Header_File_Name [] = "Thread_Locker.h";

     char Include_Word [] = "-include";

     char Include_Directory_Determiner [] = {'-','I','\0'};

     char Thread_Library_Name [] =  "-lwinpthread";

     char Space_Character [] = {' ','\0'};

     char Output_Redirection_Command [] = "2>";

     char Error_Message_File_Name [] = {'/','C','o','m','p','i','l','e','r','_','O','u','t','p','u','t','\0'};


     size_t Source_File_Name_Size = strlen(Source_File_Name);

     size_t Header_File_Name_Size = strlen(Header_File_Name);

     size_t Locker_Class_Header_File_Name_Size = strlen(Locker_Class_Header_File_Name);

     size_t Thread_Data_Manager_Header_Builder_String_Size = strlen(Thread_Data_Manager_Header);

     size_t Process_Command_Name_Size = strlen(Process_Command);

     size_t Thread_Library_Name_Size = strlen(Thread_Library_Name);

     size_t Include_Word_Name_Size = strlen(Include_Word);

     size_t Include_Directory_Determiner_Size = strlen(Include_Directory_Determiner);

     size_t Current_Directory_Name_Size = strlen(this->Directory_Manager.GetCurrentlyWorkingDirectory());

     size_t Compiler_Command_Size = Source_File_Name_Size + Header_File_Name_Size

                                + Process_Command_Name_Size + Thread_Library_Name_Size

                                + Current_Directory_Name_Size + Locker_Class_Header_File_Name_Size

                                + Include_Word_Name_Size + Include_Directory_Determiner_Size

                                + Thread_Data_Manager_Header_Builder_String_Size;

     this->Compiler_Command = new char [10*Compiler_Command_Size];

     int index_counter = 0;

     this->Place_Information(&this->Compiler_Command,Process_Command,&index_counter);

     this->Place_Information(&this->Compiler_Command,Include_Directory_Determiner,&index_counter);

     this->Place_Information(&this->Compiler_Command,this->Directory_Manager.GetCurrentlyWorkingDirectory(),&index_counter);

     this->Place_Information(&this->Compiler_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_Command,Source_File_Name,&index_counter);

     this->Place_Information(&this->Compiler_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_Command,Include_Word,&index_counter);

     this->Place_Information(&this->Compiler_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_Command,Header_File_Name,&index_counter);

     this->Place_Information(&this->Compiler_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_Command,Include_Word,&index_counter);

     this->Place_Information(&this->Compiler_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_Command,Thread_Data_Manager_Header,&index_counter);

     this->Place_Information(&this->Compiler_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_Command,Include_Word,&index_counter);

     this->Place_Information(&this->Compiler_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_Command,Locker_Class_Header_File_Name,&index_counter);

     this->Place_Information(&this->Compiler_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_Command,Thread_Library_Name,&index_counter);

     this->Place_Information(&this->Compiler_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_Command,Output_Redirection_Command,&index_counter);

     this->Place_Information(&this->Compiler_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_Command,this->Reader_Pointer->Get_Construction_Point(),&index_counter);

     this->Place_Information(&this->Compiler_Command,Error_Message_File_Name,&index_counter);

     this->Compiler_Command[index_counter] = '\0';
}

void Thread_Manager_Builder::Remove_Source_File(){

     char Source_File_Name [] = "Thread_Manager.cpp";

     char Locker_Class_Name [] ="Thread_Locker.cpp";

     char Directory_Character [] = {'/','\0'};

     char * Construction_Point = this->Reader_Pointer->Get_Construction_Point();

     size_t Construction_Point_Size = strlen(Construction_Point);

     size_t Source_File_Name_Size = strlen(Source_File_Name);

     size_t Locker_Class_Name_Size = strlen(Locker_Class_Name);

     size_t Source_File_Path_Size = Source_File_Name_Size + Construction_Point_Size;

     size_t Locker_Class_Path_Size = Locker_Class_Name_Size + Construction_Point_Size;

     char * Source_File_Path = new char [10*Source_File_Path_Size];

     int index_counter = 0;

     this->Place_Information(&Source_File_Path,Construction_Point,&index_counter);

     this->Place_Information(&Source_File_Path,Directory_Character,&index_counter);

     this->Place_Information(&Source_File_Path,Source_File_Name,&index_counter);

     Source_File_Path[index_counter] = '\0';

     this->FileManager.Delete_File(Source_File_Path);

     delete [] Source_File_Path;

     char * Locker_Class_Path = new char [10*Locker_Class_Path_Size];

     index_counter = 0;

     this->Place_Information(&Locker_Class_Path,Construction_Point,&index_counter);

     this->Place_Information(&Locker_Class_Path,Directory_Character,&index_counter);

     this->Place_Information(&Locker_Class_Path,Locker_Class_Name,&index_counter);

     Locker_Class_Path[index_counter] = '\0';

     this->FileManager.Delete_File(Locker_Class_Path);

     delete [] Locker_Class_Path;
}

void Thread_Manager_Builder::Remove_Header_Extra_File(){

     char Header_Extra_File [] = "Thread_Manager.h.gch";

     char Directory_Character [] = {'/','\0'};

     char * Construction_Point = this->Reader_Pointer->Get_Construction_Point();

     size_t Construction_Point_Size = strlen(Construction_Point);

     size_t Header_File_Name_Size = strlen(Header_Extra_File);

     size_t File_Path_Size = Construction_Point_Size  + Header_File_Name_Size;

     char * File_Path = new char [10*File_Path_Size];

     int index_counter = 0;

     this->Place_Information(&File_Path,Construction_Point,&index_counter);

     this->Place_Information(&File_Path,Directory_Character,&index_counter);

     this->Place_Information(&File_Path,Header_Extra_File,&index_counter);

     File_Path[index_counter] = '\0';

     if(this->FileManager.Is_Path_Exist(File_Path)){

        this->FileManager.Delete_File(File_Path);
     }

     delete [] File_Path;
}

void Thread_Manager_Builder::Move_Header_File(){

     char Header_File_Name [] = "Thread_Manager.h";

     char Directory_Character [] = {'/','\0'};

     char * Construction_Point = this->Reader_Pointer->Get_Construction_Point();

     size_t Target_Directory_Size = strlen(this->Constructed_Include_Directory);

     size_t Header_File_Name_Size = strlen(Header_File_Name);

     size_t Construction_Point_Size = strlen(Construction_Point);

     size_t Current_Path_Size = Construction_Point_Size + Header_File_Name_Size;

     size_t Target_Path_Size = Target_Directory_Size + Header_File_Name_Size;

     char * Current_Path = new char [10*Current_Path_Size];

     int index_counter = 0;

     this->Place_Information(&Current_Path,Construction_Point,&index_counter);

     this->Place_Information(&Current_Path,Directory_Character,&index_counter);

     this->Place_Information(&Current_Path,Header_File_Name,&index_counter);

     Current_Path[index_counter] = '\0';

     char * Target_Path  = new char [10*Target_Path_Size];

     index_counter = 0;

     this->Place_Information(&Target_Path,this->Constructed_Include_Directory,&index_counter);

     this->Place_Information(&Target_Path,Directory_Character,&index_counter);

     this->Place_Information(&Target_Path,Header_File_Name,&index_counter);

     Target_Path[index_counter] = '\0';

     this->FileManager.Move_File(Current_Path,Target_Path);

     delete [] Current_Path;

     delete [] Target_Path;

     char Locker_Class_Header_File_Name [] = "Thread_Locker.h";

     size_t Locker_Class_Header_File_Current_Path_Size = strlen(Locker_Class_Header_File_Name) + Construction_Point_Size;

     char * Locker_Path = new char [10*Locker_Class_Header_File_Current_Path_Size];

     index_counter = 0;

     this->Place_Information(&Locker_Path,Construction_Point,&index_counter);

     this->Place_Information(&Locker_Path,Directory_Character,&index_counter);

     this->Place_Information(&Locker_Path,Locker_Class_Header_File_Name,&index_counter);

     Locker_Path[index_counter] = '\0';

     size_t Locker_Target_Path_Size = Target_Directory_Size + strlen(Locker_Class_Header_File_Name);

     char * Locker_Target_Path = new char [10*Locker_Target_Path_Size];

     index_counter = 0;

     this->Place_Information(&Locker_Target_Path,this->Constructed_Include_Directory,&index_counter);

     this->Place_Information(&Locker_Target_Path,Directory_Character,&index_counter);

     this->Place_Information(&Locker_Target_Path,Locker_Class_Header_File_Name,&index_counter);

     Locker_Target_Path[index_counter] = '\0';

     this->FileManager.Move_File(Locker_Path,Locker_Target_Path);

     delete [] Locker_Path;

     delete [] Locker_Target_Path;
}


void Thread_Manager_Builder::Build_Output_Stream_File(){

     std::string path = "Compiler_Output";

     this->FileManager.SetFilePath(path);

     this->FileManager.FileOpen(RWCf);

     this->FileManager.FileClose();
}

void Thread_Manager_Builder::Run_System_Commands(){

     this->Build_Output_Stream_File();

     int system_return_value = system(this->Compiler_Command);

     if(system_return_value != 0){

        std::cout << "\n";

        std::cerr << "An error occured in Thread_Manager class compiling.." << std::endl;

        std::cout << "\n";

        exit(1);
     }

     this->Locker_Builder.Run_System_Commands();

     this->Data_Manager_Builder.Run_System_Commands();

     this->Remove_Source_File();

     this->Remove_Header_Extra_File();

     this->Move_Header_File();
}

void Thread_Manager_Builder::Place_Information(char ** Pointer, char * Information, int * Counter){

     size_t Information_Size = strlen(Information);

     for(size_t i=0;i<Information_Size;i++){

        (*Pointer)[(*Counter)] = Information[i];

        (*Counter)++;
     }
}
