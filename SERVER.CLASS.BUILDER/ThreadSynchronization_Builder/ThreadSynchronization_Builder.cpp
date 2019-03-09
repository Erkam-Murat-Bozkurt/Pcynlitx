
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

#include "ThreadSynchronization_Builder.h"

ThreadSynchronization_Builder::ThreadSynchronization_Builder(){

    this->Memory_Delete_Condition = false;

    this->Compiler_Command = nullptr;

    this->Supervisor_Constructed_Include_Directory = nullptr;
};

ThreadSynchronization_Builder::ThreadSynchronization_Builder(const ThreadSynchronization_Builder & orig){

};

ThreadSynchronization_Builder::~ThreadSynchronization_Builder(){

     if(!this->Memory_Delete_Condition){

        this->Clear_Dynamic_Memory();
     }
};

void ThreadSynchronization_Builder::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        if(this->Compiler_Command != nullptr){

           delete [] this->Compiler_Command;

           this->Compiler_Command = nullptr;
        }

        this->Locker_Builder.Clear_Dynamic_Memory();
     }
}

void ThreadSynchronization_Builder::Receive_Process_Supervisor_Descriptor_File_Reader(Process_Supervisor_Descriptor_File_Reader * Pointer){

     this->Reader_Pointer = Pointer;

     this->HeaderFileBuilder.Receive_Process_Supervisor_Descriptor_File_Reader(Pointer);

     this->Locker_Builder.Receive_Construction_Point(this->Reader_Pointer->Get_Construction_Point());
}

void ThreadSynchronization_Builder::Receive_Supervisor_Newly_Constructed_Include_Directory(char * Directory){

     this->Supervisor_Constructed_Include_Directory = Directory;

     this->Locker_Builder.Receive_Supervisor_Newly_Constructed_Include_Directory(Directory);
}

void ThreadSynchronization_Builder::Build_ThreadSynchronization(){

     this->Memory_Delete_Condition = false;

     this->Directory_Manager.DetermineCurrentDirectory();

     this->Determine_Compiler_Command();

     this->Locker_Builder.Build_Thread_Locker();

     this->HeaderFileBuilder.Build_ThreadSynchronization_Header_File();

     this->FileManager.SetFilePath("ThreadSynchronization.cpp");

     this->FileManager.FileOpen(RWC);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n #include \"ThreadSynchronization.h\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n ThreadSynchronization::ThreadSynchronization(){");

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

     this->FileManager.WriteToFile("\n      for(int i=0;i<this->Total_Thread_Number;i++){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n          this->Thread_Data_List[i].Thread_Number = -1;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n          this->Thread_Data_List[i].wait_enter_counter = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n          this->Thread_Data_List[i].Send_Rescue_Signal_Enter_Condition = false;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n          this->Thread_Data_List[i].wait_untill_exit_thread_number = -1;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n          sem_init(&(this->Thread_Data_List[i].Thread_Semaphore),0,0);");

     this->FileManager.WriteToFile("\n      };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int return_value = 0;");

     this->FileManager.WriteToFile("\n");

     for(int i=0;i<Thread_Function_Number;i++){

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n      this->Function_Names_Data_List[");

         this->FileManager.WriteToFile(this->Translater.Translate(i));

         this->FileManager.WriteToFile("].Thread_Function_Name = \"");

         this->FileManager.WriteToFile(this->Reader_Pointer->Get_Thread_Function_Names()[i]);

         this->FileManager.WriteToFile("\";");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n      this->Function_Names_Data_List[");

         this->FileManager.WriteToFile(this->Translater.Translate(i));

         this->FileManager.WriteToFile("].Function_Number = ");

         this->FileManager.WriteToFile(this->Translater.Translate(i));

         this->FileManager.WriteToFile(";");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n      this->Function_Names_Data_List[");

         this->FileManager.WriteToFile(this->Translater.Translate(i));

         this->FileManager.WriteToFile("].Member_Counter = 0;");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n      this->Function_Names_Data_List[");

         this->FileManager.WriteToFile(this->Translater.Translate(i));

         this->FileManager.WriteToFile("].Barier_Enter_Counter = 0;");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n      this->Function_Names_Data_List[");

         this->FileManager.WriteToFile(this->Translater.Translate(i));

         this->FileManager.WriteToFile("].Barier_Exit_Counter = 0;");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n      this->Function_Names_Data_List[");

         this->FileManager.WriteToFile(this->Translater.Translate(i));

         this->FileManager.WriteToFile("].Signaling_Condition = false;");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n      this->Function_Names_Data_List[");

         this->FileManager.WriteToFile(this->Translater.Translate(i));

         this->FileManager.WriteToFile("].barier_pass_condition = false;");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n      return_value = sem_init(");

         this->FileManager.WriteToFile("&(this->Function_Names_Data_List[");

         this->FileManager.WriteToFile(this->Translater.Translate(i));

         this->FileManager.WriteToFile("].function_block_wait),0,0);");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n      if(return_value != 0){");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n            std::cout << \"\\n\\n The semaphore can not be initialized !..\";");

         this->FileManager.WriteToFile("\n      }");

         this->FileManager.WriteToFile("\n");
     }

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->entered_thread_number_for_wait_function = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->entered_thread_number_for_barier_wait_function = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->waiting_thread_number_in_barier = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->wait_list_setup_condition = false;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->barier_wait_setup_condition = false;");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n ThreadSynchronization::ThreadSynchronization(const ThreadSynchronization & orig){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n ThreadSynchronization::~ThreadSynchronization(){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::lock(){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Outside_Locker.lock();");

     this->FileManager.WriteToFile("\n }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::unlock(){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Outside_Locker.unlock();");

     this->FileManager.WriteToFile("\n }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::barier_wait(){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(this->barier_wait_setup_condition == false){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->barier_wait_setup_condition = true;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->entered_thread_number_for_barier_wait_function = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->waiting_thread_number_in_barier = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         int return_value = sem_init(&this->barier_wait_function,0,0);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         if(return_value != 0){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n            printf(\"\\n\\n [ ERROR ] In Syncronier class, barier_wait function; the semaphore can not be initialized !..\");");

     this->FileManager.WriteToFile("\n         }");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->entered_thread_number_for_barier_wait_function++;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int Active_Thread_Number = this->Operational_Thread_Number - this->entered_thread_number_for_barier_wait_function;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(((Active_Thread_Number > 0) && (this->Operational_Thread_Number > 1))){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->waiting_thread_number_in_barier++;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         int wait_return_value = sem_wait(&this->barier_wait_function);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         if(wait_return_value == 0){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n            this->waiting_thread_number_in_barier--;");

     this->FileManager.WriteToFile("\n         }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n      else{");

     this->FileManager.WriteToFile("\n              this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->entered_thread_number_for_barier_wait_function--;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(this->waiting_thread_number_in_barier > 0){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         sem_post(&this->barier_wait_function);");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n      else{");

     this->FileManager.WriteToFile("\n                sem_destroy(&this->barier_wait_function);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                this->barier_wait_setup_condition = false;");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::wait(int * wait_list, int wait_list_size, int rescuer_thread){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      bool wait_enter_condition = false;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int Thread_Number = this->Get_Thread_Number();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      std::thread::id this_id = std::this_thread::get_id();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(this->wait_list_setup_condition == false){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->wait_list_setup_condition = true;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->entered_thread_number_for_wait_function = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         int return_value = sem_init(&this->list_wait,0,0);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         if(return_value != 0){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n            std::cout << \"\\n\\n The semaphore can not be initialized !..\";");

     this->FileManager.WriteToFile("\n         }");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      bool thread_rescue_condition = this->Thread_Data_List[rescuer_thread].Send_Rescue_Signal_Enter_Condition;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(((this->Thread_Data_List[rescuer_thread].Thread_ID_Number == this_id ) && thread_rescue_condition )){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         wait_enter_condition = true;");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n      else{");

     this->FileManager.WriteToFile("\n              for(int i=0;i< wait_list_size;i++){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                  if(this->Thread_Data_List[wait_list[i]].Thread_ID_Number == this_id ){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                     wait_enter_condition = true;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                     break;");

     this->FileManager.WriteToFile("\n                  };");

     this->FileManager.WriteToFile("\n              }");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(wait_enter_condition){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->entered_thread_number_for_wait_function++;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         bool Thread_Stop_Condition = false;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         if((((this->entered_thread_number_for_wait_function < (wait_list_size +1)) && !thread_rescue_condition ))){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n               Thread_Stop_Condition = true;");

     this->FileManager.WriteToFile("\n         }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         if(Thread_Stop_Condition){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n            sem_wait(&this->list_wait);");

     this->FileManager.WriteToFile("\n         }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         sem_post(&this->list_wait);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->entered_thread_number_for_wait_function--;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         if(this->entered_thread_number_for_wait_function == 0){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n             this->wait_list_setup_condition = false;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n             sem_destroy(&this->list_wait);");

     this->FileManager.WriteToFile("\n         }");

     this->FileManager.WriteToFile("\n     };");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::wait(int Number, int Rescuer_Thread){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int Thread_Number = this->Get_Thread_Number();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      bool thread_rescue_condition = this->Thread_Data_List[Rescuer_Thread].Send_Rescue_Signal_Enter_Condition;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      bool wait_enter_condition = false;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(Thread_Number == Number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n          wait_enter_condition = true;");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n      else{");

     this->FileManager.WriteToFile("\n               if(((Thread_Number == Rescuer_Thread) && (thread_rescue_condition))){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                     wait_enter_condition = true;");

     this->FileManager.WriteToFile("\n              }");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(wait_enter_condition){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Thread_Data_List[Number].wait_enter_counter++;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         if(this->Thread_Data_List[Number].wait_enter_counter > 1){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n             if(Thread_Number == Number){;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                      sem_post(&(this->Thread_Data_List[Rescuer_Thread].Thread_Semaphore));");

     this->FileManager.WriteToFile("\n             }");

     this->FileManager.WriteToFile("\n             else{");

     this->FileManager.WriteToFile("\n                      sem_post(&(this->Thread_Data_List[Number].Thread_Semaphore));");

     this->FileManager.WriteToFile("\n             }");

     this->FileManager.WriteToFile("\n         }");

     this->FileManager.WriteToFile("\n         else{");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                 if((Thread_Number == Rescuer_Thread) && (this->Thread_Data_List[Rescuer_Thread].Send_Rescue_Signal_Enter_Condition == true)){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                     this->Thread_Data_List[Rescuer_Thread].Send_Rescue_Signal_Enter_Condition = false; ");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                     sem_wait(&(this->Thread_Data_List[Thread_Number].Thread_Semaphore));");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                     this->Thread_Data_List[Number].wait_enter_counter = 0;");

     this->FileManager.WriteToFile("\n                 }");

     this->FileManager.WriteToFile("\n                 else {");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                           if(Thread_Number != Rescuer_Thread){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                              sem_wait(&(this->Thread_Data_List[Thread_Number].Thread_Semaphore));");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                              this->Thread_Data_List[Number].wait_enter_counter = 0;");

     this->FileManager.WriteToFile("\n                          }");

     this->FileManager.WriteToFile("\n                 }");

     this->FileManager.WriteToFile("\n         }");

     this->FileManager.WriteToFile("\n     }");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::wait(int Number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      sem_wait(&(this->Thread_Data_List[Number].Thread_Semaphore));");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::rescue(int Number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      sem_post(&(this->Thread_Data_List[Number].Thread_Semaphore));");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::rescue(int Number, int Rescuer_Thread){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(this->Thread_Data_List[Rescuer_Thread].Thread_ID_Number == std::this_thread::get_id()){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Thread_Data_List[Rescuer_Thread].Send_Rescue_Signal_Enter_Condition = true; ");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->wait(Number,Rescuer_Thread);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n          this->Clear_Send_Rescue_Signal_Conditions(); ");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::wait(std::string Function_Name){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int Function_Name_Number = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int Thread_Number = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Get_Thread_Function_Name_Number(Function_Name,&Function_Name_Number);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      Thread_Number = this->Get_Thread_Number();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(this->Thread_Data_List[Thread_Number].Thread_Function_Name == Function_Name){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->function_block_wait_mutex[Function_Name_Number].lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Function_Names_Data_List[Function_Name_Number].Barier_Enter_Counter++;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->function_block_wait_mutex[Function_Name_Number].unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->function_block_wait_mutex[Function_Name_Number].lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         if(this->Function_Names_Data_List[Function_Name_Number].Barier_Enter_Counter == this->Function_Names_Data_List[Function_Name_Number].Member_Counter){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n            this->Function_Names_Data_List[Function_Name_Number].Barier_Enter_Counter = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n            this->function_block_wait_mutex[Function_Name_Number].unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n            for(int i=0;i<this->Total_Thread_Number;i++){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                if(((this->Thread_Data_List[i].Thread_Function_Name == Function_Name) && (i != Thread_Number))){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                     if(this->Thread_Data_List[i].Thread_Operational_Status){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                        sem_post(&(this->Thread_Data_List[i].Thread_Semaphore));");

     this->FileManager.WriteToFile("\n                     }");

     this->FileManager.WriteToFile("\n                }");

     this->FileManager.WriteToFile("\n             }");

     this->FileManager.WriteToFile("\n          }");

     this->FileManager.WriteToFile("\n          else{");

     this->FileManager.WriteToFile("\n                 this->function_block_wait_mutex[Function_Name_Number].unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                 sem_wait(&(this->Thread_Data_List[Thread_Number].Thread_Semaphore));");

     this->FileManager.WriteToFile("\n          }");

     this->FileManager.WriteToFile("\n     }");

     this->FileManager.WriteToFile("\n }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::wait(std::string Function_Name, int Rescuer_Thread_Number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      bool Function_Enter_Condition = false;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      bool Barier_Pass_Condition = false;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int Function_Name_Number = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Get_Thread_Function_Name_Number(Function_Name,&Function_Name_Number);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int Thread_Number = this->Get_Thread_Number();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      std::thread::id this_id = std::this_thread::get_id();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(this->Thread_Data_List[Rescuer_Thread_Number].Thread_ID_Number == this_id){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Function_Names_Data_List[Function_Name_Number].Signaling_Condition = true;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         Function_Enter_Condition = true;");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(this->Thread_Data_List[Thread_Number].Thread_Function_Name == Function_Name){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         Function_Enter_Condition = true;");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(Function_Enter_Condition){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->function_wait_mutex[Function_Name_Number].lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Function_Names_Data_List[Function_Name_Number].Barier_Enter_Counter++;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         if(this->Function_Names_Data_List[Function_Name_Number].Barier_Enter_Counter == (this->Function_Names_Data_List[Function_Name_Number].Member_Counter+1)){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n            Barier_Pass_Condition = true;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n            this->Function_Names_Data_List[Function_Name_Number].Barier_Enter_Counter = 0;");

     this->FileManager.WriteToFile("\n         }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->function_wait_mutex[Function_Name_Number].unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         if((this->Function_Names_Data_List[Function_Name_Number].Signaling_Condition && Barier_Pass_Condition)){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n             for(int i=0;i<this->Total_Thread_Number;i++){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                if(((this->Thread_Data_List[i].Thread_Function_Name == Function_Name) && (i != Thread_Number))){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                     if(this->Thread_Data_List[i].Thread_Operational_Status){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                        sem_post(&(this->Thread_Data_List[i].Thread_Semaphore));");

     this->FileManager.WriteToFile("\n                     }");

     this->FileManager.WriteToFile("\n                }");

     this->FileManager.WriteToFile("\n             }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n             sem_post(&(this->Thread_Data_List[Rescuer_Thread_Number].Thread_Semaphore));");

     this->FileManager.WriteToFile("\n         }");

     this->FileManager.WriteToFile("\n         else{");

     this->FileManager.WriteToFile("\n                  if(this->Thread_Data_List[Rescuer_Thread_Number].Thread_ID_Number == this_id){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n                      sem_wait(&(this->Thread_Data_List[Rescuer_Thread_Number].Thread_Semaphore));");

     this->FileManager.WriteToFile("\n                  }");

     this->FileManager.WriteToFile("\n                  else{");

     this->FileManager.WriteToFile("\n                          sem_wait(&(this->Thread_Data_List[Thread_Number].Thread_Semaphore));");

     this->FileManager.WriteToFile("\n                  }");

     this->FileManager.WriteToFile("\n         }");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::rescue(std::string Function_Name, int Rescuer_Thread_Number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      std::thread::id this_id = std::this_thread::get_id();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(this->Thread_Data_List[Rescuer_Thread_Number].Thread_ID_Number == this_id ){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->wait(Function_Name,Rescuer_Thread_Number);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         this->Clear_Send_Rescue_Signal_Conditions(); ");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::rescue(int * wait_list, int wait_list_size, int Rescuer_Thread_Number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      std::thread::id this_id = std::this_thread::get_id();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(this->Thread_Data_List[Rescuer_Thread_Number].Thread_ID_Number == this_id){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n          this->Thread_Data_List[Rescuer_Thread_Number].Send_Rescue_Signal_Enter_Condition = true; ");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n          this->wait(wait_list,wait_list_size,Rescuer_Thread_Number);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n          this->Clear_Send_Rescue_Signal_Conditions(); ");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::Receive_Thread_ID(std::string Function_Name, int Thread_Number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      std::thread::id this_id = std::this_thread::get_id();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Thread_Data_List[Thread_Number].Thread_ID_Number = this_id;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Thread_Data_List[Thread_Number].Thread_Number = Thread_Number;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Thread_Data_List[Thread_Number].Thread_Function_Name = Function_Name;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int Function_Name_Number = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Thread_Data_List[Thread_Number].Thread_Operational_Status = true;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Get_Thread_Function_Name_Number(Function_Name,&Function_Name_Number);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Function_Names_Data_List[Function_Name_Number].Member_Counter++;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n int ThreadSynchronization::Get_Thread_Number(){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      std::thread::id this_id = std::this_thread::get_id();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Inside_Locker.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      for(int i=0;i<this->Total_Thread_Number;i++){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n          if(this->Thread_Data_List[i].Thread_ID_Number == this_id ){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n             return this->Thread_Data_List[i].Thread_Number;");

     this->FileManager.WriteToFile("\n          };");

     this->FileManager.WriteToFile("\n      };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::Get_Thread_Function_Name_Number(std::string Function_Name, int * Function_Name_Number){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      *Function_Name_Number = -1;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      for(int i=0;i<this->Thread_Function_Number;i++){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n          if(this->Function_Names_Data_List[i].Thread_Function_Name == Function_Name){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n             *Function_Name_Number = this->Function_Names_Data_List[i].Function_Number;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n              break;");

     this->FileManager.WriteToFile("\n          }");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      if(*Function_Name_Number == -1){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         std::cout << \"\\n\\n [Error] - The synchronizer object  can not determine the thread function names! \";");

     this->FileManager.WriteToFile("\n         std::cout << \"\\n\\n           Most probably, the synchronizer object recives a wrong name ! \";");

     this->FileManager.WriteToFile("\n         std::cout << \"\\n\\n           Please check the initialization of the synchronizer object.  \";");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         std::cout << \"\\n\\n \";");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n         exit(EXIT_FAILURE);");

     this->FileManager.WriteToFile("\n      }");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::Clear_Send_Rescue_Signal_Conditions(){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      for(int i=0;i<this->Total_Thread_Number;i++){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n          this->Thread_Data_List[i].Send_Rescue_Signal_Enter_Condition = false;");

     this->FileManager.WriteToFile("\n      };");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::Exit(){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->thread_exit_mutex.lock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Operational_Thread_Number--;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int Thread_Number = this->Get_Thread_Number();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Thread_Data_List[Thread_Number].Thread_Operational_Status = false;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      std::string Function_Name = this->Thread_Data_List[Thread_Number].Thread_Function_Name;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      int Function_Name_Number = 0;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Get_Thread_Function_Name_Number(Function_Name,&Function_Name_Number);");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Function_Names_Data_List[Function_Name_Number].Member_Counter--;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->Check_Is_There_Waiting_Until_Exit();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      this->thread_exit_mutex.unlock();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n int ThreadSynchronization::Get_Operational_Thread_Number() const {");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n      return this->Operational_Thread_Number;");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::wait_until_exit(int Number, int Rescuer_Thread) {");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n     this->Thread_Data_List[Rescuer_Thread].wait_untill_exit_thread_number = Number;");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n     this->wait(Number,Rescuer_Thread);");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n void ThreadSynchronization::Check_Is_There_Waiting_Until_Exit() {");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n     int Thread_Number = this->Get_Thread_Number();");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n     if(this->Thread_Data_List[Thread_Number].wait_untill_exit_thread_number != -1){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n        this->rescue(this->Thread_Data_List[Thread_Number].wait_untill_exit_thread_number,Thread_Number);");

     this->FileManager.WriteToFile("\n     }");

     this->FileManager.WriteToFile("\n };");

     this->FileManager.FileClose();

     this->FileManager.Clear_Dynamic_Memory();

     this->Directory_Manager.Clear_Dynamic_Memory();
}

void ThreadSynchronization_Builder::Determine_Compiler_Command(){

     char Process_Command [] = {'g','+','+',' ','-','c',' ','-','s','t','d','=','c','+','+','1','4',' ','\0'};

     char Source_File_Name [] = "ThreadSynchronization.cpp";

     char Header_File_Name [] = "ThreadSynchronization.h";

     char Locker_Class_Header_File_Name [] = "Thread_Locker.h";

     char Include_Word [] = "-include";

     char Include_Directory_Determiner [] = {'-','I','\0'};

     char Thread_Library_Name [] = {'-','l','p','t','h','r','e','a','d','\0'};

     char Space_Character [] = {' ','\0'};

     char Output_Redirection_Command [] = {'2','>','\0'};

     char Error_Message_File_Name [] = {'/','C','o','m','p','i','l','e','r','_','O','u','t','p','u','t','\0'};

     int Source_File_Name_Size = strlen(Source_File_Name);

     int Header_File_Name_Size = strlen(Header_File_Name);

     int Locker_Class_Header_File_Name_Size = strlen(Locker_Class_Header_File_Name);

     int Process_Command_Name_Size = strlen(Process_Command);

     int Thread_Library_Name_Size = strlen(Thread_Library_Name);

     int Include_Word_Name_Size = strlen(Include_Word);

     int Include_Directory_Determiner_Size = strlen(Include_Directory_Determiner);

     int Current_Directory_Name_Size = strlen(this->Directory_Manager.GetCurrentlyWorkingDirectory());

     int Compiler_Command_Size = Source_File_Name_Size + Header_File_Name_Size

                                + Process_Command_Name_Size + Thread_Library_Name_Size

                                + Current_Directory_Name_Size + Locker_Class_Header_File_Name_Size

                                + Include_Word_Name_Size + Include_Directory_Determiner_Size;

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

void ThreadSynchronization_Builder::Remove_Source_File(){

     char Source_File_Name [] = "ThreadSynchronization.cpp";

     char Locker_Class_Name [] ="Thread_Locker.cpp";

     char Directory_Character [] = {'/','\0'};

     char * Construction_Point = this->Reader_Pointer->Get_Construction_Point();

     int Construction_Point_Size = strlen(Construction_Point);

     int Source_File_Name_Size = strlen(Source_File_Name);

     int Locker_Class_Name_Size = strlen(Locker_Class_Name);

     int Source_File_Path_Size = Source_File_Name_Size + Construction_Point_Size;

     int Locker_Class_Path_Size = Locker_Class_Name_Size + Construction_Point_Size;

     char * Source_File_Path = new char [10*Source_File_Path_Size];

     int index_counter = 0;

     this->Place_Information(&Source_File_Path,Construction_Point,&index_counter);

     this->Place_Information(&Source_File_Path,Directory_Character,&index_counter);

     this->Place_Information(&Source_File_Path,Source_File_Name,&index_counter);

     Source_File_Path[index_counter] = '\0';

     this->FileManager.DeleteFile(Source_File_Path);

     delete [] Source_File_Path;

     char * Locker_Class_Path = new char [10*Locker_Class_Path_Size];

     index_counter = 0;

     this->Place_Information(&Locker_Class_Path,Construction_Point,&index_counter);

     this->Place_Information(&Locker_Class_Path,Directory_Character,&index_counter);

     this->Place_Information(&Locker_Class_Path,Locker_Class_Name,&index_counter);

     Locker_Class_Path[index_counter] = '\0';

     this->FileManager.DeleteFile(Locker_Class_Path);

     delete [] Locker_Class_Path;
}

void ThreadSynchronization_Builder::Remove_Header_Extra_File(){

     char Header_Extra_File [] = "ThreadSynchronization.h.gch";

     char Directory_Character [] = {'/','\0'};

     char * Construction_Point = this->Reader_Pointer->Get_Construction_Point();

     int Construction_Point_Size = strlen(Construction_Point);

     int Header_File_Name_Size = strlen(Header_Extra_File);

     int File_Path_Size = Construction_Point_Size  + Header_File_Name_Size;

     char * File_Path = new char [10*File_Path_Size];

     int index_counter = 0;

     this->Place_Information(&File_Path,Construction_Point,&index_counter);

     this->Place_Information(&File_Path,Directory_Character,&index_counter);

     this->Place_Information(&File_Path,Header_Extra_File,&index_counter);

     File_Path[index_counter] = '\0';

     this->FileManager.DeleteFile(File_Path);

     delete [] File_Path;
}


void ThreadSynchronization_Builder::Move_Header_File(){

     char Header_File_Name [] = "ThreadSynchronization.h";

     char Directory_Character [] = {'/','\0'};

     char * Construction_Point = this->Reader_Pointer->Get_Construction_Point();

     int Target_Directory_Size = strlen(this->Supervisor_Constructed_Include_Directory);

     int Header_File_Name_Size = strlen(Header_File_Name);

     int Construction_Point_Size = strlen(Construction_Point);

     int Current_Path_Size = Construction_Point_Size + Header_File_Name_Size;

     int Target_Path_Size = Target_Directory_Size + Header_File_Name_Size;

     char * Current_Path = new char [10*Current_Path_Size];

     int index_counter = 0;

     this->Place_Information(&Current_Path,Construction_Point,&index_counter);

     this->Place_Information(&Current_Path,Directory_Character,&index_counter);

     this->Place_Information(&Current_Path,Header_File_Name,&index_counter);

     Current_Path[index_counter] = '\0';

     char * Target_Path  = new char [10*Target_Path_Size];

     index_counter = 0;

     this->Place_Information(&Target_Path,this->Supervisor_Constructed_Include_Directory,&index_counter);

     this->Place_Information(&Target_Path,Directory_Character,&index_counter);

     this->Place_Information(&Target_Path,Header_File_Name,&index_counter);

     Target_Path[index_counter] = '\0';

     this->FileManager.Move_File(Target_Path,Current_Path);

     delete [] Current_Path;

     delete [] Target_Path;

     char Locker_Class_Header_File_Name [] = "Thread_Locker.h";

     int Locker_Class_Header_File_Current_Path_Size = strlen(Locker_Class_Header_File_Name) + Construction_Point_Size;

     char * Locker_Path = new char [10*Locker_Class_Header_File_Current_Path_Size];

     index_counter = 0;

     this->Place_Information(&Locker_Path,Construction_Point,&index_counter);

     this->Place_Information(&Locker_Path,Directory_Character,&index_counter);

     this->Place_Information(&Locker_Path,Locker_Class_Header_File_Name,&index_counter);

     Locker_Path[index_counter] = '\0';

     int Locker_Target_Path_Size = Target_Directory_Size + strlen(Locker_Class_Header_File_Name);

     char * Locker_Target_Path = new char [10*Locker_Target_Path_Size];

     index_counter = 0;

     this->Place_Information(&Locker_Target_Path,this->Supervisor_Constructed_Include_Directory,&index_counter);

     this->Place_Information(&Locker_Target_Path,Directory_Character,&index_counter);

     this->Place_Information(&Locker_Target_Path,Locker_Class_Header_File_Name,&index_counter);

     Locker_Target_Path[index_counter] = '\0';

     this->FileManager.Move_File(Locker_Target_Path,Locker_Path);

     delete [] Locker_Path;

     delete [] Locker_Target_Path;
}


void ThreadSynchronization_Builder::Run_System_Commands(){

     this->Locker_Builder.Run_System_Commands();

     int system_return_value = system(this->Compiler_Command);

     if(system_return_value != 0){

        std::cerr << "An error occured in ThreadSynchronization class compiling..";

        exit(1);
     }

     this->Remove_Source_File();

     this->Remove_Header_Extra_File();

     this->Move_Header_File();
}

void ThreadSynchronization_Builder::Place_Information(char ** Pointer, char * Information, int * Counter){

     int Information_Size = strlen(Information);

     for(int i=0;i<Information_Size;i++){

        (*Pointer)[(*Counter)] = Information[i];

        (*Counter)++;
     }
}
